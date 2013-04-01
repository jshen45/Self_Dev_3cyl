

//=============================================================================
//   device and simple io include files
//=============================================================================
#include "dd_crank.h"
#include "dd_crank_scheduler.h"
#include "io_conversion.h"
#include "io_config_tpu.h"
#include "io_config_crank.h"


#include "dd_pfi_interface.h"
#include "dd_spark_interface.h"


//=============================================================================
//   Constant Data Defines
//=============================================================================
#define CRANK_SECONDS_PER_MINUTE      (60)
#define CRANK_DEFAULT_RPM_PRECSION    (8)
//=============================================================================
//   Constant definitions
//=============================================================================
typedef struct
{
   uint8_t  previous_n_1;
   uint8_t  previous_1_n;

} IO_Crank_Gap_T;

typedef struct
{
   bitfield32_t  sync_second_revolution        :  1; // bit 31   @emem 
   bitfield32_t  sync_first_revolution         :  1; // bit 30,  @emem 
   bitfield32_t                                : 14; // bits
   bitfield32_t  transition_to_cam_backup      :  1; // bit 15,  @emem 
   bitfield32_t  cam_backup                    :  1; // bit 14,  @emem 
   bitfield32_t  stall_detected                :  1; // bit 13,  @emem 
   bitfield32_t  using_dynamic_scheduler       :  1; // bit 12,  @emem 
   bitfield32_t                                :  1; // bit 11,  @emem 
   bitfield32_t  engine_turning                :  1; // bit 10,  @emem 
   bitfield32_t  resync_attempt_in_prog        :  1; // bit  9,  @emem 
   bitfield32_t  valid_tooth                   :  1; // bit  8,  @emem 
   bitfield32_t  sync_started                  :  1; // bit  7,  @emem 
   bitfield32_t  run_reset_bypass_filter       :  1; // bit  6,  @emem 
   bitfield32_t  filter_enabled                :  1; // bit  5,  @emem 
   bitfield32_t  power_up                      :  1; // bit  4,  @emem 
   bitfield32_t  first_cylinder_event_occured  :  1; // bit  3,  @emem 
   bitfield32_t  sync_error_in_progress        :  1; // bit  2,  @emem 
   bitfield32_t  first_sync_occurred           :  1; // bit  1,  @emem 
   bitfield32_t  sync_occurred                 :  1; // bit  0,  @emem 


} CRANK_Flag_F_T;

typedef union
{
   CRANK_Flag_F_T F;
   uint32_t       U32;

}  CRANK_Flags_T;

typedef struct
{
   uint32_t         hi_res_reference_period;
   uint32_t         lo_res_reference_period;
   uint32_t         time_base;
   uint32_t         current_edge_time;
   uint32_t         edge_time;
   uint32_t         edge_angle;
   uint32_t         timer_value_raw;
   uint32_t         max_timer_value;
   uint32_t         filter_value;
   uint32_t         cylinder_event_reference_time;
   uint32_t         cylinder_event_reference_angle;
   uint32_t         initial_virtual_teeth_per_cylinder_event;
   uint32_t         virtual_teeth_per_cylinder_event;
   uint32_t         angle_at_cylinder_event;
   uint32_t         reference_tooth_error_count;
   uint32_t         current_tooth;
   uint32_t         angle_from_cylinder_event_to_tdc;
   uint32_t         number_of_gaps_detected;
   uint32_t         real_reference_period;
   uint32_t         stall_timeout;
   uint32_t         cam_history;
   uint32_t         engine_speed;
   uint32_t         current_edge_count;
}  CRANK_Parameters_F_T;

typedef union
{
   CRANK_Parameters_F_T F;
   uint32_t             U32[CRANK_PARAMETER_MAX];

}  CRANK_Parameters_T;

//Any events will have a problem knowing the correct pointer. These shall use the installed pointer
//It must be noted that the installed pointer shall have to be managed durring a transition to another crank backup mode.


//=============================================================================
// Variables available through crank_private for crank backup using cam.
//=============================================================================
uCrank_Count_T    CRANK_Current_Event_Tooth; //[1, 120]
uCrank_Count_T    CRANK_Current_Event_PA_Content;
uCrank_Count_T    CRANK_Next_Event_PA_Content;
uCrank_Count_T    CRANK_First_Cylinder_Event_Tooth;
uCrank_Count_T    CRANK_Synchronization_Start_Tooth;
uCrank_Count_T    CRANK_Error_Count_More;
uCrank_Count_T    CRANK_Error_Count_Less;
uCrank_Count_T    CRANK_Error_Count_More_Max;
uCrank_Count_T    CRANK_Error_Count_Less_Max;


//=============================================================================
// Local Variable Definitions
//=============================================================================
static uint32_t            CRANK_Real_Edge_Time_Current;
static uint32_t            CRANK_Real_Edge_Time_Previous;
static uint32_t            CRANK_Previous_Hi_Res_Reference_Time;
static uint32_t            CRANK_Hi_Res_Edge_Time;

static Crank_Cylinder_T    CRANK_Cylinder_ID;
static CRANK_Parameters_T  CRANK_Parameters;

static IO_Crank_Initialization_Parameters_T *CRANK_Initialization_Parameters;
static Crank_Cylinder_T    CRANK_Cylinder_ID_Even;


//=============================================================================
//   Local Variable Definitions
//=============================================================================
volatile uint32_t                CRANK_Tooth_Duration;
volatile CRANK_Flags_T           CRANK_Internal_State;
volatile uint32_t                CRANK_Filtered_Min_Tooth_Period;
volatile uint32_t                CRANK_Filtered_Max_Tooth_Period;
volatile uint8_t                 CRANK_Last_Cylinder_Event_Tooth;
volatile uint8_t                 CRANK_Valid_Sync_Period;
volatile uCrank_Count_T          CRANK_Tooth_Sync_Count;  // PA @ last sync


//=============================================================================
// /------------------------------------------------------------------------
// | Local Function declarations
// \------------------------------------------------------------------------
//=============================================================================

//=============================================================================
// OS_Engine_Stall_Reset
//=============================================================================
 void OS_Engine_Stall_Reset(void) ;
//=============================================================================
// CRANK_Process_Stall_Event
//=============================================================================
void CRANK_Process_Stall_Event(void) ;
//=============================================================================
// CRANK_Convert_Ref_Period_To_RPM
//=============================================================================
static uint32_t CRANK_Convert_Ref_Period_To_RPM( void);

//=============================================================================
// /------------------------------------------------------------------------
// | CRANK Initialization and reset functions
// \------------------------------------------------------------------------
//=============================================================================

//=============================================================================
// CRANK_Initialize
//=============================================================================
void CRANK_Initialize(
   IO_Crank_Initialization_Parameters_T  * const in_initialization_parameters )
{
   uint32_t counter;

   
      MCD5408_Initialize_Channel(
                       EPPWMT_TPU_INDEX,
                       &TPU,
                       TPU_CONFIG_IC_EPPWMT,
                      &EPPWMT_INIT);

   CRANK_Initialization_Parameters = in_initialization_parameters;

   CRANK_Synchronization_Start_Tooth = (uCrank_Count_T)CRANK_Convert_uCrank_Angle_To_Teeth(CRANK_Initialization_Parameters->synchronization_start_angle);
   CRANK_First_Cylinder_Event_Tooth = (uCrank_Count_T)CRANK_Convert_uCrank_Angle_To_Teeth(CRANK_Initialization_Parameters->first_cylinder_event_angle);

   CRANK_Parameters.F.time_base                                = TPU_TIMER_Get_Base_Frequency( EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT );
   CRANK_Parameters.F.max_timer_value                          = (uint32_t)( ( (1 << TPU_TIMER_Get_Size( ) ) -1 ) );
   CRANK_Parameters.F.filter_value = 200;
   CRANK_Parameters.F.initial_virtual_teeth_per_cylinder_event = CRANK_VIRTUAL_TEETH_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders;
   CRANK_Parameters.F.angle_from_cylinder_event_to_tdc         = CRANK_Initialization_Parameters->degrees_top_dead_center;

   // False selects the Angle Mode, True selects Edge Mode - May need to make selectable.
   MCD5408_Set_Angle_Clock_Mode( EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, EPPWMT_ANGLE_MODE_PLL );

     // clear the crank schedule table
   for( counter = 0; counter < CRANK_VIRTUAL_TEETH_PER_REVOLUTION; counter++ )
   {
      // clear events for all teeth
      CRANK_Schedule_Table[ counter ] = 0;
   }

   // Initialize Crank filter time
   MCD5408_Set_Filter_Time( EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT,
          CRANK_Parameters.F.filter_value ); // timer counts
   MCD5408_Set_IRQ_Enable(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT,(EPI_CRANK_GAP_DETECTED_IRQ_ENABLE |\
         EPI_CRANK_TOOTHPULSE_IRQ_ENABLE_1));   


}



//=============================================================================
//  Removes all assigned crank events from the synchronous schedule
// table, restores the powerup state of the state-machine,
// and reinitializes the hardware.
//
// Initialize crank configuration variables:
//  - Number of teeth per low resolution event( 30 for 4-cylinder
//    application, 20 for 6 cyclinder application)
//  - Degrees crankshaft per lo res event( 180 deg. for
//    4-cylinder application, 120 deg. for 6-cyl. application)
//  - tooth number of last lo res. event
//
//=============================================================================
void CRANK_Reset_Parameters( void )
{
   uCrank_Count_T new_gap_cnt;
   uint32_t       cs;
   uint32_t       time_base;


      CRANK_Parameters.F.virtual_teeth_per_cylinder_event = CRANK_VIRTUAL_TEETH_PER_REVOLUTION
                                               / CRANK_Initialization_Parameters->number_of_cylinders;

      CRANK_Last_Cylinder_Event_Tooth = (uint8_t)( CRANK_Synchronization_Start_Tooth
                                 + ( (uint32_t)( CRANK_Initialization_Parameters->number_of_cylinders - 1 )
                                     * CRANK_Parameters.F.virtual_teeth_per_cylinder_event ) );


      // Initialize Crank reference event related variables
      CRANK_Cylinder_ID = CRANK_CYLINDER_A;
      CRANK_Cylinder_ID_Even = CRANK_CYLINDER_A;
      CRANK_Parameters.F.lo_res_reference_period = 0x00FFFFFF;
      CRANK_Parameters.F.engine_speed= 0;
      CRANK_Parameters.F.reference_tooth_error_count = 0;
      CRANK_Parameters.F.number_of_gaps_detected = 0;

      time_base = TPU_TIMER_Get_Base_Frequency( EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT );

      // Magic number 60 is seconds per minute
      CRANK_Filtered_Min_Tooth_Period =
         ( time_base / ( ( CRANK_Initialization_Parameters->filter_max_rpm_for_synchronization * CRANK_VIRTUAL_TEETH_PER_CRANK ) / 60 ) );

      CRANK_Filtered_Max_Tooth_Period =
         ( time_base / ( ( CRANK_Initialization_Parameters->filter_min_rpm_for_synchronization * CRANK_VIRTUAL_TEETH_PER_CRANK ) / 60 ) );

      // init crank state flags
      CRANK_Internal_State.U32 = CRANK_INITIAL_INTERNAL_STATE;

      // Disable interrupts
      MCD5408_Disable_Host_Interrupt(
         EPPWMT_TPU_INDEX,
         &TPU,
         TPU_CONFIG_IC_EPPWMT);
	  
      CRANK_Internal_State.U32 = CRANK_Set_Sync_Second_Revolution( CRANK_Internal_State.U32, false );
	  
      new_gap_cnt = MCD5408_Get_IRQ_Count_At_Last_Interrupt( EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, CRANK_EPPE_IRQ_Select ) + CRANK_COUNT_MAX;
       MCD5408_Set_New_Gap_Count( EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, new_gap_cnt );
      MCD5408_Set_Previous_n_1(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT,0);
      MCD5408_Set_Previous_1_n(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT,0);

   // Call the Resync functions based on a stall event:
      CAM_Reset_Parameters();
      SPARK_Reset_Parameters();
      PFI_Reset_Parameters();
        //   IO_KNOCK_Reset_Parameters
      OS_Engine_Stall_Reset();  
}


//=============================================================================
// /-----------------------------------------------------------------------\
// |                    CRANK  MANAGEMENT FUNCTIONS
// \-----------------------------------------------------------------------/
//=============================================================================


//=============================================================================
//   CRANK EVENT :
//
// Lauch the routine(s) associated with the event(s) enabled for
// the current tooth. The priority order is SynEv15 down to SynEv0.
//=============================================================================
void CRANK_Manage_Execute_Event( void )
{
   int8_t   counter;
   uint32_t mask;
   uint32_t current_event;

   // Set the initial mask to be reduced each time through the loop:
   mask = UINT32_MAX;

   // Read the current row from the schedule table:
   current_event = CRANK_Schedule_Table[ CRANK_Current_Event_Tooth - 1 ];

   // Check each column of the schedule table:
  for( counter = CRANK_EVENT_ID_MAX - 1; counter > -1; counter-- )
   //	for( counter = 0; counter <CRANK_EVENT_ID_MAX; counter++ )
   {
      // Reduce the mask:
      mask &= ~(Mask32( counter, 1));

      // If the current event is selected (indicated by a '1' in the schedule
      // table), but the handler routine pointer is empty, a problem has occurred:
      //
      if( current_event & ( 0x1 << counter) )
      {

         // Call the handler routine in CRANK_Event_List which corresponds
         // to this bit in CRANK_Schedule_Table_Ptr[current_event]:
         //
         ( *CRANK_Event_List[ counter ] )();

         // If there are no more scheduled events on this tooth, exit:
         if( !( ( current_event ) & mask ) )
         {
            break;
         }
      }
   }

}


//=============================================================================
// /-----------------------------------------------------------------------\
// |    CRANK SYNCHRONIZATION LOGIC
// \-----------------------------------------------------------------------/
//=============================================================================

//=============================================================================
// CRANK SYNCHRONIZATION :
// Filter out spikes during crank due to low signal/noise ratio
// from the crank sensor. Before synchronising, the filter must be
// disable, so 5 consecutive valid teeth (within valid RPM range) must be seen
//=============================================================================
static void CRANK_Filter_Crank_Signal( void )
{
   if( CRANK_Get_Run_Reset_Bypass_Filter( CRANK_Internal_State.U32 ) )
   {
      CRANK_Internal_State.U32 = CRANK_Set_Filter_Enabled( CRANK_Internal_State.U32, false );
      CRANK_Internal_State.U32 = CRANK_Set_Sync_Started( CRANK_Internal_State.U32, true );
      CRANK_Internal_State.U32 = CRANK_Set_Run_Reset_Bypass_Filter( CRANK_Internal_State.U32, false );
   }
   else
   {
      // A tooth is valid if it corresponds to an engine speed
      // with tooth periods between the given min and max values or
      // we are measuring a gap tooth so the Max_Tooth_Period is not valid and could cause a stall.
       if( ( CRANK_Tooth_Duration > CRANK_Filtered_Min_Tooth_Period ) &&
            ( CRANK_Tooth_Duration< CRANK_Filtered_Max_Tooth_Period ) )
      
      {
         CRANK_Valid_Sync_Period++;
         // before disabling the filter:
         //
         CRANK_Internal_State.U32 = CRANK_Set_Valid_Tooth( CRANK_Internal_State.U32, true );
         if( CRANK_Valid_Sync_Period >= CRANK_Initialization_Parameters->valid_synchronization_tooth_periods )
         {
            CRANK_Internal_State.U32 = CRANK_Set_Engine_Turning( CRANK_Internal_State.U32, true );
            CRANK_Internal_State.U32 = CRANK_Set_Filter_Enabled( CRANK_Internal_State.U32, false );
            CRANK_Internal_State.U32 = CRANK_Set_Sync_Started( CRANK_Internal_State.U32, true );
            CRANK_Valid_Sync_Period = 0;
         }
      }
      else
      {
         CRANK_Valid_Sync_Period = 0;
      }
   }
}

unsigned int crank_test0;
unsigned int crank_test1;

//=============================================================================
// CRANK SYNCHRONIZATION :Get conditions met state
// Determine if the gap has been found.
//
// GAP determination scheme :
//     _   _        _____   _
//   _| V_| V______|     V_| V_
//
//   --><--><-----------><--><--
//            Double     Half
//            tooth      tooth
//
//   1) Half length tooth number - Double length tooth number = 1
//      to make sure that the gap pattern is identified on
//      consecutive teeth.
//
//   2) The half length tooth number is the number expected
//      to make sure that the gap is where it was expected
//
//=============================================================================
static bool CRANK_Gap_Cofirm( void )
{

   uCrank_Count_T previous_n_1;
   uCrank_Count_T previous_1_n;
   uCrank_Count_T tooth_count;
   bool           gap_detected = 0;

   previous_n_1 = MCD5408_Get_Previous_n_1(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT);
   previous_1_n = MCD5408_Get_Previous_1_n(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT);
       crank_test1++;
     if( // 1st criterion : gap at expected location
      (CRANK_Next_Event_PA_Content == previous_n_1 ) &&
       //-- 2nd criterion : gap pattern recognized
      ( ( uCrank_Count_T  )( previous_n_1 - previous_1_n ) == ( uCrank_Count_T  )1 ) )
     {
         crank_test0++;
	  if( !CRANK_Get_First_Sync_Occurred( CRANK_Internal_State.U32 ) )
	    {
                 // 1st GAP found
                 CRANK_Parameters.F.number_of_gaps_detected = 0;    
		   CRANK_Internal_State.U32 = CRANK_Set_Sync_Started( CRANK_Internal_State.U32, false );
		   CRANK_Internal_State.U32 = CRANK_Set_First_Sync_Occurred( CRANK_Internal_State.U32, true );
                 CRANK_Internal_State.U32 = CRANK_Set_Sync_First_Revolution( CRANK_Internal_State.U32, true );
                 CRANK_Internal_State.U32 = CRANK_Set_Sync_Second_Revolution( CRANK_Internal_State.U32, false );

		  // MCD5408_Set_Gap_Count(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, CRANK_ACTUAL_TEETH_PER_CRANK );
		   MCD5408_Set_Abs_Edge_Count(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT,2);
      
		   // Estimate when previous CylinderEvent would have occurred
		   CRANK_Parameters.F.cylinder_event_reference_time = ( CRANK_Parameters.F.edge_time -
                   ( (uint32_t)( CRANK_Tooth_Duration *
                   (  (uint8_t)( CRANK_Parameters.F.virtual_teeth_per_cylinder_event -
                                     ( CRANK_First_Cylinder_Event_Tooth -
                                       CRANK_Synchronization_Start_Tooth ) ) ) ) ) ) & 0x00FFFFFF;
           				 
	     }
	   else
	    {
                //eliminate  the tooth count  difference in each loop
		  if (CRANK_Current_Event_Tooth>CRANK_VIRTUAL_TEETH_PER_CRANK)
		  {
		     tooth_count = CRANK_Current_Event_Tooth - CRANK_VIRTUAL_TEETH_PER_CRANK;
		  }	
		  else
		  {
		     tooth_count = CRANK_Current_Event_Tooth;
		  }	 
                // Tooth count error calculation
	         if(	tooth_count == 2)
	         {
                    // Indicate that the synchronization not missed
                      CRANK_Internal_State.U32 = CRANK_Set_Sync_Error_In_Progress( CRANK_Internal_State.U32, false );
                      CRANK_Internal_State.U32 = CRANK_Set_Resync_Attempt_In_Prog( CRANK_Internal_State.U32, false );
			CRANK_Error_Count_More = 0;	
		       CRANK_Error_Count_Less = 0;
					  
	          }
		   else
		   {
		                       // Indicate that the synchronization has been missed
                      CRANK_Internal_State.U32 = CRANK_Set_Sync_Error_In_Progress( CRANK_Internal_State.U32, true );
                      CRANK_Internal_State.U32 = CRANK_Set_Resync_Attempt_In_Prog( CRANK_Internal_State.U32, true );
					  
                     if(tooth_count > 2)
                      {
                         CRANK_Error_Count_More = tooth_count - CRANK_VIRTUAL_TEETH_PER_CRANK;
				   
		          if(CRANK_Error_Count_More>CRANK_Error_Count_More_Max)
		           {
		               CRANK_Error_Count_More_Max = CRANK_Error_Count_More;
		            }	 
                      }
		       else
		       {
		          CRANK_Error_Count_Less =  CRANK_ACTUAL_TEETH_PER_CRANK -tooth_count;
			  
		          if(CRANK_Error_Count_Less>CRANK_Error_Count_Less_Max)
		            {
		              CRANK_Error_Count_Less_Max = CRANK_Error_Count_Less;
		           }
		       }
		   }
	          if(CRANK_Get_Sync_First_Revolution( CRANK_Internal_State.U32 ))
                 {
		       CRANK_Internal_State.U32 = CRANK_Set_Sync_First_Revolution( CRANK_Internal_State.U32, false );
                     CRANK_Internal_State.U32 = CRANK_Set_Sync_Second_Revolution( CRANK_Internal_State.U32, true );
                 }
	         else
	         {
		       MCD5408_Set_Abs_Edge_Count(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT,2);
		       CRANK_Internal_State.U32 = CRANK_Set_Sync_First_Revolution( CRANK_Internal_State.U32, true );
                     CRANK_Internal_State.U32 = CRANK_Set_Sync_Second_Revolution( CRANK_Internal_State.U32, false );
	          }

                 if(CRANK_Parameters.F.number_of_gaps_detected<0xFF)
                  {
		       CRANK_Parameters.F.number_of_gaps_detected++;
                  }	   
	   }	
	
	    //		
           CRANK_Internal_State.U32 = CRANK_Set_Sync_Occurred( CRANK_Internal_State.U32, true );
           MCD5408_Set_Gap_Count(EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT,CRANK_ACTUAL_TEETH_PER_CRANK);
           gap_detected = true;

      }
     return gap_detected;

}
//=============================================================================
// CRANK SYNCHRONIZATION : Search for the first gap.
// this function is accessed from the crank interrupt service
// routine when the first gap has not been detected
//=============================================================================
static void CRANK_Search_For_First_Gap( void )
{

   bool   sync_conditions_met;
   
   if( CRANK_Get_Power_Up( CRANK_Internal_State.U32 ) )
   {
      //
      // 1st time a GapSearch is done after powerup No prev. tooth time to get
      // duration.
      //
      CRANK_Internal_State.U32 = CRANK_Set_Power_Up( CRANK_Internal_State.U32, false );
   }
   else
   {
      if ( CRANK_Get_Filter_Enabled( CRANK_Internal_State.U32 ))
      {
         //
         // Filter out any spike due to low signal to noise ratio from the
         // sensor on the first teeth during crank.
         //
         CRANK_Filter_Crank_Signal();
      }
      else
      {
         CRANK_Internal_State.U32 = CRANK_Set_Engine_Turning( CRANK_Internal_State.U32, true );
         CRANK_Internal_State.U32 = CRANK_Set_Valid_Tooth( CRANK_Internal_State.U32, true );
         if( !CRANK_Get_Sync_Started( CRANK_Internal_State.U32 ) )
         {
            //
            // 2 intervals are needed for gap identification if the software
            // filter is disabled.
            //
            CRANK_Internal_State.U32 = CRANK_Set_Sync_Started( CRANK_Internal_State.U32, true );
         }
         else
         {
            // Perform the gap search
            sync_conditions_met =  CRANK_Gap_Cofirm( );

         }
      }

   }

}
//=============================================================================
//
//  Function:            CRANK_Process_Crank_Event
//=============================================================================
void CRANK_Process_Crank_Event( void )  
{
    bool             sync_conditions_met;
    EPPwMT_Coherent_Edge_Time_And_Count_T edgeTimeAndCount;
     uint32_t  temp_count;
	   uCrank_Count_T actual_irq_count;
   
    // Clear the interrupt flag: false == clear
    MCD5408_Set_Host_Interrupt_Status(EPPWMT_TPU_INDEX,&TPU,TPU_CONFIG_IC_EPPWMT,false);

   // Read the actual interrupt counter to see when we are being interrupted:
   actual_irq_count = MCD5408_Get_IRQ_Count_At_Last_Interrupt(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, CRANK_EPPE_IRQ_Select );

  
     // Read the current edge time and period from the PCP:
     CRANK_Parameters.F.edge_time  =  MCD5408_Get_Buffered_Edge_Time(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT,CRANK_EPPE_IRQ_Select);
     CRANK_Parameters.F.edge_angle = CRANK_Convert_Teeth_To_uCrank_Angle( actual_irq_count );

     CRANK_Tooth_Duration =MCD5408_Get_Period(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT);    
     CRANK_Hi_Res_Edge_Time = CRANK_Parameters.F.edge_time;	
     CRANK_Current_Event_Tooth = MCD5408_Get_Abs_Edge_Count(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT);
     CRANK_Parameters.F.current_tooth = CRANK_Current_Event_Tooth;

      // Check if first synchronization took place:
      if( !CRANK_Get_First_Sync_Occurred( CRANK_Internal_State.U32 ) )
      {
         // Look for the first synchronization:
         CRANK_Search_For_First_Gap();
      }
      else
      {
          if( !CRANK_Gap_Cofirm( ))
           {
	      CRANK_Manage_Execute_Event();  
            }
      }		  
		  
     temp_count =   CRANK_Next_Event_PA_Content;
     CRANK_Next_Event_PA_Content++;
	   
     // Set IRQ_Cnt to match Pulse_Cnt at the next sched. event
     // If the tooth at which the next interrupt should take
     // place is already passed, the EPPwMT Primitive mechanism will automa-
      // tically retrigger an interrupt to handle the passed
      // event.
     //We would not miss any tooth since there are a time buffer in etpu
     MCD5408_Set_New_IRQ_Count(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, CRANK_EPPE_IRQ_Select, CRANK_Next_Event_PA_Content );
     // get current count value   
    MCD5408_Get_Coherent_Edge_Time_And_Count( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT, &edgeTimeAndCount );
     CRANK_Current_Event_PA_Content = edgeTimeAndCount.Count;   	 
     if(temp_count!=CRANK_Current_Event_PA_Content)
	 		 	
     {
        if(CRANK_Current_Event_PA_Content - temp_count <0x0f)
        {
           // triger a HSR update if a tooth miss excuted 
           MCD5408_Update_IRQ_Count(EPPWMT_TPU_INDEX,&TPU, TPU_CONFIG_IC_EPPWMT);
        }
	else
	{
	  // error status
           CRANK_Process_Stall_Event();
	}  
     }
      	 

}

unsigned int crank_test3;
//=============================================================================
//
//  FUNCTION: CRANK_High_Priority_Cylinder_Event
//
//=============================================================================
void CRANK_High_Priority_Cylinder_Event( void )
{
      // crank_test3 ++;
   crank_test3 =CRANK_Current_Event_Tooth;
      // Update Irq tooth count at Cylinder Event
      CRANK_Parameters.F.angle_at_cylinder_event = (CRANK_Current_Event_PA_Content+1) << uCRANK_ANGLE_PRECISION;

      // Update CylinderEvent event period and time
      CRANK_Parameters.F.lo_res_reference_period =
         ( CRANK_Parameters.F.edge_time - CRANK_Parameters.F.cylinder_event_reference_time ) & 0x00FFFFFF;

      CRANK_Parameters.F.engine_speed = CRANK_Convert_Ref_Period_To_RPM();

      CRANK_Parameters.F.cylinder_event_reference_time = CRANK_Parameters.F.edge_time;

      CRANK_Parameters.F.cylinder_event_reference_angle = CRANK_Parameters.F.edge_angle;

      //Update real ref period
      CRANK_Real_Edge_Time_Current = MCD5408_Get_Real_Edge_Time(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT);

      CRANK_Parameters.F.real_reference_period = (CRANK_Real_Edge_Time_Current - CRANK_Real_Edge_Time_Previous)& 0x00FFFFFF;
      CRANK_Real_Edge_Time_Previous = CRANK_Real_Edge_Time_Current;

      //Set up stall timeout
  
      CRANK_Set_Flag( CRANK_FLAG_STALL_DETECTED, false );

      // Updates the crank filter time based on current Cylinder Event period
      MCD5408_Set_Filter_Time( EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, CRANK_Parameters.F.filter_value ); // timer counts

	// Perform High Priority Cylinder Event Event tasks
      //CRANK_Increment_Cylinder_Event_Counter
      if( CRANK_Cylinder_ID >= (uint16_t) CRANK_Initialization_Parameters->number_of_cylinders - 1 )
        {
           CRANK_Cylinder_ID = CRANK_CYLINDER_A;
	    HAL_GPIO_SET_MIL_Enable(~ HAL_GPIO_GET_MIL_Status());
         }
      else
       {
           CRANK_Cylinder_ID++;
       }

      CRANK_Cylinder_ID_Even = CRANK_Cylinder_ID/2;
	  
      //CRANK_Update_Hi_Res_Reference_Period
      CRANK_Parameters.F.hi_res_reference_period = (CRANK_Hi_Res_Edge_Time - CRANK_Previous_Hi_Res_Reference_Time) & UINT24_MAX;

      // Save current hi-res ref event time for next event
     CRANK_Previous_Hi_Res_Reference_Time = CRANK_Hi_Res_Edge_Time;

      // Clear fist cylinder event
      CRANK_Internal_State.U32 = CRANK_Set_First_Cylinder_Event_Occured( CRANK_Internal_State.U32, false );


}

//=============================================================================
// Enables the detection of the CRANK synchronization.
//=============================================================================
 void CRANK_Enable_Synchronization( void )
{
   EPPwMT_Coherent_Edge_Time_And_Count_T   edge_time_and_count;
   uint16_t                          first_tooth_count;
   uint32_t                         cs;

      // Schedule first EPPwMT Primitive crank interrupt on next tooth:
      MCD5408_Get_Coherent_Edge_Time_And_Count( EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, &edge_time_and_count );
      CRANK_Next_Event_PA_Content = edge_time_and_count.Count + 1;
      first_tooth_count = edge_time_and_count.Count + 1;

    //  CRANK_Setup_Next_Event( first_tooth_count );
	    MCD5408_Set_New_IRQ_Count(
         EPPWMT_TPU_INDEX,
         TPU_CONFIG_IC_EPPWMT,
         EPPWMT_IRQ_1, first_tooth_count);

      // Clear the interrupt flag: false == clear
      MCD5408_Set_Host_Interrupt_Status( EPPWMT_TPU_INDEX,&TPU,TPU_CONFIG_IC_EPPWMT, false );

      // Enable interrupts
      MCD5408_Enable_Host_Interrupt( EPPWMT_TPU_INDEX,&TPU,TPU_CONFIG_IC_EPPWMT);

}


//=============================================================================
// CRANK_Convert_To_Crank_Angle
//=============================================================================
Crank_Angle_T CRANK_Convert_To_Crank_Angle(
   int32_t in_signed_angle,
   uint8_t in_precision )
{
   uint32_t       unsigned_angle = (uint32_t)in_signed_angle;
   Crank_Angle_T  crank_angle;
   uint32_t       temp_count;

   if ( in_signed_angle < 0 )
   {
      unsigned_angle = ( 0 - unsigned_angle );

      temp_count = CRANK_Convert_Angle_To_uCrank_Angle( unsigned_angle, in_precision );

      crank_angle = (Crank_Angle_T)( ( temp_count > CRANK_ANGLE_MAX ) ? CRANK_ANGLE_MIN : -(int32_t)temp_count );
   }
   else
   {
      //
      // Convert to intermediate value( temp_count ) before converting to Crank_Angle_T
      //
      temp_count = CRANK_Convert_Angle_To_uCrank_Angle( unsigned_angle, in_precision );

      crank_angle = (Crank_Angle_T)( ( temp_count > CRANK_ANGLE_MAX ) ? CRANK_ANGLE_MAX : temp_count );
   }

   return( crank_angle );
}

//=============================================================================
// CRANK_Convert_To_uCrank_Angle
//=============================================================================
uCrank_Angle_T CRANK_Convert_To_uCrank_Angle(
   uint32_t in_unsigned_angle,
   uint8_t  in_precision )
{
   Crank_Angle_T  crank_angle;
   uint32_t       temp_count;

   temp_count = CRANK_Convert_Angle_To_uCrank_Angle( in_unsigned_angle, in_precision );

   crank_angle = (Crank_Angle_T)( ( temp_count > uCRANK_ANGLE_MAX ) ? uCRANK_ANGLE_MAX : temp_count );
   
   return( crank_angle );
}

//=============================================================================
// Crank Angle to Time conversion
//=============================================================================

//=============================================================================
// CRANK_Convert_uCrank_Angle_To_uTime
//=============================================================================
uint32_t CRANK_Convert_uCrank_Angle_To_uTime(
   uCrank_Angle_T  in_angle )
{
   uint32_t time;

   time = IO_Convert_uAngle_To_uTime(
      in_angle,
      uCRANK_ANGLE_PRECISION,
      CRANK_Parameters.F.lo_res_reference_period,
      ( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders ) );

   return ( time );
}

//=============================================================================
// CRANK_Convert_Crank_Angle_To_Time
//=============================================================================
int32_t CRANK_Convert_Crank_Angle_To_Time(
   Crank_Angle_T  in_angle )
{
   int32_t time;

   time = IO_Convert_Angle_To_Time(
      in_angle,
      uCRANK_ANGLE_PRECISION,
      CRANK_Parameters.F.lo_res_reference_period,
      ( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders ) );

   return ( time );
}

//=============================================================================
// CRANK_Convert_uTime_To_uCrank_Angle
//=============================================================================
uCrank_Angle_T CRANK_Convert_uTime_To_uCrank_Angle(
    uint32_t in_time )
{
   uCrank_Angle_T angle;

   angle = IO_Convert_uTime_To_uAngle(
      in_time,
      uCRANK_ANGLE_PRECISION,
      CRANK_Parameters.F.lo_res_reference_period,
      ( CRANK_SCHEDULE_CONFIG_VIRTUAL_TEETH_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders ) );

   return ( angle );
}

//=============================================================================
// CRANK_Convert_Time_To_Crank_Angle
//=============================================================================
Crank_Angle_T CRANK_Convert_Time_To_Crank_Angle(
    int32_t in_time )
{
   Crank_Angle_T angle;

   angle = (Crank_Angle_T)IO_Convert_Time_To_Angle(
      in_time,
      uCRANK_ANGLE_PRECISION,
      CRANK_Parameters.F.lo_res_reference_period,
      (uint8_t)( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders ) );

   return ( angle );
}

//=============================================================================
// Angle to Time conversion
//=============================================================================

//=============================================================================
// CRANK_Convert_uAngle_To_uTime
//
// @func
//
// @parm uint8_t | in_precision | for the angle.
//
// @rdesc none
//
// @end
//=============================================================================
uint32_t CRANK_Convert_uAngle_To_uTime(
   uint32_t in_angle,
   uint8_t  in_precision )
{
   uint32_t time;

   time = IO_Convert_uAngle_To_uTime(
      in_angle,
      in_precision,
      CRANK_Parameters.F.lo_res_reference_period,
      (uint8_t)( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders ) );

   return ( time );
}

//=============================================================================
// CRANK_Convert_Angle_To_Time
//
// @func
//
// @parm uint8_t | in_precision | for the angle.
//
// @rdesc none
//
// @end
//=============================================================================
int32_t CRANK_Convert_Angle_To_Time(
   int32_t  in_angle,
   uint8_t  in_precision )
{
   int32_t time;

   time = IO_Convert_Angle_To_Time(
      in_angle,
      in_precision,
      CRANK_Parameters.F.lo_res_reference_period,
      ( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders ) );

   return ( time );
}

//=============================================================================
// Time to Angle conversion
//=============================================================================

//=============================================================================
// CRANK_Convert_uTime_To_uAngle
//
// @func
//
// @parm uint8_t | in_precision | for the angle.
//
// @rdesc none
//
// @end
//=============================================================================
uint32_t CRANK_Convert_uTime_To_uAngle(
   uint32_t in_time,
   uint8_t  in_precision )
{
   uint32_t angle;

   angle = IO_Convert_uTime_To_uAngle(
      in_time,
      in_precision,
      CRANK_Parameters.F.lo_res_reference_period,
      ( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders ) );

   return ( angle );
}

//=============================================================================
// CRANK_Convert_Time_To_Angle
//
// @func
//
// @parm uint8_t | in_precision | for the angle.
//
// @rdesc none
//
// @end
//=============================================================================
int32_t CRANK_Convert_Time_To_Angle(
   int32_t  in_time,
   uint8_t  in_precision )
{
   int32_t angle;

   angle = IO_Convert_Time_To_Angle(
      in_time,
      in_precision,
      CRANK_Parameters.F.lo_res_reference_period,
      ( CRANK_NUMBER_OF_DEGREES_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders ) );

   return ( angle );
}

//=============================================================================
// CRANK_Convert_Ref_Period_To_RPM
//
// @func
//
// @parm uint8_t | in_precision | for the RPM.
//
// @rdesc uint32_t | RPM
//
// @end
//=============================================================================
uint32_t CRANK_Convert_Ref_Period_To_RPM( void )
{
   uint32_t engine_speed=0;
   uint8_t tooth_per_lores;
   uint8_t rpm_conv_factor;

  // tooth_per_lores = CRANK_SCHEDULE_VIRTUAL_TEETH_PER_REVOLUTION / CRANK_Initialization_Parameters->number_of_cylinders;

   //The conversion factor is applied to support other crank profiles like 24x,30x etc
   //rpm_conv_factor = (tooth_per_lores *CRANK_SECONDS_PER_MINUTE)/CRANK_VIRTUAL_TEETH_PER_CRANK;
   rpm_conv_factor = (CRANK_SECONDS_PER_MINUTE)/CRANK_VIRTUAL_TEETH_PER_CRANK;


   //Check if the reference period is valid
   if((0 < CRANK_Parameters.F.lo_res_reference_period)&&(CRANK_Parameters.F.lo_res_reference_period < 0xFFFFFF))
   {
      engine_speed = IO_Convert_Counts_To_Frequency(
         rpm_conv_factor,
         CRANK_DEFAULT_RPM_PRECSION,
         CRANK_Parameters.F.time_base,
         CRANK_Parameters.F.lo_res_reference_period);
   }
   return ( engine_speed );
}

//=============================================================================
// CRANK_Get_Cylinder_ID
//=============================================================================
Crank_Cylinder_T CRANK_Get_Cylinder_ID( void )
{
   return CRANK_Cylinder_ID;
}

//=============================================================================
// CRANK_Set_Cylinder_ID
// This function should only be called by cam!
//=============================================================================
void CRANK_Set_Cylinder_ID(
   Crank_Cylinder_T  in_id )
{
   CRANK_Cylinder_ID = in_id;
}


//=============================================================================
// CRANK_Get_Next_Cylinder_ID
//=============================================================================
Crank_Cylinder_T CRANK_Get_Next_Cylinder_ID( void )
{
   return CRANK_Get_Future_Cylinder_ID( 1 );
}


//=============================================================================
// CRANK_Get_Future_Cylinder_ID
//=============================================================================
Crank_Cylinder_T CRANK_Get_Future_Cylinder_ID(
   uint8_t  in_offset )
{
   Crank_Cylinder_T future_cylinder_id;
   Crank_Cylinder_T current_cylinder_id = CRANK_Get_Cylinder_ID();

   future_cylinder_id =  CRANK_Increment_Cylinder_ID( current_cylinder_id, (int8_t)(in_offset & INT8_MAX) );

   return future_cylinder_id;
}


//=============================================================================
// CRANK_Get_Future_Cylinder_ID
//=============================================================================
Crank_Cylinder_T CRANK_Increment_Cylinder_ID(
   Crank_Cylinder_T  in_current_id,
   int8_t            in_offset )
{
   int8_t future_cylinder_id;

   future_cylinder_id = (int8_t)in_current_id + in_offset;

   while ( future_cylinder_id < 0 )
   {
      //
      // Add number of cylinders so that we can handle any multiple of the cylinder
      // in the past passed in down to -128
      //
      future_cylinder_id += CRANK_Initialization_Parameters->number_of_cylinders;
   }

   if( future_cylinder_id >= CRANK_Initialization_Parameters->number_of_cylinders )
   {
      //
      // Do a %= so that we can handle any multiple of the cylinder
      // in the future passed in up to 127
      //
      future_cylinder_id %= CRANK_Initialization_Parameters->number_of_cylinders;
   }

   return (Crank_Cylinder_T)future_cylinder_id;
}

//=============================================================================
// CRANK_Get_Number_Of_Cylinders
//=============================================================================
uint8_t CRANK_Get_Number_Of_Cylinders( void )
{
   return CRANK_Initialization_Parameters->number_of_cylinders;
}

//=============================================================================
// CRANK_Get_First_Cylinder_Event_Angle
//=============================================================================
uCrank_Angle_T CRANK_Get_First_Cylinder_Event_Angle( void )
{
   return( CRANK_First_Cylinder_Event_Tooth * CRANK_DEGREES_PER_TOOTH );
}



//=============================================================================
// IO_PULSE_Convert_Counts_To_Time
// This function may return a value greater than the timer you are using can 
// support. Make sure that you mask it or check for saturation.
//=============================================================================
static uint32_t IO_PULSE_Convert_Counts_To_Time(
   uint32_t    counts_per_time,
   uint32_t    in_count,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution )
{
   uint32_t time;

   if ( !in_time_precision && !in_time_resolution )
   {
      time = in_count;
   }
   else
   {
      // Convert the raw counts to the values according to the math
      // library used.
      time = ( uint32_t )IO_Convert_Count_To_Time(
         in_count,
         counts_per_time,
         in_time_precision,
         in_time_resolution );
   }

   return time;
}


//=============================================================================
// CRANK_Get_Parameter
//=============================================================================
uint32_t CRANK_Get_Parameter(
   Crank_Parameter_T in_parameter,
   uint8_t           in_time_precision,
   uint8_t           in_time_resolution )
{
   uint32_t parameter_value;
   uint32_t value;
   uint32_t time_base = MCD5408_Get_Time_Base( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT);
   uint32_t    time;
    uint32_t    counts_per_time;

   switch ( in_parameter )
   {

   case   CRANK_PARAMETER_CURRENT_EDGE_TIME:
      {
         EPPwMT_Coherent_Edge_Time_And_Count_T edgeTimeAndCount;

         MCD5408_Get_Coherent_Edge_Time_And_Count( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT, &edgeTimeAndCount );

         CRANK_Parameters.F.current_edge_time = edgeTimeAndCount.Time;
      }
      break;
   case   CRANK_PARAMETER_TIMER_VALUE_RAW:
   	  counts_per_time = TPU_TIMER_Get_Base_Frequency( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT);
	  time = TPU_TIMER_Get_Value(TPU_CONFIG_IC_EPPWMT);
	  CRANK_Parameters.F.timer_value_raw = IO_PULSE_Convert_Counts_To_Time(counts_per_time, time,0,0);
      //CRANK_Parameters.F.timer_value_raw = IO_PULSE_Timer_Get_Value_Immediate( CRANK_Object->Init.Eppwmt, 0, 0 );
      break;

   case   CRANK_PARAMETER_CURRENT_TOOTH:
      {
	  	
      CRANK_Parameters.F.current_tooth = CRANK_Current_Event_Tooth;
      break;
      }
   

   case   CRANK_PARAMETER_CAM_HISTORY:
      CRANK_Parameters.F.cam_history =  MCD5408_Get_CAM_History( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT);
      break;
   
   case   CRANK_PARAMETER_CURRENT_EDGE_COUNT:
      {
     EPPwMT_Coherent_Edge_Time_And_Count_T edgeTimeAndCount;

      MCD5408_Get_Coherent_Edge_Time_And_Count( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT, &edgeTimeAndCount );

     CRANK_Parameters.F.current_edge_count = edgeTimeAndCount.Count;
      //CRANK_Parameters.F.current_edge_count = 
	  //MCD5408_Get_IRQ_Count_At_Last_Interrupt(EPPWMT_TPU_INDEX,TPU_CONFIG_IC_EPPWMT, CRANK_EPPE_IRQ_Select );
      break;
      }

   default:
      break;

   }


   parameter_value = CRANK_Parameters.U32[in_parameter];

   if ( !in_time_precision && !in_time_resolution )
   {
      value = parameter_value;
   }
   else
   {
      value = ( uint32_t )IO_Convert_Count_To_Time(
         parameter_value,
         time_base,
         in_time_precision,
         in_time_resolution );
   }

   return value;

}

//=============================================================================
// CRANK_Set_Flag
//=============================================================================
void CRANK_Set_Flag(
   Crank_Flag_T   in_flag,
   bool           in_value )
{
   CRANK_Internal_State.U32 = Insert_Bits( CRANK_Internal_State.U32, in_value, in_flag, 1 );
}

//=============================================================================
// CRANK_Get_Flag
//=============================================================================
bool CRANK_Get_Flag(
   Crank_Flag_T   in_flag )
{
  return (bool)( Extract_Bits( CRANK_Internal_State.U32, in_flag, 1 ) );
}

//=============================================================================
// CRANK_Reset_Flag
//=============================================================================
bool CRANK_Reset_Flag(
   Crank_Flag_T   in_flag )
{
   bool flag_value;

   flag_value = (bool)( Extract_Bits( CRANK_Internal_State.U32, in_flag, 1 ) );

   CRANK_Internal_State.U32 = Insert_Bits( CRANK_Internal_State.U32, false, in_flag, 1 );

   return flag_value;
}



//=============================================================================
// CRANK_Get_Edge_Time_From_Count
//=============================================================================
uint32_t CRANK_Get_Edge_Time_From_Count(
   uint16_t in_edge_count )
{
   uint32_t edge_time;

   edge_time = MCD5408_Get_Only_Edge_Time_From_Array( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT, in_edge_count );

   return edge_time;
}

//=============================================================================
// CRANK_Process_Stall_Event
//=============================================================================
void CRANK_Process_Stall_Event(void) 
{
 
   CRANK_Reset_Parameters();

   CRANK_Set_Flag( CRANK_FLAG_STALL_DETECTED, true );

   CRANK_Enable_Synchronization();
}



//=============================================================================
// CRANK_EngineStall_Check
//=============================================================================
void CRANK_EngineStall_PerioCheck(void)
{
   uint32_t edge_time;
   uint32_t stall_time_out;
   uint32_t    counts_per_time;
   uint32_t current_time;
   
   //Need to do stall check only when engine running
   if ( CRANK_Get_Flag( CRANK_FLAG_STALL_DETECTED ) != true )
   {
      stall_time_out = CRANK_Get_Parameter( CRANK_PARAMETER_LO_RES_REFERENCE_PERIOD, 0, 0 ) / 2;
      edge_time  = CRANK_Get_Parameter(CRANK_PARAMETER_CURRENT_EDGE_TIME, 0, 0 );
      counts_per_time = TPU_TIMER_Get_Base_Frequency( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT);
      current_time = TPU_TIMER_Get_Value( EPPWMT_TPU_INDEX, TPU_CONFIG_IC_EPPWMT);
       current_time = IO_PULSE_Convert_Counts_To_Time(counts_per_time, current_time,0,0);

	 if ( ( (current_time - edge_time) & UINT24_MAX ) > stall_time_out)  	
      {
         CRANK_Process_Stall_Event();
      }
     
   }
}




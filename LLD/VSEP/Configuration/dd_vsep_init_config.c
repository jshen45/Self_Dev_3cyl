//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_init.c~12:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 11:47:56 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Mon Aug 27 14:48:09 2007 %
//
// %version:         12 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================
#include "io_config_vsep.h"
#include "dd_vsep.h"
#include "dd_vsep_deps.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_est_select.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_pwm.h"
#include "dd_vsep_soh.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_init_config.h"
#include "vsepcald.h"


const VSEP_Fault_Channel_Data_T VSEP_Fault_Logging[VSEP_CHANNEL_PCH_30_FLT_LVL_7+1] =
{
    {MTSA_CONFIG_VSEP_PCH_01, MTSA_CONFIG_VSEP_PCH_01, VSEP_FAULT_IO_KIND_OUTPUT_COMPARE,         ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_01),1)))}, // PCH1
    {MTSA_CONFIG_VSEP_PCH_02, MTSA_CONFIG_VSEP_PCH_02, VSEP_FAULT_IO_KIND_OUTPUT_COMPARE,         ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_02),1)))}, // PCH2
    {MTSA_CONFIG_VSEP_PCH_03, MTSA_CONFIG_VSEP_PCH_03, VSEP_FAULT_IO_KIND_OUTPUT_COMPARE,         ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_03),1)))}, // PCH3
    {MTSA_CONFIG_VSEP_PCH_04, MTSA_CONFIG_VSEP_PCH_04, VSEP_FAULT_IO_KIND_OUTPUT_COMPARE,         ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_04),1)))}, // PCH4
    {MTSA_CONFIG_VSEP_PCH_05, MTSA_CONFIG_VSEP_PCH_05, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_05),1)))}, // PCH5
    {MTSA_CONFIG_VSEP_PCH_06, MTSA_CONFIG_VSEP_PCH_06, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_06),1)))}, // PCH6
    {MTSA_CONFIG_VSEP_PCH_07, MTSA_CONFIG_VSEP_PCH_07, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_07),1)))}, // PCH7
    {MTSA_CONFIG_VSEP_PCH_08, MTSA_CONFIG_VSEP_PCH_08, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_08),1)))}, // PCH8
    {MTSA_CONFIG_VSEP_PCH_09, MTSA_CONFIG_VSEP_PCH_09, VSEP_FAULT_IO_KIND_OUTPUT_COMPARE,         ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_09),1)))}, // PCH9
    {MTSA_CONFIG_VSEP_PCH_10, MTSA_CONFIG_VSEP_PCH_10, VSEP_FAULT_IO_KIND_OUTPUT_COMPARE,         ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_10),1)))}, // PCH10
    {MTSA_CONFIG_VSEP_PCH_11, MTSA_CONFIG_VSEP_PCH_11, VSEP_FAULT_IO_KIND_OUTPUT_COMPARE,         ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_11),1)))}, // PCH11
    {MTSA_CONFIG_VSEP_PCH_12, MTSA_CONFIG_VSEP_PCH_12, VSEP_FAULT_IO_KIND_OUTPUT_COMPARE,         ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_12),1)))}, // PCH12
    {MTSA_CONFIG_VSEP_PCH_13, MTSA_CONFIG_VSEP_PCH_13, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_13),1)))}, // PCH13
    {MTSA_CONFIG_VSEP_PCH_14, MTSA_CONFIG_VSEP_PCH_14, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_14),1)))}, // PCH14
    {MTSA_CONFIG_VSEP_PCH_15, MTSA_CONFIG_VSEP_PCH_15, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_15),1)))}, // PCH15
    {MTSA_CONFIG_VSEP_PCH_16, MTSA_CONFIG_VSEP_PCH_16, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_16),1)))}, // PCH16
    {MTSA_CONFIG_VSEP_PCH_17, MTSA_CONFIG_VSEP_PCH_17, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_17),1)))}, // PCH17
    {MTSA_CONFIG_VSEP_PCH_18, MTSA_CONFIG_VSEP_PCH_18, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_18),1)))}, // PCH18
    {MTSA_CONFIG_VSEP_PCH_19, MTSA_CONFIG_VSEP_PCH_19, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_19),1)))}, // PCH19
    {MTSA_CONFIG_VSEP_PCH_20, MTSA_CONFIG_VSEP_PCH_20, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_20),1)))}, // PCH20
    {MTSA_CONFIG_VSEP_PCH_21, MTSA_CONFIG_VSEP_PCH_21, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_21),1)))}, // PCH21  
    {MTSA_CONFIG_VSEP_PCH_22, MTSA_CONFIG_VSEP_PCH_22, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_22),1)))}, // PCH22
    {MTSA_CONFIG_VSEP_PCH_23, MTSA_CONFIG_VSEP_PCH_23, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_23),1)))}, // PCH23
    {MTSA_CONFIG_VSEP_PCH_24, MTSA_CONFIG_VSEP_PCH_24, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_24),1)))}, // PCH24
    {MTSA_CONFIG_VSEP_PCH_25, MTSA_CONFIG_VSEP_PCH_25, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_25),1)))}, // PCH25
    {MTSA_CONFIG_VSEP_PCH_26, MTSA_CONFIG_VSEP_PCH_26, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_26),1)))}, // PCH26
    {MTSA_CONFIG_VSEP_PCH_27, MTSA_CONFIG_VSEP_PCH_27, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_27),1)))}, // PCH27
    {MTSA_CONFIG_VSEP_PCH_28, MTSA_CONFIG_VSEP_PCH_28, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_28),1)))}, // PCH28
    {MTSA_CONFIG_VSEP_PCH_29, MTSA_CONFIG_VSEP_PCH_29, VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION, ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_29),1)))}, // PCH29
    {MTSA_CONFIG_VSEP_PCH_30, MTSA_CONFIG_VSEP_PCH_30, VSEP_FAULT_IO_KIND_DISCRETE,               ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_30),1)))}  // PCH30
};

#ifdef  VSEP_CALIBRATION_ENABLE
uint16_t VSEP_INIT_TXD_INITIAL[VSEP_INIT_TXD_MESSAGE_MAX];
#else
const uint16_t VSEP_INIT_TXD_INITIAL[VSEP_INIT_TXD_MESSAGE_MAX] =
{
      {
          VSEP_Msg_Set_FLTCLR( 0, true                   ) |
         VSEP_Msg_Set_CRTOCLR( 0, true                   ) |
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED ) | 
            ( 0, VSEP_TXD_SDIA_VR1_CTRL )   
      },
      { 
          VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_0_VR_1_INIT )      ) |        
             VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_1_INIT ) ) |
             VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Min_Threshold( VSEP_0_VR_1_INIT ) ) 
      },
      { 
          VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_0_VR_2_INIT )      ) |        
             VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_2_INIT ) ) |
             VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Min_Threshold( VSEP_0_VR_2_INIT ) ) 
      },
      {     
          VSEP_Msg_DEPS_Set_Delay( 0, VSEP_DEPS_Get_Initial_Delay( VSEP_0_DEPS_INIT ) ) 
      },
      { 
          VSEP_Msg_SLEW_Set_Group_1( 0, VSEP_Get_Slew_Group_1( VSEP_0_SLEW_INIT )     ) |
          VSEP_Msg_SLEW_Set_Group_2( 0, VSEP_Get_Slew_Group_2( VSEP_0_SLEW_INIT )     ) |
          VSEP_Msg_SLEW_Set_Group_3( 0, VSEP_Get_Slew_Group_3( VSEP_0_SLEW_INIT )     ) |
          VSEP_Msg_SLEW_Set_Group_4( 0, VSEP_Get_Slew_Group_4( VSEP_0_SLEW_INIT )     ) |
          VSEP_Msg_SLEW_Set_Group_5( 0, VSEP_Get_Slew_Group_5( VSEP_0_SLEW_INIT )     ) |
        VSEP_Msg_SLEW_Set_Group_CAN( 0, VSEP_Get_Slew_Group_CAN( VSEP_0_SLEW_INIT )   )
      },
      {
         VSEP_Msg_FAULT_Set_Level_1( 0, VSEP_Get_Fault_Level_1( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_2( 0, VSEP_Get_Fault_Level_2( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_3( 0, VSEP_Get_Fault_Level_3( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_4( 0, VSEP_Get_Fault_Level_4( VSEP_0_FAULT_INIT ) ) 
        
      },
      {
         VSEP_Msg_FAULT_Set_Level_5( 0, VSEP_Get_Fault_Level_5( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_6( 0, VSEP_Get_Fault_Level_6( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_7( 0, VSEP_Get_Fault_Level_7( VSEP_0_FAULT_INIT ) ) 
      },
      {
          ( VSEP_Msg_FAULT_Filter_Set_Non_Spark_Channels_1_To_8( 0, VSEP_FAULT_FILTER_Get_1TO8NSP_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                VSEP_Msg_FAULT_Filter_Set_Spark_Channels_1_To_8( 0,  VSEP_FAULT_FILTER_Get_1TO8SP_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                     VSEP_Msg_FAULT_Filter_Set_Channels_9_To_12( 0,   VSEP_FAULT_FILTER_Get_9TO12_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_13_To_16( 0,  VSEP_FAULT_FILTER_Get_13TO16_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_17_To_18( 0,  VSEP_FAULT_FILTER_Get_17TO18_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_19_To_20( 0,  VSEP_FAULT_FILTER_Get_19TO20_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_21_To_24( 0,  VSEP_FAULT_FILTER_Get_21TO24_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_25_To_30( 0,  VSEP_FAULT_FILTER_Get_25TO30_Time( VSEP_0_FAULT_FILTER_INIT ) ) )
      },
      {
          ( VSEP_Msg_LEDMODE_Set_Channel_25( 0, VSEP_LEDMODE_Get_Enable( VSEP_0_LEDMODE_25_INIT ) ) |
            VSEP_Msg_LEDMODE_Set_Channel_26( 0, VSEP_LEDMODE_Get_Enable( VSEP_0_LEDMODE_26_INIT ) ) |
            VSEP_Msg_LEDMODE_Set_Channel_30( 0, VSEP_LEDMODE_Get_Enable( VSEP_0_LEDMODE_30_INIT ) ) )
      },
      { 
          VSEP_Msg_IGBT_Set_GRADFILT( 0,  VSEP_Gradient_Check_Get_Filter_Time(VSEP_0_GRADIENT_CHECK_INIT ) ) |
         VSEP_Msg_IGBT_Set_GRADTHR( 0, VSEP_Gradient_Check_Get_Threshold(VSEP_0_GRADIENT_CHECK_INIT ) ) 
      },
      { 
            VSEP_Msg_EST_Set_EDGE( 0,     VSEP_EST_Select_Get_Index_Pin_Select( VSEP_0_EST_SELECT_SETUP_INIT ) ) |
           VSEP_Msg_EST_Set_INDEX( 0, VSEP_EST_Select_Get_Increment_Index_Mode( VSEP_0_EST_SELECT_SETUP_INIT ) ) |
          VSEP_Msg_EST_Set_PFMODE( 0,     VSEP_EST_Select_Get_Paired_Fire_Mode( VSEP_0_EST_SELECT_SETUP_INIT ) ) 
      },
      {
                   VSEP_Msg_Set_SOHRSTEN( 0, VSEP_SOH_Get_SOHRSTEN( VSEP_0_SOHRSTEN_INIT )                                              ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_1-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M1_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_2-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M2_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_3-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M3_INIT ) ) |
                 VSEP_Msg_EST_Set_CYLCNT( 0, VSEP_EST_Select_Get_Cylinder_Count( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
              VSEP_Msg_EST_Set_DEC_DISCB( 0,    VSEP_EST_Select_Get_Select_Mode( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
                VSEP_Msg_EST_Set_IGBTCFG( 0,     VSEP_EST_Select_Get_Drive_Mode( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
		VSEP_Msg_SOH_Set_CRDISARM( 0,     VSEP_SOH_Get_ENABLE_STATE( VSEP_0_SOH_ENABLE_INIT )        )
	}
};
#endif


#ifdef VSEP_EST_DIAGNOSTIC_DEBUG
uint8_t VSEP_EST_Select_Dwell_Current_Time[8];
#endif

#ifdef  VSEP_CALIBRATION_ENABLE
 uint16_t VSEP_EST_SELECT_INITIAL[VSEP_EST_SELECT_TXD_MESSAGE_MAX];
#else
const uint16_t VSEP_EST_SELECT_INITIAL[VSEP_EST_SELECT_TXD_MESSAGE_MAX] =
{
      {
         VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_EST_STAT  ) |
         VSEP_Msg_Set_SDIA(0,VSEP_TXD_SDIA_EST_CTRL)  
      } ,
      { // Do not set the count for the initial structure.
            VSEP_Msg_EST_Set_EDGE( 0,     VSEP_EST_Select_Get_Index_Pin_Select( VSEP_0_EST_SELECT_SETUP_INIT ) ) |
           VSEP_Msg_EST_Set_INDEX( 0, VSEP_EST_Select_Get_Increment_Index_Mode( VSEP_0_EST_SELECT_SETUP_INIT ) ) |
          VSEP_Msg_EST_Set_PFMODE( 0,     VSEP_EST_Select_Get_Paired_Fire_Mode( VSEP_0_EST_SELECT_SETUP_INIT ) ) 
      }
};
#endif


const uint32_t VSEP_TIMER_DEPS_Base_Frequency = 0;
const uint16_t VSEP_DEPS_TXD_INITIAL[VSEP_DEPS_TXD_MESSAGE_MAX] =
{
      {     VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED  ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_DEPS_CTRL )   
      },
      {     
            VSEP_Msg_DEPS_Set_Delay( 0, VSEP_DEPS_Get_Initial_Delay( VSEP_0_DEPS_INIT ) ) 
      }
};


const uint32_t VSEP_TIMER_VR_Base_Frequency = 0;
const uint16_t VSEP_VR_TXD_INITIAL[VSEP_VR_TXD_MESSAGE_MAX] = 
{
    {
        VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED  ) |
        VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_VR1_CTRL  )
    },
    { 
        VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_0_VR_1_INIT )      ) |
        VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_1_INIT ) ) |
        VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_1_INIT ) )
    },
    { 
        VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_0_VR_2_INIT )      ) |
        VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_2_INIT ) ) |
        VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_2_INIT ) ) 
    }
};

const uint32_t VSEP_BASE_FREQUENCY = VSEP_EXTERNAL_CLOCK_BASE_FREQUENCY;

#define VSEP_GRADCOUNT_BASE_FREQUENCY_DEFINE ((VSEP_EXTERNAL_CLOCK_BASE_FREQUENCY + (VSEP_GRADCOUNT_DIVIDER/2)) / VSEP_GRADCOUNT_DIVIDER)

const uint32_t VSEP_GRADCOUNT_BASE_FREQUENCY = VSEP_GRADCOUNT_BASE_FREQUENCY_DEFINE;

#define VSEP_128_US_BASE_FREQUENCY ( 1.0 / 0.000128 )

const uint8_t VSEP_GRADCOUNT_FAULT_WINDOW = (uint8_t)((VSEP_GRADCOUNT_BASE_FREQUENCY_DEFINE + (VSEP_128_US_BASE_FREQUENCY/2))/ VSEP_128_US_BASE_FREQUENCY); //128us in terms of GRADCOUNT ticks

const uint16_t VSEP_PWM_TXD_INITIAL[VSEP_PWM_CHANNEL_MAX][VSEP_PWM_TXD_MESSAGE_MAX]=
{
    { //PWM Channel 1
        {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_1   )   
        },
        {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_1_PWM_INIT ) )   
        },
        {
            VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_1_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_1_PWM_INIT ) )
        }
    },
    { //PWM Channel 2
        {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_2   )
        },
        {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_2_PWM_INIT ) )   
        },
        {
            VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_2_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_2_PWM_INIT ) )
        }
    },
    { //PWM Channel 3
        {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_3   )   
        },
        {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_3_PWM_INIT ) )   
        },
        {
            VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_3_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_3_PWM_INIT ) )
        }
    },
    { //PWM Channel 4
        {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_4   )   
        },
        {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_4_PWM_INIT ) )   
        },
        {
            VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_4_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_4_PWM_INIT ) )
        }
    },
    { //PWM Channel 5
        {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_5   )   
        },
        {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_5_PWM_INIT ) )   
        },
        {
            VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_5_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_5_PWM_INIT ) )
        }
    },
    { //PWM Channel 6
        {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_6   )   
        },
        {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_6_PWM_INIT ) )   
        },
        {
            VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_6_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_6_PWM_INIT ) )
        }
    },
    { //PWM Channel 7
        {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_7   )   
        },
        {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_7_PWM_INIT ) )   
        },
        {
            VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_7_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_7_PWM_INIT ) )
        }
    },
    { //PWM Channel 8
        {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_8   )   
        },
        {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_8_PWM_INIT ) )   
        },
        {
            VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_8_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_8_PWM_INIT ) )
        }
    }
};

/* VSEP PCH Init Value */
const uint16_t VSEP_PCH_TXD_INITIAL[VSEP_PCH_TXD_MESSAGE_MAX] = 
{
      {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_EST_STAT ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PCH      )   
            
      },
      {
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_4,  VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH4_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_5 , VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH5_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_6 , VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH6_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_7 , VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH7_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_8 , VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH8_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_13, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH13_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_14, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH14_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_17, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH17_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_18, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH18_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_19, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH19_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_20, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH20_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_23, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH23_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_25, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH25_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_26, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH26_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_30, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH30_INIT ) ) ) 
      }
};

/* vsep soh module init value */
const uint16_t VSEP_SOH_STATUS_TXD[VSEP_SOH_STATUS_TXD_MESSAGE_MAX] =
{
     {  
         VSEP_Msg_Set_FLTCLR( 0, 0 ) |
        VSEP_Msg_Set_CRTOCLR( 0, 0 ) |
           VSEP_Msg_Set_SDOA(0, VSEP_RXD_SDOA_EST_STAT ) |
           VSEP_Msg_Set_SDIA(0, VSEP_TXD_SDIA_NOT_USED )     
     },
     { 0                                                 }
};

// IGBT GRAD Fault data
const uint16_t VSEP_EST_FAULT_GRAD_INITIAL[VSEP_EST_FAULT_TXD_MESSAGE_MAX]=
{
    {  
        VSEP_Msg_Set_FLTCLR( 0, false ) |
        VSEP_Msg_Set_CRTOCLR( 0, false ) |
        VSEP_Msg_Set_SDOA(0, VSEP_RXD_SDOA_GRADCOUNT ) |
        VSEP_Msg_Set_SDIA(0, VSEP_TXD_SDIA_GRAD_CTRL )
    },
    {
        VSEP_Msg_IGBT_Set_GRADTHR( 0,   VSEP_Gradient_Check_Get_Threshold(VSEP_0_GRADIENT_CHECK_INIT ) ) |
        VSEP_Msg_IGBT_Set_GRADFILT( 0, VSEP_Gradient_Check_Get_Filter_Time(VSEP_0_GRADIENT_CHECK_INIT ) )
    }  // GRADIENT Threshold and Time
};

//for MT22.1 special spark and fault diagnostic logic.
const uint8_t VSEP_EST_FAULT_SYNC_MESSAGE_BYTE_INITIAL[VSEP_EST_FAULT_SYNC_TXD_MESSAGE_MAX_BYTE]=
{
    {  
        VSEP_Msg_Set_FLTCLR_BYTE_FORMAT( 0, true )  |
        VSEP_Msg_Set_CRTOCLR_BYTE_FORMAT( 0, false ) |
        VSEP_Msg_Set_SDOA_BYTE_FORMAT(0, VSEP_RXD_SDOA_FAULT_GRP_5 )
    },
    {  VSEP_Msg_Set_SDIA_BYTE_FORMAT(0, VSEP_TXD_SDIA_EST_CTRL )},
    { 0                                                 } // SDOA 5 byte 1
};

//Fault data	for MT22.1, start at VSEP_RXD_SDOA_FAULT_GRP_6 
const uint16_t VSEP_FAULT_TXD[VSEP_FAULT_TXD_MESSAGE_MAX]=
{
    {  
        VSEP_Msg_Set_FLTCLR( 0, true )  |
        VSEP_Msg_Set_CRTOCLR( 0, false ) |
        VSEP_Msg_Set_SDOA(0, VSEP_RXD_SDOA_FAULT_GRP_6 ) |
        VSEP_Msg_Set_SDIA(0, VSEP_TXD_SDIA_NOT_USED )
    },
    { 0                                                 }, // SDOA 6 word 1
    { 0                                                 }, // SDOA 8 word 2
    { 0                                                 }, // SDOA A word 3
    { 0                                                 }  // SDOA C word 4
};

const uint16_t VSEP_MPIO_MODE_TXD_INITIAL[VSEP_MPIO_MODE_TXD_MESSAGE_MAX] =
{

      {     VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED  ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_SETUP )   
      },
      {     
                   VSEP_Msg_Set_SOHRSTEN( 0, VSEP_SOH_Get_SOHRSTEN( VSEP_0_SOHRSTEN_INIT )                                              ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_1-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M1_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_2-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M2_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_3-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M3_INIT ) ) |
                 VSEP_Msg_EST_Set_CYLCNT( 0, VSEP_EST_Select_Get_Cylinder_Count( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
              VSEP_Msg_EST_Set_DEC_DISCB( 0,    VSEP_EST_Select_Get_Select_Mode( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
                VSEP_Msg_EST_Set_IGBTCFG( 0,     VSEP_EST_Select_Get_Drive_Mode( VSEP_0_EST_SELECT_SETUP_INIT )                         ) 
      }
};

/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 * 9.0  272        08/11/24 sjl Add configurable calibrations for discrete inputs 
\*===========================================================================*/

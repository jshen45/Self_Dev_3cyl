
#include "dd_intc.h"

//=============================================================================
// INTC
//=============================================================================
INTC_T INTC;

//=============================================================================
// INTC & exception address define in dld file
//=============================================================================
extern uint32_t EXCEPTION_TABLE_ADDRESS[];
//=============================================================================
// INTC vector
//=============================================================================
//const INTC_Vector_Table_T INTC_Vector_Table [ NO_OF_INTC_CHANNEL ];


//=============================================================================
// INTC_Initialize_Device
//=============================================================================
void INTC_Initialize_Device(void)
{
   uint16_t i;

   
   INTC_Exception_Initialize(EXCEPTION_TABLE_ADDRESS);

   INTC.MCR.F.VTES_PRC0= INTC_Vector_Table_Entry_Size_4;

   INTC.MCR.F.HVEN_PRC0 = INTC_INTERRUPT_METHOD_SOFTWARE;

   INTC.IACKR_PRC0.F.VTBA = ( ( uint32_t )( &INTC_Vector_Table ));

   // Vector table base address is set in IVPR register - same base
   // address as exception table.

    /* Set the PSR Priority */
   INTC.PSR[INTC_CHANNEL_RTI_CH].F.PRI = INTC_CHANNEL_RTI_PRIORITY; 
   INTC.PSR[INTC_CHANNEL_FLEXCAN_A_BUFFER_15_CH].F.PRI = INTC_CHANNEL_FLEXCAN_A_BUFFER_15_PRIORITY; 
   INTC.PSR[INTC_CHANNEL_TPU_1_CH0_CH].F.PRI = INTC_CHANNEL_TPU_A_CH0_PRIORITY;
   INTC.PSR[INTC_CHANNEL_SOFTWARE_CH0_CH].F.PRI = INTC_CHANNEL_SOFTWARE_CH0_PRIORITY;
   INTC.PSR[INTC_CHANNEL_TPU_1_CH17_CH].F.PRI = INTC_CHANNEL_TPU_A_CH17_PRIORITY;
   INTC.PSR[INTC_CHANNEL_DMA_CH13_DSPI_B_RX_FIFO_DRAIN].F.PRI = INTC_CHANNEL_DMA_CH13_DSPI_B_RX_FIFO_DRAIN_PRIORITY;
   INTC.PSR[INTC_CHANNEL_TPU_1_CH1_CH].F.PRI = INTC_CHANNEL_TPU_A_CH1_PRIORITY;
   INTC.PSR[INTC_CHANNEL_TPU_1_CH16_CH].F.PRI = INTC_CHANNEL_TPU_A_CH16_PRIORITY;
   // Clear all software settable interrupt requests.
   for( i = 0; i < INTC_SSCIR_QUANTITY; i++ )
   {
      INTC.SSCIR[i].U8 = 0;
   }


   INTC.CPR_PRC0.U32 = 0;

}

//=============================================================================
//need to update prolo and eplio if nested interrupt enable
//=============================================================================
void INTC_External_Interrupt_Prologue( void )
{
}

//=============================================================================
//need to update prolo and eplio if nested interrupt enable
//=============================================================================
void INTC_External_Interrupt_Epilogue(void )
{
   
      asm(" msync ");

      Disable_Interrupts();

      asm(" oris 0,0,0 ");

  
      INTC.EOIR_PRC0 = 0;

}


#ifndef DD_INTC_H
#define DD_INTC_H

#include "hw_intc.h"
#include "io_vector.h"

#define SECTION_INTC_REGISTER
#include "section.h"
extern INTC_T INTC;
#define SECTION_END
#include "section.h"


#define UNUSED_IRQ 0
#define USED_IRQ   1

#define INTC_PRIORITY_0 (0)
#define INTC_PRIORITY_1 (1)
#define INTC_PRIORITY_2 (2)
#define INTC_PRIORITY_3 (3)
#define INTC_PRIORITY_4 (4)
#define INTC_PRIORITY_5 (5)
#define INTC_PRIORITY_6 (6)
#define INTC_PRIORITY_7 (7)
#define INTC_PRIORITY_8 (8)
#define INTC_PRIORITY_9 (9)
#define INTC_PRIORITY_10 (10)
#define INTC_PRIORITY_11 (11)
#define INTC_PRIORITY_12 (12)
#define INTC_PRIORITY_13 (13)
#define INTC_PRIORITY_14 (14)
#define INTC_PRIORITY_15 (15)

typedef enum INTC_Channel_Tag
{
   INTC_CHANNEL_SOFTWARE_CH0_CH,
   INTC_CHANNEL_SOFTWARE_CH1_CH,
   INTC_CHANNEL_SOFTWARE_CH2_CH,
   INTC_CHANNEL_SOFTWARE_CH3_CH,
   INTC_CHANNEL_SOFTWARE_CH4_CH,
   INTC_CHANNEL_SOFTWARE_CH5_CH,
   INTC_CHANNEL_SOFTWARE_CH6_CH,
   INTC_CHANNEL_SOFTWARE_CH7_CH,
   INTC_CHANNEL_SW_WATCHDOG_IR_CH,
   INTC_CHANNEL_ECSM_RAM_FLASH_ERROR_CH,
   INTC_CHANNEL_DMA_ERROR_CH31_0_CH,
   INTC_CHANNEL_DMA_CH0_QADC_CFIFO_0_FILL_CH,
   INTC_CHANNEL_DMA_CH1_QADC_RFIFO_0_DRAIN_CH,
   INTC_CHANNEL_DMA_CH2_QADC_CFIFO_1_FILL_CH,
   INTC_CHANNEL_DMA_CH3_QADC_RFIFO_1_DRAIN_CH,
   INTC_CHANNEL_DMA_CH4_QADC_CFIFO_2_FILL_CH,
   INTC_CHANNEL_DMA_CH5_QADC_RFIFO_2_DRAIN_CH,
   INTC_CHANNEL_DMA_CH6_QADC_CFIFO_3_FILL_CH,
   INTC_CHANNEL_DMA_CH7_QADC_RFIFO_3_DRAIN_CH,
   INTC_CHANNEL_DMA_CH8_QADC_CFIFO_4_FILL_CH,
   INTC_CHANNEL_DMA_CH9_QADC_RFIFO_4_DRAIN_CH,
   INTC_CHANNEL_DMA_CH10_QADC_CFIFO_5_FILL_CH,
   INTC_CHANNEL_DMA_CH11_QADC_RFIFO_5_DRAIN_CH,
   INTC_CHANNEL_DMA_CH12_DSPI_B_TX_FIFO_FILL_CH,
   INTC_CHANNEL_DMA_CH13_DSPI_B_RX_FIFO_DRAIN_CH,
   INTC_CHANNEL_DMA_CH14_DSPI_C_TX_FIFO_FILL_CH,
   INTC_CHANNEL_DMA_CH15_DSPI_C_RX_FIFO_DRAIN_CH,
   INTC_CHANNEL_DMA_CH16_DEC_FILTER_FILL_CH,
   INTC_CHANNEL_DMA_CH17_DEC_FILTER_DRAIN_CH,
   INTC_CHANNEL_DMA_CH18_SCI_A_TX_CH,
   INTC_CHANNEL_DMA_CH19_SCI_A_RX_CH,
   INTC_CHANNEL_DMA_CH20_MIOS_CH0_CH,
   INTC_CHANNEL_DMA_CH21_MIOS_CH1_CH,
   INTC_CHANNEL_DMA_CH22_MIOS_CH2_CH,
   INTC_CHANNEL_DMA_CH23_MIOS_CH3_CH,
   INTC_CHANNEL_DMA_CH24_MIOS_CH4_CH,
   INTC_CHANNEL_DMA_CH25_MIOS_CH8_CH,
   INTC_CHANNEL_DMA_CH26_MIOS_CH9_CH,
   INTC_CHANNEL_DMA_CH27_TPU_1_CH0_CH,
   INTC_CHANNEL_DMA_CH28_TPU_1_CH1_CH,
   INTC_CHANNEL_DMA_CH29_TPU_1_CH2_CH,
   INTC_CHANNEL_DMA_CH30_TPU_1_CH14_CH,
   INTC_CHANNEL_DMA_CH31_TPU_1_CH15_CH,
   INTC_CHANNEL_FMPLL_LOSS_CLOCK_CH,
   INTC_CHANNEL_FMPLL_LOSS_LOCK_CH,
   INTC_CHANNEL_SIU_OVERRUN_CH,
   INTC_CHANNEL_SIU_EXTERNAL_CH0_CH,
   INTC_CHANNEL_SIU_EXTERNAL_CH1_CH,
   INTC_CHANNEL_SIU_EXTERNAL_CH2_CH,
   INTC_CHANNEL_SIU_EXTERNAL_CH3_CH,
   INTC_CHANNEL_SIU_EXTERNAL_CH15_4_CH,
   INTC_CHANNEL_MIOS_CH0_CH,
   INTC_CHANNEL_MIOS_CH1_CH,
   INTC_CHANNEL_MIOS_CH2_CH,
   INTC_CHANNEL_MIOS_CH3_CH,
   INTC_CHANNEL_MIOS_CH4_CH,
   INTC_CHANNEL_MIOS_CH5_CH,
   INTC_CHANNEL_MIOS_CH6_CH,
   INTC_CHANNEL_MIOS_CH7_CH,
   INTC_CHANNEL_MIOS_CH8_CH,
   INTC_CHANNEL_MIOS_CH9_CH,
   INTC_CHANNEL_MIOS_CH10_CH,
   INTC_CHANNEL_MIOS_CH11_CH,
   INTC_CHANNEL_MIOS_CH12_CH,
   INTC_CHANNEL_MIOS_CH13_CH,
   INTC_CHANNEL_MIOS_CH14_CH,
   INTC_CHANNEL_MIOS_CH15_CH,
   INTC_CHANNEL_TPU_GLOBAL_EXCEPTION_CH,
   INTC_CHANNEL_TPU_1_CH0_CH,
   INTC_CHANNEL_TPU_1_CH1_CH,
   INTC_CHANNEL_TPU_1_CH2_CH,
   INTC_CHANNEL_TPU_1_CH3_CH,
   INTC_CHANNEL_TPU_1_CH4_CH,
   INTC_CHANNEL_TPU_1_CH5_CH,
   INTC_CHANNEL_TPU_1_CH6_CH,
   INTC_CHANNEL_TPU_1_CH7_CH,
   INTC_CHANNEL_TPU_1_CH8_CH,
   INTC_CHANNEL_TPU_1_CH9_CH,
   INTC_CHANNEL_TPU_1_CH10_CH,
   INTC_CHANNEL_TPU_1_CH11_CH,
   INTC_CHANNEL_TPU_1_CH12_CH,
   INTC_CHANNEL_TPU_1_CH13_CH,
   INTC_CHANNEL_TPU_1_CH14_CH,
   INTC_CHANNEL_TPU_1_CH15_CH,
   INTC_CHANNEL_TPU_1_CH16_CH,
   INTC_CHANNEL_TPU_1_CH17_CH,
   INTC_CHANNEL_TPU_1_CH18_CH,
   INTC_CHANNEL_TPU_1_CH19_CH,
   INTC_CHANNEL_TPU_1_CH20_CH,
   INTC_CHANNEL_TPU_1_CH21_CH,
   INTC_CHANNEL_TPU_1_CH22_CH,
   INTC_CHANNEL_TPU_1_CH23_CH,
   INTC_CHANNEL_TPU_1_CH24_CH,
   INTC_CHANNEL_TPU_1_CH25_CH,
   INTC_CHANNEL_TPU_1_CH26_CH,
   INTC_CHANNEL_TPU_1_CH27_CH,
   INTC_CHANNEL_TPU_1_CH28_CH,
   INTC_CHANNEL_TPU_1_CH29_CH,
   INTC_CHANNEL_TPU_1_CH30_CH,
   INTC_CHANNEL_TPU_1_CH31_CH,
   INTC_CHANNEL_QADC_OVERFLOW_CH,
   INTC_CHANNEL_QADC_CFIFO_CH0_INCOHERENT_CH,
   INTC_CHANNEL_QADC_CFIFO_CH0_PAUSE_CH,
   INTC_CHANNEL_QADC_CFIFO_CH0_EOQ_CH,
   INTC_CHANNEL_QADC_CFIFO_CH0_FILL_CH,
   INTC_CHANNEL_QADC_RFIFO_CH0_DRAIN_CH,
   INTC_CHANNEL_QADC_CFIFO_CH1_INCOHERENT_CH,
   INTC_CHANNEL_QADC_CFIFO_CH1_PAUSE_CH,
   INTC_CHANNEL_QADC_CFIFO_CH1_EOQ_CH,
   INTC_CHANNEL_QADC_CFIFO_CH1_FILL_CH,
   INTC_CHANNEL_QADC_RFIFO_CH1_DRAIN_CH,
   INTC_CHANNEL_QADC_CFIFO_CH2_INCOHERENT_CH,
   INTC_CHANNEL_QADC_CFIFO_CH2_PAUSE_CH,
   INTC_CHANNEL_QADC_CFIFO_CH2_EOQ_CH,
   INTC_CHANNEL_QADC_CFIFO_CH2_FILL_CH,
   INTC_CHANNEL_QADC_RFIFO_CH2_DRAIN_CH,
   INTC_CHANNEL_QADC_CFIFO_CH3_INCOHERENT_CH,
   INTC_CHANNEL_QADC_CFIFO_CH3_PAUSE_CH,
   INTC_CHANNEL_QADC_CFIFO_CH3_EOQ_CH,
   INTC_CHANNEL_QADC_CFIFO_CH3_FIL_CHL,
   INTC_CHANNEL_QADC_RFIFO_CH3_DRAIN_CH,
   INTC_CHANNEL_QADC_CFIFO_CH4_INCOHERENT_CH,
   INTC_CHANNEL_QADC_CFIFO_CH4_PAUSE_CH,
   INTC_CHANNEL_QADC_CFIFO_CH4_EOQ_CH,
   INTC_CHANNEL_QADC_CFIFO_CH4_FILL_CH,
   INTC_CHANNEL_QADC_RFIFO_CH4_DRAIN_CH,
   INTC_CHANNEL_QADC_CFIFO_CH5_INCOHERENT_CH,
   INTC_CHANNEL_QADC_CFIFO_CH5_PAUSE_CH,
   INTC_CHANNEL_QADC_CFIFO_CH5_EOQ_CH,
   INTC_CHANNEL_QADC_CFIFO_CH5_FILL_CH,
   INTC_CHANNEL_QADC_RFIFO_CH5_DRAIN_CH,
   INTC_CHANNEL_DSPI_B_OVERFLOW_CH,
   INTC_CHANNEL_DSPI_B_TFIFO_EOQ_CH,
   INTC_CHANNEL_DSPI_B_TFIFO_FILL_CH,
   INTC_CHANNEL_DSPI_B_TX_COMPLETE_CH,
   INTC_CHANNEL_DSPI_B_RFIFO_DRAIN_CH,
   INTC_CHANNEL_DSPI_C_OVERFLOW_CH,
   INTC_CHANNEL_DSPI_C_TFIFO_EOQ_CH,
   INTC_CHANNEL_DSPI_C_TFIFO_FILL_CH,
   INTC_CHANNEL_DSPI_C_TX_COMPLETE_CH,
   INTC_CHANNEL_DSPI_C_RFIFO_DRAIN_CH,
   INTC_CHANNEL_RESERVED_141_CH,
   INTC_CHANNEL_RESERVED_142_CH,
   INTC_CHANNEL_RESERVED_143_CH,
   INTC_CHANNEL_RESERVED_144_CH,
   INTC_CHANNEL_RESERVED_145_CH,
   INTC_CHANNEL_SCI_A_CH,
   INTC_CHANNEL_RESERVED_147_CH,
   INTC_CHANNEL_RESERVED_148_CH,
   INTC_CHANNEL_SCI_B_CH,
   INTC_CHANNEL_RESERVED_150_CH,
   INTC_CHANNEL_RESERVED_151_CH,
   INTC_CHANNEL_FLEXCAN_A_BUS_OFF_CH,
   INTC_CHANNEL_FLEXCAN_A_ERROR_CH,
   INTC_CHANNEL_FLEXCAN_A_WAKEUP_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_0_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_1_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_2_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_3_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_4_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_5_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_6_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_7_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_8_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_9_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_10_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_11_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_12_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_13_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_14_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_15_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_31_16_CH,
   INTC_CHANNEL_FLEXCAN_A_BUFFER_63_32_CH,
   INTC_CHANNEL_FLEXCAN_C_BUS_OFF_CH,
   INTC_CHANNEL_FLEXCAN_C_ERROR_CH,
   INTC_CHANNEL_FLEXCAN_C_WAKEUP_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_0_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_1_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_2_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_3_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_4_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_5_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_6_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_7_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_8_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_9_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_10_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_11_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_12_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_13_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_14_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_15_CH,
   INTC_CHANNEL_FLEXCAN_C_BUFFER_31_16_CH,
   INTC_CHANNEL_RESERVED_193_CH,
   INTC_CHANNEL_RESERVED_194_CH,
   INTC_CHANNEL_RESERVED_195_CH,
   INTC_CHANNEL_RESERVED_196_CH,
   INTC_CHANNEL_DEC_FILTER_A_INPUT_FILL_CH,
   INTC_CHANNEL_DEC_FILTER_A_OUTPUT_DRAIN_CH,
   INTC_CHANNEL_DEC_FILTER_A_ERROR_CH,
   INTC_CHANNEL_SYSTEM_TIMER_MODULE_0_CH,
   INTC_CHANNEL_SYSTEM_TIMER_MODULE_1_3_CH,
   INTC_CHANNEL_RESERVED_202_CH,
   INTC_CHANNEL_RESERVED_203_CH,
   INTC_CHANNEL_RESERVED_204_CH,
   INTC_CHANNEL_RESERVED_205_CH,
   INTC_CHANNEL_RESERVED_206_CH,
   INTC_CHANNEL_RESERVED_207_CH,
   INTC_CHANNEL_RESERVED_208_CH,
   INTC_CHANNEL_MIOS_CH23_CH,
   INTC_CHANNEL_RESERVED_210_CH,
   INTC_CHANNEL_RESERVED_211_CH,
   INTC_CHANNEL_RESERVED_212_CH,
   INTC_CHANNEL_RESERVED_213_CH,
   INTC_CHANNEL_RESERVED_214_CH,
   INTC_CHANNEL_RESERVED_215_CH,
   INTC_CHANNEL_RESERVED_216_CH,
   INTC_CHANNEL_RESERVED_217_CH,
   INTC_CHANNEL_RESERVED_218_CH,
   INTC_CHANNEL_RESERVED_219_CH,
   INTC_CHANNEL_RESERVED_220_CH,
   INTC_CHANNEL_RESERVED_221_CH,
   INTC_CHANNEL_RESERVED_222_CH,
   INTC_CHANNEL_RESERVED_223_CH,
   INTC_CHANNEL_RESERVED_224_CH,
   INTC_CHANNEL_RESERVED_225_CH,
   INTC_CHANNEL_RESERVED_226_CH,
   INTC_CHANNEL_RESERVED_227_CH,
   INTC_CHANNEL_RESERVED_228_CH,
   INTC_CHANNEL_RESERVED_229_CH,
   INTC_CHANNEL_RESERVED_230_CH,
   INTC_CHANNEL_RESERVED_231_CH,
   INTC_CHANNEL_RESERVED_232_CH,
   INTC_CHANNEL_RESERVED_233_CH,
   INTC_CHANNEL_RESERVED_234_CH,
   INTC_CHANNEL_RESERVED_235_CH,
   INTC_CHANNEL_RESERVED_236_CH,
   INTC_CHANNEL_RESERVED_237_CH,
   INTC_CHANNEL_RESERVED_238_CH,
   INTC_CHANNEL_RESERVED_239_CH,
   INTC_CHANNEL_RESERVED_240_CH,
   INTC_CHANNEL_RESERVED_241_CH,
   INTC_CHANNEL_RESERVED_242_CH,
   INTC_CHANNEL_RESERVED_243_CH,
   INTC_CHANNEL_RESERVED_244_CH,
   INTC_CHANNEL_RESERVED_245_CH,
   INTC_CHANNEL_RESERVED_246_CH,
   INTC_CHANNEL_RESERVED_247_CH,
   INTC_CHANNEL_RESERVED_248_CH,
   INTC_CHANNEL_RESERVED_249_CH,
   INTC_CHANNEL_RESERVED_250_CH,
   INTC_CHANNEL_RESERVED_251_CH,
   INTC_CHANNEL_RESERVED_252_CH,
   INTC_CHANNEL_RESERVED_253_CH,
   INTC_CHANNEL_RESERVED_254_CH,
   INTC_CHANNEL_RESERVED_255_CH,
   INTC_CHANNEL_RESERVED_256_CH,
   INTC_CHANNEL_RESERVED_257_CH,
   INTC_CHANNEL_RESERVED_258_CH,
   INTC_CHANNEL_RESERVED_259_CH,
   INTC_CHANNEL_RESERVED_260_CH,
   INTC_CHANNEL_RESERVED_261_CH,
   INTC_CHANNEL_RESERVED_262_CH,
   INTC_CHANNEL_RESERVED_263_CH,
   INTC_CHANNEL_RESERVED_264_CH,
   INTC_CHANNEL_RESERVED_265_CH,
   INTC_CHANNEL_RESERVED_266_CH,
   INTC_CHANNEL_RESERVED_267_CH,
   INTC_CHANNEL_RESERVED_268_CH,
   INTC_CHANNEL_RESERVED_269_CH,
   INTC_CHANNEL_RESERVED_270_CH,
   INTC_CHANNEL_RESERVED_271_CH,
   INTC_CHANNEL_RESERVED_272_CH,
   INTC_CHANNEL_RESERVED_273_CH,
   INTC_CHANNEL_RESERVED_274_CH,
   INTC_CHANNEL_RESERVED_275_CH,
   INTC_CHANNEL_RESERVED_276_CH,
   INTC_CHANNEL_RESERVED_277_CH,
   INTC_CHANNEL_RESERVED_278_CH,
   INTC_CHANNEL_RESERVED_279_CH,
   INTC_CHANNEL_RESERVED_280_CH,
   INTC_CHANNEL_RESERVED_281_CH,
   INTC_CHANNEL_RESERVED_282_CH,
   INTC_CHANNEL_RESERVED_283_CH,
   INTC_CHANNEL_RESERVED_284_CH,
   INTC_CHANNEL_RESERVED_285_CH,
   INTC_CHANNEL_RESERVED_286_CH,
   INTC_CHANNEL_RESERVED_287_CH,
   INTC_CHANNEL_RESERVED_288_CH,
   INTC_CHANNEL_RESERVED_289_CH,
   INTC_CHANNEL_RESERVED_290_CH,
   INTC_CHANNEL_RESERVED_291_CH,
   INTC_CHANNEL_RESERVED_292_CH,
   INTC_CHANNEL_RESERVED_293_CH,
   INTC_CHANNEL_RESERVED_294_CH,
   INTC_CHANNEL_RESERVED_295_CH,
   INTC_CHANNEL_RESERVED_296_CH,
   INTC_CHANNEL_RESERVED_297_CH,
   INTC_CHANNEL_RESERVED_298_CH,
   INTC_CHANNEL_RESERVED_299_CH,
   INTC_CHANNEL_RESERVED_300_CH,
   INTC_CHANNEL_PIT_0_CH,
   INTC_CHANNEL_PIT_1_CH,
   INTC_CHANNEL_PIT_2_CH,
   INTC_CHANNEL_PIT_3_CH,
   INTC_CHANNEL_RTI_CH,
   INTC_CHANNEL_PMC_CH,
   INTC_CHANNEL_ECC_CORRECTION_CH,
   INTC_CHANNEL_RESERVED_308_CH,
   INTC_CHANNEL_RESERVED_309_CH,
   INTC_CHANNEL_RESERVED_310_CH,
   INTC_CHANNEL_RESERVED_311_CH,
   INTC_CHANNEL_RESERVED_312_CH,
   INTC_CHANNEL_RESERVED_313_CH,
   INTC_CHANNEL_RESERVED_314_CH,
   INTC_CHANNEL_RESERVED_315_CH,
   INTC_CHANNEL_RESERVED_316_CH,
   INTC_CHANNEL_RESERVED_317_CH,
   INTC_CHANNEL_RESERVED_318_CH,
   INTC_CHANNEL_RESERVED_319_CH,
   INTC_CHANNEL_RESERVED_320_CH,
   INTC_CHANNEL_RESERVED_321_CH,
   INTC_CHANNEL_RESERVED_322_CH,
   INTC_CHANNEL_RESERVED_323_CH,
   INTC_CHANNEL_RESERVED_324_CH,
   INTC_CHANNEL_RESERVED_325_CH,
   INTC_CHANNEL_RESERVED_326_CH,
   INTC_CHANNEL_RESERVED_327_CH,
   INTC_CHANNEL_RESERVED_328_CH,
   INTC_CHANNEL_RESERVED_329_CH,
   INTC_CHANNEL_RESERVED_330_CH,
   INTC_CHANNEL_RESERVED_331_CH,
   INTC_CHANNEL_RESERVED_332_CH,
   INTC_CHANNEL_RESERVED_333_CH,
   INTC_CHANNEL_RESERVED_334_CH,
   INTC_CHANNEL_RESERVED_335_CH,
   INTC_CHANNEL_RESERVED_336_CH,
   INTC_CHANNEL_RESERVED_337_CH,
   INTC_CHANNEL_RESERVED_338_CH,
   INTC_CHANNEL_RESERVED_339_CH,
   INTC_CHANNEL_RESERVED_340_CH,
   INTC_CHANNEL_RESERVED_341_CH,
   INTC_CHANNEL_RESERVED_342_CH,
   INTC_CHANNEL_RESERVED_343_CH,
   INTC_CHANNEL_RESERVED_344_CH,
   INTC_CHANNEL_RESERVED_345_CH,
   INTC_CHANNEL_RESERVED_346_CH,
   INTC_CHANNEL_RESERVED_347_CH,
   INTC_CHANNEL_RESERVED_348_CH,
   INTC_CHANNEL_RESERVED_349_CH,
   INTC_CHANNEL_RESERVED_350_CH,
   INTC_CHANNEL_RESERVED_351_CH,
   INTC_CHANNEL_RESERVED_352_CH,
   INTC_CHANNEL_RESERVED_353_CH,
   INTC_CHANNEL_RESERVED_354_CH,
   INTC_CHANNEL_RESERVED_355_CH,
   INTC_CHANNEL_RESERVED_356_CH,
   INTC_CHANNEL_RESERVED_357_CH,
   INTC_CHANNEL_STM_1_CH,
   INTC_CHANNEL_STM_2_CH,
   INTC_CHANNEL_STM_3_CH,
   INTC_CHANNEL_RESERVED_361_CH,
   INTC_CHANNEL_RESERVED_362_CH,
   INTC_CHANNEL_RESERVED_363_CH
}  INTC_Channel_T;





typedef void (*INTC_Vector_Callback_T)( void);



typedef enum
{
   INTC_INTERRUPT_METHOD_SOFTWARE,
   INTC_INTERRUPT_METHOD_HARDWARE
}INTC_Interrupt_Method_T;

typedef enum
{
   INTC_Vector_Table_Entry_Size_4,
   INTC_Vector_Table_Entry_Size_8
}INTC_Vector_Table_Entry_Size_T;


//=============================================================================
typedef struct 
{
   uint32_t exception_id;
   uint32_t srr0;
   uint32_t srr1;
   uint32_t csrr0;
   uint32_t csrr1;
   uint32_t dsrr0;
   uint32_t dsrr1;
   uint32_t esr;
   uint32_t mcsr;
   uint32_t dear;
}INTC_EXCEPTION_Log_T;

typedef enum
{
   INTC_EXCEPTION_IVOR0_CRITICAL_INPUT,
   INTC_EXCEPTION_IVOR1_MACHINE_CHECK,
   INTC_EXCEPTION_IVOR2_DATA_STORAGE,
   INTC_EXCEPTION_IVOR3_INSTRUCTION_STORAGE,
   INTC_EXCEPTION_IVOR4_EXTERNAL_INPUT,
   INTC_EXCEPTION_IVOR5_ALIGNMENT,
   INTC_EXCEPTION_IVOR6_PROGRAM,
   INTC_EXCEPTION_IVOR7_FLOATING_POINT_UNAVAILABLE,
   INTC_EXCEPTION_IVOR8_SYSTEM_CALL,
   INTC_EXCEPTION_IVOR9_AUXILIARY_PROCESSOR_UNAVAILABLE,
   INTC_EXCEPTION_IVOR10_DECREMENTER,
   INTC_EXCEPTION_IVOR11_FIXED_INTERVAL_TIMER_INTERRUPT,
   INTC_EXCEPTION_IVOR12_WATCHDOG_TIMER_INTERRUPT,
   INTC_EXCEPTION_IVOR13_DATA_TLB_ERROR,
   INTC_EXCEPTION_IVOR14_INSTRUCTION_TLB_ERROR,
   INTC_EXCEPTION_IVOR15_DEBUG,
   INTC_EXCEPTION_IVOR32_SPE_APU_UNAVAILABLE,
   INTC_EXCEPTION_IVOR33_SPE_FLOATING_POINT_DATA_EXCEPTION,
   INTC_EXCEPTION_IVOR34_SPE_FLOATING_POINT_ROUND_EXCEPTION,
   INTC_EXCEPTION_UNUSED_EXCEPTION,
   INTC_EXCEPTION_IVOR_MAX

}INTC_EXCEPTION_T;



typedef void(*INTC_EXCEPTION_Handler_T)(void);

//=============================================================================
// INTC_EXCEPTION_Halt
//
// @func
//
// @rdesc none
//
// @end
//=============================================================================
void INTC_EXCEPTION_Halt( void );



//=============================================================================
// INTC_Exception_Initialize
//
// @func 
//
// @rdesc none
//
// @end
//=============================================================================
void INTC_Exception_Initialize( void* in_table );


//=============================================================================
// Called whenever an interrupt is generated. This routine will call the
//  appropriate interrupt handler ( eMIOS, INTC, SIU, etc. ).
//
// @param None.
//
// @return None.
//
// @par External References:
//   INTC Vector table.
//
// @par Deviations From Standards:
//   None.
//
// @par Preconditions:
// This function must only be called as an interrupt service routine.
//
// @par Postconditions:
// Disables/blocks all interrupts ( of current priority and lower ).
//
//=============================================================================
void INTC_Interrupt_Handler( void );

void INTC_External_Interrupt_Prologue( void );
void INTC_External_Interrupt_Epilogue(void );




extern const  INTC_Vector_Callback_T INTC_Vector_Table[ NO_OF_INTC_CHANNEL ];


#endif // DD_INTC_H

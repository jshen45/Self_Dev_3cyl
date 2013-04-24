#ifndef HAL_SPARK_H
#define HAL_SPARK_H

//=============================================================================
// include files
//=============================================================================
#include "hal.h"

//=============================================================================
// Spark
//=============================================================================
//=============================================================================
// SetHWIO_SPARK_DiagEnabled
//=============================================================================
void SetHWIO_SPARK_DiagEnabled( void );

//=============================================================================
// SetHWIO_SPARK_DiagDisabled
//=============================================================================
void SetHWIO_SPARK_DiagDisabled( void );

//=============================================================================
// DisableHWIO_EST
//=============================================================================
void DisableHWIO_EST( void );

//=============================================================================
// EnableHWIO_EST
//=============================================================================
void EnableHWIO_EST( void );
//=============================================================================
// GetHWIO_t_DeliveredDwell
//=============================================================================
T_MILLISECONDSb GetHWIO_t_DeliveredDwell( void );
//=============================================================================
// GetHWIO_Num58xGapsBeforeSeqn
//=============================================================================
uint8_t GetHWIO_Num58xGapsBeforeSeqn (void);

//=============================================================================
// GetHWIO_phi_DeliveredSparkAngle
//=============================================================================
T_ANGLEa GetHWIO_phi_DeliveredSparkAngle(uint8_t in_cylinder );

//=============================================================================
// SetHWIO_DualEST_AlternatingMode
//=============================================================================
void SetHWIO_DualEST_AlternatingMode( void );
//=============================================================================
// SetHWIO_DwellTime
//=============================================================================
void SetHWIO_DwellTime(T_MILLISECONDSb in_dwell_time );
//=============================================================================
// SetHWIO_MaxDwell
//=============================================================================
void SetHWIO_MaxDwell(T_MILLISECONDSb in_max_dwell );
//=============================================================================
// SetHWIO_MinDwell
//=============================================================================
void SetHWIO_MinDwell(T_MILLISECONDSb in_min_dwell );
//=============================================================================
// SetHWIO_SequentialEST_Mode
//=============================================================================
void SetHWIO_SequentialEST_Mode( void );
//=============================================================================
// SetHWIO_SimultaneousEST_Mode
//=============================================================================
void SetHWIO_SimultaneousEST_Mode( void );
//=============================================================================
// SetHWIO_SingleChannelEST_Mode
//=============================================================================
void SetHWIO_SingleChannelEST_Mode( void );

//=============================================================================
// SetHWIO_SpkAngle
//=============================================================================
void SetHWIO_SpkAngle( T_ANGLEa * in_spark_angle );
//=============================================================================
// SetHWIO_SprkMinBurn
//=============================================================================
void SetHWIO_SprkMinBurn(T_MILLISECONDSb SfVIOS_MinBurn);

//=============================================================================
// EnableHWIO_Spark_Overide
//=============================================================================
void EnableHWIO_Spark_Overide(void);

//=============================================================================
// DisableHWIO_Spark_Overide
//=============================================================================
void DisableHWIO_Spark_Overide(void);
//=============================================================================
// SetHWIO_SparkForcedPulse
//=============================================================================
void SetHWIO_SparkForcedPulse(uint8_t in_channel, T_MILLISECONDSb in_dwell_time);

//=============================================================================
// GetHWIO_t_Spark_BurnTime
//=============================================================================
T_MILLISECONDSb GetHWIO_t_Spark_BurnTime( uint8_t in_cylinder, uint8_t in_pulse_index );
//=============================================================================
// GetIO_SPRK_BurnTime
//=============================================================================
T_MILLISECONDSb GetIO_SPRK_BurnTime( uint8_t in_cylinder, uint8_t in_pulse_index );
//=============================================================================
// SetIO_SPRK_BT_OneShotOption
//=============================================================================
void SetIO_SPRK_BT_OneShotOption(TbBOOLEAN one_shot);
//=============================================================================
// SetHWIO_Min_OffTime
//=============================================================================
void SetHWIO_Min_OffTime(T_MILLISECONDSb in_min_dwell );
//=============================================================================
// SetIO_SPRK_BT_WakeUpDelay
//=============================================================================
void SetIO_SPRK_BT_WakeUpDelay(T_MILLISECONDSb in_wakeup_delay );

#endif



#ifndef IO_CONFIG_PIT_H
#define IO_CONFIG_PIT_H

#include "io_config_fmpll.h"



//=============================================================================
// PIT Scaling
//=============================================================================
#define PIT_INTERNAL_VALUE_10MS  10000
#define RTI_INTERNAL_VALUE_1MS    1000
#define PIT_INTERNAL_VALUE_20US    20
#define PIT_INTERNAL_VALUE_5US    5

#define PIT_CLOCK_FREQUENCY_HZ (SYSTEM_FREQUENCY_HZ)
#define RTI_CLOCK_FREQUENCY_HZ (CRYSTAL_FREQUENCY_HZ)

#define PIT_LOAD_VALUE_10MS                 (PIT_INTERNAL_VALUE_10MS/ ( 1000000.0/PIT_CLOCK_FREQUENCY_HZ  ) ) //1ms     
#define RTI_LOAD_VALUE_1MS                 (RTI_INTERNAL_VALUE_1MS/ ( 1000000.0/RTI_CLOCK_FREQUENCY_HZ  ) ) //1ms     
#define PIT_LOAD_VALUE_20US                 (PIT_INTERNAL_VALUE_20US/ ( 1000000.0/PIT_CLOCK_FREQUENCY_HZ  ) )      
#define PIT_LOAD_VALUE_5US                 (PIT_INTERNAL_VALUE_5US/ ( 1000000.0/PIT_CLOCK_FREQUENCY_HZ  ) )      

#endif //IO_CONFIG_PIT_H

#ifndef OS_TYPE_H
#define OS_TYPE_H

//=============================================================================
// include files
//=============================================================================
#include "reuse.h"

//=============================================================================
// type define
//=============================================================================
typedef union
{
   struct
   {
      uint8_t TimeFor1ms     : 1 ;
      uint8_t TimeFor5ms     : 1 ;
      uint8_t TimeFor10ms   : 1 ;
      uint8_t Unused                : 5 ;
   } bf;
   uint8_t byte;
} RtiFlagsType ;

//=============================================================================
// extern variables
//=============================================================================
extern RtiFlagsType RTI_Flags;

#endif
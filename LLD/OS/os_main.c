//=============================================================================
// include files
//=============================================================================
#include "os_main.h"


//=============================================================================
// function define
//=============================================================================
void StartupHook(void);
//=============================================================================
// function define
//=============================================================================
void StartOS_Task_Normal(void);

//=============================================================================
// StartOS
//=============================================================================
void StartOS(AppModeType_T Mode)
{


   StartupHook();
   InitializeHardwareLast();


   if( Mode == AM_normal )
   {

      StartOS_Task_Normal();
   }
   else
   {
      while(1);
   }

}





#ifndef HLS_H
#define HLS_H

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "reuse.h"
#include "t_scaled.h"
#include "t_custom.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
/*  none */


/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/


/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/
typedef struct {
uint8_t B_failed : 1; /*signal failed * comprehending min, max and sig*/
uint8_t B_fail_pending : 1; /*signal failure pending */
uint8_t B_max : 1; /* signal value high or short to battery */
uint8_t B_min : 1; /* signal value low or short to ground */
uint8_t B_sig : 1; /* signal open load */
uint8_t B_npl : 1; /* reserved position for HLS signal value non-plausible ( for EOBD) */
uint8_t B_substitute: 1; /* substitute value is being passed by LLD */
uint8_t B_clrerr : 1; /* reserved position for HLS */
} status_bits;

/*ATD input module*/
typedef struct{
uint16_t     LLD_atd_val; /* raw value from register(10bit width) */
status_bits  LLD_atd_status; /* Status Code */
} LLD_atd_input_item;

/* DI data structure */
typedef struct{
uint8_t DebounceTimes; // HLS can set it in initialization, other wise it��s 0
uint8_t value ; /* Input level to return,1 or 0 */
status_bits status ; /* Status when electrical diagnostics are available, otherwise no use */
}LLD_di_item;

typedef struct{
uint8_t value; /* Value to be output 0-low; 1-high */
status_bits status; /* Status code - Reserved */
}LLD_do_item;

typedef struct{
uint8_t B_enable; /* enable the PWM channel, only writable by HLS */
uint8_t period; /* PWM period */
uint8_t duty; /* PWM duty cycle */
status_bits status; /* Status Code */
}LLD_pwm_out_item;

typedef struct {
uint8_t B_crank_failed : 1; /*signal failed */
uint8_t B_crank_no_sync : 1; /*crank no movement */
uint8_t B_crank_sync : 1; /*crank synchronizedy */
uint8_t B_crank_pre_sync : 1; /* crank moving but not synchronized, 3 or less teeth */
uint8_t B_crank_stall : 1; /* crank was synched but now no movement */
uint8_t B_crank_loss_of_sync : 1; /* lost synchronization */
uint8_t B_crank_limp_home : 1; /* running limphome on CAM sensor */
uint8_t B_rsv : 1; /* reserved bits */
} crank_status_bits;

typedef struct {
uint32_t segment_time; // Segement time
uint16_t engine_rpm; // Engine revolution per minute
uint8_t  engine_position_tc; // Engine position tooth count
crank_status_bits crank_status; // Crank status
} crank_signals;

typedef struct {
uint8_t B_cam_failed : 1; /*signal failed */
uint8_t B_cam_loss_of_sync : 1; /* cam level is wrong at the crank GAP */
uint8_t B_cam_limp_home : 1; /* running limphome on crank sensor */
uint8_t B_rsv : 5; /* reserved bits */
} cam_status_bits;

typedef struct {
uint32_t period; // between falling edges
uint8_t edge_count; // cam edge counter, from 1 to 8
uint8_t level; // current cam sensor level
cam_status_bits status;
} cam_signals;

typedef struct {
uint16_t period; // Vehicle Speed Period
status_bits status;
} veh_spd_signals;


/*ignition channels, A,B,C,D are corresponding to the firing order: 1,3,4,2 for example*/
typedef struct {
uint8_t B_ign_A : 1; /*enable igntion channel A */
uint8_t B_ign_B : 1; /*enable igntion channel B */
uint8_t B_ign_C : 1; /*enable igntion channel C */
uint8_t B_ign_D : 1; /*enable igntion channel D */
uint8_t B_ign_rsv : 4; /*reserved */
} ign_enable_bits;


typedef struct {
int8_t ign_angle;
uint16_t dwell_time;
uint8_t   follow_up_sparks;
uint16_t dwell_time_of_follow_up_sparks;
uint16_t break_time_of_follow_up_sparks;
status_bits status; /* Status Code */
} ign_signals;


/*injection channels, A,B,C,D are corresponding to the firing order: 1,3,4,2 for example*/
typedef struct {
uint8_t B_inj_A : 1; /*enable injection channel A */
uint8_t B_inj_B : 1; /*enable injection channel B */
uint8_t B_inj_C : 1; /*enable injection channel C */
uint8_t B_inj_D : 1; /*enable injection channel D */
uint8_t B_inj_rsv : 4; /* reserved */
} inj_enable_bits;


typedef struct {
uint8_t inj_end_angle;
uint32_t inj_time;
uint8_t B_post_inj; /*boundary conditions, HLS to set this bit and let LLD to handle the latency.*/
uint16_t post_inj_time;
uint8_t abort_angle;
status_bits status; /* Status Code */
} inj_signals;

typedef struct {
uint8_t desired_position; /* HLS commanded position */
uint8_t current_position; /* LLD calculated position, LLD updates this every 5 ms */
uint8_t correct_position; /* The real current position calculated by HLS during idle status */
bool B_correct_position; /* Conditon to correct variable ��current_position�� by variable
                            correct_position */
bool B_zero_position_learning; /* HLS commands LLD to learn the zero position */
status_bits status1; /* Status Code */
//step_status_bits status2; /* stepper specific status bits */
} Step_signals;

typedef struct {
uint8_t B_Pwf : 1; /*ECU power fail happened */
uint8_t B_after_run_end_abnormal: 1; /* ECU after run end abnormally */
uint8_t B_rsv : 6; /*reserved bits */
} sys_status_bits;

typedef struct {
uint8_t B_SW_Pwf : 1; /*HLS commanded power fail */
uint8_t B_after_run_end: 1; /* HLS after-run end */
uint8_t B_rsv : 6; /* reserved bits */
} sys_cmmd_bits;


typedef enum
{
   LLD_AN00,
   LLD_AN01,
   LLD_AN02,
   LLD_AN03,
   LLD_AN04,
   LLD_AN05,
   LLD_AN06,
   LLD_AN07,
   LLD_AN08,
   LLD_AN09,
   LLD_AN10,
   LLD_AN11,
   LLD_AN12,
   LLD_AN13,
   LLD_AN14,
   LLD_AN15,
   LLD_AN16,
   LLD_AN17,
   LLD_AN18,
   LLD_AN19,
   LLD_AN20,
   LLD_AN21,
   LLD_AN22,
   LLD_AN23,
   LLD_ATD_MAX_CHANNEL 
}  LLD_ATD_T;

typedef enum
{
   LLD_DI00,
   LLD_DI01,
   LLD_DI02,
   LLD_DI03,
   LLD_DI04,
   LLD_DI05,
   LLD_DI06,
   LLD_DI07,
   LLD_DI08,
   LLD_DI09,
   LLD_DI10,
   LLD_DI11,
   LLD_DI12,
   LLD_DI_MAX_CHANNEL 
}  LLD_DI_T;

typedef enum
{
   LLD_DO00,
   LLD_DO01,
   LLD_DO02,
   LLD_DO03,
   LLD_DO04,
   LLD_DO05,
   LLD_DO06,
   LLD_DO07,
   LLD_DO08,
   LLD_DO09,
   LLD_DO10,
   LLD_DO11,
   LLD_DO12,
   LLD_DO13,
   LLD_DO14,
   LLD_DO_MAX_CHANNEL 
}  LLD_DO_T;

typedef enum
{
   LLD_PWM00,
   LLD_PWM01,
   LLD_PWM02,
   LLD_PWM03,
   LLD_PWM04,
   LLD_PWM05,
   LLD_PWM06,
   LLD_PWM07,
   LLD_PWM08,
   LLD_PWM09,
   LLD_PWM_MAX_CHANNEL 
}  LLD_PWM_T;


typedef enum{
CYLINDER_0=0,
CYLINDER_1,
CYLINDER_2,
CYLINDER_3
} current_channel_num;


typedef struct
{			
       uint8_t  tele_Monitor_status[4];      /*0x01  Monitor status since DTCs cleared */
	//uint8_t   tele_Monitor_status_2;      /*0x02  Monitor status since DTCs cleared */
       //uint8_t   tele_Monitor_status_3;      /*0x03  Monitor status since DTCs cleared */
	//uint8_t   tele_Monitor_status_4;      /*0x04 Monitor status since DTCs cleared */
       uint16_t tele_Cause_Frame_Pcode;  /* 0x02 DTC that caused required freeze frame data storage */
  uint8_t  tele_B_FuelStatus;      /* 0x03  fuel supply system status*/		                         
  uint8_t  tele_CsMaf;	           /* 0x04  Calculated LOAD Value	*/
  uint8_t  tele_TmLin;   	   /* 0x05  Engine Coolant Temperature	*/
  uint8_t  tele_fLc;	           /* 0x06  Short Term Fuel Trim Bank 1 	*/
  uint8_t  tele_fLcAd;	           /* 0x07  Long Term Fuel Trim Bank 1	*/
  uint8_t  tele_Pmap;	           /* 0x0B  Intake Manifold Absolute Pressure	*/
  uint16_t tele_N;	           /* 0x0C  Engine RPM	*/
  uint8_t  tele_Vsp;	           /* 0x0D  Vehicle Speed Sensor	*/
  uint8_t  tele_IgaOut;	           /* 0x0E  Ignition Timing Advance for #1 Cylinder	*/
  uint8_t  tele_TaLin;	           /* 0x0F  Intake Air Temperature	*/
  uint8_t  tele_TpPos;	           /* 0x11  Absolute Throttle Position	*/
  uint8_t  tele_O2SPos;	           /* 0x13  Location of Oxygen Sensors	*/
  uint8_t  tele_uLsb;	           /* 0x14  Sensor Output Voltage	*/
  uint8_t  tele_uLsbfLc;           /* 0x14  Short Term Fuel Trim (B1-S1)	*/
  uint8_t  tele_uLsa;	           /* 0x15  Sensor Output Voltage	*/
  uint8_t  tele_uLsafLc;           /* 0x15  Short Term Fuel Trim (B1-S2)	*/
  uint8_t  tele_obd_Type;          /* 0x1C  OBD requirements to which vehicle is designed 	*/
  uint16_t tele_tStaEnd;           /* 0x1F  Time Since Engine Start	*/
  uint16_t tele_KmQ6Mil;           /* 0x21  Distance Travelled While MIL is Activated	*/
  uint8_t  tele_DuCyPgOut;         /* 0x2E  Command Evaporative Purge	*/
  uint8_t  tele_fuel;	           /* 0x2F  Fuel Level Input	*/
  uint8_t  tele_WmuCntVal;         /* 0x30  Number of warm-ups since diagnostic trouble codescleared	*/
  uint8_t  tele_Pam;	           /* 0x33  Ambient air Pressure	*/
  uint16_t tele_TcatMain;          /* 0x3C  Catalyst Temperature	*/
  uint16_t tele_Ub_b;	           /* 0x42  System voltage	*/
  uint8_t  tele_Tam;	           /* 0x46  Ambient air temperature	*/
}tele_type;
extern tele_type telem_data;


/*the flowing is SAEJ1979 service 0x02 */		 
typedef struct										
{	
       uint16_t Ffm_Frame_Pcode;   /* 0x02  indicates no freeze frame data)  */
       uint8_t  Ffm_B_FuelStatus; /* 0x03fuel supply system status*/                        
	uint8_t	Ffm_CsMaf;	  /* 0x04	Calculated LOAD Value!	*/
	uint8_t	Ffm_TmLin;     /* 0x05	Engine Coolant Temperature	*/
	uint8_t	Ffm_fLc;	      /* 0x06	Short Term Fuel Trim Bank	*/
	uint8_t	Ffm_fLcAd;     /* 0x07	Long Term Fuel Trim Bank 	*/
	uint8_t	Ffm_Pmap;      /* 0x0B	Intake Manifold Absolute pressure	*/
	uint16_t Ffm_N;	      /* 0x0C	Engine RPM	*/
	uint8_t	Ffm_Vsp;	      /* 0x0D	Vehicle Speed Sensor	*/
	uint8_t	Ffm_IgaOut;    /* 0x0E	Ignition Timing Advance for #1 Cylinder	*/
	uint8_t	Ffm_TaLin;	  /* 0x0F	Intake Air Temperature	*/
	uint8_t	Ffm_TpPos;     /* 0x11	Absolute Throttle Position	*/
	uint16_t Ffm_KmQ6Mil;  /* 0x21	Distance Travelled While MIL is Activated	*/
	uint16_t Ffm_Ub_b;	  /* 0x42	System voltage	*/
}Freeze_Frame_Elem;										
extern Freeze_Frame_Elem  DIAG_STATUS_FREEZE_FRAME;


typedef struct									
{	uint8_t   VIN[17];				/*Vehicle Identification Number*/				
	uint8_t   CALID[16];				/*Calibration Identifications*/				
	uint8_t   CVN[4];				/*Calibration Verification Numbers*/				
}VehicleInformation;


#define SCN_ECUID_SWVERNUM_LENGHT	16
#define SCN_ECUID_HWVERNUM_LENGHT	4
#define SCN_ECUID_MDLSERNUM_LENGHT	30
#define SCN_ECUID_PRGINF_LENGHT		18

typedef struct ECU_Identification {
	uint8_t	SwVerNum[SCN_ECUID_SWVERNUM_LENGHT];
	uint8_t	HwVerNum[SCN_ECUID_HWVERNUM_LENGHT];
	uint8_t	MdlSerNum[SCN_ECUID_MDLSERNUM_LENGHT];
	uint8_t	PrgInf_Original[SCN_ECUID_PRGINF_LENGHT];
	uint8_t	PrgInf_No1[SCN_ECUID_PRGINF_LENGHT];
	uint8_t	PrgInf_No2[SCN_ECUID_PRGINF_LENGHT];
	uint8_t	PrgInf_No3[SCN_ECUID_PRGINF_LENGHT];
}ECU_Identification;
extern ECU_Identification scnEcuId;


#define			SY_FCMTSIZE			5
extern uint8_t 	count_DTCs_SID03;				/* DTC counter for service 03 */
extern uint16_t	DTCs_SID03[SY_FCMTSIZE];		/* DTCs for service 03*/

extern bool	B_DiagInfoClrReq;		/*condition: request to clear diagnostic information */

#define			SY_FCMTSIZE			5
extern uint8_t 	count_DTCs_SID07;				/* DTC counter for service 07 */
extern uint16_t	DTCs_SID07[SY_FCMTSIZE];		/* DTCs for service 07*/

/* ==========================================================================*\
 * Exported INLINE functions and #define function-like macros.
\* ==========================================================================*/
/*chery ATD*/
/* ATD Index */
#define LLD_ATD_MAP LLD_AN01
#define LLD_ATD_VBATT_SW LLD_AN02
#define LLD_ATD_OXYGEN_SENSOR_1 LLD_AN03
#define LLD_ATD_OXYGEN_SENSOR_2 LLD_AN04
#define LLD_ATD_TA LLD_AN05
#define LLD_ATD_ECT LLD_AN06
#define LLD_ATD_THROTTLE_1 LLD_AN07
#define LLD_ATD_THROTTLE_2 LLD_AN08
#define LLD_ATD_PEDAL_1 LLD_AN09
#define LLD_ATD_PEDAL_2 LLD_AN10
#define LLD_ATD_FRONT_EVAP_TEMP LLD_AN11
#define LLD_ATD_AC_PRESSURE  LLD_AN12


/*chery DI*/
/* DI Index */
#define LLD_DI_AC_REQUEST_INPUT LLD_DI00
#define LLD_DI_AC_PRESSURE_SWITCH LLD_DI01
#define LLD_DI_CAM_1 LLD_DI02
#define LLD_DI_IGN_ON_OFF_SW LLD_DI03
#define LLD_DI_HEAD_LAMP LLD_DI04
#define LLD_DI_POWER_STEERING LLD_DI05
#define LLD_DI_BRAKE_LAMP LLD_DI06
#define LLD_DI_BRAKE_SWITCH LLD_DI07
#define LLD_DI_CLUTCH_TOP LLD_DI08
/* Add for start-stop application */
//#define LLD_DI_CLUTCH_TOP LLD_DI06
//#define LLD_DI_START_MOTOR_FEEDBACK LLD_DI07
//#define LLD_DI_CLUTCH_BOTTOM LLD_DI08
//#define LLD_DI_NEUTRAL_GEAR LLD_DI09
//#define LLD_DI_DRIVE_CHAIN_RLY LLD_DI10
//#define LLD_DI_START_STOP_SWITCH LLD_DI11
//#define LLD_DI_HIGH_ENABLE_LOAD LLD_DI12

/*debounce time*/
/*Debounce time for all digital inputs are tentatively defined as 10ms. It could be changed later.*/
#define LLD_DI_AC_REQUEST_INPUT_DebTime 10 /*ms*/
#define LLD_DI_AC_PRESSURE_SWITCH_DebTime 10
#define LLD_DI_CAM_1_DebTime 10 /**/
#define LLD_DI_IGN_ON_OFF_SW_DebTime 10
#define LLD_DI_HEAD_LAMP_DebTime 10
#define LLD_DI_POWER_STEERING_DebTime 10
/* Add for start stop application */
#define LLD_DI_CLUTCH_TOP_DebTime 10
#define LLD_DI_HEAD_LAMP_COMP_DebTime 10
#define LLD_DI_START_MOTOR_FEEDBACK_DebTime 10
#define LLD_DI_CLUTCH_BOTTOM_DebTime 10
#define LLD_DI_NEUTRAL_GEAR_DebTime 10
#define LLD_DI_DRIVE_CHAIN_RLY_DebTime 10
#define LLD_DI_START_STOP_SWITCH_DebTime 10
#define LLD_DI_HIGH_ENABLE_LOAD_DebTime 10

/* Corresponding PIN number of connector */
#define LLD_DO_FAN1 LLD_DO00 //index of digital output channel 0
#define LLD_DO_FAN2 LLD_DO01 //index of digital output channel 1
#define LLD_DO_FUEL_PUMP LLD_DO02 //index of digital output channel 2
#define LLD_DO_MAIN_RELAY LLD_DO03 //index of digital output channel 3
#define LLD_DO_MIL_LAMP LLD_DO04 //index of digital output channel 4
#define LLD_DO_SVS_LAMP LLD_DO05 //index of digital output channel 5
#define LLD_DO_AC_CLUTCH LLD_DO06 //index of digital output channel 6
#define LLD_DO_R_LINE LLD_DO07 //index of digital output channel 7
#define LLD_DO_START_MOTR_RLY LLD_DO08 //index of digital output channel 8
#define LLD_DO_VIS_SWITCH LLD_DO09 //index of digital output channel 9
#define LLD_DO_ETB_DIS LLD_DO10 //index of digital output channel 10
#define LLD_DO_ETB_DIR LLD_DO11 //index of digital output channel 11

#define LLD_PWM_O2_HEATER_1 LLD_PWM00 //index of digital output channel 0
#define LLD_PWM_FUEL_CONSUMPTION LLD_PWM01 //index of digital output channel 6
#define LLD_PWM_PURGE LLD_PWM02 //index of digital output channel 2
#define LLD_PWM_ECT LLD_PWM03//index of digital output channel 5
#define LLD_PWM_EGR LLD_PWM04 //index of digital output channel 3
#define LLD_PWM_TACHO LLD_PWM05
#define LLD_PWM_O2_HEATER_2 LLD_PWM06
#define LLD_PWM_VVT1 LLD_PWM07
#define LLD_PWM_VVT2 LLD_PWM08
#define LLD_PWM_ETB LLD_PWM09



#define LLD_IGN_CHANNEL_A 0
#define LLD_IGN_CHANNEL_B 1
#define LLD_IGN_CHANNEL_C 2
#define LLD_IGN_CHANNEL_D 3
#define LLD_MAX_IGN_CHANNEL 4



#define INJ_CHANNEL_A 0
#define INJ_CHANNEL_B 1
#define INJ_CHANNEL_C 2
#define INJ_CHANNEL_D 3
#define MAX_INJ_CHANNEL 4


/*===========================================================================*/
/* Exported global variable                               */
/*===========================================================================*/
extern LLD_atd_input_item LLD_atd_input_table[LLD_ATD_MAX_CHANNEL];
extern LLD_di_item LLD_di_table[LLD_DI_MAX_CHANNEL];
extern LLD_do_item LLD_do_table[LLD_DO_MAX_CHANNEL]; /* Digital output value*/
extern LLD_pwm_out_item LLD_pwm_out_table[LLD_PWM_MAX_CHANNEL]; /* The index means the channel no of the PWM output module */
extern crank_signals crank_sig;
extern  cam_signals cam_sig;
extern veh_spd_signals veh_spd_sig;
extern current_channel_num LLD_cyl_num;
extern ign_enable_bits ign_enable;
extern ign_signals ign_sig[LLD_MAX_IGN_CHANNEL];
extern inj_enable_bits inj_enable;
extern inj_signals inj_sig[MAX_INJ_CHANNEL];
extern sys_status_bits sys_status;
extern sys_cmmd_bits sys_cmd;
extern Step_signals   StepSig;  
extern uint8_t        StepPos;
extern bool           B_syn_update;  
extern bool           B_KeyOn;  
extern bool           S_AC;
extern tele_type telem_data;


/* The coolant pull up resister flag */
/* True for 4k, False for 348 */
extern bool        CLT_Range_High;

/* The instant fuel consumption from HLS */
extern uint16_t instant_fuel_consumption;

/* HLS mileage variable */
extern uint32_t odometer;

/* Attention: Do not defined as hls_bss variable */
extern uint32_t Sys_time;

/* chery requirement*/
extern  const uint16_t VAL_uTpsMx;
extern  const uint16_t VAL_uTpsMn;
extern  const uint16_t VAL_uTmMx;
extern  const uint16_t VAL_uTmMn;
extern const uint16_t VAL_uTaMx;
extern  const uint16_t VAL_uTaMn;
extern  const uint16_t VAL_uPmapMx;
extern  const uint16_t VAL_uPmapMn;
extern  const uint16_t VAL_uLsbMx;
extern  const uint16_t VAL_uLsbMn;
extern  const uint8_t  VAL_LmDgFofDly;

/* IAC calibration */
extern  const uint8_t VAL_StepPosMx;
extern  const uint8_t VAL_dNStepLrn;

extern  const uint8_t VAL_TsStPos;

extern unsigned char  TpPos_b;
extern unsigned char  Pmap_b;
extern unsigned char  Tm;
extern unsigned char  TmLin;
extern unsigned char  Ta;
extern uint8_t FCMEnd;
extern uint8_t MafTst;
extern uint16_t fLc;
extern uint16_t fLcAd;
extern uint8_t Pmap_b;
extern uint16_t N;
extern uint8_t Vsp_b;
extern int8_t IgaOut;
//extern uint8_t TaLin;
extern uint16_t Tpp;
extern uint16_t uLsb;
extern uint16_t uLsa;
extern uint16_t KmQ1Mil;
extern uint8_t Ub_b;
extern uint8_t TpPos_b;
extern uint16_t uTm;
extern uint8_t uTa;
extern uint16_t uPmap;
extern uint16_t uTps;
extern uint16_t Ti;
extern uint8_t NDsrIdc;
extern uint8_t Ld_b;
extern uint16_t fAlt;
extern int16_t  dTqIdcP;
extern int16_t dTqIdcI;
//extern int8_t dIgaKnc[3];
//extern uint16_t FtCntEmisCyl[3];
extern uint8_t StepPos;
extern uint8_t StepPosDsr;
extern bool  B_Fan1;
extern bool  B_Fan2; 
extern bool  B_AcOn;
extern uint16_t tLsbAfFlt;
extern int8_t IntLcDwnI;
extern uint8_t SsCatDwnM;
extern uint8_t MxGrdLsaFit_b;
extern uint8_t Gr;
extern uint8_t Maf_b;

extern bool knock_flag_a;
extern bool knock_flag_b;
extern bool knock_flag_c;
extern bool knock_flag_d;

/*VCPC*/
extern unsigned int angle_crank_cam_inlet;
extern unsigned int angle_crank_cam_outlet;


/* Data for transmit */
extern uint8_t  VsCAN_CHERY_ID0FA[8];
extern uint8_t  VsCAN_CHERY_ID101[8];
extern uint8_t  VsCAN_CHERY_ID270[8];
extern uint8_t  VsCAN_CHERY_ID278[8];
extern uint8_t  VsCAN_CHERY_ID2C1[8];
extern uint8_t  VsCAN_CHERY_ID370[8];
extern uint8_t  VsCAN_CHERY_ID378[8];
extern uint8_t  VsCAN_CHERY_ID501[8];
extern uint8_t  VsCAN_CHERY_ID623[8];
extern uint8_t  VsCAN_CHERY_ID7C1[6];

/* Data for receive */
extern uint8_t  VsCAN_CHERY_ID2E9[8];
extern uint8_t  VsCAN_CHERY_ID310[8];
extern uint8_t  VsCAN_CHERY_ID391[8];
extern uint8_t  VsCAN_CHERY_ID3C0[8];
extern uint8_t  VsCAN_CHERY_ID430[8];

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/
/*Disable/enable interrupt interface*/
extern   void Disable_1ms_interrupt(void) ;
extern   void Enable_1ms_interrupt(void) ;
extern   void LLD_disable_interrupt(void);
extern   void LLD_enable_interrupt(void);
/* Call back function for 1ms task */
extern  void HLS_Task_1ms(void);
/* Call back function for 5ms task */
extern   void HLS_Task_5ms(void);
/* Call back function for 10ms task */
extern   void HLS_Task_10ms(void);
/* Call back function for 20ms task */
extern   void HLS_Task_20ms(void);
/* Call back function for 50ms task */
extern   void HLS_Task_50ms(void);
/* Call back function for 100ms task */
extern   void HLS_Task_100ms(void);
/* Call back function for 200ms task */
extern   void HLS_Task_200ms(void);
/* Call back function for 1000ms task */
extern  void HLS_Task_1000ms(void);
/*HLS initialization function.*/
extern   void HLS_ini(void);
/*HLS initialization function*/
extern  void HLS_ini2(void);
/*will be called after _ini() at ECU power on, and at engine stall*/
extern  void HLS_inisyn(void);
/*will be called when the synch is lost/reset, this is an event trigged function call*/
extern  void HLS_rstsyn(void);
/*will be called when the first Synchronization (first gap) is confirmed, this is an event trigged function call*/
extern  void HLS_firstsyn(void);
/*will be called for every segment (at Software reference mark)*/
extern  void HLS_syn(void);
/*will be called on each falling edge of the CAM1 signal*/
extern  void HLS_ph1(void);
/*will be called on each falling edge of the CAM2 signal*/
extern  void HLS_ph2(void);
/*will be called when Ignition off*/
extern  void HLS_afterrun(void); 
/*will be called at the falling edge of every crank tooth */
extern  void HLS_tooth_interrupt(void);


/*===========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/*===========================================================================*/
/*                                                                           */
/*  Date        user id     SCR       (description on following lines)       */
/* ----------   -------     ---     ----------------------------------       */
/*===========================================================================*/
#endif 

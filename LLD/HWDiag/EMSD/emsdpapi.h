#ifndef EMSDPAPI_H
#define EMSDPAPI_H
/******************************************************************************
 *
 * Filename:          emsdpapi.h
 *
 * Description:       This is the public header file for
 *                    the ems side I/O hardware diagnostics.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 * Forward Engine Management Systems
 *
 * Copyright 1997-2005 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#5/incl/emsdpapi.h/1 %
 * %date_created:  Wed Mar 19 10:10:11 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
 *  Include Files
 *****************************************************************************/

/******************************************************************************
 * Include Files
 *****************************************************************************/
#include "t_gentypes.h" /* For global data types            */

/******************************************************************************
 *  Function Exports
 *****************************************************************************/

/******************************************************************************
 *  AC Clutch Function Prototype
 *****************************************************************************/

void MngEMSD_AcClutch200msTasks (void);

/******************************************************************************
 *  Main Power Relay  Function Prototype
 *****************************************************************************/
void MngEMSD_MainRelay200msTasks (void);

/******************************************************************************
 *  Fuel Pump Function Prototype
 *****************************************************************************/

void MngEMSD_FuelPump200msTasks (void);

/******************************************************************************
 *  MIL Function Prototype
 *****************************************************************************/
void MngEMSD_MIL200msTasks (void);

/******************************************************************************
 *  SVS Function Prototype
 *****************************************************************************/
void MngEMSD_SVS200msTasks (void);

/******************************************************************************
 *  GIS Function Prototype
 *****************************************************************************/
void MngEMSD_GIS200msTasks (void);

/******************************************************************************
 *  Fanx Function Prototype
 *****************************************************************************/
void MngEMSD_FanA200msTasks (void);
void MngEMSD_FanB200msTasks (void);

/******************************************************************************
 *  SMR Function Prototype
 *****************************************************************************/
void MngEMSD_SMR200msTasks (void);

/******************************************************************************
 *  FileROM Function Prototype
 *****************************************************************************/
void InitEMSD_FileROMRstToKeyOn(void);
void MngEMSD_FileROM10msTasks (void);



void InitEMSD_AcClutchRstToKeyOn(void);
void InitEMSD_FanxRstToKeyOn(void);
//void InitEMSD_FileROMRstToKeyOn(void);
void InitEMSD_FuelPumpRstToKeyOn(void);
void InitEMSD_MILRstToKeyOn(void);
void InitEMSD_MainRelayRstToKeyOn(void);
void InitEMSD_SVSRstToKeyOn(void);
void InitEMSD_GISRstToKeyOn();
void InitEMSD_SmrRstToKeyOn();
#endif    /* #define EMSDPAPI_H                       */

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 
\* ============================================================================ */


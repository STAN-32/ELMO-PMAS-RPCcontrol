/* ============================================================================

Name:			Win32BulkRead.h

 Create	 :		16/12/2012
 Author  :		Hanoch Cassif
 Version :		1.0
 Description : 	
============================================================================ */
#include "MMC_definitions.h"
#include "MMCPPlib.hpp"
#include <ctime>
#include <iostream>


#define EXT


/* ============================================================================
 General constants
 ============================================================================ */
#define 	MAX_AXES					5		// number of Physical axes in the system.
#define		MAX_VECTORS					0		// number of X,Y vectors in the system.
#define 	FALSE						0
#define 	TRUE						1

#define 	RUN							1
#define 	DONE						0
#define 	ERROR					   -1


#define		VALID_STAND_STILL_MASK		0x40000080
#define		VALID_STAND_DISABLE_MASK	0x40000200

/* ============================================================================
 Application tyde definitions
 ============================================================================ */
enum AxisState
{
	STT_START,
	STT_CMD0,
	STT_CMD1,
	STT_CMD2,
	STT_CMD3,
	STT_CMD4,
	STT_CMD5,
	STT_DONE,
	STT_ERR
};


/* ============================================================================
 Application global variables
 ============================================================================ */
EXT MMC_CONNECT_HNDL			g_conn_hndl;
EXT MMC_READSTATUS_IN			read_status_in;
EXT MMC_READSTATUS_OUT			read_status_out;
EXT MMC_POWER_IN				power_in;
EXT MMC_POWER_OUT				power_out;
EXT MMC_CONNECTION_PARAM_STRUCT conn_param;
EXT MMC_GET_VER_OUT				ver_out;
EXT CMMCBulkRead				*stBulkData;
EXT MMC_CONFIGBULKREAD_IN 		stCfgBulkReadIn;
EXT CMMCConnection 				cConn ;
EXT CMMCSingleAxis 				cAxis[MAX_AXES];
EXT int 						axis_state[MAX_AXES];


EXT int 				giStatus;
timespec s_ts;
timespec e_ts;

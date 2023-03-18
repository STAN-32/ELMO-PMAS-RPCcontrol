////////////////////////////////////////////////////////////////////////////////
/// \file MMC_drive_comm_API.h
/// Name        : MMC_drive_comm_API.h
/// Author      : Barak R
/// Created on  : April 19, 20010
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.4.2 Updated 26Aug2019 Haim H.
///               0.4.3 Updated 20Apr2021 Haim H. Updates according to update in "Gen C lib in Plastic"
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_DRIVE_COMM_API_H_
#define MMC_DRIVE_COMM_API_H_

//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif


#define NODE_ASCII_ARRAY_MAX_LENGTH     80
#define ETHERCAT_ID_MAX                 100

////////////////////////////////////////////////////////////////////////////////
/// \enum OPM402
/// \brief DS402 operation modes.
////////////////////////////////////////////////////////////////////////////////
typedef enum OP_MODE_DS402
{
    OPM402_NO = -1,
    OPM402_PROFILE_POSITION_MODE = 1,
    OPM402_PROFILE_VELOCITY_MODE = 3,
    OPM402_TORQUE_PROFILE_MODE = 4,
    OPM402_HOMING_MODE = 6,
    OPM402_INTERPOLATED_POSITION_MODE = 7,
    OPM402_CYCLIC_SYNC_POSITION_MODE = 8,
    OPM402_CYCLIC_SYNC_VELOCITY_MODE = 9,
    OPM402_CYCLIC_SYNC_TORQUE_MODE = 10,
	OPM402_CYCLIC_SYNC_TORQUE_MODE_WITH_ANGLE = 11,
}OPM402;

typedef enum comm_err
{
    eCOMM_ERR_FAULT_BIT         = 0x1,
    eCOMM_ERR_AL_ERROR          = 0x2,
    eCOMM_ERR_HEARTBEAT         = 0x4,
    eCOMM_ERR_EMCY              = 0x10,
    eCOMM_ERR_UNEXPECTED_SW     = 0x20,
    eCOMM_ERR_COMM              = 0x40,
    eCOMM_ERR_AXIS_FAULT        = 0x80
}COMM_ERRORS;
////////////////////////////////////////////////////////////////////////////////
/// \enum NC_COMM_EVENT_GROUP
/// \brief PDO3/PDO4 configuration groups for TX PDO's
////////////////////////////////////////////////////////////////////////////////


typedef enum
{
    NC_COMM_EVENT_NO_GROUP = 0,
    NC_COMM_EVENT_GROUP1,   /// Position Actual Value + Velocity Actual Value
    NC_COMM_EVENT_GROUP2,   /// Position Actual Value + Digital Inputs
    NC_COMM_EVENT_GROUP3,   /// Digital Inputs + Velocity Actual Value
    NC_COMM_EVENT_GROUP4,   /// Digital Inputs + Current Actual Value
    NC_COMM_EVENT_GROUP5,   /// Current Actual Value + Position Actual Value
    NC_COMM_EVENT_GROUP6,   /// Current Actual Value + Velocity Actual Value
    NC_COMM_EVENT_GROUP7,   /// User parameter(Integer)+Actual Pos
    NC_COMM_EVENT_GROUP8,   /// User parameter(Integer)+Digital Inputs
    NC_COMM_EVENT_GROUP9,   /// User parameter(Float)+Actual Pos
    NC_COMM_EVENT_GROUP10,  /// User parameter(Float)+Digital Inputs
    NC_COMM_EVENT_GROUP11,  /// Digital Inputs
    NC_COMM_EVENT_GROUP12,  /// User parameter integer 1 + User parameter integer 2.
    NC_COMM_EVENT_GROUP13,  /// User parameter integer 3 + User parameter integer 4.
    NC_COMM_EVENT_GROUP14,  /// User parameter float   1 + User parameter float 2.
    NC_COMM_EVENT_GROUP15,  /// User parameter float   3 + User parameter float 4.
    NC_COMM_EVENT_GROUP16,  /// General Purpose group parameter1. 
    NC_COMM_EVENT_GROUP17   /// General Purpose group parameter2. 
}NC_COMM_EVENT_GROUP;


////////////////////////////////////////////////////////////////////////////////
/// \enum NC_COMM_EVENT_GROUP
/// \brief PDO3/PDO4 configuration groups for RX PDO's
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    NC_COMM_RXEVENT_NO_GROUP = 0,
    NC_COMM_RXEVENT_GROUP1,     /// User Integer 3  + user integer 3 aux.
    NC_COMM_RXEVENT_GROUP2,     /// User Integer 4  + user integer4 aux.
    NC_COMM_RXEVENT_GROUP3,     /// User Float 3    + user Float 3 aux.
    NC_COMM_RXEVENT_GROUP4,     /// User Float 4    + user Float 4 aux.
    NC_COMM_RXEVENT_GROUP5,     /// User Integer 3  + user Float 3.
    NC_COMM_RXEVENT_GROUP6,     /// General Purpose group parameter1. 
    NC_COMM_RXEVENT_GROUP7      /// General Purpose group parameter2. 
}NC_COMM_RXEVENT_GROUP;


typedef enum
{
    MC_PDO_EVENT_NO_NOTIF   = 0,
    MC_PDO_EVENT_CYCLIC_NOTIF ,
    MC_PDO_EVENT_IMMIDIATE_NOTIF
} MC_PDO_EVENT_NOTIF_MODE_ENUM;
//
#define PDO_COM_PARAM_SYNC  0x01
#define PDO_COM_PARAM_ASYNC 0xFF
#define PDO_COM_PARAM_EVENT 0xFE
//
typedef enum
{
    MC_PDO_TYPE_RPDO = 0,
    MC_PDO_TYPE_TXPDO
} MC_PDO_TYPE_ENUM;

typedef enum
{
    MC_PDO_TIMER_NON = 0,
    MC_PDO_TIMER_1_MILISEC,
    MC_PDO_TIMER_2_MILISEC,
    MC_PDO_TIMER_3_MILISEC,
    MC_PDO_TIMER_4_MILISEC,
    MC_PDO_TIMER_5_MILISEC,
    MC_PDO_TIMER_10_MILISEC = 10,
    MC_PDO_TIMER_20_MILISEC = 20,
    MC_PDO_TIMER_25_MILISEC = 25,
    MC_PDO_TIMER_50_MILISEC = 50,
    MC_PDO_TIMER_100_MILISEC = 100,
    MC_PDO_TIMER_150_MILISEC = 150,
    MC_PDO_TIMER_200_MILISEC = 200,
    MC_PDO_TIMER_250_MILISEC = 250,
    MC_PDO_TIMER_255_MILISEC = 255
} MC_PDO_TIMER_EVENT_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGREGULARPARAMEVENTPDO3_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32 uiPDOCommParamEvent;
    ELMO_UINT16 usEventTimer;
    ELMO_UINT8  ucEventGroup;
    ELMO_UINT8  ucPDOCommParam;
}MMC_CONFIGREGULARPARAMEVENTPDO3_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGREGULARPARAMEVENTPDO3_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CONFIGREGULARPARAMEVENTPDO3_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGREGULARPARAMEVENTPDO4_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32 uiPDOCommParamEvent;
    ELMO_UINT16 usEventTimer;
    ELMO_UINT8  ucEventGroup;
    ELMO_UINT8  ucPDOCommParam;
}MMC_CONFIGREGULARPARAMEVENTPDO4_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGREGULARPARAMEVENTPDO4_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CONFIGREGULARPARAMEVENTPDO4_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGUSERPARAMEVENTPDO3_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32 uiPDOCommParamEvent;
    ELMO_UINT16 usEventTimer;
    ELMO_UINT8  ucEventGroup;
    ELMO_UINT8  ucSubIndex;
    ELMO_UINT8  ucPDOCommParam;
    ELMO_UINT8  ucPDOType;
}MMC_CONFIGUSERPARAMEVENTPDO3_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGUSERPARAMEVENTPDO3_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CONFIGUSERPARAMEVENTPDO3_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGUSERPARAMEVENTPDO4_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32 uiPDOCommParamEvent ;
    ELMO_UINT16 usEventTimer;
    ELMO_UINT8  ucEventGroup;
    ELMO_UINT8  ucSubIndex;
    ELMO_UINT8  ucPDOCommParam;
    ELMO_UINT8  ucPDOType;
}MMC_CONFIGUSERPARAMEVENTPDO4_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGUSERPARAMEVENTPDO4_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CONFIGUSERPARAMEVENTPDO4_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CANCELPARAMEVENTPDO3_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 dummy;
}MMC_CANCELPARAMEVENTPDO3_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CANCELPARAMEVENTPDO3_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CANCELPARAMEVENTPDO3_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CANCELPARAMEVENTPDO4_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 dummy;
}MMC_CANCELPARAMEVENTPDO4_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CANCELPARAMEVENTPDO4_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CANCELPARAMEVENTPDO4_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETPDOINFO_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 ucPDONumber;
}MMC_GETPDOINFO_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETPDOINFO_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_getpdoinfo_out
{
    ELMO_INT32  iPDOEventMode;
    ELMO_UINT32 uiCommParamEventPDO;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
    ELMO_UINT16 usEventTimerPDO;
    ELMO_UINT8  ucRPDOCommType;
    ELMO_UINT8  ucTPDOCommType;
    ELMO_UINT8  ucTPDOCommEventGroup;
    ELMO_UINT8  ucRPDOCommEventGroup;
    ELMO_UINT8  ucSubIndexRPDO;
    ELMO_UINT8  ucSubIndexTPDO;
}MMC_GETPDOINFO_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SENDSDO_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    int32_t         lData;
    uint32_t        ulDataLength;
    ELMO_UINT16     usSlaveID;   // 2
    ELMO_UINT16     usIndex;
    ELMO_UINT8      ucSubIndex;
    ELMO_UINT8      ucService;    // 1 - Download, 2 - Upload
}MMC_SENDSDO_IN;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SENDSDO_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    int32_t         lData;
    uint32_t        ulDataLength;
    ELMO_UINT16     usStatus;    ///< Returned command status.
    ELMO_INT16      usErrorID;    ///< Returned command error ID.
}MMC_SENDSDO_OUT;
///////////////////////////////////////////////////////////////////////////////
/// \union SEND_SDO_DATA_EX
/// \brief
///////////////////////////////////////////////////////////////////////////////
//@IR - 13.09.17 - Added EC 8+ bytes SDO support.
typedef union
{
        ELMO_UINT8  pData[NODE_ASCII_ARRAY_MAX_LENGTH];
        ELMO_DOUBLE dbData;
        ELMO_FLOAT  fData;
        ELMO_UINT64 ullData;
        ELMO_INT64  llData;
        uint32_t    ulData;
        int32_t     lData;
        ELMO_UINT32 uiData;
        ELMO_INT32  iData;
        ELMO_UINT16 usData;
        ELMO_INT16  sData;
        ELMO_UINT8  ucData;
        ELMO_INT8   cData;

}SEND_SDO_DATA_EX;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SENDSDOEX_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
//@IR - 13.09.17 - Added EC 8+ bytes SDO support.
typedef struct mmc_sendsdoex_in
{
        //data
        SEND_SDO_DATA_EX uData;

        //Reserve
        int32_t     pReserve[10];

        ELMO_UINT16 usIndex;     //index
        ELMO_UINT8  ucSubIndex;  //sub index
        ELMO_UINT8  ucService;   //// 1 - Download, 2 - Upload
        ELMO_UINT8  ucDataLength;//actual length
}MMC_SENDSDOEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SENDSDOEX_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
//@IR - 13.09.17 - Added EC 8+ bytes SDO support.
typedef struct mmc_sendsdoex_out
{

        //data
        SEND_SDO_DATA_EX uData;

        //Reserve
        int32_t     pReserve[10];

        ELMO_UINT16 usStatus;
        ELMO_UINT16 usErrorID;
        ELMO_UINT8  ucDataLength;//actual length
}MMC_SENDSDOEX_OUT;


typedef struct
{
    ELMO_UINT8 ucParam;
}MMC_GENERALPARAMPDOREAD_IN;


typedef struct 
    {
        ELMO_UINT64  ulliVal;
        ELMO_UINT16  usStatus;
        ELMO_INT16   usErrorID;
    }MMC_GENERALPARAMPDOREAD_OUT;


typedef union _unGeneralPDOWriteData
        {
                ELMO_UINT8  pData[8];
                ELMO_UINT64 ulliVal;
        }unGeneralPDOWriteData;

typedef struct
{
    unGeneralPDOWriteData   DataUnion;
    ELMO_UINT8              ucParam;
}MMC_GENERALPARAMPDOWRITE_IN;

typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_GENERALPARAMPDOWRITE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SENDCMD_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT8 pCmd[80];
}MMC_SENDCMD_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SENDCMD_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_SENDCMD_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETSYNCTIME_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usSYNCTime;
}MMC_SETSYNCTIME_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETSYNCTIME_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_SETSYNCTIME_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETSYNCTIME_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  dummy;
}MMC_GETSYNCTIME_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETSYNCTIME_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usSYNCTime;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_GETSYNCTIME_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CHANGEMOTIONMODE_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  ucMotionMode;
}MMC_CHANGEMOTIONMODE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETAXISREFFROMCANID_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  ucNodeID;
}MMC_GETAXISREFFROMCANID_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETAXISREFFROMCANID_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usAxisRef;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_GETAXISREFFROMCANID_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CHANGEMOTIONMODE_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CHANGEMOTIONMODE_OUT;

typedef struct
{
    ELMO_UINT16 usCOB_ID;
    ELMO_UINT8  ucLength;
    ELMO_UINT8  pData[8];
}MMC_SENDRAWDATA_IN;

typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_SENDRAWDATA_OUT;

typedef struct
{
    ELMO_UINT16 usFunctionID ;
    ELMO_UINT16 usNumerator;
    ELMO_UINT16 usDatasize;
    ELMO_UINT16 usPadding    ;
    ELMO_UINT16 usStatus ;
    ELMO_INT16  usErrorid ;
    ELMO_UINT16 usCOB_ID;
    ELMO_UINT16 usAxisRef;
    ELMO_UINT8  can_data_length;
    ELMO_UINT8  data[8] ;
    ELMO_UINT8  ucAsyncEventType;
}MMC_CAN_REPLY_DATA_OUT;

//@IR - 13.09.17 - Added EC 8+ bytes SDO support.
typedef struct
{
        ELMO_UINT16 usFunctionID;
        ELMO_UINT16 usNumerator;
        ELMO_UINT16 usDatasize;
        ELMO_UINT16 usPadding;
        ELMO_UINT16 usStatus;
        ELMO_INT16  usErrorid;
        ELMO_UINT16 usCOB_ID;
        ELMO_UINT16 usAxisRef;
        ELMO_UINT8  can_data_length;
        ELMO_UINT8  data[8];
        ELMO_UINT8  ucAsyncEventType;
        ELMO_UINT8  dataEx[NODE_ASCII_ARRAY_MAX_LENGTH];
}MMC_CAN_REPLY_DATA_EX_OUT;
///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETCOMMSTATISTICS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usAxesRef/*usSlaveID*/;
}MMC_GETCOMMSTATISTICS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETCOMMSTATISTICS_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    uint32_t        dwSendErrors;
    uint32_t        dwReceiveErrors;
    uint32_t        dwWrongWC;
    uint32_t        dwParseErrors;
    ELMO_UINT16     usNumOfSlaves;
    ELMO_UINT16     usStatus;
    ELMO_INT16      usErrorID;
    ELMO_UINT8      ucMasterState;
    ELMO_UINT8      ucSlaveState;
}MMC_GETCOMMSTATISTICS_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESETCOMMSTATISTICS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 dummy;
}MMC_RESETCOMMSTATISTICS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESETCOMMSTATISTICS_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_RESETCOMMSTATISTICS_OUT;

typedef struct
{
    ELMO_UINT32 uiHeartbeatTimeFactor;
}MMC_SETHEARTBEATCONSUMER_IN;

typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_SETHEARTBEATCONSUMER_OUT;


typedef struct
{
    ELMO_UINT8  ucLength;
    ELMO_UINT8  pData[NODE_ASCII_ARRAY_MAX_LENGTH];
}MMC_INTERPEXECUTECMD_IN;

typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_INTERPEXECUTECMD_OUT;


/* ****************************** */
/*   APIs added at 10.11.2010     */
/* ****************************** */

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGEVENTMODEPDO3_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  ucPDOEventMode;
}MMC_CONFIGEVENTMODEPDO3_IN;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGEVENTMODEPDO3_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CONFIGEVENTMODEPDO3_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGEVENTMODEPDO4_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  ucPDOEventMode;
}MMC_CONFIGEVENTMODEPDO4_IN;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CONFIGEVENTMODEPDO4_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CONFIGEVENTMODEPDO4_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETCOMMDIAGNOSTICS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  ucDummy;
}MMC_GETCOMMDIAGNOSTICS_IN;



typedef struct
{
    ELMO_UINT8  ucRXErrorsPort0;
    ELMO_UINT8  ucInvalidFramesPort0;
    ELMO_UINT8  ucLostLinkErrorsPort0;
    ELMO_UINT8  ucRXErrorsPort1;
    ELMO_UINT8  ucInvalidFramesPort1;
    ELMO_UINT8  ucLostLinkErrorsPort1;
    ELMO_UINT8  ucRXErrorsPort2;
    ELMO_UINT8  ucInvalidFramesPort2;
    ELMO_UINT8  ucLostLinkErrorsPort2;
    ELMO_UINT8  ucRXErrorsPort3;
    ELMO_UINT8  ucInvalidFramesPort3;
    ELMO_UINT8  ucLostLinkErrorsPort3;
}MMC_ETHERCAT_DIAGNOSTICS_INFO;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETCOMMDIAGNOSTICS_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16                     usStatus;
    ELMO_INT16                      usErrorID;
    MMC_ETHERCAT_DIAGNOSTICS_INFO   pDiagnosticsSlavesArr[ETHERCAT_ID_MAX];
}MMC_GETCOMMDIAGNOSTICS_OUT;
///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETCOMMDIAGNOSTICS_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
        ELMO_UINT16                     usStatus;
        ELMO_UINT16                     usErrorID;
        ELMO_UINT16                     usMainSlaveCount;
        ELMO_UINT16                     usRedundancySlaveCount;
        ELMO_UINT16                     usNetworkState;
        MMC_ETHERCAT_DIAGNOSTICS_INFO   pDiagnosticsSlavesArr[ETHERCAT_ID_MAX];
    	uint32_t ulSpare[50];
}MMC_GETCOMMDIAGNOSTICSEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESETCOMMDIAGNOSTICS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  ucDummy;
}MMC_RESETCOMMDIAGNOSTICS_IN;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESETCOMMDIAGNOSTICS_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_RESETCOMMDIAGNOSTICS_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETREACTORSTATISTICS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  ucDummy;
}MMC_GETREACTORSTATISTICS_IN;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETREACTORSTATISTICS_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32  iReactorQueueSize;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_GETREACTORSTATISTICS_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_ENABLECOMMGATEWAY_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  ucDummy;
}MMC_ENABLE_ECATCONFIGMODE_IN;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_ENABLECOMMGATEWAY_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_ENABLE_ECATCONFIGMODE_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_DISABLECOMMGATEWAY_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  ucDummy;
}MMC_DISABLE_ECATCONFIGMODE_IN;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_DISABLECOMMGATEWAY_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_DISABLE_ECATCONFIGMODE_OUT;

typedef struct 
{
    ELMO_UINT8  ucDummy;
}MMC_IS_ECATCONFIGMODE_IN;


typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
    ELMO_UINT8  ucResult;
}MMC_IS_ECATCONFIGMODE_OUT;

typedef struct  mmc_configpdocommparam_in
{
    ELMO_UINT8  ucPDONum;         // 1 -4.
    ELMO_UINT8  ucPDODir;         // 0 RXPDO. 1 TXPDO
    ELMO_UINT8  ucPDOCommParam;   // 1. OnSync. 255. On Event (ASYNCHRONOUS).
}MMC_CONFIGPDOCOMMPARAM_IN;

typedef struct mmc_configpdocommparam_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CONFIGPDOCOMMPARAM_OUT;

typedef struct mmc_configvirtualencoder_in
{
    ELMO_DOUBLE dbLowPos;
    ELMO_DOUBLE dbHighPos;
    ELMO_FLOAT  fFactor;
    ELMO_UINT8  ucMode;
    ELMO_UINT8  ucGroupID;
}MMC_CONFIGVIRTUALENCODER_IN;

typedef struct mmc_configvirtualencoder_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CONFIGVIRTUALENCODER_OUT;

typedef struct mmc_cancelvirtualencoder_in
{
    ELMO_UINT8  ucDummy;
}MMC_CANCELVIRTUALENCODER_IN;

typedef struct mmc_cancelvirtualencoder_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CANCELVIRTUALENCODER_OUT;
typedef struct mmc_startbulkupload_in
{
    ELMO_UINT16 usIndex;
    ELMO_UINT8  ucSubIndex;
} MMC_STARTBULKUPLOAD_IN;

typedef struct mmc_startbulkupload_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
} MMC_STARTBULKUPLOAD_OUT;

typedef struct mmc_getbulkuploadstatus_in
{
    ELMO_UINT8  ucDummy;
} MMC_GETBULKUPLOADSTATUS_IN;

typedef struct mmc_getbulkuploadstatus_out
{
    ELMO_UINT32 uiSizeCompleted;
    uint32_t    ulSizeReported;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
    ELMO_INT16  usCommError;
    ELMO_INT16  usUploadError;
    ELMO_UINT8  ucUploadState;
} MMC_GETBULKUPLOADSTATUS_OUT;

typedef struct mmc_getbulkuploaddata_in
{
    uint32_t    ulStartIndex;
    uint32_t    ulEndIndex;
} MMC_GETBULKUPLOADDATA_IN;

typedef struct mmc_getbulkuploaddata_out
{
    ELMO_UINT16 usStatus;
    ELMO_UINT16 usErrorID;
    ELMO_INT8   cDataBuffer[NC_MAX_REC_PACKET_SIZE];
} MMC_GETBULKUPLOADDATA_OUT;
typedef struct mmc_getslavescanalias_in
{
        ELMO_UINT8 ucDummy;
} MMC_GETSLAVESCANALIAS_IN;

typedef struct mmc_getslavescanalias_out
{
        ELMO_UINT16 usStatus;
        ELMO_INT16  sErrorID;
        ELMO_UINT16 usNumberOfAlias;
        ELMO_UINT16  usScanAlias[256];
        ELMO_UINT16  usScanAliasIndex[256];
        ELMO_UINT8  ucSpare[256];
} MMC_GETSLAVESCANALIAS_OUT;

typedef struct mmc_getslavesdiagnostics_in
{
        ELMO_UINT8 ucDummy;
} MMC_GETSLAVEDIAGNOSTICS_IN;

typedef struct mmc_getslavesdiagnostics_out
{
        ELMO_UINT16 usStatus;
        ELMO_INT16  sErrorID;
        ELMO_UINT8  ucSlaveState[256];
        ELMO_UINT8  ucSpare[512];
} MMC_GETSLAVEDIAGNOSTICS_OUT;
/// functions

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetSyncTimeCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_GETSYNCTIME_IN* pInParam,
///             OUT MMC_GETSYNCTIME_OUT* pOutParam)
/// \brief The function returns the SYNC time, in case of CAN communication.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Get Sync Time input parameters
/// \param  pOutParam - [OUT] Pointer to Get Sync Time output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetSyncTimeCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_GETSYNCTIME_IN* pInParam,
        OUT MMC_GETSYNCTIME_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CfgRegParamEvPDO3Cmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_CONFIGREGULARPARAMEVENTPDO3_IN* pInParam,
///             OUT MMC_CONFIGREGULARPARAMEVENTPDO3_OUT* pOutParam)
/// \brief The function configures regular parameter event PDO3 according group type.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Configure Regular Parameter Event PDO3 input parameters
/// \param  pOutParam - [OUT] Pointer to Configure Regular Parameter Event PDO3 output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_CfgRegParamEvPDO3Cmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_CONFIGREGULARPARAMEVENTPDO3_IN* pInParam,
        OUT MMC_CONFIGREGULARPARAMEVENTPDO3_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CfgRegParamEvPDO4Cmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_CONFIGREGULARPARAMEVENTPDO4_IN* pInParam,
///             OUT MMC_CONFIGREGULARPARAMEVENTPDO4_OUT* pOutParam)
/// \brief The function configures regular parameter event PDO4 according group type.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Configure Regular Parameter Event PDO4 input parameters
/// \param  pOutParam - [OUT] Pointer to Configure Regular Parameter Event PDO4 output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_CfgRegParamEvPDO4Cmd(
        IN MMC_CONNECT_HNDL                     hConn,
        IN MMC_AXIS_REF_HNDL                    hAxisRef,
        IN MMC_CONFIGREGULARPARAMEVENTPDO4_IN*  pInParam,
        OUT MMC_CONFIGREGULARPARAMEVENTPDO4_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CfgUserParamEvPDO3Cmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_CONFIGUSERPARAMEVENTPDO3_IN* pInParam,
///             OUT MMC_CONFIGUSERPARAMEVENTPDO3_OUT* pOutParam)
/// \brief The function configures user parameter event PDO3 according group type.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Configure User Parameter Event PDO3 input parameters
/// \param  pOutParam - [OUT] Pointer to Configure User Parameter Event PDO3 output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_CfgUserParamEvPDO3Cmd(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_CONFIGUSERPARAMEVENTPDO3_IN* pInParam,
        OUT MMC_CONFIGUSERPARAMEVENTPDO3_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CfgUserParamEvPDO4Cmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_CONFIUSERPARAMEVENTPDO4_IN* pInParam,
///             OUT MMC_CONFIGUSERPARAMEVENTPDO4_OUT* pOutParam)
/// \brief The function configures user parameter event PDO4 according group type.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Configure User Parameter Event PDO4 input parameters
/// \param  pOutParam - [OUT] Pointer to Configure User Parameter Event PDO4 output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_CfgUserParamEvPDO4Cmd(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_CONFIGUSERPARAMEVENTPDO4_IN* pInParam,
        OUT MMC_CONFIGUSERPARAMEVENTPDO4_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CancelParamEvPDO3Cmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_CANCELPARAMEVENTPDO3_IN* pInParam,
///             OUT MMC_CANCELPARAMEVENTPDO3_OUT* pOutParam)
/// \brief The function cancels TPDO3 event processing.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Cancel PDO3 Event Processing input parameters
/// \param  pOutParam - [OUT] Pointer to Cancel PDO3 Event Processing output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_CancelParamEvPDO3Cmd(
        IN MMC_CONNECT_HNDL             hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        IN MMC_CANCELPARAMEVENTPDO3_IN* pInParam,
        OUT MMC_CANCELPARAMEVENTPDO3_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CancelParamEvPDO4Cmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_CANCELPARAMEVENTPDO4_IN* pInParam,
///             OUT MMC_CANCELRPARAMEVENTPDO4_OUT* pOutParam)
/// \brief The function cancels TPDO4 event processing.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Cancel PDO4 Event Processing input parameters
/// \param  pOutParam - [OUT] Pointer to Cancel PDO4 Event Processing output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_CancelParamEvPDO4Cmd(
        IN MMC_CONNECT_HNDL             hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        IN MMC_CANCELPARAMEVENTPDO4_IN* pInParam,
        OUT MMC_CANCELPARAMEVENTPDO4_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetPDOInfoCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_GETPDOINFO_IN* pInParam,
///             OUT MMC_GETPDOINFO_OUT* pOutParam)
/// \brief The function return information about PDO 3\4.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to input parameters
/// \param  pOutParam - [OUT] Pointer to output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetPDOInfoCmd(
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_AXIS_REF_HNDL        hAxisRef,
        IN MMC_GETPDOINFO_IN*       pInParam,
        OUT MMC_GETPDOINFO_OUT*     pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ChngOpMode (
///
///
/// \brief      This function changes motion mode between NC/Non NC
/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ChngOpMode(
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_AXIS_REF_HNDL        hAxisRef,
        IN MMC_CHANGEMOTIONMODE_IN* pInParam,
        OUT MMC_CHANGEMOTIONMODE_OUT*   pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_SendCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_SENDCMD_IN* pInParam,
///             OUT MMC_SENDCMD_OUT* pOutParam)
/// \brief The function sends a command string to the DRIVE.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Send CMD input parameters
/// \param  pOutParam - [OUT] Pointer to Send CMD output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SendCmd(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_SENDCMD_IN*      pInParam,
        OUT MMC_SENDCMD_OUT*    pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_SendSdoCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_SENDSDO_IN* pInParam,
///             OUT MMC_SENDSDO_OUT* pOutParam)
/// \brief This function send SDO message command.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Send SDO input parameters
/// \param  pOutParam - [OUT] Pointer to Send SDO output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SendSdoCmd(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_SENDSDO_IN*      pInParam,
        OUT MMC_SENDSDO_OUT*    pOutParam);


////////////////////////////////////////////////////////////////////////////////
////   MMC_LIB_API int MMC_SendSdoAsyncCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_SENDSDO_IN* pInParam,
///             OUT MMC_SENDSDO_OUT* pOutParam)
/// \brief This function send SDO message command.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Send SDO input parameters
/// \param  pOutParam - [OUT] Pointer to Send SDO output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SendSdoAsyncCmd(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_SENDSDO_IN*      pInParam,
        OUT MMC_SENDSDO_OUT*    pOutParam);

////////////////////////////////////////////////////////////////////////////////
//// MMC_LIB_API int MMC_RetrieveSdoAsyncCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_SENDSDO_IN* pInParam,
///             OUT MMC_SENDSDO_OUT* pOutParam)
/// \brief This function send SDO message command.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Send SDO input parameters
/// \param  pOutParam - [OUT] Pointer to Send SDO output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_RetrieveSdoAsyncCmd(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        OUT MMC_SENDSDO_OUT*    pOutParam);
                
////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_SendSdoExCmd(
///                             IN MMC_CONNECT_HNDL hConn,
///                             IN MMC_AXIS_REF_HNDL hAxisRef,
///                             IN MMC_SENDSDOEX_IN* pInParam,
///                             OUT MMC_SENDSDOEX_OUT* pOutParam)
/// \brief This function send SDO message command with up to 80 bytes size.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Send SDO input parameters
/// \param  pOutParam - [OUT] Pointer to Send SDO output parameters
/// \return     return - 0 if success
///                              error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SendSdoExCmd(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_SENDSDOEX_IN*    pInParam,
        OUT MMC_SENDSDOEX_OUT*  pOutParam);

////////////////////////////////////////////////////////////////////////////////
////   MMC_LIB_API int MMC_SendSdoAsyncExCmd(
///                             IN MMC_CONNECT_HNDL hConn,
///                             IN MMC_AXIS_REF_HNDL hAxisRef,
///                             IN MMC_SENDSDOEX_IN* pInParam,
///                             OUT MMC_SENDSDOEX_OUT* pOutParam)
/// \brief This function send SDO message command 80 bytes.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Send SDO input parameters
/// \param  pOutParam - [OUT] Pointer to Send SDO output parameters
/// \return     return - 0 if success
///                              error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SendSdoAsyncExCmd(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_SENDSDOEX_IN*    pInParam,
        OUT MMC_SENDSDOEX_OUT*  pOutParam);

////////////////////////////////////////////////////////////////////////////////
//// MMC_LIB_API int MMC_RetrieveSdoAsyncExCmd(
///                             IN MMC_CONNECT_HNDL hConn,
///                             IN MMC_AXIS_REF_HNDL hAxisRef,
///                             IN MMC_SENDSDOEX_IN* pInParam,
///                             OUT MMC_SENDSDOEX_OUT* pOutParam)
/// \brief This function send SDO message command 80 bytes.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Send SDO input parameters
/// \param  pOutParam - [OUT] Pointer to Send SDO output parameters
/// \return     return - 0 if success
///                              error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_RetrieveSdoAsyncExCmd(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_SENDSDOEX_IN*    pInParam,
        OUT MMC_SENDSDOEX_OUT*  pOutParam);
////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_PDOGeneralReadCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_GENERALPARAMPDOREAD_IN* pInParam,
///             OUT MMC_GENERALPARAMPDOREAD_OUT* pOutParam)
/// \brief This function send SDO message command.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to MMC_PDOGeneralReadCmd input parameters
/// \param  pOutParam - [OUT] Pointer to MMC_PDOGeneralReadCmd output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_PDOGeneralReadCmd(
        IN MMC_CONNECT_HNDL             hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        IN MMC_GENERALPARAMPDOREAD_IN*  pInParam,
        OUT MMC_GENERALPARAMPDOREAD_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_PDOGeneralWriteCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_GENERALPARAMPDOWRITE_IN* pInParam,
///             OUT MMC_GENERALPARAMPDOWRITE_OUT* pOutParam)
/// \brief This function send SDO message command.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to MMC_PDOGeneralWriteCmd input parameters
/// \param  pOutParam - [OUT] Pointer to MMC_PDOGeneralWriteCmd output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_PDOGeneralWriteCmd(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_GENERALPARAMPDOWRITE_IN*     pInParam,
        OUT MMC_GENERALPARAMPDOWRITE_OUT*   pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetSyncTimeCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_SETSYNCTIME_IN* pInParam,
///             OUT MMC_SETSYNCTIME_OUT* pOutParam)
/// \brief The function sets the SYNC time in the communication module, updates
///     relevant nodes which their motion - mode is IP and update kernel with SYNC
///     time, in case we are in CAN communication.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Set Sync Time input parameters
/// \param  pOutParam - [OUT] Pointer to Set Sync Time output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SetSyncTimeCmd(
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_SETSYNCTIME_IN*      pInParam,
        OUT MMC_SETSYNCTIME_OUT*    pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SendandReceiveCANRawData (
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_SENDRAWDATA_IN * pInParam
///             OUT MMC_CAN_REPLY_DATA_OUT* pOutParam)
/// \brief      This function sends prepared CANOpen data (DS301 or DS402) via PDO2
/// \param  hConn - [IN] Connection handle.
/// \param  pOutParam - [OUT] Immediate status error.
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SendandReceiveCANRawData (
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_AXIS_REF_HNDL        hAxisRef,
        IN  MMC_SENDRAWDATA_IN *    pInParam,
        OUT MMC_CAN_REPLY_DATA_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SendCANRawData (
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_SENDRAWDATA_IN  * pInParam
///             OUT MMC_SENDRAWDATA_OUT* pOutParam)
/// \brief      This function sends prepared CANOpen RAW data (DS301 or DS402)
/// \param  hConn - [IN] Connection handle.
/// \param  pOutParam - [OUT] Immediate status error.
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SendCANRawData (
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_AXIS_REF_HNDL        hAxisRef,
        IN  MMC_SENDRAWDATA_IN *    pInParam,
        OUT MMC_SENDRAWDATA_OUT*    pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReceiveCANRawData (
///             IN MMC_CONNECT_HNDL hConn,
///             OUT MMC_CAN_REPLY_DATA_OUT* pOutParam)
/// \brief      This function receives prepared CANOpen RAW data (DS301 or DS402)
/// \param  hConn - [IN] Connection handle.
/// \param  iTimeOutms- [IN] Time to wait.
/// \param  pOutParam - [OUT] Immediate status error.
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReceiveCANRawData (
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_AXIS_REF_HNDL        hAxisRef,
        IN ELMO_UINT16              iTimeOutms,
        OUT MMC_CAN_REPLY_DATA_OUT* pOutParam) ;


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetAxisByCanIdCmd (
///             IN MMC_CONNECT_HNDL hConn,
///             IN  MMC_GETAXISREFFROMCANID_IN *pInParam,
///             OUT MMC_GETAXISREFFROMCANID_OUT* pOutParam)
///
/// \brief      This return Axis handle by CAN ID
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Get Axis By CAN ID input parameters
/// \param  pOutParam - [OUT] Pointer to Get Axis By CAN ID output parameters
/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetAxisByCanIdCmd (
        IN  MMC_CONNECT_HNDL                hConn,
        IN  MMC_GETAXISREFFROMCANID_IN*     pInParam,
        OUT MMC_GETAXISREFFROMCANID_OUT*    pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetCommStatistics(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             OUT MMC_GETCOMMSTATISTICS_OUT* pOutParam)
/// \brief This function receive communication statistics for specific axis..
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle
/// \param  pOutParam - [OUT] Pointer to Get Communication Statistics output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetCommStatistics(
        IN MMC_CONNECT_HNDL             hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        OUT MMC_GETCOMMSTATISTICS_OUT*  pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ResetCommStatistics(
///             IN MMC_CONNECT_HNDL hConn,
///             OUT MMC_RESETCOMMSTATISTICS_OUT* pOutParam)
/// \brief This function reset all communication statistics.
/// \param  hConn - [IN] Connection handle
/// \param  pOutParam - [OUT] Pointer to Reset Communication Statistics output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ResetCommStatistics(
        IN MMC_CONNECT_HNDL                 hConn,
        OUT MMC_RESETCOMMSTATISTICS_OUT*    pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetHeartBeatConsumerCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_SETHEARTBEATCONSUMER_IN* pInParam,
///             OUT MMC_SETHEARTBEATCONSUMER_OUT* pOutParam)
/// \brief The function sets the consumer heartbeat time for all axes in the system
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Heartbeat input parameters
/// \param  pOutParam - [OUT] Pointer to Heartbeat output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SetHeartBeatConsumerCmd(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_SETHEARTBEATCONSUMER_IN*     pInParam,
        OUT MMC_SETHEARTBEATCONSUMER_OUT*   pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoSetParameter(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN char cCmd[3],
///             IN unsigned char ucValType,
///             IN void* pVal)
/// \brief This function set parameters.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  cCmd - [IN] Command characters
/// \param  ucValType - [IN]  Data value type (integer/float)
/// \param  pVal - [IN] Pointer to data value. (max 4 bytes)
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoSetParameter(
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_AXIS_REF_HNDL        hAxisRef,
        IN ELMO_INT8                cCmd[3],
        IN ELMO_UINT8               ucValType,
        IN ELMO_PVOID                pVal);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoGetParameter(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN char cCmd[3])
/// \brief This function send get parameters request.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  cCmd - [IN] Command characters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoGetParameter(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN ELMO_INT8            cCmd[3],
        IN ELMO_UINT8           ucValType);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoGetArray(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN char cCmd[3],
///             IN short iArrayIdx)
/// \brief This function send get array element parameters request.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  cCmd - [IN] Command characters
/// \param  iArrayIdx - [IN] Index of array element
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoGetArray(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN ELMO_INT8            cCmd[3],
        IN ELMO_INT16           iArrayIdx,
        IN ELMO_UINT8           ucValType);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoSetArray(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN char cCmd[3],
///             IN short iArrayIdx
///             IN unsigned char ucValType,
///             IN unsigned char ucVal[8])
/// \brief This function set parameters.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  cCmd - [IN] Command characters
/// \param  iArrayIdx - [IN] Index of array element
/// \param  ucValType - [IN]  Data value type (integer/float)
/// \param  pVal - [IN] Pointer to data value. (max 4 bytes)
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoSetArray(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN ELMO_INT8            cCmd[3],
        IN ELMO_INT16           iArrayIdx,
        IN ELMO_UINT8           ucValType,
        IN ELMO_PVOID           pVal);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoGetParameterAndRetrieveData(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef
///             IN char cCmd[3],
///             IN unsigned char ucValType,
///             OUT void *pVal,
///             OUT unsigned int* uiErrorID)
/// \brief This function do synchronous  get parameter
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  cCmd - [IN] Command characters
/// \param  ucValType - [IN]  Data value type (integer/float)
/// \param  pVal - [OUT] Pointer to retrived data.
/// \param  uiErrorID - [OUT] returned Error Code
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoGetParameterAndRetrieveData(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN ELMO_INT8            cCmd[3],
        IN ELMO_UINT8           ucValType,
        OUT ELMO_PVOID          pVal,
        OUT ELMO_PUINT32        uiErrorID);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoGetArrayAndRetrieveData(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef
///             IN char cCmd[3],
///             IN short iArrayIdx,
///             IN unsigned char ucValType,
///             OUT void *pVal,
///             OUT unsigned int* uiErrorID)
/// \brief This function do synchronous  get array parameter
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  cCmd - [IN] Command characters
/// \param  iArrayIdx - [IN] Index of array element
/// \param  ucValType - [IN]  Data value type (integer/float)
/// \param  pVal - [OUT] Pointer to retrived data.
/// \param  uiErrorID - [OUT] returned Error Code
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoGetArrayAndRetrieveData(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN ELMO_INT8            cCmd[3],
        IN ELMO_INT16           iArrayIdx,
        IN ELMO_UINT8           ucValType,
        OUT ELMO_PVOID           pVal,
        OUT ELMO_PUINT32        uiErrorID);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoQueryOperationFIFOIndex(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             OUT int* iReceivedMsgIdx)
/// \brief This function return number received messages.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  iReceivedMsgIdx - [OUT] Returned number of received messages.
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoQueryOperationFIFOIndex(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        OUT ELMO_PINT32         iReceivedMsgIdx);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoQueryOperationFIFORetrieveData(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef
///             OUT void *pVal,
///             OUT unsigned int* uiErrorID)
/// \brief This function retrieve message data.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  pVal - [OUT] Pointer to retrived data.
/// \param  uiErrorID - [OUT] returned Error Code
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoQueryOperationFIFORetrieveData(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        OUT ELMO_PVOID          pVal,
        OUT ELMO_PUINT32        uiErrorID);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoQueryOperationFIFOIndexReset(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef)
/// \brief This function erase message FIFO.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoQueryOperationFIFOIndexReset(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoExecuteLabel(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_INTERPEXECUTECMD_IN* pInParam,
///             OUT MMC_INTERPEXECUTECMD_OUT* pOutParam)
/// \brief This function send command to execute label
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  pInParam - [IN] Pointer to Interpreter Execute Command input parameters
/// \param  pOutParam - [OUT] Pointer to Interpreter Execute Command output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoExecuteLabel(
        IN MMC_CONNECT_HNDL             hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        IN MMC_INTERPEXECUTECMD_IN*     pInParam,
        OUT MMC_INTERPEXECUTECMD_OUT*   pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ElmoCall(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN char cCmd[3])
/// \brief This function call execute command.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param  cCmd - [IN] Command characters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ElmoCall(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN ELMO_INT8            cCmd[3]);
////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_CfgEventModePDO3Cmd(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
/// \brief
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_CfgEventModePDO3Cmd(
        IN MMC_CONNECT_HNDL             hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        IN MMC_CONFIGEVENTMODEPDO3_IN*  pInParam,
        OUT MMC_CONFIGEVENTMODEPDO3_OUT* pOutParam);
////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_CfgEventModePDO4Cmd(
///             N MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
/// \brief
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle.
/// \param
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_CfgEventModePDO4Cmd(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_CONFIGEVENTMODEPDO4_IN*      pInParam,
        OUT MMC_CONFIGEVENTMODEPDO4_OUT*    pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetCommDiagnostics(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_GETCOMMDIAGNOSTICS_IN* pInParam,
///             OUT MMC_GETCOMMDIAGNOSTICS_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle
/// \param  pInParam - [IN] Pointer to MMC_GetCommDiagnostics input parameters
/// \param  pOutParam - [OUT] Pointer to MMC_GetCommDiagnostics output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetCommDiagnostics(
        IN MMC_CONNECT_HNDL             hConn,
        IN MMC_GETCOMMDIAGNOSTICS_IN*   pInParam,
        OUT MMC_GETCOMMDIAGNOSTICS_OUT* pOutParam);
                
////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetCommDiagnostics(
///                             IN MMC_CONNECT_HNDL hConn,
///                             IN MMC_GETCOMMDIAGNOSTICS_IN* pInParam,
///                             OUT MMC_GETCOMMDIAGNOSTICS_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle
/// \param  pInParam - [IN] Pointer to MMC_GetCommDiagnostics input parameters
/// \param  pOutParam - [OUT] Pointer to MMC_GetCommDiagnostics output parameters
/// \return     return - 0 if success
///                              error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetCommDiagnosticsEx(
                IN MMC_CONNECT_HNDL                 hConn,
                IN MMC_GETCOMMDIAGNOSTICS_IN*       pInParam,
                OUT MMC_GETCOMMDIAGNOSTICSEX_OUT*   pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ResetCommDiagnostics(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_RESETCOMMDIAGNOSTICS_IN* pInParam,
///             OUT MMC_RESETCOMMDIAGNOSTICS_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to MMC_ResetCommDiagnostics input parameters
/// \param  pOutParam - [OUT] Pointer to MMC_ResetCommDiagnostics output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ResetCommDiagnostics(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_RESETCOMMDIAGNOSTICS_IN*     pInParam,
        OUT MMC_RESETCOMMDIAGNOSTICS_OUT*   pOutParam);
////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetReactorStatistics(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_GETREACTORSTATISTICS_IN* pInParam,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             OUT MMC_GETREACTORSTATISTICS_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis/Group Reference handle
/// \param  pInParam - [IN] Pointer to MMC_GetReactorStatistics input parameters
/// \param  pOutParam - [OUT] Pointer to Get Reactor Statistics output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetReactorStatistics(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_GETREACTORSTATISTICS_IN*     pInParam,
        OUT MMC_GETREACTORSTATISTICS_OUT*   pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_EnableEthercatConfigMode(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_ENABLECOMMGATEWAY_IN* pInParam,
///             OUT MMC_ENABLECOMMGATEWAY_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
/// \param  pOutParam - [OUT] Pointer to MMC_EnableCommGateway output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_EnableEthercatConfigMode(
        IN MMC_CONNECT_HNDL                 hConn,
        OUT MMC_ENABLE_ECATCONFIGMODE_OUT*  pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_DisableEthercatConfigMode(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_DISABLECOMMGATEWAY_IN* pInParam,
///             OUT MMC_DISABLECOMMGATEWAY_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to MMC_DisableCommGateway input parameters
/// \param  pOutParam - [OUT] Pointer to MMC_DisableCommGateway output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_DisableEthercatConfigMode(
        IN MMC_CONNECT_HNDL                 hConn,
        OUT MMC_DISABLE_ECATCONFIGMODE_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_IsEthercatConfigMode(
///             IN MMC_CONNECT_HNDL hConn,
///             OUT MMC_IS_ECATCONFIGMODE_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
/// \param  pOutParam - [OUT] Pointer to MMC_IsEthercatConfigMode output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_IsEthercatConfigMode(
        IN MMC_CONNECT_HNDL             hConn,
        OUT MMC_IS_ECATCONFIGMODE_OUT*  pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_ChangeDefaultPDOConfiguration(
///             IN MMC_CONNECT_HNDL hConn,
///             OUT MMC_IS_ECATCONFIGMODE_OUT* pOutParam)
/// \brief
/// \param  hConn -     [IN]    Connection handle
/// \param  pInParam -  [IN]    Pointer to MMC_ChangeDefaultPDOConfiguration input parameters
/// \param  pOutParam - [OUT]   Pointer to MMC_ChangeDefaultPDOConfiguration output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ChangeDefaultPDOConfiguration(
        IN  MMC_CONNECT_HNDL            hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        IN  MMC_CONFIGPDOCOMMPARAM_IN*  pInParam, 
        OUT MMC_CONFIGPDOCOMMPARAM_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ConfigVirtualEncoder(IN MMC_CONNECT_HNDL hConn,
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,IN MMC_CONFIGVIRTUALENCODER_IN* pInParam,
//              OUT MMC_CONFIGVIRTUALENCODER_OUT *pOutParam)
/// \brief
/// \param  hConn -     [IN]    Connection handle
/// \param  pInParam -  [IN]    Pointer to MMC_ConfigVirtualEncoder input parameters
/// \param  pOutParam - [OUT]   Pointer to MMC_ConfigVirtualEncoder output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ConfigVirtualEncoder(IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_CONFIGVIRTUALENCODER_IN*     pInParam,
        OUT MMC_CONFIGVIRTUALENCODER_OUT*   pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CancelVirtualEncoder(IN MMC_CONNECT_HNDL hConn,
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
//              OUT MMC_CONFIGVIRTUALENCODER_OUT *pOutParam)
/// \brief
/// \param  hConn -     [IN]    Connection handle
/// \param  pOutParam - [OUT]   Pointer to MMC_ConfigVirtualEncoder output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_CancelVirtualEncoder(IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        OUT MMC_CONFIGVIRTUALENCODER_OUT*   pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_StartBulkUploadCmd(IN MMC_CONNECT_HNDL hConn,
///                                IN MMC_AXIS_REF_HNDL hAxisRef,
///                                IN MMC_STARTBULKUPLOAD_IN* pInParam,
///                                OUT MMC_STARTBULKUPLOAD_OUT *pOutParam)
/// \brief
/// \param  hConn -     [IN]    Connection handle
/// \param  hAxisRef -  [IN]    Axis Reference
/// \param  pInParam -  [IN]    Pointer to MMC_StartBulkUpload input parameters
/// \param  pOutParam - [OUT]   Pointer to MMC_StartBulkUpload output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_StartBulkUploadCmd(IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        IN MMC_STARTBULKUPLOAD_IN*      pInParam,
        OUT MMC_STARTBULKUPLOAD_OUT*    pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetBulkUploadStatusCmd(IN MMC_CONNECT_HNDL hConn,
///                                    IN MMC_AXIS_REF_HNDL hAxisRef,
///                                    IN MMC_GETTBULKUPLOADSTATUS_IN* pInParam,
///                                    OUT MMC_GETBULKUPLOADSTATUS_OUT *pOutParam)
/// \brief
/// \param  hConn -     [IN]    Connection handle
/// \param  hAxisRef -  [IN]    Axis Reference
/// \param  pInParam -  [IN]    Pointer to MMC_GetBulkUploadStatus input parameters
/// \param  pOutParam - [OUT]   Pointer to MMC_GetBulkUploadStatus output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetBulkUploadStatusCmd(IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        IN MMC_GETBULKUPLOADSTATUS_IN*  pInParam,
        OUT MMC_GETBULKUPLOADSTATUS_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetBulkUploadDataCmd(IN MMC_CONNECT_HNDL hConn,
///                                  IN MMC_AXIS_REF_HNDL hAxisRef,
///                                  IN MMC_GETBULKUPLOADDATA_IN* pInParam,
///                                  OUT MMC_GETBULKUPLOADDATA_OUT *pOutParam)
/// \brief
/// \param  hConn -     [IN]    Connection handle
/// \param  hAxisRef -  [IN]    Axis Reference
/// \param  pInParam -  [IN]    Pointer to MMC_GetBulkUploadData input parameters
/// \param  pOutParam - [OUT]   Pointer to MMC_GetBulkUploadData output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetBulkUploadDataCmd(IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL            hAxisRef,
        IN MMC_GETBULKUPLOADDATA_IN*    pInParam,
        OUT MMC_GETBULKUPLOADDATA_OUT*  pOutParam);
////////////////////////////////////////////////////////////////////////////////
/// \fn unsigned int GetSlaveScanAlias(
///                             IN MMC_CONNECT_HNDL hConn)
/// \brief return alias of scan slave.
/// \param
/// \return     return - 0 if success
///                              error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 GetSlaveScanAlias(MMC_CONNECT_HNDL hConn,IN MMC_GETSLAVESCANALIAS_IN* pInParam,MMC_GETSLAVESCANALIAS_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn unsigned int GetEcatSlaveDiagnostic(
///                             IN MMC_CONNECT_HNDL hConn)
/// \brief return ECAT slaves diagnostics.
/// \param
/// \return
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 GetEcatSlaveDiagnostic(MMC_CONNECT_HNDL hConn,IN MMC_GETSLAVEDIAGNOSTICS_IN* pInParam,MMC_GETSLAVEDIAGNOSTICS_OUT* pOutParam);
//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif

#endif /* MMC_DRIVE_COMM_API_H_ */

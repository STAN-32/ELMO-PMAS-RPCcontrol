////////////////////////////////////////////////////////////////////////////////
/// \file MMC_events_API.h
/// Name        : MMC_events_API.h
/// Author      : Barak R
/// Created on  : April 19, 20010
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.2.2 Updated 16Nov2020 Haim H. Add define for AMS events
///               0.4.3 Updated 20Apr2021 Haim H. Updates according to update in "Gen C lib in Plastic"
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_EVENTS_API_H_
#define MMC_EVENTS_API_H_

//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif

#define  ASYNC_REPLY_EVT        0
#define  DOWNLOAD_FW_EVT        4
#define  EMCY_EVT               5
#define  MOTIONENDED_EVT        6
#define  HBEAT_EVT              7
#define  PDORCV_EVT             8
#define  DRVERROR_EVT           9
#define  EMIT_EVT               10
#define  HOME_ENDED_EVT         11
#define  SYSTEMERROR_EVT        12
#define  MODBUS_WRITE_EVT       13
#define  TOUCH_PROBE_ENDED_EVT  14
#define  NODE_ERROR_EVT         15
#define  STOP_ON_LIMIT_EVT      16
#define  TABLE_UNDERFLOW_EVT    17
#define  NODE_CONNECTED_EVT     18
#define  GLOBAL_ASYNC_REPLY_EVT 19
#define  NODE_INIT_FINISHED_EVT 20
#define  FB_NOTIFICATION_EVT    21
#define  POLICY_ENDED_EVT       22

									/* Events using in CodeSys IEC. On IEC they are handleling similar 	*/
									/* to "Move Event". This Events are Syntectic Generating in AMS/ADS */
									/* IEC's modules (Beckhoff comm. protocol).							*/
									/* Meaning: Remote Client Send Data to Maestro (=AMS Server)		*/
#define  AMS_ClientReqWrite_TCP_EVT	70
#define  AMS_ClientReqRead_TCP_EVT	71
#define  AMS_ClientReqWrite_UDP_EVT	72
#define  AMS_ClientReqRead_UDP_EVT	73



 // Global (not axis related) ASYNC Events
 enum
 {
    eGLOBAL_SET_HEARTBEAT,
    eGLOBAL_SET_SYNC,
    eGLOBAL_GMAS_INIT,
    eGLOBAL_SYS_RESET,
 };

 // ASYNC_REPLY_EVT (axis related) specific events enumerators
 enum
 {
     eASYNC_EVENT_SDO_DOWNLOAD = 1,
     eASYNC_EVENT_SDO_UPLOAD,
     eASYNC_EVENT_CHANGE_MOTION_MODE,
     eASYNC_EVENT_INTERP_CMD_GET,
     eASYNC_EVENT_READ_DI_GROUP,
     eASYNC_EVENT_WRITE_DO_GROUP,
     eASYNC_EVENT_CONFIG_REG_PARAM_EVENT_PDO3,
     eASYNC_EVENT_CONFIG_REG_PARAM_EVENT_PDO4,
     eASYNC_EVENT_CONFIG_USER_PARAM_EVENT_PDO3,
     eASYNC_EVENT_CONFIG_USER_PARAM_EVENT_PDO4,
     eASYNC_EVENT_CANCEL_PARAM_EVENT_PDO3,
     eASYNC_EVENT_CANCEL_PARAM_EVENT_PDO4,
     eASYNC_EVENT_RESET,
     eASYNC_EVENT_INTERP_CMD_SET,
     eASYNC_EVENT_SEND_RAW_DATA,
     eASYNC_EVENT_EXECUTE_LABEL,
     eASYNC_EVENT_CONFIG_PDO_COMM_PARAM,
     eASYNC_EVENT_CONFIG_VIRTUAL_ENC,
     eASYNC_EVENT_BULK_UPLOAD,
     eASYNC_EVENT_SDO_DOWNLOAD_MOTION_PROCESS,
     eASYNC_EVENT_SDO_UPLOAD_MOTION_PROCESS,
 };

 enum
 {
    ePOLICY_STATE_DETECTED      = 1,
    ePOLICY_STATE_STOP          = 2,
    ePOLICY_STATE_POWER         = 3,
    ePOLICY_STATE_SAFEOP        = 4,
    ePOLICY_STATE_HNDLED        = 5
 };

 enum
 {
     eNODE_POLICY_TYPE          = 0,
     eSYS_POLICY_TYPE           = 1,
 };

 enum
 {
    eNODE_ERR_FAULT_BIT         = 0x1,
    eNODE_ERR_HEARTBEAT         = 0x2,
    eNODE_ERR_EMCY              = 0x4,
    eNODE_ERR_COMM              = 0x8,
    eNODE_ERR_CFG_FILE          = 0x10,
    eNODE_ERR_AXIS_FAULT        = 0x20,
    eNODE_ERR_AL_ERROR          = 0x40,
    eNODE_ERR_UNEXPECTED_SW     = 0x80
 };

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETEVENTSMASK_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32 iEventsMask;
}MMC_SETEVENTSMASK_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETEVENTSMASK_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_SETEVENTSMASK_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CLEAREVENTSMASK_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32  iEventsMask;
}MMC_CLEAREVENTSMASK_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CLEAREVENTSMASK_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_CLEAREVENTSMASK_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETEVENTSMASK_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  dummy;
}MMC_GETEVENTSMASK_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETEVENTSMASK_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32  iEventsMask;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_GETEVENTSMASK_OUT;
//
///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_ENABLEMOTIONENDEDEVENT_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  dummy;
}MMC_ENABLEMOTIONENDEDEVENT_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_ENABLEMOTIONENDEDEVENT_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_ENABLEMOTIONENDEDEVENT_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_DISABLEMOTIONENDEDEVENT_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  dummy;
}MMC_DISABLEMOTIONENDEDEVENT_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_DISABLEMOTIONENDEDEVENT_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_DISABLEMOTIONENDEDEVENT_OUT;

typedef struct mmc_insnotificationfb_in
{
    ELMO_INT32                      iEventCode;
    ELMO_UINT16                     usNotifyOnCondition;
    ELMO_UINT16                     usSourceAxisRefernce;
    ELMO_INT32                      iParameterID;
    ELMO_INT32                      iParameterIndex;
    ELMO_DOUBLE                     dbReferenceValue;
    MC_CONDITIONFB_OPERATION_TYPE   eOperationType;
    int32_t		                    lSpare[2];
}MMC_INSNOTIFICATIONFB_IN;

typedef struct mmc_insnotificationfb_out
{
    ELMO_UINT32 uiHndl;
    ELMO_UINT16 usStatus;    ///< Returned command status.
    ELMO_INT16  usErrorID;        ///< Returned command error ID.
}MMC_INSNOTIFICATIONFB_OUT;
////// functions

// Events Enumeration to be sent in SetEventsMask and OpenUDPChannel:

enum
{
    eEVENT_TYPE_COMM_ASYNC_REPLY        = (1 << 0),
    eEVENT_TYPE_DOWNLOAD_FW             = (1 << 4),
    eEVENT_TYPE_COMM_EMGCY              = (1 << 5),
    eEVENT_TYPE_COMM_MOTION_ENDED       = (1 << 6),
    eEVENT_TYPE_COMM_HEARTBEAT_ERROR    = (1 << 7),
    eEVENT_TYPE_COMM_PDO_RECEIVED       = (1 << 8),
    eEVENT_TYPE_DRIVE_ERROR             = (1 << 9),
    eEVENT_TYPE_EMIT                    = (1 << 10),
    eEVENT_TYPE_HOME_ENDED              = (1 << 11),
    eEVENT_TYPE_SYSTEM_ERROR            = (1 << 12),
    eEVENT_TYPE_MODBUS                  = (1 << 13),
    eEVENT_TYPE_TOUCH_PROBE_ENDED       = (1 << 14),
    eEVENT_TYPE_NODE_ERROR              = (1 << 15),
    eEVENT_TYPE_STOP_ON_LIMIT           = (1 << 16),
    eEVENT_TYPE_TABLE_UNDERFLOW         = (1 << 17),
    eEVENT_TYPE_SEND_ASYNC_EVENT        = (1 << 18),
    eEVENT_TYPE_NODE_CONNECTED          = (1 << 19),
    eEVENT_TYPE_GLOBAL_ASYNC_REPLY      = (1 << 20),
    eEVENT_TYPE_NODE_INIT_FINISHED      = (1 << 21),
    eEVENT_TYPE_FB_NOTIFICATION         = (1 << 22),
    eEVENT_TYPE_NODE_POLICY             = (1 << 23)
};

typedef enum
{
    eEVENT_MODBUS_SUBTYPE_HOL_REG_PROTOCOL,
    eEVENT_MODBUS_SUBTYPE_HOL_REG_RPC_API,
    eEVENT_MODBUS_SUBTYPE_COILS_PROTOCOL,
    eEVENT_MODBUS_SUBTYPE_COILS_RPC_API
}MODBUS_SUB_TYPE;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetEventsMaskCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_SETEVENTSMASK_IN* pInParam,
///             OUT MMC_SETEVENTSMASK_OUT* pOutParam)
/// \brief The function sets the events mask for a specific connection according input mask.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Set Event Mask input parameters
/// \param  pOutParam - [OUT] Pointer to Set Event Mask output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SetEventsMaskCmd(
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_SETEVENTSMASK_IN*    pInParam,
        OUT MMC_SETEVENTSMASK_OUT*  pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ClearEventsMaskCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_CLEAREVENTSMASK_IN* pInParam,
///             OUT MMC_CLEAREVENTSMASK_OUT* pOutParam)
/// \brief The function clears the events mask for a specific connection according input mask.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Clear Event Mask input parameters
/// \param  pOutParam - [OUT] Pointer to Clear Event Mask output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ClearEventsMaskCmd(
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_CLEAREVENTSMASK_IN*  pInParam,
        OUT MMC_CLEAREVENTSMASK_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetEventsMaskCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_CLEAREVENTSMASK_IN* pInParam,
///             OUT MMC_CLEAREVENTSMASK_OUT* pOutParam)
/// \brief The function returns the events mask for a specific connection.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Get Event Mask input parameters
/// \param  pOutParam - [OUT] Pointer to Get Event Mask output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetEventsMaskCmd(
        IN MMC_CONNECT_HNDL         hConn,
        IN MMC_GETEVENTSMASK_IN*    pInParam,
        OUT MMC_GETEVENTSMASK_OUT*  pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_EnableMotionEndedEventCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_ENABLEMOTIONENDEDEVENT_IN* pInParam,
///             OUT MMC_ENABLEMOTIONENDEDEVENT_OUT* pOutParam)
/// \brief The function enables the Motion Ended event mechanism for specific Node.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Enable Motion Ended Event input parameters
/// \param  pOutParam - [OUT] Pointer to Enable Motion Ended Event output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_EnableMotionEndedEventCmd(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_ENABLEMOTIONENDEDEVENT_IN*   pInParam,
        OUT MMC_ENABLEMOTIONENDEDEVENT_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_DisableMotionEndedEventCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_DISABLEMOTIONENDEDEVENT_IN* pInParam,
///             OUT MMC_DISABLEMOTIONENDEDEVENT_OUT* pOutParam)
/// \brief The function disables the Motion Ended event mechanism for specific Node.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Disable Motion Ended Event input parameters
/// \param  pOutParam - [OUT] Pointer to Disable Motion Ended Event output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_DisableMotionEndedEventCmd(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_DISABLEMOTIONENDEDEVENT_IN*  pInParam,
        OUT MMC_DISABLEMOTIONENDEDEVENT_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_InsertNotificationFb(
        IN  MMC_CONNECT_HNDL                hConn,
        IN  MMC_AXIS_REF_HNDL               hAxisRef,
        IN  MMC_INSNOTIFICATIONFB_IN*       pInParam,
        OUT MMC_INSNOTIFICATIONFB_OUT*      pOutParam);
//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif
#endif /* MMC_EVENTS_API_H_ */

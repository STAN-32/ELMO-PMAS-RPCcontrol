/*
 * CMMCConnection.hpp
 *
 *  Created on: 22/03/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */

#ifndef MMCPPCONNECTION_HPP_
#define MMCPPCONNECTION_HPP_

#include "MMC_definitions.h"
#include "MMCPPGlobal.hpp"


#define USR_VAR_1               0
#define USR_VAR_2               1
#define USR_VAR_3               2
#define USR_VAR_4               3
#define EMERGENCY_MANUFACTURER_SPECIFIC_BLOCK_SIZE   5

#define EVENT_ID_INDX           0
#define POLICYERROR_ID_INDX  	10
#define AXIS_REF_INDX           12
#define ASYNC_EVENT_LEN_INDX    16
#define PDO_GROUP_INDX          14
#define PDO_DATA_INDX           15
#define MSG_DATA_INDX           8
#define EMGCY_LEN_INDX          4
#define EMGCY_DATA_INDX         14
#define TOUCHP_POS_INDX         14
#define EVENT_CODE_INDX         14

typedef union {ELMO_UINT16 usVal; ELMO_FLOAT fVal; ELMO_LINT32 lVal;} UNPDODAT;

typedef void (*PdoRcvEventCallback)(ELMO_UINT16 usAxisRef, ELMO_UINT16 usGrpID, UNPDODAT unDat1, UNPDODAT unDat2);
typedef void (*HBeateEventCallback)(ELMO_UINT16 usAxisRef);
typedef void (*MotionEndEventCallback)(ELMO_UINT16 usAxisRef, ELMO_BOOL bResult);
typedef void (*EmergencyEventCallback)(ELMO_UINT16 usAxisRef, ELMO_INT16 sEmcyCode, ELMO_INT8 cErrReg, ELMO_INT8 cManSpec[EMERGENCY_MANUFACTURER_SPECIFIC_BLOCK_SIZE]);
typedef void (*HomeEndedEventCallback)(ELMO_UINT16 usAxisRef, ELMO_INT16 sErrCode,...);
typedef void (*ModbusWriteEventCallback)(ELMO_UINT16 usSubType);
typedef void (*SysErrorEventCallback)();
typedef void (*AsyncReplyEventCallback)(ELMO_UINT16 usAxisRef,ELMO_UINT16 usStatus, ELMO_UINT16 usError,
                                        ELMO_UINT16 usCobID, ELMO_UINT16 usLength, ELMO_PUINT8 ucBuffer,
                                        ELMO_UINT8 ucAsyncEventType, ELMO_UINT32 uiAbortCode, ELMO_UINT16 usIndex,
                                        ELMO_UINT8 ucHeader, ELMO_UINT8 ucSubIndex);
typedef void (*TouchProbeEndCallback)(ELMO_UINT16 usAxisRef, ELMO_LINT32  lPosition);
typedef void (*NodeErrorEventCallback)(ELMO_UINT16 usAxisRef,ELMO_UINT16 sErrorID,ELMO_UINT16 usEmergencyCode);
typedef void (*StopOnLimitEventCallback)(ELMO_UINT16 usAxisRef, ELMO_UINT16 usError, ELMO_UINT32 uiStatusRegister, ELMO_UINT32 uiMcsLimitRegister);
typedef void (*TableUnderflowEventCallback)(ELMO_UINT16 usAxisRef);
typedef void (*NodeConnectedEventCallback)(ELMO_UINT16 usAxisRef);
typedef void (*GlobalAsyncReplyEventCallback)(ELMO_UINT16 usStatus, ELMO_UINT16 usError, ELMO_UINT8 ucMessageID);
typedef void (*NodeInitEventCallback)(ELMO_UINT16 usError, ELMO_UINT16 usAxisRef);
typedef void (*FBNotifyEventCallback)(ELMO_UINT16 usAxisRef, ELMO_INT32  iEventCode);
typedef void (*PolicyEndedEventCallback)(ELMO_UINT16 usAxisRef, ELMO_INT16 sError, ELMO_UINT16 ucPolType, ELMO_UINT16 ucPolState, ELMO_UINT16 ucErrorType);


typedef enum {MMCPP_PDORCV, MMCPP_HBEAT,  MMCPP_MOTIONENDED,  MMCPP_EMCY,
    MMCPP_ASYNC_REPLY, MMCPP_HOME_ENDED, MMCPP_MODBUS_WRITE, MMCPP_TOUCH_PROBE_ENDED,
    MMCPP_NODE_ERROR, MMCPP_STOP_ON_LIMIT, MMCPP_TABLE_UNDERFLOW, MMCPP_NODE_CONNECTED,
   	MMCPP_GLOBAL_ASYNC_REPLY, MMCPP_NODE_INIT, MMCPP_FB_NOTIFICATION, MMCPP_POLICY_ENDED
    } MMC_EVENT_ENUM;


class DLLMMCPP_API CMMCConnection {
public:
    CMMCConnection();
    virtual ~CMMCConnection();
    
    #if (OS_PLATFORM == LINUXIPC32_PLATFORM)
        MMC_CONNECT_HNDL ConnectIPC(ELMO_INT32 iEventMask, MMC_CB_FUNC fpClbk);
        MMC_CONNECT_HNDL ConnectIPCEx(ELMO_INT32 iEventMask, MMC_MB_CLBK fpClbk);
    #endif

    MMC_CONNECT_HNDL ConnectRPC(ELMO_PINT8 cHostIP, ELMO_PINT8 cDestIP, ELMO_INT32 iEventMask, MMC_CB_FUNC fpClbk);
    MMC_CONNECT_HNDL ConnectRPCEx(ELMO_PINT8 cHostIP, ELMO_PINT8 cDestIP, ELMO_INT32 iEventMask, MMC_MB_CLBK fpClbk);
    void CloseConnection();

    MMC_CONNECT_HNDL GetConnHndl() {return m_uiConnHndl;}
    void GetVersion() throw (CMMCException);
    void GetVersion_Ex()  throw (CMMCException);
    void GetLibVersion();
    void GetVersionEx(std::string& strVersion) throw (CMMCException);
    void GetVersion(ELMO_INT32& iVer) throw (CMMCException);


    /*! \fn void MMC_GlobalWriteBoolParameterSetGlobalBoolParameter(unsigned long ulValue, MMC_PARAMETER_LIST_ENUM eNumber, int iIndex, unsigned char ucEnable = 1)
    * \brief This function write boolean global parameter.
    * \return   return - 0 if success, otherwise throws CMMCException.
    */
    void SetGlobalBoolParameter(ELMO_LINT32 lValue, MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    void SetGlobalParameter(ELMO_DOUBLE dbValue, MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    ELMO_LINT32 GetGlobalBoolParameter(MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    ELMO_DOUBLE GetGlobalParameter(MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    //
    void SaveParameters() throw (CMMCException);
    void LoadParameters() throw (CMMCException);
    void SetDefaultManufacturerParameters() throw (CMMCException);
    void SetIsToLoadGlobalParams(ELMO_UINT8 ucVal) throw (CMMCException);
    void SetHeartBeatConsumer(ELMO_UINT32 uiHeartbeatTimeFactor) throw (CMMCException);
    ELMO_INT32 CallbackFunc(ELMO_PUINT8, ELMO_INT16, ELMO_PVOID);
    void RegisterEventCallback(MMC_EVENT_ENUM eClbType, ELMO_PVOID pfClbk);//register event callbacks
    void RegisterSyncTimerFunction(MMC_SYNC_TIMER_CB_FUNC func, ELMO_UINT16 usSYNCTimerTime);
	void GetMaestroTime(ELMO_UINT16 &year, ELMO_UINT16 &month, ELMO_UINT16 &day, ELMO_UINT16 &hour,
			ELMO_UINT16 &minute, ELMO_UINT16 &second, ELMO_UINT16 &milliSecond) throw (CMMCException);
	void SetMaestroTime(ELMO_UINT16 year, ELMO_UINT16 month, ELMO_UINT16 day, ELMO_UINT16 hour,
			ELMO_UINT16 minute, ELMO_UINT16 second, ELMO_UINT16 milliSecond) throw (CMMCException);

    // Connection related functions that deal with UDP event mask
    void SetEventsMask(ELMO_UINT32 uiEventMask) throw (CMMCException);
    void ClearEventsMask(ELMO_UINT32 uiEventMask) throw (CMMCException);
    ELMO_UINT32 GetEventsMask() throw (CMMCException);

private:
    MMC_MB_CLBK                     m_fpClbk;
    MMC_CONNECT_HNDL                m_uiConnHndl;  /*!< communication session handler;                 */
    ELMO_INT8                       m_cHost[16];
    ELMO_INT8                       m_cDest[16];
    ELMO_INT32                      m_iConnID;
   	ELMO_UINT8						m_ucDeviceType;
    PdoRcvEventCallback             m_pfPdoRcvEventClbk;
    HBeateEventCallback             m_pfHBeateEventClbk;
    MotionEndEventCallback          m_pfMotionEndEventClbk;
    EmergencyEventCallback          m_pfEmergencyEventClbk;
    HomeEndedEventCallback          m_pfHomeEndEventClbk;
    ModbusWriteEventCallback        m_pfModbusWriteEventClbk;
    //SysErrorEventCallback         m_pfSysErrorEventClbk;
    AsyncReplyEventCallback         m_pfAsyncReplyEventClbk;
    TouchProbeEndCallback           m_pfTouchProbeEndCallback;
    NodeErrorEventCallback          m_pfNodeErrorEventClbk;
    StopOnLimitEventCallback        m_pfStopOnLimitEventClbk;
    TableUnderflowEventCallback     m_pfTableUnderflowEventClbk;
    NodeConnectedEventCallback      m_pfNodeConnectedEventClbk;
    GlobalAsyncReplyEventCallback   m_pfGlobalAsyncReplyEventClbk;
    NodeInitEventCallback           m_pfNodeInitEventClbk;
    FBNotifyEventCallback           m_pfFBNotifyEventClbk;
	PolicyEndedEventCallback  		m_pfPolicyEndedEventClbk;
};

#endif /* MMCPPCONNECTION_HPP_ */

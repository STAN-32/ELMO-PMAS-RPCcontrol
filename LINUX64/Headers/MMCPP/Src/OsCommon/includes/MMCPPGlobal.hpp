/*
 * CMMCPPGlobal.hpp
 *
 *  Created on: 15/03/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 *              0.4.0 Updated 11Sep2017 Haim H.
 */
/*
 * -------------------------------------------------------------------------------------------------------------
 * history list of modification
 * -------------------------------------------------------------------------------------------------------------
 *       #              description                                 version release        name               date
 *  __________________________________________________________________________________
 *      001         add version release definition                      v1.0.0.1            YL              30/10/2013
 *      002         add message size restriction to TCP/UDP messages    v1.0.0.1            YL              30/10/2013
 *      003         bypass Linux socket select bug
 *                      in CMMCPP::IsWriable & ::IsReadable             v1.0.0.1            YL              30/10/2013
 *      004         reset #003. getpeername system call is not          v1.0.0.2            YL/HH           23/01/2014
 *                      a suitable solution.
 *      005         add ECAM API                                                            v1.0.0.4 YL     30/11/2014
 *      006         add CurveType input parameter to MC_CamIn           v1.0.1.0            YL              04/03/2015
 *                  within InitPVT Table, PVT dynamic is on unless Cyclic
 *                  if on. underflow threshold is 0 if Cyclic is on.
 *                  Cyclic is meaningless on PVT dynamic mode.          v1.0.1.0            YL              04/03/2015
 */

#ifndef MMCPPGLOBAL_HPP_
#define MMCPPGLOBAL_HPP_
//
//
#include <stdlib.h>
#include <string.h>
#include "MMC_definitions.h"
//
typedef ELMO_INT32 (*RTE_CLBKP)(const ELMO_INT8* cErrMsg, MMC_CONNECT_HNDL uiConnHndl, ELMO_UINT16 usAxisRef, ELMO_INT16 sErrorID, ELMO_UINT16 usStatus);
typedef ELMO_INT32 (*WARNING_CLBKP)(const ELMO_INT8* cFunctionName, MMC_CONNECT_HNDL uiConnHndl, ELMO_UINT16 usAxisRef, ELMO_INT32 iRetCode, ELMO_INT16 sErrorID, ELMO_UINT16 usStatus);


#ifdef __cplusplus //@YL 20201020
#include <iostream>
#include <fstream>

//
using namespace std;
//
//using std::cout;
//using std::endl;
//using std::fstream;
//using std::string;
//

    typedef ELMO_UINT64 MMCPPULL_T;

//
#include "MMCMessage.hpp"

//#define _MMCPP_VERSION_RELEASE "v1.0.0.1"
//#define _MMCPP_VERSION_RELEASE "v2.0.0.0"
                                        // 12Sep2017 send to PRAUT / Mariusz
//#define _MMCPP_VERSION_RELEASE "v2.1.0.0"
//#define _MMCPP_VERSION_RELEASE "v2.1.2.0"
										// 23Nov2020 Update interface up to "v1.0.6.4"
										// Follow "source" version = "v1.0.6.4" by change the base to '100'
#define _MMCPP_VERSION_RELEASE "v100.0.6.4"
//
//
#if ((OS_PLATFORM == WIN32_PLATFORM) || (OS_PLATFORM == WIN64_PLATFORM))

 //   #ifdef PROAUT_CHANGES
 //   //PROAUT: nothing to do because timespec is already define for gcc/mingw
 //   #else
 //           struct timespec
 //       {
 //         time_t     tv_sec;
 //         ELMO_LINT32 tv_nsec;
 //       };
 //   #endif

    void nanosleep (const struct timespec *requested_delay);

#endif


#ifdef MMCPP_DEBUG
    #define  MMCPP_TRACE(FORMAT,FUNC,RC,NAME,REF,ERRID,STATUS) \
        printf(FORMAT,FUNC,RC,NAME,REF,ERRID,STATUS);
    #define _MMCPP_TRACE(FORMAT,RC,NAME,REF,ERRID,STATUS) \
        printf(FORMAT,RC,NAME,REF,ERRID,STATUS);
    #define _MMCPP_TRACE_INFO(INFOSTR) \
        cout << INFOSTR << endl;
#else
    #define  MMCPP_TRACE(FORMAT,FUNC,RC,NAME,REF,ERRID,STATUS)
    #define _MMCPP_TRACE(FORMAT,RC,NAME,REF,ERRID,STATUS)
    #define _MMCPP_TRACE_INFO(INFOSTR)
#endif
//
//
#define MMCPP_MAX_CONNECTIONS_NUM   20
//
typedef struct
{
    MMC_CONNECT_HNDL	m_uiConnHndl;
    ELMO_PVOID      	m_pConn;
} MMCPP_CONN_REG;


template <class T>
class TMMCPPSingleton
{
public:
    static T * Instance()
    {
        static T obj;
        return &obj;
    }

private:
     TMMCPPSingleton() {}
    ~TMMCPPSingleton() {}
};

#define SINGLETON(T) protected:friend class TMMCPPSingleton< T >;T(){};
#define SINGLETONINSTANCE(T) TMMCPPSingleton< T >::Instance()

// ----------------------------------------------------------------------------



class DLLMMCPP_API CMMCException
{
public:
    CMMCException(const ELMO_INT8* msg, const ELMO_INT8* cAxisName, ELMO_UINT16 usAxisRef, ELMO_INT32 errid, ELMO_UINT16 status); //: m_usErrorID(errid), m_usStatus(status), m_usAxisRef(usAxisRef)

    const   ELMO_INT8*   what()      {return m_cMessage;}
    const   ELMO_INT8*   axisName()  {return m_cAxisName;}
            ELMO_INT16   error()     {return m_usErrorID;}
            ELMO_UINT16  status()    {return m_usStatus;}
            ELMO_UINT16  axisRef()   {return m_usAxisRef;}

private:
    ELMO_INT8    m_cMessage[1024];
    ELMO_INT8    m_cAxisName[128];
    ELMO_UINT16  m_usErrorID;
    ELMO_UINT16  m_usStatus;
    ELMO_UINT16  m_usAxisRef;     /*!< set by GetAxisByName                           */
};
//



//
class DLLMMCPP_API CMMCPPGlobal {
//  SINGLETON( CMMCPPGlobal )
public:
    static CMMCPPGlobal * Instance()
    {
        static CMMCPPGlobal g_Instance;     
        return &g_Instance;
    }

public:
    //
    void RegisterRTE(RTE_CLBKP pRTEClbk, ELMO_BOOL bIsToCloseOnRTE = true);
    void RegisterWarningClbk(WARNING_CLBKP pWarningClbk) {m_pWarningClbk =  pWarningClbk;}
    void SetThrowFlag(ELMO_BOOL bThrow, ELMO_BOOL bIsToCloseOnThrow = true) {m_bThrowException_OnError =  bThrow;m_bIsToCloseOnThrow = bIsToCloseOnThrow;}
    void SetThrowWarningFlag(ELMO_BOOL bThrowWarining) {m_bThrowException_OnWarning =  bThrowWarining;}
    void SetPrintErrorFlag(ELMO_BOOL bPrintError) {m_bPrintError =  bPrintError;}
    void SetPrintWarningFlag(ELMO_BOOL bPrintWarining) {m_bPrintWarning =  bPrintWarining;}
    ELMO_BOOL IsToThrowError() { return m_bThrowException_OnError;}
    ELMO_BOOL IsToThrowWarning() {return m_bThrowException_OnWarning;}
    ELMO_BOOL IsToCallWarningClbk() { return (m_pWarningClbk != NULL);}
    ELMO_BOOL IsToCallRTEClbk() {return (m_pRTEClbk != NULL);}
    void  MMCPPThrow(const ELMO_INT8* cFunctionName, MMC_CONNECT_HNDL uiConnHndl, ELMO_UINT16 usAxisRef, ELMO_INT32 iRetCode, ELMO_INT16 sErrorID, ELMO_UINT16 usStatus);
    /*! \fn unsigned short GetSyncTime()
    * \brief The function returns the SYNC time, in case of CAN communication.
    * \return   return - sync time on success, otherwise throws CMMCException.
    */
    ELMO_UINT16 GetSyncTime(MMC_CONNECT_HNDL uiConnHndl) throw (CMMCException);
    /*! \fn int SetSyncTime(
    * \brief The function sets the SYNC time in the communication module.
    * \param  usSync - sync time.
    * \return   return - 0 if success, otherwise throws CMMCException.
    */
    ELMO_INT32 SetSyncTime(MMC_CONNECT_HNDL uiConnHndl, ELMO_UINT16 usSync) throw (CMMCException);
    void CreateSYNCTimer(MMC_CONNECT_HNDL uiConnHndl, MMC_SYNC_TIMER_CB_FUNC pfClbk, ELMO_UINT16 usSYNCTimerTime)  throw (CMMCException);
    void DestroySYNCTimer(MMC_CONNECT_HNDL uiConnHndl) throw (CMMCException);
    //
    ELMO_INT32 RegisterConnection(MMC_CONNECT_HNDL uiConnHndl, ELMO_PVOID pConn);
    ELMO_PVOID GetConnectionReg(MMC_CONNECT_HNDL uiConnHndl);
    void ClearConnectionReg(MMC_CONNECT_HNDL uiConnHndl);
    //
    void            ThrowMessage(ELMO_INT32 iRetval,ELMO_INT32 iErrorID,const ELMO_INT8* cFunctionName);
    MMCPP_CONN_TYPE GetConnectionType(){return m_eConnectionType;}
    void            SetConnectionType(MMCPP_CONN_TYPE eConnectionType_IN){m_eConnectionType = eConnectionType_IN;}
    
    #if (OS_PLATFORM == LINUXIPC32_PLATFORM)
        string          GetMessageFileName(){return m_cMessage.GetMessageFileName();}
        void            SetMessageFileName(string sMessageFileName_IN){m_cMessage.SetMessageFileName(sMessageFileName_IN);}
        void            SetMessageFileName(ELMO_PINT8 cMessageFileName_IN){m_cMessage.SetMessageFileName(cMessageFileName_IN);}
    #endif

    void            ConfigBulkRead(MMC_CONNECT_HNDL hConnHndl,
                                   NC_BULKREAD_CONFIG_ENUM eConfig,
                                   NC_BULKREAD_PRESET_ENUM ePreset,
                                   ELMO_UINT16 usAxisRefArray[],
                                   ELMO_UINT16 usNumberOfAxes,
                                   ELMO_PFLOAT fFactorsArray) throw (CMMCException);

    void            ConfigBulkRead(MMC_CONNECT_HNDL hConnHndl,
                                   NC_BULKREAD_CONFIG_ENUM eConfig,
                                   ELMO_ULINT32  ulParameters[],
                                   ELMO_UINT16   usAxisRefArray[],
                                   ELMO_UINT16   usNumberOfAxes,
                                   ELMO_PFLOAT   fFactorsArray) throw (CMMCException);

    void            PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
                                   ELMO_UINT16 usNumberOfAxes,
                                   NC_BULKREAD_CONFIG_ENUM eConfiguration,
                                   NC_BULKREAD_PRESET_ENUM& eChosenPreset,
                                   NC_BULKREAD_PRESET_1 stOutputData[]);

    void            PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
                                   ELMO_UINT16 usNumberOfAxes,
                                   NC_BULKREAD_CONFIG_ENUM eConfiguration,
                                   NC_BULKREAD_PRESET_ENUM& eChosenPreset,
                                   NC_BULKREAD_PRESET_2 stOutputData[]);

    void            PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
                                   ELMO_UINT16 usNumberOfAxes,
                                   NC_BULKREAD_CONFIG_ENUM eConfiguration,
                                   NC_BULKREAD_PRESET_ENUM& eChosenPreset,
                                   NC_BULKREAD_PRESET_3 stOutputData[]);

    void            PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
                                   ELMO_UINT16 usNumberOfAxes,
                                   NC_BULKREAD_CONFIG_ENUM eConfiguration,
                                   NC_BULKREAD_PRESET_ENUM& eChosenPreset,
                                   NC_BULKREAD_PRESET_4 stOutputData[]);

    void            PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
                                   ELMO_UINT16 usNumberOfAxes,
                                   NC_BULKREAD_CONFIG_ENUM eConfiguration,
                                   NC_BULKREAD_PRESET_ENUM& eChosenPreset,
                                   NC_BULKREAD_PRESET_5 stOutputData[]);

    void            PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
                                   ELMO_UINT16 usNumberOfAxes,
                                   NC_BULKREAD_CONFIG_ENUM eConfiguration,
                                   NC_BULKREAD_PRESET_ENUM& eChosenPreset,
                                   ELMO_PULINT32 ulOutputData);
    //
    void            UserCommandControlExe(MMC_CONNECT_HNDL hConnHndl,
                                   ELMO_INT8 cUserCommandIn[128],
                                   MC_COMMAND_OPERATION eUsrCommandOpIn,
                                   ELMO_INT32 &iStatus,
                                   ELMO_INT8  cExecutableFileName[64] = NULL);

    void RegErrPolicy(MMC_CONNECT_HNDL hConnHndl,MMC_REGERRPOLICY_IN stInParams) throw (CMMCException);
    void GetErrPolicy(MMC_CONNECT_HNDL hConnHndl,MMC_GETERRPOLICY_IN stInParams,MMC_GETERRPOLICY_OUT &stOutParams) throw (CMMCException);
    void ResetSystem(MMC_CONNECT_HNDL hConnHndl) throw (CMMCException);

    void RunSineGenrator(MMC_CONNECT_HNDL hConnHndl,MMC_SINEGENERATOR_IN &stInParams) throw (CMMCException);

//#ifndef WIN32
#if ((OS_PLATFORM == LINUXIPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC64_PLATFORM))

                           std::string GetLibVersion(); __attribute__ ((deprecated));

#elif ((OS_PLATFORM == WIN32_PLATFORM) || (OS_PLATFORM == WIN64_PLATFORM) || (OS_PLATFORM == VXWORKS32_PLATFORM))

    /*
    * too risky. user project's settings must comply exactly to library 
    * use GetLibVersion(std::string& str) (see below)
    */
    __declspec(deprecated) std::string GetLibVersion(); 

#else
    #error "***MMCPPGlobal.hpp: Supporting Env. Visual or Eclipse (found Env. from defined platform...). "
#endif

    /**
    * \fn void GetLibVersion(std::string& str)
    * \brief        retrieves this library version release
    * \param str    string reference from user program to retrieve the version.
    * \return none. version in str.
    */
inline void GetLibVersion(std::string& str) {str = std::string(_MMCPP_VERSION_RELEASE);}

    /*!
     * \fn  int GetProfileConditioning(MMC_PROFCONDINF_OUT& o_params)
     * \brief   this method gets 'profile conditioning' information.
     *
     * it gets 'profile conditioning' data for axes on which this mode of operation is enabled.
     *
     * \param hConnHndl connection handler.
     * \param o_params  stores data information of active axes by profile conditioning.
     * \return 0 if completed successfully, otherwise error or throws exception.
     */
    ELMO_INT32 GetProfileConditioning(MMC_CONNECT_HNDL hConnHndl, MMC_PROFCONDINF_OUT& o_params) throw (CMMCException);

private:

CMMCPPGlobal() : m_bIsToCloseOnThrow(false), m_pRTEClbk(NULL),m_pWarningClbk(NULL)
{
    for(ELMO_INT32 i=0;i<MMCPP_MAX_CONNECTIONS_NUM;i++)
    {
        m_ConnRegTable[i].m_uiConnHndl=0;
    }
    m_bThrowException_OnError   = ELMO_FALSE;
    m_bThrowException_OnWarning = ELMO_FALSE;
    m_bPrintWarning             = ELMO_FALSE;
    m_bPrintError               = ELMO_TRUE;
    m_bIsToCloseOnRTE           = ELMO_TRUE;
    m_eConnectionType           = CT_UNKNOWN;
}

    ~CMMCPPGlobal()
    {
    }

    CMMCPPGlobal(CMMCPPGlobal const&);   // Don't Implement
    void operator=(CMMCPPGlobal const&); // Don't implement
    //
    ELMO_BOOL       m_bThrowException_OnError;
    ELMO_BOOL       m_bThrowException_OnWarning;
    ELMO_BOOL       m_bPrintWarning;
    ELMO_BOOL       m_bPrintError;
    ELMO_BOOL       m_bIsToCloseOnRTE;
    ELMO_BOOL       m_bIsToCloseOnThrow;
    MMCPP_CONN_TYPE m_eConnectionType;
    RTE_CLBKP       m_pRTEClbk;
    WARNING_CLBKP   m_pWarningClbk;
    MMCPP_CONN_REG  m_ConnRegTable[MMCPP_MAX_CONNECTIONS_NUM];      

    #if (OS_PLATFORM == LINUXIPC32_PLATFORM)
        CMMCMessage m_cMessage;
    #endif
};


namespace MMCPPUtils
{
    inline void NetToLocal(ELMO_PVOID NetBuff, ELMO_PUINT16 usVal)
    {

        if (NetBuff != (ELMO_PVOID)usVal)
        {
            memcpy((ELMO_PUINT8)usVal,(ELMO_PUINT8)NetBuff, 2);
        }
        #if (ENDIAN_SELECT == RPC_ENDIAN_AUTO_SET)
            /* ????  Should set according to diff between Host Endian (same by diffinition to GMAS only on IPC...) ???? */
            /* ???? if different should swap. Meanwhile this setting SUTIABLE ONLY TO "OLD GMAS"                   ???? */
            endian_swap16((ELMO_PUINT16)usVal);
        #elif (ENDIAN_SELECT == IPC_ENDIAN_IS_TRNSP)
        #else
            #error "***MMCPPGlobal.hpp 'ENDIAN_SELECT' (1) should set to one of: 'RPC_ENDIAN_AUTO_SET' or 'IPC_ENDIAN_IS_TRNSP' (see OS_PlatformsSelect.h)"
        #endif
    }

    inline void NetToLocal(ELMO_PVOID NetBuff, ELMO_PVOID iVal)
    {
        if (NetBuff != iVal)
        {
            memcpy((ELMO_PUINT8)iVal,(ELMO_PUINT8)NetBuff,4);
        }
        #if (ENDIAN_SELECT == RPC_ENDIAN_AUTO_SET)
            /* ????  Should set according to diff between Host Endian (same by diffinition to GMAS only on IPC...) ???? */
            /* ???? if different should swap. Meanwhile this setting SUTIABLE ONLY TO "OLD GMAS"                   ???? */
            endian_swap32((ELMO_PUINT32)iVal);
        #elif (ENDIAN_SELECT == IPC_ENDIAN_IS_TRNSP)
        #else
            #error "***MMCPPGlobal.hpp 'ENDIAN_SELECT' (2) should set to one of: 'RPC_ENDIAN_AUTO_SET' or 'IPC_ENDIAN_IS_TRNSP' (see OS_PlatformsSelect.h)"
        #endif
    }
}
#endif // __cplusplus //@YL 20201020

/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C  back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif
	/*!
	 * \fn void register_rte_clbk(RTE_CLBKP clbk)
	 * \brief this function is C interface, which allows C code to handle runtime exception from Elmo's C++ library.
	 * \param clbk the call-back function (the exception handler).
	 * \return none.
	 */
	void register_rte_clbk(RTE_CLBKP clbk);
	/*!
	 * \fn void unregister_rte_clbk(void)
	 * \brief this function is C interface, which allows C code to decouple from the  runtime exception handler via Elmo's C++ library.
	 * \return none.
	 */
	void unregister_rte_clbk(void);
#ifdef __cplusplus
}
#endif


#endif /* MMCPPGLOBAL_HPP_ */

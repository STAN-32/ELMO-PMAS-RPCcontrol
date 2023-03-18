////////////////////////////////////////////////////////////////////////////////
/// Name        : Os_Platform.h
/// Author      : Haim Hillel
/// Created on  : 29Jan2013
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.3.0 Updated 03Aug2015 Haim H. support Littlendian & Bigendian GMAs
///               0.3.8 Updated 07Sep2017 Haim H. for PROAUT
///               0.4.0 Updated 11Sep2017 Haim H.
///               0.4.2 Updated 26Aug2019 Haim H.
///               0.4.4 Updated 22Nov2020 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain GMAS Operating System Platform dependencies data type and definitions.
////////////////////////////////////////////////////////////////////////////////

#ifndef OS_PLATFORM_H_
#define OS_PLATFORM_H_

#include <fcntl.h>
#include <errno.h>
#include <string.h>




#ifdef __cplusplus
 extern "C" {
#endif

                /* Actualy common for all platforms... */
#define LINUX_ALIGNMENT
typedef enum {
                        ePLATFORM_SAME_HOST_GMAS_ENDIAN  = 0x02,
                        ePLATFORM_DIFF_HOST_GMAS_ENDIAN  = 0x40
}eGMAS_ENDIAN_TYPE;


#if   (OS_PLATFORM == LINUXIPC32_PLATFORM)
    #define NC_ALIGNMENT __attribute__((aligned(8)))
    #define LINUX_ALIGNMENT
    // HH ??? #define LINUX_ALIGNMENT __attribute__((packed,aligned(32)))
    #define MMC_PACKED_STRUCT struct NC_ALIGNMENT
	//
    #include "OS_PlatformLinuxIpc32.h"
	//
#elif (OS_PLATFORM == WIN32_PLATFORM)
    #ifdef PROAUT_CHANGES
        #define NC_ALIGNMENT __attribute__((aligned(8)))
    #else
        #define NC_ALIGNMENT __declspec(align(8)) //double alignmment
    #endif
    #define MMC_PACKED_STRUCT NC_ALIGNMENT struct
	//
    #include "OS_PlatformWin32.h"
	//
#elif (OS_PLATFORM == WIN64_PLATFORM)
    #ifdef PROAUT_CHANGES
        #define NC_ALIGNMENT __attribute__((aligned(8)))
    #else
        #define NC_ALIGNMENT __declspec(align(8)) //double alignmment
    #endif
    #define MMC_PACKED_STRUCT NC_ALIGNMENT struct
	//
    #include "OS_PlatformWin64.h"
	//
#elif (OS_PLATFORM == LINUXRPC32_PLATFORM)
    #define NC_ALIGNMENT __attribute__((aligned(8)))
    #define MMC_PACKED_STRUCT struct NC_ALIGNMENT
	//
    #include "OS_PlatformLinuxRpc32.h"
	//
#elif (OS_PLATFORM == LINUXRPC64_PLATFORM)
    #define NC_ALIGNMENT __attribute__((aligned(8)))
    #define MMC_PACKED_STRUCT struct NC_ALIGNMENT
	//
    #include "OS_PlatformLinuxRpc64.h"
	//
#elif (OS_PLATFORM == VXWORKS32_PLATFORM)
    #define NC_ALIGNMENT __attribute__((aligned(8)))
    #define MMC_PACKED_STRUCT struct NC_ALIGNMENT
	//
    #include "OS_PlatformVxWorks32.h"
	//
#else
    #error "***OS_Platform.h: Symbol 'OS_PLATFORM' should set to one of: 'LINUXIPC32_PLATFORM', 'WIN32_PLATFORM', Etc... (See OS_PlatformSelect.h) "
#endif

                             /* For Debug Identifay C lib Compile time config   */
                             /* (Compilation-Time sybols in RT variables)       */
                             /* *********************************************** */
extern ELMO_INT32 gi_RPC_ENDIAN_AUTO_SET;
extern ELMO_INT32 gi_IPC_ENDIAN_IS_TRNSP;

extern ELMO_INT32 gi_LINUXIPC32_PLATFORM;
extern ELMO_INT32 gi_WIN32_PLATFORM     ;
extern ELMO_INT32 gi_WIN64_PLATFORM     ;
extern ELMO_INT32 gi_LINUXRPC32_PLATFORM;
extern ELMO_INT32 gi_LINUXRPC64_PLATFORM;
extern ELMO_INT32 gi_VXWORKS32_PLATFORM ;
   
extern ELMO_INT32 gi_ENDIAN_SELECT      ;
extern ELMO_INT32 gi_OS_PLATFORM        ;

extern ELMO_INT32 gi_OS_PLATFORMID      ;

MMC_LIB_API void print_MMC_API_Lib3264Characteristic(
                                            ELMO_INT32 _prm_iRPC_ENDIAN_AUTO_SET,
                                            ELMO_INT32 _prm_iIPC_ENDIAN_IS_TRNSP,
                                        
                                            ELMO_INT32 _prm_iLINUXIPC32_PLATFORM,
                                            ELMO_INT32 _prm_iWIN32_PLATFORM     ,
                                            ELMO_INT32 _prm_iWIN64_PLATFORM     ,
                                            ELMO_INT32 _prm_iLINUXRPC32_PLATFORM,
                                            ELMO_INT32 _prm_iLINUXRPC64_PLATFORM,
                                            ELMO_INT32 _prm_iVXWORKS32_PLATFORM ,
                                        
                                            ELMO_INT32 _prm_iENDIAN_SELECT      ,
                                            ELMO_INT32 _prm_iOS_PLATFORM        
                                         );
                             /* ************************************************ */


///////////////////////////////////////////////////////////////////////////////
/// \typedef MMC_SND_MSG_FUNC
/// \brief  IPC/RPC send function prototype.
///////////////////////////////////////////////////////////////////////////////
typedef ELMO_INT32 (*MMC_SND_MSG_FUNC)(IN MMC_IF_STRUCT* pMmcIf, IN MMC_AXIS_REF_HNDL hAxisRef, IN ELMO_INT32 iFuncId, IN ELMO_PVOID pInParam, IN ELMO_INT16 iInSize, IN ELMO_INT16 iOutSize, OUT ELMO_PVOID pOutParam);

typedef ELMO_INT32 (*PfuncType)(ELMO_PVOID funcPrm);


MMC_LIB_API ELMO_INT32       OS_PlatformMMC_CreateRpcConnect     (MMC_IF_STRUCT* pMmcIf, IN ELMO_PINT8 pSockPath, ELMO_UINT16  usPort, ELMO_PINT8 cpHostIPAddr);
MMC_LIB_API ELMO_INT32       OS_PlatformMMC_CloseRpcConnect      (MMC_IF_STRUCT* pMmcIf);
MMC_LIB_API ELMO_INT32       OS_PlatformMMC_IpcSndMsg            (MMC_IF_STRUCT* pMmcIf, MMC_AXIS_REF_HNDL hAxisRef, ELMO_INT32 iFuncId, ELMO_PVOID pInParam, ELMO_INT16 iInSize, ELMO_INT16  iOutSize, ELMO_PVOID pOutParam);
MMC_LIB_API ELMO_INT32       OS_PlatformMMC_RpcSndMsg            (MMC_IF_STRUCT* pMmcIf, MMC_AXIS_REF_HNDL hAxisRef, ELMO_INT32 iFuncId, ELMO_PVOID pInParam, ELMO_INT16 iInSize, ELMO_INT16  iOutSize, ELMO_PVOID pOutParam);
MMC_LIB_API ELMO_INT32       OS_PlatformMMC_CreateIpcConnect     (MMC_IF_STRUCT* pMmcIf, IN ELMO_PINT8 pSockPath);
MMC_LIB_API void             OS_PlatformIpcMultiAxisControl      (MMC_IF_STRUCT* pMmcIf);
MMC_LIB_API ELMO_INT32       OS_PlatformMMC_CloseIpcConnect      (MMC_IF_STRUCT* pMmcIf);
MMC_LIB_API ELMO_INT32       OS_PlatformDestroyUDPSocketListener (MMC_IF_STRUCT* pMmcIf);
MMC_LIB_API ELMO_INT32       OS_PlatformCreateSocket             (MMC_IF_STRUCT* pMmcIf, ELMO_INT32 nType, ELMO_PINT8 cErr);
MMC_LIB_API ELMO_INT32       OS_PlatformUDPThreadFunc            (ELMO_PVOID ptrConn);

MMC_LIB_API ELMO_INT32       OS_PlatformMMC_CloseConnection      (MMC_CONNECT_HNDL hConn);
MMC_LIB_API ELMO_INT32       OS_PlatformMMC_IPCInitConnection    (MMC_IPC_CONNECTION_PARAM_STRUCT sConnParam, IN  MMC_CB_FUNC pCbFunc, OUT MMC_CONNECT_HNDL* pHndl);

MMC_LIB_API ELMO_INT32       OS_PlatformCreateUDPSocketListenerThread(MMC_IF_STRUCT* pMmcIf, PfuncType UDPThreadFunc, ELMO_PINT8 cErrStr);
MMC_LIB_API ELMO_INT32       OS_PlatformSleepDelayMiliSec        (ELMO_LINT32 sleepDelayMiliSec);
MMC_LIB_API ELMO_INT32       OS_PlatformIpcResetMultiAxisControl (MMC_IF_STRUCT* mmc_if);

MMC_LIB_API ELMO_PVOID       OC_PlatformGetHostIpByName          (ELMO_PINT8 host_name, ELMO_INT8 Ip[]);
MMC_LIB_API void             OS_PlatformCloseUdpConnection       (ELMO_INT32 sockListen, ELMO_INT32 shutdownMod);

MMC_LIB_API OS_SIGNL_EVENT_IMPL  OS_PlatformCreateEvent (ELMO_PVOID attr, ELMO_BOOL resetMode, ELMO_INT32 InitialState, ELMO_PINT8 lpName);

MMC_LIB_API ELMO_INT32       OS_PlatformResetEvent               (OS_SIGNL_EVENT_IMPL* event_arg);
MMC_LIB_API ELMO_INT32       OS_PlatformCloseHandle              (OS_SIGNL_EVENT_IMPL* event_arg);
MMC_LIB_API ELMO_INT32       OS_PlatformSetEvent                 (OS_SIGNL_EVENT_IMPL* event_arg);
MMC_LIB_API ELMO_INT32       OS_PlatformWaitForSingleObject      (OS_SIGNL_EVENT_IMPL* event_arg, ELMO_LINT32 timeout_ms);

MMC_LIB_API ELMO_INT32       OS_PlatformInitializeCriticalSection(OS_CRITIC_SEC_IMPL *  critical_section);
MMC_LIB_API void             OS_PlatformDeleteCriticalSection    (OS_CRITIC_SEC_IMPL *  critical_section);
MMC_LIB_API ELMO_INT32       OS_PlatformEnterCriticalSection     (OS_CRITIC_SEC_IMPL *  critical_section);
MMC_LIB_API ELMO_INT32       OS_PlatformLeaveCriticalSection     (OS_CRITIC_SEC_IMPL *  critical_section);

MMC_LIB_API void             OS_PlatformIntializeTermiEvent      (OS_PlatformTermiEvent * hTerminateEvent);



#ifdef __cplusplus
}
#endif

        /* OS_PLATFORM_H_ */
#endif

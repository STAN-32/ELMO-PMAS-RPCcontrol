////////////////////////////////////////////////////////////////////////////////
/// File name   : os_platformWin32.h
/// Author      : Haim Hillel
/// Created on  : 07Feb2013
/// Version     : 0.0.1,
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.4.0 Updated 11Sep2017 Haim H.
///               0.4.2 Updated 26Aug2019 Haim H.
///               0.4.3 Updated 14Apr2021 Haim H. Add: #include <stdint.h>
/// Copyright   : Your copyright notice
/// Description : This file contain GMAS RPC WIN32 Operating System  Platform dependencies.
///               The file is selected to be including in OS_Platform.h in case target select to be WIN32
////////////////////////////////////////////////////////////////////////////////

#ifndef OS_PLATFORMWIN32_H_
#define OS_PLATFORMWIN32_H_ 

    #include <winsock2.h>
    #include <WinSock.h>
    #include <windows.h>
    #include <winbase.h>
	#include <stdio.h>
	#include <winsock2.h>
    #include <io.h>
    #include <stdlib.h>
	#include <limits.h>
	#include <stdint.h>
    


    #ifdef MMC_LIB_EXPORTS
        #define MMC_LIB_API                 __declspec(dllexport)
    #else
        #ifdef __cplusplus
            #define MMC_LIB_API extern "C"  __declspec(dllimport)
        #else
            #define MMC_LIB_API extern      __declspec(dllimport)
        #endif
    #endif

    #define __func__                __FUNCTION__
    #define OS_SIGNL_EVENT_IMPL     HANDLE
    #define OS_CRITIC_SEC_IMPL      CRITICAL_SECTION
    #define OS_PLATFORM_SINGOBJ_TO  WAIT_TIMEOUT
    #define OS_PlatformTermiEvent   HANDLE
    
    
    #define OS_PLATFORM_INVALID_SOCKET  INVALID_SOCKET
    #define OS_PLATFORM_SOCKET_ERROR    SOCKET_ERROR

    typedef struct 
        {
        ELMO_UINT64          ulliDI;
        ELMO_UINT16          usStatus;
        ELMO_INT16           usErrorID;
        }MMC_READDI_OUT;
    
    typedef struct
        {
        ELMO_UINT64          ulliDO;
        }MMC_WRITEDO_IN;


#include "datastructs.h"


    
///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_IPC_SHM_IN_STRUCT
/// \brief IPC host to target transaction data structure
///
/// This structure defines host to target shared memory transaction for IPC.
///////////////////////////////////////////////////////////////////////////////
typedef struct shared_memory_region1
{
    MMC_IPC_BASIC_IN_STRUCT basic_in ;
    ELMO_UINT8              in_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
    MOTION_FUNCS_INNER_ARGS inner_args;
}LINUX_ALIGNMENT MMC_IPC_SHM_IN_STRUCT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_IPC_SHM_OUT_STRUCT
/// \brief IPC target to host transaction data structure
///////////////////////////////////////////////////////////////////////////////
typedef struct shared_memory_out_region1
{
    ELMO_UINT16  numerator_id;
    ELMO_UINT16  data_size;
    ELMO_UINT16  dummy[2];
    ELMO_UINT8   out_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
    MOTION_FUNCS_INNER_ARGS inner_args;
}LINUX_ALIGNMENT MMC_IPC_SHM_OUT_STRUCT;

    

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_IF_STRUCT
/// \brief Connection interface data structure
///////////////////////////////////////////////////////////////////////////////


typedef struct mmc_if_struct
    {
        ELMO_UINT32                  magic;
        MMC_CONNECTION_TYPE         conn_type;
        MMC_CONNECTION_PARAM_STRUCT conn_param;

        ELMO_DOUBLE      dData[190] ;
        ELMO_INT32       blocksock ;
        ELMO_INT32       sockListen ;
        ELMO_ULINT32     tID ;
        ELMO_INT32       udpport ;

        ELMO_INT32       hConnectThread ;
        OS_SIGNL_EVENT_IMPL hTerminateEvent ;

        ELMO_INT32       iActiveAxesNum;
        MMC_UDP_DATA_FIFO_STRUCT* stUDPDataFIFO[MMC_MAX_NUM_AXIS] ;

        OS_CRITIC_SEC_IMPL  lpCriticalSectionUDP ;
        OS_CRITIC_SEC_IMPL  lpCriticalSectionSendRcv;

        MMC_CB_FUNC     pCbFunc ;
        MMC_CB_FUNC     pCbFuncSecondary ;
        ELMO_INT32       ipc_conn_num;
        ELMO_UINT32      msg_numerator;
        ELMO_PVOID       snd_msg;
                                                                /* GMAS Endian type relating to the Cpu running */
                                                                /* user program => SAME OR DIFFERENT ENDIAN     */
                                                                /* Use in RPC for direct whether GMAS bytes in  */
                                                                /* sensitive to endian should swap.             */
                                                                /* Put also in IPC - for be similar to RPC...   */
        eGMAS_ENDIAN_TYPE eGmasEndianType;
        ELMO_INT8        cLastError[512] ;
        ELMO_UINT8       ucSendAsyncEventFlag ;

        ELMO_UINT8                  ucDeviceType;
        ELMO_INT8                   dest_ip[IP_ADDR_SIZE + 1];  /* Dest ip for rpc calls */

    } LINUX_ALIGNMENT   MMC_IF_STRUCT;


#ifdef __cplusplus
 extern "C" {
#endif
    MMC_LIB_API    ELMO_INT32 MMC_DestroySYNCTimer(IN MMC_CONNECT_HNDL hConn);
    MMC_LIB_API    ELMO_INT32 MMC_CreateSYNCTimer (IN MMC_CONNECT_HNDL hConn, IN MMC_SYNC_TIMER_CB_FUNC func, IN ELMO_UINT16 usSYNCTimerTime);
#ifdef __cplusplus
    }
#endif
    
    #include "blocksock.h"
    

        /* OS_PLATFORMWIN32_H_  */
#endif


////////////////////////////////////////////////////////////////////////////////
/// file os_platformLinuxIpc
/// Name        : OS_platformLinuxIpc.h
/// Author      : Haim Hillel
/// Created on  : 07Feb2013
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.4.0 Updated 11Sep2017 Haim H.
///               0.4.2 Updated 26Aug2019 Haim H.
///               0.4.3 Updated 20Apr2021 Haim H. Add 'ucPause;' to MMC_IF_STRUCT
/// Copyright   : Your copyright notice
/// Description : This file contain GMAS LINUX IPC Operating System Platform dependencies code.
///               The file is selected to be including in OS_Platform.h in case target select to be LINUX IPC.
////////////////////////////////////////////////////////////////////////////////

#ifndef OS_PLATFORMLINUXIPC_H_
#define OS_PLATFORMLINUXIPC_H_

    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <sys/stat.h>
    #include <sys/mman.h>
    #include <sys/socket.h>
    #include <sys/sem.h>
    #include <sys/time.h>
//    #include <sys/ioctl.h>
    #include <sys/wait.h>
    #include <netinet/in.h>
    #include <netinet/tcp.h>
    #include <arpa/inet.h>
    #include <linux/unistd.h>

    #include <stdio.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <signal.h>
    #include <unistd.h>
    #include <syscall.h>
    #include <pthread.h>
    #include <netdb.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    #include <semaphore.h>
	#include <limits.h>
	
                                /* HH Shuld be define in <semaphore.h> but seem not efected... */
    ELMO_INT32 sem_timedwait (sem_t *sem, const struct timespec *abstime);
    
    #define MMC_LIB_API
    #define OS_SIGNL_EVENT_IMPL     sem_t
    #define OS_CRITIC_SEC_IMPL      pthread_mutex_t
    #define OS_PLATFORM_SINGOBJ_TO  ERROR
    #define OS_PlatformTermiEvent   ELMO_INT32

    #ifdef     OUT
        #undef OUT
    #endif
    
    #ifdef     IN
        #undef IN
    #endif
    
    #ifdef  TRUE
        #undef  TRUE
    #endif
    
    #define TRUE    1
    
    #ifdef  FALSE
        #undef  FALSE
    #endif
    
    #define FALSE   0

    
    #define ERROR                   -1              /* For IPC, in RPC it define in one of sys header E.G. host.h */
    
            /* as in VxWorks */
    #define OS_PLATFORM_INVALID_SOCKET  ERROR
    #define OS_PLATFORM_SOCKET_ERROR    ERROR
//    #define TCP_NODELAY                 0x01      /* define in TCP.h */

    
    typedef struct 
    {
        ELMO_UINT64  ulliDI;
        ELMO_UINT16  usStatus;
        ELMO_INT16   usErrorID;
    }MMC_READDI_OUT;

    typedef struct
    {
        ELMO_UINT64 ulliDO;
    }MMC_WRITEDO_IN;

    #include "datastructs.h"
    #include "OS_PlatformLinuxIpcfb_datastruct.h"


    
    ///////////////////////////////////////////////////////////////////////////////
    /// \struct MMC_IPC_SHM_IN_STRUCT
    /// \brief IPC host to target transaction data structure
    ///
    /// This structure defines host to target shared memory transaction for IPC.
    ///////////////////////////////////////////////////////////////////////////////
    typedef struct shared_memory_region1
    {
        MMC_IPC_BASIC_IN_STRUCT basic_in ;
        MOTION_FUNCS_INNER_ARGS inner_args;
        ELMO_UINT8              in_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
    }LINUX_ALIGNMENT MMC_IPC_SHM_IN_STRUCT;
    
    
    ///////////////////////////////////////////////////////////////////////////////
    /// \struct MMC_IPC_SHM_OUT_STRUCT
    /// \brief IPC target to host transaction data structure
    ///////////////////////////////////////////////////////////////////////////////
    typedef struct shared_memory_out_region1
    {
        ELMO_UINT16 numerator_id;
        ELMO_UINT16 data_size;
        ELMO_UINT16 dummy[2];
        MOTION_FUNCS_INNER_ARGS inner_args;                         // why is this here ? Benji !!!!
        ELMO_UINT8  out_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
    }LINUX_ALIGNMENT MMC_IPC_SHM_OUT_STRUCT;
    
    
    ///////////////////////////////////////////////////////////////////////////////
    /// \struct MMC_IF_STRUCT
    /// \brief Connection interface data structure
    ///////////////////////////////////////////////////////////////////////////////
    
    typedef void(*RPC_HANDLER)(void *rpc_pkt);
    
    typedef struct
    {
        ELMO_UINT32                  magic;
        MMC_CONNECTION_TYPE         conn_type;
        MMC_CONNECTION_PARAM_STRUCT conn_param;
        ELMO_INT32                   sock;
        ELMO_INT32                   shm_fd;
        ELMO_PUINT8                  ipc_shm_addr;
        ELMO_INT32                   ipc_server_semid;
        ELMO_INT32                   ipc_client_semid;
        ELMO_INT32                   ipc_conn_num;
        ELMO_UINT32                  msg_numerator;
        ELMO_PVOID                   snd_msg;
        OS_CRITIC_SEC_IMPL          snd_msg_mutex;
        // HH not in use... pthread_mutexattr_t         snd_msg_mutex_attr;
        ELMO_INT32                   sockListen ;
        //MMC_CB_FUNC pCbFunc ;MB support to MMCPP library. @YL 27-06-2011
        MMC_MB_CLBK                 pCbFunc ;
        MMC_MB_CLBK                 pCbFuncSecondary ;
    //    OS_SIGNL_EVENT_IMPL         hTerminateEvent ;
        ELMO_INT32                   hTerminateEvent ;
        pthread_attr_t              hConnectThreadAttr;
        pthread_t                   hConnectThread;
        ELMO_INT32                   udpport ;
        ELMO_INT32                   iActiveAxesNum;
        MMC_UDP_DATA_FIFO_STRUCT *  stUDPDataFIFO[MMC_MAX_NUM_AXIS] ;
        ELMO_INT8                    cLastError[512] ;
        OS_CRITIC_SEC_IMPL          lpCriticalSectionUDP;
        // HH not in use... pthread_mutexattr_t         lpCriticalSectionUDPAttr;
        ELMO_INT32                   db_shm_fd;
        ELMO_PUINT8                  ipc_db_shm_addr;
        ELMO_PUINT8                  shm_ptr;
        ELMO_UINT8                   ucIsSYNCTimerActive;
        ELMO_UINT8                   ucSYNCTimerExit;
        ELMO_INT32                   nc_drv_fd;
                                                                /* GMAS Endian type relating to the Cpu running */
                                                                /* user program => SAME OR DIFFERENT ENDIAN     */
                                                                /* Use in RPC for direct whether GMAS bytes in  */
                                                                /* sensitive to endian should swap.             */
                                                                /* Put also in IPC - for be similar to RPC...   */
        eGMAS_ENDIAN_TYPE           eGmasEndianType;

        ELMO_INT32                  blocksock ;                 /* Not in use in IPC... */
        OS_CRITIC_SEC_IMPL          lpCriticalSectionSendRcv;   /* Not in use in IPC... */
        ELMO_UINT8                  ucSendAsyncEventFlag ;


		ELMO_UINT8 					ucDeviceType;
		ELMO_UINT8 					ucSetRTUserCallback;

        MMC_IPC_SHM_IN_STRUCT       args_in; //@ZB IEC realted variable
        RPC_HANDLER *               pIECExeuteCmd;
        pthread_mutex_t *           connection_lock;
        ELMO_INT8                   dest_ip[IP_ADDR_SIZE+1];    /* Dest ip for rpc calls*/

		ELMO_UINT8 					ucPause;		 /*!< aflag for IEC connection. active(0), pause(1). 2YL 20210303*/

    } MMC_IF_STRUCT;


                    /* ============================== *\
                    |* Mod Bus Global data and manage *|
                    \* ============================== */
#define MODBUS_TABLE_SIZE           32767                   // in short units (2 bytes)
#define MODBUS_REGISTERS_LAST_INDEX MODBUS_TABLE_SIZE-1024  // in short units (2 bytes)
#define MODBUS_COILS_LAST_INDEX     MODBUS_TABLE_SIZE-512   // in short units (2 bytes)
#define MODBUS_COILS_TABLE_SIZE     1024                    // chars - 512 shorts
#define MODBUS_INPUTS_TABLE_SIZE    1024                    // chars - 512 shorts
                                                /* Mbus Mutex location on Mbus Share memory. Index      */
                                                /* when looking on mBus shareMemory as array of chars   */
#define MUTEX_SM_LOCATION           0
//
                        // MBus share memory ID
extern ELMO_INT32   g_mbus_shmid;
                        // Pointer to Mbus shm area (start of)
                        // This shm Including: Mutex; Mbus Registers; Mbus Coiles; mbus "inputs"
extern ELMO_PINT8   g_pshm_addr;
                        // Pointer to Mbus Registers; Coiles; mbus "inputs" (on mbus share memory)
extern ELMO_PINT16  g_mmc_modbus_device_Data;
                        // BitSet has 512 shorts=1024 chars(shorts) from 31743-32255
extern ELMO_PINT8   CoilsSet;
                        // InputSet has 512 shorts=1024 chars(shorts) from 32255-32767
extern ELMO_PINT8   InputSet;
                        // Size of share memory sigment (intended for Mbus device and its mutex...)
extern ELMO_INT32   g_segment_size;         /* size in bytes    */
                        // Size on mbus shm keeping for mbus mutex sync (may be more of
                        // mutex data type size, E.g: well alinment for efficiant consideration)
extern ELMO_INT32   g_mutex_keeping_size;   /* size in bytes    */
                        // Pointer to "global data area" laing on IPC shm (E.g. mbus flags...)
extern MMC_GSHM_STRUCT *    g_gshm_data;
                        // modbus lock
extern pthread_mutex_t *   g_pmbus_lock;
//
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_IPCmodbusPrepareResourceMap()
/// \brief This function prepare the resources for access MBus data,
///                map the process to MBus share memory, and initialize
///                 global variable using for following access the MBus.
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 MMC_IPCmodbusPrepareResourceMap();
//

    
    MMC_LIB_API ELMO_INT32 SYNCTimerThreadFunc (ELMO_PVOID arg);
    MMC_LIB_API ELMO_INT32 MMC_DestroySYNCTimer(IN MMC_CONNECT_HNDL hConn);
    MMC_LIB_API ELMO_INT32 MMC_CreateSYNCTimer (IN MMC_CONNECT_HNDL hConn, IN MMC_SYNC_TIMER_CB_FUNC func, IN ELMO_UINT16 usSYNCTimerTime);
    
    MMC_LIB_API ELMO_PINT8 MMC_MapShmPtr     (MMC_CONNECT_HNDL hConn);
    MMC_LIB_API ELMO_INT32 MMC_UnmapShmPtr   (ELMO_PINT8 pShmPtr);
    MMC_LIB_API ELMO_INT32 MMC_GetCmdStatusEx(MMC_CONNECT_HNDL hConn, ELMO_UINT32 uiFbHndl, ELMO_UINT32 uiParamOffset, ELMO_PUINT32 uiStatus);
    
    MMC_LIB_API ELMO_INT32 GetShmSize (MMC_CONNECT_HNDL hConn, MMC_GETSHMSIZE_IN* pInParam, MMC_GETSHMSIZE_OUT* pOutParam);
    MMC_LIB_API ELMO_INT32 MMC_IECCtrl(MMC_CONNECT_HNDL hConn, MMC_IECCTRL_IN   * pInParam, MMC_IECCTRL_OUT   * pOutParam);
    
                /// Orginal was in iec.h
                /// Send IEC message and receive response data. Return - 0 if success, error_id in case of error
    ELMO_INT32 MMC_IECSndMsg(
                IN MMC_IF_STRUCT*       pMmcIf,
                IN MMC_AXIS_REF_HNDL    hAxisRef,
                IN ELMO_INT32           iFuncId,
                IN ELMO_PVOID           pInParam,
                IN ELMO_INT16           iInSize,
                IN ELMO_INT16           iOutSize,
                OUT ELMO_PVOID          pOutParam);

                /// Orginal was in MMC_general_IEC_API.h
    #ifdef __cplusplus
     extern "C" {
    #endif
    

    MMC_LIB_API ELMO_INT32 MMC_IECInitConnection (OUT MMC_CONNECT_HNDL* pHndl, ELMO_UINT32 inRemotFuncArr, pthread_mutex_t* pConnLock);
    MMC_LIB_API ELMO_INT32 MMC_IECUdpChannelClose(IN  MMC_CONNECT_HNDL  hConn);
    MMC_LIB_API ELMO_INT32 MMC_CloseConnection   (IN  MMC_CONNECT_HNDL  hConn);

    MMC_LIB_API ELMO_INT32 MMC_IECUdpChannelInit (IN  MMC_CONNECT_HNDL  hConn);
    MMC_LIB_API ELMO_INT32 MMC_IECUdpCopyFifo    (IN  MMC_CONNECT_HNDL  hConn, ELMO_PUINT8 ucData,ELMO_UINT32 uiAxRef,ELMO_INT32 iSize);
    MMC_LIB_API ELMO_INT32 MMC_IECSetEvent       (IN  MMC_CONNECT_HNDL  hConn, ELMO_UINT32 uiAxRef);


    #ifdef __cplusplus
     }
    #endif



    #include "blocksock.h"
    #include "ipc.h"

        /* OS_PLATFORMLINUXIPC_H_ */
#endif


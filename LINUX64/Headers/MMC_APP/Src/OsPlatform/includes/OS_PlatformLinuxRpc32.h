////////////////////////////////////////////////////////////////////////////////
/// file os_platformLinuxIpc
/// Name        : OS_platformLinuxRpc32.h
/// Author      : Haim Hillel
/// Created on  : 07Feb2013
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.4.0 Updated 11Sep2017 Haim H.
///               0.4.2 Updated 26Aug2019 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain GMAS LINUX RPC Operating System Platform dependencies code.
///               The file is selected to be including in OS_Platform.h in case target select to be LINUX RPC.
////////////////////////////////////////////////////////////////////////////////

#ifndef OS_PLATFORMLINUXRPC32_H_
#define OS_PLATFORMLINUXRPC32_H_

    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <sys/stat.h>
    #include <sys/mman.h>
    #include <sys/socket.h>
    #include <sys/sem.h>
    #include <sys/time.h>
    #include <sys/ioctl.h>
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

#define HANDLE  sem_t

                                /* HH Shuld be define in <semaphore.h> but seem not efected... */
 ELMO_INT32 sem_timedwait (sem_t *sem, const struct timespec *abstime);
    
    #define MMC_LIB_API
    #define OS_SIGNL_EVENT_IMPL     sem_t
    #define OS_CRITIC_SEC_IMPL      pthread_mutex_t
    #define OS_PLATFORM_SINGOBJ_TO  ETIMEDOUT
    #define OS_PlatformTermiEvent   sem_t

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
//    #define TCP_NODELAY                 0x01        /* For IPC which acltualy not in use, for RPC it define in TCP.h */

    

            typedef struct 
                {
                ELMO_UINT64  ulliDI;
                ELMO_UINT16  usStatus;
                ELMO_INT16   usErrorID;
                }MMC_READDI_OUT;

            typedef struct
                {
                ELMO_UINT64  ulliDO;
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
    ELMO_UINT16              numerator_id;
    ELMO_UINT16              data_size;
    ELMO_UINT16              dummy[2];
    ELMO_UINT8               out_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
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

        ELMO_DOUBLE                  dData[190] ;
        ELMO_INT32                   blocksock ;
        ELMO_INT32                   sockListen ;
        ELMO_ULINT32                 tID ;
        ELMO_INT32                   udpport ;

        pthread_attr_t              hConnectThreadAttr;
        pthread_t                   hConnectThread;
        OS_SIGNL_EVENT_IMPL         hTerminateEvent ;

        ELMO_INT32                   iActiveAxesNum;
        MMC_UDP_DATA_FIFO_STRUCT*   stUDPDataFIFO[MMC_MAX_NUM_AXIS] ;

        OS_CRITIC_SEC_IMPL          lpCriticalSectionUDP ;
        OS_CRITIC_SEC_IMPL          lpCriticalSectionSendRcv;

        MMC_CB_FUNC                 pCbFunc ;
        MMC_CB_FUNC                 pCbFuncSecondary ;
        ELMO_INT32                   ipc_conn_num;
        ELMO_UINT32                  msg_numerator;
        ELMO_PVOID                   snd_msg;
                                                                /* GMAS Endian type relating to the Cpu running */
                                                                /* user program => SAME OR DIFFERENT ENDIAN     */
                                                                /* Use in RPC for direct whether GMAS bytes in  */
                                                                /* sensitive to endian should swap.             */
                                                                /* Put also in IPC - for be similar to RPC...   */
        eGMAS_ENDIAN_TYPE           eGmasEndianType;
        ELMO_INT8                    cLastError[512] ;
        ELMO_UINT8                   ucSendAsyncEventFlag ;

        ELMO_UINT8                  ucDeviceType;
        ELMO_INT8                   dest_ip[IP_ADDR_SIZE + 1];  /* Dest ip for rpc calls */

    } LINUX_ALIGNMENT   MMC_IF_STRUCT;

    MMC_LIB_API ELMO_INT32 MMC_DestroySYNCTimer(IN MMC_CONNECT_HNDL hConn);
    MMC_LIB_API ELMO_INT32 MMC_CreateSYNCTimer (IN MMC_CONNECT_HNDL hConn, IN MMC_SYNC_TIMER_CB_FUNC func, IN ELMO_UINT16 usSYNCTimerTime);

    #include "blocksock.h"


        /* OS_PLATFORMLINUXRPC32_H_ */
#endif


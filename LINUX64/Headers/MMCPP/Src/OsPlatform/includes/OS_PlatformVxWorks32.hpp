////////////////////////////////////////////////////////////////////////////////
/// file os_platformVxWorks
/// Name        : OS_platformVxWorks.hpp
/// Author      : Haim Hillel
/// Created on  : 01Mar2015
/// Version     : 0.0.1
///               0.3.0 Updated 03Aug2015 Haim H. support Littlendian & Bigendian GMAs.
/// Copyright   : Your copyright notice
/// Description : This file contain GMAS RPC VxWorks Operating System  Platform dependencies.
///               The file is selected to be including in OS_Platform.h in case target select to be VxWorks
////////////////////////////////////////////////////////////////////////////////

#ifndef OS_PLATFORMVXWORKS_HPP_
#define OS_PLATFORMVXWORKS_HPP_ 

    #include <VxWorks.h>
    #include <taskLib.h>
    #include <pthread.h>
    
    #include <sockLib.h>
    #include <socket.h>
    #include <selectLib.h>
    
    #include <netLib.h>
    #include <netinet\tcp.h>
    #include <netinet\in.h>
    #include <inetLib.h>
    
    #include <semLib.h> 
    #include <semaphore.h>
    
    #include <taskLib.h>
    #include <tickLib.h>
    
    #include <time.h>
    #include <errno.h>
    #include <stdio.h>
    
    #include <float.h>
    
    #include <hostLib.h>
    #include <sysLib.h>
    #include <stdlib.h>
    #include <iostream>
    #include <string>
    #include <fstream>

    #define DLLMMCPP_API
    #define MMC_LIB_API
	
    #define OS_SIGNL_EVENT_IMPL     SEM_ID
    #define OS_CRITIC_SEC_IMPL      SEM_ID
    #define OS_PLATFORM_SINGOBJ_TO  ERROR
    #define OS_PlatformTermiEvent   SEM_ID
    
            /* Define Sokcet fun return code symbols behaver as in VxWorks */
    #define OS_PLATFORM_INVALID_SOCKET  ERROR
    #define OS_PLATFORM_SOCKET_ERROR    ERROR



        typedef struct 
            {
            ELM_INT4U       ulliVal;
            ELMO_UINT16      usStatus;
            ELMO_INT16       usErrorID;
            }MMC_GENERALPARAMPDOREAD_OUT;

        typedef union _unGeneralPDOWriteData
            {
            ELMO_UINT8       pData[8];
            ELMO_UINT64      ulliVal;
            }unGeneralPDOWriteData;

        typedef struct
            {
            ELMO_UINT64      ulliDI;
            ELMO_UINT16      usStatus;
            ELMO_INT16       usErrorID;
            }MMC_READDI_OUT;

        typedef struct
            {
            ELMO_UINT64      ulliDO;
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
    ELMO_UINT8               in_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
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
        ELMO_UINT32          magic;
        MMC_CONNECTION_TYPE conn_type;
        MMC_CONNECTION_PARAM_STRUCT conn_param;

        ELMO_DOUBLE          dData[190] ;
        ELMO_INT32           blocksock ;
        ELMO_INT32           sockListen ;
        ELMO_ULINT32         tID ;
        ELMO_INT32           udpport ;

        ELMO_INT32           hConnectThread ;
        OS_SIGNL_EVENT_IMPL hTerminateEvent ;

        ELMO_INT32           iActiveAxesNum;
        MMC_UDP_DATA_FIFO_STRUCT* stUDPDataFIFO[MMC_MAX_NUM_AXIS] ;

        OS_CRITIC_SEC_IMPL  lpCriticalSectionUDP ;
        OS_CRITIC_SEC_IMPL  lpCriticalSectionSendRcv;

        MMC_CB_FUNC         pCbFunc ;
        ELMO_INT32           ipc_conn_num;
        ELMO_UINT32          msg_numerator;
        ELMO_PVOID           snd_msg;
        ELMO_INT8            cLastError[512] ;
        ELMO_UINT8           ucSendAsyncEventFlag ;
    } LINUX_ALIGNMENT       MMC_IF_STRUCT;


    #include "blocksock.h"


        /* OS_PLATFORMVXWORKS_HPP_  */
#endif


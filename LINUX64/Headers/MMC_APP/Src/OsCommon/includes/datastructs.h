////////////////////////////////////////////////////////////////////////////////
/// \file datastructs.h
/// Name        : datastructs.h
/// Author      : Arcady Chechik
/// Created on  : Jun 9, 2008
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.4.0 Updated 11Sep2017 Haim H.
///               0.4.2 Updated 26Aug2019 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain basic RPC/IPC communication structures
////////////////////////////////////////////////////////////////////////////////

#ifndef _DATASTRUCTS_
#define _DATASTRUCTS_

#include "MMC_definitions.h"


#ifdef NULL
#undef NULL
    #define NULL 0
#endif



#define IPC_MSG_MAX_LENGTH                  260

#ifdef _PLATINUM
	#define IPC_MSG_IN_OUT_ARGS_MAX_SIZE 		1500
#else
	#define IPC_MSG_IN_OUT_ARGS_MAX_SIZE 		1000
#endif


#define IPC_SOCKET_PATH                     "/var/MMC/socket/fae-motion-srv"
#define IPC_UDP_SOCKET_PATH                 "/var/MMC/socket/fae-motion-udp-srv"
#define SHM_NAME1                           "/ipc_shm1_name"
#define IPC_MSG_S_SEM_NAME_LENGTH_SIZE      1
#define IPC_SEM_NAME_MAX_LENGTH             80
#define IPC_SEM_NAME_MIN_LENGTH             2
#define IPC_MSG_CONN_NUM_LENGTH             sizeof(ELMO_INT32)
#define IPC_MIRR_PARAM_ADDR_LENGTH          sizeof(ELMO_UINT32)
//
#define IPC_MSG_S_SEM_NAME_LENGTH_OFFSET    0
#define IPC_MSG_S_SEM_NAME_OFFSET           (IPC_MSG_S_SEM_NAME_LENGTH_OFFSET + IPC_MSG_S_SEM_NAME_LENGTH_SIZE)
#define IPC_MSG_C_SEM_NAME_LENGTH_OFFSET    (IPC_MSG_S_SEM_NAME_OFFSET + IPC_SEM_NAME_MAX_LENGTH)
#define IPC_MSG_C_SEM_NAME_OFFSET           (IPC_MSG_C_SEM_NAME_LENGTH_OFFSET + IPC_MSG_S_SEM_NAME_LENGTH_SIZE)
#define IPC_MSG_CONN_NUM_OFFSET             (IPC_MSG_C_SEM_NAME_OFFSET + IPC_SEM_NAME_MAX_LENGTH)
#define IPC_MSG_MIRR_PARAM_ADDR_OFFSET      (IPC_REG_AXES_NUM_OFFSET + IPC_REG_AXES_NUM_LENGTH)

#define MMC_REMOTE_FUNC_MOTION_FUNC_MAX_INDEX               20

#define IPC_MSG_FUNC_CODE_ID_OPEN_UDP_RESPONSE_CHANNEL      102
#define IPC_MSG_FUNC_CODE_ID_CLOSE_UDP_RESPONSE_CHANNEL     103
#define IPC_MSG_FUNC_CODE_ID_CLOSE_IPC_CHANNEL              104

#define MMC_MAX_CONNECTION_NUMBER                           20

#define SEND_GET_SYNC_TIMEOUTms                            3000



#define MMC_MAX_NUM_AXIS                                    127

                        /* Flag Values: marks the status of mbus share memory   */
#define MMC_MBUS_SHM_AVAIL          0x1111
#define MMC_MBUS_SHM_ISNOT_AVAIL    0x0000

///////////////////////////////////////////////////////////////////////////////
// NC driver - IOCTLs
///////////////////////////////////////////////////////////////////////////////

// Use 'k' as magic number
#define NC_DRV_IOC_MAGIC  'k'

#define NC_IOCBEGINRECORDING                _IO(NC_DRV_IOC_MAGIC,   0)
#define NC_IOCSTOPRECORDING                 _IO(NC_DRV_IOC_MAGIC,   1)
#define NC_IOCDEBUG                         _IO(NC_DRV_IOC_MAGIC,   2)
#define NC_IOCSTARTHRTIMER                  _IOW(NC_DRV_IOC_MAGIC,  3, ELMO_UINT32)
#define NC_IOCSTOPHRTIMER                   _IO(NC_DRV_IOC_MAGIC,   4)
#define NC_IOCREGNCTASK                     _IOW(NC_DRV_IOC_MAGIC,  5, ELMO_UINT8)
#define NC_IOCUNREGNCTASK                   _IO(NC_DRV_IOC_MAGIC,   6)
#define NC_IOCPOWERENABLE                   _IOW(NC_DRV_IOC_MAGIC,  7, ELMO_UINT32)
#define NC_IOCPOWERENABLEDBG                _IOW(NC_DRV_IOC_MAGIC,  8, ELMO_UINT32)
#define NC_IOCSINTABLEINIT                  _IOW(NC_DRV_IOC_MAGIC,  9, ELMO_UINT32)
#define NC_IOCMMINIT                        _IOW(NC_DRV_IOC_MAGIC,  10, ELMO_UINT32)
#define NC_IOCGETTRFUNC                     _IOWR(NC_DRV_IOC_MAGIC, 11, ELMO_UINT32)
#define NC_IOCGETCANCOMMEVENTS              _IOW(NC_DRV_IOC_MAGIC,  12, ELMO_UINT32)
#define NC_IOCSETSYNCTIME                   _IOW(NC_DRV_IOC_MAGIC,  13, ELMO_UINT16)
#define NC_IOCSETHEARTBEATTIMEFACTOR        _IOW(NC_DRV_IOC_MAGIC,  14, ELMO_UINT32)
#ifdef _PRM_SNAPSHOT_
    #define NC_IOCGETPARAMMIRRORADDR        _IOW(NC_DRV_IOC_MAGIC,  15, ELMO_UINT32)
#endif
#define NC_IOCSETGPIO                       _IOW(NC_DRV_IOC_MAGIC,  16, ELMO_UINT8)
#define NC_IOCCLEARGPIO                     _IOW(NC_DRV_IOC_MAGIC,  17, ELMO_UINT8)
#define NC_IOCSYNCTIMER                     _IOW(NC_DRV_IOC_MAGIC,  18, ELMO_UINT16)
#define NC_IOCSYNCTIMERSTARTSTOP            _IOW(NC_DRV_IOC_MAGIC,  19, ELMO_UINT8)
#define NC_IOCCOMMCONFIGMODEENABLE          _IO(NC_DRV_IOC_MAGIC,   20)
#define NC_IOCCOMMCONFIGMODEDISABLE         _IO(NC_DRV_IOC_MAGIC,   21)

#ifdef _PLATINUM
	#define NC_IOSETCOREAFFINITY			_IO(NC_DRV_IOC_MAGIC, 	33)
#endif

///////////////////////////////////////////////////////////////////////////////
/// \struct Global flags structure on IPC Share memory (not related to specific IPC)
/// \brief Command common data
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_gshm_struct
{
    ELMO_ULINT32    mbusShmGflags;
    ELMO_ULINT32    shmGflag_2;
    ELMO_ULINT32    shmGflag_3;
    ELMO_ULINT32    shmGflag_4;
    ELMO_INT8       pad[48];
} MMC_GSHM_STRUCT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MOTION_FUNCS_INNER_ARGS
/// \brief Command common data
///////////////////////////////////////////////////////////////////////////////
typedef struct motion_funcs_inner_args
{
    ELMO_UINT32  uiConnIndex;            ///< Connection index
    ELMO_PVOID   pAxisRef;               ///< Pointer to Axis data structure
    ELMO_UINT16  usNumerator;            ///< Command enumerator
    ELMO_UINT16  usOutputDataSize;       ///< Size of output data
    ELMO_UINT16  usFuncID;               ///< Command function ID
    ELMO_UINT8   ucConnType;             ///< Connection type (IPC/RPC)
    ELMO_UINT8   dummy;                  ///< added for whole 16-byte size
}MOTION_FUNCS_INNER_ARGS;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_IPC_BASIC_IN_STRUCT
/// \brief Basic common IPC/RPC command header
///////////////////////////////////////////////////////////////////////////////
typedef struct basic_input
{
    ELMO_UINT16 func_code_id;       ///< Function ID code
    ELMO_UINT16 numerator_id;       ///< Command enumerator
    ELMO_UINT16 data_size;          ///< Command data size
    ELMO_UINT16 axis_ref;           ///< Handle of command related axis.
}LINUX_ALIGNMENT MMC_IPC_BASIC_IN_STRUCT;




///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESP_HEADER_STRUCT
/// \brief Common responce data structure
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16  usErrorID;      ///< Returned command error ID.
}LINUX_ALIGNMENT MMC_RESP_HEADER_STRUCT;

#define MAX_UDP_FIFO_SIZE   16
#define MX_UDP_FIFO_MSG_SIZE ((ELMO_INT32)sizeof(MMC_CAN_REPLY_DATA_OUT))
#define MX_UDP_FIFO_MSG_EX_SIZE sizeof(MMC_CAN_REPLY_DATA_EX_OUT)

typedef struct {
    ELMO_INT32  iUDPFIFOSize ;
    ELMO_INT32  iLen;
    ELMO_UINT8  ucData[MX_UDP_FIFO_MSG_EX_SIZE];
    ELMO_UINT16 usCanId;
    OS_SIGNL_EVENT_IMPL  synchronised_communication_event;

} LINUX_ALIGNMENT MMC_UDP_DATA_FIFO_STRUCT;


#endif

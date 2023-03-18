////////////////////////////////////////////////////////////////////////////////
/// \file MMC_host_comm_API.h
/// Name        : MMC_host_comm_API.h
/// Author      : Barak R
/// Created on  : April 19, 20010
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_HOST_COMM_API_H_
#define MMC_HOST_COMM_API_H_

#ifdef __cplusplus
 extern "C" {
#endif

// Modbus Definitions
#define MODBUS_IPC_READ_VALUES           250    ///< maximum number of items to read from modbus register table
#define MODBUS_IPC_WRITE_VALUES          250    ///< maximum number of items to write to modbus register table


/////  structures

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSREADHOLDINGREGISTERSTABLE_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32  startRef;
    ELMO_INT32  refCnt;
}MMC_MODBUSREADHOLDINGREGISTERSTABLE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSREADHOLDINGREGISTERSTABLE_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT16  regArr[MODBUS_IPC_READ_VALUES];
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;

}MMC_MODBUSREADHOLDINGREGISTERSTABLE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32  startRef;
    ELMO_INT32  refCnt;
    ELMO_INT16  regArr[MODBUS_IPC_WRITE_VALUES];

}MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSSTARTSERVER_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 id;
}MMC_MODBUSSTARTSERVER_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSSTARTSERVER_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_MODBUSSTARTSERVER_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSSTOPSERVER_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  dummy;
}MMC_MODBUSSTOPSERVER_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSSTOPSERVER_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_MODBUSSTOPSERVER_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSISRUNNING_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8  dummy;
}MMC_MODBUSISRUNNING_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSISRUNNING_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 isrunning;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_MODBUSISRUNNING_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSREADCOILS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32  startRef;
    ELMO_INT32  refCnt;
}MMC_MODBUSREADCOILS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSREADCOILS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
    ELMO_INT8   coilsArr[MODBUS_IPC_READ_VALUES];
}MMC_MODBUSREADCOILS_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSREADCOILS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32  startRef;
    ELMO_INT32  refCnt;
    ELMO_INT8   coilsArr[MODBUS_IPC_WRITE_VALUES];
}MMC_MODBUSWRITECOILS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSWRITECOILS_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_MODBUSWRITECOILS_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSREADINPUTS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32 startRef;
    ELMO_INT32 refCnt;
}MMC_MODBUSREADINPUTS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MODBUSREADINPUTS_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
    ELMO_INT8   inputsArr[MODBUS_IPC_READ_VALUES];
}MMC_MODBUSREADINPUTS_OUT;

////// functions

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MbusReadHoldingRegisterTable (
///
///
/// \brief      This function reads part of modbus register table
/// \param  hConn - [IN] Connection handle.
/// \param  pInParam - [IN] Pointer to modbus holding reference count and number of parameters
/// \param  pOutParam - [OUT] Pointer to modbus holding register table output parameters
/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MbusReadHoldingRegisterTable (
        IN  MMC_CONNECT_HNDL                            hConn,
        IN  MMC_MODBUSREADHOLDINGREGISTERSTABLE_IN*     pInParam,
        OUT MMC_MODBUSREADHOLDINGREGISTERSTABLE_OUT*    pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MbusWriteHoldingRegisterTable (
///
///
/// \brief      This function writes part of modbus register table
/// \param  hConn - [IN] Connection handle.
/// \param  pInParam - [IN] Pointer to modbus holding register table input parameters
/// \param  pOutParam - [OUT] Pointer output parameters
/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MbusWriteHoldingRegisterTable (
        IN  MMC_CONNECT_HNDL                            hConn,
        IN  MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN*    pInParam,
        OUT MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_OUT*   pOutParam);
//
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MbusStartServer (
///
///
/// \brief      This function starts the modbus server thread
/// \param  hConn - [IN] Connection handle.
/// \param  pInParam - [IN] Pointer to input parameters
/// \param  pOutParam - [OUT] Pointer to output parameters
/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MbusStartServer (
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_MODBUSSTARTSERVER_IN*   pInParam,
        OUT MMC_MODBUSSTARTSERVER_OUT*  pOutParam);
//
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MbusStopServer (
///
///
/// \brief      This function stops the modbus server thread
/// \param  hConn - [IN] Connection handle.
/// \param  pInParam - [IN] Pointer to input parameters
/// \param  pOutParam - [OUT] Pointer to output parameters

/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MbusStopServer (
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_MODBUSSTOPSERVER_IN*    pInParam,
        OUT MMC_MODBUSSTOPSERVER_OUT*   pOutParam);
//
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MbusIsRunning (
///
///
/// \brief      This function stops the modbus server thread
/// \param  hConn - [IN] Connection handle.
/// \param  pInParam - [IN] Pointer to input parameters
/// \param  pOutParam - [OUT] Pointer output parameters including isrunning which equals 1, if modbus is running

/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MbusIsRunning (
        IN MMC_CONNECT_HNDL             hConn,
        IN  MMC_MODBUSISRUNNING_IN*     pInParam,
        OUT MMC_MODBUSISRUNNING_OUT*    pOutParam);
//
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MbusReadCoilsTable (
///
///
/// \brief      This function reads part of modbus register table
/// \param  hConn - [IN] Connection handle.
/// \param  pInParam - [IN] Pointer to modbus holding reference count and number of parameters
/// \param  pOutParam - [OUT] Pointer to modbus holding coils table array and output parameters

/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MbusReadCoilsTable (
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_MODBUSREADCOILS_IN*     pInParam,
        OUT MMC_MODBUSREADCOILS_OUT*    pOutParam);
//
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MbusWriteCoilsTable (
///
///
/// \brief      This function writes part of modbus register table
/// \param  hConn - [IN] Connection handle.
/// \param  pInParam - [IN] Pointer to modbus holding coils table input parameters
/// \param  pOutParam - [OUT] Pointer to output parameters

/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MbusWriteCoilsTable (
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_MODBUSWRITECOILS_IN*    pInParam,
        OUT MMC_MODBUSWRITECOILS_OUT*   pOutParam);
//
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MbusReadInputsTable (
///
///
/// \brief      This function writes part of modbus register table
/// \param  hConn - [IN] Connection handle.
/// \param  pInParam - [IN] Pointer to modbus input parameters, start reference, and reference count
/// \param  pOutParam - [OUT] Pointer to output parameters, including inputs table parameters

/// \return return - 0 if failed
///                  error_id in case of error
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MbusReadInputsTable (
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_MODBUSREADINPUTS_IN*    pInParam,
        OUT MMC_MODBUSREADINPUTS_OUT*   pOutParam);
//
//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif

#endif /* MMC_HOST_COMM_API_H_*/

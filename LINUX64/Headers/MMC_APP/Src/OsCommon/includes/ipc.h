////////////////////////////////////////////////////////////////////////////////
/// \file ipc.h
/// Name        : ipc.h
/// Author      : Arcady Chechik
/// Created on  : Jun 9, 2008
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
/// Copyright   : Your copyright notice
/// Description : This file contain IPC communication definitions
////////////////////////////////////////////////////////////////////////////////

#ifndef _IPC_FUNCS_
#define _IPC_FUNCS_




////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CreateIpcConnect(
///             IN MMC_IF_STRUCT* pMmcIf,
///             IN char* pSockPath)
/// \brief This function create new IPC connection session.
/// \param pMmcIf       - [IN] Pointer to IPC connection structure .
/// \param pSockPath    - [IN] Path to named socket.
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
int MMC_CreateIpcConnect(
                IN MMC_IF_STRUCT*   pMmcIf,
                IN ELMO_PINT8        pSockPath);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CloseIpcConnect(
///             IN MMC_IF_STRUCT* pMmcIf)
/// \brief This function close IPC connection session.
/// \param pMmcIf - [IN] Pointer to IPC connection structure .
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
int MMC_CloseIpcConnect(
                IN MMC_IF_STRUCT* pMmcIf);


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_IpcSndMsg(
///             IN MMC_IF_STRUCT* pMmcIf,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN int iFuncId,
///             IN void* pInParam,
///             IN short iInSize,
///             IN short iOutSize,
///             OUT void* pOutParam)
/// \brief This function close IPC connection session.
/// \param pMmcIf   - [IN] Pointer to IPC connection structure.
/// \param hAxisRef - [IN] Relevant Axis handle.
/// \param iFuncId  - [IN] IPC Function ID
/// \param pInParam - [IN] Pointer to input parameter structure.
/// \param iInSize  - [IN] Size of input data structure.
/// \param iOutSize - [IN] Size of output data structure.
/// \param pOutParam - [OUT] Pointer to output data structure.
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
int MMC_IpcSndMsg(
                IN  MMC_IF_STRUCT*      pMmcIf,
                IN  MMC_AXIS_REF_HNDL   hAxisRef,
                IN  ELMO_INT32           iFuncId,
                IN  ELMO_PVOID           pInParam,
                IN  ELMO_INT16           iInSize,
                IN  ELMO_INT16           iOutSize,
                OUT ELMO_PVOID           pOutParam);



////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_IPCInitConnection(
///             IN MMC_IPC_CONNECTION_PARAM_STRUCT sConnParam,
///             IN MMC_CB_FUNC pCbFunc,
///             OUT MMC_CONNECT_HNDL* pHndl)
/// \brief This function initiates IPC connection to MMC.
/// \param MMC_IPC_CONNECTION_PARAM_STRUCT sConnParam - [IN] Connection parameters. (Currently only Explicit connection supported).
/// \param MMC_CB_FUNC pCbFunc - [IN]
/// \param MMC_CONNECT_HNDL* pHndl - [OUT] Connection handle
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
int MMC_IPCInitConnection(
        IN  MMC_IPC_CONNECTION_PARAM_STRUCT sConnParam,
        IN  MMC_CB_FUNC                     pCbFunc ,
        OUT MMC_CONNECT_HNDL*               pHndl);


#endif  // _IPC_FUNCS_

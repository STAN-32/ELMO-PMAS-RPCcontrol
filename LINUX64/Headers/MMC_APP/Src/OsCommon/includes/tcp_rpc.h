#ifndef _TCPRPC_FUNCS_
#define _TCPRPC_FUNCS_

#include "datastructs.h"
#include "MMC_definitions.h"


ELMO_INT32 MMC_RpcSndMsg(
                IN  MMC_IF_STRUCT*      pMmcIf,
                IN  MMC_AXIS_REF_HNDL   hAxisRef,
                IN  ELMO_INT32          iFuncId,
                IN  ELMO_PVOID          pInParam,
                IN  ELMO_INT16          iInSize,
                IN  ELMO_INT16          iOutSize,
                OUT ELMO_PVOID          pOutParam);


ELMO_INT32 MMC_CreateRpcConnect(IN MMC_IF_STRUCT* pMmcIf,IN ELMO_PINT8 pSockPath, ELMO_UINT16 usPort, ELMO_PINT8 cpHostIPAddr);

ELMO_INT32 MMC_CloseRpcConnect (IN MMC_IF_STRUCT* pMmcIf);


#endif  // _TCPRPC_FUNCS_

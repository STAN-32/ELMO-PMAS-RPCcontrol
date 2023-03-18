#ifndef ENQFBSTATUS_H_
#define ENQFBSTATUS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "MMC_definitions.h"

typedef enum
{
    NC_ENQUIRE_FB_STATUS_NONE = -1,
    NC_ENQUIRE_FB_STATUS_FALSE = 0,
    NC_ENQUIRE_FB_STATUS_TRUE = 1,
    NC_ENQUIRE_FB_STATUS_MAX = 2,
} NC_ENQUIRE_FB_STATUS_ENUM;

typedef struct mmc_getenquirefbstatus_in
{
    ELMO_UINT8 ucDummy;
} MMC_GETENQUIREFBSTATUS_IN;

typedef struct mmc_getenquirefbstatus_out
{
    ELMO_UINT8 ucCurrentStatus;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
} MMC_GETENQUIREFBSTATUS_OUT;

typedef struct mmc_setenquirefbstatus_in
{
    ELMO_UINT8 ucStatus;
} MMC_SETENQUIREFBSTATUS_IN;

typedef struct mmc_setenquirefbstatus_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
} MMC_SETENQUIREFBSTATUS_OUT;

MMC_LIB_API ELMO_INT32 MMC_GetEnquireFbStatusCmd(
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_GETENQUIREFBSTATUS_IN*  pInParam,
        OUT MMC_GETENQUIREFBSTATUS_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_SetEnquireFbStatusCmd(
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_SETENQUIREFBSTATUS_IN*  pInParam,
        OUT MMC_SETENQUIREFBSTATUS_OUT* pOutParam);

#ifdef __cplusplus
}
#endif
#endif // ENQFBSTATUS_H_

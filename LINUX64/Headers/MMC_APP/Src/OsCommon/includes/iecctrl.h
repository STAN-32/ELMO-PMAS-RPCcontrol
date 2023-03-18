//////////////////////////////////////////////////////////////////////////////////////////////////
/// \file MMC_iecctrl.h
/// Name        : MMC_iecctrl.h
/// Author      : Alex Kushnir
/// Created on  : Jan 1, 2012
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
/// Copyright   : Your copyright notice
/// Description : This file contains all necessary definitions to control IEC runtime
//////////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_IECCTRL_H_
#define MMC_IECCTRL_H_
#include "MMC_definitions.h"

#ifdef __cplusplus
 extern "C" {
#endif

/*
 * Options enum
 */
typedef enum mmc_iecctrl_enum
{
    eMMC_IECCTRL_OPTION_NONE,
    eMMC_IECCTRL_OPTION_RUN,
    eMMC_IECCTRL_OPTION_STOP,
    eMMC_IECCTRL_OPTION_RUN_STARTUP,
    eMMC_IECCTRL_OPTION_DISABLE_STARTUP,
    eMMC_IECCTRL_OPTION_RUNTIME_STATUS,
    eMMC_IECCTRL_OPTION_RUN_ON_STARTUP_STATUS,
    eMMC_IECCTRL_OPTION_MAX
} MMC_IECCTRL_ENUM;

typedef enum mmc_iecisrunning_enum
{
    eMMC_IEC_NOT_RUNNING,
    eMMC_IEC_RUNNING
} MMC_IECISRUNNING_ENUM;
/*
 * I/O structures
 */
typedef struct mmc_iecctrl_in
{
    MMC_IECCTRL_ENUM    eIECCtrlOption;
    ELMO_UINT8          szIECRuntimeSwitches[50];
} MMC_IECCTRL_IN;

typedef struct mmc_iecctrl_out
{
    MMC_IECISRUNNING_ENUM   eIsIECRunning;
    ELMO_UINT16             usStatus;
    ELMO_INT16              usErrorID;
} MMC_IECCTRL_OUT;


/*
 * Function prototype
 */

// HH: Define in OS_PlatformLinuxIpc32.h...
// MMC_LIB_API ELMO_INT32 MMC_IECCtrl(MMC_CONNECT_HNDL hConn, MMC_IECCTRL_IN* pInParam, MMC_IECCTRL_OUT* pOutParam);

#ifdef __cplusplus
}
#endif

#endif /* MMC_IECCTRL_H_*/

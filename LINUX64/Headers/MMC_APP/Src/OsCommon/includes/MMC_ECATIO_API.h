////////////////////////////////////////////////////////////////////////////////
/// \file MMC_ECATIO_API.h
/// Name        : MMC_ECATIO_API.h
/// Author      : Benjamin Spitzer
/// Created on  : June, 2011
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///				  0.4.0 Updated 11Sep2017 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_ECATIO_API_H
#define MMC_ECATIO_API_H
//
//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif


typedef struct  mmc_readai_in
{
    ELMO_UINT8  ucIndex;
}MMC_READAI_IN;

typedef struct mmc_readai_out
{
    ELMO_INT16  sAI;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_READAI_OUT;

typedef struct  mmc_writeao_in
{
    ELMO_INT16  sAO;
    ELMO_UINT8  ucIndex;
}MMC_WRITEAO_IN;

typedef struct  mmc_writeao_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
}MMC_WRITEAO_OUT;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ECATIOEnableDIChangedEvent(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_CONFIGREGULARPARAMEVENTPDO3_IN* pInParam,
///             OUT MMC_CONFIGREGULARPARAMEVENTPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ECATIOEnableDIChangedEvent(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_ENABLEDICHANGEDEVENT_IN*     pInParam,
        OUT MMC_ENABLEDICHANGEDEVENT_OUT*   pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ECATIODisableDIChangedEvent(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_CONFIGREGULARPARAMEVENTPDO3_IN* pInParam,
///             OUT MMC_CONFIGREGULARPARAMEVENTPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ECATIODisableDIChangedEvent(
        IN MMC_CONNECT_HNDL                 hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_DISABLEDICHANGEDEVENT_IN*    pInParam,
        OUT MMC_DISABLEDICHANGEDEVENT_OUT*  pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MMC_ECATIOReadDigitalInput(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READDI_IN* pInParam,
///             OUT MMC_READDI_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ECATIOReadDigitalInput(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_READDI_IN*       pInParam,
        OUT MMC_READDI_OUT*     pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MMC_ECATIOWriteDigitalOutput(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_WRITEDO_IN* pInParam,
///             OUT MMC_WRITEDO_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ECATIOWriteDigitalOutput(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_WRITEDO_IN*      pInParam,
        OUT MMC_WRITEDO_OUT*    pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MMC_ECATIOReadAnalogInput(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_WRITEDO_IN* pInParam,
///             OUT MMC_WRITEDO_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ECATIOReadAnalogInput(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_READAI_IN*       pInParam,
        OUT MMC_READAI_OUT*     pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MMC_ECATIOWriteAnalogOutput(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_WRITEAO_IN* pInParam,
///             OUT MMC_WRITEAO_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ECATIOWriteAnalogOutput(
        IN MMC_CONNECT_HNDL     hConn,
        IN MMC_AXIS_REF_HNDL    hAxisRef,
        IN MMC_WRITEAO_IN*      pInParam,
        OUT MMC_WRITEAO_OUT*    pOutParam) ;

//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif

#endif /* MMC_ECATIO_API_H */

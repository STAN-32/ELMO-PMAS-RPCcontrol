////////////////////////////////////////////////////////////////////////////////
/// \file MMC_EIP_API.h
/// Name        : MMC_EIP_API.h
/// Author      : HanochC
/// Created on  : 12/7/2011
/// Version     : 0.0.1
///               0.1.0 Updated 00Aug2017 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for Ethernet IP support
////////////////////////////////////////////////////////////////////////////////

#ifndef EIP_API_H
#define EIP_API_H
//
//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif


#include "platform.h"
#include "EtIpApi.h"


#define EIP_MAJ_VER                         2
#define EIP_MIN_VER                         8

#ifdef EIP_DEBUG_VERSION
    #define EIP_BUILD_VER                   11  //debug
#else
    #define EIP_BUILD_VER                   10  //release
#endif

#define NAME_MAX_LENGTH                     80

#ifndef MAX_REQUEST_DATA_SIZE
	#define MAX_REQUEST_DATA_SIZE           504
#endif

/* callbak function constants */
#define MAX_TOKEN_SIZE                      40
#define EIP_EVENT                           20
#define MAX_REQUEST_ID                      255 + 1

/* error codes */
#define EIP_ERR_OK                          0
#define EIP_ERR_NO_MEMORY_CREATED           -2000
#define EIP_ERR_REFERENCE_OUT_OF_RANGE      -2001
#define EIP_ERR_REFERENCE_NOT_FOUND         -2002
#define EIP_ERR_INVALID_INSTANCE            -2003
#define EIP_ERR_INVALID_BUFFER              -2005
#define EIP_ERR_NETPATH_FAILURE             -2006
#define EIP_ERR_INVALID_TAG_NAME            -2007
#define EIP_ERR_ILLEGAL_UNCONNECTED_REQUEST -2008
#define EIP_ERR_DATA_NOT_RECEIVED           -2009
#define EIP_ERR_SET_EVENT_FAILURE           -2010
#define EIP_ERR_SESSION_FAIL                -2011
#define EIP_ERR_EIPTASK_FAIL                -2012
#define EIP_ERR_INIT_MUTEX_FAIL             -2013
#define EIP_ERR_NO_OPEN_SESSION             -2014
#define EIP_ERR_MEMORY_CREATED              -2015
#define EIP_ERR_OPEN_FILE_FAILURE           -2016
#define EIP_ERR_PARSE_FILE_FAILURE          -2017
#define EIP_ERR_CLOSE_FILE_FAILURE          -2018
#define EIP_ERR_ASSEMBLY_CREATE_FAIL        -2019
#define EIP_ERR_DEVTAG_CREATE_FAIL          -2020
#define EIP_ERR_ADPTAG_CREATE_FAIL          -2021
#define EIP_ERR_SEMAPHORE_INIT_FAIL         -2022
#define EIP_ERR_DESTROY_MUTEX_FAIL          -2023
#define EIP_ERR_INVALID_ASSEMBLY            -2024
#define EIP_ERR_INVALID_DEVICE              -2025
#define EIP_ERR_INVALID_ADAPTER             -2026
#define EIP_ERR_REQUESTS_LIMIT_REACHED      -2027
#define EIP_ERR_OUT_OF_MEMORY               -2028
#define EIP_ERR_INVALID_NETWORK_PATH        -2029

/*
 * Device tag replay types
 */
#define DEVTAG_REPLY_OK                     0   //STACK call-back event NM_REQUEST_RESPONSE_RECEIVED
#define DEVTAG_REPLY_WAIT                   1   //no replay yet
#define DEVTAG_REPLY_TIMEOUT                2   //STACK call-back event NM_REQUEST_TIMED_OUT
#define DEVTAG_REPLY_LIMRCHD                3   //STACK call-back event NM_PENDING_REQUESTS_LIMIT_REACHED
#define DEVTAG_REPLY_NPATHERR               4   //STACK call-back event NM_REQUEST_FAILED_INVALID_NETWORK_PATH
/*---------------------------------
 * supported types
 */
 typedef enum {
     EIP_TYPE_BOOL=0,       // signed char (1 byte)
     EIP_TYPE_SINT,         // short int (2 bytes)
     EIP_TYPE_INT,          // int (4 bytes)
     EIP_TYPE_REAL          // float (4 bytes)
 } _EIP_TYPES_ENUM;

typedef ELMO_INT32 (*EIP_CALLBACK_FUNC)(ELMO_PUINT8, ELMO_INT16, ELMO_PVOID);

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_REFBYNAME_IN
/// \brief Get Tag/Assembly Handle By Name Data Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT8 cName[NAME_MAX_LENGTH];           ///< Tag/assembly name as declared in XML configuration file
}EIP_REFBYNAME_IN;


///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_REFBYNAME_OUT
/// \brief Get Tag/Assembly Handle By Name Data Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;                       ///< Returned command status.
    ELMO_INT16  usErrorID;                      ///< Returned command error ID.
    ELMO_UINT16 usTagRef;                       ///< Tag/Assembly Index Reference.
}EIP_REFBYNAME_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_REFBYINSTANCE_IN
/// \brief Get Tag/Assembly Handle By Instance Data Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_INT32 iInstance;                      ///< assembly instance as declared in XML configuration file
}EIP_REFBYINSTANCE_IN;


///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_REFBYINSTANCE_OUT
/// \brief Get Tag/Assembly Handle By Name Instance Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;                       ///< Returned command status.
    ELMO_INT16  usErrorID;                      ///< Returned command error ID.
    ELMO_UINT16 usTagRef;                       ///< Assembly Reference.
}EIP_REFBYINSTANCE_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_GETDEVTAG_IN
/// \brief Reads device tag Data input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16 usTagRef;                      ///< Tag Index Reference.
}EIP_GETDEVTAG_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_GETDEVTAG_OUT
/// \brief Reads device tag Data output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_INT32 iReqid;                         ///< Request ID.
     ELMO_UINT16 usStatus;                      ///< Returned command status.
     ELMO_INT16 usErrorID;                      ///< Returned command error ID.
}EIP_GETDEVTAG_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_GETSYNC_IN
/// \brief Reads synchronicaly device tag Data input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16 usTagRef;       ///< Tag Index Reference.
}EIP_GETSYNC_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_GETSYNC_OUT
/// \brief Reads synchronicaly device tag Data output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_LINT32    dummy;                      ///< dummy as 32bit alignment to all structure members
     ELMO_UINT16    usStatus;                   ///< Returned command status.
     ELMO_INT16     usErrorID;                  ///< Returned command error ID.
     ELMO_INT8      buffer[MAX_REQUEST_DATA_SIZE];    ///< Buffer which holds data
}EIP_GETSYNC_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_SETDEVTAG_IN
/// \brief Write device tag Data input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_LINT32 dummy;                         ///< dummy as 32bit alignment to all structure members
     ELMO_UINT16 usTagRef;                      ///< Tag Index Reference.
     ELMO_INT8   buffer[MAX_REQUEST_DATA_SIZE]; ///< Buffer which holds data
}EIP_SETDEVTAG_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_SETDEVTAG_OUT
/// \brief Write device tag Data output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_INT32 iReqid;                         ///< Device tag request id
     ELMO_UINT16 usStatus;                      ///< Returned command status.
     ELMO_INT16 usErrorID;                      ///< Returned command error ID.
}EIP_SETDEVTAG_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_CHECKREPLY_IN
/// \brief Check device tag Data reply input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_INT32 iReqid;                         ///< Device tag request id
}EIP_CHECKREPLY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_CHECKREPLY_OUT
/// \brief Check device tag Data reply input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16 usStatus;                      ///< Returned command status.
     ELMO_INT16 usErrorID;                      ///< Returned command error ID.
     ELMO_INT16 sReplyStatus;                   ///< Returned reply status flag.
}EIP_CHECKREPLY_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_READDEVTAG_IN
/// \brief Read device tag Data input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16 usTagRef;                      ///< Tag Reference.
}EIP_READDEVTAG_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_READDEVTAG_OUT
/// \brief Read device tag Data output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_LINT32 dummy;                         ///< dummy as 32bit alignment to all structure members
     ELMO_UINT16 usStatus;                      ///< Returned command status.
     ELMO_INT16 usErrorID;                      ///< Returned command error ID.
     ELMO_INT8 buffer[MAX_REQUEST_DATA_SIZE];   ///< Buffer that holds returned data.
}EIP_READDEVTAG_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_READADPTAG_IN
/// \brief Read adapter tag Data input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16 usTagRef;                      ///< Tag  Reference.
}EIP_READADPTAG_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_READADPTAG_OUT
/// \brief Read adapter tag data output data structure
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_LINT32 dummy;                         ///< dummy as 32bit alignment to all structure members
     ELMO_UINT16 usStatus;                      ///< Returned command status.
     ELMO_INT16 usErrorID;                      ///< Returned command error ID.
     ELMO_INT8 buffer[MAX_REQUEST_DATA_SIZE];   ///< Buffer that holds returned data.
}EIP_READADPTAG_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_WRITETAG_IN
/// \brief Write adapter tag Data input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_LINT32 dummy;                         ///< dummy as 32bit alignment to all structure members
     ELMO_UINT16 usTagRef;                      ///< Tag  Reference.
     ELMO_INT8 buffer[MAX_REQUEST_DATA_SIZE];   ///< Buffer that holds data to be written .
}EIP_WRITEADPTAG_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_WRITETAG_OUT
/// \brief Write adapter tag Data input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16 usStatus;                      ///< Returned command status.
     ELMO_INT16 usErrorID;                      ///< Returned command error ID.
     ELMO_INT32 iReqid;                         ///< Adapter tag request id
}EIP_WRITEADPTAG_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_SETASSEMBLY_IN
/// \brief Write assembly data input structure
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_LINT32 dummy;                         ///< dummy as 32bit alignment to all structure members
     ELMO_UINT16 usTagRef;                      ///< Assembly instance reference.
     ELMO_INT8 buffer[MAX_REQUEST_DATA_SIZE];   ///< Data Buffer to be send.
}EIP_SETASSEMBLY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_SETASSEMBLY_OUT
/// \brief Write assembly data output structure
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16 usStatus;                      ///< Returned command status.
     ELMO_INT16 usErrorID;                      ///< Returned command error ID.
}EIP_SETASSEMBLY_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_GETASSEMBLY_IN
/// \brief Reads Assembly Data input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16 usTagRef;                      ///< Assembly instance reference.
}EIP_GETASSEMBLY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_GETASSEMBLY_OUT
/// \brief Reads Assembly Data input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_LINT32 dummy;                         ///< dummy as 32bit alignment to all structure members
     ELMO_UINT16 usStatus;                      ///< Returned command status.
     ELMO_INT16 usErrorID;                      ///< Returned command error ID.
     ELMO_INT8 buffer[MAX_REQUEST_DATA_SIZE];   ///< updated Input data Buffer .
}EIP_GETASSEMBLY_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_CREATE_IN
/// \brief Allocates EIP session memory input structure
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_INT8 cPath[80];
}EIP_CREATE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_CREATE_OUT
/// \brief Allocates EIP session memory input structure
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16    usStatus;                   ///< Returned command status.
     ELMO_INT16     usErrorID;                  ///< Returned command error ID.
}EIP_CREATE_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_OPEN_SESSION_IN
/// \brief Open EIP session input structure
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_INT8 cNotifyEvant;
}EIP_OPEN_SESSION_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_OPEN_SESSION_OUT
/// \brief Open EIP session output structure
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16    usStatus;                   ///< Returned command status.
     ELMO_INT16     usErrorID;                  ///< Returned command error ID.
}EIP_OPEN_SESSION_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_OPEN_SESSION_IN
/// \brief Free EIP session memory input structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_INT8 dummy;
}EIP_DESTROY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_OPEN_SESSION_OUT
/// \brief Free EIP session memory output structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16    usStatus;                   ///< Returned command status.
     ELMO_INT16     usErrorID;                  ///< Returned command error ID.
}EIP_DESTROY_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_OPEN_SESSION_IN
/// \brief Close EIP session input structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_INT8 cDummy;
}EIP_CLOSE_SESSION_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct EIP_OPEN_SESSION_OUT
/// \brief Close EIP session output structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
     ELMO_UINT16    usStatus;                   ///< Returned command status.
     ELMO_INT16     usErrorID;                  ///< Returned command error ID.
}EIP_CLOSE_SESSION_OUT;



////////////////////////////////////////////////////////////////////////////////
/// \fn int EipGetLIBVersion(
///             IN  char *adp_name,
///             OUT int *adp_ref)
/// \brief   pritns EIP LIB version and creation date
/// \param  adp_name -
/// \param  adp_ref -
/// \return value -
///
////////////////////////////////////////////////////////////////////////////////
void EipGetLIBVersion();

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipGetAdpTagRefByName(
///             IN  char *adp_name,
///             OUT ELMO_INT32 *adp_ref)
/// \brief  this function returns adapter tag reference index according to its name
/// \param  adp_name - [IN] Adapter tag name as declared in XML configuration file
/// \param  adp_ref - [OUT] index that is a reference to the adapter tag
/// \return value - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipGetAdpTagRefByName( IN  EIP_REFBYNAME_IN  *pInParam,
                           OUT EIP_REFBYNAME_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipWriteAdpTag(
///             IN ELMO_INT32 adp_ref,
///             IN void* out_buff)
/// \brief writes data to adapter memory
/// \adp_ref - [IN]  reference index to adapter tag
/// \out_buff - [IN] data to be written to the referenced adapter tag
/// \return value - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipWriteAdpTag( IN EIP_WRITEADPTAG_IN   *pInParam,
                    OUT EIP_WRITEADPTAG_OUT  *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipReadAdpTag(
///             IN ELMO_INT32 adp_ref,
///             IN void* in_buff)
/// \brief copies adapter tag data from memory into input buffer
/// \param  adp_ref - [IN] reference index to adapter tag
/// \param  in_buff - [OUT] buffer to hold adapter data
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipReadAdpTag( IN  EIP_READADPTAG_IN     *pInParam,
                   OUT EIP_READADPTAG_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipGetAssemblyRefByInstance(
///             IN ELMO_INT32 asm_instance,
///             IN void* asm_ref)
/// \brief finds asm_instance and applies a reference to this instance
/// \param  asm_instance - [IN] an existing assembly instance
/// \param  asm_ref  - [OUT] index that is a reference to the requested assembly
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipGetAssemblyRefByInstance( IN  EIP_REFBYINSTANCE_IN  *pInParam,
                                 OUT EIP_REFBYINSTANCE_OUT *pOutParam );


////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipGetAssemblyRefByName(
///             IN char *asm_name,
///             IN ELMO_INT32 *asm_ref)
/// \brief this function returns assembly reference index according to its name
/// \asm_name - [IN] Assembly name as declared in XML configuration file
/// \asm_ref  - [OUT] Index that is a reference to the adapter tag
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipGetAssemblyRefByName( IN  EIP_REFBYNAME_IN  *pInParam,
                             OUT EIP_REFBYNAME_OUT *pOutParam );


////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipSetAssembly(
///             IN ELMO_INT32 asm_instance,
///             OUT void* out_buff)
/// \brief Fills Assembly data with out_buff data and sends it through EthernetIP
/// \asm_instance - [IN] instance of requested assembly
/// \out_buff - [OUT] buffer which holds data and send to assembly
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipSetAssembly( IN  EIP_SETASSEMBLY_IN  *pInParam,
                    OUT EIP_SETASSEMBLY_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipGetAssembly(
///             IN ELMO_INT32 asm_instance,
///             OUT void* in_buff)
/// \brief copies an assembly data identified by instance to in_buff
/// \param  asm_instance - [IN] instance of requested assembly
/// \param  in_buff  - [OUT] buffer to hold incoming assembly data
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipGetAssembly(IN  EIP_GETASSEMBLY_IN  *pInParam,
                   OUT EIP_GETASSEMBLY_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipGetDevTagRefByName(
///             IN  char *dev_name,
///             OUT ELMO_INT32 *dev_ref)
/// \brief this function returns device tag reference index according to its name
/// \dev_name - [IN] device tag name as declared in XML configuration file
/// \dev_ref  - [OUT] index that is a reference to the device tag
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipGetDevTagRefByName( IN  EIP_REFBYNAME_IN  *pInParam,
                           OUT EIP_REFBYNAME_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipSetDevTag(
///             IN ELMO_INT32 dev_ref,
///             IN void* out_buff)
/// \brief updates device tag data and sends it to EIP device
/// \param  dev_ref - [IN] index that is a reference to the device tag
/// \out_buff - [OUT] buffer which holds data to be sent to the device tag
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipSetDevTag( IN  EIP_SETDEVTAG_IN  *pInParam,
                  OUT EIP_SETDEVTAG_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipGetDevTag(
///             IN ELMO_INT32 dev_ref,
///             OUT ELMO_INT32 *req_id)
/// \brief  sends request to EIP device to read specific device tag
///         data from the EIP device
/// \dev_ref - [IN] index that is a reference to the device tag
/// \req_id - [OUT] request id to be used to read data when received
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipGetDevTag( IN  EIP_GETDEVTAG_IN  *pInParam,
                  OUT EIP_GETDEVTAG_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipReadDevTagData(
///             IN ELMO_INT32 dev_ref,
///             OUT void* in_buff)
/// \brief  Reads and stores device tag data that has been received by
///         EIP device, as a response to user request.
/// \dev_ref - [IN] index that is a reference to the device tag
/// \in_buff - [OUT] buffer to hold incoming device tag data
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipReadDevTagData( IN  EIP_READDEVTAG_IN  *pInParam,
                       OUT EIP_READDEVTAG_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipSyncGetDevTag(
///             IN ELMO_INT32 dev_ref,
///             OUT void* in_buff)
/// \brief sends request to read device tag data, waits till response received
///             then reads the response data into in_buff buffer
/// \dev_ref -  [IN] index that is a reference to the device tag
/// \in_buff -  [OUT] buffer to hold incoming device tag data
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipSyncGetDevTag( IN  EIP_GETSYNC_IN  *pInParam,
                      OUT EIP_GETSYNC_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipCheckDevTagReply(
/// \                   IN ELMO_INT32 req_id)
/// \brief  check that reply has received for a specific device tag request
/// \req_id - [IN]  device tag request id
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
void  EipCheckDevTagReply(IN EIP_CHECKREPLY_IN *pInParam,OUT EIP_CHECKREPLY_OUT *pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipOpenSession(IN MMC_CONNECT_HNDL* pHndl))
/// \brief  initialize  and starts EIP session in order to be able to use ethernetIP
/// \pHndl pointer to connection
/// \return return - 0 if success
///                  error_id if error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipOpenSession( IN  EIP_CALLBACK_FUNC     pCallBackFunc,
                    IN  EIP_OPEN_SESSION_IN  *pInParam,
                    OUT EIP_OPEN_SESSION_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EIPCloseSession()
/// \brief close EtherntIP session and frees allocated memoey before terminating program
/// \param - none
/// \param  - none
/// \return return - 0 if success
///                  error_id if error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EIPCloseSession(IN  EIP_CLOSE_SESSION_IN  *pInParam,
                    OUT EIP_CLOSE_SESSION_OUT *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipCreate()
/// \brief   allocates memory for tags ans assemblies according to xml config file
/// \param - none
/// \param  - none
/// \return return - 0 if success
///                  error_id if error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipCreate( IN  EIP_CREATE_IN    *pInParam,
                OUT EIP_CREATE_OUT  *pOutParam );

////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipDestroy()
/// \brief
/// \param - none
/// \param  - none
/// \return return - 0 if success
///                  error_id if error
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipDestroy( IN  EIP_DESTROY_IN  *pInParam,
                OUT EIP_DESTROY_OUT *pOutParam );


////////////////////////////////////////////////////////////////////////////////
/// \fn ELMO_INT32 EipIsDevTagWaiting(ELMO_UINT16 usTagRef, OUT EIP_CHECKREPLY_OUT  *pOutParam)
///
/// \brief      Checks that reply has received for a specific device tag request
/// \pInParam - [IN]  device tag number (tag reference)
/// \pOutParam -[OUT] sReplyStatus assigned with reply type (OK, wait or error)
/// \return  - 0 if not waiting (request was replied) otherwise its still waiting.
////////////////////////////////////////////////////////////////////////////////
ELMO_INT32 EipIsDevTagWaiting(ELMO_UINT16 usTagRef, OUT EIP_CHECKREPLY_OUT  *pOutParam );

/*---------------------------------------------------------------
 * API to access data model in memory basically for CPP wrappers
 */
ELMO_INT32 EipGetAdptrTagType(ELMO_UINT16 usTagRef);
ELMO_INT32 EipGetAdptrTagDim(ELMO_UINT16 usTagRef);
ELMO_INT32 EipGetDevTagType(ELMO_UINT16 usTagRef);
ELMO_INT32 EipGetDevTagDim(ELMO_UINT16 usTagRef);
ELMO_INT32 EipGetAsmblTagType(ELMO_UINT16 usTagRef);
ELMO_INT32 EipGetAsmblTagDim(ELMO_UINT16 usTagRef);
ELMO_INT32 EipGetAsmblTagTypeByInst(ELMO_INT32 iInstance);
ELMO_INT32 EipGetAsmblTagDimByInst(ELMO_INT32 iInstance);
void EipSetDebuggingLevel(ELMO_UINT8 ucDebugLevel, ELMO_UINT16 usDebugType);

#ifdef __cplusplus
	}
#endif

#endif /* EIP_API_H */

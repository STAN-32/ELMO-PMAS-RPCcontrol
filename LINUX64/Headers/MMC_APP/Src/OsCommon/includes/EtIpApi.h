/****************************************************************************
*****************************************************************************
**
** File Name
** ---------
**
** EtIpApi.h
**
** COPYRIGHT (c) 2001-2006 Pyramid Solutions, Inc.
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
**
** EtherNet/IP Protocol Stack API declaration. Should be included in the 
** client application project.
**
*****************************************************************************
*****************************************************************************
**
** Source Change Indices
** ---------------------
**
** Porting: <none>0----<major>         Customization: <none>0----<major>
**
*****************************************************************************
*****************************************************************************
*/

#ifndef ET_IP_API_H
#define ET_IP_API_H

#define MAX_NETWORK_PATH_SIZE       256        /* Maximum size of the network path string */
#define MAX_CONNECTION_NAME_SIZE    256        /* Maximum size of the connection name string */
#define MAX_REQUEST_TAG_SIZE        256        /* Maximum size of the tag string */
#define MAX_MODULE_CONFIG_SIZE      512        /* Maximum size of the module specific data */
#define MAX_ERROR_DESC_SIZE         512        /* Maximum size of the error description string */

#define MAX_SESSIONS                4        /* 128 barak Maximum number of sessions that can be opened at the same time */
#define MAX_CONNECTIONS             4        /* 128 barak Maximum number of connections that can be opened at the same time */

#define MAX_HOST_ADDRESSES           16        /* Maximum number of host adapters "IP Addresses" installed on a device */

#define MAX_CLIENT_APP_PROC_CLASS_NBR        64     /* Maximum number of classes the client application can register for its own processing */
#define MAX_CLIENT_APP_PROC_SERVICE_NBR      64     /* Maximum number of services the client application can register for its own processing */

#define MAX_REQUEST_DATA_SIZE        504        /* Maximum data size that can be send with the UCMM message = maximum encapsulation size */
#define MAX_DATA_TAG_SIZE            498        /* Maximum size of a data tag of an explicit message in bytes */
#define MAX_ASSEMBLY_SIZE            502        /* Maximum size of an assembly object in bytes */
#define MAX_ASSEMBLY_NAME_SIZE        64        /* Maximum assembly name length */

#define MAX_PCCC_DATA_SIZE			244			/* Maximum data size that can be sent with a PCCC message */
#ifdef SUPPORT_CSP
#define MAX_PCCC_ADDRESS_SIZE		32			/* Maximum address data size that can be sent with a PCCC message */
#endif

#ifdef ET_IP_SCANNER
#define ASSEMBLY_SCANNER_INPUT_INSTANCE             1
#define ASSEMBLY_SCANNER_OUTPUT_INSTANCE            2
#define INPUT_SCANNER_ASSEMBLY_SIZE                 0xffff
#define OUTPUT_SCANNER_ASSEMBLY_SIZE                0xffff
#endif

#define INVALID_SLOT_INDEX            0xff        /* Invalid slot index */
#define INVALID_CONN_POINT            0xffff      /* Invalid connection point */
#define INVALID_CLASS                 0xffff      /* Class is not valid flag should be used when no class should be specified in the UCMM */
#define INVALID_SERVICE               0xff        /* Service is not valid flag should be used when no service should be specified in the UCMM */
#define INVALID_INSTANCE              0xffff      /* Instance is not valid flag should be used when no instance should be specified in the UCMM */
#define INVALID_ATTRIBUTE             0xffff      /* Attribute is not valid flag should be used when no attribute should be specified in the UCMM */
#define INVALID_MEMBER                0xffff      /* Member is not valid flag should be used when no member should be specified in the UCMM */
#define INVALID_OFFSET                0xffffffff  /* Data Table offset should be assigned automatically by the stack */
#define INVALID_CONNECTION_FLAG       0xffff      /* Connection flag should be built automatically by the stack */
#define INVALID_CONN_INSTANCE         0xffffffff  /* Invalid connection instance number */

#define REQUEST_INDEX_BASE            0x100    /* Request IDs will start with this number. Used to separate request IDs from the returned errors */
#define LIST_IDENTITY_INDEX_BASE	  0x100    /* IDs will start with this number. Used to separate IDs from the returned errors */

/* Connection related notification messages. Second parameter in the callback function will be Connection Instance number */            
#define NM_CONNECTION_ESTABLISHED                     1    /* New connection successfully established */
#define NM_CONN_CONFIG_FAILED_INVALID_NETWORK_PATH    2    /* Connection establishment failed. Target is offline. */
#define NM_CONN_CONFIG_FAILED_NO_RESPONSE             3    /* Connection establishment failed. Target is online but did not respond to the connection request. */
#define NM_CONN_CONFIG_FAILED_ERROR_RESPONSE          4    /* Connection establishment failed. Target responded with an error response. Use EtIPGetConnectionErrorInfo() function to get error details. */
#define NM_CONNECTION_TIMED_OUT                       5    /* Active connection timed out. iWatchdogTimeoutAction member of the connection configuration will determine the associated action */
#define NM_CONNECTION_CLOSED                          6    /* Connection closed based either on the local or remote request */
#define NM_INCOMING_CONNECTION_RUN_IDLE_FLAG_CHANGED  7    /* Run Idle flag changed for the incoming Class1 connection. Param1 contains connection instance. Param2 contains the new flag (1 - Run, 0 - Idle). */
#define NM_ASSEMBLY_NEW_INSTANCE_DATA                 8    /* New data received for the specified assembly instance. Param1 contains assembly instance. */
#define NM_ASSEMBLY_NEW_MEMBER_DATA                   9    /* New data received for the specified assembly member. Param1 contains assembly instance. Param2 contains instance member. */
#define NM_CONNECTION_NEW_INPUT_SCANNER_DATA          10   /* New input data received for the scanner connection. Param1 contains connection instance. */
#define NM_CONNECTION_VERIFICATION					  11   /* New connection received.  Waiting for application to verify validity */
#define NM_CONNECTION_RECONFIGURED                    12    /* Connection successfully reconfigured (successful NULL Forward Open) */

/* Object Request related notification messages. Second parameter in the callback function will be the Request ID */            
#define NM_REQUEST_RESPONSE_RECEIVED                  100   /* Response received on the previously sent request */
#define NM_REQUEST_FAILED_INVALID_NETWORK_PATH        101   /* Unable to connect to the path specified in the request */
#define NM_REQUEST_TIMED_OUT                          102   /* Request timed out - response never received. */
#define NM_CLIENT_OBJECT_REQUEST_RECEIVED             103   /* Request received for the object registered for the client application processing */
#define NM_NEW_CLASS3_RESPONSE                        104   /* Detected change in the response received on the previously established Class3 connection */
#define NM_CLIENT_PCCC_REQUEST_RECEIVED               105   /* Request received for the PCCC object */
#define NM_NEW_LIST_IDENTITY_RESPONSE				  106   /* Response received for previously send List Identity broadcast */

/* General error messages. Second parameter in the callback function is not used. */ 
#define NM_OUT_OF_MEMORY                              200   /* Out of available memory. */
#define NM_UNABLE_INTIALIZE_WINSOCK                   201   /* Unable to initialize Windows Sockets library. */
#define NM_UNABLE_START_THREAD                        202   /* Unable to start a thread */
#define NM_ERROR_USING_WINSOCK                        203   /* Received an error when using Windows Sockets library functions */
#define NM_ERROR_SETTING_SOCKET_TO_NONBLOCKING        204   /* Error encountered when setting the socket to non-blocking mode */
#define NM_ERROR_SETTING_TIMER                        205   /* Error encountered when setting the required timer object */
#define NM_SESSION_COUNT_LIMIT_REACHED                206   /* Number of network peers exceeded MAX_SESSIONS constant */
#define NM_CONNECTION_COUNT_LIMIT_REACHED             207   /* Number of connections exceeded MAX_CONNECTIONS limit */
#define NM_PENDING_REQUESTS_LIMIT_REACHED             208   /* Number of outstanding object requests exceeded MAX_REQUESTS limit */
#define NM_ID_RESET									  209   /* And Identity Reset was received */

/* Following error codes may be returned to one of the function calls. They will not be used when invoking the callback function */
#define ERR_OBJECT_REQUEST_UNKNOWN_INDEX              300   /* Unknown index specified when trying to get an object response */
#define ERR_NO_AVAILABLE_OBJECT_RESPONSE              301   /* The response on the request sent has not been received yet */
#define ERR_INVALID_CONNECTION_INSTANCE_SPECIFIED     302   /* There is no active connection available for the specified instance */
#define ERR_NO_CLAIMED_HOST_ADDRESSES                 303   /* No host addresses have been claimed yet */
#define ERR_INVALID_OR_NOT_CLAIMED_HOST_ADDRESS       304   /* Invalid or not yet claimed host address specified in the function call */
#define ERR_ASSEMBLY_INVALID_INSTANCE                 305   /* Invalid assembly instance specified */
#define ERR_ASSEMBLY_INSTANCE_ALREADY_EXIST           306   /* Multiple claims of the assembly instance */
#define ERR_ASSEMBLY_OBJECTS_LIMIT_REACHED            307   /* Number of configured assemblies would exceed MAX_ASSEMBLIES limit */
#define ERR_ASSEMBLY_SPECIFIED_OFFSET_INVALID         308   /* Specified offset and size combination overlap with one of the already configured assemblies */
#define ERR_ASSEMBLY_NO_BUFFER_SPACE_LEFT             309   /* No unallocated buffer space left in the assembly buffer */
#define ERR_ASSEMBLY_SIZE_EXCEED_LIMIT                310   /* Specified assembly size exceed maximum allowed size of MAX_ASSEMBLY_SIZE */
#define ERR_ASSEMBLY_SPECIFIED_INSTANCE_INVALID       311   /* Specified assembly instance has not been configured */
#define ERR_ASSEMBLY_INSTANCE_USED                    312   /* Specified assembly instance is being used by one of the active or pending connections */
#define ERR_ASSEMBLY_MEMBER_SIZE_EXCEED_LIMIT         313   /* Specified member size would cause the total member list size exceed assembly instance size */
#define ERR_ASSEMBLY_MEMBER_LIMIT_REACHED             314   /* Number of configured members for the corresponding assembly would exceed MAX_MEMBERS limit */
#define ERR_ASSEMBLY_MEMBER_ALREADY_EXIST             315   /* Multiple claims of the assembly instance member */
#define ERR_IDENTITY_INVALID_INSTANCE                 316   /* Invalid identity instance specified */
#define ERR_CONNECTION_ALREADY_BEING_CONFIGURED		  317	/* NULL Forward Open request made while existing one is still being processed */

#define MAX_ASSEMBLIES                               128   /* Maximum number of assembly instances */
#define MAX_MEMBERS                                   64   /* Maximum number of members per assembly instance */

/* Assembly type will be set by combining a type from EtIPAssemblyAccessType with a type from 
   EtIPAssemblyDirectionType and, optionally, one of the types from tagEtIPAssemblyAdditionalFlag. */

typedef enum tagEtIPAssemblyAccessType        
{
    AssemblyStatic  = 1,               /* Static Assembly. Outside explicit requests not allowed to modify member list. */
    AssemblyDynamic = 2                /* Dynamic Assembly. Outside explicit requests are allowed to modify member list. */
}
EtIPAssemblyAccessType;

#define ASSEMBLY_ACCESS_TYPE_FLAG    3

typedef enum tagEtIPAssemblyDirectionType        
{
    AssemblyConsuming        = 4,    /* Assembly that consumes data from the network */
    AssemblyProducing        = 8,    /* Assembly that produces data on the network */
    AssemblyConfiguration    = 16    /* Assembly that will be used to store configuration data that comes with incoming Forward Open. Should be listed as Connection Configuration Instance in the incoming Forward Open. Not used for originating connections. */
}
EtIPAssemblyDirectionType;

#define ASSEMBLY_DIRECTION_TYPE_FLAG  0x1c

typedef enum tagEtIPAssemblyAdditionalFlag        
{
    AssemblyRequireCCConfigurationForIncomingConnection     = 32,    /* Require that connection be configured through CC object before accepting incoming Forward Open */
    AssemblyNotAllowCCConfigurationForOutgoingConnection    = 64     /* Connections can be initiated only through an API call, not through CC object configuration */    
}
EtIPAssemblyAdditionalFlag;

#define ASSEMBLY_ADDITIONAL_FLAG  0x60

typedef struct tagEtIPAssemblyMemberConfig
{
    UINT16 iMember;                    /* Unique assembly member id. May be INVALID_MEMBER for the data that should be ignored. */
    UINT16 iOffset;                    /* Offset in bits from the beginning of the assembly instance data buffer. Will be automatically assigned by the stack - not the client. */
    UINT16 iSize;                      /* Member size in bits */    
}
EtIPAssemblyMemberConfig;

typedef struct tagEtIPAssemblyConfig
{
    INT32  nInstance;                                /* Unique assembly object instance. Examples are connection connection points and connection configuration instance. */
    INT32  nOffset;                                  /* Offset from the beginning of the assembly buffer in bytes. May be set to EtIPAssemblyConfig to be automatically assigned by the stack. */
    INT32  nSize;                                    /* Assembly size in bytes. */
    INT32  nType;                                    /* Combination of a type from EtIPAssemblyAccessType with a type from EtIPAssemblyDirectionType and, optionally, one of the types from tagEtIPAssemblyAdditionalFlag */
    EtIPAssemblyMemberConfig Members[MAX_MEMBERS];   /* Member list */
    INT32  nNumMembers;                              /* Number of members in the member list */    
    INT8   szTagName[MAX_ASSEMBLY_NAME_SIZE];        /* Optional 0 terminated ASCII name associated with the assembly instance */    
}
EtIPAssemblyConfig;

/* Tag Types */
#define TAG_TYPE_CLASS                     1
#define TAG_TYPE_INSTANCE                  2
#define TAG_TYPE_ATTRIBUTE                 3
#define TAG_TYPE_MEMBER                    4
#define TAG_TYPE_PORT                      5
#define TAG_TYPE_LINK_ADDRESS              6
#define TAG_TYPE_SLOT                      7
#define TAG_TYPE_CONN_POINT                8
#define TAG_TYPE_KEY                       9
#define TAG_TYPE_INHIBIT_INTERVAL         10
#define TAG_TYPE_SYMBOL                   11
#define TAG_TYPE_EXT_SYMBOL               12
#define TAG_TYPE_DATA                     13

#define MAX_TAGS                16        /* Max number of different tags that can be specified in the PDU */

typedef struct tagETAG
{        
    UINT32        TagData;                 /* Can be UINT8 or UINT16 or UINT8* depending on the type */
    UINT16        iTagDataSize;            /* Tag Data size in bytes */
    UINT16        iTagType;                /* See TAG_TYPE_* macros above for the type list */    
}
ETAG;

typedef struct tagEPATH
{    
    ETAG        Tags[MAX_TAGS];
    UINT8       bNumTags;                /* Actual number of tags in EPATH */
    BOOL        bPadded;                 /* Either Padded or Packed format for EPATH */
}
EPATH;

typedef struct tagSTRINGI
{
	UINT8	aLang[3];								/* Common Language Codes from ISO 639-2/T */
	UINT8	bEPATH;									/* EPATH (limited to the values 0xD0, 0xD5, 0xD9, and0xDA) */
	UINT16	iCharacterSet;							/* Character set of string */
	UINT8	bLength;								/* Length of string */
	UINT8	stringData[MAX_REQUEST_TAG_SIZE];		/* String data */
} STRINGI;

typedef struct tagEtIPObjectRequest                /* Structure used to transfer UCMM message */
{
    INT8    networkPath[MAX_NETWORK_PATH_SIZE];    /* Null terminated peer network path string. If we are originating request this can be a complex routing path. If we are the target this is the IP address of the peer this request came from. */    
    UINT8   bService;                              /* Service to be performed */
    UINT16  iClass;                                /* Target class */
    UINT16  iInstance;                             /* Target instance. Can be 0 if the target is class */
    UINT16  iAttribute;                            /* Target attribute. Must be INVALID_ATTRIBUTE if the attribute should not be a part of the path */
    UINT16  iMember;                               /* Target member. Must be INVALID_MEMBER if the member should not be a part of the path */
    INT8    requestTag[MAX_REQUEST_TAG_SIZE];      /* Target extended symbol segment. If not used iTagSize must be 0. */
    UINT16  iTagSize;                              /* The actual size of the requestTag */
    UINT8   requestData[MAX_REQUEST_DATA_SIZE];    /* Data that should be sent to the target. If not used iDataSize must be 0. */
    UINT16  iDataSize;                             /* The actual size of the requestData */
    UINT32  lExplicitMessageTimeout;               /* Message Timeout in milliseconds. If 0, DEFAULT_EXPLICIT_REQUEST_TIMEOUT will be used instead. */
    UINT32  lHostIPAddr;                           /* Host IPAddress in UINT32 format for the opened session */
}
EtIPObjectRequest;

typedef struct tagEtIPEPATHObjectRequest           /* Structure used to transfer UCMM message using the ready to use EPATH */
{
    INT8    networkPath[MAX_NETWORK_PATH_SIZE];    /* Null terminated peer network path string. If we are originating request this can be a complex routing path. If we are the target this is the IP address of the peer this request came from. */    
    UINT8   bService;                              /* Service to be performed */
    EPATH   ePATH;                                 /* Ready to use EPATH for cases more complex that the ones that can be serviced by EtIPObjectRequest */
    UINT8   requestData[MAX_REQUEST_DATA_SIZE];    /* Data that should be sent to the target. If not used iDataSize must be 0. */
    UINT16  iDataSize;                             /* The actual size of the requestData */
    UINT32  lExplicitMessageTimeout;               /* Message Timeout in milliseconds. If 0, DEFAULT_EXPLICIT_REQUEST_TIMEOUT will be used instead. */
    UINT32  lHostIPAddr;                           /* Host IPAddress in UINT32 format for the opened session */
}
EtIPEPATHObjectRequest;


typedef struct tagEtIPObjectResponse               /* Structure used to get the response to a UCMM or an Unconnected Send message */
{        
    UINT8   bGeneralStatus;                        /* 0 in case of successful response, or one of the CIP general codes. */
    UINT16  iExtendedStatus;                       /* Together with General Status is used to provide more error information. */
    INT8    errorDescription[MAX_ERROR_DESC_SIZE]; /* Null terminated error description string. It is filled only if bGeneralStatus is other than 0. */
    UINT8   responseData[MAX_REQUEST_DATA_SIZE];   /* Response Data in case of a success. */
    UINT16  iDataSize;                             /* The size of the responseData in bytes */
}
EtIPObjectResponse;

typedef struct tagEtIPPCCCRequest
{
    UINT32 lNetworkAddr;						/* Peer network IPAddress in UINT32 format. If we are the target this is the IP address of the peer this request came from. */  
	UINT8 bCommand;								/* PCCC Command */
	UINT8 bExtCommand;							/* PCCC Extended Command (for commands 6, 7, 14 and 15) */
    UINT8 requestData[MAX_PCCC_DATA_SIZE];			/* Data that should be sent to the target. If not used iDataSize must be 0. */
    UINT16 iDataSize;                             /* The actual size of the requestData */

	UINT8 bHasRequestorIDData;					/* Used to determine if iVendorID, lSerialNumber, and requesterIDData are valid data */
	UINT16 iVendorId;							  /* Used with PCCC Object Execute PCCC service */
	UINT32 lSerialNumber;						/* Used with PCCC Object Execute PCCC service */
	UINT8 requesterIDData[MAX_PCCC_DATA_SIZE];	/* Used with PCCC Object Execute PCCC service */
	UINT8 iRequesterIDDataSize;					/* Used with PCCC Object Execute PCCC service */

#ifdef SUPPORT_CSP
	UINT8	addressData[MAX_PCCC_ADDRESS_SIZE];		/* Address data that should be sent to the target. If not used iAddressDataSize must be 0. */
    UINT16 iAddressDataSize;                        /* The actual size of the addressData */
#endif

    UINT32  lExplicitMessageTimeout;               /* Message Timeout in milliseconds. If 0, DEFAULT_EXPLICIT_REQUEST_TIMEOUT will be used instead. */
    UINT32  lHostIPAddr;                           /* Host IPAddress in UINT32 format for the opened session */

} EtIPPCCCRequest;

typedef struct tagEtIPPCCCResponse
{
	UINT8 bError;								/* PCCC Error */
	UINT8 bExtStatus;							/* Extended status for certain PCCC Commands */
    UINT8  responseData[MAX_PCCC_DATA_SIZE];   /* Response Data in case of a success. */
    UINT16 iDataSize;                          /* The size of the responseData in bytes */	
#ifdef SUPPORT_CSP
	UINT8	addressData[MAX_PCCC_ADDRESS_SIZE];		/* Address data that should be sent to the target. If not used iAddressDataSize must be 0. */
    UINT16 iAddressDataSize;                        /* The actual size of the addressData */
#endif

} EtIPPCCCResponse;

typedef enum tagEtIPTransportClass        /* Class 1 and Class 3 transports supported */
{
    Class1  = 1,
    Class3  = 3
}
EtIPConnectionClass;

typedef enum tagEtIPTransportType
{
    Cyclic                = 0,            /* Produce and consume cyclicly on the connection */
    ChangeOfState         = 0x10,         /* Produce and consume on the state change as well as cyclicly to keep the connection open */
    ApplicationTriggered  = 0x20          /* Treat the same as ChangeOfState */
}
EtIPTransportType;

typedef enum tagEtIPConnectionType
{
    PointToPoint          = 0x4000,        /* Should be always used for Originator to Target transports */
    Multicast             = 0x2000,        /* Could be used for Target to Originator transports */
    NullConnType          = 0              /* Null connection type */
}
EtIPConnectionType;

typedef enum tagEtIPConnectionPriority
{
    LowPriority           = 0x0,        
    HighPriority          = 0x400,        
    ScheduledPriority     = 0x800,        
    UrgentPriority        = 0xC00        
}
EtIPConnectionPriority;

typedef enum tagEtIPConnectionRunIdleFlag
{
    IdleFlag            = 0x0,        
    RunFlag             = 0x1,        
    UnknownRunIdleFlag  = 0x2            
}
EtIPConnectionRunIdleFlag;

typedef enum tagEtIPConnectionState
{
    ConnectionNonExistent         = 0x0,    /* Connection is not instantiated    */
    ConnectionConfiguring         = 0x1,    /* In the process of opening a new connection    */
    ConnectionWaitingForID        = 0x2,    /* This status will never be assigned since Connection object services are not supported */
    ConnectionEstablished         = 0x3,    /* Connection is active */
    ConnectionTimedOut            = 0x4,    /* Connection has timed out; will stay in this state at least for some time if iWatchdogTimeoutAction is set to TimeoutManualReset or TimeoutDelayAutoReset.*/
    ConnectionDeferredDelete      = 0x5,    /* Connection is about to be deleted and waiting for child connections to be closed first. */
    ConnectionClosing             = 0x6     /* In the process of closing the connection */
}
EtIPConnectionState;

typedef enum tagEtIPWatchdogTimeoutAction
{
    TimeoutAutoDelete            = 0x0,        /* Immediately Delete connection on watchdog timeout */
    TimeoutDeferredDelete        = 0x1,        /* Delete connection after child connections are closed. */ 
    TimeoutAutoReset             = 0x2,        /* Immediately attempt to reconnect on watchdog timeout */
    TimeoutDelayAutoReset        = 0x3,        /* Attempt to reconnect after predetermined delay period */    
    TimeoutManualReset           = 0x4         /* Wait in time out state until the user calls EtIPResetConnection */
}
EtIPWatchdogTimeoutAction;

typedef enum tagEtIPNetworkStatus
{
	NetworkStatusOff				= 0x0,		/* No power or no IP (claimed) address */
	NetworkStatusFlashingGreen		= 0x1,		/* No connections */
	NetworkStatusGreen				= 0x2,		/* At least 1 connection */
	NetworkStatusFlashingRed		= 0x3,		/* One or more connections have timed out */
	NetworkStatusRed				= 0x4,		/* Duplicate IP address */
	NetworkStatusFlashingGreenRed	= 0x5		/* Selftest */
}
EtIPNetworkStatus;

typedef struct tagEtIPDeviceID                /* Could be used for device keying */
{
    UINT16 iVendorID;
    UINT16 iProductType;
    UINT16 iProductCode;
    UINT8  bMajorRevision;
    UINT8  bMinorRevision;
}
EtIPDeviceID;

typedef struct tagEtIPErrorInfo                            
{    
    UINT8            bGeneralStatus;                               /* Together with Extended Status is used to provide more error information. 0 if connection is running fine, 0xD0 if connecting or disconnecting. */
    UINT16           iExtendedStatus;                              /* Together with General Status is used to provide more error information. 2 if connecting, 3 if disconnecting, or any other extended error code. */
    INT8             errorDescription[MAX_ERROR_DESC_SIZE];        /* Null terminated error description string */
}
EtIPErrorInfo;

typedef struct tagEtIPConnectionConfig                            
{
    INT32     nInstance;                                  /* Instance of the Connection object. If 0, Instance will be assigned automatically by the stack and available on the function call return. */
    BOOL      bOriginator;                                /* Indicates whether whether this is outgoing or incoming connection */
    INT8      networkPath[MAX_NETWORK_PATH_SIZE];         /* Null terminated connection path string. If originator, it can be the complex routing path. If target, it is the IP address of the peer the connection request came from. */    
    UINT16    iConnectionFlag;                            /* Should be set to INVALID_CONN_POINT when calling EtIPOpenConnection. EtIPGetConnectionFlag() returns valid flag compatible with RSNetworx format */            
    UINT16    iTargetConfigConnInstance;                  /* Target Assembly configuration instance. */    
    UINT16    iTargetProducingConnPoint;                  /* Target Assembly Producing instance. */
    UINT16    iTargetConsumingConnPoint;                  /* Target Assembly Consuming instance. */        
    INT8      targetProducingConnTag[MAX_REQUEST_TAG_SIZE]; /* Optional target producing connection tag. Could be used instead of specifying the iTargetProducingConnPoint. */
    UINT16    iTargetProducingConnTagSize;                  /* Connection target producing connection tag size. Must be set to 0 if target producing connection tag is not used */
	INT8      targetConsumingConnTag[MAX_REQUEST_TAG_SIZE]; /* Optional target consuming connection tag. Could be used instead of specifying the iTargetConsumingConnPoint. */
    UINT16    iTargetConsumingConnTagSize;                  /* Connection target consuming connection tag size. Must be set to 0 if target consuming connection tag is not used */
    UINT32    lProducingDataRate;                         /* Producing by this stack I/O data rate in milliseconds */
    UINT32    lConsumingDataRate;                         /* Consuming by this stack I/O data rate in milliseconds */
    UINT8     bProductionOTInhibitInterval;               /* The scanner (originator) will not produce with the higher rate than inhibit interval. Value of 0 disables it. */
    UINT8     bProductionTOInhibitInterval;               /* The adapter (target) will not produce with the higher rate than inhibit interval. Value of 0 disables it. */
    BOOL      bOutputRunProgramHeader;                    /* Set to TRUE if the first 4 bytes of the output data represent Run/Program header */    
    BOOL      bInputRunProgramHeader;                     /* Set to TRUE if the first 4 bytes of the input data represent Run/Program header */    
    UINT16    iProducingConnectionType;                   /* Producing connection type to use. Must be PointToPoint when Originator and could be either PointToPoint or Multicast when Target. */
    UINT16    iConsumingConnectionType;                   /* Consuming connection type to use. Could be either PointToPoint or Multicast when Originator and must be PointToPoint when Target. */    
    UINT16    iProducingPriority;                         /* Must be one of the EtIPConnectionPriority values */    
    UINT16    iConsumingPriority;                         /* Must be one of the EtIPConnectionPriority values */    
    UINT8     bTransportClass;                            /* Indicates whether transport is Class 1 or Class 3. Must be one of the EtIPConnectionClass values. */
    UINT8     bTransportType;                             /* One of the EtIPTransportType enumeration values */
    UINT8     bTimeoutMultiplier;                         /* Timeout multiplier of 0 indicates that timeout should be 4 times larger than the consuming data rate, 1 - 8 times larger, 2 - 16 times, and so on */
    UINT16    iWatchdogTimeoutAction;                     /* Watchdog Timeout Action from the EtIPWatchdogTimeoutAction enumeration */
    UINT32    lWatchdogTimeoutReconnectDelay;             /* If Watchdog Timeout Action is TimeoutDelayAutoReset, Watchdog Timeout Reconnect Delay specifies reconnect delay in milliseconds */    
    EtIPDeviceID   deviceId;                              /* Optional target device identification. All members must be set to 0 to turn off identification. If set, it will be specified in the Forward Open Connection Path. */    
    INT8      connectionName[MAX_CONNECTION_NAME_SIZE];   /* Optional user recognizable connection name. */
    UINT16    iConnectionNameSize;                        /* Connection name size. Must be set to 0 if connection name is not used */
    UINT8     moduleConfig1[MAX_MODULE_CONFIG_SIZE];      /* Optional first part of the target device specific configuration */
    UINT16    iModuleConfig1Size;                         /* The size of the first part of the target device specific configuration. Must be set to 0 if configuration is not passed to the target device */
    UINT8     moduleConfig2[MAX_MODULE_CONFIG_SIZE];      /* Optional second part of the target device specific configuration */
    UINT16    iModuleConfig2Size;                         /* The size of the second part of the target device specific configuration. Must be set to 0 if configuration is not passed to the target device */        
    UINT32    lHostIPAddr;                                /* Host IPAddress in UINT32 format for the opened session */
#ifdef ET_IP_SCANNER
    INT32     nInputScannerOffset;                        /* Offset in the Input Scanner assembly where the data begins for this connection */
    INT32     nInputScannerSize;                          /* Size allocated for this connection in the Input Scanner assembly */
    INT32     nOutputScannerOffset;                       /* Offset in the Output Scanner assembly where the data begins for this connection */
    INT32     nOutputScannerSize;                         /* Size allocated for this connection in the Output Scanner assembly */
#endif
}
EtIPConnectionConfig;

typedef struct tagEtIPClass3Request                /* Structure used to set a Class3 request */
{    
    UINT8    bService;                             /* Service to be performed */
    UINT16   iClass;                               /* Target class */
    UINT16   iInstance;                            /* Target instance. Can be 0 if the target is class */
    UINT16   iAttribute;                           /* Target attribute. Must be INVALID_ATTRIBUTE if the attribute should not be a part of the path */
    UINT16   iMember;                              /* Target member. Must be INVALID_MEMBER if the member should not be a part of the path */
    INT8     requestTag[MAX_REQUEST_TAG_SIZE];     /* Target extended symbol segment. If not used iTagSize must be 0. */
    UINT16   iTagSize;                             /* The actual size of the requestTag */
    UINT8    requestData[MAX_REQUEST_DATA_SIZE];   /* Data that should be sent to the target. If not used iDataSize must be 0. */
    UINT16   iDataSize;                            /* The actual size of the requestData */    
}
EtIPClass3Request;

typedef struct tagEtIPEPATHClass3Request        /* Structure used to set a Class3 request using the ready to use EPATH */
{    
    UINT8    bService;                             /* Service to be performed */
    EPATH    ePATH;                                /* Ready to use EPATH for cases more complex that the ones that can be serviced by EtIPObjectRequest */
    UINT8    requestData[MAX_REQUEST_DATA_SIZE];   /* Data that should be sent to the target. If not used iDataSize must be 0. */
    UINT16   iDataSize;                            /* The actual size of the requestData */    
}
EtIPEPATHClass3Request;


#define MAX_PRODUCT_NAME_SIZE    33                    /* Maximum number of 32 characters and the ending 0 */

typedef struct tagEtIPIdentityInfo
{
   UINT16  iVendor;
   UINT16  iProductType;
   UINT16  iProductCode;
   UINT8   bMajorRevision;
   UINT8   bMinorRevision;
   UINT16  iStatus;
   UINT32  lSerialNumber;   
   INT8    productName[MAX_PRODUCT_NAME_SIZE];
   UINT8   bUseApplicationStatus;
   STRINGI szUserName;
   STRINGI szUserDescription;
   STRINGI szUserLocation;
}
EtIPIdentityInfo;

#define MAX_IDENTITY_INSTANCE	1

typedef void LogEventCallbackType( INT32 nEvent, INT32 nParam1, INT32 nParam2 );    /* Callback function to be called in case of any notification or error event */

typedef struct tagEtIPConnectionStats                    /* Structure used to transfer connection statistics */
{
    UINT32          lSendPackets;                        /* Number of sent packets */
    UINT32          lRcvdPackets;                        /* Number of received packets */
    float           fSendAPI;                            /* The actual packet interval for the sent packets */
    float           fRcvdAPI;                            /* The actual packet interval for the received packets */
    UINT32          lMaxSendDelay;                       /* The maximum delay between any two consecutive send packets */
    UINT32          lMaxRcvdDelay;                       /* The maximum delay between any two consecutive receive packets */
    UINT32          lLostPackets;                        /* The number of lost packets */
}
EtIPConnectionStats;

typedef struct tagEtIPListIdentityInfo
{
	INT32 lID;											/* Identitier for a device's response */
	UINT32 lIPAddress;									/* IP address of the device */
	UINT32 lHostAddress;								/* Host IP address that sent the ListIdentity broadcast */
	EtIPDeviceID deviceId;								/* Device information */
	UINT16  iStatus;									/* Device's status */
	UINT32  lSerialNumber;								/* Device's serial number */
	INT8    productName[MAX_PRODUCT_NAME_SIZE];			/* Device's product name */
	UINT8	bTargetState;								/* Device's state */

} EtIPListIdentityInfo;

/* The following are CIP (Ethernet/IP) Generic error codes */
#define ROUTER_ERROR_SUCCESS                    0x00  /* We done good...               */
#define ROUTER_ERROR_FAILURE                    0x01  /* Connection failure            */
#define ROUTER_ERROR_NO_RESOURCE                0x02  /* Resource(s) unavailable       */
#define ROUTER_ERROR_INVALID_PARAMETER_VALUE    0x03  /* Obj specific data bad         */
#define ROUTER_ERROR_INVALID_SEG_TYPE            0x04  /* Invalid segment type in path  */
#define ROUTER_ERROR_INVALID_DESTINATION        0x05  /* Invalid segment value in path */
#define ROUTER_ERROR_PARTIAL_DATA                0x06  /* Not all expected data sent    */
#define ROUTER_ERROR_CONN_LOST                    0x07  /* Messaging connection lost     */
#define ROUTER_ERROR_BAD_SERVICE                0x08  /* Unimplemented service code    */
#define ROUTER_ERROR_BAD_ATTR_DATA                0x09  /* Bad attribute data value      */
#define ROUTER_ERROR_ATTR_LIST_ERROR            0x0A  /* Get/set attr list failed      */
#define ROUTER_ERROR_ALREADY_IN_REQUESTED_MODE    0x0B  /* Obj already in requested mode */
#define ROUTER_ERROR_OBJECT_STATE_CONFLICT        0x0C  /* Obj not in proper mode        */
#define ROUTER_ERROR_OBJ_ALREADY_EXISTS            0x0D  /* Object already created        */
#define ROUTER_ERROR_ATTR_NOT_SETTABLE            0x0E  /* Set of get only attr tried    */
#define ROUTER_ERROR_PERMISSION_DENIED            0x0F  /* Insufficient access permission*/
#define ROUTER_ERROR_DEV_IN_WRONG_STATE            0x10  /* Device not in proper mode     */
#define ROUTER_ERROR_REPLY_DATA_TOO_LARGE        0x11  /* Response packet too large     */
#define ROUTER_ERROR_FRAGMENT_PRIMITIVE            0x12  /* Primitive value will fragment */
#define ROUTER_ERROR_NOT_ENOUGH_DATA            0x13  /* Goldilocks complaint #1       */
#define ROUTER_ERROR_ATTR_NOT_SUPPORTED            0x14  /* Attribute is undefined        */
#define ROUTER_ERROR_TOO_MUCH_DATA                0x15  /* Goldilocks complaint #2       */
#define ROUTER_ERROR_OBJ_DOES_NOT_EXIST            0x16  /* Non-existant object specified */
#define ROUTER_ERROR_NO_FRAGMENTATION            0x17  /* Fragmentation not active      */
#define ROUTER_ERROR_DATA_NOT_SAVED                0x18  /* Attr data not previously saved*/
#define ROUTER_ERROR_DATA_WRITE_FAILURE            0x19  /* Attr data not saved this time */
#define ROUTER_ERROR_REQUEST_TOO_LARGE            0x1A  /* Routing failure on request    */
#define ROUTER_ERROR_RESPONSE_TOO_LARGE            0x1B  /* Routing failure on response   */
#define ROUTER_ERROR_MISSING_LIST_DATA            0x1C  /* Attr data not found in list   */
#define ROUTER_ERROR_INVALID_LIST_STATUS        0x1D  /* Returned list of attr w/status*/
#define ROUTER_ERROR_SERVICE_ERROR                0x1E  /* Embedded service failed       */
#define ROUTER_ERROR_VENDOR_SPECIFIC            0x1F  /* Vendor specific error           */
#define ROUTER_ERROR_INVALID_PARAMETER            0x20  /* Invalid parameter               */
#define ROUTER_ERROR_WRITE_ONCE_FAILURE            0x21  /* Write once previously done    */
#define ROUTER_ERROR_INVALID_REPLY                0x22  /* Invalid reply received        */
#define ROUTER_ERROR_BAD_KEY_IN_PATH            0x25  /* Electronic key in path failed */
#define ROUTER_ERROR_BAD_PATH_SIZE                0x26  /* Invalid path size             */
#define ROUTER_ERROR_UNEXPECTED_ATTR            0x27  /* Cannot set attr at this time  */
#define ROUTER_ERROR_INVALID_MEMBER                0x28  /* Member ID in list nonexistant */
#define ROUTER_ERROR_MEMBER_NOT_SETTABLE        0x29  /* Cannot set value of member    */
#define ROUTER_ERROR_STILL_PROCESSING            0xFF  /* Special marker to indicate    */
                                                /* we haven't finished processing */
                                                /* the request yet               */

#define ROUTER_ERROR_ENCAP_PROTOCOL                0x6A  /* Error in encapsulation header */    

/* The following are CIP (Ethernet/IP) Extended error codes */
#define ROUTER_EXT_ERR_NO_EXTENDED						0xFF
#define ROUTER_EXT_ERR_DUPLICATE_FWD_OPEN                0x100
#define ROUTER_EXT_ERR_CLASS_TRIGGER_INVALID            0x103
#define ROUTER_EXT_ERR_OWNERSHIP_CONFLICT                0x106
#define ROUTER_EXT_ERR_CONNECTION_NOT_FOUND                0x107
#define ROUTER_EXT_ERR_INVALID_CONN_TYPE                0x108
#define ROUTER_EXT_ERR_INVALID_CONN_SIZE                0x109
#define ROUTER_EXT_ERR_DEVICE_NOT_CONFIGURED            0x110
#define ROUTER_EXT_ERR_RPI_NOT_SUPPORTED                0x111
#define ROUTER_EXT_ERR_CONNECTION_LIMIT_REACHED            0x113
#define ROUTER_EXT_ERR_VENDOR_PRODUCT_CODE_MISMATCH        0x114
#define ROUTER_EXT_ERR_PRODUCT_TYPE_MISMATCH            0x115
#define ROUTER_EXT_ERR_REVISION_MISMATCH                0x116
#define ROUTER_EXT_ERR_INVALID_CONN_POINT                0x117
#define ROUTER_EXT_ERR_INVALID_CONFIG_FORMAT            0x118
#define ROUTER_EXT_ERR_NO_CONTROLLING_CONNECTION        0x119
#define ROUTER_EXT_ERR_TARGET_CONN_LIMIT_REACHED        0x11A
#define ROUTER_EXT_ERR_RPI_SMALLER_THAN_INHIBIT            0x11B
#define ROUTER_EXT_ERR_CONNECTION_TIMED_OUT                0x203
#define ROUTER_EXT_ERR_UNCONNECTED_SEND_TIMED_OUT        0x204
#define ROUTER_EXT_ERR_PARAMETER_ERROR                    0x205
#define ROUTER_EXT_ERR_MESSAGE_TOO_LARGE                0x206
#define ROUTER_EXT_ERR_UNCONN_ACK_WITHOUT_REPLY            0x207
#define ROUTER_EXT_ERR_NO_BUFFER_MEMORY_AVAILABLE        0x301
#define ROUTER_EXT_ERR_BANDWIDTH_NOT_AVAILABLE            0x302
#define ROUTER_EXT_ERR_TAG_FILTERS_NOT_AVAILABLE        0x303
#define ROUTER_EXT_ERR_REAL_TIME_DATA_NOT_CONFIG        0x304
#define ROUTER_EXT_ERR_PORT_NOT_AVAILABLE                0x311
#define ROUTER_EXT_ERR_LINK_ADDR_NOT_AVAILABLE            0x312
#define ROUTER_EXT_ERR_INVALID_SEGMENT_TYPE_VALUE        0x315
#define ROUTER_EXT_ERR_PATH_CONNECTION_MISMATCH            0x316
#define ROUTER_EXT_ERR_INVALID_NETWORK_SEGMENT            0x317
#define ROUTER_EXT_ERR_INVALID_LINK_ADDRESS                0x318
#define ROUTER_EXT_ERR_SECOND_RESOURCES_NOT_AVAILABLE    0x319
#define ROUTER_EXT_ERR_CONNECTION_ALREADY_ESTABLISHED    0x31A
#define ROUTER_EXT_ERR_DIRECT_CONN_ALREADY_ESTABLISHED    0x31B
#define ROUTER_EXT_ERR_MISC                                0x31C
#define ROUTER_EXT_ERR_REDUNDANT_CONNECTION_MISMATCH    0x31D
#define ROUTER_EXT_ERR_NO_MORE_CONSUMER_RESOURCES        0x31E
#define ROUTER_EXT_ERR_NO_TARGET_PATH_RESOURCES            0x31F
#define ROUTER_EXT_ERR_VENDOR_SPECIFIC                    0x320

/* The following are CIP (Ethernet/IP) service codes */
#define SVC_GET_ATTR_ALL          0x01        
#define SVC_SET_ATTR_ALL          0x02
#define SVC_GET_ATTR_LIST         0x03
#define SVC_SET_ATTR_LIST         0x04
#define SVC_RESET                 0x05
#define SVC_START                 0x06
#define SVC_STOP                  0x07
#define SVC_CREATE                0x08
#define SVC_DELETE                0x09
#define SVC_APPLY_ATTRIBUTES      0x0D
#define SVC_GET_ATTR_SINGLE       0x0E
#define SVC_SET_ATTR_SINGLE       0x10
#define SVC_FIND_NEXT_OBJ_INST    0x11
#define SVC_RESTORE               0x15
#define SVC_SAVE                  0x16
#define SVC_NO_OP                 0x17
#define SVC_GET_MEMBER            0x18
#define SVC_SET_MEMBER            0x19
#define SVC_CIP_DATA_TABLE_READ   0x4C
#define SVC_CIP_DATA_TABLE_WRITE  0x4D


/* The following macros are required for certain types of processors (i.e. ARM).
   They replace word and double word addressing with individual byte handling */

/* Please note that we assume that over the wire the data always is transferred
   in little-endian format, even if target and/or originator are using big-endian */

/*
** Macros for ENCAP number representation conversion.  Multi-byte fields
** in ENCAP are all LITTLE ENDIAN (x86 order).  If the byte order of 
** the target machine is not specified then LITTLE ENDIAN is assumed.
**
** These macros are provided in three forms:
**      1.) In Place Conversion
**              Converts a variable and assigns the new value
**              back to the variable.
**
**              ENCAP_CVT_HL    - Convert into Host Long
**              ENCAP_CVT_PL    - Convert into Protocol Long
**              ENCAP_CVT_HS    - Convert into Host Short
**              ENCAP_CVT_PS    - Convert into Protocol Short
**
**      2.) Value Conversion
**              Simply convert variable value.  This form can
**              be used on the right-hand side of an assignment.
**
**              ENCAP_TO_HL(x)  - To Host Long
**              ENCAP_TO_PL(x)  - To Protocol Long
**              ENCAP_TO_HS(x)  - To Host Short
**              ENCAP_TO_PS(x)  - To Protocol Short
**/

#ifndef HIBYTE
#define HIBYTE(w)           ((BYTE)(((UINT16)(w) >> 8) & 0xFF))
#endif
#ifndef LOBYTE
#define LOBYTE(w)           ((BYTE)(w))
#endif
#ifndef HIWORD
#define HIWORD(l)           ((UINT16)(((UINT32)(l) >> 16) & 0xFFFF))
#endif
#ifndef LOWORD
#define LOWORD(l)           ((UINT16)(l))
#endif
#ifndef MAKEWORD
#define MAKEWORD(a, b)      ((UINT16)((((BYTE)(a)) & 0xff) | ((UINT16)((((BYTE)(b)) << 8) & 0xff00))))
#endif
#ifndef MAKELONG                            
#define MAKELONG(a, b)      ((INT32)((((UINT16)(a)) & 0xffff) | ((UINT32)((((UINT16)(b)) << 16) & 0xffff0000))))
#endif

#define UINT32_SET( ptr, value )  { *(UINT8*)(ptr) = LOBYTE(LOWORD((UINT32)value));  \
                    *(UINT8*)(((UINT8*)(ptr))+1) = HIBYTE(LOWORD((UINT32)value));  \
                    *(UINT8*)(((UINT8*)(ptr))+2) = LOBYTE(HIWORD((UINT32)value));  \
                    *(UINT8*)(((UINT8*)(ptr))+3) = HIBYTE(HIWORD((UINT32)value));  }

#define UINT32_GET( ptr ) (UINT32) (MAKELONG(MAKEWORD((*(UINT8*)(ptr)),(*(UINT8*)(ptr+1))),MAKEWORD((*(UINT8*)(ptr+2)),(*(UINT8*)(ptr+3)))))

#define UINT16_SET( ptr, value )  { *(UINT8*)(ptr) = LOBYTE((UINT16)value);  \
                    *(UINT8*)(((UINT8*)(ptr))+1) = HIBYTE((UINT16)value); } 

#define UINT16_GET( ptr )  (UINT16) (MAKEWORD((*(UINT8*)(ptr)),(*(UINT8*)(ptr+1))))



#ifdef EIP_BIG_ENDIAN

#define _SWAPL_(a)              (((a) << 24) & 0xff000000) | (((a) << 8) & 0xff0000) | \
                                (((a) >> 8) & 0xff00) | ((((UINT32) (a)) >> 24) & 0xff)

#define _SWAPS_(a)              (((a & 0xff) << 8) | ((((a) >> 8)) & 0xff) )

#else    /* #ifdef EIP_BIG_ENDIAN */

#define _SWAPL_(a)              (a)
#define _SWAPS_(a)              (a)

#endif    /* #ifdef EIP_BIG_ENDIAN */


#define ENCAP_CVT_HL(x)         (x) = _SWAPL_((x))
#define ENCAP_CVT_PL(x)         (x) = _SWAPL_((x))
#define ENCAP_CVT_HS(x)         (x) = _SWAPS_((x))
#define ENCAP_CVT_PS(x)         (x) = _SWAPS_((x))

#define ENCAP_TO_HL(x)          _SWAPL_((x))
#define ENCAP_TO_PL(x)          _SWAPL_((x))
#define ENCAP_TO_HS(x)          _SWAPS_((x))
#define ENCAP_TO_PS(x)          _SWAPS_((x))

#endif /* ET_IP_API_H */





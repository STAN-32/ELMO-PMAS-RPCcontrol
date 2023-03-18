////////////////////////////////////////////////////////////////////////////////
/// \file MMC_definitions.h
/// Name        : mmc_lib_if.h
/// Author      : Arcady Chechik
/// Created on  : Jun 9, 2008
/// Update      : 24Feb2015 Haim H. for Integration Os (32/64 bit for LinuxIpc and Win, Vxworks and Linux Rpc)
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///             : 0.3.0 Update 12Aug2015 Haim H.
/// Update      : 24Feb2015 Haim H. for Integration Os (32/64 bit for LinuxIpc and Win, Vxworks and Linux Rpc)
///                               0.4.0 Updated 11Sep2017 Haim H.
///               0.4.2 Updated 26Aug2019 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for interface for MMC library
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_DEFINITIONS_H_
#define MMC_DEFINITIONS_H_

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif


#define MMC_IPC_WAIT_TIMEOUT_SEC    20
#define MMC_IPC_WAIT_TIMEOUT_NSEC   0

#define MMC_IF_MAGIC                0xFEFA


///////////////////////////////////////////////////////////////////////////////
/// \typedef MMC_CONNECT_HNDL
/// \brief Connection Handle Type.
///////////////////////////////////////////////////////////////////////////////
//HH???? typedef ELMO_UINT32 MMC_CONNECT_HNDL;
typedef  ELMO_PINT8 MMC_CONNECT_HNDL;

#define NC_MAX_NUM_AXES_IN_NODE             16      ///< Maximal number Axis in Group.


#define NODE_NAME_MAX_LENGTH                80      ///< Maximal length of Axis/Group name.

#define MAX_GETVERSION_CHARS                120     ///<Maximal length of MMC_GetVersion output string

#define NC_ENHANCED_MAX_REC_SIGNALS_NUM     96
#define NC_MAX_REC_SIGNALS_NUM              32      ///< Maximal number recorder signals.


#define NC_MAX_REC_PARAMS_NUM               8       ///< Maximal number recorder parameters.
#define NC_ENHANCED_REC_MAX_PARAMS_NUM      10      ///< Maximal number recorder parameters. //@ML 31.7.16 Enhanced Data Recording



#define NC_MAX_REC_PACKET_SIZE              1400    ///< Maximal length of packet recorded data.
#define NC_MAX_LONG                         NC_MAX_REC_PACKET_SIZE / 4  ///< Maximal length of packet recorded data.

#define NC_NODES_SING_AXIS_NUM                  96
#define NC_NODES_MULT_AXIS_NUM                      48

#define NC_MAX_BULK_READ_READABLE_PACKET_SIZE       350
#define NC_MAX_PI_BULK_READ_VARIABLES               175
#define NC_MAX_AXES_PER_BULK_READ                   100
#define NC_BULK_READ_DEFAULT_VARIABLES_PER_PRESET   5


MMC_LIB_API void endian_swap16(ELMO_PUINT16 x);
MMC_LIB_API void endian_swap32(ELMO_PUINT32 x);
MMC_LIB_API void endian_swap64(ELMO_PUINT64 x);


///////////////////////////////////////////////////////////////////////////////
/// \typedef MMC_CB_FUNC
/// \brief Callback function type.
///////////////////////////////////////////////////////////////////////////////
// HH typedef int (*MMC_CB_FUNC)(unsigned char*, short,void*);
typedef ELMO_INT32 (*MMC_CB_FUNC)(ELMO_PUINT8, ELMO_INT16, ELMO_PVOID,...);
typedef ELMO_INT32 (*MMC_MB_CLBK)(ELMO_PUINT8, ELMO_INT16, ELMO_PVOID,...); //MB support to MMCPP library. @YL 27-06-2011


//
///////////////////////////////////////////////////////////////////////////////
/// \typedef MMC_AXIS_REF_HNDL
/// \brief Axis/Group Reference Handle Type.
///////////////////////////////////////////////////////////////////////////////
typedef ELMO_UINT16 MMC_AXIS_REF_HNDL;

///////////////////////////////////////////////////////////////////////////////
/// \typedef NC_NODE_HNDL_T
/// This type define Node index.
///////////////////////////////////////////////////////////////////////////////
typedef ELMO_UINT32 NC_NODE_HNDL_T;

typedef ELMO_INT32 (*MMC_SYNC_TIMER_CB_FUNC)(void);

typedef struct mmc_sync_timer_data
{
    ELMO_PVOID               pMmcIf;
    MMC_SYNC_TIMER_CB_FUNC  func;
    ELMO_UINT16             usSYNCTimerTime;
}MMC_SYNC_TIMER_DATA;

// all include files
#include "MMC_host_comm_API.h"
#include "MMC_drive_comm_API.h"
#include "MMC_general_API.h"
#include "MMC_PLCopen_group_API.h"
#include "MMC_PLCopen_single_API.h"
#include "MMC_network_API.h"
#include "MMC_events_API.h"
#include "MMC_DS401_API.h"
#include "MMC_ECATIO_API.h"
#include "MMC_ErrorCorr_API.h"
#include "MMC_PVT_ECAM_API.h"
#include "iecctrl.h"
///////////////////////////////////////////////////////////////////////////////
// Download Firmware Phases
///////////////////////////////////////////////////////////////////////////////
#define DOWNLOAD_VERSION_PHASE_TFTP     0
#define DOWNLOAD_VERSION_PHASE_BURN     1
#define DOWNLOAD_VERSION_PHASE_CRC      2
//#define FALLBACK_VERSION_PHASE_CRC        3
#define DOWNLOAD_VERSION_PHASE_RESET    3
#define DOWNLOAD_VERSION_IMAGE_LOADEDOK 4
#define DOWNLOAD_VERSION_LOADING_IMAGE  5

///////////////////////////////////////////////////////////////////////////////
// Download Firmware Errors
///////////////////////////////////////////////////////////////////////////////
#define DOWNLOAD_VERSION_ERROR_FS               -1  ///< Download Firmware. Target file system error
#define DOWNLOAD_VERSION_ERROR_TFTP             -2  ///< Download Firmware. TFTP fail
#define DOWNLOAD_VERSION_ERROR_BURN             -3  ///< Download Firmware. Copy to flash is fail.
#define DOWNLOAD_VERSION_ERROR_CRC              -4  ///< Download Firmware. Wrong CRC.
#define DOWNLOAD_VERSION_NON_LINUX_IMAGE        -5  ///< Download Firmware. Image is not Linux type.
#define DOWNLOAD_VERSION_ERROR_DF_IN_PROCESS    -6  ///< Download Firmware. Error DF in process.
#define DOWNLOAD_VERSION_DIFFERENT_MD5SUM       -7  ///< Wrong MD5 CHKSum

#define FALLBACK_VERSION_ERROR_CRC              -8  ///< Fallback version has CRC error !!!
#define BOOTED_WITH_FALLBACK_VER_ERROR          -9  ///< Booted with fallback error

///////////////////////////////////////////////////////////////////////////////
// Communication library errors
///////////////////////////////////////////////////////////////////////////////
#define MMC_OK                               0      ///< No error. No warning. All OK.
#define MMC_WARNING                          100    ///< Get warning from G-MAS or Profiler or GMAS, refer to ErrorID variable to get the exact warning number
#define MMC_LIB_UPXML_WARNING                300    ///< Get warning from get User Param from XML file library
#define MMC_GMAS_ERROR                      -1      ///< Error occurred on GMAS side. Please refer to ErrorID for further information..
#define MMC_LIB_ERROR                       -2      ///< Error occurred on the library.
#define MMC_LIB_UPXML_ERROR                 -3      ///< Error occurred on Get User Parameter from XML file
#define MMC_LIB_SEND_ERR                    -2000   ///< Send data is fail.
#define MMC_LIB_RCV_TIMEOUT_ERR             -2001   ///< Timeout in receive response data.
#define MMC_LIB_RCV_SELECT_ERR              -2002   ///< Wait for response is fail.
#define MMC_LIB_RCV_ERR                     -2003   ///< Receive response data is fail.
#define MMC_LIB_RCV_SIZE_ERR                -2004   ///< Wrong received response data size.
#define MMC_LIB_CAN_RCV_TIMEOUT_ERR         -2005   ///< CAN received response data timeout.
#define MMC_LIB_AXISREF_ERR                 -2006   ///< Axis ref error.
#define MMC_LIB_DATA_ERR                    -2007   ///< Input Data error.
#define MMC_LIB_NOUDP_ERR                   -2008   ///< No UDP Callback connection established.
#define MMC_LIB_NOT_SUPPORTED_CONN_TYPE_ERR -2009   ///< Not Supported under current connection type
///////////////////////////////////////////////////////////////////////////////
/// Get User Parameter from XML file Errors code:
///////////////////////////////////////////////////////////////////////////////
#define MMC_LIB_UPXML_FILE_FORMAT           (-3010) /* XML file Syntax is not well form */
#define MMC_LIB_UPXML_FAIL_ALLOC            (-3011) /* Failed in allocation memory.     */
#define MMC_LIB_UPXML_OPEN_FAILD            (-3012) /* Failed in Open XML file.         */
#define MMC_LIB_UPXML_LONG_NAME             (-3013) /* File name (inc path) is too long */

#define MMC_LIB_UPXML_SAVE_wx_FAIL          (-3015) /* Req. protect write to exist file */

#define MMC_LIB_UPXML_WRITE_FAILD           (-3016) /* Actual len diff from element len */
#define MMC_LIB_UPXML_NUM_FORMAT            (-3017) /* Worng format for number          */
#define MMC_LIB_UPXML_NOT_SUPPORTNG         (-3018) /* Not supporting yet...            */
#define MMC_LIB_UPXML_ILLEGAL_ARRYSIZE      (-3019) /* Illegal array size (E.g: -1)     */


#define MMC_LIB_UPXML_UNEXP_CHR             (-3021) /* Found but has Unexpected char    */
#define MMC_LIB_UPXML_NOT_IN_RANGE          (-3022) /* Found Value outside of Min Max   */
#define MMC_LIB_UPXML_SAVE_w_FAILD          (-3023) /* Faild open file for write.       */

                                                    /* Sequence error (read with not    */
                                                    /* open; open more then once;       */
#define MMC_LIB_UPXML_SEQUENCE              (-3024)
#define MMC_LIB_UPXML_NOT_FOUND             (-3025) /* ENTRY NOT Found                  */   
#define MMC_LIB_UPXML_ILLEGAL_FLOAT_FORMAT  (-3026) /* Illegal parm for PutFloatFormat()*/

#define MMC_LIB_UTILTFTP_PARSE_OPT          (-3030) /* Util: Tftp activ. arg. parsing err   */
#define MMC_LIB_UTILTFTP_CREATE_LOCK        (-3031) /* Util: Tftp Cannot create sync lock   */
#define MMC_LIB_UTILTFTP_INIT               (-3032) /* Util: Tftp initialisation failure    */
#define MMC_LIB_UTILTFTP_START_SERVER       (-3033) /* Util: Tftp Server failed to start    */
#define MMC_LIB_UTILTFTP_INVLD_HOST_NAME    (-3034) /* Util: Tftp Invalid hostname specified*/   
#define MMC_LIB_UTILTFTP_INVLD_FILE_NAME    (-3035) /* Util: Tftp Invalid filename specified*/   
#define MMC_LIB_UTILTFTP_CLIENT_SEND_FILE   (-3036) /* Util: Tftp Send file failed          */
#define MMC_LIB_UTILTFTP_CLIENT_GET_FILE    (-3037) /* Util: Tftp Get file failed           */

#define MMC_LIB_EoE_DRV_ERR                 (-3050)
#define MMC_LIB_EoE_SENDCMD_ERR             (-3051)
#define MMC_LIB_EoE_RETRIES_ERR             (-3052)
#define MMC_LIB_EoE_SETASYNC_ERR            (-3053)
#define MMC_LIB_EoE_GETASYNC_ERR            (-3054)
#define MMC_LIB_EoE_SETSYNC_ERR             (-3055)
#define MMC_LIB_EoE_GETSYNC_ERR             (-3056)

#define MMC_LIB_EoE_INV_TYP_ERR             (-3057)
#define MMC_LIB_PI_VAR_ALIAS_SIZE_GREATER_THEN_PI_ALIASING_LENGTH    (-3060)    ///< The alias size is greater then PI_ALIASING_LENGTH
#define MMC_LIB_WRITE_PI_TO_ePI_INPUT_FORBIDDEN                      (-3061)    ///< Prevent write PI to input
#define MMC_LIB_PI_VAR_TYPE_NOT_MATCH                                (-3062)    ///< Try to read/write to type that is not matching the PI VAR type
#define MMC_LIB_PI_SIZE_INVALID                                      (-3063)    ///< ReadPI input size shoud be 4 for PI_REG_VAR_SIZE or 16 for PI_LARGE_VAR_SIZE
#define MMC_LIB_PI_VAR_READ_FROM_CLEAR_BULK                          (-3064)    ///< Try to read pi that is append to bulk read that was clear, unbind the PIVAR
#define MMC_LIB_PI_BULK_TRY_TO_EXCEED_BULK_READ_PI_SIGNALS_NUMBER    (-3070)    ///< When init bulk object with size that is greater then NC_MAX_BULK_READ_PI_SIGNALS or smaller then 1
#define MMC_LIB_PI_BULK_FAIL_TO_ALLOCATE                             (-3071)    ///< failed to allocate m_pVarsBulkReadEntryArray
#define MMC_LIB_PI_BULK_THE_PIVAR_ALLREADY_APPEND                    (-3072)    ///< The PIVar is allready append to a bulk read
#define MMC_LIB_PI_BULK_CANNOT_APPEND_ARRAY_FULL                     (-3073)    ///< Array of bulk read is full
#define MMC_LIB_PI_BULK_ALLREADY_INITIALIZED                         (-3074)    ///< The bulk read is allreay initialized , if you want to reuse execute clear()



#define MMC_LIB_UDP_CREATE_IP_ERR           (-3080)
#define MMC_LIB_UDP_CREATE_SOCKET_ERR       (-3081)
#define MMC_LIB_UDP_PORT_ERR                (-3082)
#define MMC_LIB_UDP_CREATE_BIND_ERR         (-3083)
#define MMC_LIB_UDP_CREATE_OPT_ERR          (-3084)
#define MMC_LIB_UDP_CREATE_CTRL_ERR         (-3085)
#define MMC_LIB_UDP_ISREADABLE_INI_ERR      (-3086)
#define MMC_LIB_UDP_ISREADABLE_SEL_ERR      (-3087)
#define MMC_LIB_UDP_SEND_SOCKINV_ERR        (-3088)
#define MMC_LIB_UDP_RECEIVE_SOCKINV_ERR     (-3089)
#define MMC_LIB_UDP_CONNECT_IP_ERR          (-3090)
#define MMC_LIB_UDP_CONNECT_SOCKET_ERR      (-3091)
#define MMC_LIB_UDP_CONNECT_CTRL_ERR        (-3092)
#define MMC_LIB_UDP_ISPENDING_INI_ERR       (-3093)
#define MMC_LIB_UDP_ISPENDING_SEL_ERR       (-3094)
#define MMC_LIB_TCP_ISREADABLE_INI_ERR      (-3095)
#define MMC_LIB_TCP_ISREADABLE_SEL_ERR      (-3096) 
#define MMC_LIB_TCP_CREATE_SOCKET_ERR       (-3097) 
#define MMC_LIB_TCP_CREATE_OPT_ERR          (-3098) 
#define MMC_LIB_TCP_CREATE_BIND_ERR         (-3099) 
#define MMC_LIB_TCP_CRTCLBK_SOCKET_ERR      (-3100) 
#define MMC_LIB_TCP_CRTCLBK_OPT_ERR         (-3101) 
#define MMC_LIB_TCP_CRTCLBK_BIND_ERR        (-3102) 
#define MMC_LIB_TCP_CRTCLBK_LSN_ERR         (-3103) 
#define MMC_LIB_TCP_RECEIVE_SEL_ERR         (-3104) 
#define MMC_LIB_TCP_CONNECT_IP_ERR          (-3105) 
#define MMC_LIB_TCP_CONNECT_SOCKET_ERR      (-3106) 
#define MMC_LIB_TCP_CONNECT_CTRL_ERR        (-3107) 
#define MMC_LIB_TCP_CONNECT_CONN_ERR        (-3108) 
#define MMC_LIB_TCP_ISWRITABLE_INI_ERR      (-3109) 
#define MMC_LIB_TCP_ISPENDING_INI_ERR       (-3110)
#define MMC_LIB_TCP_ISPENDING_SEL_ERR       (-3111)

#define MMC_LIB_CODESYS_SHM_NOT_STARTED     (-3300)
//
///////////////////////////////////////////////////////////////////////////////
/// Common Axis and Group Status Bit Mask
///////////////////////////////////////////////////////////////////////////////
#define NC_AXIS_DONE_MASK                   0x80000000  ///< Axis/Group Motion Done Bit Mask.
#define NC_AXIS_VALID_MASK                  0x40000000  ///< Axis/Group Data Valid Bit Mask.
#define NC_AXIS_ERROR_MASK                  0x20000000  ///< Axis/Group Error Bit Mask
#define NC_AXIS_PENDING_MASK                0x10000000  ///< Axis/Group Pending Bit Mask

///////////////////////////////////////////////////////////////////////////////
/// Function Block Status Bit Mask
///////////////////////////////////////////////////////////////////////////////
#define MC_FB_IN_CAM_MASK                   0x1000
#define MC_FB_CMD_ABORT_BIT_MASK            0x0200  ///< Function Block Command Abort Bit Mask. Veddor Defined. It's indicate that f.b. got abortion command.
#define MC_FB_BUSY_BIT_MASK                 0x0100  ///< Function Block Busy StateBit Mask.
#define MC_FB_ACTIVE_BIT_MASK               0x0080  ///< Function Block Active State Bit Mask.
#define MC_FB_DONE_BIT_MASK                 0x0040  ///< Function Block Done State Bit Mask.
#define MC_FB_ABORTED_BIT_MASK              0x0020  ///< Function Block Aborted State Bit Mask.
#define MC_FB_ERROR_BIT_MASK                0x0010  ///< Function Block Error State Bit Mask.
#define MC_FB_IN_GEAR_MASK                  0x0008  ///< Function Block In Gear State Bit Mask.
#define MC_FB_IN_SYNC_MASK                  0x0004  ///< Function Block In Sync State Bit Mask.
#define MC_FB_IN_VELOCITY_MASK              0x0002  ///< Function Block In Velocity State Bit Mask.
#define MC_FB_END_OF_PROFILE_MASK           0x0001  ///< Function Block End Of Profile State Bit Mask.




///////////////////////////////////////////////////////////////////////////////
// NC Driver Error IDs
///////////////////////////////////////////////////////////////////////////////
#define NC_OK                                   (0)
#define NC_ERR_DRV_FAIL                         (-1)    ///< NC driver error
#define NC_ERR_MMAP_FAIL                        (-2)    ///< NC driver mmap fail
#define NC_ERR_REC_LEN_TOO_LARGE                (-3)    ///< RL*num_set_bit(RC) more than maximal recorder buffer size
                                                    ///  or exceed size allocated upload data buffer.

#define NC_ERR_REC_ILLEGAL_GAP                  (-4)    ///< Illegal RG  value
#define NC_ERR_REC_BEGIN_WITHOUT_STOP           (-5)    ///< Call Begin Recording when RR is not zero

#define NC_WRONG_NODE_HNDL                      (-6)    ///< Wrong Node handle
#define NC_NODE_FB_LIST_IS_EMPTY                (-7)    ///< Node's function blocks list is empty
#define NC_UNSUITABLE_NODE_STATE                (-8)    ///< Node state is unsuitable for active function block
#define NC_NODE_NOT_FOUND                       (-9)    ///< Node is not found
#define NC_NODE_DISABLED                        (-10)   ///< This Node is disabled for use
#define NC_NODE_LIST_EMPTY                      (-11)   ///< No free Nodes in list
#define NC_WRONG_NODE_TYPE                      (-12)   ///< Type of Node excluded from Node handle is wrong

#define NC_WRONG_FB_TYPE                        (-13)   ///< Wrong function block type parameter
#define NC_FREE_FB_LIST_IS_EMPTY                (-14)   ///< Free function blocks list is empty
#define NC_NOT_SUPPORTED_FB_TYPE                (-15)   ///< Function block type not supported by NC
#define NC_FB_NOT_FOUND                         (-16)

#define NC_FREE_STATUS_LIST_IS_EMPTY            (-17)   ///< Free function blocks status structures list is empty
#define NC_STATUS_HNDL_NOT_VALID                (-18)   ///< Status handle parameter is not valid
#define NC_STATUS_STRUCT_IS_FREE                (-19)   ///< Status structure get is moved to free list
#define NC_STATE_FUNC_NOT_DEFINED               (-20)   ///< Function for change axis state is not defined

#define NC_GROUP_NODE_USED_BY_OTHER             (-21)   ///< Axis used by other vector.

#define NC_PARAM_OUT_OF_RANGE                   (-22)   ///< One of parameters out of permitted range
#define NC_INCOMPATIBLE_PERIOD_SHIFT            (-23)   ///< Axis Update Cycle Period or Shift is not compatible for Vector
#define NC_COORD_SYSTEM_NOT_ENABLE              (-24)   ///< Wrong coordinate system passed or coordinate system is not enable now
#define NC_GROUP_ISNOT_ENABLED                  (-25)   ///< Vector can't receive motion command because it's disabled

#define NC_NOT_ALL_RPC_CONN_CLOSED              (-26)   ///< More than one RPC connections are opened still.It's may happen in functions like download new firmware.
#define NC_NOT_ALL_IPC_CONN_CLOSED              (-26)   ///< At least  one IPC connection is opened still.It's may happen in functions like download new firmware.
#define NC_UDP_ADDR_IS_NULL                     (-27)   ///< UDP address is not set
#define NC_UDP_SOCKET_NOT_OPEN                  (-28)   ///< UDP socket is not opened
#define NC_UDP_SOCKET_OPEN_FAIL                 (-29)   ///< Open UDP socket fail
#define NC_UDP_SOCKET_BIND_FAIL                 (-30)   ///< Bimd UDP socket fail
#define NC_FUNC_NOT_SUPPORT_IPC                 (-31)   ///< Call this function from IPC is not permitted
#define NC_WRONG_CONN_TYPE                      (-32)   ///< Wrong connection type parameter
#define NC_SOME_AXES_ARE_POWER_ON               (-33)   ///< At least one of registered axis is powered on.

#define NC_SET_UDP_SOCKET_FAIL                  (-34)   ///< Set UDP socket function fail
#define NC_SET_UDP_ADDR_FAIL                    (-35)   ///< Set UDP address function fail
#define NC_SET_EVENT_MASK_FAIL                  (-36)   ///< Set event mask function fail

#define NC_GET_UDP_SOCKET_FAIL                  (-37)   ///< Get UDP socket function fail
#define NC_GET_UDP_ADDR_FAIL                    (-38)   ///< Get UDP address function fail
#define NC_GET_EVENT_MASK_FAIL                  (-39)   ///< Get event mask function fail

#define NC_IS_NOT_CONFIG_MODE                   (-40)   ///< MMC mode is not "Configuration Mode"

#define NC_SET_DHCP_FAIL                        (-42)   ///<
#define NC_WRONG_DHCP_EN_MODE                   (-43)   ///< DHCP enable mode is not 1-true/yes or 0-false
#define NC_CREATE_FORK_FAIL                     (-44)   ///< Linux Fork craetion fail

#define NC_READ_FROM_FLASH_FAIL                 (-45)   ///< Read configuration data from flash is failed
#define NC_SAVE_CONFIG_FAIL                     (-46)   ///< Configuration save is failed
#define NC_OPEN_DIR_FAIL                        (-47)   ///< Open directory is failed
#define NC_OPEN_FILE_FAIL                       (-48)   ///< Open file is failed

#define NC_NON_NC_ASSIGNMENT_FAIL               (-49)   ///< Motion parameter assignment is failed
#define NC_NON_NC_IN_MOTION                     (-50)   ///< Node in None-NC mode  
#define NC_NON_NC_HOME_FAIL                     (-51)   ///< Homing is failed
#define NC_NON_NC_REACTOR_FAIL                  (-52)

#define NC_MODE_NOT_SUPPORTED                   (-53)   ///< Mode that user request is not supported by firmware
#define NC_ONE_OR_LESS_MEMBERS_IN_GRP           (-54)   ///< Group contain less than 2 axis.

#define NC_LIB_CONNECTION_FAIL                  (-55)   ///< Library driver could not connect to target

#define NC_WRONG_MOTION_MODE_FAIL               (-56)   ///< Wrong motion mode
#define NC_WRONG_COMM_TYPE_FAIL                 (-57)   ///< Wrong communicaton type
#define NC_WRONG_FUNC_ARGUMENT_TYPE             (-58)   ///< Wrong function argument type
#define NC_VECTOR_NOT_FOUND                     (-59)   ///< Vector is not found
#define NC_NETWORK_SCAN_FAIL                    (-60)   ///< Network scan failure
#define NC_COMM_GET_STATISTICS_FAIL             (-61)   ///< Network get statistics failure
#define NC_COMM_RESET_STATISTICS_FAIL           (-62)   ///< Network reset statistics failure
#define NC_FS_FAIL                              (-63)   ///< FS(File System) failure.
#define NC_DYNAMIC_ALLOC_FAIL                   (-64)   ///< Dynamic allocation failure.
#define NC_XML_PARSER_FAIL                      (-65)   ///< XML parser failure.
#define NC_OPEN_COMM_FAIL                       (-66)   ///< Open communication failure.
#define NC_CLOSE_COMM_FAIL                      (-67)   ///< Close communication failure.
#define NC_COMM_SCAN_BUS_FAIL                   (-68)   ///< Communication scan bus process failure.
#define NC_DUPLICATED_MEMBER                    (-69)   ///< Attempt add axis member to group when axis or ID are present in group yet.
#define NC_MAX_MEMBERS_IN_VECTOR                (-70)   ///< Max numberof members in group is reached
#define NC_PR_PRECALC_FAIL                      (-71)   ///< One of profiler precalc functions call is fail
#define NC_PR_RECALC_END_VEL_FAIL               (-72)   ///< Precalculating End Velocity Failed.
#define NC_PR_MODIFY_SEG_ENDP_FAIL              (-73)   ///< Modifying the Endpoint segment failed

#define NC_DRV_NOT_INITIALIZE                   (-74)   ///< The RealTime Driver was not initialised due to a configuration / hardware error
#define NC_WRONG_PARAM_CAST_TYPE                (-75)   ///< Wrong type sent to function
#define NC_WRITE_ATTEMPT_RO_PARAMETER           (-76)   ///< There was an attempt to write to a read-only parameter
#define NC_WRONG_TRANSFORM_FUNC                 (-77)   ///< Wrong transformation type
#define NC_DRV_OPEN_FAIL                        (-78)   ///< Error opening Real Time Driver
#define NC_DRV_MUTEX_INIT_FAIL                  (-79)   ///< Mutex initialisation error
#define NC_DRV_MUTEX_LOCK_FAIL                  (-80)   ///< Error opening Real Time Driver
#define NC_WRONG_MEMBER_NODE_INDEX              (-81)   ///< Illegal node index

#define NC_KOBJECT_CREATE_FAIL                  (-82)   ///< Error Creating Resource File
#define NC_KOBJECT_NOT_VECTOR                   (-83)   ///< OObject is not a group
#define NC_KOBJECT_WRONG_COMM_TYPE              (-84)   ///< Wrong Communication Type
#define NC_KOBJECT_WRONG_KEYWORD                (-85)   ///< Keyword Error
#define NC_KOBJECT_WRONG_NODE_TYPE              (-86)   ///< Wrong node Type
#define NC_KOBJECT_WRONG_CYCLE_TIME             (-87)   ///< Illegal Cycle Time
#define NC_KOBJECT_WRONG_BAUDRATE               (-88)   ///< Wrong Baud Rate
#define NC_KOBJECT_OUT_OF_RANGE                 (-89)   ///< Object out of range
#define NC_KOBJECT_MAX_NODE_NUM_REACHED         (-90)   ///< Maximun number of axes reached
#define NC_KOBJECT_WRONG_NODE_NAME              (-91)   ///< Wrong node name
#define NC_KOBJECT_WRONG_NODE_CYCLE_PERIOD      (-92)   ///< Cycle Period Error
#define NC_KOBJECT_WRONG_NODE_CYCLE_SHIFT       (-93)   ///< Cycle Shift Error
#define NC_KOBJECT_NODE_OBJ_CREATE_FAIL         (-94)   ///< Error Creading Axis Object
#define NC_KOBJECT_VECTOR_OBJ_CREATE_FAIL       (-95)   ///< Error Creading Group Object
#define NC_KOBJECT_MAX_NUM_NODES_IN_VECTOR      (-96)   ///< Maximun number of axes in group reached
#define NC_PARAMS_SHMKEY_FAIL                   (-97)
#define NC_PARAMS_SHMGET_FAIL                   (-99)
#define NC_COMM_INIT_FAIL                       (-100)  ///< Communication Initialisation Error

#define NC_ONE_GRP_MEMBER_IS_DISABLED           (-101)  ///< One of the group members is disabled
#define NC_NOT_BUFFERED_SWITCH_COORD_MODE       (-102)  ///< You Must switch coordination mode

#define NC_SYNCHRONIZE_MOTION_PROHIBIT          (-103)  ///< Synchronised motion prohibited
    
#define NC_WRONG_REC_RV_PARAM                   (-104)  ///< Wrong recording RV parameter

#define NC_CHNG_COORD_SYSTEM_IN_MOTION          (-105)  ///< An attempt was made to modify coordination system during motion
#define NC_MCS_COORD_SYSTEM_IS_NOT_SET          (-106)  ///< MCS coordination system is not set

#define NC_NON_NC_PTP_MOTION_FAIL               (-107)  ///< Distributed motion fail
#define NC_NOT_2D_CIRC_ANGLE_MOTION             (-108)  ///< Not a 2D Circular angle motion
#define NC_WRONG_PARAM_NUMBER                   (-109)  ///< Wrong number of parameters.
#define NC_COMM_GET_DIAGNOSTICS_FAIL            (-110)  ///< Get Diagnostics Failed.
#define NC_NOT_DEFINED_VALUE_PARAM              (-111)  ///< Error while retrieving value. Value undefined.

#define NC_NON_NC_REACTOR_OVERFLOW_FAIL         (-112)  ///< Internal FIFO Overflow

#define NC_ALREADY_IN_MODE_FAIL                 (-113)  ///< Axis already in mode
#define NC_END_FB_LIST_REACHED                  (-114)
#define NC_INCOMP_BUFFER_TRANSITION_MODE        (-115)
/*
 * Error correction error IDs
 */
#define NC_ERROR_TABLE_HEADER_PARSING_ERROR     (-116)
#define NC_ERROR_TABLE_TABLE_PARSING_ERROR      (-117)
#define NC_ERROR_TABLE_NO_AVAILABLE_SPACE       (-118)
#define NC_ERROR_TABLE_ENTRY_ALREADY_TAKEN      (-119)
#define NC_ERROR_TABLE_ENABLED                  (-120)
#define NC_ERROR_TABLE_DISABLED                 (-121)
#define NC_ERROR_TABLE_LOADED                   (-122)
#define NC_ERROR_TABLE_UNLOADED                 (-123)
#define NC_ERROR_TABLE_AXIS_ALREADY_MAPPED      (-124)
#define NC_AXIS_IS_IN_ENABLED_GROUP             (-125)
#define NC_MODBUS_ERROR_TABLE_SIZE_EXCEEDED     (-126)
#define NC_MODBUS_ERROR_WRONG_TABLE_ID          (-127)
#define NC_MODBUS_ERROR_MODBUS_ALREADY_RUNNING  (-128)
#define NC_TFTP_ERROR                           (-129)
#define NC_TRANSITION_MODE_OUT_OF_RANGE         (-130)
#define NC_ERROR_TABLE_NUMBER_OUT_OF_RANGE      (-131)
#define NC_ERROR_TABLE_RESOLUTION_OUT_OF_RANGE  (-132)
#define NC_ERROR_TABLE_SEGMENT_OUT_OF_RANGE     (-133)
#define NC_REC_TRIGGER_WINDOW_OUT_OF_RANGE      (-134)
#define NC_FILE_TYPE_OUT_OF_RANGE               (-135)
#define NC_SET_IS_TO_LOAD_PARAM_OUT_OF_RANGE    (-136)
#define NC_SET_OVERRIDE_OUT_OF_RANGE            (-137)
#define NC_NUM_OF_AXES_OUT_OF_RANGE             (-138)
#define NC_TR_FUNC_TYPE_OUT_OF_RANGE            (-139)
#define NC_BUFFERED_MODE_OUT_OF_RANGE           (-140)
#define NC_HOMEDS402_METHOD_OUT_OF_RANGE        (-141)
#define NC_DIGITAL_INPUT_NUMBER_OUT_OF_RANGE    (-142)
#define NC_MAX_VELOCITY_OUT_OF_RANGE            (-143)
#define NC_MAX_ACCELERATION_OUT_OF_RANGE        (-144)
#define NC_MAX_DECCELERATION_OUT_OF_RANGE       (-145)
#define NC_MAX_JERK_OUT_OF_RANGE                (-146)
#define NC_DIRECTION_TYPE_OUT_OF_RANGE          (-147)
#define NC_NEGATIVE_VELOCITY                    (-148)
#define NC_COORD_SYSTEM_TYPE_OUT_OF_RANGE       (-149)
#define NC_CIRCLE_MODE_OUT_OF_RANGE             (-150)
#define NC_PATH_CHOICE_TYPE_OUT_OF_RANGE        (-151)
#define NC_ARC_SHORT_LONG_TYPE_OUT_OF_RANGE     (-152)
#define NC_POSITION_OUT_OF_RANGE                (-153)
///////////////////////////////////////////////////////////////////////////////
// FOE
///////////////////////////////////////////////////////////////////////////////
#define NC_COMM_FOE_STATE_TRANSIT_FAIL          (-154)
#define NC_COMM_FOE_FS                          (-155)
#define NC_COMM_FOE_WRITE_STREAM                (-156)
#define NC_COMM_FOE_CLOSE                       (-157)
#define NC_COMM_FOE_RETRY_MAX                   (-158)
#define NC_COMM_FOE_TFTP_FAIL                   (-159)
#define NC_COMM_FOE_ALL_SLAVES_FAIL             (-160)
#define NC_COMM_FOE_INVALID_SLAVES_NUM          (-161)
///////////////////////////////////////////////////////////////////////////////
// Bulk Read Error IDs
///////////////////////////////////////////////////////////////////////////////
#define NC_BULK_READ_RV_ARRAY_FAILURE           (-162)
#define NC_BULK_READ_UNSUPPORTED_MODE           (-163)
#define NC_BULK_READ_REQUESTED_DATA_TOO_BIG     (-164)
#define NC_BULK_READ_MEM_ALLOC_FAILURE          (-165)
#define NC_BULK_READ_UNALLOCATED_MEM_SEGMENT    (-166)
#define NC_BULK_READ_NUM_OF_AXES_OUT_OF_RANGE   (-167)
#define NC_BULK_READ_CONFIG_OUT_OF_RANGE        (-168)

#define NC_THREAD_CREATION_FAIL                 (-169)
#define NC_SYSTEM_CALL_FAIL                     (-170)
#define NC_COMM_CLOSED_FAIL                     (-171)
#define NC_INVALID_AXES_NUM                     (-172)
#define NC_INVALID_AXIS_ID                      (-173)
#define NC_IECCTRL_ILLEGAL_OPTION               (-174)
#define NC_IECCTRL_FAILED_TO_EXECUTE            (-175)
#define NC_WRONG_PARAM_TYPE                     (-176)

// Reset FB list error IDs
#define NC_CLEAR_FB_LIST_NODE_RETRIEVE_FAIL     (-177)
#define NC_CLEAR_FB_LIST_IN_MOTION_FAIL         (-178)
#define NC_CLEAR_FB_LIST_RESET_FAIL             (-179)

#define NC_TRANSITION_MODE_NOT_SUPPORTED        (-180)
#define NC_WRONG_COEFFS_RATIO                   (-181)
#define NC_INAPPROPRIATE_STATE_FOR_SETKIN       (-182)
#define NC_ENQUIRE_FB_STATUS_OUT_OF_RANGE       (-183)
#define NC_NOT_APPROPRIATE_PATH_CHOICE          (-184)
#define NC_NOT_APPROPRIATE_ARC_SHORT_LONG       (-185)
#define NC_UNDEFINED_PRECALC_PROFILER_ERROR     (-186)
#define NC_WRONG_EVENT_MODE                     (-187)
#define NC_SUPPORTED_ONLY_ON_3D_CASE            (-188)
#define NC_BULK_UPLOAD_IN_PROGRESS              (-189)
#define NC_BULK_UPLOAD_TIMEOUT_EXPIRED          (-190)
#define NC_BULK_UPLOAD_REQ_RSP_NOT_MATCH        (-191)
#define NC_BULK_UPLOAD_THREAD_CREATION_FAILED   (-192)
#define NC_BULK_UPLOAD_INIT_BULK_UPLOAD_FAILED  (-193)
#define NC_BULK_UPLOAD_DYNAMIC_ALLOC_FAILED     (-194)
#define NC_BULK_UPLOAD_SET_DELAY_FAILED         (-195)
#define NC_BULK_UPLOAD_ZERO_SIZE_BUFFER         (-196)
#define NC_BULK_UPLOAD_DATA_SIZE_TOO_BIG        (-197)
#define NC_BULK_UPLOAD_COMM_QUEUE_EMPTY         (-198)
#define NC_BULK_UPLOAD_COMM_MSG_LEN_IS_ZERO     (-199)
#define NC_BULK_UPLOAD_COMM_NOT_EXPECTED_MSG    (-200)
#define NC_BULK_UPLOAD_COMM_NOT_EXPECTED_SEQNO  (-201)
#define NC_BULK_UPLOAD_BOUNDS_OUT_OF_RANGE      (-202)
#define NC_KINEMATIC_DIRECTION_NOT_SUPPORTED    (-203)
#define NC_N_AXES_ARE_NOT_CONSECUTIVE           (-204)
#define NC_WRONG_PERSONALITY_FILE_FORMAT        (-205)
#define NC_DATA_NOT_FOUND_ON_PERSONALITY_FILE   (-206)
#define NC_ALL_AXES_SHOULD_BE_IN_KINEMATIC      (-207)
#define NC_NOT_SUPPORT_ONE_CARTESIAN_AXIS       (-208)
#define NC_NOT_SUPPORTED_COORDINATE_SYSTEM      (-209)
#define NC_NOT_SUPPORT_BLEND_TRANS_ON_ACS       (-210)
#define NC_HIGH_LOW_SW_LIMIT_CONTRADICTION      (-211)
#define NC_MOTION_FORBIDDEN_ON_HW_LIMIT         (-212)
#define NC_MOTION_FORBIDDEN_ON_ACS_SW_LIMIT     (-213)
#define NC_MA_FORBIDDEN_DIRECTION_ON_ACS_LIMIT  (-214)
#define NC_MOTION_FORBIDDEN_ON_MCS_SW_LIMIT     (-215)
#define NC_SA_MOTION_TOWARD_SW_LIMIT_FORBIDDEN  (-216)
#define NC_MA_MOTION_TOWARD_SW_LIMIT_FORBIDDEN  (-217)
#define NC_SA_FORBIDDEN_DIRECTION_ON_LIMIT      (-218)
#define NC_MA_FORBIDDEN_DIRECTION_ON_MCS_LIMIT  (-219)
#define NC_BULK_UPLOAD_SIZE_DOES_NOT_MATCH      (-220)
#define NC_BULK_UPLOAD_SEND_ACK_FAILED          (-221)
#define NC_PVT_ECAM_FAILED_TO_OPEN_FILE         (-222)
#define NC_PVT_ECAM_FAILED_TO_PARSE_HEADER      (-223)
#define NC_PVT_ECAM_UNCOMPATIBLE_TABLE_MODE     (-224)
#define NC_PVT_ECAM_FAILED_TO_PARSE_DATA        (-225)
#define NC_PVT_ECAM_TABLE_ALLOC_FAILED          (-226)
#define NC_TABLE_DIMENSION_DOES_NOT_MATCH       (-227)
#define NC_PVT_ECAM_MEM_HANDLE_OUT_OF_RANGE     (-228)
#define NC_PVT_ECAM_UNALLOCATED_SEGMENT_ERROR   (-229)
#define NC_PVT_ECAM_NUM_OF_PTS_DOES_NOT_MATCH   (-230)
#define NC_PVT_ECAM_PATH_FOR_ANOTHER_AXIS       (-231)
#define NC_PVT_ECAM_AT_LEAST_2_PTS_REQUIRED     (-232)
#define NC_PVT_ECAM_JOURNAL_HANDLE_OUT_OF_RANGE (-233)
#define NC_PVT_ECAM_INVALID_FILE_NAME           (-234)
#define NC_BUFFER_INSERTION_FORBIDDEN_ON_LIMIT  (-235)
#define NC_TORQUE_OUT_OF_RANGE                  (-236)
#define NC_PARAMETER_INDEX_OUT_OF_RANGE         (-237)
#define NC_CANNOT_DEFINE_SAME_NODE_TWICE        (-238)
#define NC_PVT_ECAM_INDEX_RETRIEVE_FAIL         (-239)
#define NC_PVT_ECAM_INDEX_IS_CLOSE_TO_CURRENT   (-240)
#define NC_PVT_ECAM_TABLE_IS_NOT_INITIALIZED    (-241)
#define NC_PVT_ECAM_OVERFLOW_TABLE_ERROR        (-242)
#define NC_PVT_ECAM_START_INDEX_OUT_OF_RANGE    (-243)
#define NC_PVT_ECAM_END_INDEX_OUT_OF_RANGE      (-244)
#define NC_PVT_ECAM_NO_POINTS_IN_TABLE          (-245)
#define NC_PVT_ECAM_NOT_ADJACENT_APPEND         (-246)
#define NC_PVT_ECAM_UNDERFLOW_THRESHOLD_TOO_BIG (-247)
#define NC_MODBUS_MAXIMUM_PACKET_SIZE_EXCEEDED  (-248)
#define NC_AXIS_LINK_MODE_OUT_OF_RANGE          (-249)
#define NC_AXIS_LINK_ONE_OF_AXES_NOT_IN_STD     (-250)
#define NC_AXIS_LINK_SLAVE_CANNOT_BE_PHYSICAL   (-251)
#define NC_AXIS_LINK_SLAVE_SHOULD_BE_IN_ZERO_POS (-252)
#define NC_AXIS_LINK_CANNOT_UNLINK_DURING_SLAVE_MOTION (-253)
#define NC_AXIS_LINK_CANNOT_LINK_AXIS_TWICE     (-254)
#define NC_AXIS_LINK_ONLY_DS402_TYPE_SUPPORTED  (-255)
#define NC_FILE_NOT_EXIST                       (-256)
#define NC_NOT_SUPPORTED_VALUE_TYPE_FOR_TRIGGER (-257)
#define NC_PARAMETER_CANNOT_BE_QUEUED_SET       (-258)
#define NC_WRONG_NUMBER_OF_PARAMETERS           (-259)
//////////////////////////////////////////////////////
// Dwell
//////////////////////////////////////////////////////
#define NC_DWELL_IS_TOO_SHORT                   (-260)

//////////////////////////////////////////////////////
// Administrative FB handling
//////////////////////////////////////////////////////
#define NC_MAX_IMM_FB_LIMIT_REACHED             (-261)

//////////////////////////////////////////////////////
// PVT/ECAM - continued
//////////////////////////////////////////////////////
#define NC_PVT_ECAM_CYCLIC_MODE_OUT_OF_RANGE    (-262)
#define NC_PVT_ECAM_DYNAMIC_MODE_OUT_OF_RANGE   (-263)
#define NC_PVT_ECAM_AUTO_MODE_OUT_OF_RANGE      (-264)
#define NC_PVT_ECAM_POS_ABSOLUTE_OUT_OF_RANGE   (-265)
#define NC_PVT_ECAM_TIME_ABSOLUTE_OUT_OF_RANGE  (-266)
#define NC_PVT_ECAM_FILE_MODE_IS_NOT_ALLOWED    (-267)
#define NC_PVT_ECAM_APPEND_DYNAMIC_TO_STATIC    (-268)
#define NC_PVT_ECAM_TIME_INTERVAL_TOO_SMALL     (-269)
#define NC_PVT_ECAM_SPLINE_INSERTION_FORBIDDEN  (-270)
#define NC_SPLINE_PVT_INSERTION_FORBIDDEN       (-271)
#define NC_PREV_FB_EXECUTE_NOT_SET              (-272)
#define NC_PVT_ECAM_CYCLIC_AND_T_ABS_PROHIBITED (-273)
#define NC_FAIL_TO_COPY_FILE_TO_TARGET          (-274)
#define NC_ERROR_TABLE_MEMORY_OVERLAPING        (-275)
#define NC_CANNOT_ENABLE_VIRTUAL_ENCODER        (-276)
#define NC_TABLE_CONTRADICTION_OF_COORD_SYS     (-277)
#define NC_TABLE_SUPPORT_ONLY_CART_MCS          (-278)
#define NC_PVT_ECAM_BIG_APPEND_BLOCK_SIZE       (-279)
#define NC_JOURNAL_BIG_TABLE_SIZE               (-280)

///////////////////////////////////////////////////////////////////////////////
// CAN Errors
///////////////////////////////////////////////////////////////////////////////
#define NC_SDO_ABORTED                          (-281)
#define NC_SDO_TIMEOUT                          (-282)
#define NC_CAN_DRV_FAIL                         (-283)
#define NC_SDO_SEG_TOGGLE_BIT_UNCHANGED         (-284)
#define NC_INVALID_PDO_NUM                      (-285)
#define NC_FAULT_BIT_RESET_TIMEOUT              (-286)
#define NC_MOTOR_OFF_TIMEOUT                    (-287)
#define NC_WRONG_PDO_LENGTH                     (-288)
#define NC_CAN_ERROR_INTERRUPT                  (-289)
///////////////////////////////////////////////////////////////////////////////
#define NC_OP_MODE_DISPLAY_INCONSISTENT         (-290)
#define NC_INTERPRETER_CMD_ERROR                (-291)
#define NC_INTERPRETER_CMD_LENGTH_ERROR         (-292)
#define NC_UDP_MESSAGE_SEND_FAILED              (-293)
#define NC_AXIS_IS_VIRTUAL                      (-294)
#define NC_STRTOL_FAILED                        (-295)
#define NC_IP_VALIDATION_TIMEOUT                (-296)
#define NC_RESOURCE_FILE_NO_IO_TYPE             (-297)
#define NC_INVALID_GROUP_NUM                    (-298)
#define NC_RESET_IS_ALREADY_IN_PROGRESS         (-299)
#define NC_TELNET_SERVER_THREAD_CREATION_FAIL   (-300)
#define NC_TABLE_TO_NONTABLE_FB_FAIL            (-301)
#define NC_TWO_CONSEQUENT_POLYNOM_FAIL          (-302)
#define NC_ABORTION_MODE_NOT_SUPPORTED          (-303)
#define NC_BULK_READ_UNSUPPORTED_VECTOR         (-304)
#define NC_TRANSITION_AFTER_POLYNOM_FAIL        (-305)
#define NC_SET_OVERRIDE_IDX_OUT_OF_RANGE        (-306)
#define NC_RPC_SERVER_THREAD_CREATION_FAIL      (-307)
#define NC_IPC_SERVER_THREAD_CREATION_FAIL      (-308)
#define NC_SET_SCHED_FAIL                       (-309)
#define NC_SOCKET_CREATION_FAILED               (-310)
#define NC_CHANGE_SOCK_OWNER_FAILED             (-311)
#define NC_SET_SOCKET_OPT_FAIL                  (-312)
#define NC_FAILED_TO_GET_IP_ADDR_FROM_SOCK      (-313)
#define NC_BIND_FAILED                          (-314)
#define NC_LISTEN_FAILED                        (-315)
#define NC_ACCEPT_FAILED                        (-316)
#define NC_THREAD_ATTR_FAILED                   (-317)
#define NC_THREAD_ATTR_DESTROY_FAILED           (-318)
#define NC_THREAD_DETACH_FAILED                 (-319)
#define NC_IPC_INITIALIZATION_FAILED            (-320)
#define NC_MAX_CONNECTIONS_REACHED              (-321)
#define NC_OPEN_ETHERCAT_COMM_FAIL              (-322)
#define NC_ETHERCAT_STATE_TRANSITION_TIMEOUT    (-323)
#define NC_NODE_INIT_IS_ALREADY_IN_PROGRESS     (-324)
#define NC_ETHERCAT_SLAVE_ERROR_RESET_FAILED    (-325)
#define NC_ETHERCAT_REGISTER_WRITE_FAIL         (-326)
#define NC_NO_NODES_ON_RESOURCE_FILE            (-327)
#define NC_BAD_SYNC_FACTOR                      (-328)
#define NC_BAD_HEARTBEAT_FACTOR                 (-329)
#define NC_KINEMATIC_TYPE_OUT_OF_RANGE          (-330)
#define NC_DELTA_ROBOT_DIRECT_KIN_FAIL          (-331)
#define NC_DELTA_ROBOT_INVERSE_KIN_FAIL         (-332)
#define NC_PCS_COORD_SYSTEM_IS_NOT_SET          (-333)
#define NC_DELTA_ROBOT_MISSING_THETA_DEFINITION (-334)
#define NC_DELTA_ROBOT_ZERO_NEGATIVE_MECHANIC   (-335)
#define NC_DELTA_ROBOT_WRONG_MECHANIC_RATIO     (-336)
#define NC_CANNOT_GET_VALIDATION_FUNCTION       (-337)
#define NC_CONDITIONFB_OP_OUT_OF_RANGE          (-338)
#define NC_CONDITIONFB_NOT_SUPPORT_GLB_PARAM    (-339)
#define NC_CONDITIONFB_PRM_NOT_FIT_TO_NODE_TYPE (-340)
#define NC_CONDITIONFB_PRM_TYPE_ERROR           (-341)
#define NC_ERROR_TABLE_HIGH_CORRECTION_VALUE    (-342)
#define NC_ETHERCAT_REGISTER_READ_FAIL          (-343)
#define NC_EXCEEDED_MAX_LENGTH                  (-344)
#define NC_PI_PARSER_WRONG_ATTRIBUTE            (-345)
#define NC_PI_PARSER_VAR_OFFSET_TO_LARGE        (-346)
#define NC_PI_PARSER_VAR_OFFSET_DUPLICATED      (-347)
#define NC_PI_PARSER_ELEMENT_NOT_FOUND          (-348)
#define NC_PI_PARSER_BITSIZE_TOO_LARGE          (-349)
#define NC_PI_PARSER_MISMATCHING_VAR_NUM        (-350)
#define NC_PI_PARSER_INPUTS_DUPLICATED          (-351)
#define NC_PI_PARSER_OUTPUTS_DUPLICATED         (-352)
#define NC_PI_PARSER_IN_OUT_ELEMENT_MISSING     (-353)
#define NC_PI_PARSER_WRONG_VARIABLES_NUM        (-354)
#define NC_PI_EXCEEDED_MAX_MEMORY               (-355)
#define NC_PI_VAR_INDEX_TOO_LARGE               (-356)
#define NC_PI_INVALID_DIRECTION                 (-357)
#define NC_PI_INCOMPATIBLE_BIT_SIZE             (-358)
#define NC_CHANGEOPMODEFB_NOT_ALL_VARS_MAPPED   (-359)
#define NC_ETHERCAT_CHANGE_STATE_TIMEOUT        (-360)
#define NC_PI_PARSER_MISMATCHING_VAR_TYPE       (-361)
#define NC_NO_NODES_CONNECTED                   (-362)
#define NC_WRONG_KINEMATIC_DIRECTION_TYPE       (-363)
#define NC_UU_MODIFICATION_WRONG_STATE          (-364)
#define NC_UU_MEMBERS_HAS_DIFFERENT_UU          (-365)
#define NC_UU_CANNOT_SET_WHEN_GROUP_ACTIVE      (-366)
#define NC_TWO_REPETITIVE_FB_FAIL               (-367)
#define NC_MOTION_AFTER_REPETITIVE_FORBIDEN     (-368)
#define NC_VELOCITY_OUT_OF_RANGE_NON_NC         (-369)
#define NC_AC_OUT_OF_RANGE_NON_NC               (-370)
#define NC_DC_OUT_OF_RANGE_NON_NC               (-371)
#define NC_POSITION_OUT_OF_RANGE_NON_NC         (-372)
#define NC_SET_POS_DS402                        (-373)
#define NC_SET_POS_WRONG_STATE                  (-374)
#define NC_SET_POS_QUEUED_MODE_NOT_SUPPORTED    (-375)
#define NC_SET_MODULO_NEGATIVE_RANGE            (-376)
#define NC_RADO_ONLY_NEG_POS_ON_MOVE_VEL        (-377)
#define NC_RADO_OUT_OF_RANGE                    (-378)
#define NC_MODULO_ERROR_CORRECTION_RANGE_ERROR  (-379)
#define NC_MODULO_CHANGE_TYPE_MODE_ERROR        (-380)
#define NC_EXECUTION_MODE_OUT_OF_RANGE          (-381)
#define NC_NON_NC_MODE_FOR_VIRTUAL_AXIS_ERROR   (-382)
#define NC_OP_MODE_OUT_OF_RANGE                 (-383)
#define NC_NON_NC_OPMODE_REQUEST_PENDING_ERROR  (-384)
#define NC_SET_QUEUED_OPMODE_CAN_ERROR          (-385)
#define NC_SET_QUEUED_IP_MODE_ERROR             (-386)
#define NC_ONE_GRP_MEMBER_IS_PENDING            (-387)
#define NC_PI_PARSER_WRONG_BIT_SIZE             (-388)
#define NC_TARGET_TORQUE_NOT_MAPPED             (-389)
#define NC_MOTION_MODE_NOT_SUPPORTED            (-390)
#define NC_MOTOR_ON_TIMEOUT                     (-391)
#define NC_CHANGEOPMODE_FB_IN_QUEUE             (-392)
#define NC_FUNCTION_OBSOLETE                    (-393)
#define NC_TARGET_TORQUE_OUT_OF_RANGE           (-394)
#define NC_TARGET_TORQUE_OUT_OF_DS402_RANGE     (-395)
#define NC_TORQUE_VELOCITY_OUT_OF_RANGE         (-396)
#define NC_TORQUE_ACCELERATION_OUT_OF_RANGE     (-397)
#define NC_ZERO_RATED_CURRENT                   (-398)
#define NC_MOVE_TORQUE_BLENDED_ERROR            (-399)
#define NC_CHANGE_OP_MODE_PENDING_ERROR         (-400)
#define NC_WRONG_STOP_FUNC_ID                   (-401)
#define NC_CHANGEOPMODE_IN_PROGRESS             (-402)
#define NC_ECAT_CANNOT_GET_SLAVE_STATE          (-403)
#define NC_PI_PARSER_ALIGNMENT_OBJECT           (-404)
#define NC_DRIVE_CONTROL_VARS_NOT_MAPPED        (-405)
#define NC_ELMO_DRIVE_POSITION_NOT_MAPPED       (-406)
#define NC_NO_INPUTS_OR_OUTPUTS                 (-407)
#define NC_TARGET_VELOCITY_NOT_MAPPED           (-408)
#define NC_HOMING_ATTAINED_BIT_IS_ON            (-409)
#define NC_DETECTION_TIME_LIMIT_OUT_OF_RANGE    (-410)
#define NC_PROFILE_TORQUE_NOT_SUPPORTED         (-411)
#define NC_CANNOT_REQUEST_MASTER_STATE          (-412)
#define NC_CANNOT_SCAN_NETWORK                  (-413)
#define NC_ECAT_SLAVE_IS_IN_AL_ERROR            (-414)
#define NC_OPERATION_IS_IN_PROGRESS             (-415)
#define NC_POWER_FSTM_INTERRUPTED               (-416)
#define NC_PI_PARSER_ADD_DATA_NOT_INSERTED      (-417)
#define NC_CAN_INTERRUPT_PASSIVE                (-418)
#define NC_CAN_BUS_OVERRUN                      (-419)
#define NC_NODE_REINITIALIZED                   (-420)
#define NC_PI_VAR_NOT_FOUND                     (-421)
#define NC_PI_VAR_NUM_TOO_LARGE                 (-422)
#define NC_PI_INVALID_INDEX                     (-423)
#define NC_PI_VAR_NOT_SUPPORTED                 (-424)
#define NC_PI_IMMEDIATE_WRITE_NOT_SUPPORTED     (-425)
#define NC_PI_BOOL_OP_NOT_SUPPORTED             (-426)
#define NC_PI_REC_LARGE_VAR_UNFINISHED          (-427)
#define NC_PI_TRIGGER_INVALID_DIRECTION         (-428)
#define NC_FP_VAR_IS_NAN                        (-429)
#define NC_REC_BOOL_TRIGGER_NOT_SUPPORTED       (-430)
#define NC_USR_COMMAND_FAIL_TO_START            (-431)
#define NC_USR_COMMAND_FAIL_TO_STOP             (-432)
#define NC_USR_COMMAND_FAIL_TO_REMOVE           (-433)
#define NC_USR_COMMAND_EXCEED_MAX_RUNNING_PROGRAM (-434)
#define NC_TOUCH_PROB_COUNTER_ZERO_VALUE_ONLY   (-435)
#define NC_POWER_FAIL_HW_POS_LARG_MODULO_RANG   (-436)
#define NC_PI_BULK_READ_NO_VARS                 (-437)
#define NC_KOBJECT_ID_DUPLICATED                (-438)
#define NC_KOBJECT_NAME_DUPLICATED              (-439)
#define NC_MEMORY_NOT_ALLOCATED                 (-440)
#define NC_SDO_SYSTEM_CALL_FAILED               (-441)
#define NC_CAN_STOP_ONLY_DS402_NODE             (-442)
#define NC_CAN_POWER_OFF_ONLY_DS402_NODE        (-443)
#define NC_WRONG_ERROR_TYPE                     (-444)
#define NC_ERROR_HANDLING_IS_IN_PROGRESS        (-445)
#define NC_INVALID_CONFIGURATION                (-446)
#define NC_POLICY_CANNOT_APPLY_ALL              (-447)
#define NC_WRONG_IDENTITY                       (-448)
#define NC_SYSTEM_ERROR_OCCURRED                (-449)
#define NC_CANNOT_RECOVER_ERROR                 (-450)
#define NC_THREHOLD_CANNOT_BE_CHANGED           (-451)
#define NC_TOO_MANY_MEMBERS                     (-452)
#define NC_AXIS_IS_NOT_CONNECTED                (-453)
#define NC_AXIS_IS_IN_ERROR                     (-454)
#define NC_POLICY_APPLIED_PARTIALLY             (-455)
#define NC_NODE_ERR_EVENT_CANNOT_APPLY_ALL      (-456)
#define NC_CAN_POWER_OFF_ONLY_AFTER_STOP        (-457)
#define NC_CANNOT_SAFEOP_IN_CAN                 (-458)
#define NC_REACTION_MUST_BE_APPLIED             (-459)
#define NC_COULDNT_DISABLE_GROUP                (-460)
#define NC_FOE_IN_PROGRESS                      (-461)
#define NC_MAX_CYCLES_EXCEEDS_TIMEOUT           (-462)
#define NC_ERROR_RELEVANT_FOR_DS402_ONLY        (-463)
#define NC_POLICY_DOES_NOT_EXIST                (-464)
#define NC_GMAS_IS_INITIALIZING                 (-465)
#define NC_GMAS_IS_IN_CONFIG_MODE               (-466)
#define NC_SAFEOP_SYSTEM_ONLY                   (-467)
#define NC_PORTS_OPEN_TIMEOUT                   (-468)
#define NC_BULK_READ_LOW_HIGH_MISMATCH          (-469)
#define NC_BULK_READ_WRONG_VARIABLE_TYPE        (-470)
#define NC_POWER_FSTM_IN_PROGRESS               (-471)
#define NC_XML_MISMATCH_VERSION                 (-472)
#define NC_MASTER_CREATE_FAIL                   (-473)
#define NC_MASTER_CONNECT_FAIL                  (-474)
#define NC_SET_AUTORECOVERY_FAIL                (-475)
#define NC_STOP_CYCLIC_OP_FAIL                  (-476)
#define NC_START_CYCLIC_OP_FAIL                 (-477)
#define NC_MASTER_XML_PARSER_FAIL               (-478)
#define NC_SCARA_ROBOT_INVERSE_KIN_FAIL         (-479)
#define NC_SCARA_ROBOT_DIRECT_KIN_FAIL          (-480)
#define NC_SCARA_ROBOT_WRONG_ELBOW_DIR          (-481)
#define NC_SCARA_ROBOT_MISSING_THETA_DEFINITION (-482)
#define NC_SCARA_ROBOT_ZERO_NEGATIVE_MECHANIC   (-483)
#define NC_3LINK_ROBOT_INVERSE_KIN_FAIL         (-484)
#define NC_3LINK_ROBOT_DIRECT_KIN_FAIL          (-485)
#define NC_3LINK_ROBOT_WRONG_ELBOW_DIR          (-486)
#define NC_3LINK_ROBOT_MISSING_THETA_DEFINITION (-487)
#define NC_3LINK_ROBOT_ZERO_NEGATIVE_MECHANIC   (-488)
#define NC_INAPPROPRIATE_STATE_FOR_SETCARTESIAN (-489)
#define NC_INAPPROPRIATE_STATE_FOR_CONVEYORBELT (-490)
#define NC_INAPPROPRIATE_STATE_FOR_ROTARYTABLE  (-491)
#define NC_WRONG_PCS_MCS_TRANSFORM_TYPE         (-492)
#define NC_RESET_SYSTEM_NO_ERR                  (-493)
#define NC_ERR_ENHANCED_REC_RV_MUST_BE_ALIGNE   (-494)
#define NC_ERR_ENHANCED_REC_LARGE_VAR_UNFINISHED (-495)
#define NC_ERR_LOAD_KINEMATIC_FAILED            (-496)
#define NC_ERR_KINEMATIC_WAS_NOT_DEFINED        (-497)

#define NOT_SUPPORTED_HARDWARE                  (-522)

///////////////////////////////////////////////////////////////////////////////
// ECAM/ONLS Tables Errors
///////////////////////////////////////////////////////////////////////////////
// ECAM/ONLS Tables Errors
///////////////////////////////////////////////////////////////////////////////
#define TABLE_NOTSELECTED_ERR                   (-500)
#define TABLE_PNTSNUM_UNDERFLOW_ERR             (-501)
#define TABLE_VERSION_ERR                       (-502)
#define TABLE_COLUMNS_NUM_ERR                   (-503)
#define TABLE_INVALID_NODE_TYPE_ERR             (-504)
#define TABLE_STARTPNT_OUTOF_RANGE_ERR          (-505)
#define TABLE_MONOTONIC_ERR                     (-506)
#define TABLE_ROMODE_ERR                        (-507)
#define TABLE_SCALING_ERR                       (-508)
#define TABLE_MASTERDIST_ERR                    (-517)
#define TABLE_MASTERSYNC_ERR                    (-518)
///////////////////////////////////////////////////////////////////////////////
// MODBUS SHM Errors
///////////////////////////////////////////////////////////////////////////////
#define NC_MBUS_SHMGET_FAIL                     (-570)
#define NC_MBUS_SHMGET_FAIL_EXIST               (-571)
#define NC_MBUS_SHMMAP_FAIL                     (-572)
#define NC_MBUS_COMM_AREA_NOT_AVAIL             (-573)
///////////////////////////////////////////////////////////////////////////////
// NC Driver Warning IDs
///////////////////////////////////////////////////////////////////////////////
#define NC_AXIS_IS_ALREADY_IN_POWER_OFF         (2000)
#define NC_AXIS_IS_ALREADY_IN_POWER_ON          (2001)
#define NC_AXIS_IS_ALREADY_IN_MOTION_MODE       (2002)
#define NC_TOUCHPROBE_IS_ALREADY_ENABLED        (2003)
#define NC_TOUCHPROBE_IS_ALREADY_DISABLED       (2004)
#define NC_FAST_REF_IS_NOT_MAPPED               (2005)

///////////////////////////////////////////////////////////////////////////////
/// Warning: Get User Parameter from XML file:
///////////////////////////////////////////////////////////////////////////////
#define MMC_LIB_UPXML_DEF_NOT_FOUND         3020    /* Set Def; NOT Found               */ 
#define MMC_LIB_UPXML_DEF_UNEXP_CHR         3021    /* Set Def; Found Unexpected char   */ 
#define MMC_LIB_UPXML_DEF_NOT_IN_RANGE      3022    /* Set Def; Found Val out of Min Max*/ 
#define MMC_LIB_UPXML_UPDATE_L3_ELEM        3023    /* Update Elem Val. (exist)   in Lvl 3  */
#define MMC_LIB_UPXML_UPDATE_L2_ELEM        3024    /* Create (Upd tree) new Elem in Lvl 2  */
#define MMC_LIB_UPXML_UPDATE_L1_ELEM        3025    /* Create (Upd tree) new Elem in Lvl 1  */

///////////////////////////////////////////////////////////////////////////////
// NC Profiler Error IDs
///////////////////////////////////////////////////////////////////////////////
#define NC_GET_ACTIVE_FB_REJECT             (-1000)  ///< NC_GetActiveFb() returned -1
#define NC_GET_NEXT_FB_REJECT               (-1001)  ///< NC_GetNextFb() returned -1
#define NC_GET_PREV_FB_REJECT               (-1002)  ///< NC_GetPrevFb
#define NC_GET_LAST_FB_REJECT               (-1003)  ///< NC_GetPrevFb
#define NC_GET_PREV_FB_REJECT_REV           (-1004)  ///< NC_GetPrevFb
#define NC_GET_LAST_FB_REJECT_REV           (-1005)  ///< NC_GetPrevFb
#define NC_GET_NEXT_FB_REJECT_REV           (-1006)  ///< NC_GetNextFb() returned -1
#define NC_GET_PREV_FB_REJECT_MSEP          (-1007)  ///< NC_GetPrevFb
#define NC_GET_NEXT_FB_REJECT_MSEP          (-1008)  ///< NC_GetNextFb() returned -1
#define NC_MOVE_ACTIVE_FB_REJECT            (-1009)
#define NC_GET_ACTIVE_FB_PTR_REJECT         (-1010)
#define NC_FB_IND_GT_NUM_FB_IN_QUE          (-1011)
#define NC_NULL_FB_PTR                      (-1012)

#define NC_ZERO_LEN_FB_OLD                  (-1020)  ///< No longer relevant from version 1031
#define NC_ZERO_LEN_LINE_SEG_OLD            (-1021)  ///< No longer relevant from version 1031
#define NC_ZERO_LEN_CIRC_SEG_OLD            (-1022)  ///< No longer relevant from version 1031
#define NC_ZERO_LEN_ACS_SEG_OLD             (-1023)  ///< No longer relevant from version 1031
#define NC_ZERO_LEN_SINGLE_AXIS_SEG_OLD     (-1024)  ///< No longer relevant from version 1031
#define NC_TRANS_CURVE_FAILED               (-1025)  ///< Transition curve was not built because of any reason
#define NC_3D_CIRCLE_MODE2_PI_OR_2PI        (-1026)  ///< 3D circle is undefined
#define NC_FALSE_CIRCLE_PARAMS              (-1027)  ///< contradiction between circle params
#define NC_NOT_SUPPORTED_TRANS_CURVE        (-1028)  ///< 3D Transition curve: circle-line, line-circle or circle-circle is not supported             
#define NC_ROOT_NGTV_CALC_MAX_VEND          (-1029)  ///< root from negative value in CalcMaxPossibleVendOpt()
#define NC_MAP_TO_PLANE_RADIUS_ZERO_U0      (-1030)  ///< MapToPlaneRadius() - vector Uo with zero lingth 
#define NC_MAP_TO_PLANE_RADIUS_ZERO_W0      (-1031)  ///< MapToPlaneRadius() - vector Wo with zero lingth 
#define NC_MAP_TO_PLANE_RADIUS_ZERO_R       (-1032)  ///< MapToPlaneRadius() - vector zero lingth radius 
#define NC_MAP_TO_PLANE_CENTER_ZERO_R       (-1033)  ///< CircDefByCenter() - zero radius was calculated
#define NC_CIRCLE_CENTER_ZERO_R             (-1034)  ///< CircDefByCenter() calculated zero radius 
#define NC_TWO_POSSIBLE_CENTERS_ERROR       (-1035)  ///< CalcTwoPossibleCenters() root from negative value
#define NC_CIRCLE_ZERO_RADIUS_PARAM         (-1036)  ///< Circle mode radius - zero input parameter
#define NC_MODIF_SEG_END_POINT_FALSE_FB_NUM (-1037)
#define NC_ACTIVE_FB_ZERO_V0                (-1038)
#define NC_NEW_ACTIVE_FB_ZERO_VMAX          (-1039)  ///< zero max velocity
#define NC_CIRCLE_ANGLE_ZERO_ANGLE          (-1040)  ///< zero sweep angle
#define NC_CIRCLE_CENTER_ANGLE_180          (-1041)  ///< sweep angle equal 180
#define NC_CIRCLE_CENTER_ANGLE_360          (-1042)  ///< sweep angle equal 180
#define NC_CIRCLE_ANGLE_IN_3D               (-1043)  ///<
#define NC_OVERSHOOT_FLAG                   (-1044)  ///<

#define NC_CIRCLE_BORDER_2POINTS_COINCIDE   (-1045)
#define NC_CIRC_BORDER_3PNTS_ON_THE_LINE    (-1046)
#define NC_ZERO_REG_NUM_AXES                (-1047)
#define NC_REG_NUM_AXES_GT_16               (-1048)

#define NC_TWO_LINES_COINCIDE               (-1050)  ///< Transition curve cannot be inserted - two lines coincide
#define NC_TWO_LINES_COINCIDE_SAME_DIR      (-1051)  ///< Transition curve cannot be inserted - angle between two lines close to 0
#define NC_TWO_LINES_COINCIDE_OPPOSITE_DIR  (-1052)  ///< Transition curve cannot be inserted angle between two lines close to 180
#define NC_LC_DO_NOT_INTRSCT                (-1053)
#define NC_CL_DO_NOT_INTRSCT                (-1054)
#define NC_CC_DV_SWITCH_ARC_ERROR           (-1055)
#define NC_SPLINE_SEG_ZERO_LENGTH           (-1056)
#define NC_SPLINE_SEG_ZERO_TIME             (-1057)
#define NC_LC_ARC_GEOM_PARAMS_NEGTV_ROOT    (-1058)
#define NC_CL_ARC_GEOM_PARAMS_NEGTV_ROOT    (-1059)
#define NC_LC_ZERO_LINE_LENGTH              (-1060)
#define NC_CL_ZERO_LINE_LENGTH              (-1061)
#define NC_LC_ARC_END_POINT_OUT_CIRC        (-1062)
#define NC_LC_ARC_START_POINT_OUT_LINE      (-1063)
#define NC_CL_ARC_START_POINT_OUT_CIRC      (-1062)
#define NC_CL_ARC_END_POINT_OUT_LINE        (-1063)
#define NC_CL_DV_ARC_END_POINT_OUT_LINE     (-1064)
#define NC_CL_FR_ZERO_SWITCH_R              (-1065)
#define NC_CL_INIT_CIRC_ZERO_R              (-1066)
#define NC_CL_DV_CALC_ERROR                 (-1067)
#define NC_LC_FD_CALC_ERROR                 (-1068)
#define NC_LC_FD_R_LE_ZERO                  (-1069)  
#define NC_LC_DV_ARC_START_POINT_OUT_LINE   (-1070)
#define NC_LC_DV_CALC_ERROR                 (-1071)
#define NC_LC_FD_ARC_R_LE_ZERO              (-1072)
#define NC_CC_FR_CALC_ERROR                 (-1073)
#define NC_CL_FD_ARC_R_LE_ZERO              (-1074)
#define NC_SPLINE_ALLOCATION_ERROR          (-1075)
#define NC_SPLINE_DEALLOCATION_ERROR        (-1076)
#define NC_SPLINE_FILE_ERROR                (-1077)
#define NC_SPLINE_DATA_VALIDATION_ERROR     (-1078)
#define NC_SPLINE_UNALLOCATED_SEGMENT_ERROR (-1079)
#define NC_SPLINE_MEM_HANDLE_OUT_OF_RANGE   (-1080)
#define NC_SPLINE_NUM_PNTS_LESS_3           (-1081)
#define NC_POLYNOM_START_PNT_EQV_AUX        (-1082)
#define NC_POLYNOM_START_PNT_EQV_LAST       (-1083)
#define NC_POLYNOM_END_PNT_EQV_AUX          (-1084)
#define NC_POLYNOM_AUX_PNT_RATIO_ERROR      (-1085)


///////////////////////////////////////////////////////////////////////////////
// NC Profiler Warning IDs
///////////////////////////////////////////////////////////////////////////////
#define NC_TWO_LINES_SAME_DIR               (1001)
#define NC_CIRC_LINE_TANGENT_SAME_DIR       (1002)
#define NC_TWO_CIRCLES_TANGENT_SAME_DIR     (1003)
#define NC_BLEND_TRANS_CONTRADICTION        (1004)
#define NC_ZERO_LEN_FB                      (1005)  ///< Segment length calculated due to user params is zero
#define NC_ZERO_LEN_LINE_SEG                (1006)  ///< Segment length calculated due to user params is zero
#define NC_ZERO_LEN_CIRC_SEG                (1007)  ///< Segment length calculated due to user params is zero
#define NC_ZERO_LEN_ACS_SEG                 (1008)  ///< Segment length calculated due to user params is zero
#define NC_ZERO_LEN_SINGLE_AXIS_SEG         (1009)  ///< Segment length calculated due to user params is ze


#define IP_ADDR_SIZE    15

///////////////////////////////////////////////////////////////////////////////
/// FUNCTIONS DEFINITIONS
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_InitIf(void)
/// \brief This function initiates interface .
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_InitIf(void);

////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetLibVersion (void)
///
///
/// \brief      This function returns the MMC LIB Version.
/// \return return - library version
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API  ELMO_INT32 MMC_GetLibVersion () ;

////////////////////////////////////////////////////////////////////////////////
/// \fn void MMC_GetLastError (
///             IN MMC_CONNECT_HNDL hConn,
///             OUT char* chStr,
///             IN int iSize)
/// \brief  This function returns the last error that occurred in the designated connection.
/// \param hConn - [IN] Connection handle.
/// \param chStr - [OUT] Pointer to error string.
/// \param iSize - [IN] Size of error string.
/// \return return - void
///
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API  void MMC_GetLastError (IN MMC_CONNECT_HNDL hConn, OUT ELMO_PINT8 chStr, IN ELMO_INT32 iSize) ;

MMC_LIB_API ELMO_INT32 UpdateStatusAndError(ELMO_INT32 retval, ELMO_PUINT16 pusStatus, ELMO_PINT16 pusErrorID);
MMC_LIB_API ELMO_INT32 MMC_IsConnHndlValid(IN MMC_CONNECT_HNDL hConn);

/*!
 * \struct MMC_DESTIP_OUT
 */
typedef struct _mmc_destip_out {
    ELMO_INT8 dest_ip[IP_ADDR_SIZE+1]; /*!< ip address of dest machine.*/
}MMC_DESTIP_OUT;

/*!
 * \fn  int MMC_GetDestIP(MMC_CONNECT_HNDL hConn, MMC_DESTIP_OUT* o_params)
 * \brief   this function retrieves ip address of maestro.
 *
 *  given connection handler it stores the destination ip in output parameter.
 *  \param o_params output parameter stores destination ip address if completed successfully.
 *  \return 0 if completed successfully, otherwise error.
 */
MMC_LIB_API ELMO_INT32 MMC_GetDestIP(MMC_CONNECT_HNDL hConn, MMC_DESTIP_OUT* o_params);
/*
 * get active function block on axis queue.
 */
typedef struct _active_fb_in {
    ELMO_UINT8   _reserve[32];   /*!< for future use.*/
} MMC_ACTIVE_FB_IN;

typedef struct _active_fb_out {
    ELMO_UINT32     _uiHandler;     /*!< active handler.*/
    ELMO_UINT32     _data;          /*!< user footprint.*/
    ELMO_UINT16     usStatus;       /*!< api status.    */
    ELMO_INT16      usErrorID;      /*!< api error id.  */
    ELMO_UINT8      _reserve[32];   /*!< for future use.*/
} MMC_ACTIVE_FB_OUT;

MMC_LIB_API ELMO_INT32 MMC_GetActiveFB(
    IN MMC_CONNECT_HNDL hConn,
    IN MMC_AXIS_REF_HNDL hAxisRef,
    IN MMC_ACTIVE_FB_IN* i_params,
    OUT MMC_ACTIVE_FB_OUT* o_params);

#ifdef __cplusplus
    }
#endif

#endif /* MMC_DEFINITIONS_H_ */

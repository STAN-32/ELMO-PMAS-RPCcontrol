/*
 * CMMCLogger.h
 *
 *  Created on: 21Apr2015
 *      Author: Haim H.
 *      Update: 06May2015   Haim H.
 *      Update: 14May2015   Haim H. implement meetting action items.
 *      Update: 05Sep2017   Haim H. implement for Itegration3264OS
 *
 * Description: Class for Gmass Logging-Services, about this Gmas Logging-Services:
 *                  Implement above native Linux services (syslog / syslogd / rlogging) - a GMAS class wrap.
 *                  - Services for:
 *                          - Configure / Start/Stop Logging Server (daemon).
 *                                      Server Daemon:
 *                                                  Collect and direct logging messges (into files / remote Host / both).
 *                          - Send logging message from application to local server (Daemon).
 *                  Services only for IPC (not support RPC).
 *                  Only Cpp serices (not for C).
 *              Assume:
 *                  - Only Single Process/Thread uses at given time (especialy Configure methodes).
 *                  - Applications sync and control:
 *                          For Gmas Up-seassion (boot): no more then one Starting of logging-Server before Stop.
 *                          (else possible two or more servers may creats).
 *              Useing:
 *                  Before Send Logging-Message:
 *                      If any expectation the Server alreay reunning starts by Stopping it...
 *                      Calls to (one or more as needs) Server's Configure-Methode.
 *                      Call to Start-Logging-Server (daemon),
 *                          (if above sucess from now Send Logging-Message should registers [on file, on remote, both...]).
 *                  Send Logging-Messages from applications.
 *                  Stop-Logging (Stop Server).
 *
 *                  When / if Restart the Login-Server after it Stops, the Server run with last (previouse) configure values
 *                  (When MMCLogger Re-enter into scope Configure values sets to default).
 *                  Remmber:
 *                      !!! B4 calling Configure functions server should be stop           !!!
 *                      !!! Stopping the server do not set Configure parameters to default !!!
 *
 *                  'syslog packet size' is limited to 1024 bytes including all of carries information
 *                  (Facility,Severity,Hostname,Timestamp,AppMessage)
 *
 *              Refference: 
 *                  Linux syslog (Gmas services deliver by Gnu service call).
 *                  Linux syslogd (Gmas service [Server needs to startup; Starting up can be as shell command] deliver by Busybox [Gmas pack]).
 *                  Linux Rlogging (Server [remotes host, syslogd sends logging])
 *                  Busybox-1.10.0 (Gbl Package, come in source form, integrate as part of Gmas).
 */

#ifndef __MMCLogger_HPP__
#define __MMCLogger_HPP__

//#ifndef WIN32
#if (OS_PLATFORM == LINUXIPC32_PLATFORM)

	#include <syslog.h>
	#include <stdarg.h>
	
	#include "MMCPPGlobal.hpp"
	#include "MMC_definitions.h"
	
									/* Error / Reports code:        */
	 #define  LOG_MSG_ILLEGAL_PRM_MsgSIZE       -10
	 #define  LOG_MSG_ILLEGAL_PRM_SizeB4ROTATE  -20
	 #define  LOG_MSG_ILLEGAL_PRM_ROTATEFILES   -30
	 #define  LOG_MSG_ILLEGAL_PRM_REMOTEHOST    -40
	 #define  LOG_MSG_ILLEGAL_PRM_LOGMSG        -50
	
	 #define LOG_MSG_DEF_LOG_MSG_LEVEL      LOG_INFO
	 
					/* Default Base Logging File path and name      */
	 #define LOG_MSG_DEF_LOG_FILE_NAME      "LogMsg"
	 // Orginal syslogd write to /var/log/ -> permtion deny problem...
	 // #define LOG_MSG_VOLATILE_FILE_PATH     "/var/log/"
	 #define LOG_MSG_VOLATILE_FILE_PATH     "/tmp/"
	 #define LOG_MSG_FLASH_FILE_PATH        "/mnt/jffs/usr/"
					/* Extention (for EAS uses) adding to file Name */
	 #define LOG_MSG_EAS_FILE_EXTENTION     ".log"
	 
	 
	 #define LOG_MSG_SMALLER_LOGGING_OUTPUT "-S"
					/* Size of one logging file, before round to next file */
	 #define LOG_MSG_MIN_FILE_SIZEKB        2
	 #define LOG_MSG_MAX_FILE_SIZEKB        150
	 #define LOG_MSG_DEF_FILE_SIZEKB        100
		 
	 #define LOG_MSG_MIN_ROTATE_FILES       1
	 #define LOG_MSG_MAX_ROTATE_FILES       20
	 #define LOG_MSG_DEF_ROTATE_FILES       5
	 
	 #define LOG_MSG_DEF_SRV_LOCAL_LEVEL    8
	 #define LOG_MSG_DEF_PORT               514
	
	 #define SYSLOGD_ACTIVATION_CMD_LEN     200
	 
	 #define LOG_MSG_FILE_AND_PATH_STORAGE_NAME_LEN 100
					/* Array size holding remotes host Ip        */
	 #define LOG_MSG_REMOTE_IP_STORAGE_LEN  20
					/* Address context info. adding to user message Normal or Small                 */
	 typedef enum {enLOG_MSG_SIZE_NORM = 3, enLOG_MSG_SIZE_SMALL} enLOG_MSG_SIZE_ENUM;
					/* Logging file on Volatile location => File life along boot GMAS session,      */
					/* Logging file on Flash    location => File life along Not explicity delete    */
	 typedef enum {enLOG_MSG_VOLATILE_FILE_PATH = 5,  enLOG_MSG_FLASH_FILE_PATH} enLOG_MSG_LOGGING_FILE_LOCATION_PATH;
	 
	class MMCLogger
	{
	public:
	 MMCLogger()                            : _uiConnHndl(0)          { LogMsgConfigureToDefault(); }
	 MMCLogger(MMC_CONNECT_HNDL uiConnHndl) : _uiConnHndl(uiConnHndl) { LogMsgConfigureToDefault(); }
	
	 ~MMCLogger() {}
	
	 void             SetConnectionHndl(MMC_CONNECT_HNDL uiConnHndl){_uiConnHndl = uiConnHndl;}
	 MMC_CONNECT_HNDL GetConnectionHndl()                           {return _uiConnHndl;      }
	
	
	
					/* Server Configure function:                                   */
					/* Set Server Configure parameters to defaults.                 */
					/* !!! NOT EFECT RUNNING SERVER, EFECT ONLY ON NEXT SERVER START*/
	 void   	LogMsgConfigureToDefault(void);
	
					/* Server Configure function:                                   */
					/* Define Logging file path & name                              */
					/* Add extention to Base file name (or user deliver name)       */
					/* (The EAS search/find logging files according this extention).*/
					/* If not specifay name or its NULL => use the defaults name.   */
					/* Return 0 when everything ok and as expecting.                */
					/* If not called using the defaults.                            */
	 ELMO_INT32	LogMsgConfigureFilePathAndName(ELMO_PINT8 pcLogMsgFileName = LOG_MSG_DEF_LOG_FILE_NAME,
										   enLOG_MSG_LOGGING_FILE_LOCATION_PATH enLogMsgLoggingFileLocation = enLOG_MSG_FLASH_FILE_PATH);
	
					/* Server Configure function:                                   */
					/* Remove (Delete) specific (or defaults) logging files.        */
					/* Add extention to Base file name (or user deliver name)       */
					/* (The EAS search/find logging files according this extention).*/
					/* If not specifay name or its NULL => use the defaults name.   */
					/* Return 0 when everything ok and as expecting.                */
					/* If not called using the defaults.                            */
	 ELMO_INT32	LogMsgConfigureRmoveLogFiles(ELMO_PINT8 pcLogMsgFileName = LOG_MSG_DEF_LOG_FILE_NAME,                              
										 enLOG_MSG_LOGGING_FILE_LOCATION_PATH enLogMsgLoggingFileLocation = enLOG_MSG_FLASH_FILE_PATH);
	
					/* Server Configure function:                                   */
					/* Normal / Smaller logging context - Set logging message size  */
					/* Return 0 when everything ok and as expecting.                */
					/* If not called using the defaults.                            */
	 ELMO_INT32	LogMsgConfigureLogMsgSize(enLOG_MSG_SIZE_ENUM enLogMsgSize = enLOG_MSG_SIZE_SMALL);
	
					/* Server Configure function:                                   */
					/* Define (set) the Max File size before rotate:                */
					/* Range: LOG_MSG_MIN_FILE_SIZEKB to LOG_MSG_MAX_FILE_SIZEKB    */
					/* Default: LOG_MSG_DEF_FILE_SIZEKB                             */
					/* Return 0 when everything ok and as expecting.                */
					/* If not called using the defaults.                            */
	 ELMO_INT32	LogMsgConfigureMaxFileSizeB4Rotate(int iFileSizeB4RotateKB = LOG_MSG_DEF_FILE_SIZEKB);
	
					/* Server Configure function:                                   */
					/* Set Number of rotated logs file to keep:                     */
					/* Range: LOG_MSG_MIN_ROTATE_FILES to LOG_MSG_MAX_ROTATE_FILES  */
					/* E.g1:  Files for iNumRotateFiles=1 LogMsg, LogMsg.0          */
					/* E.g2:  Files for iNumRotateFiles=2 LogMsg, LogMsg.0 LogMsg.1 */
					/* E.g3:  LogMsgNumRotateFiles(3);                              */
					/*      Cause cyclic write to files:                            */
					/*          LogMsg, LogMsg.0, LogMsg.1, LogMsg.2                */
					/* Return 0 when everything ok and as expecting.                */
					/* If not called using the defaults.                            */
	 ELMO_INT32	LogMsgConfigureNumRotateFiles(ELMO_INT32 iNumRotateFiles = LOG_MSG_DEF_ROTATE_FILES);
	
					/* Server Configure function:                                   */
					/* Set Logging to remote (logging also localy when|if explicit  */
					/* request), define remote IP and Port:                         */
					/* If (pcRemoteHostIp == NULL) Configure for NO LOG TO REMOTE   */
					/* !!! Any Configure take affect only on next servers start !!! */
					/* Return 0 when everything ok and as expecting.                */
	 ELMO_INT32	LogMsgConfigureToRemoteHost(ELMO_PINT8   pcRemoteHostIp,
							ELMO_BOOL    bReportAlsoLocal = ELMO_FALSE,
							ELMO_INT32   iRemoteHostPort = LOG_MSG_DEF_PORT);
	
					/* Configure and Start server daemon, all parameters should exist in call   */
					/* If MsgFileName is NULL => use the defaults name.                         */
					/* If pcRemoteHostIp is NULL => no log to remote.                           */
					/* The behavior is like all of related config function are call with the    */
					/* relevant parameters and then calling to start server.                    */
	 ELMO_INT32	LogMsgConfigureAndStartLoggerServer(ELMO_PINT8                          pcLogMsgFileName,
												enLOG_MSG_LOGGING_FILE_LOCATION_PATH    enLogMsgLoggingFileLocation,
												enLOG_MSG_SIZE_ENUM                     enLogMsgSize,
												ELMO_INT32                              iFileSizeB4RotateKB,
												ELMO_INT32                              iNumRotateFiles,
												ELMO_PINT8                              pcRemoteHostIp,
												ELMO_BOOL                               bReportAlsoLocal,
												ELMO_INT32                              iRemoteHostPort);
	
					/* Activate Logger Server with configured values (defaults      */
					/* or from Configure calls).                                    */
					/* This call should start the message collector server (daemon) */
					/* which stays running also after the application exit.         */
					/* Call to configure methods (above) after Start has no         */
					/* effect on the running server!!!                              */
					/* Return 0 when everything ok and as expecting.                */
	 ELMO_INT32	LogMsgStartLoggerServer();
	
					/* Stop logging server:                                         */
					/* This call should stop collecting logging message by server   */
					/* (stop the Server daemon) which stays running also after the  */
					/* application logout/exit.                                     */
					/* Return 0 when everything ok and as expecting.                */
	 ELMO_INT32	LogMsgStopLoggerServer();
	
					/* Send logging Message to server:                              */
					/* if the server already running (started) the message should   */
					/* rgister in logging file / send to remote or both acording to */
					/* server Configure.                                            */
					/* Message builds according to format as in printf(forma,...)   */
					/* Return 0 when everything ok and as expecting.                */
					/*          E.g:                                                */
					/*          int     iSeq=0;                                     */
					/*          …                                                   */
					/*          iSeq++;                                             */
					/*          LogMsg(LOG_CRIT, "Good Message Number %d", iSeq);   */
					/* Call with !!! DEFAULT LEVEL !!!                              */
	 ELMO_INT32	LogMsg(               const ELMO_PINT8 format, ...);
					/* ABOVE FUNCTION FOR call with DEFAULT LEVEL !!!               */
					/* THIS FUCTION FOR USER SPECIFIC LEVEL.                        */
	 /*
	  * Legal values for the SendLevel:
	  *      LOG_EMERG LOG_ALERT LOG_CRIT LOG_ERR LOG_WARNING LOG_NOTICE LOG_INFO LOG_DEBUG
	  */
	 ELMO_INT32	LogMsg(ELMO_INT32 SendLevel, const ELMO_PINT8 format, ...);
	
	private:
					/* Is pointing string is legal format for Ip Add? */
					/* true=>Legal format; false=>Illegal format.     */
	 ELMO_BOOL	LogMsgIsValidIp(ELMO_PINT8 IpAdd);
					/* In case there more then 1 file in round (<fileName>.1 or more)       */
					/* on first round the orginal code try to rename existing files and     */
					/* faile... (at this moment there is no <fileName>.0 for rename to <>.1)*/
					/* for correct this problem this function creates the empty files...    */
	 ELMO_INT32	LogMsgRoundFileCreation();
	
		   /* Server Configure values */
					/* Keep hear file and path name (stay in scope along the class is) */
	 ELMO_INT8  _pcLogMsgFileAndPathStorageName[LOG_MSG_FILE_AND_PATH_STORAGE_NAME_LEN];
					/* Output message size {normal / Smaller [-S]}) */
	 enLOG_MSG_SIZE_ENUM   _enLogMsgNormalOrSmallerMsgSize;
					/* Log Message File Location (path) Volatile | Flash */
	 enLOG_MSG_LOGGING_FILE_LOCATION_PATH _enLogMsgVolatileOrFlash;
					/* Max File size Before Rotate */
	 ELMO_INT32	_iLogMsgMaxFileSizeB4RotateKb;
					/* Number of rotated logs file to keep */
	 ELMO_INT32	_iLogMsgNumRotateFilesKeep;
					/* !! LOCAL !! Mask for file collecting level 1-8. Collect if the send bit is NOT set.  */
					/* E.g. for set the level=4; 4 & 5 not collects; 0,1,2,3,6,7                            */
					/* If send to remote Configure, send message not effect from this setting.              */
	 ELMO_INT32	_iLogMsgServerLocalLevel;
					/* storage for remote Host Ip  */
	 ELMO_INT8  _pcLogMsgRemoteHostIp[LOG_MSG_REMOTE_IP_STORAGE_LEN];
					/* whether logging local when send logging to remote */
	 ELMO_BOOL	_bReportAlsoLocal;
					/* Remote port */
	 ELMO_INT32	_iRemoteHostPort;
	
	 MMC_CONNECT_HNDL _uiConnHndl;
	};
	
#endif  /* #ifndef WIN32                        */
#endif  /* #ifndef __MMCLogger_h__      */


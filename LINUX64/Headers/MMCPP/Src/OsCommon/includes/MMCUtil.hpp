/*
 * MMCUtil.h
 *
 *  Created on: 21/07/2013
 *      Author: Haim Hillel
 *  Update on: 06Sep2017
 */

#ifndef MMCUtil_H_
#define MMCUtil_H_

#include "MMC_definitions.h"
#include "MMCPPGlobal.hpp"


class DLLMMCPP_API CMMCUtil
{
public:
	 CMMCUtil();

	~CMMCUtil();

					/* Function steps: ensure server running, transfer file, shutdown server (conditional)	*/
						/* Download ("ImportFile") direction is "TO Gmas"	*/
						/* if FileName including path it ignore (removes)	*/
						/* DesHostFilePath keep on host (not send to client)*/
						/* if null keep previous path or use the default.	*/
ELMO_INT32	UtilDownloadFile(IN MMC_CONNECT_HNDL ConnHndl, ELMO_PINT8 FileName, ELMO_PINT8 DesHostFilePath, ELMO_PINT8 RpcHostIp, MMC_DOWNLOAD_TYPE_ENUM FileDownloadType)	throw (CMMCException);
						/* Upload ("ExportFile") direction is "FROM Gmas"	*/
ELMO_INT32	UtilUploadFile  (IN MMC_CONNECT_HNDL ConnHndl, ELMO_PINT8 FileName, ELMO_PINT8 DesHostFilePath, ELMO_PINT8 RpcHostIp, MMC_DOWNLOAD_TYPE_ENUM FileDownloadType)	throw (CMMCException);
						/* If the server not running, run it and flag it	*/
						/* for stay running.								*/
						/* DesHostFilePath keep on host (not send to client)*/
						/* if null keep previous path or use the default.	*/
ELMO_INT32	UtilStartTftpServer(ELMO_PINT8 DesHostFilePath);
						/* If Tftp server running stop it.					*/
void	UtilStopTftpServer(void);
						/* Set the TFTP low level services to new speak	(report level), return the	*/
						/* running speak level.														*/
						/* Range 0 (=HSTFTPAPP_SPEAK_LVL_ALL) to 5 (=HSTFTPAPP_SPEAK_LVL_NONE)		*/
						/* If value is out of range (Eg -1) set it same as DEF_SPEAK_LVL			*/
						/* (concider its the "default").											*/
						/* The newSpeakLvl effect Only during calling actions between 				*/
						/* UtilStartTftpServer to UtilStopTftpServer.								*/
						/* While calling UtilDownloadFile or UtilUploadFile which rerunning server,	*/
						/* (no preciding call to UtilStartTftpServer) the server rerunning with 	*/
						/* default speak level...													*/
ELMO_INT32	UtilSetTftpSpeakLvl(ELMO_INT32 newSpeakLvl);



private:
	ELMO_BOOL	bReqServerStayRunning;

						/* Activate TFTP Server.							*/
						/* For detaile about activation argument look in	*/
						/* files: MMCUtil.cpp under'UtilActivateTftpServer' */
						/*        (and in) HsTftpApp.cpp					*/
						/*			under HSTFTPAPP_MAIN_EP_NAME			*/
						/* Param name DesHostFilePath is the location of 	*/
						/* file on Host, this setting replace location come	*/
						/* from client (so, in case the client send file    */
						/* path (location) client path is ignore).			*/
						/* When this Param is null, keepping previous sets  */
						/* value (path), if not set, using the default.		*/
	ELMO_INT32	UtilActivateTftpServer(ELMO_PINT8 DesHostFilePath);
};

#endif /* #ifndef MMCUtil_H_ */


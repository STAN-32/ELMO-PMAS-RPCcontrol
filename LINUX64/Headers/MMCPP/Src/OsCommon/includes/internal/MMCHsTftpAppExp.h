/*
============================================================================
 Name 	:	HsTftpAppExp.h
 Author :	Haim Hillel
 Version:	22Jul2013
 Description :
			Elements exported from Hillstone Tftp package porting in Elmo.
==============================================================================
*/

//	   	Exported error code, define in global definitions of Gmas error code (MMC_definitions.h)
//
//#define MMC_OK                            0     ///< No error. No warning. All OK.
//#define MMC_LIB_UTILTFTP_PARSE_OPT        (-30) /* ??? Util: Tftp activ. arg. parsing err		*/
//#define MMC_LIB_UTILTFTP_CREATE_LOCK      (-31) /* ??? Util: Tftp Cannot create sync lock	    */
//#define MMC_LIB_UTILTFTP_INIT             (-32) /* ??? Util: Tftp initialisation failure      */
//#define MMC_LIB_UTILTFTP_START_SERVER     (-32) /* ??? Util: Tftp Server failed to start	    */
//#define MMC_LIB_UTILTFTP_INVLD_HOST_NAME  (-32) /* ??? Util: Tftp Invalid hostname specified  */
//#define MMC_LIB_UTILTFTP_INVLD_FILE_NAME  (-32) /* ??? Util: Tftp Invalid filename specified  */
//#define MMC_LIB_UTILTFTP_CLIENT_SEND_FILE (-32) /* ??? Util: Tftp Send file failed		    */
//#define MMC_LIB_UTILTFTP_CLIENT_GET_FILE  (-32) /* ??? Util: Tftp Get file failed				*/
//
								  	/* Main Util funtion, start Tftp (Server or	cliant,	*/
								  	/* Gmas currently use only server).					*/
	ELMO_INT32 HsTftpApp_main_ep(ELMO_INT32 argc, ELMO_PINT8 argv[]);
									/* Stop and clear Tftp Util session (shut down the server)	*/
	void deinit(void);
									/* If not null update host path	*/
	void updHostPath(ELMO_PINT8 DesHostFilePath);


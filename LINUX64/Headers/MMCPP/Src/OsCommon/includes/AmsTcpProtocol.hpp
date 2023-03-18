/*
============================================================================
 Name : AmsTcpProtocol.h
 Author : Haim H.
 Version :      14Jul2015
				24Feb2020
				22Nov2020 HH porting for IntegrationOS3264
 Description :  Implement ADS / AMS Beckhoof protocol above Tcp.
                GMAS implementation for be Server responce to ADS client.


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Meanwhile support only size of AMS_MAX_SIZE_DEF_TCP
	meaning: whenever appear 'size' as parameter set AMS_MAX_SIZE_DEF_TCP
	this because of fix static assinge of (see size of array - look on code):
        // unsigned char   _gucTcpSndBuf[_iMsgMaxSize];
        unsigned char   _gucTcpSndBuf[AMS_MAX_SIZE_DEF_TCP];
	The code (almost) ready for dynmic (on initialize parameter) frames
	size...
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
============================================================================
*/

#ifndef __AmsTcpProtocol_h__
#define __AmsTcpProtocol_h__

// #ifndef WIN32
#if   (OS_PLATFORM == LINUXIPC32_PLATFORM)


					/* Below includs files should appear in both AmsTcp* and AmsUdp	*/
					/* some module including both of them headers...				*/
					/* eliminate compilation 'multiple definitions errors 			*/
					/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
					/* !!! The symbol: '_ShareIncForAMS_UDP_and_TCP' should		!!! */
					/* !!! appearing same (functional and lexcical) in:			!!! */
					/* !!!	 AmcTcpProtocol.h & AmsUdpProtocol.h				!!! */
					/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
#ifndef		_ShareIncForAMS_UDP_and_TCP
	#define	_ShareIncForAMS_UDP_and_TCP
	
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <sys/types.h>
	#include <pthread.h>
	#include <sys/ioctl.h>
	#include <errno.h>
	#include <netinet/tcp.h>

	#include "MMCPPGlobal.hpp"
	#include "MMCSocket.hpp"
#endif
                    
                    
#include <AmsTcpUdpProtocolDef.hpp>

                    /* Define dump line length. Number of chars in one dump line (line length is more then  */
                    /* twice as: Space from begin of line, Hex, Space (betweens Hex to ascci) Asscii...     */
#define ADS_AMS_BYTES_IN_DUMP_LINE      16
    


                            /* Implement ADS/AMS READ,WRITE protocol    */
    class DLLMMCPP_API CMMCAmsTcpProtocol
    {
    public:
        CMMCAmsTcpProtocol() : _iServerSock(-1), _bClbkThreadAlive(ELMO_FALSE)
        {
            _giDbgLclFlag = 0;
            _giDbgCommuFlag = 0;

								/* Mark (when true) IN IEC course Not send automatic data to remote client).*/
								/* client after return from callback funtions.								*/
			_gbIecCourse = ELMO_FALSE;

            /* From MMCTCP ???? */

            #ifdef WIN32
                static ELMO_INT32 err = WSAStartup(MAKEWORD(2,0),&m_wsaData); //one-time initialization for a proccess.
                if(err != MMC_OK) {
                    cout<<"Socket Initialization Error. Program aborted\n";
                    return;
                }
            #endif

            memset(&_saddConnect, 0, sizeof (_saddConnect));
            _iSock = -1;
            /* From MMCTCP ???? */
								/* Default size - Initialization */
			_iMsgMaxSize = AMS_MAX_SIZE_DEF_TCP;
        };

        ~ CMMCAmsTcpProtocol()
        {
            /* From MMCTCP ???? */
            _bClbkThreadAlive = ELMO_FALSE; //quit call-back mode thread.
            if (_iServerSock != -1) //if function as server
            {
                this->CloseSock_TCP(_iServerSock); //close listener file descriptor.
            }
            if (_iSock != -1)
            {
                this->CloseSock_TCP(_iSock); //close client file descriptor.
            }
            /* From MMCCPP ???? */
        };

							/* Use this instead of AmsProtocolInit_TCP(...) while in IEC*/
                            /* Application Initialize (connection to ADS/AMS) supplay:  */
                            /*  port number,                                            */
                            /*  ClientReqRead - call back function, response to Client  */
                            /*          requst Read Data from server.                   */
                            /*  ClientReqWrite - Call back function, response to Client */
                            /*          requst Write Data to server.                    */
							/*  iMsgMaxSize - size (Max len) allocated for data buffer	*/
        ELMO_INT32     AmsProtocolInitIEC_TCP(ELMO_UINT16 	usPort,
                                    AMS_CLBK_REQ_READ_TCP  	fnClbkRespClientReqRead_TCP,
                                    AMS_CLBK_REQ_WRITE_TCP 	fnClbkClientReqWrite_TCP,
									ELMO_INT32			   	iMsgMaxSize = AMS_MAX_SIZE_DEF_TCP);

							/* Use this instead of AmsProtocolInitIEC_TCP(...) while in */
							/* not working against IEC.									*/
                            /* Application Initialize (connection to ADS/AMS) supplay:  */
                            /*  port number,                                            */
                            /*  ClientReqRead - call back function, response to Client  */
                            /*          requst Read Data from server.                   */
                            /*  ClientReqWrite - Call back function, response to Client */
                            /*          requst Write Data to server.                    */
							/*  iMsgMaxSize - size (Max len) allocated for data buffer	*/
        ELMO_INT32		AmsProtocolInit_TCP(ELMO_UINT16  	usPort,
                                    AMS_CLBK_REQ_READ_TCP  	fnClbkRespClientReqRead_TCP,
                                    AMS_CLBK_REQ_WRITE_TCP 	fnClbkClientReqWrite_TCP,
									ELMO_INT32			   	iMsgMaxSize = AMS_MAX_SIZE_DEF_TCP);

							/* Send response to client 									*/
							/* While use for IEC calling this func initialize from user */
							/* meaning, the call are from 'IEC - CodeSys'				*/
		ELMO_INT32		AmsSendClientRes_TCP();

                            /* Dbg Service, when iDbgCommuFlag != 0 print communication */
        void    AmsSetDbg        (ELMO_INT32 iDbgLclFlag, ELMO_INT32 iDbgCommuFlag);
                           /* Dbg service, print string in Hex & Ascii format           */
        void    DumpStreamBuffer    (ELMO_UINT8 pucStrStream[], ELMO_UINT32 uiNumCharForPrint);


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
                    /* Original takes From MMCTCP !!!! */
                    /* Original takes From MMCTCP !!!! */
#include    "AmsTcpProtocolTcp.hpp"
                    /* Original takes From MMCTCP !!!! */
                    /* Original takes From MMCTCP !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

    private:
        ELMO_INT32     	DecodeAmsHeader     (ELMO_UINT8 ucStrStream[]);
        ELMO_INT32     	DecodeGrpOffsetLen  (ELMO_UINT8 ucStrStream[]);
        ELMO_INT32		ResponseClientReq	(ELMO_UINT8 ucRcvBuf[], ELMO_UINT8 ucSndBuf[]);
                                            /* Call from thread while soket receive data */
        ELMO_INT32     	SocketfnClbk        (ELMO_INT16 sSockEvent, ELMO_UINT8 pucReadBuf[], ELMO_INT32 iReadBufSize, ...);
		ELMO_INT32		BuildTcpSendBuf		(void);

                                            /* Buffers for TCP Send communication to client */
        // unsigned char   _gucTcpSndBuf[_iMsgMaxSize];
        ELMO_UINT8		_gucTcpSndBuf[AMS_MAX_SIZE_DEF_TCP];
											/* pointer to buffer filling by recive from Remote client (pc...)  */
		ELMO_PUINT8 	_gucBuffer;
											/*	_gusSndRespSize = Whole size of response, for put into Send buffer	*/
											/*	(response size). Size of buffer, num of char for send				*/
        ELMO_UINT16		_gusSndRespSize;

                                            /* Commad Id, type appear both (exchange between) 'unsigned short'  */
                                            /* and 'eAMS_CMDId' be carfull because enumerated type is 'int'.    */
        ELMO_UINT16  	_gusRcvCommandId;
                        /* From Client point of view                    */
                        /* Rcv => GMAS got the command (read/write...)  */
		ELMO_INT32		_guiRcvHdrTcpLen;	/* Len appear in TCP header */
        ELMO_UINT16  	_gusRcvPortTarget;  /* Target port  */
        ELMO_UINT16  	_gusRcvPortSource;  /* Source port  */ 
        ELMO_UINT16		_gusRcvStateFlags;  /* State Flags  */
        ELMO_UINT32	    _guiRcvHdrLen;      /* Whole range of 'DATA AREA', E.g.: Including: IndexGroup, InexOffset, Length and "Pure Data" */
        ELMO_UINT32	    _guiRcvErrorCode;   /* Error Code   */
        ELMO_UINT32	    _guiRcvInvokeId;    /* Invoke Id.   */
        
                        /* From Last relevant Rcv Command */
        ELMO_UINT32	    _guiIndexGroup;     /* Index Group of the data which should be written.     */
        ELMO_UINT32	    _guiIndexOffset;    /* Index Offset, in which the data should be written.   */
        
                                            /* Length of the data (in bytes) which are written.     */ 
                                            /*   "pure data within data area" Not Including         */
                                            /*   IndexGroup, InexOffset, Length.... E.g. when pure  */
                                            /*   data is 'a' this field be 1.                       */
        ELMO_UINT32	    _guiPureDataLen;
											/* Result put on the buffer send to client as response	*/
											/* to requsted operation (read or write command).		*/
		ELMO_UINT32		_guiResultToClient;


        ELMO_INT32      _giSizeRcv;
        ELMO_INT32      _giSizeForSnd;
											/* Storage for process communication Header				*/
		AMSHDR_TCP     	_gtAmsHdrFromClient;
		AMSHDR_TCP     	_gtAmsHdrToClient, *_gptAmsHdrToClient;

                                            /* Pointer to user function call in responce to Client  */
                                            /* requst Read (return roud data from server to client).*/
        AMS_CLBK_REQ_READ_TCP   _fnClbkRespClientReqRead_TCP;
                                            /* Pointer to user function call while Client requst    */
                                            /* Write (return client data to server).                */
        AMS_CLBK_REQ_WRITE_TCP  _fnClbkClientReqWrite_TCP;
											/* Flag, when==true mean set class methode behave for	*/
											/* IEC. Meaning the user should initiate send remote	*/
											/* client respose. Other it enter after return from the	*/
											/* callback functions.									*/
		ELMO_BOOL				_gbIecCourse;
                                            /* Trace & debug flags                                  */
        ELMO_INT32              _giDbgLclFlag;
        ELMO_INT32              _giDbgCommuFlag;
    };



#endif  /* #if   (OS_PLATFORM == LINUXIPC32_PLATFORM) */

#endif  /* #define __AmsTcpProtocol_h__ */


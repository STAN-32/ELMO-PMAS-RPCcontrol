/*
============================================================================
 Name : AmsTcpUdpProtocolDef.h
 Author : Haim H.
 Version : 22Jun2020
				22Nov2020 HH porting for IntegrationOS3264
 Description :  The definitions of values for supporting ADS / AMS Beckhoof protocol for TCP & UDP.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Meanwhile support only size of AMS_MAX_SIZE_DEF_UDP
	meaning: whenever appear 'size' as parameter set AMS_MAX_SIZE_DEF_UDP
	this because of fix static assinge of (see size of array - look on code):
        // unsigned char   _gucUdpSndBuf[_iMsgMaxSize];
        unsigned char   _gucUdpSndBuf[AMS_MAX_SIZE_DEF_UDP];
	The code (almost) ready for dynmic (on initialize parameter) frames
	size...
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
============================================================================
*/

#ifndef	__AmsTcpUdpProtocolDef_h__
#define	__AmsTcpUdpProtocolDef_h__


	/***********/
	/* For TCP */
	/***********/
	#define AMS_MAX_SIZE_DEF_TCP 			1500 //In accordance with MTU definitoins
	
                    /* ADS/AMS Structure OFFSETS (interesting item offset within AMS stream) */
					
															/* AMS/TCP Header	*/
	#define AMSHDR_RSRV_FOR_TCP			    0
    #define AMSHDR_LEN_FOR_TCP              2
    #define AMSHDR_FOR_TCP                  6
															/* AMS Header		*/
    #define AMSHDR_NETID_TRG_TCP            (AMSHDR_FOR_TCP+ 0)
    #define AMSHDR_PORT_TRG_TCP             (AMSHDR_FOR_TCP+ 6)
    #define AMSHDR_NETID_SRC_TCP            (AMSHDR_FOR_TCP+ 8)
    #define AMSHDR_PORT_SRC_TCP             (AMSHDR_FOR_TCP+14)
    #define AMSHDR_CMD_TCP                  (AMSHDR_FOR_TCP+16)
    #define AMSHDR_STATE_TCP                (AMSHDR_FOR_TCP+18)
    #define AMSHDR_LEN_TCP                  (AMSHDR_FOR_TCP+20)
    #define AMSHDR_ERR_CODE_TCP             (AMSHDR_FOR_TCP+24)
    #define AMSHDR_INVOKE_ID_TCP            (AMSHDR_FOR_TCP+28)
	
															/* Offset for Start of data, len write in offset AMSHDR_LEN	*/
    #define AMSDATA_STR_TCP                 (AMSHDR_FOR_TCP+32)
    
															/* Offset on Data area for case of ADS Read	*/
    #define AMSDATA_IDX_GRP_TCP             (AMSDATA_STR_TCP+0)
    #define AMSDATA_IDX_OFST_TCP            (AMSDATA_STR_TCP+4)
    #define AMSDATA_REQ_LEN_TCP             (AMSDATA_STR_TCP+8)
    
															/* Offset on Data area for case of ADS Response	*/
    #define AMSDATA_RESP_RESULT_TCP         (AMSDATA_STR_TCP+0)
    #define AMSDATA_RESP_READ_LEN_TCP       (AMSDATA_STR_TCP+4)
    #define AMSDATA_RESP_READ_PURE_DATA_TCP (AMSDATA_STR_TCP+8)
    
    #define AMSDATA_WRITE_STR_TCP           (AMSDATA_STR_TCP+12)
	
	   
                                   /* Set current struct pack, push pack level on compiler stack. Prgma set for pack on alime 0 (=pack)     */
                                   /* #pragma pack(push[,n]) pushes the current alignment setting on an internal stack and then optionally  */
                                   /* sets the new alignment.                                                                               */
                                   /* Also can handle by use of __attribute__ see example:                                                  */
                                   /*       struct  __attribute__((__packed__)) my_struct                                                   */
                                   /*           {                                                                                           */
                                   /*               ...                                                                                     */
                                   /*           };                                                                                          */
                                   /*       int *e __attribute__((aligned(1))) = &a.i;                                                      */
#pragma pack(push, 0)
	typedef struct AMSHDR_TCP_TAG
		{
					/* !!! Exist Only In TCP !!!	*/
														/* These bytes must be set to 0									*/
			ELMO_UINT16	usAMSTcpReserved;
														/* Bytes of packet. Contains AMS-Header and enclosed ADS data.	*/
														/* lENGTH NOT INCUDING THE 6 BYTES OF TCP (2 RESERVED, 4 LENGTH)*/
			ELMO_UINT32		uiAMSTcpLength;
					/* !!! Exist Only In TCP !!!	*/
			
			ELMO_UINT8    cpAMSNetIdTarget[6];    		/* AMSNetId of the station, for which the packet is intended.   */
			ELMO_UINT16   usAMSPortTarget;        		/* AMSPort of the station, for which the packet is intended.    */
			ELMO_UINT8    cpAMSNetIdSource[6];    		/* AMSNetId of the station, from which the packet was sent.     */
			ELMO_UINT16   usAMSPortSource;        		/* AMSPort of the station, from which the packet was sent.      */
       
			ELMO_UINT16   usCommandId;                
			ELMO_UINT16   usStateFlags;
			ELMO_UINT32   uiHdrLen;            			/* Size of the data range. The unit is byte.                    */
			ELMO_UINT32   uiErrorCode;            		/* AMS error number                                             */
			ELMO_UINT32   uiInvokeId;             		/* Free usable 32 bit array. Usually this array serves to send  */
														/* an Id. This Id makes is possible to assign a received        */
														/* response to a request, which was sent before                 */
    } AMSHDR_TCP;
                                   /* Resume the working structure pack (from top of stack)                                                 */
                                   /* #pragma pack(pop) restores the alignment setting to the one saved at the top of the internal stack    */
                                   /* (and removes that stack entry). Note that #pragma pack([n]) does not influence this internal stack;   */
                                   /* thus it is possible to have #pragma pack(push) followed by multiple #pragma pack(n) instances and     */
                                   /* finalized by a single #pragma pack(pop).                                                              */
#pragma pack(pop)

                    /* Type of function the class calls for get user data as*/
                    /* response to Client requst Read data from Server      */
    typedef ELMO_INT32 (* AMS_CLBK_REQ_READ_TCP)(ELMO_UINT8  ucDataClientReqRead[],
                                         ELMO_UINT32    uiDataClientReqReadSize,
                                         ELMO_UINT32    uiIndexGroup,
                                         ELMO_UINT32    uiIndexOffset,
                                         ELMO_PUINT32   puiResult,
                                         AMSHDR_TCP*    ptAmsHdrFromClient,     /* Copy of the org.         */
                                         AMSHDR_TCP**   pptAmsHdrToClient);     /* If Null take from Rcv    */

                    /* Type of function the class calls for serve client    */
                    /* requsted Write data to server (client sends data)    */
    typedef ELMO_INT32 (* AMS_CLBK_REQ_WRITE_TCP)(ELMO_UINT8 ucDataClientReqWrite[],
                                         ELMO_UINT32    uiDataClientReqWriteSize,
                                         ELMO_UINT32    uiIndexGroup,
                                         ELMO_UINT32    uiIndexOffset,
                                         ELMO_PUINT32   puiResult,
                                         AMSHDR_TCP*    ptAmsHdrFromClient,     /* Copy of the org.         */
                                         AMSHDR_TCP**   pptAmsHdrToClient);     /* If Null take from Rcv    */ 


	/***********/
	/* For UDP */
	/***********/

	#define AMS_MAX_SIZE_DEF_UDP  			512

                    /* ADS/AMS Structure OFFSETS (interesting item offset within AMS stream) */
    #define AMSHDR_NETID_TRG_UDP             0
    #define AMSHDR_PORT_TRG_UDP              6
    #define AMSHDR_NETID_SRC_UDP             8
    #define AMSHDR_PORT_SRC_UDP             14
    #define AMSHDR_CMD_UDP                  16
    #define AMSHDR_STATE_UDP                18
    #define AMSHDR_LEN_UDP                  20
    #define AMSHDR_ERR_CODE_UDP             24
    #define AMSHDR_INVOKE_ID_UDP            28
    
    #define AMSDATA_STR_UDP                 32
    #define AMSDATA_IDX_GRP_UDP             (AMSDATA_STR_UDP+0)
    #define AMSDATA_IDX_OFST_UDP            (AMSDATA_STR_UDP+4)
    #define AMSDATA_REQ_LEN_UDP             (AMSDATA_STR_UDP+8)
    
    #define AMSDATA_RESP_READ_LEN_UDP       (AMSDATA_STR_UDP+4)
    #define AMSDATA_RESP_READ_PURE_DATA_UDP (AMSDATA_STR_UDP+8)
    
    #define AMSDATA_WRITE_STR_UDP           (AMSDATA_STR_UDP+12)


                    /* Start of data received by 'udp.Receive' */
    typedef struct AMSHDR_UDP_TAG
       {
           ELMO_UINT8    cpAMSNetIdTarget[6];    		/* AMSNetId of the station, for which the packet is intended.   */
           ELMO_UINT16   usAMSPortTarget;        		/* AMSPort of the station, for which the packet is intended.    */
           ELMO_UINT8    cpAMSNetIdSource[6];    		/* AMSNetId of the station, from which the packet was sent.     */
           ELMO_UINT16   usAMSPortSource;        		/* AMSPort of the station, from which the packet was sent.      */
       
           ELMO_UINT16   usCommandId;                
           ELMO_UINT16   usStateFlags;
           ELMO_UINT32   uiHdrLen;						/* Size of the data range. The unit is byte.                    */
           ELMO_UINT32   uiErrorCode;            		/* AMS error number                                             */
           ELMO_UINT32   uiInvokeId;             		/* Free usable 32 bit array. Usually this array serves to send  */
														/* an Id. This Id makes is possible to assign a received        */
														/* response to a request, which was sent before                 */
       } AMSHDR_UDP;

    
                    /* Type of function the class calls for get user data as*/
                    /* response to Client requst Read data from Server      */
    typedef ELMO_INT32 (* AMS_CLBK_REQ_READ_UDP)(ELMO_UINT8  ucDataClientReqRead[],
                                         ELMO_UINT32    uiDataClientReqReadSize,
										 ELMO_UINT32    uiIndexGroup,
										 ELMO_UINT32    uiIndexOffset,
										 ELMO_PUINT32   puiResult,
                                         AMSHDR_UDP*    ptAmsHdrFromClient,     /* Copy of the org.         */
                                         AMSHDR_UDP**   pptAmsHdrToClient);     /* If Null take from Rcv    */

                    /* Type of function the class calls for serve client    */
                    /* requsted Write data to server (client sends data)    */
    typedef ELMO_INT32 (* AMS_CLBK_REQ_WRITE_UDP)(ELMO_UINT8 ucDataClientReqWrite[],
                                         ELMO_UINT32    uiDataClientReqWriteSize,
                                         ELMO_UINT32    uiIndexGroup,
                                         ELMO_UINT32    uiIndexOffset,
                                         ELMO_PUINT32   puiResult,
                                         AMSHDR_UDP*    ptAmsHdrFromClient,     /* Copy of the org.         */
                                         AMSHDR_UDP**   pptAmsHdrToClient);     /* If Null take from Rcv    */ 


	/***********************/
	/* Share for TCP & UDP */
	/***********************/
                    /* AMS ADS Command ID. Other commands are not defined or are used Beckhoff internally.  */
                    /* Therefore the Command Id  is only allowed to contain the above enumerated values!    */
                    /* Commad Id, type appearing both (exchange between) 'unsigned short'   */
                    /* and 'eAMS_CMDId' be carfull because enumerated type is 'int',        */
                    /* in ADS/AMS header the command appear in size of 'short'              */
#ifndef	AMS_CMDId_def
#define	AMS_CMDId_def
			/* DEFINE SAME (AND SHOULD BE SO) ON BOTHE:	*/
			/*		AmsUdpProtocol.h					*/
			/*		AmsTcpProtocol.h					*/
    typedef enum AMS_CMDId_TAg
    {
        eAMS_CMDIdInvalid                    =0x0000,
        eAMS_CMDIdReadDeviceInfo             =0x0001,
        eAMS_CMDIdRead                       =0x0002,
        eAMS_CMDIdWrite                      =0x0003,
        eAMS_CMDIdReadState                  =0x0004,
        eAMS_CMDIdWriteControl               =0x0005,
        eAMS_CMDIdAddDeviceNotification      =0x0006,
        eAMS_CMDIdDeleteDeviceNotification   =0x0007,
        eAMS_CMDIdDeviceNotification         =0x0008,
        eAMS_CMDIdReadWrite                  =0x0009
    } eAMS_CMDId;
#endif


                    /* Macros for GET/PUT data from/into stream.        */
                    /* Also change from Little-Endian to Big-Endian.    */
                                                        /* See: GNU "Statement Expressions" */
    #define GET_USHORT(ucStream, offSetOnStream)                        	\
            ({                                                          	\
				ELMO_UINT16       	us1;                                  	\
                ELMO_UINT16       	us0;                                  	\
                us1 = (ELMO_UINT16)ucStream[offSetOnStream + 1] << 8;   	\
                us0 = (ELMO_UINT16)ucStream[offSetOnStream + 0] << 0;   	\
                                    /* Macro return value */            	\
                us0 + us1;                                              	\
            })                                                          	\

                                                        /* See: GNU "Statement Expressions" */
    #define GET_USINT(ucStream, offSetOnStream)                         	\
            ({                                                          	\
                ELMO_UINT32         ui3;                                	\
                ELMO_UINT32         ui2;                                	\
                ELMO_UINT32         ui1;                                	\
                ELMO_UINT32         ui0;                                	\
                ui3 = (ELMO_UINT32)ucStream[offSetOnStream + 3] << 24;   	\
                ui2 = (ELMO_UINT32)ucStream[offSetOnStream + 2] << 16;   	\
                ui1 = (ELMO_UINT32)ucStream[offSetOnStream + 1] <<  8;   	\
                ui0 = (ELMO_UINT32)ucStream[offSetOnStream + 0] <<  0;   	\
                                    /* Macro return value */                \
                ui0 + ui1 + ui2 + ui3;                                      \
            })                                                              \


    #define PUT_USHORT(ucStream, offSetOnStream, usVal)                     \
            ({                                                              \
                ELMO_UINT8       uc1;                                   	\
                ELMO_UINT8       uc0;                                   	\
                uc1 = (ELMO_UINT8)((usVal >> 8) & 0xff);                 	\
                uc0 = (ELMO_UINT8)((usVal >> 0) & 0xff);                 	\
                ucStream[offSetOnStream + 1] = uc1;                         \
                ucStream[offSetOnStream + 0] = uc0;                         \
            })                                                              \


    #define PUT_USINT(ucStream, offSetOnStream, uiVal)                      \
            ({                                                              \
                ELMO_UINT8        uc3;                                   	\
                ELMO_UINT8        uc2;                                   	\
                ELMO_UINT8        uc1;                                   	\
                ELMO_UINT8        uc0;                                   	\
                uc3 = (ELMO_UINT8)((uiVal >> 24) & 0xff);                	\
                uc2 = (ELMO_UINT8)((uiVal >> 16) & 0xff);                	\
                uc1 = (ELMO_UINT8)((uiVal >>  8) & 0xff);                	\
                uc0 = (ELMO_UINT8)((uiVal >>  0) & 0xff);                	\
                ucStream[offSetOnStream + 3] = uc3;                         \
                ucStream[offSetOnStream + 2] = uc2;                         \
                ucStream[offSetOnStream + 1] = uc1;                         \
                ucStream[offSetOnStream + 0] = uc0;                         \
            })                                                              \


#endif		/* #define	__AmsTcpUdpProtocolDef_h__	*/


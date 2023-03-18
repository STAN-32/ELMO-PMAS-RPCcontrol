/*
============================================================================
 Name : AmsUdpProtocolUdp.h
 Author : Haim H.
 Version : 15Jul2015
				24Feb2020
				22Nov2020 HH porting for IntegrationOS3264
 Description :  Implement ADS / AMS Beckhoof protocol above UDP.
                GMAS implementation for be Server responce to ADS client.
				Udp services for ADS/AMS
				This services takes with very little change from MMCUDP


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

#ifndef __AmsUdpProtocolUdp_H__
#define __AmsUdpProtocolUdp_H__

#if   (OS_PLATFORM == LINUXIPC32_PLATFORM)

  //  int GetPort() throw (CMMCException) ;

      /*! \fn int Close_UDP ()
      * \brief this function closes the socket.
      * \return   return - 0 on success, otherwise throws CMMCException or -1 is returned.
      */
      ELMO_INT32 Close_UDP();

  /**\!fn int CreateSocketfnClbk_UDP (unsigned short usPort, int iMsgMaxSize=AMS_MAX_SIZE_DEF_UDP)
   * \brief creates UDP none blocking server (listener)
   * \param usPort port number to listen on (or to bind with)
   * \param iMsgMaxSize largest possible message (in bytes). relevant only for call-back mode of operation.
   * \return 0 on success, -1 otherwise. socket number (iSock) is update on success, otherwise -1;
   */
  ELMO_INT32 CreateSocketfnClbk_UDP (ELMO_UINT16 usPort, int iMsgMaxSize=AMS_MAX_SIZE_DEF_UDP) throw (CMMCException);

  /**\!fn int Receive_UDP(void * pData, unsigned short usSize, long lDelay, sockaddr_in* pSockaddr)
   * \brief receives UDP message pointed by pData.
   * \param pData (IN) pointer to buffer, which will store the received data.
   * \param usSize message size to read.
   * \param lDelay delay time. default is 0 (no delay)
   * \param pSockaddr pointer to socket address. default is NULL.
   *        On call-back mode it shell be delivered to Send by call-back function for synchronous matters.
   * \return number of read bytes, -1 otherwise.
   */
  ELMO_INT32 Receive_UDP(ELMO_PVOID pData, ELMO_UINT16 usSize, ELMO_LINT32 lDelay=0L, sockaddr_in* pSockaddr=NULL) throw (CMMCException);

  /**\!fn int Send_UDP(void * pData, unsigned short usSize, sockaddr_in* pSockaddr)
   * \brief sends udp message pointed by pData.
   * \param pData (IN) pointer to data to send
   * \param usSize message size.
   * \param pSockaddr pointer to socket address. default is NULL.
   *        On call-back mode it may be pointed to the socket address with data from last receive.
   * \return number of bytes actually sent, -1 otherwise.
   */
  ELMO_INT32 Send_UDP(ELMO_PVOID pData, ELMO_UINT16 usSize, sockaddr_in* pSockaddr=NULL) throw (CMMCException);

  //int inline Connect_UDP(char * cIP, int iPort) {return Create(cIP, iPort);}
  ELMO_INT32 Connect_UDP(ELMO_PINT8 szAddr, ELMO_UINT16 usPort, ELMO_BOOL& bWait, ELMO_INT32 iMsgMaxSize=AMS_MAX_SIZE_DEF_UDP) throw (CMMCException);

  /**! \fn int IsReady_UDP();
   * \brief checks for errors and whether or not UDP connection is ready for read operation.
   * return true if ready for read operation, otherwise false.
   */
  ELMO_INT32 IsReady_UDP();

  /**! \fn void SetMaxSize(int iSize);
  * \brief overwrite default message size.
  * \param iSize new message size.
  * |Update: for let user define the max length and not check it...
  * return none.
  */
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!! Do Nothing - (empty function, only for back compatible...!!!
  // !!! For case already exist calling in code...				  !!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  void SetMaxSize(ELMO_INT32 iSize) {}

  /**! \fn bool IsWritable_UDP();
  * \brief checks for errors and whether or not connection is ready for write operation.
  * \param iSock client socket connection to check.
  * return true if writable, otherwise false.
  */
  ELMO_BOOL IsWritable_UDP();

  /**! \fn bool IsReadable_UDP(int iTimeOut=0);
   * \brief checks for errors and whether or not UDP connection is ready for read operation.
   * \param iTimeOut waiting time for checking. default behavior is not to wait.
   * return true if readable, otherwise false.
   */
  ELMO_BOOL IsReadable_UDP(ELMO_INT32 iTimeOut=0);

  private:
      /**! \fn int IsPending(int iSock, bool& bFail)
      * \brief check pending connection on a non blocking socket
      *  actuall checks for errors and whether or not connection is ready for write operation.
      * \param iSock client socket connection to check.
      * \param bFail true if error(socket must be closed then), false otherwise.
      * \return: OK if connection complete / ERROR if fail or still pending
      */
      ELMO_INT32 IsPending(ELMO_INT32 iSock) throw (CMMCException);

      /*! \fn int SetSocketTimeout(int  iMilliseconds)
      * \brief this function set socket to block only for iMilliseconds on receive operation.
      * \param iMilliseconds - timeout in ms to wait on receive.
      * \return   return - 0 on success, otherwise throws CMMCException or none zero error..
      */
      ELMO_INT32 SetSocketTimeout(ELMO_INT32 iMilliseconds);
      friend ELMO_PVOID fnAmsUDPClbkThread(ELMO_PVOID);	//call-back argument for pthread_create within RunClbkThread.
      ELMO_INT32 RunClbkThread();                    	//launches the call-back thread for call-back mode of operation.
      void ClbkThread();                      //the actual implementation of call-back mode of operation.

  private:
      typedef void (CMMCAmsUdpProtocol::*PCLBKTHREAD)(ELMO_PVOID);
      PCLBKTHREAD 	_pThreadClbk;
      ELMO_INT32 	_iSock;
      ELMO_UINT16	_usPort;
  //  struct sockaddr_in m_sockAddrIn;    //old client convention
      struct sockaddr_in m_sockAddrOut;   //new client/server convention
      ELMO_INT32 	_iMsgMaxSize;
      ELMO_BOOL 	_bClbkThreadAlive;
      pthread_t 	_thread;


#endif	/* #if   (OS_PLATFORM == LINUXIPC32_PLATFORM) */

#endif	/* #ifndef __AmsUdpProtocolUdp_H__ */


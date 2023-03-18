/*
 * CMMCUdp.hpp
 *
 *  Created on: 28/06/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */

#ifndef CMMCUDP_HPP_
#define CMMCUDP_HPP_


#include "MMCSocket.hpp"
/*
 *
 */
#define MMCUDP_MaxSize  512
class DLLMMCPP_API CMMCUDP {
public:
    CMMCUDP();
    virtual ~CMMCUDP();

    inline void SetMessageMaxSize(int iSize) {_iMsgMaxSize = iSize;}

    /*! \fn int Create (char * cIP, int iPort) throw (CMMCException)
    * \brief this function creates the socket.
    * \param cIP - IP address of driver.
    * \param iPort - port for socket connection.
    * \return   return - 0 on success, otherwise throws CMMCException or non zero.
    */
    ELMO_INT32 Create (ELMO_PINT8 cIP, ELMO_INT32 iPort, ELMO_INT32 iGMASPort = 0, ELMO_INT32 iMaxSize = 512) throw (CMMCException) ;

    /*! \fn int SendTo(char* msg, short sLength) throw (CMMCException)
    * \brief this function sends data via socket.
    * \param msg - message buffer to send..
    * \param sLength - length (bytes) of data to send. must not be more then buffer length.
    * \return result>=0 on success, otherwise throws CMMCException or -1.
    */
    ELMO_INT32 SendTo(ELMO_PINT8 msg, ELMO_INT16 sLength, ELMO_BOOL clrRcvBuf=true) ;//throw (CMMCException);

    /*! \fn int RecvFrom(char* msg, short sLength, short sTimeoutMS) throw (CMMCException)
    * \brief this function receives data from socket.
    * \param msg - message buffer to receive data..
    * \param sLength - length to read. must not be more then buffer length.
    * \param sTimeoutMS - milliseconds to wait on receive.
    * \return   return - result>=0 on success, otherwise throws CMMCException or result<0.
    */
    ELMO_INT32 ReceiveFrom(ELMO_PINT8 msg, ELMO_INT16 sLength, ELMO_INT16 sTimeout) throw (CMMCException);


    /*! \fn int GetIP(char* msg, short sLength) throw (CMMCException)
    * \brief This function returns the ip of the connection
    * \return the IP address as character array.
    */
    in_addr GetIP() ;//throw (CMMCException);

//  int GetPort() throw (CMMCException) ;

    /*! \fn int Close ()
    * \brief this function closes the socket.
    * \return   return - 0 on success, otherwise throws CMMCException or -1 is returned.
    */
    ELMO_INT32 Close();
    
/*-------------------------------------------------------------------------
* new API for UDP class basically to comply with TCP API
*/

/**\!fn int Create (unsigned short usPort, SOCK_CLBK fnClbk=NULL, int iMsgMaxSize=512)
 * \brief creates UDP none blocking server (listener)
 * \param usPort port number to listen on (or to bind with)
 * \param fnClbk user call-back function. relevant only for call-back mode of operation.
 * \param iSock reference to socket file (descriptor)
 * \param iMsgMaxSize largest possible message (in bytes). relevant only for call-back mode of operation.
 * \return 0 on success, -1 otherwise. socket number (iSock) is update on success, otherwise -1;
 */
ELMO_INT32 Create (ELMO_UINT16 usPort, SOCK_CLBK fnClbk=NULL, ELMO_INT32 iMsgMaxSize=512) throw (CMMCException);

/**\!fn int Receive (void * pData, unsigned short usSize, long lDelay, sockaddr_in* pSockaddr)
 * \brief receives UDP message pointed by pData.
 * \param pData (IN) pointer to buffer, which will store the received data.
 * \param usSize message size to read.
 * \param lDelay delay time. default is 0 (no delay)
 * \param pSockaddr pointer to socket address. default is NULL.
 *        On call-back mode it shell be delivered to Send by call-back function for synchronous matters.
 * \return number of read bytes, -1 otherwise.
 */
ELMO_INT32 Receive (ELMO_PVOID pData, ELMO_UINT16 usSize, ELMO_LINT32 lDelay=0L, sockaddr_in* pSockaddr=NULL) throw (CMMCException);
/**\!fn int Send (void * pData, unsigned short usSize, sockaddr_in* pSockaddr)
 * \brief sends udp message pointed by pData.
 * \param pData (IN) pointer to data to send
 * \param usSize message size.
 * \param pSockaddr pointer to socket address. default is NULL.
 *        On call-back mode it may be pointed to the socket address with data from last receive.
 * \return number of bytes actually sent, -1 otherwise.
 */
ELMO_INT32 Send (ELMO_PVOID pData, ELMO_UINT16 usSize, sockaddr_in* pSockaddr=NULL) throw (CMMCException);
//int inline Connect(char * cIP, int iPort) {return Create(cIP, iPort);}
ELMO_INT32 Connect(ELMO_PINT8 szAddr, ELMO_UINT16 usPort, ELMO_BOOL& bWait, ELMO_INT32 iMsgMaxSize=512) throw (CMMCException);

/**! \fn int IsReady();
 * \brief checks for errors and whether or not UDP connection is ready for read operation.
 * return true if ready for read operation, otherwise false.
 */
ELMO_INT32 IsReady();

/**! \fn void SetMaxSize(int iSize);
* \brief overwrite default (512)  message size.
* \param iSize new message size.
* return none.
*/
void SetMaxSize(ELMO_INT32 iSize) {_iMsgMaxSize = (iSize>512 || iSize < 0)?512:iSize;}

/**! \fn bool IsWritable();
* \brief checks for errors and whether or not connection is ready for write operation.
* \param iSock client socket connection to check.
* return true if writable, otherwise false.
*/
ELMO_BOOL IsWritable();

/**! \fn bool IsReadable(int iTimeOut=0);
 * \brief checks for errors and whether or not UDP connection is ready for read operation.
 * \param iTimeOut waiting time for checking. default behavior is not to wait.
 * return true if readable, otherwise false.
 */
ELMO_BOOL IsReadable(ELMO_INT32 iTimeOut=0);

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

// ????????????????? HH (Needs change...) ????????????
#if ((OS_PLATFORM == WIN32_PLATFORM) || (OS_PLATFORM == WIN64_PLATFORM))
    friend DWORD WINAPI fnUDPClbkThread(ELMO_PVOID lpParam);
#elif ((OS_PLATFORM == LINUXIPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC64_PLATFORM))
    friend ELMO_PVOID    fnUDPClbkThread(ELMO_PVOID lpParam);   //call-back argument for pthread_create within RunClbkThread.
// #elif    (OS_PLATFORM == VXWORKS32_PLATFORM)
//  // Not implemented yet...
#else
    #error "***MMCUdp.hpp Symbol 'OS_PLATFORM' (1) is out of range... (See OS_PlatformSelect.h) "
#endif
// ????????????????? HH (Needs change...) ????????????

    ELMO_INT32 RunClbkThread();                    //launches the call-back thread for call-back mode of operation.
    void ClbkThread();                      //the actual implementation of call-back mode of operation.

private:
    typedef void (CMMCUDP::*PCLBKTHREAD)(ELMO_PVOID);
    PCLBKTHREAD _pThreadClbk;
    ELMO_INT32   _iSock;
    ELMO_UINT32  _usPort;
//  struct sockaddr_in m_sockAddrIn;    //old client convention
    struct sockaddr_in m_sockAddrOut;   //new client/server convention
    SOCK_CLBK   _fnClbk;
    ELMO_INT32   _iMsgMaxSize;
    ELMO_BOOL    _bClbkThreadAlive;

// ????????????????? HH (Needs change...) ????????????
#if ((OS_PLATFORM == WIN32_PLATFORM) || (OS_PLATFORM == WIN64_PLATFORM))
    WSADATA     m_wsaData;
    HANDLE      _thread;
#elif ((OS_PLATFORM == LINUXIPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC64_PLATFORM))
    pthread_t   _thread;
// #elif    (OS_PLATFORM == VXWORKS32_PLATFORM)
//  // Not implemented yet...
#else
    #error "***MMCUdp.hpp Symbol 'OS_PLATFORM' (2) is out of range... (See OS_PlatformSelect.h) "
#endif
// ????????????????? HH (Needs change...) ????????????

};
#endif /* CMMCUDP_HPP_ */

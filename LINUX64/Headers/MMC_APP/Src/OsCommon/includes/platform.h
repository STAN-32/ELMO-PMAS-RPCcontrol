/****************************************************************************
*****************************************************************************
**
** File Name
** ---------
**
** PLATFORM.h
**
** COPYRIGHT (c) 2003 Pyramid Solutions, Inc.
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
**
** Platform dependant declarations and definitions.
**
*****************************************************************************
*****************************************************************************
**
** Source Change Indices
** ---------------------
**
** Porting: <none>----0<major>         Customization: <none>----0<major>
**
*****************************************************************************
*****************************************************************************
*/

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/timeb.h>
#include <time.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stddef.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>


/************************ Platform specific defines *************************/

#define INT8            signed char
#define UINT8           unsigned char
#define INT16           signed short
#define UINT16          unsigned short
#define INT32           signed int
#define UINT32          unsigned int
#define DWORD			unsigned int
#define WORD			unsigned short
#define UINT			unsigned short
#define BOOL			unsigned char
#define BYTE			unsigned char
#define USHORT			unsigned short
#define TCHAR			char

#define VOID			void
#define SINT16			signed short
#ifndef SO_DONTLINGER
#define SO_DONTLINGER   (int)(~SO_LINGER)
#endif

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

//#define TRACE_OUTPUT
//#define TRACE_FILE_OUTPUT

#define IS_BYTE(x)	( (((UINT16)x & 0xFF00)==0) ? TRUE : FALSE )

#define PLATFORM_MIN(x,y) ((x < y) ? x : y)
#define PLATFORM_MAX(x,y) ((x > y) ? x : y)

#if !defined(_T)
#define _T
#endif

#define MAX_LOG_FILE_PATH	128

/*
** Socket porting defines
*/

#define INVALID_SOCKET	(-1)

/*
** Platform specific Mutex and Event typedefs
*/

typedef pthread_mutex_t* PLATFORM_MUTEX_TYPE;

/*
** TCP/IP Configuration Data structure for use w/ platformGetTcpIpCfgData()
*/

#define DOMAIN_NAME_LEN		48


#define EIP_BIG_ENDIAN   // GMAS is big endian

#define EIP_STACK_MEMORY  // do not use malloc


/********************************* Typedefs ***********************************/

/*
** Name of the Ethernet device for use by platformGetMacID()
*/

#define EN_DEVNAME "eth0"


/*
** Number of milliseconds between executions of the EADK main task
*/

#define TIMER_INTERVAL		1		/* Main task should be executed once per TIMER_INTERVAL milliseconds */

/*
** Maximum time to wait for the mutex before timing out. Has no use in UNIX
*/

#define MUTEX_TIMEOUT		0


/*
** Public Function prototypes
*/

extern UINT32 platformGetCurrentTickCount(void);

extern void platformGetEnetData( void );

extern void platformSleep(int ticks);

extern void platformSetBlockSocket(int sid, int on);

extern PLATFORM_MUTEX_TYPE platformInitMutex(char *strMutexName);
extern void platformDiscardMutex(PLATFORM_MUTEX_TYPE xMutex);

extern void platformInitLogFile(void);
extern void platformCloseLogFile(void);
extern void platformWriteLog(UINT8 iSeverity, UINT16 iType, UINT32 lSrcIp, UINT32 lDstIp, char *szBuf, BOOL bTimeStamp);
extern UINT32 platformAddrFromPath( const char* szPath, INT32 nLen );


/*
** Macro definitions
*/

#define platformIoctl(sock,cmnd,argp) ioctl(sock, cmnd, argp)
#define platformSetSockOpt(s,l,o,d,dl)		setsockopt(s,l,o,d,dl)
#define platformGetLastError() errno
#define platformGetLastSocketError(socket) platformGetLastError()
#define platformCloseSocket(sock) close(sock)
#define platformSetSockBufSize( p1,p2,p3,p4,p5) 0  
#define platformSocketLibInit()
#define platformSocketLibCleanup()	

#define platformInetNtoa(in)				inet_ntoa(in)

#define platformAccept(s, a, l)				accept(s, a, l)
#define platformBind(s, a, l)				bind(s, a, l)
#define platformConnect(s,a,al)				connect(s,a,al)
#define platformGetPeerName(socket, name, len)	getpeername(socket, name, len)
#define platformListen(s, i)				listen(s, i)
#define platformRecv(s,b,l,f)				recv(s,b,l,f)
#define platformRecvFrom(s,b,l,f,a,al)		recvfrom(s,b,l,f,a,al)
#define platformSelect(n, i, o, e, t)		select(n, i, o, e, t)
#define platformSend(s,b,l,f)				send(s,b,l,f)
#define platformSendTo(s,b,l,f,a,al,p)		sendto(s,b,l,f,a,al)
#define platformSocket(x,y,z)				socket(x,y,z)
#define platformGetInternetAddress(addr)	addr.s_addr
#define platformGetSockName(x,y,z)			getsockname(x,y,z)
#define platformGetHostName(name, host)		gethostname(name, host)
#define platformGetHostByName(name, host)	gethostbyname(name)

#define platformReleaseMutex(xMutex) pthread_mutex_unlock( xMutex )
#define platformWaitMutex(xMutex, lWait) pthread_mutex_lock( xMutex )

#endif /* #ifndef PLATFORM_H */


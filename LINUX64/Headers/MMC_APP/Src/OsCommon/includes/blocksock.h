/*
 blocksock.h
 31jan2013 Haim Hillel
 19Jan2015 Haim Hillel
 Update for handle multi operating system.
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///				  0.4.0 Updated 11Sep2017 Haim H.

 */
#ifndef _BLOCKSOCK_
#define _BLOCKSOCK_


typedef struct sockaddr* LPCSOCKADDR;


ELMO_BOOL    DisableNagelAlg        (MMC_IF_STRUCT*  pMmcIf, ELMO_PINT8  cErr);
ELMO_BOOL    BindSocket             (MMC_IF_STRUCT*  pMmcIf, ELMO_PINT8  cpHostIPAddr, ELMO_PINT8 cErr);
ELMO_BOOL    ConnectSocket          (MMC_IF_STRUCT*  pMmcIf, LPCSOCKADDR psa, ELMO_PINT8 cErr);
ELMO_BOOL    DisConnectSocket       (MMC_IF_STRUCT*  pMmcIf, ELMO_PINT8  cErr);
ELMO_INT32   Send                   (MMC_IF_STRUCT*  pMmcIf, ELMO_PINT8  pch,          const ELMO_INT32 nSize, ELMO_PINT8 cErr);
ELMO_INT32   Receive                (MMC_IF_STRUCT*  pMmcIf, ELMO_PINT8  pch,          const ELMO_INT32 nSize, ELMO_PINT8 cErrStr);
ELMO_INT32   CreateUDPSocketListener(MMC_IF_STRUCT*  pMmcIf, ELMO_PINT8  cErrStr,      ELMO_PINT8 udp_address);

#endif

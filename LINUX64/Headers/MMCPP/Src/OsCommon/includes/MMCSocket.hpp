/*
 * MMCSocket.hpp
 *
 *  Created on: 25/12/2012
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */

#ifndef MMCSOCKET_HPP_
#define MMCSOCKET_HPP_

#include "MMCPPGlobal.hpp"


#define MMCPP_RETERROR  1
#define MMCPP_RETOK     0
#define MMCPP_INVSOCKET -1
#define MMCPP_SOCKERROR -1

#define MMCPP_SOCK_INFINIT_BLOCK    -1
#define MMCPP_SOCK_EOE_RETRIES      3
#define MMCPP_SOCK_NEW_EVENT        10
#define MMCPP_SOCK_READY_EVENT      11
#define MMCPP_SOCK_CLOSED_EVENT     12
#define MMCPP_SOCK_ABORT_EVENT      13
#define MMCPP_SOCK_MAXLIM_EVENT     14

#ifdef __cplusplus
extern "C" {
#endif
typedef ELMO_INT32 (*SOCK_CLBK)(ELMO_INT32, ELMO_INT16, ELMO_PUINT8, ELMO_INT32, ...);
#ifdef __cplusplus
}
#endif

#endif /* MMCSOCKET_HPP_ */

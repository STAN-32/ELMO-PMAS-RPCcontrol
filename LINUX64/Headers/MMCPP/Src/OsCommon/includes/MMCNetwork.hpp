/*
 * MMCNetwork.hpp
 *
 *  Created on: 27/03/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */

#ifndef MMCNETWORK_HPP_
#define MMCNETWORK_HPP_

#include "MMCPPGlobal.hpp"

class DLLMMCPP_API CMMCNetwork {
public:
    CMMCNetwork();
    ~CMMCNetwork();

    void SetConnHndl(MMC_CONNECT_HNDL uiConnHndl) {m_uiConnHndl = uiConnHndl;}

    void ResetCommStatistics(MMC_RESETCOMMSTATISTICS_OUT& stOutParams) throw (CMMCException);
    void ResetCommDiagnostics(MMC_RESETCOMMDIAGNOSTICS_OUT& stOutParams) throw (CMMCException);
    void GetCommDiagnostics(MMC_GETCOMMDIAGNOSTICS_OUT& stOutParams) throw (CMMCException);
    ELMO_INT32 GetCommStatistic(MMC_GETCOMMSTATISTICS_OUT& stOutParams) throw (CMMCException);
    ELMO_INT32 GetNetworkInfo(MMC_NETWORKINFO_OUT& stOutParams) throw (CMMCException);
    //
private:
    MMC_CONNECT_HNDL m_uiConnHndl;                  /*!< communication session handler;                 */
};

#endif /* MMCNETWORK_HPP_ */

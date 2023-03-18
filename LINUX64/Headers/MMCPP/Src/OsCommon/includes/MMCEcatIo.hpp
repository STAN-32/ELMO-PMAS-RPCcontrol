/*
 * CMMCECATIO.h
 *
 *  Created on: 27/06/2011
 *      Author: yuvall
 *      Update: Haim H. 16Sep2019 Changes for support Multi type of OS.
 */

#ifndef CMMCECATIO_H_
#define CMMCECATIO_H_

#include "MMCGroupAxis.hpp"
#include "MMCNode.hpp"

/*
 *
 */
class DLLMMCPP_API CMMCECATIO : public CMMCNode {
public:
    CMMCECATIO();
    virtual ~CMMCECATIO();

    void        ECATIOEnableDIChangedEvent  (                                       )   throw (CMMCException);
    void        ECATIODisableDIChangedEvent (                                       )   throw (CMMCException);
    MMCPPULL_T  ECATIOReadDigitalInput      (                                       )   throw (CMMCException);
    void        ECATIOWriteDigitalOutput    (MMCPPULL_T ulliDO                      )   throw (CMMCException);
    ELMO_INT16  ECATIOReadAnalogInput       (ELMO_UINT8 ucIndex                     )   throw (CMMCException);
    void        ECATIOWriteAnalogOutput     (ELMO_UINT8 ucIndex, ELMO_INT16 sAOValue)   throw (CMMCException);

};

#endif /* CMMCECATIO_H_ */

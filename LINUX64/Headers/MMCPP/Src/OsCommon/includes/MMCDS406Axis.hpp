/*
 * MMCDS406Axis.hpp
 *
 *  Created on: 27/03/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 *              0.4.0 Updated 11Sep2017 Haim H.
 */

#ifndef MMCDS406_HPP_
#define MMCDS406_HPP_

#include "MMCNode.hpp"

#ifdef PROAUT_CHANGES
	//save compiler switches
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

class DLLMMCPP_API CMMCDS406 : public CMMCNode {
public:
    CMMCDS406();
    ~CMMCDS406();

    ELMO_DOUBLE GetActualPosition() throw (CMMCException);

    //
    /*! \fn void ConfigGeneralTPDO3()
    *   \brief This function configure to transmit general PDO3 message.
    *   \return - void.
    */
    void ConfigGeneralTPDO3(ELMO_UINT8 ucEventType) throw(CMMCException);

    //
    /*! \fn void ConfigGeneralTPDO4()
    *   \brief This function configure to transmit general PDO4 message.
    *   \return - void.
    */
    void ConfigGeneralTPDO4(ELMO_UINT8 ucEventType) throw(CMMCException);

    //
    /*! \fn void CancelGeneralTPDO3()
    *   \brief This function cancle the configuration of transmitting general PDO3 message.
    *   \return - void.
    */
    void CancelGeneralTPDO3() throw(CMMCException);

    //
    /*! \fn void CancelGeneralTPDO4()
    *   \brief This function cancle the configuration of transmitting general PDO3 message.
    *   \return - void.
    */
    void CancelGeneralTPDO4() throw(CMMCException);

private:

    void PDOGeneralWrite(ELMO_UINT8 ucParam,MMCPPULL_T ulliVal)throw (CMMCException){return;}
    void GetPDOInfo(ELMO_UINT8 uiPDONumber, ELMO_INT32 &iPDOEventMode, ELMO_UINT8 &ucPDOCommType, ELMO_UINT8 &ucTPDOCommEventGroup, ELMO_UINT8 &ucRPDOCommEventGroup)throw (CMMCException){return;}

};


#ifdef PROAUT_CHANGES
	//restore compiler switches
	#pragma GCC diagnostic pop
#endif


#endif /* MMCDS406_HPP_ */

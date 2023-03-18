/*
 * CMMCModbusBuffer.hpp
 *
 *  Created on: 26/04/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */

#ifndef CMMCMODBUSBUFFER_HPP_
#define CMMCMODBUSBUFFER_HPP_
#include "MMC_definitions.h"
#include "MMCPPGlobal.hpp"

class DLLMMCPP_API CMMCModbusBuffer {
public:
    CMMCModbusBuffer();
    CMMCModbusBuffer(ELMO_INT32 iOffset, ELMO_INT32 iCount=0);
    virtual ~CMMCModbusBuffer();

    inline void SetOffset  (ELMO_INT32 iOffset) {m_inBuffer.startRef=iOffset;}
    inline void SetRefCount(ELMO_INT32 iCount)  {m_inBuffer.refCnt = iCount;}

    void SetValue (ELMO_INT32 iIndex, ELMO_FLOAT fValue);
    void SetValue (ELMO_INT32 iIndex, ELMO_LINT32 lValue);
    void SetValue (ELMO_INT32 iIndex, ELMO_INT16  sValue);

    void GetValue (ELMO_INT32 iIndex, ELMO_FLOAT & fValue);
    void GetValue (ELMO_INT32 iIndex, ELMO_LINT32 & lValue);
    void GetValue (ELMO_INT32 iIndex, ELMO_INT16 &  sValue);
    void TypeToModbusShortArr(ELMO_INT32 iIndex,  ELMO_FLOAT fVal);
    void TypeToModbusShortArr(ELMO_INT32 iIndex,  ELMO_LINT32 lVal);
    void TypeToModbusShortArr(ELMO_INT32 iIndex,  ELMO_INT16  sVal);
    inline MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& GetBuffer() {return m_inBuffer;}

  protected:
    MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN m_inBuffer;
};

#endif /* CMMCMODBUSBUFFER_HPP_ */

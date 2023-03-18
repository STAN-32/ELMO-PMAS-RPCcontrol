/*
 * CMMCHostComm.hpp
 *
 *  Created on: 24/03/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */

#ifndef CHOSTCOMM_HPP_
#define CHOSTCOMM_HPP_

#include "MMCPPGlobal.hpp"
#include "MMCModbusSwapBuffer.hpp"


class DLLMMCPP_API CMMCHostComm {
public:
    CMMCHostComm() {m_uiConnHndl= 0 ;}
    ~CMMCHostComm() {}

    inline void MbusSetConnection(MMC_CONNECT_HNDL uiConnHndl) {m_uiConnHndl = uiConnHndl;}
    void MbusStartServer(MMC_CONNECT_HNDL uiConnHndl, ELMO_UINT16 usID) throw (CMMCException);
    void MbusStopServer() throw (CMMCException);
    void MbusReadHoldingRegisterTable(int startRef, int refCnt, MMC_MODBUSREADHOLDINGREGISTERSTABLE_OUT& stOutParams) throw (CMMCException);
    void MbusWriteHoldingRegisterTable(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams) throw (CMMCException);
    bool MbusIsRunning(MMC_CONNECT_HNDL uiConnHndl = NULL) throw (CMMCException);
    void MbusReadCoilsTable(ELMO_INT32 startRef, ELMO_INT32 refCnt, MMC_MODBUSREADCOILS_OUT& stOutParams) throw (CMMCException);
    void MbusWriteCoilsTable(MMC_MODBUSWRITECOILS_IN& stInParams) throw (CMMCException);
    void MbusReadInputsTable(ELMO_INT32 startRef, ELMO_INT32 refCnt, MMC_MODBUSREADINPUTS_OUT& stOutParams) throw (CMMCException);

    void SetModbusLong(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, ELMO_INT32 iOffset, ELMO_LINT32 lValue) throw (CMMCException);
    void SetModbus(ELMO_INT32 iOffset, ELMO_LINT32 lValue) throw (CMMCException);
    void SetModbus(ELMO_INT32 iOffset, ELMO_FLOAT fValue) throw (CMMCException);
    void SetModbus(ELMO_INT32 iOffset, ELMO_INT16 sValue) throw (CMMCException);

    void SetModbusLongSwapped(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, ELMO_INT32 iOffset, ELMO_LINT32 lPos) throw (CMMCException);
    void SetModbusShort(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, ELMO_INT32 iOffset, ELMO_INT16 sPos) throw (CMMCException);
    void SetModbusFloat(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, ELMO_INT32 iOffset, ELMO_FLOAT fPos) throw (CMMCException);
    void SetModbusFloatSwapped(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, ELMO_INT32 iOffset, ELMO_FLOAT fPos) throw (CMMCException);
    void SetModbus(ELMO_INT32 iOffset, ELMO_INT32 iRefCount, CMMCModbusBuffer& stInParams) throw (CMMCException);
    void SetModbus(ELMO_INT32 iOffset, ELMO_INT32 iRefCount, CMMCModbusSwapBuffer& stInParams) throw (CMMCException);

    void GetModbus(ELMO_INT32 iOffset, ELMO_INT32 iRefCount, CMMCModbusBuffer& stOutParams) throw (CMMCException);
    void GetModbus(ELMO_INT32 iOffset, ELMO_INT32 iRefCount, CMMCModbusSwapBuffer& stOutParams) throw (CMMCException);


protected:
    //
    void LongToModbusShortArr(ELMO_PINT16 spArr, ELMO_LINT32 lVal)
    {
          *spArr      = (ELMO_INT16) (lVal   & 0xFFFF);
          *(spArr + 1)= (ELMO_INT16)((lVal >> 16) & 0xFFFF);
    }
    void SwapLongToModbusShortArr(ELMO_PINT16 spArr, ELMO_LINT32 lVal)
    {
          *spArr      = (ELMO_INT16)((lVal >> 16) & 0xFFFF);
          *(spArr + 1)= (ELMO_INT16) (lVal & 0xFFFF);
    }

    void FloatToModbusShortArr(ELMO_PINT16 spArr, ELMO_FLOAT fVal)
    {
        union {
            ELMO_FLOAT fVal;
            ELMO_LINT32 lVal;
        } lfloat;
        lfloat.fVal = fVal;

        *spArr      = (ELMO_INT16) (lfloat.lVal & 0xFFFF);
        *(spArr + 1)= (ELMO_INT16)((lfloat.lVal >> 16) & 0xFFFF);
    }
    void SwapFloatToModbusShortArr(ELMO_PINT16 spArr, ELMO_FLOAT fVal)
    {
        union {
            ELMO_FLOAT fVal;
            ELMO_LINT32 lVal;
        } lfloat;
        lfloat.fVal = fVal;
        *spArr      = (ELMO_INT16)((lfloat.lVal >> 16) & 0xFFFF);
        *(spArr + 1)= (ELMO_INT16) (lfloat.lVal & 0xFFFF);
    }

private:
    MMC_CONNECT_HNDL m_uiConnHndl;
};

#endif /* CHOSTCOMM_HPP_ */

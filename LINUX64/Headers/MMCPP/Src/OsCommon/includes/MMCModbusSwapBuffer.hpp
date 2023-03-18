/*
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */
#ifndef IMMC_MODBUS_SWAPLONG_BUFF_HPP_
#define IMMC_MODBUS_SWAPLONG_BUFF_HPP_

#include "MMCModbusBuffer.hpp"

class DLLMMCPP_API CMMCModbusSwapBuffer
{
public:
    CMMCModbusSwapBuffer();
    CMMCModbusSwapBuffer(ELMO_INT32 iOffset, ELMO_INT32 iCount=0);
    virtual ~CMMCModbusSwapBuffer() {};

    inline void SetOffset  (ELMO_INT32 iOffset){m_inBuffer.startRef = iOffset;}
    inline void SetRefCount(ELMO_INT32 iCount) {m_inBuffer.refCnt=iCount;}

    void SetValue (ELMO_INT32 iIndex, ELMO_LINT32 lValue);
    void SetValue (ELMO_INT32 iIndex, ELMO_FLOAT  fValue);
    void GetValue (ELMO_INT32 iIndex, ELMO_LINT32 & lValue);
    void GetValue (ELMO_INT32 iIndex, ELMO_FLOAT& fValue);
    template <typename T>
    void TypeToModbusShortArr(ELMO_INT32 iIndex, T tValue)
    {
        union {
            T tVal;
            ELMO_ULINT32 ulVal;
        } ltype;
        ltype.tVal = tValue;
        m_inBuffer.regArr[iIndex+1]  =  (ELMO_INT16) (ltype.ulVal & 0xFFFF);
        m_inBuffer.regArr[iIndex]= (ELMO_INT16)((ltype.ulVal >> 16) & 0xFFFF);
    }

    inline MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& GetBuffer() {return m_inBuffer;}

  private:

    MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN m_inBuffer;
};


#endif //IMMC_MODBUS_SWAPLONG_BUFF_HPP_

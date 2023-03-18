/*
 * MMCEoE.hpp
 *
 *  Created on: 06/01/2013
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */

#ifndef MMCEOE_HPP_
#define MMCEOE_HPP_

#include "MMCSocket.hpp"
#include "MMCUdp.hpp"

#define EoE_BUFFER_SIZE 128

/*
 *
 */
class DLLMMCPP_API CMMCEoE : public CMMCUDP {
public:
    /**
    * default constructor
    */
    CMMCEoE();

    /**
    * default destructor
    */
    virtual ~CMMCEoE()
    {
        this->DestroySemSyncDrvIo();
    }

    /**! \fn SetTimeout(long lTimeOut)
    * \brief set default time out for UDP socket.
    * \param lTimeOut default to set.
    * \return none
    */
    void SetTimeout(ELMO_LINT32 lTimeOut) {this->_lTimeOut = lTimeOut;}

    /**! \fn ElmoSetAsyncArray(char szCmd[3], short iIndex, const int iVal)
     * \brief send EoE array command asynchronously.
     * \param szCmd the command
     * \param iIndex EoE array index
     * \param iValue integer value to set.
     * \return 0 on success otherwise error (<0).
     */
    ELMO_INT32 ElmoSetAsyncArray(ELMO_INT8 cCmd[3], ELMO_INT16 iIndex, const ELMO_INT32 iVal)throw (CMMCException);

    /**! \fn ElmoSetAsyncArray(char szCmd[3], short iIndex, const float fVal)
     * \brief send EoE array command asynchronously.
     * \param szCmd the command
     * \param iIndex EoE array index
     * \param fVal real value to set.
     * \return 0 on success otherwise error (<0).
     */
    ELMO_INT32 ElmoSetAsyncArray(ELMO_INT8 cCmd[3], ELMO_INT16 iIndex, const ELMO_FLOAT fVal)throw (CMMCException);

    /**! \fn ElmoSetAsyncParameter(char szCmd[3], const int iVal)
     * \brief send EoE command asynchronously.
     * \param szCmd the command
     * \param iVal value to set.
     * \return 0 on success otherwise error (<0).
     */
    ELMO_INT32 ElmoSetAsyncParameter(ELMO_INT8 cCmd[3], const ELMO_INT32 iVal)throw (CMMCException);

    /**! \fn ElmoSetAsyncParameter(char szCmd[3], const int fVal)
     * \brief sends EoE command asynchronously.
     * \param szCmd the command
     * \param fValue value to set.
     * \return 0 on success otherwise error (<0).
     */
    ELMO_INT32 ElmoSetAsyncParameter(ELMO_INT8 cCmd[3], const ELMO_FLOAT fVal)throw (CMMCException);

    /**! \fn ElmoSetArray(char szCmd[3], short iIndex, const int iVal)
     * \brief send EoE array command.
     * \param szCmd the command
     * \param iIndex EoE array index
     *  \param iVal integer value to set.
     * \return 0 on success otherwise error (<0).
     */
    ELMO_INT32 ElmoSetArray(ELMO_INT8 cCmd[3], short iIndex, const ELMO_INT32 iVal)throw (CMMCException);

    /**! \fn ElmoSetArray(char szCmd[3], short iIndex, const int fVal)
     * \brief send EoE array command.
     * \param szCmd the command
     * \param iIndex EoE array index
     *  \param fVal real value to set.
     * \return 0 on success otherwise error (<0).
     */
    ELMO_INT32 ElmoSetArray(ELMO_INT8 cCmd[3], ELMO_INT16 iIndex, const ELMO_FLOAT fVal)throw (CMMCException);

    /*! \fn ElmoSetParameter(char szCmd[3], const int iVal)
    * \brief sets parameter of type int.
    * \param szCmd string command.
    * \param iVal integer value to set.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoSetParameter(ELMO_INT8 cCmd[3], const ELMO_INT32 iVal)throw (CMMCException);

    /*! \fn ElmoSetParameter(char szCmd[3], const int fVal)
    * \brief sets parameter of type float.
    * \param szCmd string command.
    * \param fVal float value to set.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoSetParameter(ELMO_INT8 cCmd[3], const ELMO_FLOAT fVal)throw (CMMCException);

    /*! \fn ElmoGetAsyncArray(char szCmd[3], short iIndex, int& fVal)
    * \brief sends asynchronous array command to get EoE parameter.
    *       one may get the result asynchronously as follows:
    *       call IsReady, then ElmoReadData API.
    * \param szCmd string command.
    * \param iIndex index to array cell.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoGetAsyncArray(ELMO_INT8 cCmd[3], ELMO_INT16 iIndex)throw (CMMCException);

    /*! \fn ElmoGetAsyncParameter(char szCmd[3])
    * \brief sends asynchronous command to get EoE parameter.
    *       one may get the result asynchronously as follows:
    *       call IsReady, then ElmoReadData API.
    * \param szCmd string command.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoGetAsyncParameter(ELMO_INT8 cCmd[3])throw (CMMCException);

    /*! \fn ElmoGetArray(char szCmd[3], short iIndex, int& iVal)
    * \brief sends command to get EoE parameter of type integer.
    * \param szCmd string command.
    * \param iIndex index to EoE array.
    * \param iVal reference for returned value.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoGetArray(ELMO_INT8 cCmd[3], ELMO_INT16 iIndex, ELMO_INT32 & iVal)throw (CMMCException);

    /*! \fn ElmoGetArray(char szCmd[3], short iIndex, int& iVal)
    * \brief sends command to get EoE parameter of type float.
    * \param szCmd string command.
    * \param iIndex index to EoE array.
    * \param fVal reference for returned value.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoGetArray(ELMO_INT8 cCmd[3], ELMO_INT16 iIndex, ELMO_FLOAT & fVal)throw (CMMCException);

    /*! \fn ElmoGetParameter(char szCmd[3], int& iVal)
    * \brief gets EoE parameter of type integer.
    * \param szCmd string command.
    * \param iVal reference for returned value.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoGetParameter(ELMO_INT8 cCmd[3], ELMO_INT32 & iVal)throw (CMMCException);

    /*! \fn ElmoGetParameter(char szCmd[3], float& fVal)
    * \brief gets EoE parameter of type float.
    * \param szCmd string command.
    * \param fVal reference for returned value.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoGetParameter(ELMO_INT8 cCmd[3], ELMO_FLOAT & fVal)throw (CMMCException);

    /*! \fn ElmoGetParameter(char szCmd[3], char szVal[], int iSize)
    * \brief gets EoE parameter of type string.
    * \param szCmd string command.
    * \param szVal  storage for returned value.
    * \param iSize size of szVal.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoGetParameter(ELMO_INT8 szCmd[3], ELMO_INT8 szVal[], ELMO_INT32 iSize)throw (CMMCException);

    /*! \fn ElmoReadData(char* cBuffer, int iSize)
    * \brief read EoE response from driver and search for ';' suffix
    *        as for asynchronous response.
    * \param cBuffer address of buffer to store response.
    * \param iSize expected response message length.
    * \return   return number of read characters - 0 if none.
    */
    ELMO_INT32 ElmoReadData(ELMO_PINT8 cBuffer, ELMO_INT32 iSize)throw (CMMCException);

    /**! \fn ElmoReadData(int& iValue)
     * \brief read EoE data and set iValue accordingly.
     * \param iValue set with returned value if completed successfully.
     * \return 0 on success otherwise error (<0).
     */
    ELMO_INT32 ElmoReadData(ELMO_INT32& iValue);

    /**! \fn ElmoReadData(float& fValue)
     * \brief read EoE data and set fValue accordingly.
     * \param fValue set with returned value if completed successfully.
     * \return 0 on success otherwise error (<0).
     */
    ELMO_INT32 ElmoReadData(ELMO_FLOAT& fValue);

    /*! \fn ElmoCall(const char szCmd[3])
    * \brief sends EoE command for execution.
    * \param szCmd string command.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoCall(const ELMO_INT8 szCmd[3])throw (CMMCException);

    /*! \fn ElmoCallAsync(const char szCmd[3])
    * \brief sends EoE command for execution.
    * \param szCmd string command.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoCallAsync(const ELMO_INT8 szCmd[3])throw (CMMCException);

    /*! \fn ElmoAck(char* szBuffer, int iSize)
    * \brief checks wether or not a previous EoE command is acknowlaged.
    * \param szBuffer string buffer to store the acknowledgement.
    * \param iSize buffer size - number of bytes to store on success.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoAck(ELMO_PINT8 szBuffer, ELMO_INT32 iSize)throw (CMMCException);

    /*! \fn ElmoExecuteLabel(const char *szCmd)
    * \brief sends EoE command for user program execution.
    * \param szCmd string command.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoExecuteLabelAsync(const ELMO_INT8* szCmd)throw (CMMCException);

    /*! \fn ElmoExecuteLabelAsync(const char *szCmd)
    * \brief sends EoE command for user program execution.
    * \param szCmd string command.
    * \return 0 on success otherwise error (<0).
    */
    ELMO_INT32 ElmoExecuteLabel(const ELMO_INT8* szCmd)throw (CMMCException);

protected:
    /*! \fn GetAck(char* cBuffer, int iSize)
    * \brief read EoE response from and search for ';' suffix as for acknowledge.
    * \param cBuffer address of buffer to store response.
    * \param iSize expected response message length.
    * \return   return number of read characters - 0 if none.
    */
    ELMO_INT32 GetAck(ELMO_PINT8 cBuffer, ELMO_INT32 iSize)throw (CMMCException);

    /**! \fn ParseResult(char *szResult, int& iVal)
     * \brief parses read string and set fVal with accordance.
     * \param szResult read data from UDP socket (EoE)
     * \param iVal set with real value if completed successfully.
     * \return 1 if completed successfully, 0 otherwise.
     */
    ELMO_INT32 ParseResult(ELMO_PINT8 szResult, ELMO_INT32& iVal);

    /**! \fn ParseResult(char *szResult, float& fVal)
     * \brief parses read string and set fVal with accordance.
     * \param szResult read data from UDP socket (EoE)
     * \param fVal set with real value if completed successfully.
     * \return 1 if completed successfully, 0 otherwise.
     */
    ELMO_INT32 ParseResult(ELMO_PINT8 szResult, ELMO_FLOAT & fVal);

    /**! \fn ParseResult(char *szResult, char szRetVal[], int iSize)
     * \brief parses read string and set szRetVal with accordance.
     * \param szResult read data from UDP socket (EoE)
     * \param szRetVal set with string value if completed successfully.
     * \param iSize maximum length allowed for szRetVal.
     * \return 1 if completed successfully, 0 otherwise.
     */
    ELMO_INT32 ParseResult(ELMO_PINT8 szResult, ELMO_INT8 szRetVal[], ELMO_INT32 iSize);

private:
    ELMO_INT32 InitSemSyncDrvIo    (void) throw (CMMCException);
    ELMO_INT32 DestroySemSyncDrvIo (void) throw (CMMCException);
    ELMO_INT32 TakeSemSyncDrvIo    (void) throw (CMMCException);
    ELMO_INT32 ReleaseSemSyncDrvIo (void) throw (CMMCException);

private:
    ELMO_LINT32 _lTimeOut;
    ELMO_INT8 _szBuffer[EoE_BUFFER_SIZE];

#if ((OS_PLATFORM == LINUXIPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC64_PLATFORM))
            /* Sync thread aginst driver for complet set of send /recev. pakget */
    pthread_mutex_t gSemSyncDrvIo;
#endif

};
#endif /* MMCEOE_HPP_ */

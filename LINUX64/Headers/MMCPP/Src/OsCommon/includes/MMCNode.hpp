/*
 * CMMCNode.hpp
 *
 *  Created on: 27/03/2011
 *      Author: yuvall
 *      Update: HH Add func ResetAsync
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 *      Update: Haim H. 16Sep2019 Add library func.
 */
#include "MMCAxis.hpp"

#ifndef CMMCNODE_HPP_
#define CMMCNODE_HPP_


typedef enum {PDO_NUM_3 = 3, PDO_NUM_4 = 4} PDO_NUMBER_ENUM;
typedef enum {PDO_PARAM_REG = 1, PDO_PARAM_USE  = 2 } PDO_PARAM_TYPE_ENUM;

class DLLMMCPP_API CMMCNode : public CMMCAxis {
public:

    /*! \fn default constructor
    */
    CMMCNode();

    /*! \fn copy constructor
     */
    CMMCNode(CMMCNode& axis):CMMCAxis(axis){}

    /*! \fn destructor
    */
    ~CMMCNode();

    virtual void Reset()        throw(CMMCException);
    virtual void ResetAsync()   throw(CMMCException);
    /*! \fn int ReadStatus()
    *   \brief This function gets axis status for specific axis.
    *   \return return - status on success, otherwise throws CMMCException.
    */
    virtual ELMO_ULINT32 ReadStatus() throw (CMMCException);
    virtual ELMO_ULINT32 ReadStatus(ELMO_UINT16 & usAxisErrorID, ELMO_UINT16 & usStatusWord) throw (CMMCException);
    //
    /*! \fn int  MMC_SendSdoCmd(
    * \brief This function send SDO message command.*/
    virtual void SendSdoCmd(ELMO_LINT32 lData,
            ELMO_UINT8   ucService,
            ELMO_UINT8   ucSubIndex,
            ELMO_ULINT32 ulDataLength,
            ELMO_UINT16  usIndex,
            ELMO_UINT16  usSlaveID) throw (CMMCException);

    /*! \fn int  SendSdoDownloadExCmd(
    * \brief This function send download SDO message up to 80 bytes command.*/
    void SendSdoDownloadExCmd(
        SEND_SDO_DATA_EX *uData,        
        ELMO_UINT16 usIndex,
        ELMO_UINT8  ucSubIndex,      
        ELMO_UINT8  ucDataLength) throw (CMMCException);

    /*! \fn int  SendSdoUploadExCmd(
    * \brief This function send upload SDO message up to 80 bytes command.*/
    void SendSdoUploadExCmd(
        SEND_SDO_DATA_EX *uData,
        ELMO_UINT16 usIndex,
        ELMO_UINT8  ucSubIndex,
        ELMO_UINT8  ucDataLength) throw (CMMCException);

    /*! \fn int  SendSdoUploadAsyncExCmd(
    * \brief This function send upload SDO message up to 80 bytes command.*/
    void SendSdoUploadAsyncExCmd(
        SEND_SDO_DATA_EX *uData,
        ELMO_UINT16 usIndex,
        ELMO_UINT8  ucSubIndex,
        ELMO_UINT8  ucDataLength) throw (CMMCException);

    /*! \fn int  RetrieveSdoUploadAsyncExCmd(
    * \brief This function send upload SDO message up to 80 bytes command.*/
    void RetrieveSdoUploadAsyncExCmd(
        SEND_SDO_DATA_EX *uData,
        ELMO_UINT16 usIndex,
        ELMO_UINT8  ucSubIndex,
        ELMO_UINT8  ucDataLength) throw (CMMCException);

    //
    /*! \fn int  unsigned(
    * \brief This function send SDO message command.*/
    virtual void SendSdoDownload(ELMO_LINT32 lData,
            ELMO_UINT8 ucSubIndex,
            ELMO_ULINT32 ulDataLength,
            ELMO_UINT16  usIndex,
            ELMO_UINT16  usSlaveID) throw (CMMCException);


    //
    /*! \fn int  SendSdoUpload(
    * \brief This function send SDO message command.*/
    virtual ELMO_LINT32 SendSdoUpload(ELMO_UINT8 ucSubIndex,
            ELMO_ULINT32 ulDataLength,
            ELMO_UINT16  usIndex,
            ELMO_UINT16  usSlaveID) throw (CMMCException);

    //
    /*! \fn int  SendSdoUpload(
    * \brief This function send SDO message command.*/
    virtual void SendSdoUploadAsync(ELMO_UINT8 ucSubIndex,
            ELMO_ULINT32 ulDataLength,
            ELMO_UINT16  usIndex,
            ELMO_UINT16  usSlaveID) throw (CMMCException);

    //
    /*! \fn int  SendSdoUpload(
    * \brief This function send SDO message command.*/
    virtual void RetreiveSdoUploadAsync(ELMO_LINT32 & lData) throw (CMMCException);

    //
    /*! \fn void PDOGeneralRead()
    *   \brief This function gets General PDO from the axis (this PDO defined by the user).
    *   \return - Return the actual value of the PDO, ulliVal variable inserted by reference.
    */
    virtual MMCPPULL_T PDOGeneralRead(ELMO_UINT8 ucParam) throw(CMMCException);
    //
    //
    /*! \fn void PDOGeneralWrite()
    *   \brief This function sets General PDO from the axis (this PDO defined by the user).
    *   \return - void.
    */
    virtual void PDOGeneralWrite(ELMO_UINT8 ucParam,MMCPPULL_T ulliVal) throw(CMMCException);
    virtual void PDOGeneralWrite(ELMO_UINT8 ucParam,unGeneralPDOWriteData DataUnion) throw(CMMCException);

    //
    /*! \fn void GetPDOInfo()
    *   \brief This function get information about PDO 3\4.
    *   IN uiPDONumber          - PDO number (3\4)
    *   OUT iPDOEventMode       - PDO event mode (NO\CYCLE\IMMEDIATE)
    *   OUT ucPDOCommType       - Communication parameter (SYNC\ASYNC\NO_EVENT)
    *   OUT ucPDOCommEventGroup - PDO Current group (1 .... 17)
    *   \return - void.
    */
    virtual void GetPDOInfo(ELMO_UINT8 uiPDONumber, ELMO_INT32 &iPDOEventMode, ELMO_UINT32 &uiCommParamEventPDO, ELMO_UINT16 &usEventTimerPDO, ELMO_UINT8 &ucRPDOCommType,ELMO_UINT8 &ucTPDOCommType, ELMO_UINT8 &ucTPDOCommEventGroup, ELMO_UINT8 &ucRPDOCommEventGroup, ELMO_UINT8 &ucSubIndexTPDO, ELMO_UINT8 &ucSubindexRPDO) throw(CMMCException);

    virtual void        SetBoolParameter(ELMO_LINT32 lValue, MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    virtual void        SetParameter(ELMO_DOUBLE dbValue, MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    virtual ELMO_LINT32  GetBoolParameter(MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    virtual ELMO_DOUBLE  GetParameter(MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    virtual void        ConfigPDOEventMode(ELMO_UINT8 ucPDOEventMode, PDO_NUMBER_ENUM ePDONum = PDO_NUM_3) throw (CMMCException);
    virtual void        ConfigPDOEventMode(MC_PDO_EVENT_NOTIF_MODE_ENUM ePDOEventMode, PDO_NUMBER_ENUM ePDONum = PDO_NUM_3) throw (CMMCException);


    virtual ELMO_UINT16 GetAxisError(ELMO_PUINT16 usLastEmergencyErrCode) throw (CMMCException);


    virtual void EthercatWriteMemoryRange(ELMO_UINT16 usRegAddr, ELMO_UINT8 ucLength, ELMO_UINT8 pData[ETHERCAT_MEMORY_WRITE_MAX_SIZE]) throw (CMMCException);

    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT8   ucByteLength, ELMO_UINT8 pRawData[PI_REG_VAR_SIZE]) throw (CMMCException);
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT16  usByteLength, ELMO_UINT8 pRawData[PI_LARGE_VAR_SIZE]) throw (CMMCException);
//HH: See remark in cpp 'EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT8   ucData)'
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_BOOL    bData)  throw (CMMCException);
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_INT8    cData)  throw (CMMCException);
//HH: See remark in cpp 'EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT8   ucData)'
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT8   ucData) throw (CMMCException);
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT16  usData) throw (CMMCException);
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_INT16   sData)  throw (CMMCException);
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT32  uiData) throw (CMMCException);
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_INT32   iData)  throw (CMMCException);
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_FLOAT   fData)  throw (CMMCException);
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_DOUBLE  dbData) throw (CMMCException);
    
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT64  ullData)throw (CMMCException);
    virtual void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_INT64   llData) throw (CMMCException);

    virtual void EthercatReadMemoryRange(ELMO_UINT16 usRegAddr,  ELMO_UINT8 ucLength, ELMO_UINT8 pData[ETHERCAT_MEMORY_READ_MAX_SIZE]) throw (CMMCException);

    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT8     ucByteLength, ELMO_UINT8 pRawData[PI_REG_VAR_SIZE]) throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT16    usByteLength, ELMO_UINT8 pRawData[PI_LARGE_VAR_SIZE]) throw (CMMCException);
//HH: See remark in cpp 'EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT8   ucData)'
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_BOOL &    bData)  throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_INT8 &    cData)  throw (CMMCException);
//HH: See remark in cpp 'EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT8   ucData)'
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT8 &   ucData) throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT16 &  usData) throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_INT16 &   sData)  throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT32 &  uiData) throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_INT32 &   iData)  throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_FLOAT &   fData)  throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_DOUBLE &  dbData) throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT64 &  ullData)throw (CMMCException);
    virtual void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_INT64  &  llData) throw (CMMCException);
    
    virtual void EthercatPIVarInfo(ELMO_UINT16 usPIVarIndex, ELMO_UINT8 ucDirection, NC_PI_ENTRY &VarInfo) throw (CMMCException);

};

#endif /* CMMCNODE_HPP_ */

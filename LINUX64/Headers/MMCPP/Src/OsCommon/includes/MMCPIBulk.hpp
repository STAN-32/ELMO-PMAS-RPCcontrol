/*
 * MMCPIBulk.hpp
 *
 *  Created on: Mar 9, 2014
 *      Author: ZivB
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */

#ifndef MMCPIBULK_HPP_
#define MMCPIBULK_HPP_

#include "MMC_definitions.h"
#include "MMCPPGlobal.hpp"
#include "MMCPIVar.hpp"


class CMMCPIVar;

class DLLMMCPP_API CMMCPIBulk {

    friend class CMMCPIVar;

public:

    /*! \fn default constructor
    */
    CMMCPIBulk();

    /*! \fn constructor()
    *   \brief constructor that connection handle and size of array.
    */
    CMMCPIBulk(MMC_CONNECT_HNDL ConnHndl, ELMO_INT32 iSize, NC_BULKREAD_CONFIG_PI_ENUM  eConfiguration, CMMCPIVar *PIVARArr = NULL) throw (CMMCException);

    /*! \fn destructor
    */
    virtual ~CMMCPIBulk();

    /*! \fn Init()
    *   \brief set inital value for class
    */
    void Init(MMC_CONNECT_HNDL ConnHndl, ELMO_INT32 iSize, NC_BULKREAD_CONFIG_PI_ENUM  eConfiguration, CMMCPIVar *PIVARArr = NULL) throw (CMMCException);

    /*! \fn Append()
    *   \Add new CMMCCPIVar to the array of PIVAR
    */
    void Append(CMMCPIVar &PIVar) throw (CMMCException);

    /*! \fn Clear()
    *   \Clear the instance of the PIBULKREAD
    */
    void Clear() throw (CMMCException);

    /*! \fn Config()
    *   \Perform config bulk read according to the setting
    */
    void Config() throw (CMMCException);

    /*! \fn Upload()
    *   \Perform upload of the data
    */
    void Upload() throw (CMMCException);


private:

    /*! \fn Copy()
    *   \Perform copy of the requested data
    */
    void Copy(ELMO_INT32 index, ELMO_BOOL   &bValue);

    void Copy(ELMO_INT32 index, ELMO_INT8   &cValue);

    void Copy(ELMO_INT32 index, ELMO_UINT8  &ucValue);

    void Copy(ELMO_INT32 index, ELMO_INT16  &sValue);

    void Copy(ELMO_INT32 index, ELMO_UINT16 &usValue);

    void Copy(ELMO_INT32 index, ELMO_INT32  &iValue);

    void Copy(ELMO_INT32 index, ELMO_UINT32 &uiValue);

    void Copy(ELMO_INT32 index, ELMO_FLOAT  &fValue);

    void Copy(ELMO_INT32 index, ELMO_INT64  &ullValue);

    void Copy(ELMO_INT32 index, ELMO_UINT64 &ullValue);

    void Copy(ELMO_INT32 index, ELMO_DOUBLE &dValue);


    MMC_CONNECT_HNDL                m_uiConnHndl;
    MMC_CONFIGBULKREADPI_IN         m_ConfigBulkReadPIInParam;
    NC_BULKREAD_CONFIG_PI_ENUM      m_eConfiguration;
    MMC_PERFORMBULKREADPI_OUT       m_pOut_performBulkread;
    ELMO_INT32                       m_iIndexInDataBuffer;
    ELMO_INT32                       m_iIndexInInputBuffer;
    ELMO_INT32                       m_iIsBulkReadInitializedFlag;
};


#endif /* MMCPIBULK_HPP_ */

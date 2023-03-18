/*
 * MMCPIVar.hpp
 *
 *  Created on: Mar 3, 2014
 *      Author: ZivB
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 *      Update: Haim H. 11Sep2017
 */

#ifndef MMCPIVAR_HPP_
#define MMCPIVAR_HPP_

#include "MMC_definitions.h"
#include "MMCPPGlobal.hpp"
#include "MMCPIBulk.hpp"

typedef void (*CopyBool)(ELMO_INT32 index, ELMO_BOOL &bValue);

class CMMCPIBulk;

// bit operations macros
#define PI_BITS_TO_BYTES(uiBitSize)                     (((uiBitSize - 1) >> 3) + 1)
#define PI_BYTE_NUM_WITH_OFF(uiBitSize,ucBitStart)      (((uiBitSize + ucBitStart - 1) >> 3) + 1)
#define PI_MOD8_ASSIGN(x)                                x &= 0x07
#define PI_MOD8(x)                                      (x) & 0x07
#define PI_ALIGNMENT_CHECK(x)                           (x) & PI_ALIGNMENT_BYTES

class DLLMMCPP_API CMMCPIVar {

    friend class CMMCPIBulk; //new 9.3.14

public:

    /*! \fn default constructor
    */
    CMMCPIVar():m_uiConnHndl(0),m_usAxisRef(-1),m_ePIDirection(ePI_NONE),m_usPIVarOffset(0),m_ucVarType(0),m_uiBitOffset(0),m_uiBitSize(0),m_ucByteLength(0),m_pBulkRelated(NULL),
    m_iIsPIVARRelatedToBulkFlag(0)
    {

    }

    /*! \fn constructor()
    *   \brief constructor that receive PI VAR offset and direction.
    */
    CMMCPIVar(MMC_CONNECT_HNDL uHandle, MMC_AXIS_REF_HNDL hAxisRef, ELMO_UINT16 usPIVarOffset, PI_DIRECTIONS eDirection ) throw (CMMCException);

    /*! \fn constructor()
    *   \brief constructor that receive PI VAR alias.
    */
    CMMCPIVar(MMC_CONNECT_HNDL uHandle, MMC_AXIS_REF_HNDL hAxisRef, ELMO_INT8 alias[PI_ALIASING_LENGTH]) throw (CMMCException);

    /*! \fn destructor
    */
    virtual ~CMMCPIVar();

    /*! \fn Init()
    *   \brief set inital value for class variable according to offset.
    */
    virtual void Init(MMC_CONNECT_HNDL uHandle, MMC_AXIS_REF_HNDL hAxisRef, ELMO_UINT16 usPIVarOffset, PI_DIRECTIONS eDirection ) throw (CMMCException);

    /*! \fn Init()
    *   \brief set inital value for class variable according to alias.
    */
    virtual void Init(MMC_CONNECT_HNDL uHandle, MMC_AXIS_REF_HNDL hAxisRef, ELMO_INT8 alias[PI_ALIASING_LENGTH]) throw (CMMCException);

    /*! \fn UnbindFromBulkRead()
    *   \brief remove the option of reading from bulkRead.
    */
    void UnbindFromBulkRead();

    /*! \fn IsBindtoBulkRead()
    *   \brief return 1 if bind to bulk read or 0 if it is not bind to bulk read.
    */
    ELMO_INT32 IsBoundToBulkRead();

    /*! \WritePI(bool bValue)
    *   \write the input argument value to PI var.
    */
    virtual void WritePI(ELMO_BOOL bValue) throw (CMMCException);

	virtual void WritePI(ELMO_INT8 cValue) throw (CMMCException);

	virtual void WritePI(ELMO_UINT8 ucValue) throw (CMMCException);

	virtual void WritePI(ELMO_UINT16 usValue) throw (CMMCException);

	virtual void WritePI(ELMO_INT16 sValue) throw (CMMCException);

	virtual void WritePI(ELMO_UINT32 uiValue) throw (CMMCException);

	virtual void WritePI(ELMO_INT32 iValue) throw (CMMCException);

	virtual void WritePI(ELMO_FLOAT fValue) throw (CMMCException);

	virtual void WritePI(ELMO_PUINT8 ucValue, ELMO_INT32 iSize) throw (CMMCException);





    void WritePI(ELMO_UINT64 ullValue) throw (CMMCException);

    void WritePI(ELMO_INT64  llValue) throw (CMMCException);

    void WritePI(ELMO_DOUBLE dValue) throw (CMMCException);


    /*! \ReadPI(bool &bValue)
    *   \Read the value of PI variable.
    *   \The value will return in the bValue
    */
	virtual void ReadPI(ELMO_BOOL &bValue) throw (CMMCException);

	virtual void ReadPI(ELMO_INT8 &cValue) throw (CMMCException);

	virtual void ReadPI(ELMO_UINT8 &ucValue) throw (CMMCException);

	virtual void ReadPI(ELMO_INT16 &sValue) throw (CMMCException);

	virtual void ReadPI(ELMO_UINT16 &usValue) throw (CMMCException);

	virtual void ReadPI(ELMO_INT32 &iValue) throw (CMMCException);

	virtual void ReadPI(ELMO_UINT32 &uiValue) throw (CMMCException);

	virtual void ReadPI(ELMO_FLOAT &fValue) throw (CMMCException);

	virtual void ReadPI(ELMO_PUINT8 ucValue, ELMO_INT32 iSize) throw (CMMCException);



    virtual void ReadPI(ELMO_INT64  &llValue) throw (CMMCException);

    virtual void ReadPI(ELMO_UINT64 &ullValue) throw (CMMCException);

	virtual void ReadPI(ELMO_DOUBLE &dValue) throw (CMMCException);

    /*! \fn GetPIVarInfoByAlias()
    *   \brief gets the PI info according to the PI alaia.
    *   \char alias : the name of the PI
    *   \MMC_GETPIVARINFOBYALIAS_OUT &pOutParam - retrive the info data of the PI
    */
    void GetPIVarInfoByAlias(ELMO_INT8 alias[PI_ALIASING_LENGTH],MMC_GETPIVARINFOBYALIAS_OUT &pOutParam) throw (CMMCException);

    /*! \fn GetPIVarsRangeInfo()
    *   \brief gets the PI info of range of PI.
    *   \param MMC_GETPIVARSRANGEINFO_IN  pInParam
    *   \param  MMC_GETPIVARSRANGEINFO_OUT &pOutParam - retrive the info data of the PI
    */
    void GetPIVarsRangeInfo(MMC_GETPIVARSRANGEINFO_IN  pInParam,MMC_GETPIVARSRANGEINFO_OUT &pOutParam) throw (CMMCException);

protected:

    MMC_CONNECT_HNDL        m_uiConnHndl;
    MMC_AXIS_REF_HNDL       m_usAxisRef;
    PI_DIRECTIONS           m_ePIDirection;
    ELMO_UINT16             m_usPIVarOffset;
    ELMO_UINT8              m_ucVarType;
    ELMO_UINT32             m_uiBitOffset;
    ELMO_UINT32             m_uiBitSize;
    ELMO_UINT8              m_ucByteLength;

   	ELMO_UINT32 			m_uiIsMandatory;
	ELMO_UINT32 			m_uiPIMemSize;

    //BulkRead related parameters
    ELMO_INT32              m_iIndexInDataBuffer;
    CMMCPIBulk              *m_pBulkRelated;
    ELMO_INT32              m_iIsPIVARRelatedToBulkFlag;
   	ELMO_UINT8	 			m_ucBitStart;

    //CopyBool              m_pfCopyBool ;
};
#endif /* MMCPIVAR_HPP_ */

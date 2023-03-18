/*
 * MMCRTSingleAxis.hpp
 *
 *  Created on: Mar 31, 2016
 *      Author: ZivB
 */

#ifndef MMCRTSINGLEAXIS_HPP_
#define MMCRTSINGLEAXIS_HPP_

//#ifndef WIN32
#include "MMC_definitions.h"
#include "MMCAxis.hpp"
#include "MMCNode.hpp"
#include "MMCMotionAxis.hpp"
#include "MMCPPGlobal.hpp"
#include "MMCSingleAxis.hpp"

							/* HH 15Sep2020, CLBK_HANDLER change to CLBK_HANDLER02 because 	*/
							/* CLBK_HANDLER already define in csrt_sm.h						*/
typedef void (*CLBK_HANDLER02)(ELMO_INT32 iAxisIndex, ELMO_UINT16 usAxisRef);

typedef struct api_comn
{
    ELMO_UINT32 uiAxisID;
    ELMO_UINT32 uiAPIComn;
    ELMO_UINT32 uiApiReq;      //Bitwise indicating which command to execute
    ELMO_UINT32 uiInternalState;
    ELMO_UINT32 uiEnable;
    ELMO_UINT32 uiIsInSequence;
    CLBK_HANDLER02 pFunc;
    ELMO_DOUBLE data[50];

}API_COMN;

					/* HH, 15Sep2020 INTERNAL_STATE_ENUM Define also in csrt_sm.h...	*/
#ifndef INTERNAL_STATE_ENUM_ALREADY_DEF
#define INTERNAL_STATE_ENUM_ALREADY_DEF
typedef enum _INTERNAL_STATE_ENUM
{
    INTERNAL_STATE_WAIT_FOR_RISING      = 0,
    INTERNAL_STATE_ACITVATIE            = 1,
    INTERNAL_STATE_STATUS_POOL          = 2,
    INTERNAL_STATE_WAIT_FOR_FALLING     = 3,
    INTERNAL_STATE_VALUE_POOL           = 4,

} INTERNAL_STATE_ENUM;
#endif

class DLLMMCPP_API CMMCRTSingleAxis : public CMMCSingleAxis
{
public:
    virtual ~CMMCRTSingleAxis();

    CMMCRTSingleAxis();
    CMMCRTSingleAxis(CMMCSingleAxis& axis);

    void InitAxisData(const ELMO_INT8* cName, MMC_CONNECT_HNDL uHandle) throw (CMMCException);
    void SetUser607A(ELMO_INT32  iUser607Aval)  throw (CMMCException);
    void SetUser60FF(ELMO_INT32  iUser60FFval)  throw (CMMCException);
    void SetUser60B1(ELMO_INT32  iUser60B1val)  throw (CMMCException);
    void SetUser60B2(ELMO_DOUBLE iUser60B2val)  throw (CMMCException);
    void SetUser6071(ELMO_DOUBLE dUser6071val)  throw (CMMCException);
    void SetUserMB1 (ELMO_INT32      iUserMB1)  throw (CMMCException);
    void SetUserMB2 (ELMO_INT32      iUserMB2)  throw (CMMCException);
    void SetUserCW  (ELMO_UINT16  usUserCWval)  throw (CMMCException);


    ELMO_INT32      GetUser607A()       throw (CMMCException);
    ELMO_INT32      GetUser60FF()       throw (CMMCException);
    ELMO_INT32      GetUser60B1()       throw (CMMCException);
    ELMO_DOUBLE     GetUser60B2()       throw (CMMCException);
    ELMO_DOUBLE     GetUser6071()       throw (CMMCException);
    ELMO_INT32      GetUserMB1()        throw (CMMCException);
    ELMO_INT32      GetUserMB2()        throw (CMMCException);
    ELMO_DOUBLE     GetActualPosition() throw (CMMCException);
    ELMO_DOUBLE     GetActualVelocity() throw (CMMCException);
    ELMO_DOUBLE     GetdPos()           throw (CMMCException);
    ELMO_DOUBLE     GetdVel()           throw (CMMCException);
    ELMO_INT16      GetAnalogInput()    throw (CMMCException);
    ELMO_UINT32     GetDigitalInputs()  throw (CMMCException);
    void            SetDigitalOutPuts(ELMO_UINT32 uiDigitalOutputs) throw (CMMCException);
    ELMO_DOUBLE     GetActualCurrent()  throw (CMMCException);
    ELMO_UINT32     GetPLCOpenStatus()  throw (CMMCException);
    ELMO_UINT16     GetControlWord()    throw (CMMCException);
    ELMO_UINT16     GetStatusWord()     throw (CMMCException);
    ELMO_ULINT32    GetCycleCounter()   throw (CMMCException);

    int GetUserCW() throw (CMMCException);

    ELMO_INT32  GetActualPositionINT() throw (CMMCException);
    ELMO_INT32  GetActualVelocityINT() throw (CMMCException);
    ELMO_UINT32 GetStatusRegister()    throw (CMMCException);
    ELMO_DOUBLE GetdTorqueUU()         throw (CMMCException);
    void        SetUI(ELMO_INT32 iValue, ELMO_UINT32 iIndex) throw (CMMCException);
    ELMO_INT32  GetUI(ELMO_UINT32 iIndex) throw (CMMCException);
    void        SetUF(ELMO_FLOAT fValue, ELMO_UINT32 iIndex) throw (CMMCException);
    float       GetUF(ELMO_UINT32 iIndex) throw (CMMCException);


    API_COMN        m_stAPICom;
    ELMO_ULINT32    m_ulApiReq;

    void sm_activation(ELMO_INT32 iAxisIndex);


protected:

    ELMO_PUINT8  m_pShmPtr;
    ELMO_ULINT32 m_ulnode_list_param_base;
    ELMO_ULINT32 m_ulGlobalParam_base;

    ELMO_ULINT32 m_uldPosOffset;
    ELMO_ULINT32 m_ulUser607AOffset;
    ELMO_ULINT32 m_ulUser60FFOffset;
    ELMO_ULINT32 m_ulUser60B1Offset;
    ELMO_ULINT32 m_ulUser6071Offset;
    ELMO_ULINT32 m_ulUser60B2Offset;
    ELMO_ULINT32 m_ulMB1Offset;
    ELMO_ULINT32 m_ulMB2Offset;
    ELMO_ULINT32 m_ulTargetVelOffset;
    ELMO_ULINT32 m_ulActualPosOffset;
    ELMO_ULINT32 m_ulActualVelUUOffset;
    ELMO_ULINT32 m_ulAnsalogInputOffset;
    ELMO_ULINT32 m_uiDigitalInputsOffset;
    ELMO_ULINT32 m_ulActualCurrentOffset;
    ELMO_ULINT32 m_ulStatusOffset;
    ELMO_ULINT32 m_ulControlWordOffset;
    ELMO_ULINT32 m_ulStatusWordOffset;
    ELMO_ULINT32 m_ulUserCWOffset;

    ELMO_ULINT32 m_CycleCounterOffset;

    ELMO_DOUBLE  m_dbTorquemAToRCRatio;
    ELMO_FLOAT   m_fMotorRatedCurrent;
    ELMO_ULINT32 m_ulCycleTime;

    ELMO_ULINT32 m_ulActualPosINTOffset;
    ELMO_ULINT32 m_ulActualVelINTOffset;
    ELMO_ULINT32 m_ulStatusRegisterOffset;

    ELMO_ULINT32 m_ulTargetTorqueUUOffset;

    ELMO_ULINT32 m_ulUserParamIntOffset[8];
    ELMO_ULINT32 m_ulUserParamFloatOffset[8];

    ELMO_ULINT32 m_uiDigitalOutputOffset;
};

	#ifndef SHORTPARAMETER_MREF
		#define SHORTPARAMETER(base, offset) *((ELMO_PINT16  )((ELMO_PUINT8)base + offset))
		#define SHORTPARAMETER_MREF
	#endif
		
	#ifndef USHORTPARAMETER_MREF
		#define USHORTPARAMETER(base,offset) *((ELMO_PUINT16 )((ELMO_PUINT8)base + offset))
		#define USHORTPARAMETER_MREF
	#endif
	
	#ifndef INTPARAMETER_MREF
		#define INTPARAMETER(base,   offset) *((ELMO_PINT32  )((ELMO_PUINT8)base + offset))
		#define INTPARAMETER_MREF
	#endif
	
	#ifndef UINTPARAMETER_MREF
		#define UINTPARAMETER(base,  offset) *((ELMO_PUINT32 )((ELMO_PUINT8)base + offset))
		#define UINTPARAMETER_MREF
	#endif
	
	#ifndef LONGPARAMETER_MREF
		#define LONGPARAMETER(base,  offset) *((ELMO_PLINT32 )((ELMO_PUINT8)base + offset))
		#define LONGPARAMETER_MREF
	#endif
	
	#ifndef ULONGPARAMETER_MREF
		#define ULONGPARAMETER(base, offset) *((ELMO_PULINT32)((ELMO_PUINT8)base + offset))
		#define ULONGPARAMETER_MREF
	#endif
	
	#ifndef FLOATPARAMETER_MREF
		#define FLOATPARAMETER(base, offset) *((ELMO_PFLOAT  )((ELMO_PUINT8)base + offset))
		#define FLOATPARAMETER_MREF
	#endif
	
	#ifndef DOUBLEPARAMETER_MREF
		#define DOUBLEPARAMETER(base,offset) *((ELMO_PDOUBLE )((ELMO_PUINT8)base + offset))
		#define DOUBLEPARAMETER_MREF
	#endif

#define UI_UF_MAX_IDX 8
//DATA OFFSET INXDEX API_COMN
#define POWER_ENBL_IDX  30
#define DONE_IDX        30

#define MOTION_BUFF_MOD_IDX     0
#define MOTION_LPOS_IDX         1
#define MOTION_DPOS_IDX         2
#define MOTION_VEL_IDX          3
#define MOTION_AC_IDX           4
#define MOTION_JERK_IDX         5

#define OPMOD_REQ_IDX           15

#define NC_SIL_HOME_REQ                     0x00000020  ///< SIL HOME Bit Mask.
#define NC_SIL_RESET_REQ                    0x00000010  ///< SIL RESET Bit Mask.
#define NC_SIL_CHG_MOD_REQ                  0x00000008  ///< SIL Change operation mode Bit Mask.
#define NC_SIL_MOVE_REQ                     0x00000004  ///< SIL MOVE Bit Mask.
#define NC_SIL_POWER_ON_REQ                 0x00000002  ///< SIL power ON Bit Mask.
#define NC_SIL_POWER_OFF_REQ                0x00000001  ///< SIL power OFF Bit Mask.

//#endif //WIN32
#endif /* MMCRTSINGLEAXIS_HPP_ */

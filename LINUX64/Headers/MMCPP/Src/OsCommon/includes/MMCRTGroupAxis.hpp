/*
 * MMCRTGroupAxis.hpp
 *
 *  Created on: 07/07/2016
 *      Author: zivb
 */

#ifndef MMCRTGROUPAXIS_H_
#define MMCRTGROUPAXIS_H_

#include "MMC_definitions.h"
#include "MMCAxis.hpp"
#include "MMCNode.hpp"
#include "MMCMotionAxis.hpp"
#include "MMCPPGlobal.hpp"
#include "MMCGroupAxis.hpp"

class DLLMMCPP_API CMMCRTGroupAxis:public CMMCGroupAxis
{
public:
    virtual ~CMMCRTGroupAxis();

    CMMCRTGroupAxis();
    CMMCRTGroupAxis(CMMCGroupAxis& axis);

    void InitAxisData(const ELMO_PINT8 cName, MMC_CONNECT_HNDL uHandle) throw (CMMCException);

    void GetPos(ELMO_PDOUBLE dArr, NC_AXIS_IN_GROUP_TYPE_ENUM_EX startIndex, NC_AXIS_IN_GROUP_TYPE_ENUM_EX endIndex)throw (CMMCException);
    void GetVel(ELMO_PDOUBLE dArr, NC_AXIS_IN_GROUP_TYPE_ENUM_EX startIndex, NC_AXIS_IN_GROUP_TYPE_ENUM_EX endIndex)throw (CMMCException);
    
    void GetACDC(ELMO_PDOUBLE dArr, NC_AXIS_IN_GROUP_TYPE_ENUM_EX startIndex, NC_AXIS_IN_GROUP_TYPE_ENUM_EX endIndex)throw (CMMCException);
    ELMO_UINT32 GetPLCOpenStatus() throw (CMMCException);
    void GetVectorVel(ELMO_PDOUBLE dValue)throw (CMMCException);

protected:
    ELMO_PUINT8     m_pShmPtr;
    ELMO_ULINT32    m_ulnode_list_param_base;
    ELMO_ULINT32    m_ulGlobalParam_base;

    ELMO_ULINT32    m_ulaPosOffset;
    ELMO_ULINT32    m_ulaVelOffset;
    
    ELMO_ULINT32    m_ulStatusOffset;
    ELMO_ULINT32    m_ulVecVelocityOffset;
    ELMO_ULINT32    m_ulACDCOffset;
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

#endif /* MMCRTGROUPAXIS_H_ */

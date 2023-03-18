/*
 * MMCPIVarRT.h
 *
 *  Created on: 18/04/2017
 *      Author: zivb
 *      Update: Haim H. 19Sep2019 Changes for support Multi type of OS.
 */

#ifndef MMCPIVARRT_HPP_
#define MMCPIVARRT_HPP_

//#ifndef WIN32
#if (OS_PLATFORM == LINUXIPC32_PLATFORM)

    #include "MMC_definitions.h"
    
    #include "MMCAxis.hpp"
    #include "MMCNode.hpp"
    #include "MMCMotionAxis.hpp"
    #include "MMCPPGlobal.hpp"
    #include "MMCPIVar.hpp"
    
    
    
    class DLLMMCPP_API CMMCPIVarRT : public CMMCPIVar
    {
    
    public:
        virtual ~CMMCPIVarRT();
    
        CMMCPIVarRT();
        CMMCPIVarRT(CMMCPIVar& PIVar);
    
        /*! \fn Init()
        *   \brief set inital value for class variable according to offset.
        */
        virtual void Init(MMC_CONNECT_HNDL uHandle, MMC_AXIS_REF_HNDL hAxisRef, ELMO_UINT16 usPIVarOffset, PI_DIRECTIONS eDirection ) throw (CMMCException);
    
        virtual void ReadPI(ELMO_BOOL& bValue) throw (CMMCException);
    
        virtual void ReadPI(ELMO_SINT8& cValue) throw (CMMCException);
    
        virtual void ReadPI(ELMO_UINT8& ucValue) throw (CMMCException);
    
        virtual void ReadPI(ELMO_INT16& sValue) throw (CMMCException);
    
        virtual void ReadPI(ELMO_UINT16& usValue) throw (CMMCException);
    
        virtual void ReadPI(ELMO_INT32& iValue) throw (CMMCException);
    
        virtual void ReadPI(ELMO_UINT32& uiValue) throw (CMMCException);
    
        virtual void ReadPI(ELMO_FLOAT& fValue) throw (CMMCException);
    
        virtual void ReadPI(ELMO_DOUBLE& fValue) throw (CMMCException);
    
    
        virtual void WritePI(ELMO_BOOL bValue) throw (CMMCException);
    
        virtual void WritePI(ELMO_INT8 cValue) throw (CMMCException);
    
        virtual void WritePI(ELMO_UINT8 ucValue) throw (CMMCException);
    
        virtual void WritePI(ELMO_UINT16 usValue) throw (CMMCException);
    
        virtual void WritePI(ELMO_INT16 sValue) throw (CMMCException);
    
        virtual void WritePI(ELMO_UINT32 uiValue) throw (CMMCException);
    
        virtual void WritePI(ELMO_INT32 iValue) throw (CMMCException);
    
        virtual void WritePI(float fValue) throw (CMMCException);
    
        virtual void WritePI(double dValue) throw (CMMCException);
    
        ELMO_INT32 GetPIDirecton()  {return m_ePIDirection;}
        ELMO_INT32 GetNumOfPIIn()   {return m_uiNumberOfPIIn;}
        ELMO_INT32 GetNumOfPIOut()  {return m_uiNumberOfPIOut;}
    
    
    
    protected:
    
        ELMO_PUINT8  m_pShmPtr;
        ELMO_PUINT8  m_pShmPITable;
        ELMO_ULINT32 m_ulnode_list_param_base;
        ELMO_ULINT32 m_ulPIMemOffset;
    
        ELMO_ULINT32 m_ulbasePtr;
    
        ELMO_UINT32  m_uiNumberOfPIIn;
        ELMO_UINT32  m_uiNumberOfPIOut;
    };
    
    #define BOOLPARAMETER(base,  offset) *((ELMO_BOOL   *)((ELMO_PUINT8)base + offset))
    #define CHARPARAMETER(base,  offset) *((ELMO_PSINT8  )((ELMO_PUINT8)base + offset))
    #define UCHARPARAMETER(base, offset) *((ELMO_PUINT8  )((ELMO_PUINT8)base + offset))
	
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


#endif

#endif /* #ifndef MMCPIVARRT_HPP_ */


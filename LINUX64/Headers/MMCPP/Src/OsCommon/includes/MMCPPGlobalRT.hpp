/*
 * MMCPPGlobalRT.h
 *
 *  Created on: 23/04/2017
 *      Author: zivb
 *      Update: Haim H. 19Sep2019 Changes for support Multi type of OS.
 */

#ifndef MMCPPGLOBALRT_HPP_
#define MMCPPGLOBALRT_HPP_

//#ifndef WIN32
#if   (OS_PLATFORM == LINUXIPC32_PLATFORM)


    #include "MMC_definitions.h"
    
    #include "MMCAxis.hpp"
    #include "MMCNode.hpp"
    #include "MMCMotionAxis.hpp"
    #include "MMCPPGlobal.hpp"
    #include "MMCSingleAxis.hpp"
    
    #define SIL_DATA_REC_SIZE       32
    #define SIL_TIME_CAP_SIZE       5
    
    class DLLMMCPP_API MMCPPGlobalRT
    {
    public:
        virtual ~MMCPPGlobalRT();
    
        MMCPPGlobalRT();
    
        void Init(MMC_CONNECT_HNDL uHandle);
    
        ELMO_DOUBLE GetCpldAdcCh1() throw (CMMCException);
        ELMO_DOUBLE GetCpldAdcCh2() throw (CMMCException);
        ELMO_DOUBLE GetCpldAdcCh3() throw (CMMCException);
        ELMO_DOUBLE GetCpldAdcCh4() throw (CMMCException);
    
        void SetCpldAdcOUTCh1(ELMO_DOUBLE lVal) throw (CMMCException);
        void SetCpldAdcOUTCh2(ELMO_DOUBLE lVal) throw (CMMCException);
        void SetCpldAdcOUTCh3(ELMO_DOUBLE lVal) throw (CMMCException);
        void SetCpldAdcOUTCh4(ELMO_DOUBLE lVal) throw (CMMCException);
    
        ELMO_ULINT32 GetCpldExtendedIOIn1() throw (CMMCException);
        void SetCpldExtendedIOOut1(ELMO_ULINT32 ulVal) throw (CMMCException);
        void SetCpldExtendedIOOut2(ELMO_ULINT32 ulVal) throw (CMMCException);
        void SetCpldExtendedIOOut3(ELMO_ULINT32 ulVal) throw (CMMCException);
    
        void SetSILLongData(ELMO_INT32 iIndex, ELMO_LINT32 lVal) throw (CMMCException);
        void SetSILDoubleData(ELMO_INT32 iIndex, ELMO_DOUBLE dVal) throw (CMMCException);
    
    
        ELMO_ULINT32 GetCycleCounter() throw (CMMCException);
    
        void GetInputCapture(ELMO_UINT16 usIndex, ELMO_PUINT32 uiEventCounter, ELMO_PUINT32 uiCaptureTime) throw (CMMCException);

		ELMO_DOUBLE GetCpldQuad1PosUU() throw (CMMCException);
		ELMO_DOUBLE GetCpldQuad2PosUU() throw (CMMCException);
		ELMO_DOUBLE GetCpldQuad1Vel() throw (CMMCException);
		ELMO_DOUBLE GetCpldQuad2Vel() throw (CMMCException);

		ELMO_DOUBLE GetCpldAbs1PosUU() throw (CMMCException);
		ELMO_DOUBLE GetCpldAbs2PosUU() throw (CMMCException);
		ELMO_DOUBLE GetCpldAbs1Vel() throw (CMMCException);
		ELMO_DOUBLE GetCpldAbs2Vel() throw (CMMCException);
    
        ELMO_ULINT32 GetSILBAEver ();
    
    protected:
    
        ELMO_PUINT8  m_pShmPtr;
        ELMO_ULINT32 m_ulGlobalParam_base;
    
        MMC_CONNECT_HNDL m_uiConnHndl;                  /*!< communication session handler; */
    
    
        ELMO_ULINT32 m_ulCycleCounterOffset;
    
        ELMO_ULINT32 m_ulCPLDAnanlogCHA1Offset;
        ELMO_ULINT32 m_ulCPLDAnanlogCHA2Offset;
        ELMO_ULINT32 m_ulCPLDAnanlogCHB1Offset;
        ELMO_ULINT32 m_ulCPLDAnanlogCHB2Offset;
    
        ELMO_ULINT32 m_ulCPLDAnanlogOutCH1Offset;
        ELMO_ULINT32 m_ulCPLDAnanlogOutCH2Offset;
        ELMO_ULINT32 m_ulCPLDAnanlogOutCH3Offset;
        ELMO_ULINT32 m_ulCPLDAnanlogOutCH4Offset;
    
        ELMO_ULINT32 m_ulCPLDExtendedIOIn1ffset;
        ELMO_ULINT32 m_ulCPLDExtendedIOout1ffset;
        ELMO_ULINT32 m_ulCPLDExtendedIOout2ffset;
        ELMO_ULINT32 m_ulCPLDExtendedIOout3ffset;
        ELMO_ULINT32 m_ulSIL_DATA_LONG_offset[SIL_DATA_REC_SIZE];
        ELMO_ULINT32 m_ulSIL_DATA_DOUBLE_offset[SIL_DATA_REC_SIZE];
    
        ELMO_ULINT32 m_ulCPLDExtendedITimeCapLatchTimeOffset[SIL_TIME_CAP_SIZE];
        ELMO_ULINT32 m_ulCPLDExtendedITimeCapEvtCntOffset[SIL_TIME_CAP_SIZE];

		ELMO_ULINT32 m_ulCPLDEncoderQuad1PosUUOffset;
		ELMO_ULINT32 m_ulCPLDEncoderQuad2PosUUOffset;
		ELMO_ULINT32 m_ulCPLDEncoderQuad1VelOffset;
		ELMO_ULINT32 m_ulCPLDEncoderQuad2VelOffset;
		ELMO_ULINT32 m_ulCPLDEncoderAbs1PosUUOffset;
		ELMO_ULINT32 m_ulCPLDEncoderAbs2PosUUOffset;
		ELMO_ULINT32 m_ulCPLDEncoderAbs1VelOffset;
		ELMO_ULINT32 m_ulCPLDEncoderAbs2VelOffset;

        ELMO_ULINT32 m_ulSILBASEver;
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

#endif

#endif /* MMCPPGLOBALRT_H_ */

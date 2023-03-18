/*
 * MMCCodesysShm.h
 *
 *  Created on: 18/12/2017
 *      Author: zivb
 *
 *  Update: Haim H. 18Sep2019 Changes for support Multi type of OS.
 *
 */

#ifndef MMCCodesysShM_HPP_
#define MMCCodesysShM_HPP_


//#ifndef WIN32
#if (OS_PLATFORM == LINUXIPC32_PLATFORM)


    #include "MMCPPGlobal.hpp"
    #include "MMC_definitions.h"


    class DLLMMCPP_API CMMCCodesysShm
    {
    public:
    
        /*! \fn default constructor
        */
        CMMCCodesysShm();
    
        /*! \fn destructor
        */
        virtual ~CMMCCodesysShm();
    
        void shmStart(const ELMO_INT8 ShmName[100], ELMO_DOUBLE dSize) throw (CMMCException);
        void ShmStop() throw (CMMCException);
    
        template<class TYPE>
        void ShmWrite(TYPE& pData) throw (CMMCException)
        {
            if(m_ShmPtr == NULL)
            {
                CMMCPPGlobal::Instance()->MMCPPThrow("ShmWrite fail : shm not started", 0, 0, 0, MMC_LIB_CODESYS_SHM_NOT_STARTED, 0);
            }
            memcpy(m_ShmPtr, (ELMO_PVOID)&pData, m_dSize);
            return;
        }
    
        template<class TYPE>
        void shmRead(TYPE& pData) throw (CMMCException)
        {
            if (m_ShmPtr == NULL)
            {
                CMMCPPGlobal::Instance()->MMCPPThrow("shmRead fail : shm not started", 0, 0, 0, MMC_LIB_CODESYS_SHM_NOT_STARTED, 0);
            }
            memcpy((ELMO_PVOID)&pData, m_ShmPtr, m_dSize);
            return;
        }
    
    private:
        ELMO_DOUBLE m_dSize;
        ELMO_INT8   m_strShmName[100];
        ELMO_PVOID  m_ShmPtr;
    };

#endif  /* #if (OS_PLATFORM == LINUXIPC32_PLATFORM) */


#endif /* #ifndef MMCCodesysShM_HPP_ */


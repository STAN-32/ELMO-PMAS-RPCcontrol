/*
 * CMMCAxis.hpp
 *
 *  Created on: 10/03/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 */

#ifndef CMMCAXIS_HPP_
#define CMMCAXIS_HPP_

#include "MMCPPGlobal.hpp"

//using namespace std;

#define MAX_RETRIES 1000


class DLLMMCPP_API CMMCAxis {
public:
    /*! \fn default constructor
    *   \brief This function retrieves axis name.
    */
    CMMCAxis():
        m_uiConnHndl(0),
        m_usAxisRef(-1)
        {}

    CMMCAxis(CMMCAxis&  axis);
    /*! \fn destructor
    *   \brief This function retrieves axis name.
    */
    virtual ~CMMCAxis(){}

    /*! \fn char* GetName()
    *   \brief This function retrieves axis name.
    */
    const ELMO_INT8*  GetName() const {return m_strName;}
    /*! \fn MMC_CONNECT_HNDL GetConnHndl()
    *   \brief This function retrieves conneciton handler.
    */
    MMC_CONNECT_HNDL GetConnHndl() const {return m_uiConnHndl;}

    /*! \fn unsigned short GetRef()
    *   \brief This function retrieves axis reference .
    */
    ELMO_UINT16 GetRef() const {return m_usAxisRef;}

    /*! \fn void InitAxisData(const char* cName, MMC_CONNECT_HNDL uHandle)
    *   \brief This function initiates axis name and retrieves a session handler.
    */
    virtual void InitAxisData(const ELMO_INT8* cName, MMC_CONNECT_HNDL uHandle) throw (CMMCException)
    {
        SetName(cName);
        SetConnHndl(uHandle);
        GetAxisByName(cName);
    }

    /*! \fn int GetAxisByName(const char* cName)
     * \brief This function return axis index reference by his name.
     * \param  cName name of the axis.
     * \return  return - 0 on success, otherwise throws CMMCException.
     */
    ELMO_INT32 GetAxisByName(const ELMO_INT8* cName) throw (CMMCException);


    /*! \fn unsigned int SetDefaultManufacturerParameters()
    * \brief This function restore the axis\group parameters
    * \param
    * \return
    */

    void SetDefaultManufacturerParameters() throw (CMMCException);

    /*! \fn unsigned int GetStatusRegister()
    * \brief This function returns the motion status word
    * \return   return - 0 on success, otherwise throws CMMCException.
    */
    virtual ELMO_UINT32 GetStatusRegister() throw (CMMCException)
    {
        CMMCPPGlobal::Instance()->MMCPPThrow("MMC_GetStatusRegister:", m_uiConnHndl, m_usAxisRef, -1, NC_WRONG_NODE_TYPE, 0);
        return 0;
    }


    ELMO_UINT32 GetSystemCounter() throw (CMMCException);


protected:
    /*! \fn void SetName()
    *   \brief This function sets axis name.
    */
    void SetName(const ELMO_INT8* cName);
    /*! \fn void SetConnHndl()
    *   \brief This function sets axis's connection handler.
    */
    void SetConnHndl(MMC_CONNECT_HNDL uiConnHndl){m_uiConnHndl=uiConnHndl;}
    /*! \fn void SetRef()
    *   \brief This function sets axis ref.
    */
    void SetRef(ELMO_UINT16 usAxisRef){m_usAxisRef = usAxisRef;}
protected:
    //
    ELMO_INT8 m_strName[128];                       /*!< axis name.                     */
    MMC_CONNECT_HNDL m_uiConnHndl;                  /*!< communication session handler; */
    ELMO_UINT16 m_usAxisRef;                        /*!< set by GetAxisByName           */
};

#endif /* CMMCAXIS_HPP_ */

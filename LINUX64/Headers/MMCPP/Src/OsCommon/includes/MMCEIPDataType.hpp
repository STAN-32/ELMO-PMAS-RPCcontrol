/*
 * CMMCEIPDataType.h
 *
 *  Created on: 05/06/2012
 *      Author: yuvall
 *      Update: Haim H. 18Sep2019 Changes for support Multi type of OS.
 */

#ifndef CMMCEIPTAGDATATYPE_HPP_
#define CMMCEIPTAGDATATYPE_HPP_

#include "EIP_API.h"
#include "platform.h"
#include "EtIpApi.h"

using namespace std;

#ifdef __MSVC__
    #define FORCEDINLINE __forceinline
#else
    #define FORCEDINLINE __attribute__((always_inline))
#endif

typedef enum {EIPP_RESPONSE_OK=0, EIPP_RESPONSE_WAIT} EIPP_DEVWAIT_STAUS_ENUM;
typedef enum {eADAPTOR_TAG=0, eDEVICE_TAG, eASSEMBLY_TAG} EIPP_TAGTYPE_ENUM;

typedef struct
{
     ELMO_LINT32 dummy;         ///< dummy as 32bit alignment to all structure members
     ELMO_UINT16 usTagRef;      ///< Tag  Reference.
     ELMO_PINT8  buffer;        ///< Buffer that holds returned data.
}EIPP_WRITEADPTAG_IN;

typedef EIPP_WRITEADPTAG_IN EIPP_SETASSEMBLY_IN;

typedef struct
{
     ELMO_LINT32 dummy;         ///< dummy as 32bit alignment to all structure members
     ELMO_UINT16 usStatus;      ///< Returned command status.
     ELMO_INT16  usErrorID;     ///< Returned command error ID.
     ELMO_PINT8  buffer;        ///< Buffer that holds returned data.
}EIPP_READDEVTAG_OUT;

typedef EIPP_READDEVTAG_OUT EIPP_GETSYNC_OUT;
typedef EIPP_READDEVTAG_OUT EIPP_READADPTAG_OUT;
typedef EIPP_WRITEADPTAG_IN EIPP_SETDEVTAG_IN;
typedef EIPP_READDEVTAG_OUT EIPP_GETASSEMBLY_OUT;

template <class T>
class DataType
{
public:
    DataType() {};
    virtual ~DataType(){};
};

template <class T=ELMO_INT32>

class CMMCEIPDataType : protected DataType <T> {
//class DLLMMCPP_API CMMCEIPDataType {

public:
    /*!
     * \brief default constructor
     */
    CMMCEIPDataType():_iDevWaitStatus(EIPP_RESPONSE_OK) { _iGDVCounter = 0;}
    /*!
     * \brief copy constructor
     */
    CMMCEIPDataType(const CMMCEIPDataType<T>& tag);

    /*!
     * \brief default destructor
     */
    ~CMMCEIPDataType(){}//;

    /*! \fn int EipTagInit(const char *szTagName)
    *   \brief fetch tag setting by name and initializes this object with tag properties.
    *   \param szName tag name for initialization.
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipTagInit(const ELMO_INT8* szName);

    /*! \fn int EipTagInit(int iIntance)
    *   \brief fetch tag setting by instance and initializes this object with tag properties.
    *   \param iInstance tag instance for initialization (basically for assemblies).
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipTagInit(ELMO_INT32 iInstance);


    /*! \fn int EipSetTag(T tData[])
    *   \brief writes data to adapter memory
    *   \param tData data to be written into referenced adapter tag
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipSetTag(T tData[]);

    /*! \fn int EipSetTag(T tag)
    *   \brief writes data to adapter memory
    *   \param tData data to be written into referenced adapter tag
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipSetTag(T tData);

    /*! \fn int EipReadAdpTag(T tData[], bool bSync=false)
    *   \brief reads data from adapter memory into given tData buffer
    *   \param tData to retrieve data of referenced adapter tag
    *   \param bSync synchronous flag. default false (EipGetDevTag), otherwise use EipSyncGetDevTag
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipGetTag(T tData[], ELMO_BOOL bSync=false);

    /*! \fn int EipReadAdpTag(T tag, bool bSync=false)
    *   \brief reads data from adapter memory into given tData buffer
    *   \param tVar to retrieve tag data of referenced adapter tag
    *   \param bSync synchronous flag. default false (EipGetDevTag), otherwise use EipSyncGetDevTag
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipGetTag(T& tVar, ELMO_BOOL bSync=false);

    /*! \fn int EipCheckReply()
    *   \brief answers whether or not data for last request has arrived.
    *   \param sStatus response status (see EIPP_REQUEST_STAUS_ENUM).
    *   \return true if data is ready, otherwise false.
    */
    ELMO_INT32 EipCheckReply(ELMO_INT16& sStatus);
    FORCEDINLINE ELMO_BOOL EipIsWaiting() {return _iDevWaitStatus;}//1 is waiting
    /*! \fn int EipGetData(T tData[])
    *   \brief get data, which has arrived asynchronously from some request.
    *   \return true if data has fetched, otherwise false.
    */
    ELMO_INT32 EipGetData(T tData[]);
    /*! \fn int EipGetData(T& tag)
    *   \brief get data, which has arrived asynchronously from some request.
    *   \return true if data has fetched, otherwise false.
    */
    ELMO_INT32 EipGetData(T& tVar);

protected:

    /*! \fn int EipWriteAdpTag(EIPDatBuffer_T, unsigned short& usStatus)
    *   \brief writes data to adapter memory
    *   \param tData data to be written into referenced adapter tag
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipWriteAdpTag(T tData[]);

    /*! \fn int EipReadAdpTag(unsigned short usTagRef, T tData[], unsigned short& usStatus)
    *   \brief reads data from adapter memory into given tData buffer
    *   \param tData to retrieve data of referenced adapter tag
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipReadAdpTag(T tData[]);

    /*! \fn int EipSetAssembly(unsigned short usInstance, T tData[], unsigned short& usStatus)
    *   \brief  retrieves assembly data from GMAS and sends it through EthernetIP
    *   \param [out] tData data to be written into referenced instance.  relevant only on success.
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipSetAssembly(T tData[]);

    /*! \fn int EipGetAssembly(unsigned short usInstance, T tData[], unsigned short& usStatus)
    *   \brief  sets assembly data identified by instance in to tData
    *   \param [in] usInstance index to assemblies array.
    *   \param [out] tData data to be written into referenced instance.  relevant only on success.
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipGetAssembly(T tData[]);

    /*!\fn int EipSetDevTag(unsigned short usTagRef, T tData[], int& iReqid, unsigned short& usStatus)
     * \brief updates device tag data and sends it to EIP device
     * \param [in] tData data to update and send.
     * \return  0 on success, error id otherwise.
     */
    ELMO_INT32 EipSetDevTag(T tData[]);

    /*!\fn int EipReadDevTagData(unsigned short usTagRef, T tData[], unsigned short& usStatus)
     * \brief reads and stores device tag data that has been received by
     *  EIP device, as a response to user request.
     * \param [out] tData tag data.
     * \return  0 on success, error id otherwise.
     */
    ELMO_INT32 EipReadDevTagData(T tData[]);

    /*!\fn int EipGetDevTag(unsigned short usTagRef, int& iReqid, unsigned short& usStatus)
     * \brief sends request to EIP device in order to read specific device tag
     * \return  0 on success, error id otherwise.
     */
    ELMO_INT32 EipGetDevTag(T tData[]);

    /*! \fn int EipSyncGetDevTag(T tData[])
    *   \brief sends request to read device tag data, waits till response received  then reads the response data into tData buffer.
    *   \param tData reference to retrieved data.
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipSyncGetDevTag(T tData[]);

private:
    /*! \fn int EipGetDevTagRefByName(const char * strName, unsigned short& usTagRef, unsigned short& usStatus)
    *   \brief retrieves device tag index by given name. all methods shall use this index to access the device tag object in memory.
    *   \param usTagRef index to device tag array.
    *   \param strName tag name as for search key, null terminated string.
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipGetDevTagRefByName(const ELMO_INT8*  szName, ELMO_UINT16& usTagRef);

    /*! \fn int EipGetAdpTagRefByName(const char * strName, unsigned short& usTagRef, unsigned short& usStatus)
    *   \brief retrieves adapter tag index by given name. all methods shall use this index to access the tag object in memory.
    *   \param usTagRef index to adapter tag array.
    *   \param strName tag name as for search key
    *   \return 0 on success, error id otherwise.
    */
    ELMO_INT32 EipGetAdpTagRefByName(const ELMO_INT8* strName, ELMO_UINT16& usTagRef);

    /*! \fn int EipGetAssemblyRefByName(const char* szName, unsigned short& usTagRef, unsigned short&usStatus)
    *   \brief finds assembly instance by given name
    *   \param [IN] szName null terminated string..
    *   \param [OUT] usTagRef an index of given instance to assemblies storage (an array)
    *   \return 0 on success, otherwise error id.
    */
    ELMO_INT32 EipGetAssemblyRefByName(const ELMO_INT8* szName, ELMO_UINT16& usTagRef);


    /*! \fn int EipGetAssemblyRefByInstance(int iInstance, unsigned short& usTagRef, unsigned short&usStatus)
    *   \brief finds assembly instance and applies a reference (index) to that instance
    *   \param [IN] iInstance to adapter tag array.
    *   \param [OUT] usTagRef an index of given instance to assemblies storage (an array)
    *   \return 0 on success, otherwise error id.
    */
    ELMO_INT32 EipGetAssemblyRefByInstance(ELMO_INT32 iInstance, ELMO_UINT16& usTagRef);
public:
    ELMO_INT32 _iGDVCounter;

private:
    typedef ELMO_INT32 (CMMCEIPDataType<T>::*PDataExchange)(T tData[]);

    PDataExchange _pfSet;       ///< points to accurate Set method (according tag type)
    PDataExchange _pfGet;       ///< points to accurate Get method (according tag type)
    ELMO_UINT16 _usTagRef;      ///< index to array, which stores tag in EIP data model
    ELMO_UINT16 _usDim;         ///< dimension of _ucType
    ELMO_INT32  _iRequestID;            ///< EIP request id for asynchronous messages
    ELMO_UINT8  _ucType;        ///< tag variable type (SINT, INT, DINT or REAL.
    ELMO_INT8   _szName[NAME_MAX_LENGTH+1]; ///< tag name
    ELMO_INT32  _iDevWaitStatus;
    EIPP_TAGTYPE_ENUM _eTagType; ///< tag type (adaptor, device or assembly
};


#endif /* #ifndef CMMCEIPTAGDATATYPE_HPP_ */


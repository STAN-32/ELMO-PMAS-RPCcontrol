/*
 * CMMCMotionAxis.hpp
 *
 *  Created on: 20/05/2012
 *      Author: Alex
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 *              0.4.0 Updated 11Sep2017 Haim H.
 *              Haim H. 16Sep2019
 */

#ifndef CMMCMOTIONAXIS_HPP_
#define CMMCMOTIONAXIS_HPP_

#include "MMC_definitions.h"
#include "MMCNode.hpp"
#include "MMCPPGlobal.hpp"

class DLLMMCPP_API CMMCMotionAxis : public CMMCNode
{
public:
    /*! \fn default constructor
     */
    CMMCMotionAxis();

    CMMCMotionAxis(MMC_CONNECT_HNDL uiConnHndl);
    /*! \fn copy constructor
     */
    CMMCMotionAxis(CMMCMotionAxis& axis):CMMCNode(axis){}

    /*! \fn destructor
     */
    virtual ~CMMCMotionAxis();

public:


    /*! \fn unsigned int GetFbDepth(const unsigned int uiHndl)
    * \brief This function sends a command for receive number of function blocks in Node Queue .
    * \param  uiHndl handler of which to Get F.B. Depth output parameters
    * \return   return - number of function blocks on success, otherwise throws CMMCException.
    */
    ELMO_UINT32 GetFbDepth() throw (CMMCException);


    /*! \fn unsigned int EnableMotionEndedEvent()
    * \brief This function Enable the event of ended motion
    * \param
    * \return
    */
    void EnableMotionEndedEvent() throw (CMMCException);


    /*! \fn unsigned int DisableMotionEndedEvent()
    * \brief This function Disable the event of ended motion
    * \param
    * \return
    */
    void DisableMotionEndedEvent() throw (CMMCException);


    /*! \fn unsigned int GetStatusRegister()
    * \brief This function Insert a dwell fb to the FB queue of the axis
    * \return   return - 0 on success, otherwise throws CMMCException.
    */
    void Dwell(ELMO_ULINT32 ulDwellTimeMs) throw (CMMCException);

    /*! \fn unsigned int InsertNotificationFb()
    * \brief This function Insert a notification FB that will generate event when called
    * \return   return - 0 on success, otherwise throws CMMCException.
    */
    void InsertNotificationFb(ELMO_INT32 iEventCode) throw (CMMCException);
    void InsertNotificationFb(MMC_INSNOTIFICATIONFB_IN stInParams) throw (CMMCException);

    /*! \fn void WaitUntilConditionFB()
    * \brief This function Insert a condition fb to the queue of the node
    * \return   in case of error throws CMMCException.
    */
    void WaitUntilConditionFB(MMC_WAITUNTILCONDITIONFB_IN stInput) throw (CMMCException);

    void WaitUntilConditionFBEX(MMC_WAITUNTILCONDITIONFBEX_IN stInput) throw (CMMCException);

    /*! \fn void KillRepetitive()
    * \brief This function stop the repetitive motion after current FB
    * \return   in case of error throws CMMCException.
    */
    void KillRepetitive() throw (CMMCException);

    /*! \fn MC_PATH_REF InitPVTTable()
     * \brief This function loads PVT table from file
     * \param ulMaxPoints - Maximum points for one table
     * \param ulUnderflowThreshold - Upon reaching this threshold, an event will be generated
     * \param ucIsCyclic - Is the table cyclic
     * \param ucIsDynamic - Is dynamic append allowed
     * \param ucIsPosAbsolute - Are the position units absolute
     * \return void
    */
    virtual MC_PATH_REF InitPVTTable(ELMO_ULINT32 ulMaxPoints,
                           ELMO_ULINT32  ulUnderflowThreshold,
                           ELMO_UINT8    ucIsCyclic,
                           ELMO_UINT8    ucIsPosAbsolute,
                           ELMO_UINT16   usDimension,
                           MC_COORD_SYSTEM_ENUM eCoordSystem,
                           NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_ARRAY) throw (CMMCException);

    /*! \fn MC_PATH_REF InitPTTable()
     * \brief This function allocates and init PT (online spline) table on GMAS
     * \param ulMaxPoints - Maximum points for one table
     * \param ulUnderflowThreshold - Upon reaching this threshold, an event will be generated
     * \param ucIsCyclic - Is the table cyclic
     * \param ucIsDynamic - Is dynamic append allowed
     * \param ucIsPosAbsolute - Are the position units absolute
     * \param eSplineMode   - defines the way spline if calculated (FT/VT/CV_DWELL)
     * \parma ConstVelocity - constant velocity is forced on all segments
     * \parma FixedType - constant time (ms) is forced on all segments
     * \return void
    */
    virtual MC_PATH_REF InitPTTable(ELMO_ULINT32 ulMaxPoints,
                           ELMO_ULINT32 ulUnderflowThreshold,
                           ELMO_UINT8   ucIsCyclic,
                           ELMO_UINT8   ucIsDynamic,
                           ELMO_UINT8   ucIsPosAbsolute,
                           ELMO_UINT16  usDimension,
                           MC_COORD_SYSTEM_ENUM eCoordSystem,
                           NC_ONLINE_SPLINE_MODE_ENUM eSplineMode = MC_QUINTIC_ON_PARAB_VT_DWELL,
                           ELMO_DOUBLE ConstVelocity = 1000.0,
                           ELMO_DOUBLE FixedTime = 2.0) throw (CMMCException);



    /*! \fn void LoadPVTTable()
     * \brief This function loads PVT table from file
     * \param char* pFileName - File Name
     * \return void
     */
    virtual MC_PATH_REF LoadPVTTableFromFile(ELMO_PINT8 pFileName,
            MC_COORD_SYSTEM_ENUM eCoordSystem,
            NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_FILE) throw (CMMCException);

    /*! \fn void LoadPTTable()
    * \brief This function loads PT (online spline) table from file
    * \param char* pFileName - File Name
    * \param eCoordSystem coordinate system (ACS/MCS/PCS or NONE)
    * \return   - handler (>=0) of loaded table if loaded successfully otherwise 
                throws an exception or returns an error (<0).
    */
    virtual MC_PATH_REF LoadPTTableFromFile(ELMO_PINT8 pFileName,
            MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);

    MC_PATH_REF CamTableInit(ELMO_ULINT32 ulMaxPoints,
                                    ELMO_UINT16 usDimension,
                                    ELMO_UINT8 ucIsFixedGap=0,
                                    CURVE_TYPE_ENUM eCurveType=ePolynom5Interp) throw (CMMCException);

    MC_PATH_REF CamTableSelect(const MC_CamRef& CamTableDescr,
                    ELMO_UINT8 ucIsMasterPosAbsolute,
                    ELMO_UINT8 ucIsSlavePosAbsolute,
                    ELMO_UINT32 uiStartMode = 0) throw (CMMCException);

    ELMO_INT32 CamTableAdd(MC_PATH_REF hMemHandle, ELMO_PDOUBLE dbTable, ELMO_UINT16 usColumns, ELMO_ULINT32 ulNumberOfPoints) throw (CMMCException);

    ELMO_INT32 CamTableAddEx(MC_PATH_REF hMemHandle, ELMO_PDOUBLE dbTable, ELMO_UINT16 usColumns, ELMO_ULINT32 ulNumberOfPoints);

    ELMO_INT32 CamTableSet(MC_PATH_REF hMemHandle, ELMO_PDOUBLE dbTable, ELMO_UINT16 usColumns, ELMO_ULINT32 ulStartIndex, ELMO_ULINT32 ulNumberOfPoints) throw (CMMCException);
//#ifdef _DEBUG
//    ELMO_INT32 CamTablePrint(MC_PATH_REF hMemHandle, ELMO_ULINT32 ulStartIndex, ELMO_ULINT32 ulNumberOfPoints) throw (CMMCException);
//#endif  
    /**
    * \fn   int CamGetStatus(unsigned long ulEndOfProfile,
                    unsigned long ulCurrentIndex,
                    unsigned long ulCycle,
                    unsigned short usStatus,
                    short sErrorID) throw (CMMCException)
    * \brief    retrieve status of MC_CamIn FB on this axis and other parameters as given on this list
    * \param    ulEndOfProfile counts number of exists from cam table.
    * \param    ulCurrentIndex returned segment (index) in CAM table, wich is currently proccessed.
    * \param    ulCycle     returned process cycle  of CamIn on this axis
    * \param    usStatus    returned FB status
    * \param    sErrorID    returned with error number if error
    * \return   0 if completed successfully, otherwise error or thrown exception.
    */
    ELMO_INT32 CamGetStatus(ELMO_ULINT32 & ulEndOfProfile, //counts number of exists from cam table
                     ELMO_ULINT32 & ulCurrentIndex,
                     ELMO_ULINT32 & ulCycle,
                     ELMO_UINT16  & usStatus,
                     ELMO_INT16   & sErrorID)  throw (CMMCException);

    /**
    * \fn   int CamGetStatus(unsigned long ulEndOfProfile,
                    unsigned long ulCurrentIndex,
                    unsigned long ulCycle,
                    unsigned short usStatus,
                    short sErrorID) throw (CMMCException)
    * \brief    retrieve status of MC_CamIn FB on this axis and other parameters as given on this list
    * \param    ulEndOfProfile counts number of exists from cam table.
    * \param    ulCurrentIndex returned segment (index) in CAM table, wich is currently proccessed.
    * \param    ulCycle     returned process cycle  of CamIn on this axis
    * \param    usStatus    returned FB status
    * \param    sErrorID    returned with error number if error
    * \param    uiCamTableID return table handler if FB is active.
    * \return   0 if completed successfully, otherwise error or thrown exception.
    */
    int CamGetStatus(ELMO_ULINT32& ulEndOfProfile,
                     ELMO_ULINT32& ulCurrentIndex,
                     ELMO_ULINT32& ulCycle,
                     ELMO_UINT16 & usStatus,
                     ELMO_INT16  & sErrorID, ELMO_UINT32& uiCamTableID) throw (CMMCException);

    int CamSetProperty(ECAM_PROPERTIES_ENUM eProperty, ECAM_PERIODIC_ENUM ePeriodicMode) throw (CMMCException);

    ELMO_INT32 CamIn(
        ELMO_UINT16 usMaster,
        MC_BUFFERED_MODE_ENUM eBufferMode,
        ELMO_UINT32 uiCamTableID,
        CURVE_TYPE_ENUM eCurveType,
        ELMO_UINT32 ucAutoOffset = 0,
        ECAM_PERIODIC_ENUM ePeriodic=eCAM_NON_PERIODIC,
        ELMO_DOUBLE dbMasterSyncPosition=0.0,    //relative to first row in CAM table
        ELMO_DOUBLE dbMasterStartDistance = 0,   //for now, until we have Ram-In implemented.
        ELMO_UINT32 uiStartMode = 0,
        ELMO_DOUBLE dbMasterOffset = 0,
        ELMO_DOUBLE dbSlaveOffset = 0,
        ELMO_DOUBLE dbMasterScaling = 1,
        ELMO_DOUBLE dbSlaveScaling = 1,
        ECAM_VALUE_SRC_ENUM eMasterValueSource = eECAM_SET_VALUE) throw (CMMCException);
    
    ELMO_INT32 CamOut() throw (CMMCException);
    /*! \fn void MovePVT()
     * \brief This function moves along the PVT table
     * \param eCoordSystem - Coordinate system - not relevant in case of single axis
     * \return void
     */
    virtual void MovePVT(MC_PATH_REF hMemHandle, MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);

    /*! \fn void MovePT()
     * \brief This function moves along the PT table (online spline)
     * \param hMemHandle - table access handler (index to journal on GMAS)
     * \param eCoordSystem - Coordinate system - not relevant in case of single axis
     * \return 0 if completed successfully, otherwise error
     */
    virtual ELMO_INT32 MovePT(MC_PATH_REF hMemHandle, MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);

    /*! \fn void UnloadPVTTable()
     * \brief This function unloads PVT table
     * \return void
     */
    void UnloadPVTTable(MC_PATH_REF hMemHandle) throw (CMMCException);
    void CamTableUnload(MC_PATH_REF hMemHandle) throw (CMMCException) { UnloadPVTTable(hMemHandle);} 
    void UnloadCamTable(MC_PATH_REF hMemHandle) throw (CMMCException) { UnloadPVTTable(hMemHandle);}  //same as CamTableUnload but compatible to PT/PVT naming convension.
    void UnloadPTTable (MC_PATH_REF hMemHandle) throw (CMMCException) {UnloadPVTTable(hMemHandle);}


    /*! \fn void AppendPointsToTableCmn
     * \brief This function appends points to an existing table
     * \param CMMCAxis* - Pointer to axis
     * \param cName - Axis name
     * \param hConn - Connection handle
     * \return void
     */
    void AppendPVTPoints(MC_PATH_REF hMemHandle,
                                ELMO_DOUBLE (&dTable)[NC_PVT_ECAM_MAX_ARRAY_SIZE],
                                ELMO_ULINT32 ulNumberOfPoints,
                                ELMO_UINT8 ucIsTimeAbsolute = 0,
                                NC_MOTION_TABLE_TYPE_ENUM eTableType = eNC_TABLE_PVT_ARRAY) throw (CMMCException);

    /*! \fn void AppendPTPoints()
     * \brief This function appends points to an existing table
     * \param hMemHandle - table handler
     * \param dTable - and array contains ulNumberOfPoints points (rows)
     * \param ulNumberOfPoints - numbe of points to append (set) to (in) table on GMAS.
     * \param ucAutoAppend - flag for automatic append. if true, GMAS ignores ulStartIndex
                             and appends all points to the end of existing table.
     * \param ulStartIndex - table segment on GMAS from which to start the append process.
     * \param ucIsTimeAbsolute - tells GMAS whether the time column is absolute or relative (absolute or relative to previous row).
     *                           if absolute the its relative to FB activation time.
     * \return void
     */
    void AppendPTPoints(MC_PATH_REF  hMemHandle,
                        ELMO_DOUBLE  dTable[NC_PVT_ECAM_MAX_ARRAY_SIZE],
                        ELMO_ULINT32 ulNumberOfPoints,
                        ELMO_UINT8   ucAutoAppend,
                        ELMO_ULINT32 ulStartIndex,
                        ELMO_UINT8   ucIsTimeAbsolute = 0) throw (CMMCException);


        /*! \fn void AppendPointsToTableCmn
     * \brief This function appends points to an existing table
     * \param CMMCAxis* - Pointer to axis
     * \param cName - Axis name
     * \param hConn - Connection handle
     * \return void
     */
    void AppendPVTPoints(MC_PATH_REF hMemHandle,
                                ELMO_DOUBLE (&dTable)[NC_PVT_ECAM_MAX_ARRAY_SIZE],
                                ELMO_ULINT32 ulNumberOfPoints,
                                ELMO_ULINT32 ulStartIndex,
                                ELMO_UINT8 ucIsTimeAbsolute = 0,
                                NC_MOTION_TABLE_TYPE_ENUM eTableType = eNC_TABLE_PVT_ARRAY) throw (CMMCException);


    ELMO_UINT32 GetPVTTableIndex(MC_PATH_REF hMemHandle)  throw (CMMCException);
    ELMO_UINT32 GetPTTableIndex(MC_PATH_REF hMemHandle)  throw (CMMCException)
    {
        return GetPVTTableIndex(hMemHandle);
    }

    /**
    * \fn int int GetTableList(NC_MOTION_TABLE_TYPE_ENUM eTableType, unsigned int (&uiHandlers)[MMC_MAX_JOURNAL_ENTRIES]);
    * \brief this function get a list of table for given table type.
    * \param  eTableType - type of tables to retrieve.
    * \param  uiHandlers - buffer of table handlers to retriev by eTableType.
    * \param  iNum - stores number of loaded tables of eTableType on successfull return.
    * \return   return - 0 if success otherwise error or thrown CMMCException.
    */
    ELMO_INT32 GetTableList(NC_MOTION_TABLE_TYPE_ENUM eTableType, ELMO_UINT32 (&uiHandlers)[MMC_MAX_JOURNAL_ENTRIES], ELMO_INT32 & iNum) throw (CMMCException);

    /**
    * \fn int GetTableInfo(unsigned int uiHandler, char (&name)[MMC_TABLE_FILE_LENGTH+1]) throw (CMMCException);
    * \brief this method gets the table name (by table handler).
    * \param  uiHandler - table's uiHandler to retrieve its name.
    * \param  name - name of given table by uiHandler.
    * \return   return - 0 if success otherwise error or thrown CMMCException.
    */
    ELMO_INT32 GetTableInfo(ELMO_UINT32 uiHandler, ELMO_INT8 (&name)[MMC_TABLE_FILE_LENGTH+1]) throw (CMMCException);


    void ReadGroupOfParameters(MMC_READGROUPOFPARAMETERSMEMBER sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE], ELMO_UINT8 ucNumberOfParameters, ELMO_PDOUBLE dbOutVal);
    void WriteGroupOfParametersImmediate(MMC_WRITEGROUPOFPARAMETERSMEMBER sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE], ELMO_UINT8 ucNumberOfParameters);
    void WriteGroupOfParametersQueued(MMC_WRITEGROUPOFPARAMETERSMEMBER sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE], ELMO_UINT8 ucNumberOfParameters);

    void WriteGroupOfParametersImmediateEX(MMC_WRITEGROUPOFPARAMETERSMEMBEREX sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE],ELMO_UINT8 ucNumberOfParameters);
    void WriteGroupOfParametersQueuedEX(MMC_WRITEGROUPOFPARAMETERSMEMBEREX sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE],ELMO_UINT8 ucNumberOfParameters);

    /**
    * \fn int KillMotion(MC_PATH_REF hMemHandle)  throw (CMMCException);
    * \brief this method stop profiler moiton on the spot.
    * \return   return - 0 if success otherwise error or thrown CMMCException.
    */
    ELMO_INT32 KillMotion()  throw (CMMCException);


private:

        /*! \fn void AppendPointsToTableCmn
     * \brief This function appends points to an existing table
     * \param CMMCAxis* - Pointer to axis
     * \param cName - Axis name
     * \param hConn - Connection handle
     * \return void
     */
    void AppendPVTPoints(MC_PATH_REF hMemHandle,
                                ELMO_DOUBLE  (&dTable)[NC_PVT_ECAM_MAX_ARRAY_SIZE],
                                ELMO_ULINT32 ulNumberOfPoints,
                                ELMO_ULINT32 ulStartIndex,
                                ELMO_UINT8   ucIsAutoAppend,
                                ELMO_UINT8   ucIsTimeAbsolute,
                                NC_MOTION_TABLE_TYPE_ENUM eTableType = eNC_TABLE_PVT_ARRAY) throw (CMMCException);

    void WriteGroupOfParameters(MC_EXECUTION_MODE eExecutionMode,MMC_WRITEGROUPOFPARAMETERSMEMBER sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE], ELMO_UINT8 ucNumberOfParameters);
    void WriteGroupOfParametersEX(MC_EXECUTION_MODE eExecutionMode,MMC_WRITEGROUPOFPARAMETERSMEMBEREX sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE], ELMO_UINT8 ucNumberOfParameters);
};

#endif /// CMMCMOTIONAXIS_HPP_

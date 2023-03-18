// MMCSingleAxis.hpp: interface for the CMMCSingleAxis class.
//
//  Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
//                0.4.0 Updated 11Sep2017 Haim H.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMCSINGLEAXIS_HPP__3E1F67CF_C8B1_40B8_BB29_090EF2A76691__INCLUDED_)
#define      AFX_MMCSINGLEAXIS_HPP__3E1F67CF_C8B1_40B8_BB29_090EF2A76691__INCLUDED_

#if ((OS_PLATFORM == WIN32_PLATFORM) || (OS_PLATFORM == WIN64_PLATFORM))
    #ifndef PROAUT_CHANGES
        #pragma warning( disable : 4290 )
    #endif
#endif

#include "MMC_definitions.h"
#include "MMCAxis.hpp"
#include "MMCNode.hpp"
#include "MMCMotionAxis.hpp"
#include "MMCPPGlobal.hpp"



class DLLMMCPP_API MMC_MOTIONPARAMS_SINGLE
{
public:
    MMC_MOTIONPARAMS_SINGLE();
    //
    ELMO_DOUBLE      dbPosition ;
    ELMO_DOUBLE      dbDistance ;
    ELMO_FLOAT       fEndVelocity ;
    ELMO_FLOAT       fVelocity ;
    ELMO_FLOAT       fAcceleration ;
    ELMO_FLOAT       fDeceleration ;
    ELMO_FLOAT       fJerk ;
    MC_DIRECTION_ENUM       eDirection ;
    MC_BUFFERED_MODE_ENUM   eBufferMode ;
    ELMO_UINT32      uiExecDelayMs;
    ELMO_UINT8       ucExecute ;
    //
};

class DLLMMCPP_API CMMCSingleAxis : public CMMCMotionAxis
{
public:
    virtual ~CMMCSingleAxis();

    CMMCSingleAxis();
    CMMCSingleAxis(const MMC_MOTIONPARAMS_SINGLE& stParams)
    {
        SetDefaultParams(stParams);
    }

    /*! \fn CMMCSingleAxis(CMMCSingleAxis& mmcAxis)
    *   \brief copy constructor.
    *   \param mmcAxis source reference for which data is copied.
    */
    CMMCSingleAxis(CMMCSingleAxis& mmcAxis);

    ELMO_DOUBLE          m_dbTorqueVelocity;
    ELMO_DOUBLE          m_dbTorqueAcceleration;
    ELMO_FLOAT           m_fVelocity ;
    ELMO_FLOAT           m_fAcceleration ;
    ELMO_FLOAT           m_fDeceleration ;
    ELMO_FLOAT           m_fJerk ;
    ELMO_UINT8           m_ucExecute ;
    MC_DIRECTION_ENUM    m_eDirection ;
    ELMO_UINT32          m_uiExecDelayMs;
    //homing
    ELMO_DOUBLE          m_dbHomePosition;
    ELMO_FLOAT           m_fHomeAcceleration;
    ELMO_FLOAT           m_fHomeVelocity;
    ELMO_FLOAT           m_fHomeDistanceLimit;
    ELMO_FLOAT           m_fHomeTorqueLimit;
    MMC_HOME_MODE_ENUM  m_eHomingMode;
    MC_BUFFERED_MODE_ENUM   m_eHomeBufferMode;
    MC_HOME_DIRECTION_ENUM  m_eHomeDirection;
    MC_SWITCH_MODE_ENUM m_eHomeSwitchMode;
    ELMO_UINT32          m_uiHomeTimeLimit;
    ELMO_UINT32          m_uiHomingMethod;
    ELMO_UINT8           m_ucHomeExecute;    

    ELMO_DOUBLE          m_dbDetectionVelocityLimit; //HomingDS402Ex
    ELMO_UINT32          m_uiDetectionTimeLimit;     //HomingDS402Ex
    ELMO_FLOAT           m_fHomeVelocityLo;          //HomingDS402Ex: Speed during search for zero

    void SetDefaultHomeDS402Params(const MMC_HOMEDS402_IN& stSingleParams);
    void SetDefaultHomeDS402ExParams(const MMC_HOMEDS402EX_IN& stSingleParams);

    /*! \fn int SetDefaultParams MMC_MOTIONPARAMS_SINGLE& stSingleAxisParams)
    *   \brief This function initiates default parameters for motion for specific axis.
    *   \param stSingleAxisParams structure of motion parameters for single axis.
    *   \return return - 0 if success. error_id in case of error.
    */
    void SetDefaultParams(const MMC_MOTIONPARAMS_SINGLE& stSingleAxisParams);

    ELMO_INT32 MoveVelocity(ELMO_FLOAT fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

    /*! \fn int MoveAbsolute(double dPos,.....) 
    *   \brief This function send Move Absolute command to MMC server for specific Axis.
    *   \param dPos target position to move.
    *   \param motion parameters
    *   \return return - 0 if success. error_id in case of error
    */
    ELMO_INT32 MoveAbsolute(ELMO_DOUBLE dPos, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAbsolute(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAbsolute(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAbsolute(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);



    /*! \fn int MoveAdditive(double dbDistance,.....) 
    *   \brief This function send Move Additive command to MMC server for specific Axis.
    *   \param dbDistance target position to move.
    *   \param motion parameters
    *   \return return - 0 if success. error_id in case of error
    */
    ELMO_INT32 MoveAdditive(ELMO_DOUBLE dbDistance, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAdditive(ELMO_DOUBLE dbDistance, ELMO_FLOAT fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAdditive(ELMO_DOUBLE dbDistance, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAdditive(ELMO_DOUBLE dbDistance, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

    /*! \fn int MoveRelative(double dbDistance,.....) 
    *   \brief This function send Move Relitive command to MMC server for specific Axis.
    *   \param dbDistance target position to move.
    *   \param motion parameters
    *   \return return - 0 if success. error_id in case of error
    */
    ELMO_INT32 MoveRelative(ELMO_DOUBLE dbDistance, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveRelative(ELMO_DOUBLE dbDistance, ELMO_FLOAT fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveRelative(ELMO_DOUBLE dbDistance, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveRelative(ELMO_DOUBLE dbDistance, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

    /*! \fn int MoveAbsoluteRepetitive(double dPos,.....) 
    *   \brief This function send Move Absolute repetitive command to MMC server for specific Axis.
    *   \param dPos target position to move.
    *   \param motion parameters
    *   \return return - 0 if success. error_id in case of error
    */
    ELMO_INT32 MoveAbsoluteRepetitive(ELMO_DOUBLE dPos, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAbsoluteRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAbsoluteRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAbsoluteRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAbsoluteRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_UINT32 uiExecDelayMs, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);


    /*! \fn int MoveRelativeRepetitive(double dPos,.....) 
    *   \brief This function send Move Relitive repetitive command to MMC server for specific Axis.
    *   \param dPos target position to move.
    *   \param motion parameters
    *   \return return - 0 if success. error_id in case of error
    */
    ELMO_INT32 MoveRelativeRepetitive(ELMO_DOUBLE dPos, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveRelativeRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveRelativeRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveRelativeRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveRelativeRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_UINT32 uiExecDelayMs, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);


    /*! \fn int MoveAdditiveRepetitive(double dPos,.....) 
    *   \brief This function send Move Additive repetitive command to MMC server for specific Axis.
    *   \param dPos target position to move.
    *   \param motion parameters
    *   \return return - 0 if success. error_id in case of error
    */
    ELMO_INT32 MoveAdditiveRepetitive(ELMO_DOUBLE dPos, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAdditiveRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAdditiveRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAdditiveRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    ELMO_INT32 MoveAdditiveRepetitive(ELMO_DOUBLE dPos, ELMO_FLOAT fVel, ELMO_UINT32 uiExecDelayMs, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

    /*! \fn int MoveTorque(double dbTargetTorque,.....) 
    *   \brief This function send Move Torque command to MMC server for specific Axis.
    *   \param dbTargetTorque target torque to move.
    *   \param motion parameters
    *   \return return - 0 if success. error_id in case of error
    */
    void MoveTorque(ELMO_DOUBLE dbTargetTorque, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    void MoveTorque(ELMO_DOUBLE dbTargetTorque, ELMO_DOUBLE dbTorqeVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
    void MoveTorque(ELMO_DOUBLE dbTargetTorque, ELMO_DOUBLE dbTorqeVelocity, ELMO_DOUBLE dbTorqueAcceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

    ELMO_INT32 PositionProfile(MC_PATH_REF hMemHandle, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

	ELMO_INT32 TouchProbeEnable(ELMO_UINT8 ucTriggerType) throw (CMMCException);
	ELMO_INT32 TouchProbeDisable() throw (CMMCException);

	ELMO_INT32 TouchProbeEnable_Ex(ELMO_ULINT32 ulShmArraySizeAlloc, ELMO_UINT16 usConfig, ELMO_UINT16 &usTPIndex) throw (CMMCException);
	ELMO_INT32 TouchProbeDisable_Ex(ELMO_INT16 sIndex) throw (CMMCException);
	ELMO_INT32 GetTouchProbeData(ELMO_PLINT32 plBuffer, ELMO_UINT16 usTPIndex, ELMO_UINT16 usNumOfPoints) throw (CMMCException);
	ELMO_INT32 GetTouchProbeData(ELMO_PDOUBLE pdBuffer, ELMO_UINT16 usTPIndex, ELMO_UINT16 usNumOfPoints) throw (CMMCException);


    /*! \fn int SetOpMode()
    *   \brief This function changes motion mode between NC/Non NC.
    *   \param eMode operational mode.
    *   \return return - 0 on success, otherwise throws CMMCException.
    */
    ELMO_INT32 SetOpMode(OPM402 eMode) throw (CMMCException);

    /*! \fn int SetOpMode(OPM402 eMode, MC_EXECUTION_MODE eExecutionMode)
    *   \brief This function changes motion mode between NC/Non NC.
    *   \param eMode operational mode.
    *   \return return - 0 on success, otherwise throws CMMCException.
    */
    void SetOpMode(OPM402 eMode, MC_EXECUTION_MODE eExecutionMode, ELMO_DOUBLE dbInitModeValue = 0) throw (CMMCException);


    /*! \fn OPM402 GetOpMode()
    * \brief This function gets motion mode between NC/Non NC.
    * \return   return - 0 on success, otherwise throws CMMCException.
    */
    OPM402 GetOpMode() throw (CMMCException);

    /*! \fn unsigned int GetStatusRegister()
    * \brief This function returns the status register
    * \return   return - 0 on success, otherwise throws CMMCException.
    */
    ELMO_UINT32 GetStatusRegister() throw (CMMCException);
    ELMO_UINT32 GetStatusRegister(MMC_GETSTATUSREGISTER_OUT& sOutput) throw (CMMCException);

    /*! \fn void AxisLink(unsigned short usAxisRef, unsigned char ucMode = 0)
    * \brief This function link between two axes
    * \return   return - when erro throws CMMCException.
    */
    void AxisLink(ELMO_UINT16 usAxisRef, ELMO_UINT8 ucMode = 0) throw (CMMCException);

    /*! \fn void AxisUnLink()
    * \brief This function unlink the axis
    * \return   return - when erro throws CMMCException.
    */
    void AxisUnLink() throw (CMMCException);

    /*! \fn void PowerOn()
    * \brief This function sends Power On command to MMC server.
    * \return   return - none. throws CMMCException on error.
    */
    void PowerOn(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn void PowerOff()
    * \brief This function sends Power Off command to MMC server.
    * \return   return - none. throws CMMCException on error.
    */
    void PowerOff(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    ELMO_DOUBLE GetActualPosition() throw (CMMCException);
    ELMO_DOUBLE GetActualVelocity() throw (CMMCException);
    ELMO_DOUBLE GetActualTorque() throw (CMMCException);
    void Halt(ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    void Halt(ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    void Halt(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    void Stop(ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    void Stop(ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    void Stop(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);  
    ELMO_UINT8 GetDigInput(ELMO_INT32 iInputNumber) throw (CMMCException);
    ELMO_ULINT32 GetDigInputs() throw (CMMCException);
    
    ELMO_ULINT32 GetDigOutputs32bit(ELMO_INT32 iOutputNumber, ELMO_UINT8 ucEnable) throw (CMMCException);
    ELMO_ULINT32 GetDigOutputs32bit(ELMO_INT32 iOutputNumber = 0) throw (CMMCException);  
    ELMO_UINT8 GetDigOutputs(ELMO_INT32 iOutputNumber = 0) throw (CMMCException);

    void SetDigOutputs32Bit(const ELMO_INT32 iOutputNumber, const ELMO_ULINT32 ulValue) throw (CMMCException);
    void SetDigOutputs32Bit( const ELMO_ULINT32 ulValue) throw (CMMCException);
    void SetDigOutputs(const ELMO_INT32 iOutputNumber, const ELMO_UINT8 ucValue, ELMO_UINT8 ucEnable) throw (CMMCException);
    void SetDigOutputs(const ELMO_INT32 iOutputNumber, const ELMO_UINT8 ucValue) throw (CMMCException); 
    void SetDigOutputs(const ELMO_UINT8 ucValue) throw (CMMCException);  
    

    void HomeDS402() throw (CMMCException);
    void HomeDS402(MMC_HOMEDS402_IN stHomeDS402Params) throw (CMMCException);
    void HomeDS402Ex() throw (CMMCException);
    void HomeDS402Ex(MMC_HOMEDS402EX_IN stParams) throw (CMMCException);


    //
    //
    /*! \fn int SetOverride(float fAccFactor, float fJerkFactor, float fVelFactor, unsigned char ucEnable = 1)
    * \brief This function  send Set Override command to MMC server for specific Axis.
    * \return   return - none. throws CMMCException on error.
    */
    void SetOverride(ELMO_FLOAT fAccFactor, ELMO_FLOAT fJerkFactor, ELMO_FLOAT fVelFactor, ELMO_UINT16 usUpdateVelFactorIdx = 0) throw (CMMCException);
    void SetDefaultHomeParams(const MMC_HOME_IN& stSingleParams);
    ELMO_UINT16 Home(ELMO_PINT16 usErrorID, ELMO_PUINT32 uiHndl) throw (CMMCException);
    ELMO_UINT16 Home(MMC_HOME_IN stHomeParams, ELMO_PINT16 usErrorID, ELMO_PUINT32 uiHndl) throw (CMMCException);

    void ConfigPDO(PDO_NUMBER_ENUM ePDONum, PDO_PARAM_TYPE_ENUM eParamType,
            ELMO_UINT32 uiPDOCommParamEvent,
            ELMO_UINT16 usEventTimer,
            ELMO_UINT8 ucEventGroup,
            ELMO_UINT8 ucPDOCommParam,
            ELMO_UINT8 ucSubIndex,
            ELMO_UINT8 ucPDOType) throw (CMMCException);
    void CancelPDO(PDO_NUMBER_ENUM ePDONum) throw (CMMCException);
    void ChangeDefaultPDOConfig(ELMO_UINT8 ucPDONum, ELMO_UINT8 ucPDODir, ELMO_UINT8 ucPDOCommParam) throw (CMMCException);
    void ElmoSetAsyncParam(ELMO_INT8 cCmd[3], ELMO_INT32& iVal) throw (CMMCException);

    inline void USleep(ELMO_ULINT32 usecs);

    void ElmoSetAsyncParam(ELMO_INT8 cCmd[3], ELMO_FLOAT& fVal) throw (CMMCException);

    void ElmoGetAsyncIntParam(ELMO_INT8 cCmd[3]) throw (CMMCException);
    void ElmoGetAsyncFloatParam(ELMO_INT8 cCmd[3]) throw (CMMCException);
    void ElmoGetAsyncIntArray(ELMO_INT8 cCmd[3], ELMO_INT16 iArrayIdx) throw (CMMCException);
    void ElmoGetAsyncFloatArray(ELMO_INT8 cCmd[3], ELMO_INT16 iArrayIdx) throw (CMMCException);

    void ElmoSetAsyncArray(ELMO_INT8 cCmd[3], ELMO_INT16 iArrayIdx, ELMO_FLOAT& fVal) throw (CMMCException);
    void ElmoSetAsyncArray(ELMO_INT8 cCmd[3], ELMO_INT16 iArrayIdx, ELMO_INT32& iVal) throw (CMMCException);
    void ElmoGetSyncParam(ELMO_INT8 cCmd[3], ELMO_FLOAT& fVal) throw (CMMCException);
    void ElmoGetSyncParam(ELMO_INT8 cCmd[3], ELMO_INT32& iVal) throw (CMMCException);
    void ElmoGetSyncArray(ELMO_INT8 cCmd[3], ELMO_INT16 iArrayIdx, ELMO_FLOAT& fVal) throw (CMMCException);
    void ElmoGetSyncArray(ELMO_INT8 cCmd[3], ELMO_INT16 iArrayIdx, ELMO_INT32& iVal) throw (CMMCException);
    void ElmoCallAsync(ELMO_INT8 cCmd[3]) throw (CMMCException);
    void ElmoExecute(ELMO_PUINT8 pData, ELMO_UINT8 ucLength) throw (CMMCException);
    ELMO_INT32 ElmoIsReplyAwaiting() throw (CMMCException);
    void ElmoGetReply(ELMO_FLOAT& fVal) throw (CMMCException);
    void ElmoGetReply(ELMO_INT32& iVal) throw (CMMCException);

    void ConfigVirtualEncoder(ELMO_DOUBLE dbLowPos, ELMO_DOUBLE dbHighPos, ELMO_FLOAT fFactor, ELMO_UINT8 ucMode, ELMO_UINT8 ucGroupID) throw (CMMCException);
    void CancelVirtualEncoder() throw (CMMCException); 
    void SetPosition(ELMO_DOUBLE dbPosition, ELMO_UINT8 ucPosMode) throw (CMMCException);

    /*!
     * \fn  int SetProfileConditioning(MMC_PROFILECOND_IN& i_params)
     * \brief   this method sets 'profile conditioning' mode of operation.
     *
     * it turns on(1)/off(0) 'profile conditioning' and sets other input parameters.
     *
     * \param i_params  reference of input parameters.
     * \return 0 if completed successfully, otherwise error or throws exception.
     */
    ELMO_INT32 SetProfileConditioning(MMC_PROFILECOND_IN& i_params) throw (CMMCException);
    /*!
     * \fn  int EnableProfileConditioning(bool enable)
     * \brief   this interface enables "profile conditioning" mode on a single axis.
     *
     * it uses parameters, which were stored in one of three buffers on previous settings.
     * that is why other input parameters are redundant here.
     *
     * \param enable    its a flag which enable(1), disable(0) or clear(0xFF) the profile conditioning mode with the existing parameters.
     * \return 0 if completed successfully, otherwise error or throws exception.
     */
    ELMO_INT32 EnableProfileConditioning(ELMO_UINT8 enable) throw (CMMCException);


    MC_PATH_REF InitPVTTable(ELMO_ULINT32 ulMaxPoints,
                        ELMO_ULINT32 ulUnderflowThreshold,
                        ELMO_UINT8 ucIsCyclic,
                        ELMO_UINT8 ucIsPosAbsolute,
            ELMO_UINT16 usDimension,
            NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_ARRAY)
    throw (CMMCException)
    {
        return InitPVTTable(ulMaxPoints,ulUnderflowThreshold,ucIsCyclic,ucIsPosAbsolute,usDimension,MC_ACS_COORD, eTableMode);
    }
    MC_PATH_REF LoadPVTTableFromFile(ELMO_PINT8 pFileName,
            NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_FILE) throw (CMMCException)
            {
                return LoadPVTTableFromFile(pFileName, MC_ACS_COORD, eTableMode);
            }
    void MovePVT(MC_PATH_REF hMemHandle) throw (CMMCException){return MovePVT(hMemHandle,MC_ACS_COORD);};


    void SendCmdViaSdoDownload(ELMO_LINT32   lData, const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex=1) throw (CMMCException);
    void SendCmdViaSdoDownload(ELMO_FLOAT    fData, const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex=1) throw (CMMCException);
    void SendCmdViaSdoUpload  (ELMO_LINT32&  lData, const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex=1) throw (CMMCException);
    void SendCmdViaSdoUpload  (ELMO_FLOAT&   fData, const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex=1) throw (CMMCException);

    void SendCmdViaSdoDownloadPlat(ELMO_LINT32  lData,  const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex = 1) throw (CMMCException);
    void SendCmdViaSdoDownloadPlat(ELMO_FLOAT   fData,  const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex = 1) throw (CMMCException);
    void SendCmdViaSdoDownloadPlat(ELMO_INT64   llData, const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex = 1) throw (CMMCException);
    void SendCmdViaSdoDownloadPlat(ELMO_DOUBLE  dbData, const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex = 1) throw (CMMCException);
    

    void SendCmdViaSdoUploadPlat(ELMO_LINT32&   lData,  const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex = 1) throw (CMMCException);   
    void SendCmdViaSdoUploadPlat(ELMO_FLOAT&    fData,  const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex = 1) throw (CMMCException);
    void SendCmdViaSdoUploadPlat(ELMO_INT64&    llData, const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex = 1) throw (CMMCException);
    void SendCmdViaSdoUploadPlat(ELMO_DOUBLE&   dbData, const ELMO_INT8* pcCmdIdx, ELMO_UINT8 ucSubIndex = 1) throw (CMMCException);

    /**
     * \fn  GearInPos(unsigned short usMaster,...)
     * \brief   perform gear-in on position of a single axis
     * \param usMaster  axis reference of master
     * \param dbMasterStartDistance master distance for gear-in procedure (backward distance from dbMasterSyncPosition for ramp-in)
     * \param dbMasterSyncPosition  position of the master in which the slave is in-sync with the master.
     * \param dbSlaveSyncPosition   slave position at which the slave is in-sync with the master.
     * \param eBufferMode           buffered mode of this function block
     * \param iRatioNumerator       gear ratio numerator
     * \param iRatioDenominator     gear ratio denominator
     * \param eMasterValueSource    defines the source for synchronization (mcSetValue, mcActualValue, auxiliary)
     *                              mcSetValue - Synchronization on master set value
     *                              mcActualValue - Synchronization on master actual value
     *                              mcAux   -   master value retrieved from an auxiliary device
     * \param eSyncMode             eCATCH_UP(0), eSLOW_DOWN(1, performed only when conditions allow it)
     * \param dbVelocity            best effort at rump-in time
     * \param dbAcceleration        best effort at rump-in time
     * \param dbDeceleration        best effort at rump-in time
     * \param dbJerk                best effort at rump-in time
     * \return 0 if completed successfully, otherwise error or throws exception .
     */
    ELMO_INT32 GearInPos(
        ELMO_UINT16 usMaster,
        ELMO_DOUBLE dbMasterStartDistance,
        ELMO_DOUBLE dbMasterSyncPosition,
        ELMO_DOUBLE dbSlaveSyncPosition,
        MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE,
        ELMO_INT32  iRatioNumerator = 1,
        ELMO_INT32  iRatioDenominator = 1,
        ECAM_VALUE_SRC_ENUM eMasterValueSource = eECAM_SET_VALUE,
        GEAR_IN_SYNC_MODE_ENUM eSyncMode = eCATCH_UP,
        ELMO_DOUBLE dbVelocity = 10000.0,
        ELMO_DOUBLE dbAcceleration = 100000.0,
        ELMO_DOUBLE dbDeceleration = 100000.0,
        ELMO_DOUBLE dbJerk = 2000000.0) throw (CMMCException);

    /**
     * \fn  GearInPos(MMC_GEARINPOS_IN& i_params)
     * \brief   perform gear-in on position of a single axis
     * \param i_params  reference of data structure, which contains all input parameters for gear-in position.
     * \return 0 if completed successfully, otherwise error or throws exception .
     */
    ELMO_INT32 GearInPos(MMC_GEARINPOS_IN& i_params) throw (CMMCException);

    private:

    MC_PATH_REF InitPVTTable(ELMO_ULINT32 ulMaxPoints,
                           ELMO_ULINT32 ulUnderflowThreshold,
                           ELMO_UINT8 ucIsCyclic,
                           ELMO_UINT8 ucIsPosAbsolute,
                           ELMO_UINT16 usDimension,
                           MC_COORD_SYSTEM_ENUM eCoordSystem,
                           NC_MOTION_TABLE_TYPE_ENUM eTableMode  = eNC_TABLE_PVT_ARRAY) throw (CMMCException)
                           {
                                return CMMCMotionAxis::InitPVTTable(ulMaxPoints,ulUnderflowThreshold,ucIsCyclic,ucIsPosAbsolute,usDimension,eCoordSystem, eTableMode);
                           }
        MC_PATH_REF LoadPVTTableFromFile(ELMO_PINT8 pFileName,
                MC_COORD_SYSTEM_ENUM eCoordSystem,
                NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_FILE) throw (CMMCException)
                {
                    return CMMCMotionAxis::LoadPVTTableFromFile(pFileName,eCoordSystem, eTableMode);
                }
        void MovePVT(MC_PATH_REF hMemHandle, MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException){return CMMCMotionAxis::MovePVT(hMemHandle,eCoordSystem);};
        ELMO_UINT16  CalcSdoIdx(const ELMO_INT8* pcCmdIdx);
        ELMO_UINT16  CalcSdoIdxPlat(ELMO_PINT8 pcCmdIdx);

};

#endif // !defined(AFX_MMCSINGLEAXIS_HPP__3E1F67CF_C8B1_40B8_BB29_090EF2A76691__INCLUDED_)

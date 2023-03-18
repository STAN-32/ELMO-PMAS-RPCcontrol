/*
 * CMMCGroupAxis.hpp
 *
 *  Created on: 10/03/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 *      Update: Haim H. 10Sep2017
 */

#ifndef MMCGROUPAXIS_HPP_
#define MMCGROUPAXIS_HPP_

#include "MMC_definitions.h"
#include "MMCAxis.hpp"
#include "MMCMotionAxis.hpp"

#ifdef PROAUT_CHANGES
        //save compiler switches
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

typedef struct _trackex_in {
        ELMO_DOUBLE                     dbMasterOrigin[6];              //ARRAY[6] of LREAL [x,y,z,u,v,w]
        ELMO_DOUBLE                     dbPCSOrigin[6];                 //ARRAY[6] of LREAL [x,y,z,u,v,w]
        ELMO_DOUBLE                     dbInitialObjectPosition[6];     //ARRAY[6] of LREAL [x,y,z,u,v,w]
        ELMO_DOUBLE                     dbMasterInitialPosition;        //LREAL
        ELMO_DOUBLE                     dbMasterSyncPosition;           //LREAL
        ELMO_DOUBLE                     dbMasterScaling;                //LREAL uu/radian
        ELMO_DOUBLE                     dbRampTrajectoryParams[12];     //ARRAY[12] of LREAL [<Z Safe Height>, t1-t4, spare 7 doubles]
        MC_BUFFERED_MODE_ENUM           eBufferMode;
        PCS_ROTATION_ANGLE_UNITS_ENUM   eRotAngleUnits;
        TRAJECTORY_MODE_ENUM            eTrajectoryMode;                //TRAJECTORY_MODE_ENUM
        ELMO_UINT16                     usMaster;                       //master axis which we have to track
        ELMO_UINT8                      ucAutoSyncPosition;             //BOOL
        ELMO_UINT8                      ucExecute;                      //BOOL
        ELMO_UINT8                      ucSpare[32];                    //save for future use
} MMC_TRACKSYNCIN_IN;


class DLLMMCPP_API MMC_MOTIONPARAMS_GROUP
{
public:
    MMC_MOTIONPARAMS_GROUP();
    //
    ELMO_DOUBLE              dAuxPoint[NC_MAX_NUM_AXES_IN_NODE];
    ELMO_DOUBLE              dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
    ELMO_FLOAT               fVelocity;
    ELMO_FLOAT               fAcceleration;
    ELMO_FLOAT               fDeceleration;
    ELMO_FLOAT               fJerk;
    ELMO_FLOAT               fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
    MC_COORD_SYSTEM_ENUM     eCoordSystem;
    NC_TRANSITION_MODE_ENUM  eTransitionMode;
    MC_BUFFERED_MODE_ENUM    eBufferMode;
    NC_ARC_SHORT_LONG_ENUM   eArcShortLong;
    NC_PATH_CHOICE_ENUM      ePathChoice;
    NC_CIRC_MODE_ENUM        eCircleMode;
    ELMO_UINT32              m_uiExecDelayMs;
    ELMO_UINT8               ucSuperimposed;
    ELMO_UINT8               ucExecute;
    //
};

class DLLMMCPP_API CMMCGroupAxis: public CMMCMotionAxis {
public:
    CMMCGroupAxis();
    virtual ~CMMCGroupAxis();
    CMMCGroupAxis(CMMCGroupAxis& axis);

    /*! \fn void InitAxisData(const char* cName, MMC_CONNECT_HNDL uHandle)
    *   \brief This function initiates axis name and retrieves a session handler.
    */
    void InitAxisData(const ELMO_INT8* cName, MMC_CONNECT_HNDL uHandle) throw (CMMCException);

    /*! \fn int GetGroupAxisByName(const char* cName)
     * \brief This function return axis index reference by his name.
     * \param  cName name of the axis.
     * \return  return - 0 on success, otherwise throws CMMCException.
     */
    ELMO_INT32 GetGroupAxisByName(const ELMO_INT8* cName) throw (CMMCException);

    ELMO_DOUBLE              m_dAuxPoint[NC_MAX_NUM_AXES_IN_NODE];
    ELMO_DOUBLE              m_dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
    ELMO_FLOAT               m_fVelocity;
    ELMO_FLOAT               m_fAcceleration;
    ELMO_FLOAT               m_fDeceleration;
    ELMO_FLOAT               m_fJerk;
    ELMO_FLOAT               m_fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
    MC_COORD_SYSTEM_ENUM     m_eCoordSystem;
    NC_TRANSITION_MODE_ENUM  m_eTransitionMode;
    NC_ARC_SHORT_LONG_ENUM   m_eArcShortLong;
    NC_PATH_CHOICE_ENUM      m_ePathChoice;
    NC_CIRC_MODE_ENUM        m_eCircleMode;
    ELMO_UINT8               m_ucSuperimposed;
    ELMO_UINT8               m_ucExecute;
    ELMO_UINT32              m_uiExecDelayMs;

public:

    /*! \fn void SetDefaultParams(const MMC_MOTIONPARAMS_GROUP& stGroupAxisParams)
    *   \brief sets axis's default parameters. overwrite class default parameters.
    *   \param stGroupAxisParams reference of structure with default parameters.
    *   \return none. or throws CMMCException on failure.
    */
    void SetDefaultParams(const MMC_MOTIONPARAMS_GROUP& stGroupAxisParams) throw (CMMCException);

    /*! \fn void SetKinTransform(MMC_SETKINTRANSFORM_IN& stInParam)
    *   \brief sets parameters for group's kinematic transformation (MSC to ACS).
    *   \param stInParam reference of structure with kinematic parameters.
    *   \return none. or throws CMMCException on failure.
    */
    void SetKinTransform(MMC_SETKINTRANSFORM_IN& stInParam) throw (CMMCException);


        /**! \fn void SetCartesianTransform(MMC_SETCARTESIANTRANSFORM_IN& stInParam)
        *       \brief sets MCS to PCS parameters for group's kinematic transformation.
        *       \param stInParam reference of structure with kinematic parameters.
        *       \return none. or throws CMMCException on failure.
        */
        ELMO_INT32 SetCartesianTransform(MMC_SETCARTESIANTRANSFORM_IN* stInParam) throw (CMMCException);

        /**! \fn void SetCartesianTransform(double (&dbOffset)[3], double (&dbRotAngle)[3], 
        *                               PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits=PCS_DEGREE,
        *                               MC_BUFFERED_MODE_ENUM eBufferMode=MC_BUFFERED_MODE, 
        *                               MC_EXECUTION_MODE eExecutionMode=eMMC_EXECUTION_MODE_IMMEDIATE)
        *       \brief sets MCS to PCS parameters for group's kinematic transformation.
        *       \param dbOffset         group of three positions in cartesian system.
        *       \param dbRotAngle       group of three angles around the vector axes (see dbOffsets).
        *       \param eRotAngleUnits degrees (0) or radians (1).
        *       \param eBufferMode one of the buffered modes in the list.
        *       \param eExecutionMode   immediate (0) or queued (1) (currently immediate only).
        *       \return none. or throws CMMCException on failure.
        */
        ELMO_INT32 SetCartesianTransform(ELMO_DOUBLE (&dbOffset)[3], ELMO_DOUBLE (&dbRotAngle)[3], 
                PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits=PCS_DEGREE,
                MC_BUFFERED_MODE_ENUM eBufferMode=MC_BUFFERED_MODE, 
                MC_EXECUTION_MODE eExecutionMode=eMMC_EXECUTION_MODE_IMMEDIATE) throw (CMMCException);

        /*! \fn ReadCartesianTransform()
         * \brief read parameters, which was previouslly set by SetCartesianTransform (see above) .
         * \param  .
         * \return - 0 if completed successfully, otherwise  error or throws CMMCException
         */
        ELMO_INT32 ReadCartesianTransform() throw (CMMCException);

        /**
        * \fn   int TrackRotaryTable(unsigned short usMaster,   ...)
        * \brief        this function block offers an abstraction layer for a rotary table,
        *                       assisting the user with tracking objects moving on a cyrcle space.
        *                       in short, a dynamic MCS to PCS transition depends on rotary table axis position.
        *                       this command operates a real motion profiler, opposed to 'TrackRotaryTable', which is a command of type 'admin'.
        * \param usMaster                               rotary table axis reference.
        * \param dbMasterOrigin positions of conveyor belt relative to MCS.
        * \param dbPCSOrigin    positions of the part (PCS) relative to dbMasterOrigin.
        * \param dbInitialObjectPosition positions of an object lying on the part, relative to PCS.
        * \param dbRampTrajectoryParams trajectory's parameters (Z-safe, T1-T4, see document).
        * \param dbMasterInitialPosition        initial position set by user (e.g. at activation time, camera event etc...)
        * \param dbMasterSyncPosition relative distance from initial position (see ucAutoSyncPosition)
        * \param dbMasterScaling        scaling for position/speed (mainly counts to radians).
        * \param ucAutoSyncPosition if 0 then sync position relative to dbMasterInitialPosition
        *                                                       otherwise it is relative to master position at activation time.
        * \param eRotAngleUnits                 angle units, degrees (0) or radians (1)
        * \param eSourceType                    position source type from rotary table axis.
        * \return - 0 if completed successfully, otherwise error or throws CMMCException
        */
        ELMO_INT32 TrackRotaryTable(unsigned short usMaster,
                ELMO_DOUBLE(&dbMasterOrigin)[6],
                ELMO_DOUBLE(&dbPCSOrigin)[6],
                ELMO_DOUBLE(&dbInitialObjectPosition)[6],
                ELMO_DOUBLE(&dbRampTrajectoryParams)[12],
                ELMO_DOUBLE dbMasterInitialPosition,
                ELMO_DOUBLE dbMasterSyncPosition,
                ELMO_DOUBLE dbMasterScaling,
                ELMO_UINT8  ucAutoSyncPosition = 1,
                PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits = PCS_RADIAN,
                PCS_REF_AXIS_SRC_ENUM eSourceType = NC_PCS_TARGET_POS) throw (CMMCException);

        /**
        * \fn   int TrackRotaryTable(MMC_SYNCIN_IN& params)
        * \brief        this function block offers an abstraction layer for a rotary table,
        *                       assisting the user with tracking objects moving on a cyrcle space.
        *                       in short, a dynamic MCS to PCS transition depends on rotary table axis position.
        *                       this command operates a real motion profiler, opposed to 'TrackRotaryTable', which is a command of type 'admin'.
        * \param params reference for parameters data structure.
        * \return - 0 if completed successfully, otherwise error or throws CMMCException
        */
        ELMO_INT32 TrackRotaryTable(MMC_TRACKSYNCIN_IN& params) throw (CMMCException);
                
        /**
        * \fn   int TrackConveyorBelt(unsigned short usMaster,  ...)
        * \brief        this function block offers an abstraction layer for a conveyor belt,
        *                       assisting the user with tracking objects moving on a conveyor.
        *                       in short, a dynamic MCS to PCS transition depends on conveyor belt axis position.
        *                       this command operates a real motion profiler, opposed to 'TrackConveyorBelt', which is a command of type 'admin'.
        * \param usMaster                               rotary table axis reference.
        * \param dbMasterOrigin positions of conveyor belt relative to MCS.
        * \param dbPCSOrigin    positions of the part (PCS) relative to dbMasterOrigin.
        * \param dbInitialObjectPosition positions of an object lying on the part, relative to PCS.
        * \param dbRampTrajectoryParams trajectory's parameters (Z-safe, T1-T4, see document).
        * \param dbMasterInitialPosition        initial position set by user (e.g. at activation time, camera event etc...)
        * \param dbMasterSyncPosition relative distance from initial position (see ucAutoSyncPosition)
        * \param dbMasterScaling        scaling for position/speed (mainly counts to radians).
        * \param ucAutoSyncPosition if 0 then sync position relative to dbMasterInitialPosition
        *                                                       otherwise it is relative to master position at activation time.
        * \param eRotAngleUnits                 angle units, degrees (0) or radians (1)
        * \param eSourceType                    position source type from rotary table axis.
        * \return - 0 if completed successfully, otherwise error or throws CMMCException
        */
        ELMO_INT32 TrackConveyorBelt(ELMO_UINT16 usMaster,
                ELMO_DOUBLE(&dbMasterOrigin)[6],
                ELMO_DOUBLE(&dbPCSOrigin)[6],
                ELMO_DOUBLE(&dbInitialObjectPosition)[6],
                ELMO_DOUBLE(&dbRampTrajectoryParams)[12],
                ELMO_DOUBLE dbMasterInitialPosition,
                ELMO_DOUBLE dbMasterSyncPosition,
                ELMO_DOUBLE dbMasterScaling,
                ELMO_UINT8 ucAutoSyncPosition = 1,
                PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits = PCS_RADIAN,
                PCS_REF_AXIS_SRC_ENUM eSourceType = NC_PCS_TARGET_POS) throw (CMMCException);
        /**
        * \fn   int TrackConveyorBelt(MMC_SYNCIN_IN& params)
        * \brief        this function block offers an abstraction layer for a conveyor belt,
        *                       assisting the user with tracking objects moving on a cyrcle space.
        *                       in short, a dynamic MCS to PCS transition depends on conveyor axis position.
        *                       this command operates a real motion profiler, opposed to 'TrackConveyorBelt', which is a command of type 'admin'.
        * \param params reference for parameters data structure.
        * \return - 0 if completed successfully, otherwise error or throws CMMCException
        */
        ELMO_INT32 TrackConveyorBelt(MMC_TRACKSYNCIN_IN& params) throw (CMMCException);

        /**
        * \fn   int TrackSyncOut(unsigned short usMaster,       ...)
        * \brief        this function block offers an abstraction layer for syncing out a tracking process.
        *                       in short, a dynamic PCS to MCS transition depends on master (RT/CB) axis position.
        *                       this command operates a real motion profiler.
        * \param usMaster               rotary table or conveyor belt axis reference.
        * \param dbMasterOrigin positions of master (RT/CB) relative to MCS.
        * \param dbTargetPosition       target positions (MCS). relvant only on none immediate mode of operation.
        * \param dbRampTrajectoryParams trajectory's parameters (Z-safe, T1-T4, see document).
        * \param dbMasterScaling        scaling for position/speed (mainly counts to radians).
        * \param dbTime         time to sync out (seconds).
        * \param dbStopDeceleration     override node's definition for stop deceleration.
        * \param ucInstantly    Zsafe only {immediate (1)} or x,y as well {none immediate (0)}.
        * \return - 0 if completed successfully, otherwise error or throws CMMCException
        */
        ELMO_INT32 TrackSyncOut(
                ELMO_UINT16 usMaster,
                ELMO_DOUBLE (&dbMasterOrigin)[6],
                ELMO_DOUBLE (&dbTargetPosition)[6],             //relevant only for none immediate mode of operation
                ELMO_DOUBLE (&dbRampTrajectoryParams)[12],      //ARRAY[12] of LREAL[<Z Safe Height (%)>, t1-t4, spare 7 doubles]
                ELMO_DOUBLE dbMasterScaling,
                ELMO_DOUBLE dbTime,                             //Time to sync out (seconds)
                ELMO_DOUBLE dbStopDeceleration,                 //override node definition
                ELMO_UINT8  ucInstantly = 1                     //Zsafe only {immediate (1)} or x,y as well {none immediate (0)}
        ) throw (CMMCException);

        /**
        * \fn   int TrackSyncOut(MMC_SYNCIN_IN& params)
        * \brief        this function block offers an abstraction layer for syncing out a tracking process.
        *                       in short, a dynamic PCS to MCS transition depends on master (RT/CB) axis position.
        *                       this command operates a real motion profiler.
        * \param params reference for parameters data structure.
        * \return - 0 if completed successfully, otherwise error or throws CMMCException
        */
        ELMO_INT32 TrackSyncOut(MMC_TRACKSYNCOUT_IN& params) throw (CMMCException);

        
        /*!
        * \fn   int SetNormalcyMode(MMC_NORMALCY_TYPE_ENUM eType, MMC_NORMALCY_PLANE_ENUM ePlane)
        * \brief        this function sets parameters for normalcy mode of operation.
        *
        *                       please note this setting is tightly coupled with selected kinematic.
        * \param eType  normalcy mode of operation(disabled if 0).
        * \param ePlane selected plane on which the normalcy mode is activated (xy, xz or yz).
        * \return - 0 if completed successfully, otherwise error or throws CMMCException
        */
        ELMO_INT32 SetNormalcyMode(MMC_NORMALCY_TYPE_ENUM eType, MMC_NORMALCY_PLANE_ENUM ePlane) throw (CMMCException);

        /*!
         * \fn int SetNormalcyOff();
         * \brief disable normalcy mode.
         * \return - 0 if completed successfully, otherwise error or throws CMMCException
         */
        ELMO_INT32 SetNormalcyOff()  throw (CMMCException);

        /*!
         * \fn int GetNormalcyMode(MMC_NORMALCY_TYPE_ENUM& eType, MMC_NORMALCY_PLANE_ENUM& ePlane)
         * \brief get normalcy mode of operation and selected plane (xy/xz/yz).
         * \param eType reference of normalcy type (mode).
         * \param ePlane reference of normalcy plane(coordinates).
         * \return - 0 if completed successfully, otherwise error or throws CMMCException
         */
        ELMO_INT32 GetNormalcyMode(MMC_NORMALCY_TYPE_ENUM& eType, MMC_NORMALCY_PLANE_ENUM& ePlane)  throw (CMMCException);

    /*! \fn RemoveAxisFromGroup(NC_IDENT_IN_GROUP_ENUM eIdentInGroup)
     * \brief removes axis from axis group.
     * \param  eIdentInGroup - group identifier.
     * \return - none on success, otherwise throws CMMCException
     */
    void RemoveAxisFromGroup(NC_IDENT_IN_GROUP_ENUM eIdentInGroup) throw (CMMCException);

    /*! \fn MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM, NC_PATH_CHOICE_ENUM, NC_CIRC_MODE_ENUM, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Circular Absolute command to MMC server for specific Group.
     * \param  eArcShortLong - defines the kind of supported arc length.
     * \param  ePathChoice - defines the kinds of supported path choice.
     * \param  eCircleMode - defines the kinds of supported circular modes.
     * \param  eBufferMode - defines options for supported buffered mode(default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, NC_CIRC_MODE_ENUM eCircleMode, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM, NC_PATH_CHOICE_ENUM, NC_CIRC_MODE_ENUM, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Circular Absolute command to MMC server for specific Group.
     * \param  eArcShortLong - defines the kind of supported arc length.
     * \param  ePathChoice - defines the kinds of supported path choice.
     * \param  eCircleMode - defines the kinds of supported circular modes.
     * \param  dAuxPoint - list of start points.
     * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, NC_CIRC_MODE_ENUM eCircleMode, ELMO_DOUBLE dAuxPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM, NC_PATH_CHOICE_ENUM, NC_CIRC_MODE_ENUM, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Circular Absolute command to MMC server for specific Group.
     * \param  eArcShortLong - defines the kind of supported arc length.
     * \param  ePathChoice - defines the kinds of supported path choice.
     * \param  eCircleMode - defines the kinds of supported circular modes.
     * \param  dAuxPoint - list of start points.
     * \param  dEndPoint - list of end points.
     * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, NC_CIRC_MODE_ENUM eCircleMode, ELMO_DOUBLE dAuxPoint[NC_MAX_NUM_AXES_IN_NODE], ELMO_DOUBLE dEndPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Circular Center command to MMC server for specific Group.
     * \param  eArcShortLong - defines the kind of supported arc length.
     * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Circular Center command to MMC server for specific Group.
     * \param  eArcShortLong - defines the kind of supported arc length.
     * \param  dCenterPoint - list of start points.
     * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, ELMO_DOUBLE dBorderPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Circular Center command to MMC server for specific Group.
     * \param  eArcShortLong - defines the kind of supported arc length.
     * \param  dCenterPoint - list of start points.
     * \param  dEndPoint - list of end points.
     * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, ELMO_DOUBLE dCenterPoint[NC_MAX_NUM_AXES_IN_NODE], ELMO_DOUBLE dEndPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], double dEndPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Absolute Border command to MMC server for specific Group.
     * \param  dBorderPoint - list of start points.
     * \param  dEndPoint - list of end points.
     * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsoluteBorder(ELMO_DOUBLE dBorderPoint[NC_MAX_NUM_AXES_IN_NODE], ELMO_DOUBLE dEndPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Absolute Border command to MMC server for specific Group.
     * \param  dBorderPoint - list of start points.
     * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsoluteBorder(ELMO_DOUBLE dBorderPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Absolute Border command to MMC server for specific Group.
     * \param  dBorderPoint - list of start points.
     * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsoluteRadius(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Absolute Border command to MMC server for specific Group.
     * \param  dBorderPoint - list of start points.
     * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsoluteRadius(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, ELMO_DOUBLE dSpearHeadPoint[NC_MAX_NUM_AXES_IN_NODE], ELMO_DOUBLE dEndPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    /*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
     * \brief sends Move Absolute Border command to MMC server for specific Group.
     * \param  dBorderPoint - list of start points.
     * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
     * \return - 0 on success, otherwise throws CMMCException
     */
    ELMO_INT32 MoveCircularAbsoluteRadius(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, ELMO_DOUBLE dSpearHeadPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    ELMO_INT32 MoveCircularAbsoluteAngle(ELMO_DOUBLE dAngle, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveCircularAbsoluteAngle(ELMO_DOUBLE dAngle, ELMO_DOUBLE dCenterPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn int MoveAngle(double (&dCenter)[MAX_CENTER_POINTS], double dAngle, MC_COORD_AXES ePlain=NC_XY_AXES, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE, double dHelixPos=0)
	 * \brief sends Move Angle command to Maestro for specific Group.
	 *
	 * \param  dCenter	center points.
	 * \param  dAngle	the angle.
	 * \param  ePlain	selected plain (default XY).
	 * \param  eBufferMode	buffered mode (default buffered).
	 * \param  dHelixPos	future use.
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	ELMO_INT32 MoveAngle(ELMO_DOUBLE (&dCenter)[MAX_CENTER_POINTS], ELMO_DOUBLE dAngle, MC_COORD_AXES ePlain=NC_XY_AXES, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE, ELMO_DOUBLE dHelixPos=0) throw (CMMCException);

	/*! \fn int MoveAngle(double (&dCenter)[MAX_CENTER_POINTS], double dAngle, ...)
	 * \brief sends Move Angle command to Maestro for specific Group.
	 *
	 * overloaded method
	 *
	 * \param  dCenter	center points.
	 * \param  dAngle	the angle.
	 * \param  ePlain	selected plain (default XY).
	 * \param  eBufferMode	buffered mode (default buffered).
	 * \param  dHelixPos	future use.
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	ELMO_INT32 MoveAngle(ELMO_DOUBLE (&dCenter)[MAX_CENTER_POINTS], ELMO_DOUBLE dAngle,
			ELMO_DOUBLE dVelocity,
			ELMO_DOUBLE dAcceleration,
			ELMO_DOUBLE dDeceleration,
			ELMO_DOUBLE dJerk,
			ELMO_DOUBLE (&dTransitionParameter)[NC_MAX_NUM_AXES_IN_NODE],
			NC_TRANSITION_MODE_ENUM eTransitionMode = MC_TM_NONE_MODE,
 			MC_COORD_AXES ePlain=NC_XY_AXES , MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE, ELMO_DOUBLE dHelixPos=0) throw (CMMCException);

    ELMO_INT32 MoveLinearAbsolute(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAbsolute(ELMO_FLOAT fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAbsolute(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAbsolute(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAbsolute(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    
    
    ELMO_INT32 MoveLinearRelative(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearRelative(ELMO_FLOAT fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearRelative(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbDistance[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearRelative(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbDistance[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearRelative(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbDistance[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    
    
    ELMO_INT32 MoveLinearAdditive(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAdditive(ELMO_FLOAT fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAdditive(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbDistance[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAdditive(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbDistance[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAdditive(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbDistance[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    

    ELMO_INT32 MoveLinearAbsoluteRepetitive(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAbsoluteRepetitive(ELMO_FLOAT fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAbsoluteRepetitive(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAbsoluteRepetitive(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearAbsoluteRepetitive(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);


    ELMO_INT32 MoveLinearRelativeRepetitive(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearRelativeRepetitive(ELMO_FLOAT fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearRelativeRepetitive(ELMO_FLOAT fVelocity, ELMO_DOUBLE dDistance[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearRelativeRepetitive(ELMO_FLOAT fVelocity, ELMO_DOUBLE dDistance[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MoveLinearRelativeRepetitive(ELMO_FLOAT fVelocity, ELMO_DOUBLE dDistance[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

    ELMO_INT32 MovePolynomAbsolute(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MovePolynomAbsolute(ELMO_FLOAT fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MovePolynomAbsolute(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbAuxPoint[NC_MAX_NUM_AXES_IN_NODE], ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MovePolynomAbsolute(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbAuxPoint[NC_MAX_NUM_AXES_IN_NODE], ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);  
    ELMO_INT32 MovePolynomAbsolute(ELMO_FLOAT fVelocity, ELMO_DOUBLE dbAuxPoint[NC_MAX_NUM_AXES_IN_NODE], ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE], ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    ELMO_INT32 MovePolynomAbsolute(ELMO_FLOAT fVelocity, ELMO_FLOAT fAcceleration, ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    

    ELMO_INT32   GroupSetOverride(ELMO_FLOAT fVelFactor,  ELMO_FLOAT fAccFactor, ELMO_FLOAT fJerkFactor, ELMO_UINT16 usUpdateVelFactorIdx) throw (CMMCException);
	ELMO_INT32   GroupSetOverrideEx(ELMO_DOUBLE dVelFactor, ELMO_DOUBLE dAccFactor, ELMO_DOUBLE dJerkFactor, ELMO_UINT16 usUpdateVelFactorIdx) throw (CMMCException); //@UM
    ELMO_INT32   GroupSetPosition(ELMO_DOUBLE dbPosition[], MC_COORD_SYSTEM_ENUM eCoordSystem, ELMO_UINT8 ucMode, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
    uint32_t     GroupReadStatus(ELMO_UINT16& usGroupErrorID) throw (CMMCException);
    uint32_t     GroupReadStatus() throw (CMMCException);
    void                GroupEnable()  throw (CMMCException);
    void                GroupDisable() throw (CMMCException);
    void                GroupReset()   throw (CMMCException);
    ELMO_DOUBLE GroupReadActualVelocity(MC_COORD_SYSTEM_ENUM eCoordSystem, ELMO_DOUBLE dVelocity[NC_MAX_NUM_AXES_IN_NODE]) throw (CMMCException);
    ELMO_DOUBLE GroupReadActualVelocity(MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);
    ELMO_UINT16 GroupReadError() throw (CMMCException);
    void                AddAxisToGroup(NC_NODE_HNDL_T hNode, NC_IDENT_IN_GROUP_ENUM eIdentInGroup) throw (CMMCException);
    ELMO_INT32  GroupReadActualPosition(MC_COORD_SYSTEM_ENUM eCoordSystem, ELMO_DOUBLE dbPosition[NC_MAX_NUM_AXES_IN_NODE]) throw (CMMCException);
    void                GroupStop(ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode) throw (CMMCException);
    void                GroupHalt(ELMO_FLOAT fDeceleration, ELMO_FLOAT fJerk, MC_BUFFERED_MODE_ENUM eBufferMode) throw (CMMCException);

    void                MovePath(MC_PATH_REF hMemHandle, MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);
    void                MovePath(MC_PATH_REF hMemHandle, ELMO_FLOAT fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferModeeBufferMode = MC_BUFFERED_MODE,  MC_COORD_SYSTEM_ENUM eCoordSystem = MC_MCS_COORD) throw (CMMCException);
    void                PathDeselect(MC_PATH_REF hMemHandle) throw (CMMCException);
    ELMO_UINT32 PathSelect(MC_PATH_DATA_REF pPathToSplineFile) throw (CMMCException);
    ELMO_UINT32 PathSelect(MC_PATH_DATA_REF pPathToSplineFile, MC_COORD_SYSTEM_ENUM eCoordSystem, ELMO_UINT8 ucExecute = 1) throw (CMMCException);
    /**
    * \fn   unsigned int PathGetLengths(MC_PATH_REF hMemHandle,....) 
    * \brief    retrieves length values of specifies segments.
                buffer must comply to number of values, which programer expects to get 
                and cannot be greater than 170 elements.
    * \param    hMemHandle - table handler of offline spline table.
    * \param    uiStartIndex - specifies the table segment from witch to start the length values collection.
    * \param    uiNumOfSegments specifies the number of segments for the length values collection.
    * \param    dbValues - the buffer in which this API stores the collected values.
    * \return   number of returned values if completed successfuly, otherwise throws an error or error (< 0)
    */
    ELMO_UINT32 PathGetLengths(MC_PATH_REF hMemHandle,
                    ELMO_UINT32  uiStartIndex,
                    ELMO_UINT32  uiNumOfSegments,
                    ELMO_PDOUBLE dbValues) throw (CMMCException);

    void SetBoolParameter(int32_t lValue, MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    void SetParameter(ELMO_DOUBLE dbValue, MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    int32_t GetBoolParameter(MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);
    ELMO_DOUBLE GetParameter(MMC_PARAMETER_LIST_ENUM eNumber, ELMO_INT32 iIndex) throw (CMMCException);

    void GetMembersInfo(MMC_GETGROUPMEMBERSINFO_OUT* stOutput) throw (CMMCException);


//#ifndef WIN32
#if ((OS_PLATFORM == LINUXIPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC32_PLATFORM) || (OS_PLATFORM == LINUXRPC64_PLATFORM))
                           void SetCartesianKinematics(MC_KIN_REF_CARTESIAN& stCart)      throw (CMMCException) __attribute__ ((deprecated));
                           void SetDeltaRobotKinematics(MC_KIN_REF_DELTA& stDelta)        throw (CMMCException) __attribute__ ((deprecated));
                           void SetKinematic(MC_KIN_REF& stInput,NC_KIN_TYPE eKinType)    throw (CMMCException) __attribute__ ((deprecated));
#elif ((OS_PLATFORM == WIN32_PLATFORM) || (OS_PLATFORM == WIN64_PLATFORM) || (OS_PLATFORM == VXWORKS32_PLATFORM))
    __declspec(deprecated) void SetCartesianKinematics(MC_KIN_REF_CARTESIAN& stCart)      throw (CMMCException);
    __declspec(deprecated) void SetDeltaRobotKinematics(MC_KIN_REF_DELTA& stDelta)        throw (CMMCException);
    __declspec(deprecated) void SetKinematic(MC_KIN_REF& stInput,NC_KIN_TYPE eKinType)    throw (CMMCException);
#else
    #error "***MMCGroupAxis.hpp: Supporting Env. Visual or Eclipse (for defined platform see: OS_PlatformsSelect.h). "
#endif


    /*! \fn unsigned int GetStatusRegister()
    * \brief This function returns the status register
    * \return   return - 0 on success, otherwise throws CMMCException.
    */
    ELMO_UINT32 GetStatusRegister() throw (CMMCException);
    ELMO_UINT32 GetStatusRegister(MMC_GETSTATUSREGISTER_OUT& sOutput) throw (CMMCException);

    /*! \fn unsigned int GetMcsLimitRegister()
    * \brief This function returns the MCS limit register
    * \return   return - 0 on success, otherwise throws CMMCException.
    */
    ELMO_UINT32 GetMcsLimitRegister() throw (CMMCException);


    void                Reset()throw (CMMCException){GroupReset();}
    uint32_t ReadStatus()throw (CMMCException){return GroupReadStatus();}
    uint32_t ReadStatus(ELMO_UINT16& usAxisErrorID, ELMO_UINT16& usStatusWord)throw (CMMCException){return GroupReadStatus(usAxisErrorID);}

        /*
         * wrappers for kinematics's transformation API
         */
        /*! \fn void SetKinTransformDelta(MMC_KINTRANSFORM_DELTA_IN& stInParam)
        *       \brief sets parameters kinematic transformation (MSC to ACS) for DELTA robot.
        *       \param stInParam reference of structure with kinematic parameters.
        *       \return 0 if completed successfully, otherwise error or throws CMMCException.
        */
        //ELMO_INT32 SetKinTransformDelta(IN MMC_KINTRANSFORM_DELTA_IN& pInParam) throw (CMMCException);
		//int SetKinTransformDelta(IN MMC_KINTRANSFORM_DELTA_IN& pInParam) throw (CMMCException);
		/*! \fn void SetKinTransformDelta(MMC_KINTRANSFORM_DELTA_IN& i_params, unsigned char ucLinearUU, unsigned char ucRotaryUU)
		*	\brief sets kinematic transformation parameters (MSC to ACS) for delta robot using selected user units.
		*	\param i_params reference of data structure with kinematic parameters.
		*	\param ucRotaryUU rotary selected user unit (radians, degrees, miliradians. default is no conversion).
		*	\param ucLinearUU linear selected user unit (millimeters, micrometers, nanometers. default is no conversion)
		*	\return 0 if completed successfully, otherwise error or throws CMMCException.
		*/
		ELMO_INT32 SetKinTransformDelta(MMC_KINTRANSFORM_DELTA_IN& i_params, ELMO_UINT8 ucLinearUU=0, ELMO_UINT8 ucRotaryUU=0) throw (CMMCException);

        
        /*! \fn void SetKinTransformCartesian(MMC_KINTRANSFORM_CARTESIAN_IN& stInParam)
        *       \brief sets parameters kinematic transformation (MSC to ACS) for Cartesian system.
        *       \param stInParam reference of structure with kinematic parameters.
        *       \return 0 if completed successfully, otherwise error or throws CMMCException.
        */
        //ELMO_INT32 SetKinTransformCartesian(IN MMC_KINTRANSFORM_CARTESIAN_IN& pInParam) throw (CMMCException);
		/*! \fn void SetKinTransformCartesian(MMC_KINTRANSFORM_CARTESIAN_IN& i_params, unsigned char ucLinearUU, unsigned char ucRotaryUU)
		*	\brief sets kinematic transformation parameters (MSC to ACS) for cartesin system using selected user units.
		*	\param i_params reference of data structure with kinematic parameters.
		*	\param ucRotaryUU rotary selected user unit (radians, degrees, miliradians. default is no conversion).
		*	\param ucLinearUU linear selected user unit (millimeters, micrometers, nanometers. default is no conversion)
		*	\return 0 if completed successfully, otherwise error or throws CMMCException.
		*/
		ELMO_INT32 SetKinTransformCartesian(MMC_KINTRANSFORM_CARTESIAN_IN& i_params, ELMO_UINT8 ucLinearUU=0, ELMO_UINT8 ucRotaryUU=0) throw (CMMCException);


        /*! \fn void SetKinTransformScara(MMC_KINTRANSFORM_SCARA_IN& stInParam)
        *       \brief sets parameters kinematic transformation (MSC to ACS) for SCARA robot.
        *       \param stInParam reference of structure with kinematic parameters.
        *       \return 0 if completed successfully, otherwise error or throws CMMCException.
        */
        //ELMO_INT32 SetKinTransformScara(IN MMC_KINTRANSFORM_SCARA_IN& pInParam) throw (CMMCException);
		/*! \fn void SetKinTransformScara(MMC_KINTRANSFORM_SCARA_IN& i_params, unsigned char ucLinearUU, unsigned char ucRotaryUU)
		*	\brief sets kinematic transformation parameters (MSC to ACS) for scara robot using selected user units.
		*	\param i_params reference of data structure with kinematic parameters.
		*	\param ucRotaryUU rotary selected user unit (radians, degrees, miliradians. default is no conversion).
		*	\param ucLinearUU linear selected user unit (millimeters, micrometers, nanometers. default is no conversion)
		*	\return 0 if completed successfully, otherwise error or throws CMMCException.
		*/
		ELMO_INT32 SetKinTransformScara(MMC_KINTRANSFORM_SCARA_IN& i_params, ELMO_UINT8 ucLinearUU=0, ELMO_UINT8 ucRotaryUU=0) throw (CMMCException);

		/*! \fn void SetKinTransformThreeLink(MMC_KINTRANSFORM_THREELINK_IN& stInParam)
		*	\brief sets parameters kinematic transformation (MSC to ACS) for THREELINK robot.
		*	\param stInParam reference of structure with kinematic parameters.
		*	\param ucRotaryUU rotary selected user unit (radians, degrees, miliradians. default is no conversion).
		*	\param ucLinearUU linear selected user unit (millimeters, micrometers, nanometers. default is no conversion)
		*	\return 0 if completed successfully, otherwise error or throws CMMCException.
		*/
		//ELMO_INT32 SetKinTransformThreeLink(IN MMC_KINTRANSFORM_THREELINK_IN& pInParam) throw (CMMCException);
		ELMO_INT32 SetKinTransformThreeLink(MMC_KINTRANSFORM_THREELINK_IN& i_params, ELMO_UINT8 ucLinearUU=0, ELMO_UINT8 ucRotaryUU=0) throw (CMMCException);
        

        /*! \fn void SetKinTransformHxpd(MMC_KINTRANSFORM_HXPD_IN& i_params)
        *       \brief sets kinematic transformation parameters (MSC to ACS) for Hexapod robot.
        *       \param i_params reference of data structure with kinematic parameters.
        *       \return 0 if completed successfully, otherwise error or throws CMMCException.
        */
        //ELMO_INT32 SetKinTransformHxpd(IN MMC_KINTRANSFORM_HXPD_IN& i_params) throw (CMMCException);
		/*! \fn void SetKinTransformHxpd(MMC_KINTRANSFORM_HXPD_IN& i_params, unsigned char ucLinearUU, unsigned char ucRotaryUU)
		*	\brief sets kinematic transformation parameters (MSC to ACS) for Hexapod robot using selected user units.
		*	\param i_params reference of data structure with kinematic parameters.
		*	\param ucRotaryUU rotary selected user unit (radians, degrees, miliradians. default is no conversion).
		*	\param ucLinearUU linear selected user unit (millimeters, micrometers, nanometers. default is no conversion)
		*	\return 0 if completed successfully, otherwise error or throws CMMCException.
		*/
		ELMO_INT32 SetKinTransformHxpd(MMC_KINTRANSFORM_HXPD_IN& i_params, ELMO_UINT8 ucLinearUU=0, ELMO_UINT8 ucRotaryUU=0)  throw (CMMCException);
	/*! \fn void SetKinTransformDualHead(NC_DUAL_HEAD_TYPE& i_params, unsigned char ucLinearUU, unsigned char ucRotaryUU)
	*	\brief sets kinematic transformation parameters (MSC to ACS) for dual head robot using selected user units.
	*	\param i_params reference of data structure with kinematic parameters.
	*	\param ucRotaryUU rotary selected user unit (radians, degrees, miliradians. default is no conversion).
	*	\param ucLinearUU linear selected user unit (millimeters, micrometers, nanometers. default is no conversion)
	*	\return 0 if completed successfully, otherwise error or throws CMMCException.
	*/
	    ELMO_INT32 SetKinTransformDualHead(MMC_KINTRANSFORM_DUALHEAD_IN& i_params, ELMO_UINT8 ucLinearUU, ELMO_UINT8 ucRotaryUU) throw (CMMCException);

        /*! \fn void ReadKinTransform((MMC_READKINTRANSFORMEX_OUT& stOutParam)
        *       \brief This function get group's kinematic transformation parameter.
        *       \param stOutParam reference of structure with kinematic parameters.
        *       \return 0 if completed successfully, otherwise error or throws CMMCException.
        */
        ELMO_INT32 ReadKinTransform(MMC_READKINTRANSFORMEX_OUT& stOutParam) throw (CMMCException);


        /*! \fn void ClearKinTransform()
        *       \brief This function clear group's kinematic parameters.
        *       \return 0 if completed successfully, otherwise error or throws CMMCException.
        */
        ELMO_INT32 ClearKinTransform() throw (CMMCException);
        
        void GetMotionInfo(MMC_MOTIONINFO_OUT& stMotionInfoOut) throw (CMMCException);

        void SetDualHeadCartesianKinematics(MC_DUAL_HEAD_SET& stInputDualRef) throw (CMMCException);

private:
    void CopyMoveCircularAbsParams(MMC_MOVECIRCULARABSOLUTE_IN& stInParams);
    void CopyMoveCircularAbsCenterParams(MMC_MOVECIRCULARABSOLUTECENTER_IN& stInParams);
    void CopyMoveCircularAbsBorderParams(MMC_MOVECIRCULARABSOLUTEBORDER_IN& stInParams);
    void CopyMoveCircularAbsAngleParams(MMC_MOVECIRCULARABSOLUTEANGLE_IN& stInParams);
    void CopyMoveCircularAbsRadiusParams(MMC_MOVECIRCULARABSOLUTERADIUS_IN& stInParams);
    void CopyMoveLinearAbsParams(MMC_MOVELINEARABSOLUTE_IN& stInParams);
    void CopyMoveLinearRltParams(MMC_MOVELINEARRELATIVE_IN& stInParams);
    void CopyMoveLinearAbsRepParams(MMC_MOVELINEARABSOLUTEREPETITIVE_IN& stInParams);
    void CopyMoveLinearRltRepParams(MMC_MOVELINEARRELATIVEREPETITIVE_IN& stInParams);
    void CopyMoveLinearAddParams(MMC_MOVELINEARADDITIVE_IN& stInParams);
    void CopyMovePolynomAbsParams(MMC_MOVEPOLYNOMABSOLUTE_IN& stInParams);

    void SendSdoCmd(int32_t lData,
            ELMO_UINT8   ucService,
            ELMO_UINT8   ucSubIndex,
            uint32_t     ulDataLength,
            ELMO_UINT16  usIndex,
            ELMO_UINT16  usSlaveID)throw (CMMCException){return;}
                        
        void SendSdoDownloadExCmd(
                        SEND_SDO_DATA_EX *uData,                        
                        ELMO_UINT16 usIndex,
                        ELMO_UINT8  ucSubIndex,                      
                        ELMO_UINT8  ucDataLength)throw (CMMCException) {return;}
        void SendSdoUploadExCmd(
                SEND_SDO_DATA_EX *uData,
                ELMO_UINT16 usIndex,
                ELMO_UINT8  ucSubIndex,
                ELMO_UINT8  ucDataLength)throw (CMMCException) {return;}
        void SendSdoUploadAsyncExCmd(
                SEND_SDO_DATA_EX *uData,
                ELMO_UINT16 usIndex,
                ELMO_UINT8  ucSubIndex,
                ELMO_UINT8  ucDataLength)throw (CMMCException) {return;}
        void RetrieveSdoUploadAsyncExCmd(
                SEND_SDO_DATA_EX *uData,
                ELMO_UINT16 usIndex,
                ELMO_UINT8  ucSubIndex,
                ELMO_UINT8  ucDataLength)throw (CMMCException) {return;}

    void SendSdoDownload(int32_t lData,
            ELMO_UINT8   ucSubIndex,
            uint32_t     ulDataLength,
            ELMO_UINT16  usIndex,
            ELMO_UINT16  usSlaveID)throw (CMMCException){return;}
    int32_t SendSdoUpload(ELMO_UINT8 ucSubIndex,
            uint32_t     ulDataLength,
            ELMO_UINT16  usIndex,
            ELMO_UINT16  usSlaveID)throw (CMMCException){return 0;}
    void SendSdoUploadAsync(ELMO_UINT8 ucSubIndex,
            uint32_t     ulDataLength,
            ELMO_UINT16  usIndex,
            ELMO_UINT16  usSlaveID)throw (CMMCException){return;}
    void RetreiveSdoUploadAsync(int32_t& lData)throw (CMMCException){return;}
    MMCPPULL_T PDOGeneralRead(ELMO_UINT8 ucParam)throw (CMMCException){return 0;}
    void PDOGeneralWrite(ELMO_UINT8 ucParam,MMCPPULL_T ulliVal)throw (CMMCException){return;}
    void PDOGeneralWrite(ELMO_UINT8 ucParam,unGeneralPDOWriteData DataUnion)throw (CMMCException){return;}
    void GetPDOInfo(ELMO_UINT8 uiPDONumber,ELMO_UINT32 &iPDOEventMode, ELMO_UINT8 &ucPDOCommType, ELMO_UINT8 &ucTPDOCommEventGroup, ELMO_UINT8 &ucRPDOCommEventGroup)throw (CMMCException){return;}
    ELMO_UINT16 GetAxisError(ELMO_PUINT16 usLastEmergencyErrCode)throw (CMMCException){return 0;};
    void ConfigPDOEventMode(ELMO_UINT8 ucPDOEventMode, PDO_NUMBER_ENUM ePDONum = PDO_NUM_3) throw (CMMCException){return;}


    void EthercatWriteMemoryRange(ELMO_UINT16 usRegAddr, ELMO_UINT8 ucLength, ELMO_UINT8 pData[ETHERCAT_MEMORY_WRITE_MAX_SIZE]) throw (CMMCException){return;}

    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucByteLength, ELMO_UINT8 pRawData[PI_REG_VAR_SIZE]) throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT16 usByteLength, ELMO_UINT8 pRawData[PI_LARGE_VAR_SIZE]) throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_BOOL bData)     throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_INT8 cData)     throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucData)   throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT16 usData)  throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_INT16 sData)    throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT32 uiData)  throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_INT32 iData)    throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_FLOAT fData)    throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_DOUBLE dbData)  throw (CMMCException){return;}

    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_UINT64 ullData) throw (CMMCException){return;}
    void EthercatWritePIVar(ELMO_UINT16 usIndex, ELMO_INT64  llData)  throw (CMMCException){return;}

    void EthercatReadMemoryRange(ELMO_UINT16 usRegAddr,  ELMO_UINT8 ucLength, ELMO_UINT8 pData[ETHERCAT_MEMORY_READ_MAX_SIZE]) throw (CMMCException){return;}

    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT8 ucByteLength, ELMO_UINT8 pRawData[PI_REG_VAR_SIZE]) throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT16 usByteLength, ELMO_UINT8 pRawData[PI_LARGE_VAR_SIZE]) throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_BOOL   &bData)  throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_INT8   &cData)  throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT8  &ucData) throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT16 &usData) throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_INT16  &sData)  throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT32 &uiData) throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_INT32  &iData)  throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_FLOAT  &fData)  throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_DOUBLE &dbData) throw (CMMCException){return;}
    
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_UINT64 &ullData)throw (CMMCException){return;}
    void EthercatReadPIVar(ELMO_UINT16 usIndex, ELMO_UINT8 ucDirection, ELMO_INT64  &llData) throw (CMMCException){return;}
    
    void EthercatPIVarInfo(ELMO_UINT16 usPIVarIndex, ELMO_UINT8 ucDirection, NC_PI_ENTRY &VarInfo) throw (CMMCException){return;}

};

#ifdef PROAUT_CHANGES
        //restore compiler switches
        #pragma GCC diagnostic pop
#endif

#endif /* MMCGROUPAXIS_HPP_ */

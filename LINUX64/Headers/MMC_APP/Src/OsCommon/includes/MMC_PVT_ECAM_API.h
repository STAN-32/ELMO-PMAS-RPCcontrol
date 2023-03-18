
////////////////////////////////////////////////////////////////////////////////
/// \file MMC_PVT_API.h
/// Name        : MMC_PVT_API.h
/// Author      : Alex
/// Created on  : April 07, 2012
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.3.0 Updated 03Aug2015 Haim H.
///               0.4.0 Updated 11Sep2017 Haim H.
///               0.4.2 Updated 26Aug2019 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_PVT_API_H_
#define MMC_PVT_API_H_

#ifdef __cplusplus
 extern "C" {
#endif

#define NC_PVT_ECAM_MAX_ARRAY_SIZE               170

typedef enum
 {
    eNC_TABLE_NONE,
    eNC_TABLE_SPLINE,
    eNC_TABLE_PVT_FILE,                             //old method eCUBIC_POLYNOM
    eNC_TABLE_PVT_ARRAY,                            //old method eCUBIC_POLYNOM
    eNC_TABLE_PVT_FILE_QUINTIC_CUB, //new method eQUINTIC_ON_CUBIC
    eNC_TABLE_PVT_ARRAY_QUINTIC_CUB,//new method eQUINTIC_ON_CUBIC
    eNC_TABLE_ECAM_FILE,
    eNC_TABLE_ECAM_ARRAY,
    eNC_TABLE_OLSPLN_FILE,
    eNC_TABLE_OLSPLN_ARRAY,
 	eNC_TABLE_OPCMP_FILE,
 	eNC_TABLE_OPCMP_ARRAY,
} NC_MOTION_TABLE_TYPE_ENUM;

typedef enum
{
    MC_NONE_ONLINE_SPLINE_MODE = 0,
    MC_QUINTIC_ON_PARAB_FT_DWELL,   //fixed time        5-order polynomial
    MC_QUINTIC_ON_PARAB_VT_DWELL,   //variable time     5-order polynomial
    MC_QUINTIC_ON_PARAB_CV_DWELL,   //constant velocity 5-order polynomial
    MC_SEPTIC_ON_PARAB_FT_DWELL,    //7 - order polynomial
    MC_SEPTIC_ON_PARAB_VT_DWELL,    //7 - order polynomial
    MC_CYCLOID_VELOCITY_MODIFIED1,  
    MC_CYCLOID_VELOCITY_MODIFIED2,
} NC_ONLINE_SPLINE_MODE_ENUM;

typedef struct mmc_inittable_in
{
    ELMO_FLOAT                   fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
    NC_TRANSITION_MODE_ENUM     eTransitionMode;
    MC_BUFFERED_MODE_ENUM       eBufferMode;
    NC_MOTION_TABLE_TYPE_ENUM   eTableType;
    MC_COORD_SYSTEM_ENUM        eCoordSystem;
    ELMO_ULINT32                ulMaxNumberOfPoints;
    ELMO_ULINT32                ulUnderflowThreshold;
    ELMO_UINT16                 usAxisRef;
    ELMO_UINT16                 usDimension;
    ELMO_UINT8                  ucIsDynamicMode;
    ELMO_UINT8                  ucIsPosAbsolute;
    ELMO_UINT8                  ucIsCyclic;
    ELMO_UINT8                  ucSuperimposed;
    ELMO_UINT8                  ucExecute;
} MMC_INITTABLE_IN;

typedef struct mmc_inittable_out
{
    MC_PATH_REF                 hMemHandle;
    ELMO_UINT16                 usStatus;
    ELMO_INT16                  usErrorID;
} MMC_INITTABLE_OUT;

typedef struct mmc_inittableex_in
{
    ELMO_DOUBLE             dbConstVelocity;
    ELMO_DOUBLE             dbConstTime;
    MC_BUFFERED_MODE_ENUM   eBufferMode;
    NC_MOTION_TABLE_TYPE_ENUM eTableType;
    MC_COORD_SYSTEM_ENUM    eCoordSystem;
    NC_ONLINE_SPLINE_MODE_ENUM eSplineMode;
    ELMO_ULINT32            ulMaxNumberOfPoints;
    ELMO_ULINT32            ulUnderflowThreshold;
    ELMO_UINT16             usAxisRef;
    ELMO_UINT16             usDimension;
    ELMO_UINT8              ucIsDynamicMode;
    ELMO_UINT8              ucIsPosAbsolute;
    ELMO_UINT8              ucIsCyclic;
    ELMO_UINT8              ucSuperimposed;
    ELMO_UINT8              ucExecute;
    ELMO_UINT8              ucSpare[35];
} MMC_INITTABLEEX_IN;

typedef struct mmc_inittableex_out
{
    MC_PATH_REF hMemHandle;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
} MMC_INITTABLEEX_OUT;



typedef struct mmc_loadtablefromfile_in
{
    ELMO_FLOAT                  fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
    NC_TRANSITION_MODE_ENUM     eTransitionMode;
    MC_BUFFERED_MODE_ENUM       eBufferMode;
    NC_MOTION_TABLE_TYPE_ENUM   eTableType;
    MC_COORD_SYSTEM_ENUM        eCoordSystem;
    ELMO_UINT16                 usAxisRef;
    MC_PATH_DATA_REF            pPathToTableFile;
} MMC_LOADTABLEFROMFILE_IN;

/*
 * eUserDefInterp means one of the types in this list (besides eUserDefInterp)
 * from CAM table. default is eQuintic.
 */
//typedef enum {eUserDefInterp=0, eQuinticInterp, eLinearInterp, eCycloidVelocityInterp, eCycloidPositionInterp, eSepticInterp, eSinusoidalTrapezAC} CURVE_TYPE_ENUM;
typedef enum {
  eTableDefInterp = 0, 
  eLinearInterp = 1, 
  ePolynom5Interp = 2, 
  ePolynom7Interp = 3, 
  eCycloidPositionInterp = 4, 
  eCycloidVelocityModified1Interp = 5, 
  eCycloidVelocityModified2Interp = 6, 
} CURVE_TYPE_ENUM;

typedef enum {eCAMT_RWMode=0, eCAMT_ROMode} CAM_TABLE_MODE_ENUM; //if eCAMT_ROMode, 'on the fly' changes are forbidden.

typedef struct _mmc_camtable_ref
{
    ELMO_DOUBLE         dbGap;                  //relevant only if gap is fixed
    ELMO_DOUBLE         dbMasterStartPosition;  //master position in CAM table first entry.
                                                //must be specified in case of fixed gap (no master column) and master position is absolute.
    MC_COORD_SYSTEM_ENUM eCoordSystem;          //currently irrelevant because group is not supported.
    ELMO_INT32          iCamTableID;            //<0 means load new table from file. otherwise it is an handle of existing table,
                                                //which was either retrieved by mmc_camtableinitcmd or previous call to mmc_camtableselect.
    CAM_TABLE_MODE_ENUM eTableMode;             //modifiable table or not.
    MC_PATH_DATA_REF    pPathToTableFile;
    ELMO_UINT8          ucSpare[32];            //spare for future use
} MC_CamRef;

typedef struct _mmc_camtableselect_in
{
    MC_CamRef   CamTable;
    ELMO_UINT32 uiStartMode;            //reserved for future use of Ramp-In and other options.
    ELMO_UINT8  ucIsMasterPosAbsolute;  //master position relative(0) or absolute(1)
    ELMO_UINT8  ucIsSlavePosAbsolute;   //slave position relative(0) or absolute(1)
    ELMO_UINT8  ucSpare[32];            //8 longs spare
} MMC_CAMTABLESELECT_IN;

typedef struct _mmc_camtableselect_out
{
    MC_PATH_REF hMemHandle;
    ELMO_UINT16 usStatus;
    ELMO_UINT16 usErrorID;
} MMC_CAMTABLESELECT_OUT;


#define NC_ECAM_MAX_ARRAY_SIZE 164

/*
typedef NC_ALIGNMENT struct _mc_motion_func {
    unsigned short _usCurveType; //!< interpolation type. only Quintic at this phase. 
    unsigned char ucSpare[32];
} MMC_CAM_MOTION_FUNC;
*/
typedef NC_ALIGNMENT struct _mmc_camtableset_in
{
    ELMO_PDOUBLE     dbTable[NC_ECAM_MAX_ARRAY_SIZE]; //164 + 6 = 170 doubles max size
    ELMO_ULINT32    ulStartIndex;
    ELMO_ULINT32    ulNumberOfPoints;
    MC_PATH_REF     hMemHandle;
    ELMO_UINT8      ucSpare[32];          //8 longs spare
} MMC_CAMTABLESET_IN;


typedef struct _mmc_camtableset_out
{
    ELMO_UINT16 usStatus;
    ELMO_UINT16 usErrorID;
} MMC_CAMTABLESET_OUT;

typedef enum {
    eECAM_SET_VALUE = 0,
    eECAM_ACTUAL_VALUE,
    eECAM_AUX_VALUE,
} ECAM_VALUE_SRC_ENUM;
typedef enum {eCAM_NON_PERIODIC, eCAM_PERIODIC,  eCAM_LINEAR} ECAM_PERIODIC_ENUM;

typedef struct _mmc_camtableinit_in
{
    MC_BUFFERED_MODE_ENUM   eBufferMode;
    ELMO_ULINT32            ulMaxNumberOfPoints;
    ELMO_ULINT32            ulUnderflowThreshold;
    CURVE_TYPE_ENUM         eCurveType;         //interpolation type. currently only Quitic (Poly-5) is supported
    ELMO_UINT16             usDimension;
    ELMO_UINT8              ucSuperimposed;
    ELMO_UINT8              ucIsFixedGap;       //mandatory factor here for memory allocation
    ELMO_UINT8              ucExecute;
    ELMO_UINT8              ucSpare[32];        //spare for future use
} MMC_CAMTABLEINIT_IN;

typedef struct _mmc_camin_in
{
    ELMO_DOUBLE              dbMasterOffset;
    ELMO_DOUBLE              dbSlaveOffset;
    ELMO_DOUBLE              dbMasterScaling;
    ELMO_DOUBLE              dbSlaveScaling;
    ELMO_DOUBLE              dbMasterStartDistance;
    ELMO_DOUBLE              dbMasterSyncPosition;
    ECAM_VALUE_SRC_ENUM     eMasterValueSource;
    MC_BUFFERED_MODE_ENUM   eBufferMode;
    ELMO_UINT32             uiStartMode;    /**< reserved for future use of Ramp-In and other options           */
    CURVE_TYPE_ENUM         eCurveType;     /**< Interpolation type. currently only Quitic (Poly-5) is supported*/
    ECAM_PERIODIC_ENUM      ePeriodicMode;
    ELMO_UINT32             uiCamTableID;
    ELMO_UINT16             usMaster;
    ELMO_UINT8              ucAutoOffset;   /**< false for user defined offsets, true for Auto offset.          */
                                            /**< Auto mode makes sure the CAM process avoid any jump            */
    ELMO_UINT8              ucExecute ;
    ELMO_UINT8              ucSpare[32];    //spare for future use
} MMC_CAMIN_IN;

typedef struct _mmc_camin_out
{
    ELMO_UINT32 uiHandle;
    ELMO_UINT32 uiEndOfProfile;//count variable increases each time the master meets the end of the table
    ELMO_UINT16 usStatus;
    ELMO_INT16  sErrorID;
} MMC_CAMIN_OUT;

typedef struct _mmc_camout_in
{
    ELMO_UINT8 ucExecute ;
} MMC_CAMOUT_IN;

typedef struct _mmc_camout_out
{
    ELMO_UINT32 uiHandle;
    ELMO_UINT16 usStatus;
    ELMO_INT16  sErrorID;
} MMC_CAMOUT_OUT;

typedef struct _mmc_camstatus_in
{
    ELMO_UINT8  ucDummy;
} MMC_CAMSTATUS_IN;

typedef struct _mmc_camstatus_out
{
    ELMO_ULINT32 ulEndOfProfile;   //counts number of exists from cam table
    ELMO_ULINT32 ulCurrentIndex;
    ELMO_ULINT32 ulCycle;
    ELMO_UINT16  usStatus;
    ELMO_INT16   sErrorID;
    ELMO_ULINT32 uiCamTableID;
    ELMO_UINT8   ucSpare[28]; //spare for future use
} MMC_CAMSTATUS_OUT;


#define ECAM_STARTMODE_BASE         0x00000000
#define ECAM_STARTMODE_RISING_EDGE  0x00000001

typedef enum _ecam_properties {eCAM_PeriodicMode} ECAM_PROPERTIES_ENUM;

typedef union {
    ELMO_DOUBLE dbVal;
    ECAM_PERIODIC_ENUM ePeriodicMode;
    CURVE_TYPE_ENUM eCurveType;
    ELMO_INT32  iVal;
    ELMO_FLOAT  fVal;
    ELMO_INT16  sVal;
    ELMO_INT8   cVal;
} ECAM_PROPERTY_VALUE;

typedef struct _mmc_camsetprop_in
{
    ECAM_PROPERTIES_ENUM eProperty;
    ECAM_PROPERTY_VALUE value;
    ELMO_UINT8 ucExecute ;
    ELMO_UINT8 ucSpare[32]; /**< spare for future use                                            */
} MMC_CAMSETPROP_IN;

typedef struct _mmc_camsetprop_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 sErrorID;
} MMC_CAMSETPROP_OUT;

typedef enum {
    eCATCH_UP = 0,
    eSLOW_DOWN = 1,
} GEAR_IN_SYNC_MODE_ENUM;


typedef struct _mmc_gearin_in
{
    ELMO_UINT16 usMaster;                       //axis reference of master
    ELMO_INT16  iRatioNumerator;                //gear ratio Numerator
    ELMO_INT16  iRatioDenominator;              //gear ratio Denominator
    ECAM_VALUE_SRC_ENUM eMasterValueSource;     //defines the source for synchronization:
                                                //mcSetValue - Synchronization on master set value
                                                //mcActualValue - Synchronization on master actual value
    GEAR_IN_SYNC_MODE_ENUM eSyncMode;           //eCATCH_UP(0), eSLOW_DOWN(1)
    ELMO_DOUBLE dbAcceleration;                 //acceleration for gearing in
    ELMO_DOUBLE dbDeceleration;                 //deceleration for gearing in
    ELMO_DOUBLE dbJerk;                         //jerk of Gearing
    MC_BUFFERED_MODE_ENUM eBufferMode;
    ELMO_UINT8 ucExecute    ;                   //start the gearing process at the rising edge.
    ELMO_UINT8 ucSpare[32];                     //spare for future use.
} MMC_GEARIN_IN;

typedef struct _mmc_gearinpos_in
{
    ELMO_UINT16 usMaster;                   //axis reference of master
    ELMO_DOUBLE dbMasterStartDistance;          //master distance for gear in procedure (distance for ramp-in)
                                                //(when the slave axis is started to get into synchronization)
    ELMO_DOUBLE dbMasterSyncPosition;           //position of the master in which the slave is in-sync with the master.
    ELMO_DOUBLE dbSlaveSyncPosition;            //slave position at which the axes are running in sync
    ELMO_INT32 iRatioNumerator;                 //gear ratio Numerator
    ELMO_INT32 iRatioDenominator;               //gear ratio Denominator
    ECAM_VALUE_SRC_ENUM eMasterValueSource;     //defines the source for synchronization:
                                                //mcSetValue - Synchronization on master set value
                                                //mcActualValue - Synchronization on master actual value
    GEAR_IN_SYNC_MODE_ENUM eSyncMode;           //eCATCH_UP(0), eSLOW_DOWN(1)
    ELMO_DOUBLE dbVelocity;
    ELMO_DOUBLE dbAcceleration;                 //acceleration for gearing in
    ELMO_DOUBLE dbDeceleration;                 //deceleration for gearing in
    ELMO_DOUBLE dbJerk;                         //jerk of Gearing
    
    MC_BUFFERED_MODE_ENUM eBufferMode;
    ELMO_UINT8 ucExecute    ;                   //start the gearing process at the rising edge
    ELMO_UINT8 ucSpare[32];                     //spare for future use
} MMC_GEARINPOS_IN;

typedef struct _mmc_gearin_out
{
    ELMO_UINT32 uiHandle;
    ELMO_UINT16 usStatus;
    ELMO_INT16  sErrorID;
} MMC_GEARIN_OUT;

typedef struct _mmc_gearinpos_out
{
    ELMO_UINT32 uiHandle;
    ELMO_UINT16 usStatus;
    ELMO_INT16  sErrorID;
} MMC_GEARINPOS_OUT;


typedef struct _mmc_gearout_in
{
    ELMO_UINT8 ucExecute    ;                   //start the disengaging process at the rising edge
} MMC_GEAROUT_IN;

typedef struct _mmc_gearout_out
{
    ELMO_UINT32 uiHandle;
    ELMO_UINT16 usStatus;
    ELMO_INT16  sErrorID;
} MMC_GEAROUT_OUT;


typedef MMC_PATHSELECT_OUT MMC_LOADTABLE_OUT;

typedef struct mmc_appendpointstotable_in
{
    ELMO_DOUBLE                  dTable[NC_PVT_ECAM_MAX_ARRAY_SIZE];
    NC_MOTION_TABLE_TYPE_ENUM   eTableType;
    MC_PATH_REF                 hMemHandle;
    ELMO_ULINT32                ulStartIndex;
    ELMO_ULINT32                ulNumberOfPoints;
    ELMO_UINT16                 usAxisRef;
    ELMO_UINT8                  ucIsTimeAbsolute;
    ELMO_UINT8                  ucIsAutoAppend;
} MMC_APPENDPOINTSTOTABLE_IN;

typedef struct mmc_appendpointstotable_out
{
    ELMO_UINT16                 usStatus;
    ELMO_INT16                  usErrorID;
} MMC_APPENDPOINTSTOTABLE_OUT;

typedef struct mmc_gettableindex_in
{
    MC_PATH_REF                 hMemHandle;
} MMC_GETTABLEINDEX_IN;

typedef struct mmc_gettableindex_out
{
    ELMO_ULINT32                ulCurrentIndex;
    ELMO_UINT16                 usStatus;
    ELMO_INT16                  usErrorID;
} MMC_GETTABLEINDEX_OUT;

typedef MMC_MOVEPATH_IN         MMC_MOVETABLE_IN;
typedef MMC_MOVEPATH_OUT        MMC_MOVETABLE_OUT;
typedef MMC_PATHUNSELECT_IN     MMC_UNLOADTABLE_IN;
typedef MMC_PATHUNSELECT_OUT    MMC_UNLOADTABLE_OUT;

MMC_LIB_API ELMO_INT32 MMC_InitTableCmd(
        MMC_CONNECT_HNDL                hConn,
        MMC_INITTABLE_IN*               pInParam,
        MMC_INITTABLE_OUT*              pOutParam);
MMC_LIB_API ELMO_INT32 MMC_InitTableExCmd(MMC_CONNECT_HNDL hConn,
                                 MMC_INITTABLEEX_IN* pInParam,
                                 MMC_INITTABLEEX_OUT* pOutParam);
MMC_LIB_API ELMO_INT32 MMC_LoadTableFromFileCmd(
        MMC_CONNECT_HNDL                hConn,
        MMC_LOADTABLEFROMFILE_IN*       pInParam,
        MMC_LOADTABLE_OUT*              pOutParam);

MMC_LIB_API ELMO_INT32 MMC_CamTableInitCmd(MMC_CONNECT_HNDL hConn,
                                 MMC_CAMTABLEINIT_IN* pInParam,
                                 MMC_INITTABLE_OUT* pOutParam);
MMC_LIB_API ELMO_INT32 MMC_CamTableSelectCmd(IN MMC_CONNECT_HNDL hConn,
                                IN MMC_CAMTABLESELECT_IN* pInParam,
                                OUT MMC_CAMTABLESELECT_OUT* pOutParam);
MMC_LIB_API ELMO_INT32 MMC_CamTableAddCmd(MMC_CONNECT_HNDL hConn,
                                   MMC_CAMTABLESET_IN* pInParam,
                                   MMC_CAMTABLESET_OUT* pOutParam);
MMC_LIB_API ELMO_INT32 MMC_CamTableSetCmd(MMC_CONNECT_HNDL hConn,
                                   MMC_CAMTABLESET_IN* pInParam,
                                   MMC_CAMTABLESET_OUT* pOutParam);
MMC_LIB_API ELMO_INT32 MMC_CamInCmd(IN MMC_CONNECT_HNDL hConn,
                                 IN MMC_AXIS_REF_HNDL hAxisRef,
                                 IN MMC_CAMIN_IN* pInParam,
                                 OUT MMC_CAMIN_OUT* pOutParam);
MMC_LIB_API ELMO_INT32 MMC_CamOutCmd(IN MMC_CONNECT_HNDL hConn,
                                 IN MMC_AXIS_REF_HNDL hAxisRef,
                                 IN MMC_CAMOUT_IN* pInParam,
                                 OUT MMC_CAMOUT_OUT* pOutParam);
MMC_LIB_API ELMO_INT32 MMC_CamStatusCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_CAMSTATUS_IN* pInParam,
        OUT MMC_CAMSTATUS_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_CamSetPropertyCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_CAMSETPROP_IN* pInParam,
        OUT MMC_CAMSETPROP_OUT* pOutParam);

/*
* only for debug. remove on release
*/
//#ifdef _DEBUG
//MMC_LIB_API int MMC_CamTablePrintCmd(MMC_CONNECT_HNDL hConn,
//                                 MMC_CAMTABLESET_IN* pInParam,
//                                 MMC_CAMTABLESET_OUT* pOutParam);
//#endif
MMC_LIB_API ELMO_INT32 MMC_AppendPointsToTableCmd(MMC_CONNECT_HNDL hConn,
                                           MMC_APPENDPOINTSTOTABLE_IN* pInParam,
                                           MMC_APPENDPOINTSTOTABLE_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_GetTableIndexCmd(
        MMC_CONNECT_HNDL                hConn,
        MMC_GETTABLEINDEX_IN*           pInParam,
        MMC_GETTABLEINDEX_OUT*          pOutParam);

MMC_LIB_API ELMO_INT32 MMC_MoveTableCmd(
        MMC_CONNECT_HNDL                hConn,
        MMC_AXIS_REF_HNDL               hAxisRef,
        MMC_MOVETABLE_IN*               pInParam,
        MMC_MOVETABLE_OUT*              pOutParam);

MMC_LIB_API ELMO_INT32 MMC_UnloadTableCmd(
        MMC_CONNECT_HNDL                hConn,
        MMC_UNLOADTABLE_IN*             pInParam,
        MMC_UNLOADTABLE_OUT*            pOutParam);

/**
 * \fn  void mmc_gearin(void *arg)
 * \brief commands a ratio between the VELOCITY of the slave and master axis.
 * \param hConn     connection handler by which the mmc library communicate with MultiAxisControl.
 * \param hAxisRef  axis reference.
 * \param pInParam  buffer to store input arguments.
 * \param pOutParam buffer to store output arguments.
 * \return none. results returned within arg buffer.
 */
MMC_LIB_API ELMO_INT32 MMC_GearInCmd(IN MMC_CONNECT_HNDL hConn,
                                 IN MMC_AXIS_REF_HNDL hAxisRef,
                                 IN MMC_GEARIN_IN* pInParam,
                                 OUT MMC_GEARIN_OUT* pOutParam);
/**
 * \fn  void mmc_gearinpos(void *arg)
 * \brief commands a gear ratio between the position of the slave and master axes from the synchronization point onwards
 * \param hConn     connection handler by which the mmc library communicate with MultiAxisControl.
 * \param hAxisRef  axis reference.
 * \param pInParam  buffer to store input arguments.
 * \param pOutParam buffer to store output arguments.
 * \return none. results returned within arg buffer.
 */
MMC_LIB_API int MMC_GearInPosCmd(IN MMC_CONNECT_HNDL hConn,
                                 IN MMC_AXIS_REF_HNDL hAxisRef,
                                 IN MMC_GEARINPOS_IN* pInParam,
                                 OUT MMC_GEARINPOS_OUT* pOutParam);
/**
 * \fn  void MMC_GearOutCmd(void *arg)
 * \brief disengage a gear between slave and master axes. actually MC_Stop at this stage. 
 * \param hConn     connection handler by which the mmc library communicate with MultiAxisControl.
 * \param hAxisRef  axis reference.
 * \param pInParam  buffer to store input arguments.
 * \param pOutParam buffer to store output arguments.
 * \return none. results returned within arg buffer.
 */
MMC_LIB_API int MMC_GearOutCmd(IN MMC_CONNECT_HNDL hConn,
                                 IN MMC_AXIS_REF_HNDL hAxisRef,
                                 IN MMC_GEAROUT_IN* pInParam,
                                 OUT MMC_GEAROUT_OUT* pOutParam);        


/*--------------------------------------
*   table info API
*/
#define MMC_MAX_JOURNAL_ENTRIES 20
#define MMC_TABLE_FILE_LENGTH   20  //max length for table file name (exluded from path)


typedef struct o_table_list {
    ELMO_UINT32 _uiHandlers[MMC_MAX_JOURNAL_ENTRIES];   //list of table handlers
    ELMO_INT32  _iNumber;                                       //number of found tables
    ELMO_UINT16 usStatus;
    ELMO_INT16  sErrorID;
} MMC_TABLE_LIST_OUT;
typedef struct i_table_list {
    NC_MOTION_TABLE_TYPE_ENUM eTableType;
} MMC_TABLE_LIST_IN;

typedef struct o_table_data {
    ELMO_INT8   _name[MMC_TABLE_FILE_LENGTH+1];
    ELMO_UINT16 usStatus;
    ELMO_INT16  sErrorID;
} MMC_TABLE_DATA_OUT;

typedef struct i_table_list_data {
    ELMO_UINT32 uiHandler;
} MMC_TABLE_DATA_IN;

/**
* \fn int MMC_GetTableList(
*               IN MMC_CONNECT_HNDL hConn,
*               IN MMC_TABLE_LIST_IN* pInParam,
*               OUT MMC_TABLE_LIST_OUT* pOutParam)
* \brief this function get a list of table for given table type.
* \param  hConn -    [IN] connection handle
* \param  hAxisRef - [IN] axis reference handle
* \param  pInParam - [IN] input parameters.
* \param  pOutParam - [OUT] output parameters.
* \return   return - 0 if success otherwise error.
*/
MMC_LIB_API ELMO_INT32 MMC_GetTableList(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_TABLE_LIST_IN* pInParam,
        OUT MMC_TABLE_LIST_OUT* pOutParam);

/**
* \fn int MMC_GetTableInfo(
*               IN MMC_CONNECT_HNDL hConn,
*               IN MMC_AXIS_REF_HNDL hAxisRef,
*               IN MMC_TABLE_DATA_IN* pInParam,
*				OUT MMC_TABLE_DATA_OUT* pOutParam)
* \brief this function get table info (currently name only) for given table handler.
* \param  hConn -    [IN] connection handle
* \param  pInParam - [IN] input parameters.
* \param  pOutParam - [OUT] output parameters.
* \return   return - 0 if success otherwise error.
*/
MMC_LIB_API ELMO_INT32 MMC_GetTableInfo(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_TABLE_DATA_IN* pInParam,
        OUT MMC_TABLE_DATA_OUT* pOutParam);

#ifdef __cplusplus
}
#endif

#endif /* MMC_PVT_API_H_ */

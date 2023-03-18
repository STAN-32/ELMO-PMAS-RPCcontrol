////////////////////////////////////////////////////////////////////////////////
/// \file MMC_PLCopen_single_API.h
/// Name        : MMC_PLCopen_single_API.h
/// Author      : Barak R
/// Created on  : April 19, 20010
/// Version     : 0.0.1
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.4.2 Updated 26Aug2019 Haim H.
///               0.4.4 Updated 16Nov2020 Haim H.
///               0.4.5 Updated 20Apr2021 Haim H. Updates according to update in "Gen C lib in Plastic"
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_PLCOPEN_SINGLE_API_H
#define MMC_PLCOPEN_SINGLE_API_H

#ifdef __cplusplus
 extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// Axis Status Bit Mask
///////////////////////////////////////////////////////////////////////////////
#define NC_AXIS_IN_ERROR_REACTION           0x00080000  ///< Axis\Group is currently in error reaction bit Mask
#define NC_AXIS_BUSY_MASK                   0x00000800  ///< Axis Busy State Bit Mask.
#define NC_AXIS_ERROR_STOP_MASK             0x00000400  ///< Axis Error Stop State Bit Mask.
#define NC_AXIS_DISABLED_MASK               0x00000200  ///< Axis Disabled State Bit Mask.
#define NC_AXIS_STOPPING_MASK               0x00000100  ///< Axis Stopping State Bit Mask.
#define NC_AXIS_STAND_STILL_MASK            0x00000080  ///< Axis Stand Still State Bit Mask.
#define NC_AXIS_DISCRETE_MOTION_MASK        0x00000040  ///< Axis Discrete Motion State Bit Mask.
#define NC_AXIS_CONTINUOUS_MOTION_MASK      0x00000020  ///< Axis Continuous Motion State Bit Mask.
#define NC_AXIS_SYNCHRONIZED_MOTION_MASK    0x00000010  ///< Axis Synchronized Motion State Bit Mask.
#define NC_AXIS_HOMING_MASK                 0x00000008  ///< Axis Homing State Bit Mask.
#define NC_AXIS_CONSTANT_VELOCITY_MASK      0x00000004  ///< Axis Constant Velocity State Bit Mask.
#define NC_AXIS_ACCELERATING_MASK           0x00000002  ///< Axis Accelerating State Bit Mask.
#define NC_AXIS_DECELERATING_MASK           0x00000001  ///< Axis Decelerating State Bit Mask.

///////////////////////////////////////////////////////////////////////////////
// Axis Status Bit Mask
///////////////////////////////////////////////////////////////////////////////



//////////// structures

///////////////////////////////////////////////////////////////////////////////
/// \enum MC_SWITCH_MODE_ENUM
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
    MC_ON,
    MC_OFF,
    MC_EDGE_ON,
    MC_EDGE_OFF,
    MC_EDGE_SWITCH_POSITIVE,
    MC_EDGE_SWITCH_NEGATIVE
}MC_SWITCH_MODE_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum MC_HOME_DIRECTION_ENUM
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
    MC_POSITIVE,
    MC_NEGATIVE,
    MC_SWITCH_POSITIVE,
    MC_SWITCH_NEGATIVE,
}MC_HOME_DIRECTION_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum MMC_HOME_MODE_ENUM
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef enum {
    MC_ABS_SWITCH,
    MC_LIMIT_SWITCH,
    MC_REF_PULSE,
    MC_DIRECT,
    MC_BLOCK,
}MMC_HOME_MODE_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEABSOLUTE_IN
/// \brief Move Absolute Command input data structure.
///
/// (See : "Technical Specification
///     PLCopen - Technical Committee 2 – Task Force
///     Function blocks for motion control")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbPosition;                  ///< Target position for the motion (in technical unit [u]) (negative or positive)
    ELMO_FLOAT fVelocity;                    ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_FLOAT fAcceleration;                ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_FLOAT fDeceleration;                ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_FLOAT fJerk;                        ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enumerator type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
} MMC_MOVEABSOLUTE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEABSOLUTE_OUT
/// \brief Move Absolute Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
} MMC_MOVEABSOLUTE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEABSOLUTEEX_IN
/// \brief Move Absolute Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbPosition;                  ///< Target position for the motion (in technical unit [u]) (negative or positive)
    ELMO_DOUBLE dVelocity;                   ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_DOUBLE dAcceleration;               ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_DOUBLE dDeceleration;               ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_DOUBLE dJerk;                       ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enumerator type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
} MMC_MOVEABSOLUTEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEABSOLUTEEX_OUT
/// \brief Move Absolute Extended Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
} MMC_MOVEABSOLUTEEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEADDITIVE_IN
/// \brief Move Additive Command input data structure.
///
/// (See : "Technical Specification
///     PLCopen - Technical Committee 2 – Task Force
///     Function blocks for motion control")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbDistance;                  ///< Relative distance for the motion (in technical unit [u])
    ELMO_FLOAT fVelocity;                    ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_FLOAT fAcceleration;                ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_FLOAT fDeceleration;                ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_FLOAT fJerk;                        ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enum type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
}MMC_MOVEADDITIVE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEADDITIVE_OUT
/// \brief Move Additive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_MOVEADDITIVE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEADDITIVEEX_IN
/// \brief Move Additive Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbDistance;                  ///< Relative distance for the motion (in technical unit [u])
    ELMO_DOUBLE dVelocity;                   ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_DOUBLE dAcceleration;               ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_DOUBLE dDeceleration;               ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_DOUBLE dJerk;                       ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enum type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
}MMC_MOVEADDITIVEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEADDITIVEEX_OUT
/// \brief Move Additive Extended Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_MOVEADDITIVEEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVERELATIVE_IN
/// \brief Move Relative Command input data structure.
///
/// (See : "Technical Specification
///     PLCopen - Technical Committee 2 – Task Force
///     Function blocks for motion control")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbDistance;                  ///< Relative distance for the motion (in technical unit [u])
    ELMO_FLOAT fVelocity;                    ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_FLOAT fAcceleration;                ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_FLOAT fDeceleration;                ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_FLOAT fJerk;                        ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enum type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
}MMC_MOVERELATIVE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVERELATIVE_OUT
/// \brief Move Relative Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_MOVERELATIVE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVERELATIVEEX_IN
/// \brief Move Relative Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbDistance;                  ///< Relative distance for the motion (in technical unit [u])
    ELMO_DOUBLE dVelocity;                   ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_DOUBLE dAcceleration;               ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_DOUBLE dDeceleration;               ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_DOUBLE dJerk;                       ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enum type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
}MMC_MOVERELATIVEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVERELATIVEEX_OUT
/// \brief Move Relative Extended Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_MOVERELATIVEEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEVELOCITY_IN
/// \brief Move Velocity Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_FLOAT fVelocity;
    ELMO_FLOAT fAcceleration;
    ELMO_FLOAT fDeceleration;
    ELMO_FLOAT fJerk;
    MC_DIRECTION_ENUM eDirection;
    MC_BUFFERED_MODE_ENUM eBufferMode;
    ELMO_UINT8 ucExecute;
}MMC_MOVEVELOCITY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEVELOCITY_OUT
/// \brief Move Velocity Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_MOVEVELOCITY_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEVELOCITYEX_IN
/// \brief Move Velocity Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dVelocity;
    ELMO_DOUBLE dAcceleration;
    ELMO_DOUBLE dDeceleration;
    ELMO_DOUBLE dJerk;
    MC_DIRECTION_ENUM eDirection;
    MC_BUFFERED_MODE_ENUM eBufferMode;
    ELMO_UINT8 ucExecute;
}MMC_MOVEVELOCITYEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEVELOCITYEX_OUT
/// \brief Move Velocity Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_MOVEVELOCITYEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECONTINUOUS_IN
/// \brief Move Continuous Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbDistance;
    ELMO_FLOAT fVelocity;
    ELMO_FLOAT fEndVelocity;
    ELMO_FLOAT fAcceleration;
    ELMO_FLOAT fDeceleration;
    ELMO_FLOAT fJerk;
    MC_BUFFERED_MODE_ENUM eBufferMode;
    ELMO_UINT8 ucExecute;
}MMC_MOVECONTINUOUS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECONTINUOUS_OUT
/// \brief Move Continuous Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_MOVECONTINUOUS_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_HOME_IN
/// \brief Home Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbPosition;
    ELMO_FLOAT fAcceleration;
    ELMO_FLOAT fVelocity;
    ELMO_FLOAT fDistanceLimit;
    ELMO_FLOAT fTorqueLimit;
    MMC_HOME_MODE_ENUM eHomingMode;
    MC_BUFFERED_MODE_ENUM eBufferMode;
    MC_HOME_DIRECTION_ENUM eDirection;
    MC_SWITCH_MODE_ENUM eSwitchMode;
    ELMO_UINT32 uiTimeLimit;
    ELMO_UINT8 ucExecute;
}MMC_HOME_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_HOME_OUT
/// \brief Home Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_HOME_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_HOMEDS402_IN
/// \brief Home DS402 Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbPosition;
    ELMO_FLOAT fAcceleration;
    ELMO_FLOAT fVelocity;
    ELMO_FLOAT fDistanceLimit;
    ELMO_FLOAT fTorqueLimit;
    MC_BUFFERED_MODE_ENUM eBufferMode;
    ELMO_INT32 uiHomingMethod;
    ELMO_UINT32 uiTimeLimit;
    ELMO_UINT8 ucExecute;
}MMC_HOMEDS402_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_HOMEDS402EX_IN
/// \brief Home DS402EX Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_homeds402ex_in
{
    ELMO_DOUBLE dbPosition;
    ELMO_DOUBLE dbDetectionVelocityLimit;
    ELMO_FLOAT fAcceleration;
    ELMO_FLOAT fVelocityHi;   //speed search for switch
    ELMO_FLOAT fVelocityLo;   //speed search for zero
    ELMO_FLOAT fDistanceLimit;
    ELMO_FLOAT fTorqueLimit;
    MC_BUFFERED_MODE_ENUM eBufferMode;
    ELMO_INT32 uiHomingMethod;
    ELMO_UINT32 uiTimeLimit;
    ELMO_UINT32 uiDetectionTimeLimit;
    ELMO_UINT8 ucExecute;
    ELMO_UINT8 ucSpares[32]; //future usage
} MMC_HOMEDS402EX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READACTUALPOSITION_IN
/// \brief Read Actual Position Command input data structure.
///
/// (See : " Technical Specification
///     PLCopen - Technical Committee 2 – Task Force
///     Function blocks for motion control")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 ucEnable;        ///< Get the value of the parameter continuously while enabled
}MMC_READACTUALPOSITION_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READACTUALPOSITION_OUT
/// \brief Read Actual Position Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbPosition;      ///<New absolute position (in axis’ unit [u])
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_READACTUALPOSITION_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READACTUALVELOCITY_IN
/// \brief Read Actual Velocity Command input data structure.
///
/// (See : " Technical Paper
///     PLCopen Technical Committee
///     Function Blocks for motion control:
///     Part 2 - Extensions")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 ucEnable;        ///< Get the value of the parameter continuously while enabled
}MMC_READACTUALVELOCITY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READACTUALVELOCITY_OUT
/// \brief Read Actual Velocity Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dVelocity;       ///< The value of the actual velocity (in axis’ unit [u/s])
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_READACTUALVELOCITY_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READAXISERROR_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 ucEnable;
}MMC_READAXISERROR_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READAXISERROR_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
    ELMO_UINT16 usAxisErrorID;
    ELMO_UINT16 usLastEmergencyErrCode;
}MMC_READAXISERROR_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_HALT_IN
/// \brief Halt Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_FLOAT fDeceleration;
    ELMO_FLOAT fJerk;
    MC_BUFFERED_MODE_ENUM eBufferMode;
    ELMO_UINT8 ucExecute;
}MMC_HALT_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_HALT_OUT
/// \brief Halt Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_HALT_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READDIGITALINPUT_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_INT32 iInputNumber;
    ELMO_UINT8 ucEnable;
}MMC_READDIGITALINPUT_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READDIGITALINPUT_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
    ELMO_UINT8 ucValue;
}MMC_READDIGITALINPUT_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READDIGITALINPUTS_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 ucEnable;
}MMC_READDIGITALINPUTS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READDIGITALINPUTS_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    uint32_t	ulValue;
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
}MMC_READDIGITALINPUTS_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READDIGITALOUTPUT_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_readdigitaloutput_in
{
    ELMO_INT32 iOutputNumber;
    ELMO_UINT8 ucEnable;
}MMC_READDIGITALOUTPUT_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READDIGITALOUTPUT_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_readdigitaloutput_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
    ELMO_UINT8 ucValue;
}MMC_READDIGITALOUTPUT_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_WRITEDIGITALOUTPUT_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_writedigitaloutput_in
{
    ELMO_INT32 iOutputNumber;
    ELMO_UINT8 ucEnable;
    ELMO_UINT8 ucValue;
}MMC_WRITEDIGITALOUTPUT_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_WRITEDIGITALOUTPUT_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_writedigitaloutput_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
}MMC_WRITEDIGITALOUTPUT_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READDIGITALOUTPUT32Bit_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_readdigitaloutput32Bit_in
{
    ELMO_INT32 iOutputNumber;
    ELMO_UINT8 ucEnable;
}MMC_READDIGITALOUTPUT32Bit_IN;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READDIGITALOUTPUT32Bit_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_readdigitaloutput32Bit_out
{
    uint32_t	ulValue;
    ELMO_UINT16 usStatus;
    ELMO_INT16 	usErrorID;
}MMC_READDIGITALOUTPUT32Bit_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_WRITEDIGITALOUTPUT32Bit_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_writedigitaloutput32Bit_in
{
    ELMO_INT32	iOutputNumber;
    uint32_t	ulValue;
    ELMO_UINT8	ucEnable;
}MMC_WRITEDIGITALOUTPUT32Bit_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_WRITEDIGITALOUTPUT32Bit_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_writedigitaloutput32Bit_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
}MMC_WRITEDIGITALOUTPUT32Bit_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETPOSITION_IN
/// \brief Set Position Command input data structure.
///
/// (See : "Technical Paper
///     PLCopen Technical Committee
///     Function Blocks for motion control:
///     Part 2 - Extensions")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbPosition;
    MC_EXECUTION_MODE eExecutionMode;
    ELMO_UINT8 ucPosMode; // abs mode = 0. relative mode = 1.
    ELMO_UINT8 ucExecute;
} MMC_SETPOSITION_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETPOSITION_OUT
/// \brief Set Position Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
} MMC_SETPOSITION_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_STOP_IN
/// \brief Stop Command input data structure.
///
/// (See : "Technical Specification
///     PLCopen - Technical Committee 2 – Task Force
///     Function blocks for motion control")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_FLOAT fDeceleration;    ///< Value of the deceleration [u/s2]
    ELMO_FLOAT fJerk;            ///< Value of the Jerk [u/s3]
    MC_BUFFERED_MODE_ENUM eBufferMode;  ///< Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT8 ucExecute;       ///< Start the action at rising edge
}MMC_STOP_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_STOP_OUT
/// \brief Stop Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
}MMC_STOP_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESET_IN
/// \brief Reset Command input data structure.
///
/// (See : "Technical Specification
///     PLCopen - Technical Committee 2 – Task Force
///     Function blocks for motion control")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 ucExecute;
}MMC_RESET_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESET_OUT
/// \brief Reset Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
}MMC_RESET_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READSTATUS_IN
/// \brief Read Axis Status Command input data structure.
///
/// (See : "Technical Specification
///     PLCopen - Technical Committee 2 – Task Force
///     Function blocks for motion control")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32  uiHndlr;       ///< Requested Axis handle.
    ELMO_UINT8 ucEnable;        ///< Get the value of the parameter continuously while enabled
} MMC_READSTATUS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READSTATUS_OUT
/// \brief Read Axis Status Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    /* HH unsigned long ulState;    */      ///< Axis state.
	uint32_t ulState;			///< Axis state.

    ELMO_UINT16 usStatus;        ///< Returned command status.
    ELMO_INT16 usErrorID;        ///< Returned command error ID.
    ELMO_UINT16 usAxisErrorID;   ///< Axis error ID.
    ELMO_UINT16 usStatusWord;    ///< Drive Status Word.
} MMC_READSTATUS_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_POWER_IN
/// \brief Power On Command input data structure.
///
/// (See : "Technical Specification
///     PLCopen - Technical Committee 2 – Task Force
///     Function blocks for motion control")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    MC_BUFFERED_MODE_ENUM eBufferMode;
    ELMO_UINT8 ucEnable;
    ELMO_UINT8 ucEnablePositive;
    ELMO_UINT8 ucEnableNegative;
    ELMO_UINT8 ucExecute;
} MMC_POWER_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_POWER_OUT
/// \brief Power On Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;       ///< Returned function block handle.
    ELMO_UINT16 usStatus;       ///< Returned command status.
    ELMO_INT16 usErrorID;       ///< Returned command error ID.
} MMC_POWER_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETFBDEPTH_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32  uiHndl;
}MMC_GETFBDEPTH_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETFBDEPTH_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32  uiFbInQ;
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
}MMC_GETFBDEPTH_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READACTUALTORQUE_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 ucEnable;
}MMC_READACTUALTORQUE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READACTUALTORQUE_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dActualTorque;
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
    ELMO_UINT8 ucValid;
}MMC_READACTUALTORQUE_OUT;

/* Added by Alex - Integration of MoveRepetitive() */
///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEABSOLUTEREPETITIVE_IN
/// \brief Move Absolute Repetitive Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbPosition;                  ///< Target position for the motion (in technical unit [u]) (negative or positive)
    ELMO_FLOAT fVelocity;                    ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_FLOAT fAcceleration;                ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_FLOAT fDeceleration;                ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_FLOAT fJerk;                        ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enumerator type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT32  uiExecDelayMs;             ///< Defines the delay between 2 blocks (?)
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
} MMC_MOVEABSOLUTEREPETITIVE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEABSOLUTEREPETITIVE_OUT
/// \brief Move Absolute Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;                   ///< Returned function block handle.
    ELMO_UINT16 usStatus;                   ///< Returned command status.
    ELMO_INT16 usErrorID;                   ///< Returned command error ID.
} MMC_MOVEABSOLUTEREPETITIVE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEABSOLUTEREPETITIVEEX_IN
/// \brief Move Absolute Repetitive Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbPosition;                  ///< Target position for the motion (in technical unit [u]) (negative or positive)
    ELMO_DOUBLE dVelocity;                   ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_DOUBLE dAcceleration;               ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_DOUBLE dDeceleration;               ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_DOUBLE dJerk;                       ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enumerator type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT32  uiExecDelayMs;             ///< Defines the delay between 2 blocks (?)
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
} MMC_MOVEABSOLUTEREPETITIVEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEABSOLUTEREPETITIVEEX_OUT
/// \brief Move Absolute Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;                   ///< Returned function block handle.
    ELMO_UINT16 usStatus;                   ///< Returned command status.
    ELMO_INT16 usErrorID;                   ///< Returned command error ID.
} MMC_MOVEABSOLUTEREPETITIVEEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVERELATIVEREPETITIVE_IN
/// \brief Move Relative Repetitive Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbDistance;                  ///< Target position for the motion (in technical unit [u]) (negative or positive)
    ELMO_FLOAT fVelocity;                    ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_FLOAT fAcceleration;                ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_FLOAT fDeceleration;                ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_FLOAT fJerk;                        ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enumerator type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT32  uiExecDelayMs;             ///< Defines the delay between 2 blocks (?)
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
} MMC_MOVERELATIVEREPETITIVE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVERELATIVEREPETITIVE_OUT
/// \brief Move Absolute Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;                   ///< Returned function block handle.
    ELMO_UINT16 usStatus;                   ///< Returned command status.
    ELMO_INT16          usErrorID;          ///< Returned command error ID.
} MMC_MOVERELATIVEREPETITIVE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVERELATIVEREPETITIVEEX_IN
/// \brief Move Relative Repetitive Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbDistance;                  ///< Target position for the motion (in technical unit [u]) (negative or positive)
    ELMO_DOUBLE dVelocity;                   ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_DOUBLE dAcceleration;               ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_DOUBLE dDeceleration;               ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_DOUBLE dJerk;                       ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enumerator type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT32  uiExecDelayMs;             ///< Defines the delay between 2 blocks (?)
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
} MMC_MOVERELATIVEREPETITIVEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVERELATIVEREPETITIVEEX_OUT
/// \brief Move Absolute Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;                   ///< Returned function block handle.
    ELMO_UINT16 usStatus;                   ///< Returned command status.
    ELMO_INT16          usErrorID;          ///< Returned command error ID.
} MMC_MOVERELATIVEREPETITIVEEX_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEADDITIVEREPETITIVE_IN
/// \brief Move Additive Repetitive Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbDistance;                  ///< Target position for the motion (in technical unit [u]) (negative or positive)
    ELMO_FLOAT fVelocity;                    ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_FLOAT fAcceleration;                ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_FLOAT fDeceleration;                ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_FLOAT fJerk;                        ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enumerator type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT32  uiExecDelayMs;             ///< Defines the delay between 2 blocks (?)
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
} MMC_MOVEADDITIVEREPETITIVE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEADDITIVEREPETITIVE_OUT
/// \brief Move Additive Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;                   ///< Returned function block handle.
    ELMO_UINT16 usStatus;                   ///< Returned command status.
    ELMO_INT16          usErrorID;          ///< Returned command error ID.
} MMC_MOVEADDITIVEREPETITIVE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEADDITIVEREPETITIVE_IN
/// \brief Move Additive Repetitive Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbDistance;                  ///< Target position for the motion (in technical unit [u]) (negative or positive)
    ELMO_DOUBLE dVelocity;                   ///< Value of the maximum velocity (always positive) (not necessarily reached) [u/s].
    ELMO_DOUBLE dAcceleration;               ///< Value of the acceleration (always positive) (increasing energy of the motor) [u/s2]
    ELMO_DOUBLE dDeceleration;               ///< Value of the deceleration (always positive) (decreasing energy of the motor) [u/s2]
    ELMO_DOUBLE dJerk;                       ///< Value of the Jerk [u/s3]. (always positive)
    MC_DIRECTION_ENUM eDirection;           ///< MC_Direction Enumerator type (1-of-4 values: positive_direction, shortest_way, negative_direction, current_direction)
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode Defines the behavior of the axis: modes are Aborting, Buffered, Blending
    ELMO_UINT32  uiExecDelayMs;             ///< Defines the delay between 2 blocks (?)
    ELMO_UINT8 ucExecute;                   ///< Start the motion at rising edge
} MMC_MOVEADDITIVEREPETITIVEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEADDITIVEREPETITIVEEX_OUT
/// \brief Move Additive Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;                   ///< Returned function block handle.
    ELMO_UINT16 usStatus;                   ///< Returned command status.
    ELMO_INT16          usErrorID;          ///< Returned command error ID.
} MMC_MOVEADDITIVEREPETITIVEEX_OUT;


typedef struct mmc_positionprofile_in
{
    MC_BUFFERED_MODE_ENUM eBufferMode;
    MC_PATH_REF hMemHandle;
    ELMO_UINT8 ucExecute;
} MMC_POSITIONPROFILE_IN;

typedef struct mmc_positionprofile_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
} MMC_POSITIONPROFILE_OUT;

/// Touch Probe Modes:
///--------------------
enum
{
    eMMC_TOUCHPROBE_POS_EDGE = 0,
    eMMC_TOUCHPROBE_NEG_EDGE
};

typedef struct mmc_touchprobeenable_in
{
    ELMO_UINT8 ucExecute;
    ELMO_UINT8 ucTriggerType;
}MMC_TOUCHPROBEENABLE_IN;

typedef struct mmc_touchprobeenable_out
{
    //ELMO_UINT32 uiHndl;
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
}MMC_TOUCHPROBEENABLE_OUT;

typedef struct mmc_touchprobedisable_in
{
    ELMO_UINT8 ucExecute;
}MMC_TOUCHPROBEDISABLE_IN;

typedef struct mmc_touchprobedisable_out
{
    //ELMO_UINT32 uiHndl;
    ELMO_UINT16 usStatus;
    ELMO_INT16 usErrorID;
}MMC_TOUCHPROBEDISABLE_OUT;


typedef struct mmc_touchprobeenable_ex_in
{
	uint32_t  	 ulShmArraySizeAlloc;	// 2-100000
	ELMO_UINT16  usConfig;     			// Enabled = 0x1, Continuous Mode = 0x2 , Rising Edge = 0x10 , Falling edge = 0x20
	ELMO_UINT16  usSpare[9];
}MMC_TOUCHPROBEENABLE_EX_IN;

typedef struct mmc_touchprobeenable_ex_out
{
	ELMO_UINT16  usTPIndex;  			// Global TP mechanism index (0-5).
	ELMO_UINT16  usDummy;
	ELMO_UINT16  usStatus;
	ELMO_INT16   sErrorID;
}MMC_TOUCHPROBEENABLE_EX_OUT;

typedef struct mmc_touchprobedisable_ex_in
{
	ELMO_INT16   sTPIndex;               // Global TP mechanism index (0-5), or -1 for disabling all Touch Probe mechanisms
	ELMO_INT16   sSpare[11];
}MMC_TOUCHPROBEDISABLE_EX_IN;

typedef struct mmc_touchprobedisable_ex_out
{
	ELMO_UINT16  usStatus;
	ELMO_INT16   sErrorID;
}MMC_TOUCHPROBEDISABLE_EX_OUT;

typedef struct mmc_gettouchprobestatus_in
{
	ELMO_UINT16  usSpare[10];
}MMC_GETTOUCHPROBESTATUS_IN;

typedef struct mmc_gettouchprobestatus_out
{
	uint32_t  	 ulExistingPoints[6];     // updated # of existing points in the array.
	uint32_t  	 ulTPEvtCnt[6];	        // total # of Touch Probe events that occurred.
	uint32_t  	 ulShmArraySizeAlloc[6]; // 2-100000
	ELMO_UINT16  usMissedTPFlag[6];
	ELMO_UINT16  usOverflowTPFlag[6];
	ELMO_UINT16  usAxisRef[6];
	ELMO_INT16   sConfig[6];     		// Enabled = 0x1, Continuous Mode = 0x2 , Rising Edge = 0x10 , Falling edge = 0x20, or error number (< 0)
	ELMO_UINT16  usStatus;
	ELMO_INT16   sErrorID;
}MMC_GETTOUCHPROBESTATUS_OUT;

typedef struct mmc_gettouchprobedata_in
{
	ELMO_UINT16  usTPIndex;  			// Global TP mechanism index (0-5)
	ELMO_UINT16  usNumOfPoints;   		// 1-350
	ELMO_UINT16  usSpare[10];
}MMC_GETTOUCHPROBEDATA_IN;

typedef struct mmc_gettouchprobedata_out
{
	uint32_t  	 ulExistingPoints;       	// updated # of existing points in the array.
	uint32_t  	 ulTPEvtCnt;	        	// total # of Touch Probe events that occurred.
	ELMO_DOUBLE  dUURatio;		        // UU conversion factor
	int32_t  	 lData[350];				// Data in indexes above usCopiedPoints are irrelevant
	ELMO_UINT16  usCopiedPoints;      	// 1-350
	ELMO_UINT16  usMissedTPFlag;
	ELMO_UINT16  usOverflowTPFlag;
	ELMO_INT16   sDummy;
	ELMO_UINT16  usStatus;
	ELMO_INT16   sErrorID;
}MMC_GETTOUCHPROBEDATA_OUT;

typedef struct
{
	uint32_t  	 ulExistingPoints;       	// updated # of existing points in the array.
	uint32_t  	 ulTPEvtCnt;	        	// total # of Touch Probe events that occurred.
	ELMO_DOUBLE  dUURatio;		        // UU conversion factor
}MMC_GETTOUCHPROBEDATA_OUT_1;

typedef struct
{
	uint32_t  	 ulExistingPoints;       	// updated # of existing points in the array.
	uint32_t  	 ulTPEvtCnt;	        	// total # of Touch Probe events that occurred.
	ELMO_DOUBLE  dUURatio;		        // UU conversion factor
	int32_t  	 lData[350];				// Data in indexes above usCopiedPoints are irrelevant
}MMC_GETTOUCHPROBEDATA_OUT_2;

typedef struct
{
	uint32_t  	 ulExistingPoints;       	// updated # of existing points in the array.
	uint32_t  	 ulTPEvtCnt;	        	// total # of Touch Probe events that occurred.
	ELMO_DOUBLE  dUURatio;		        // UU conversion factor
	int32_t  	 lData[350];				// Data in indexes above usCopiedPoints are irrelevant
	ELMO_UINT16  usCopiedPoints;      	// 1-350
	ELMO_UINT16  usMissedTPFlag;
}MMC_GETTOUCHPROBEDATA_OUT_3;

typedef struct
{
	uint32_t  	 ulExistingPoints;       	// updated # of existing points in the array.
	uint32_t  	 ulTPEvtCnt;	        	// total # of Touch Probe events that occurred.
	ELMO_DOUBLE  dUURatio;		        // UU conversion factor
	ELMO_UINT16  usCopiedPoints;      	// 1-350
	ELMO_UINT16  usMissedTPFlag;
	ELMO_UINT16  usOverflowTPFlag;
	ELMO_INT16   sDummy;
	ELMO_UINT16  usStatus;
	ELMO_INT16   sErrorID;
}MMC_GETTOUCHPROBEDATA_OUT_WITHOUT_LDATA;

typedef struct
{
	uint32_t  	 ulExistingPoints;       	// updated # of existing points in the array.
	uint32_t  	 ulTPEvtCnt;	        	// total # of Touch Probe events that occurred.
	int32_t  	 lData[350];				// Data in indexes above usCopiedPoints are irrelevant
	ELMO_UINT16  usCopiedPoints;      	// 1-350
	ELMO_UINT16  usMissedTPFlag;
	ELMO_UINT16  usOverflowTPFlag;
	ELMO_INT16   sDummy;
	ELMO_UINT16  usStatus;
	ELMO_INT16   sErrorID;
}MMC_GETTOUCHPROBEDATA_OUT_WITHOUT_DOUBLE;

typedef struct mmc_touchprobestop_in
{
	ELMO_UINT16  usTPIndex;             // Global TP mechanism index (0-5)
	ELMO_INT16   sSpare[11];
}MMC_TOUCHPROBESTOP_IN;

typedef struct mmc_touchprobestop_out
{
	ELMO_UINT16  usStatus;
	ELMO_INT16   sErrorID;
}MMC_TOUCHPROBESTOP_OUT;

typedef struct mmc_touchprobestart_in
{
	ELMO_UINT16  usTPIndex;             // Global TP mechanism index (0-5)
	ELMO_UINT16  usTriggerType;         // 1 = Rising Edge,  0 = Falling Edge
	ELMO_INT16   sSpare[10];
}MMC_TOUCHPROBESTART_IN;

typedef struct mmc_touchprobestart_out
{
	ELMO_UINT16  usStatus;
	ELMO_INT16   sErrorID;
}MMC_TOUCHPROBESTART_OUT;


///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MMC_ACC_FF_X_AXIS_REF_INDEX  = 0,	//self-coefficient or axis-ref
	MMC_ACC_FF_Y_AXIS_REF_INDEX  = 1,
	MMC_ACC_FF_Z_AXIS_REF_INDEX  = 2,
	MMC_MAX_ACC_FF_AXES_REF = 3

}ACC_FF_AXIS_REF_INDEX_ENUM;

typedef struct
{
	ELMO_DOUBLE dAccCoef[MMC_MAX_ACC_FF_AXES_REF];
	ELMO_DOUBLE dVelCoef[MMC_MAX_ACC_FF_AXES_REF];

} MMC_ACC_FF_COEF_ENHANCED;

typedef struct
{
	MMC_ACC_FF_COEF_ENHANCED stEnhanced;
	ELMO_DOUBLE dGantryCoef;
	ELMO_DOUBLE dGantryOffset;

} MMC_ACC_FF_COEF_GANTRY;	// when dAccCoef[MMC_ACC_FF_X_AXIS_REF_INDEX] isn't constant, and depends on axisYpos

typedef union
{
	ELMO_DOUBLE					dAccCoef[MMC_MAX_ACC_FF_AXES_REF]; // 24 bytes
	MMC_ACC_FF_COEF_ENHANCED 	stEnhanced;  	  // 48 bytes
	MMC_ACC_FF_COEF_GANTRY 		stGantry;     	  // 64 bytes
	ELMO_UINT8 					ucMaxSize[128];

} MMC_ACC_FF_COEF_UNION;

typedef enum
{
	ACC_FF_NONE     = 0,
	ACC_FF_SIMPLE   = 1,
	ACC_FF_ENHANCED = 2,
	ACC_FF_GANTRY   = 3,
	ACC_FF_SPARE1   = 4,
	ACC_FF_SPARE2   = 5,

} ACC_FF_MODE_ENUM;

typedef enum
{
	ACC_FF_ERASE    = -1,
	ACC_FF_DISABLE  = 0,
	ACC_FF_ENABLE   = 1,

} ACC_FF_ENABLE_ENUM;

typedef struct
{
	ELMO_UINT16 usAxisRefs[4];		// axis refs: X, Y, Z, spare/padding
	ELMO_INT32  iAccFFMode;
    ELMO_LINT32 lSpare[21];
    MMC_ACC_FF_COEF_UNION u_CoefAccFF;	// typically up to 64 bytes (max=128)

} MMC_SETACCFFMODE_IN;					// typically up to 160 bytes (max=224)

typedef struct
{
	ELMO_UINT16  usAccFFIndex;  // Global AccFF mechanism index (0-4).
	ELMO_UINT16  usDummy;
	ELMO_UINT16  usStatus;
	ELMO_INT16  sErrorID;

} MMC_SETACCFFMODE_OUT;


typedef struct
{
	ELMO_UINT16  usSpare[10];

}MMC_GETACCFFINFO_IN;

typedef struct
{
	ELMO_UINT16 usAxisRefs[4];		// axis refs: X, Y, Z, padding
	ELMO_INT32  iAccFFMode;
    ELMO_LINT32 lSpare[21];
    MMC_ACC_FF_COEF_UNION u_CoefAccFF;	// typically up to 64 bytes (max=128)
    ELMO_INT32  iAccFFMechanismIndex;	// 1..5
	ELMO_UINT16 usStatus;
	ELMO_INT16  sErrorID;

}MMC_GETACCFFINFO_OUT;


typedef struct
{
	ELMO_INT16	sEnable;		//!< Disable(0), Enable(1), Erase AccFF data for this axis(-1)
	ELMO_INT16  sSpare[11];		//!< for future use.

}MMC_ENABLEACCFF_IN;

typedef struct
{
	ELMO_UINT16  usStatus;
	ELMO_INT16   sErrorID;

}MMC_ENABLEACCFF_OUT;

/// \struct MMC_AXISLINK_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_axislink_in
{
	uint32_t 	ulInputParameter1;
	uint32_t 	ulInputParameter2;
	uint32_t 	ulInputParameter3;
	uint32_t 	ulInputParameter4;
    ELMO_UINT16 usSlaveAxisReference;
    ELMO_UINT8 	ucMode;

}MMC_AXISLINK_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_AXISLINK_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_axislink_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 	usErrorID;
}MMC_AXISLINK_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_AXISUNLINK_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_axisunlink_in
{
    ELMO_UINT8 	ucdummy;

}MMC_AXISUNLINK_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_AXISUNLINK_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_axisunlink_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16 	usErrorID;
}MMC_AXISUNLINK_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CHANGEOPMODE_EX_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbInitModeValue;
    MC_EXECUTION_MODE eExecutionMode;   
    ELMO_UINT8 ucMotionMode;
	ELMO_UINT8 ucSpare[19];
}MMC_CHANGEOPMODE_EX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CHANGEOPMODE_EX_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;
    ELMO_UINT16 usStatus;
    ELMO_UINT16 usErrorID;
 }MMC_CHANGEOPMODE_EX_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVETORQUE_IN
/// \brief Move Torque Command input data structure.
///
/// (See : "Technical Specification
///     PLCopen - Technical Committee 2 – Task Force
///     Function blocks for motion control")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_DOUBLE dbTargetTorque;              ///< Desired Target Torque value
    ELMO_DOUBLE dbTorquetVelocity;           ///< Maximum Target torque velocity value
    ELMO_DOUBLE dbTorqueAcceleration;        ///< Maximum Target torque acceleration value
    MC_BUFFERED_MODE_ENUM eBufferMode;      ///< MC_BufferMode
    ELMO_UINT8 ucExecute;                   ///< Execution bit
} MMC_MOVETORQUE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVETORQUE_OUT
/// \brief Move Torque Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT32   uiHndl;                   ///< Returned function block handle.
    ELMO_UINT16 usStatus;                   ///< Returned command status.
    ELMO_INT16 usErrorID;                   ///< Returned command error ID.
} MMC_MOVETORQUE_OUT;

typedef enum
{
    eNODE_ERROR_ECAT_PHY_ERROR  = 0,
    eSYS_ERROR_CYCLIC_ERROR     = 1,
    eSYS_ERROR_MISSED_FRAMES    = 2,
    eNODE_ERROR_ECAT_AL_ERROR   = 3,
    eNODE_ERROR_UNEXPEC_MO_0    = 4,
    eNODE_ERROR_DRIVE_FAULT     = 5,
    eNODE_ERROR_QSTOP           = 6,
    eNODE_ERROR_HBT             = 7,
    eNODE_ERROR_EMCY            = 8,
    eNODE_ERROR_FB              = 9,
    eNODE_ERROR_MAX
}ERRORS;

typedef enum
{
    ePOLICY_NO_REACTION            = 0,
    ePOLICY_EVENT                  = 0x1,
    ePOLICY_STOP                   = 0x2,
    ePOLICY_POWER_OFF              = 0x4,
    ePOLICY_SAFEOP                 = 0x8,
    ePOLICY_APP_TO_ALL             = 0x80
}POLICY;

#define MAX_REG_POLICY              20

///////////////////////////////////////////////////////////////////////////////
/// \struct NC_POLICY_ENTRY
/// \brief register error policy input data member structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct nc_policy_entry
{
    ERRORS eErrType;    ///< Error type
    ELMO_UINT8 ucPolicy;     ///< 7 bits of possible policies, MSb defines if the policies are applied to all axes
    ELMO_UINT8 ucThreshold;  ///< the errors threshold for starting the reaction
}
NC_POLICY_ENTRY;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_REGERRPOLICY_IN
/// \brief register error policy input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    NC_POLICY_ENTRY pPolicies[MAX_REG_POLICY];
    ELMO_UINT16 usAxisRef;                   ///< relevant only for node errors
    ELMO_UINT8 ucNum;                        ///< num of policies to register
    ELMO_UINT8 pSpare[64];
} MMC_REGERRPOLICY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_REGERRPOLICY_OUT
/// \brief register error policy output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;    ///< Returned command status.
    ELMO_INT16 sErrorID;     ///< Returned command error ID.
} MMC_REGERRPOLICY_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESETSYSTEM_IN
/// \brief reset system errors input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT8 ucDummy;
}MMC_RESETSYSTEM_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESETSYSERR_OUT
/// \brief set stop options output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ELMO_UINT16 usStatus;    ///< Returned command status.
    ELMO_INT16  sErrorID;    ///< Returned command error ID.
} MMC_RESETSYSTEM_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct NC_GET_POLICY_ENTRY
/// \brief get error policy input data member structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct nc_get_policy_entry
{
    ELMO_UINT8 ucPolicy;     ///< 7 bits of possible policies, MSb defines if the policies are applied to all axes
    ELMO_UINT8 ucThreshold;  ///< the errors threshold for starting the reaction
    ELMO_UINT8 ucCurrentVal; ///< current value of registered err
}
NC_GET_POLICY_ENTRY;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETERRPOLICY_IN
/// \brief reset system errors input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ERRORS pErrType[MAX_REG_POLICY];    ///< the types of errors request
    ELMO_UINT16 usAxisRef;              ///< relevant only for node errors
    ELMO_UINT8  ucNum;                  ///< the requested number of error policies
}MMC_GETERRPOLICY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GETERRPOLICY_OUT
/// \brief set stop options output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
    NC_GET_POLICY_ENTRY pPolicies[MAX_REG_POLICY];
    ELMO_UINT16 usStatus;               ///< Returned command status.
    ELMO_INT16  sErrorID;               ///< Returned command error ID.
    ELMO_UINT8  pSpare[64];
} MMC_GETERRPOLICY_OUT;

/*!
 * \struct _is_struct
 * \brief input parameters data structure for input shaping API.
 *
 * this structure defines the input parameters for input shaping API.
 * arrays are related respectively. freq[i] to damp[i] & impulse[i] where i is 0-1.
 */
typedef struct _is_struct_in
{
    ELMO_DOUBLE freq[2];            //!< frequency of vibration.
    ELMO_DOUBLE damp[2];            //!< damping factor for vibration.
    ELMO_UINT8  freqs_num;          //!< number of frequencies(1 or 2). if 1 then freq[0] only.
    ELMO_UINT8  impls_num[2];       //!< 2 or 3 impulse for each frequency.
    ELMO_UINT8  enable;             //!< disable=0, enable=1
    ELMO_UINT8  index;              //!< number of selected mechanism (0-2).
    ELMO_UINT8  spare[31];          //!< for future use.
} MMC_PROFILECOND_IN;

/*! \struct _is_struct
* \brief output parameters data structure for profile conditioning.
*
* this structure defines the output parameters for profile conditioning API.
*/
typedef struct _is_struct_out
{
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
} MMC_PROFILECOND_OUT;

/*-----------------------------------------
 * Enable Profile Conditioning API
 *
 * this interface enables "profile conditioning" mode on a single axis.
 * it uses parameters, which were stored in one of three buffers on previous settings.
 * that is why other input parameters are redundant here.
 */

/*! \struct _is_struct_out
 * \brief this structure defines the input parameters for 'enable profile conditioning' API.
 */
typedef struct _prfcnd_enable_in
{
    ELMO_UINT8   enable;            //!< disable(0), enable(1)
    ELMO_UINT8   spare[31];         //!< for future use.
} MMC_PRFCND_ENABLE_IN;

typedef MMC_PROFILECOND_OUT MMC_PRFCND_ENABLE_OUT;


/*!
 * \struct _prfcdat_struct_in
 * \brief this structure defines the settings of profile conditioning.
 *
 * it actually reflects user settings of profile conditioning for a single axis.
 */
typedef struct _prfcdat_struct_in
{
    MMC_PROFILECOND_IN  prfc;       //!< parameters settings for profile conditioning.
    ELMO_UINT16         axis;       //!< axis reference on which profile conditioning is activated.
} MMC_PROFILECOND_DAT;

/*!
 * \struct _prfcinf_struct_in
 * \brief this structure stores retrieved data by API for profile conditioning.
 *
 * it actually reflects user settings of profile conditioning on maestro.
 */
typedef struct _prfcinf_struct_out
{
    MMC_PROFILECOND_DAT data[3];    //!< settings information for profile conditioning.
    ELMO_INT32          size;       //!< number of active axes in data member (starts from index 0-2).
    ELMO_UINT16         usStatus;   //!< just to adjust library convention.
    ELMO_INT16          usErrorID;  //!< API error. 0 if no error.
    ELMO_UINT8          spare[32];
} MMC_PROFCONDINF_OUT;

/*!
 * \struct _prfcinf_struct_in
 * \brief this structure used by API for profile conditioning.
 */
typedef struct _prfcinf_struct_in
{
    ELMO_UINT8  ucdummy;
} MMC_PROFCONDINF_IN;
       

///////// functions

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveAbsoluteCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_MOVEABSOLUTE_IN* pInParam,
///             OUT MMC_MOVEABSOLUTE_OUT* pOutParam)
/// \brief This function send Move Absolute command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Absolute input parameters
/// \param  pOutParam - [OUT] Pointer to Move Absolute output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MoveAbsoluteCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_MOVEABSOLUTE_IN* pInParam,
        OUT MMC_MOVEABSOLUTE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveAdditiveCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_MOVEADDITIVE_IN* pInParam,
///             OUT MMC_MOVEADDITIVE_OUT* pOutParam)
/// \brief This function  send Move Additive command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Additive input parameters
/// \param  pOutParam - [OUT] Pointer to Move Additive output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MoveAdditiveCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_MOVEADDITIVE_IN* pInParam,
        OUT MMC_MOVEADDITIVE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveRelativeCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_MOVERELATIVE_IN* pInParam,
///             OUT MMC_MOVERELATIVE_OUT* pOutParam)
/// \brief This function  send Move Relative command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Relative input parameters
/// \param  pOutParam - [OUT] Pointer to Move Relative output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MoveRelativeCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_MOVERELATIVE_IN* pInParam,
        OUT MMC_MOVERELATIVE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadAxisError(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READAXISERROR_IN* pInParam,
///             OUT MMC_READAXISERROR_OUT* pOutParam)
/// \brief This function read axis error.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Group Read Error input parameters
/// \param  pOutParam - [OUT] Pointer to Group Read Error output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadAxisError(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_READAXISERROR_IN* pInParam,
        OUT MMC_READAXISERROR_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveVelocityCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_MOVEVELOCITY_IN* pInParam,
///             OUT MMC_MOVEVELOCITY_OUT* pOutParam)
/// \brief This function  send Move Velocity command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Velocity input parameters
/// \param  pOutParam - [OUT] Pointer to Move Velocity output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MoveVelocityCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_MOVEVELOCITY_IN* pInParam,
        OUT MMC_MOVEVELOCITY_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveContinuousCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_MOVECONTINUOUS_IN* pInParam,
///             OUT MMC_MOVECONTINUOUS_OUT* pOutParam)
/// \brief This function  send Move Continuous command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Continuous input parameters
/// \param  pOutParam - [OUT] Pointer to Move Continuous output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MoveContinuousCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_MOVECONTINUOUS_IN* pInParam,
        OUT MMC_MOVECONTINUOUS_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_HomeCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_HOME_IN* pInParam,
///             OUT MMC_HOME_OUT* pOutParam)
/// \brief This function  send Home command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Home input parameters
/// \param  pOutParam - [OUT] Pointer to Home output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_HomeCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_HOME_IN* pInParam,
        OUT MMC_HOME_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_HomeDS402Cmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_HOME_IN* pInParam,
///             OUT MMC_HOME_OUT* pOutParam)
/// \brief This function  send Home DS402 command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Home input parameters
/// \param  pOutParam - [OUT] Pointer to Home output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_HomeDS402Cmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_HOMEDS402_IN* pInParam,
        OUT MMC_HOME_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_HomeDS402ExCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_HOMEDS402EX_IN* pInParam,
///             OUT MMC_HOME_OUT* pOutParam)
/// \brief This function  send Home DS402 command to MMC server for specific Axis.
///         supports Velocity Hi\Lo, DetectionTimeLimit and DetectionVelocityLimit
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Home input parameters
/// \param  pOutParam - [OUT] Pointer to Home output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_HomeDS402ExCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_HOMEDS402EX_IN* pInParam,
        OUT MMC_HOME_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadActualPositionCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READACTUALPOSITION_IN* pInParam,
///             OUT MMC_READACTUALPOSITION_OUT* pOutParam)
/// \brief This function read actual position of specific axis
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] input parameters structure for Read Actual Position Command
/// \param  pOutParam - [OUT] output parameters structure for Read Actual Position Command
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadActualPositionCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_READACTUALPOSITION_IN* pInParam,
        OUT MMC_READACTUALPOSITION_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadActualVelocityCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READACTUALVELOCITY_IN* pInParam,
///             OUT MMC_READACTUALVELOCITY_OUT* pOutParam)
/// \brief This function read actual velocity of specific axis
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] input parameters structure for Read Actual Velocity Command
/// \param  pOutParam - [OUT] output parameters structure for Read Actual Velocity Command
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadActualVelocityCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_READACTUALVELOCITY_IN* pInParam,
        OUT MMC_READACTUALVELOCITY_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_HaltCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_HALT_IN* pInParam,
///             OUT MMC_HALT_OUT* pOutParam)
/// \brief This function  send Halt command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Halt input parameters
/// \param  pOutParam - [OUT] Pointer to Halt output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_HaltCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_HALT_IN* pInParam,
        OUT MMC_HALT_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_StopCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_STOP_IN* pInParam,
///             OUT MMC_STOP_OUT* pOutParam)
/// \brief This function  send Stop command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Stop input parameters
/// \param  pOutParam - [OUT] Pointer to Stop output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_StopCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_STOP_IN* pInParam,
        OUT MMC_STOP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadDigitalInputCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READDIGITALINPUT_IN* pInParam,
///             OUT MMC_READDIGITALINPUT_OUT* pOutParam)
/// \brief This function  return value of specific bit digital input.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Read Digital Input input parameters
/// \param  pOutParam - [OUT] Pointer to Read Digital Input output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadDigitalInputCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_READDIGITALINPUT_IN* pInParam,
        OUT MMC_READDIGITALINPUT_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadDigitalInputsCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READDIGITALINPUTS_IN* pInParam,
///             OUT MMC_READDIGITALINPUTS_OUT* pOutParam)
/// \brief This function  return value of specific bit digital input.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Read Digital Input input parameters
/// \param  pOutParam - [OUT] Pointer to Read Digital Input output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadDigitalInputsCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_READDIGITALINPUTS_IN* pInParam,
        OUT MMC_READDIGITALINPUTS_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetPositionCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_SETPOSITION_IN* pInParam,
///             OUT MMC_SETPOSITION_OUT* pOutParam)
/// \brief This function  send Set Position command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Set Position input parameters
/// \param  pOutParam - [OUT] Pointer to Set POsition output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SetPositionCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_SETPOSITION_IN* pInParam,
        OUT MMC_SETPOSITION_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetOverrideCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_SETOVERRIDE_IN* pInParam,
///             OUT MMC_SETOVERRIDE_OUT* pOutParam)
/// \brief This function  send Set Override command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Set Override input parameters
/// \param  pOutParam - [OUT] Pointer to Set Override output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SetOverrideCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_SETOVERRIDE_IN* pInParam,
        OUT MMC_SETOVERRIDE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetOverrideCmdEx(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_SETOVERRIDEEX_IN* pInParam,
///				OUT MMC_SETOVERRIDE_OUT* pOutParam)
/// \brief This function ...
/// \param MMC_CONNECT_HNDL hConn - [IN] Connection handle
/// \param MMC_AXIS_REF_HNDL hAxisRef - [IN] Axis Reference handle
/// \param MMC_SETOVERRIDEEX_IN* pInParam - [IN] Pointer to Set Override input parameters
/// \param MMC_SETOVERRIDE_OUT* pOutParam - [OUT] Pointer to Set Override output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SetOverrideCmdEx(
	IN MMC_CONNECT_HNDL hConn,
	IN MMC_AXIS_REF_HNDL hAxisRef,
	IN MMC_SETOVERRIDEEX_IN* pInParam,
	OUT MMC_SETOVERRIDE_OUT* pOutParam);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadStatusCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READSTATUS_IN* pInParam,
///             OUT MMC_READSTATUS_OUT* pOutParam)
/// \brief This function  send Read Axis Status command to MMC server for specific Axis
/// and receive Axis status back if it's available.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Axis Status input parameters structure
/// \param  pOutParam - [OUT] Axis Status output parameters structure
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadStatusCmd(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_READSTATUS_IN* pInParam,
        OUT MMC_READSTATUS_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int   MMC_ReadParameter(
///                 IN MMC_CONNECT_HNDL hConn,
///                 IN MMC_AXIS_REF_HNDL hAxisRef,
///                 IN MMC_READPARAMETER_IN* pInParam,
///                 OUT MMC_READPARAMETER_OUT* pOutParam)
/// \brief This function read specific axis parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Read Parameter input parameters
/// \param  pOutParam - [OUT] Pointer to Read Parameter output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadParameter(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_READPARAMETER_IN* pInParam,
        OUT MMC_READPARAMETER_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int   MMC_ReadBoolParameter(
///                 IN MMC_CONNECT_HNDL hConn,
///                 IN MMC_AXIS_REF_HNDL hAxisRef,
///                 IN MMC_READBOOLPARAMETER_IN* pInParam,
///                 OUT MMC_READBOOLPARAMETER_OUT* pOutParam)
/// \brief This function read boolean specific axis parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Read Boolean Parameter input parameters
/// \param  pOutParam - [OUT] Pointer to Read Boolean Parameter output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadBoolParameter(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_READBOOLPARAMETER_IN* pInParam,
        OUT MMC_READBOOLPARAMETER_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int   MMC_WriteParameter(
///                 IN MMC_CONNECT_HNDL hConn,
///                 IN MMC_AXIS_REF_HNDL hAxisRef,
///                 IN MMC_WRITEPARAMETER_IN* pInParam,
///                 OUT MMC_WRITEPARAMETER_OUT* pOutParam)
/// \brief This function write specific axis parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Write Parameter input parameters
/// \param  pOutParam - [OUT] Pointer to Write Parameter output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_WriteParameter(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_WRITEPARAMETER_IN* pInParam,
        OUT MMC_WRITEPARAMETER_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int   MMC_WriteBoolParameter(
///                 IN MMC_CONNECT_HNDL hConn,
///                 IN MMC_AXIS_REF_HNDL hAxisRef,
///                 IN MMC_WRITEBOOLPARAMETER_IN* pInParam,
///                 OUT MMC_WRITEBOOLPARAMETER_OUT* pOutParam)
/// \brief This function write boolean specific axis parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Write Boolean Parameter input parameters
/// \param  pOutParam - [OUT] Pointer to Write Boolean Parameter output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_WriteBoolParameter(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_WRITEBOOLPARAMETER_IN* pInParam,
        OUT MMC_WRITEBOOLPARAMETER_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_Reset(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_RESET_IN* pInParam,
///             OUT MMC_RESET_OUT* pOutParam)
/// \brief This function reset axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Reset input parameters
/// \param  pOutParam - [OUT] Pointer to Reset output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_Reset(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_RESET_IN* pInParam,
        OUT MMC_RESET_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ResetAsync(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_RESET_IN* pInParam,
///             OUT MMC_RESET_OUT* pOutParam)
/// \brief This function reset axis Asynchronously.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Reset input parameters
/// \param  pOutParam - [OUT] Pointer to Reset output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ResetAsync(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL hAxisRef,
        IN MMC_RESET_IN* pInParam,
        OUT MMC_RESET_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_PowerCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_POWER_IN* pInParam,
///             OUT MMC_POWER_OUT* pOutParam)
/// \brief This function send Power On command to MMC server.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Power input parameters
/// \param  pOutParam - [OUT] Pointer to Power output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_PowerCmd(
        IN  MMC_CONNECT_HNDL    hConn,
        IN  MMC_AXIS_REF_HNDL   hAxisRef,
        IN  MMC_POWER_IN*       pInParam,
        OUT MMC_POWER_OUT*      pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetFbDepthCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_GETFBDEPTH_IN* pInParam,
///             OUT MMC_GETFBDEPTH_OUT* pOutParam)
/// \brief This function sends a command for receive number of function blocks in Node Queue - ONLY THOSE WHICH
///        did not receive DONE/ABORTED status!!!
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Get F.B. Depth input parameters
/// \param  pOutParam - [OUT] Pointer to Get F.B. Depth output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetFbDepthCmd(
        IN  MMC_CONNECT_HNDL    hConn,
        IN  MMC_AXIS_REF_HNDL   hAxisRef,
        IN  MMC_GETFBDEPTH_IN*  pInParam,
        OUT MMC_GETFBDEPTH_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetTotalFbDepthCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_GETFBDEPTH_IN* pInParam,
///             OUT MMC_GETFBDEPTH_OUT* pOutParam)
/// \brief This function sends a command for receive number of function blocks in Node Queue .
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Get F.B. Depth input parameters
/// \param  pOutParam - [OUT] Pointer to Get F.B. Depth output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetTotalFbDepthCmd(
        IN  MMC_CONNECT_HNDL    hConn,
        IN  MMC_AXIS_REF_HNDL   hAxisRef,
        IN  MMC_GETFBDEPTH_IN*  pInParam,
        OUT MMC_GETFBDEPTH_OUT* pOutParam);
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadActualTorqueCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READACTUALTORQUE_IN* pInParam,
///             OUT MMC_READACTUALTORQUE_OUT* pOutParam)
/// \brief The function returns the actual torque for specific Node.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Read Actual Torque input parameters
/// \param  pOutParam - [OUT] Pointer to Read Actual Torque output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadActualTorqueCmd(
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_AXIS_REF_HNDL           hAxisRef,
        IN  MMC_READACTUALTORQUE_IN*    pInParam,
        OUT MMC_READACTUALTORQUE_OUT*   pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadDigitalOutputs(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READDIGITALOUTPUT_IN* pInParam,
///             OUT MMC_READDIGITALOUTPUT_OUT* pOutParam)
/// \brief The function returns the actual Digital Output for specific Node.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN]     Pointer to Read Digital Output input parameters
/// \param  pOutParam - [OUT]   Pointer to Read Digital Output output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadDigitalOutputs(
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_AXIS_REF_HNDL           hAxisRef,
        IN  MMC_READDIGITALOUTPUT_IN*   pInParam,
        OUT MMC_READDIGITALOUTPUT_OUT*  pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_WriteDigitalOutputs(
/// IN MMC_CONNECT_HNDL hConn,
/// IN MMC_AXIS_REF_HNDL hAxisRef,
/// IN MMC_WRITEDIGITALOUTPUT_IN* pInParam,
/// OUT MMC_WRITEDIGITALOUTPUT_OUT* pOutParam)
/// \brief The function sets the actual Digital Output for specific Node.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN]     Pointer to Set Digital Output input parameters
/// \param  pOutParam - [OUT]   Pointer to Set Digital Output output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_WriteDigitalOutputs(
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_AXIS_REF_HNDL           hAxisRef,
        IN  MMC_WRITEDIGITALOUTPUT_IN*  pInParam,
        OUT MMC_WRITEDIGITALOUTPUT_OUT* pOutParam) ;

///
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadDigitalOutputs32Bit(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_READDIGITALOUTPUT_IN* pInParam,
///             OUT MMC_READDIGITALOUTPUT_OUT* pOutParam)
/// \brief The function returns the actual Digital Output for specific Node.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN]     Pointer to Read Digital Output input parameters
/// \param  pOutParam - [OUT]   Pointer to Read Digital Output output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ReadDigitalOutputs32Bit(
        IN  MMC_CONNECT_HNDL                hConn,
        IN  MMC_AXIS_REF_HNDL               hAxisRef,
        IN  MMC_READDIGITALOUTPUT32Bit_IN*  pInParam,
        OUT MMC_READDIGITALOUTPUT32Bit_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_WriteDigitalOutputs32Bit(
/// IN MMC_CONNECT_HNDL hConn,
/// IN MMC_AXIS_REF_HNDL hAxisRef,
/// IN MMC_WRITEDIGITALOUTPUT_IN* pInParam,
/// OUT MMC_WRITEDIGITALOUTPUT_OUT* pOutParam)
/// \brief The function sets the actual Digital Output for specific Node.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN]     Pointer to Set Digital Output input parameters
/// \param  pOutParam - [OUT]   Pointer to Set Digital Output output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_WriteDigitalOutputs32Bit(
        IN  MMC_CONNECT_HNDL                    hConn,
        IN  MMC_AXIS_REF_HNDL                   hAxisRef,
        IN  MMC_WRITEDIGITALOUTPUT32Bit_IN*     pInParam,
        OUT MMC_WRITEDIGITALOUTPUT32Bit_OUT*    pOutParam) ;

/* Alex - Integration of MoveRepetitive()*/
///////////////////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveAbsoluteRepetitiveCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_MOVEABSOLUTEREPETITIVE_IN* pInParam,
///             OUT MMC_MOVEABSOLUTEREPETITIVE_OUT* pOutParam)
/// \brief This function send Move Absolute Repetitive command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Absolute Repetitive input parameters
/// \param  pOutParam - [OUT] Pointer to Move Absolute Repetitive output parameters
/// \return return - 0 if success
///                  error_id in case of error
/////////////////////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MoveAbsoluteRepetitiveCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL               hAxisRef,
        IN  MMC_MOVEABSOLUTEREPETITIVE_IN*  pInParam,
        OUT MMC_MOVEABSOLUTEREPETITIVE_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_MoveRelativeRepetitiveCmd(IN MMC_CONNECT_HNDL hConn,
        IN MMC_AXIS_REF_HNDL                hAxisRef,
        IN MMC_MOVERELATIVEREPETITIVE_IN*   pInParam,
        OUT MMC_MOVERELATIVEREPETITIVE_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_MoveAdditiveRepetitiveCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL               hAxisRef,
        IN  MMC_MOVEADDITIVEREPETITIVE_IN*  pInParam,
        OUT MMC_MOVEADDITIVEREPETITIVE_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_PositionProfileCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL           hAxisRef,
        IN  MMC_POSITIONPROFILE_IN*     pInParam,
        OUT MMC_POSITIONPROFILE_OUT*    pOutParam);

MMC_LIB_API ELMO_INT32 MMC_MoveAbsoluteExCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL       hAxisRef,
        IN  MMC_MOVEABSOLUTEEX_IN*  pInParam,
        OUT MMC_MOVEABSOLUTEEX_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_MoveRelativeExCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL       hAxisRef,
        IN  MMC_MOVERELATIVEEX_IN*  pInParam,
        OUT MMC_MOVERELATIVEEX_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_MoveAdditiveExCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL       hAxisRef,
        IN  MMC_MOVEADDITIVEEX_IN*  pInParam,
        OUT MMC_MOVEADDITIVEEX_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_MoveVelocityExCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL       hAxisRef,
        IN  MMC_MOVEVELOCITYEX_IN*  pInParam,
        OUT MMC_MOVEVELOCITYEX_OUT* pOutParam);

MMC_LIB_API ELMO_INT32 MMC_MoveAbsoluteRepetitiveExCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL                   hAxisRef,
        IN  MMC_MOVEABSOLUTEREPETITIVEEX_IN*    pInParam,
        OUT MMC_MOVEABSOLUTEREPETITIVEEX_OUT*   pOutParam);
MMC_LIB_API ELMO_INT32 MMC_MoveRelativeRepetitiveExCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL                   hAxisRef,
        IN  MMC_MOVERELATIVEREPETITIVEEX_IN*    pInParam,
        OUT MMC_MOVERELATIVEREPETITIVEEX_OUT*   pOutParam);

MMC_LIB_API ELMO_INT32 MMC_MoveAdditiveRepetitiveExCmd(IN MMC_CONNECT_HNDL hConn,
        IN  MMC_AXIS_REF_HNDL                   hAxisRef,
        IN  MMC_MOVEADDITIVEREPETITIVEEX_IN*    pInParam,
        OUT MMC_MOVEADDITIVEREPETITIVEEX_OUT*   pOutParam);
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_TouchProbeEnable(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_TOUCHPROBEENABLE_IN* pInParam,
///             OUT MMC_TOUCHPROBEENABLE_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Touch Proble Enable input parameters
/// \param pOutParam - [OUT] Pointer to Touch Proble Enable output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_TouchProbeEnable(
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_AXIS_REF_HNDL           hAxisRef,
        IN  MMC_TOUCHPROBEENABLE_IN*    pInParam,
        OUT MMC_TOUCHPROBEENABLE_OUT*   pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_TouchProbeDisable(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_TOUCHPROBEENABLE_IN* pInParam,
///             OUT MMC_TOUCHPROBEENABLE_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Touch Proble Disable input parameters
/// \param pOutParam - [OUT] Pointer to Touch Proble Disable output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_TouchProbeDisable(
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_AXIS_REF_HNDL           hAxisRef,
        IN  MMC_TOUCHPROBEDISABLE_IN*   pInParam,
        OUT MMC_TOUCHPROBEDISABLE_OUT*  pOutParam) ;


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_TouchProbeEnable_Ex(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_TOUCHPROBEENABLE_EX_IN* pInParam,
///				OUT MMC_TOUCHPROBEENABLE_EX_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Touch Probe Enable_Ex input parameters
/// \param pOutParam - [OUT] Pointer to Touch Probe Enable_Ex output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_TouchProbeEnable_Ex(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_TOUCHPROBEENABLE_EX_IN* pInParam,
		OUT MMC_TOUCHPROBEENABLE_EX_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_TouchProbeDisable_Ex(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_TOUCHPROBEDISABLE_EX_IN* pInParam,
///				OUT MMC_TOUCHPROBEDISABLE_EX_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Touch Probe Disable_Ex input parameters
/// \param pOutParam - [OUT] Pointer to Touch Probe Disable_Ex output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_TouchProbeDisable_Ex(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_TOUCHPROBEDISABLE_EX_IN* pInParam,
		OUT MMC_TOUCHPROBEDISABLE_EX_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetTouchProbeStatus(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GETTOUCHPROBESTATUS_IN* pInParam,
///				OUT MMC_GETTOUCHPROBESTATUS_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to GetTouchProbeStatus input parameters
/// \param pOutParam - [OUT] Pointer to GetTouchProbeStatus output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetTouchProbeStatus(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GETTOUCHPROBESTATUS_IN* pInParam,
		OUT MMC_GETTOUCHPROBESTATUS_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetTouchProbeData(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GETTOUCHPROBEDATA_IN* pInParam,
///				OUT MMC_GETTOUCHPROBEDATA_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to GetTouchProbeData input parameters
/// \param pOutParam - [OUT] Pointer to GetTouchProbeData output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetTouchProbeData(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GETTOUCHPROBEDATA_IN* pInParam,
		OUT MMC_GETTOUCHPROBEDATA_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_TouchProbeStart(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_TOUCHPROBESTOP_IN* pInParam,
///				OUT MMC_TOUCHPROBESTOP_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Touch Probe Start input parameters
/// \param pOutParam - [OUT] Pointer to Touch Probe Start output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_TouchProbeStop(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_TOUCHPROBESTOP_IN* pInParam,
		OUT MMC_TOUCHPROBESTOP_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_TouchProbeStop(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_TOUCHPROBESTART_IN* pInParam,
///				OUT MMC_TOUCHPROBESTART_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Touch Probe Stop input parameters
/// \param pOutParam - [OUT] Pointer to Touch Probe Stop output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_TouchProbeStart(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_TOUCHPROBESTART_IN* pInParam,
		OUT MMC_TOUCHPROBESTART_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetAccFeedForwardMode(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_SETACCFFMODE_IN* pInParam,
///				OUT MMC_SETACCFFMODE_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Set AccFF Mode input parameters
/// \param pOutParam - [OUT] Pointer to Set AccFF Mode output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_SetAccFeedForwardMode(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_SETACCFFMODE_IN* pInParam,
		OUT MMC_SETACCFFMODE_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetAccFeedForwardInfo(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GETACCFFINFO_IN* pInParam,
///				OUT MMC_GETACCFFINFO_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Get AccFF Info input parameters
/// \param pOutParam - [OUT] Pointer to Get AccFF Info output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetAccFeedForwardInfo(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GETACCFFINFO_IN* pInParam,
		OUT MMC_GETACCFFINFO_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_EnableAccFeedForward(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_ENABLEACCFF_IN* pInParam,
///				OUT MMC_ENABLEACCFF_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Enable AccFF input parameters
/// \param pOutParam - [OUT] Pointer to Enable AccFF output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_EnableAccFeedForward(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_ENABLEACCFF_IN* pInParam,
		OUT MMC_ENABLEACCFF_OUT* pOutParam) ;


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_AxisLink(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_AXISLINK_IN* pInParam,
///             OUT MMC_AXISLINK_OUT* pOutParam)
/// \brief This function link between two axes
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Master Axis Reference handle
/// \param pInParam - [IN] Pointer to AxisLink input parameters
/// \param pOutParam - [OUT] Pointer to AxisLink output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_AxisLink(
        IN  MMC_CONNECT_HNDL    hConn,
        IN  MMC_AXIS_REF_HNDL   hAxisRef,
        IN  MMC_AXISLINK_IN*    pInParam,
        OUT MMC_AXISLINK_OUT*   pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_AxisUnLink(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_AXISUNLINK_IN* pInParam,
///             OUT MMC_AXISUNLINK_OUT* pOutParam)
/// \brief This function unlink the master axis from the slave
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Master Axis Reference handle
/// \param pInParam - [IN] Pointer to AxisUnLink input parameters
/// \param pOutParam - [OUT] Pointer to AxisUnLink output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_AxisUnLink(
        IN  MMC_CONNECT_HNDL    hConn,
        IN  MMC_AXIS_REF_HNDL   hAxisRef,
        IN  MMC_AXISUNLINK_IN*  pInParam,
        OUT MMC_AXISUNLINK_OUT* pOutParam) ;


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ChangeOpModeEx(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_CHANGEOPMODE_EX_IN* pInParam,
///             OUT MMC_CHANGEOPMODE_EX_OUT* pOutParam)
/// \brief The function change the motion mode.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to input parameters
/// \param  pOutParam - [OUT] Pointer to output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ChangeOpModeEx(
        IN  MMC_CONNECT_HNDL            hConn,
        IN  MMC_AXIS_REF_HNDL           hAxisRef,
        IN  MMC_CHANGEOPMODE_EX_IN*     pInParam,
        OUT MMC_CHANGEOPMODE_EX_OUT*    pOutParam);



////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveTorqueCmd(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_MOVETORQUE_IN* pInParam,
///             OUT MMC_MOVETORQUE_OUT* pOutParam)
/// \brief This function send Move torque command to MMC server for specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Torque input parameters
/// \param  pOutParam - [OUT] Pointer to Move Torque output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_MoveTorqueCmd(
        IN  MMC_CONNECT_HNDL    hConn,
        IN  MMC_AXIS_REF_HNDL   hAxisRef,
        IN  MMC_MOVETORQUE_IN*  pInParam,
        OUT MMC_MOVETORQUE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_RegErrPolicy(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_REGERRPOLICY_IN* pInParam,
///             OUT MMC_REGERRPOLICY_OUT* pOutParam)
/// \brief This function registers an error policy for a specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to register error policy input parameters
/// \param  pOutParam - [OUT] Pointer to register error policy output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_RegErrPolicy(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_REGERRPOLICY_IN* pInParam,
        OUT MMC_REGERRPOLICY_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ResetSystem(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_RESETSYSTEM_IN* pInParam,
///             OUT MMC_RESETSYSTEM_OUT* pOutParam)
/// \brief This function resets system errors and restarts the system errors monitoring
/// \param hConn - [IN] Connection handle
/// \param pInParam - [IN] Pointer to reset system errors input parameters
/// \param pOutParam - [OUT] Pointer to system errors output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_ResetSystem(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_RESETSYSTEM_IN* pInParam,
        OUT MMC_RESETSYSTEM_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GetErrPolicy(
///             IN MMC_CONNECT_HNDL hConn,
///             IN MMC_AXIS_REF_HNDL hAxisRef,
///             IN MMC_GETERRPOLICY_IN* pInParam,
///             OUT MMC_GETERRPOLICY_OUT* pOutParam)
/// \brief This function get an error policy for a specific Axis.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to get error policy input parameters
/// \param  pOutParam - [OUT] Pointer to get error policy output parameters
/// \return return - 0 if success
///                  error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API ELMO_INT32 MMC_GetErrPolicy(
        IN MMC_CONNECT_HNDL hConn,
        IN MMC_GETERRPOLICY_IN* pInParam,
        OUT MMC_GETERRPOLICY_OUT* pOutParam);
                
/*!
 * \fn  MMC_SetProfileConditioning(...)
 * \brief       this method sets 'profile conditioning' mode of operation.
 *
 * it turns on(1)/off(0) 'profile conditioning' and sets other input parameters.
 *
 * \param hConn connection handler.
 * \param hAxisRef      axis reference.
 * \param i_params      input parameters.
 * \param o_params      output parameters.
 * \return 0 if completed successfully, otherwise error.
 */
MMC_LIB_API ELMO_INT32 MMC_SetProfileConditioning(
        IN  MMC_CONNECT_HNDL    hConn,
        IN  MMC_AXIS_REF_HNDL   hAxisRef,
        IN  MMC_PROFILECOND_IN* i_params,
        OUT MMC_PROFILECOND_OUT* o_params);

/*!
* \fn int MMC_EnableProfileConditioning(
*                               IN MMC_CONNECT_HNDL hConn,
*                               IN MMC_AXIS_REF_HNDL hAxisRef,
*                               IN MMC_KILLMOTION_IN* pInParam,
*                               OUT MMC_KILLMOTION_OUT* pOutParam)
* \brief this interface enables "profile conditioning" mode on a single axis.
*
* it uses parameters, which were stored in one of three buffers on previous settings.
* that is why other input parameters are redundant here.
*
* \param  hConn -        [IN] connection handle
* \param  hAxisRef - [IN] axis reference handle
* \param  i_param - [IN] input parameters for this API.
* \param  o_param - [OUT] output parameters for this API.
* \return       return - 0 if success otherwise error.
*/
MMC_LIB_API ELMO_INT32 MMC_EnableProfileConditioning(
        IN  MMC_CONNECT_HNDL        hConn,
        IN  MMC_AXIS_REF_HNDL       hAxisRef,
        IN  MMC_PRFCND_ENABLE_IN*   i_param,
        OUT MMC_PRFCND_ENABLE_OUT*  o_param);
/*!
 * \fn  MMC_GetProfileConditioning(...)
 * \brief       this method gets 'profile conditioning' information.
 *
 * it gets 'profile conditioning' data for axes on which this mode of operation is enabled.
 *
 * \param hConn connection handler.
 * \param hAxisRef      axis reference.
 * \param i_params      input parameters.
 * \param o_params      output parameters.
 * \return 0 if completed successfully, otherwise error.
 */
MMC_LIB_API ELMO_INT32 MMC_GetProfileConditioning(
        IN  MMC_CONNECT_HNDL        hConn,
        IN  MMC_AXIS_REF_HNDL       hAxisRef,
        IN  MMC_PROFCONDINF_IN*     i_params,
        OUT MMC_PROFCONDINF_OUT*    o_params);

//@UM 12.05.2020
MMC_LIB_API ELMO_INT32 MMC_ChangeAxisEcatOPState(
	IN  MMC_CONNECT_HNDL hConn,
	IN  MMC_AXIS_REF_HNDL hAxisRef,
	IN  MMC_CHANGE_ECAT_STATE_IN* pInParam,
	OUT MMC_CHANGE_ECAT_STATE_OUT* pOutParam);
//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif

#endif /* MMC_PLCOPEN_SINGLE_API_H */

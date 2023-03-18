/*
============================================================================
 Name : CPP_Template.h
 Author  :		Benjamin Spitzer
 Version :
 Description : 	GMAS C/C++ project header file for Template
============================================================================
*/
/*
============================================================================
 Project general functions prototypes
============================================================================
*/
void MainInit();
void MachineSequences();
void MainClose();
void MachineSequencesInit();
void EnableMachineSequencesTimer(int TimerCycle);
void BackgroundProcesses();
void MachineSequencesClose();
int MachineSequencesTimer();
void ReadAllInputData();
void WriteAllOutputData();
void MMC_MbusReadHoldingRegisterTable_wrapper(MMC_MODBUSREADHOLDINGREGISTERSTABLE_IN *mbus_read_in, MMC_MODBUSREADHOLDINGREGISTERSTABLE_OUT *mbus_read_out);
void MMC_MbusWriteHoldingRegisterTable_wrapper(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN *mbus_write_in,MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_OUT *mbus_write_out);
void MMC_MbusStartServer_wrapper();
void MMC_MbusStopServer_wrapper() ;
void InsertLongVarToModbusShortArr(short* spArr, long lVal) ;
int OnRunTimeError(const char *msg,  unsigned int uiConnHndl, unsigned short usAxisRef, short sErrorID, unsigned short usStatus) ;
void MMC_MbusStartServer_wrapper() ;
void Emergency_Received(unsigned short usAxisRef, short sEmcyCode) ;
void ModbusWrite_Received() ;
int  CallbackFunc(unsigned char* recvBuffer, short recvBufferSize,void* lpsock);
/*
============================================================================
 States functions
============================================================================
*/
void StateFunction_1();							// TODO: Change the name of these functions accordingly
	void SubState1_1PowerOn();
	void SubState1_2WPowerOn();
	void SubState1_3Function();
	void SubState1_4Function();

void StateFunction_2 () ;						// TODO: Change the name of these functions accordingly
	void SubState2_1Function();


void StateFunction_3 () ;
void StateFunction_4 () ;
void StateXYDefaultFunction();
void MMCPP_InitConnection() ;
/*
============================================================================
 General constants
============================================================================
*/
#define 	MAX_AXES				2		// number of Physical axes in the system. TODO Update MAX_AXES accordingly
#define 	FALSE					0
#define 	TRUE					1
//
// TODO: Modbus memory map offsets must be updated accordingly.
#define 	MODBUS_READ_OUTPUTS_INDEX	0	// Start of Modbus read address
#define 	MODBUS_UPDATE_START_INDEX	16	// Start of Modbus write address (update to host)
#define 	MODBUS_UPDATE_START_INDEX	16	// Start of Modbus write address (update to host)
#define 	MODBUS_UPDATE_CNT			16	// Number of registers to update
/*
============================================================================
 Project constants
============================================================================
*/
#define		SLEEP_TIME				10000	// Sleep time of the backround idle loop, in micro seconds
#define		TIMER_CYCLE				20		// Cycle time of the main sequences timer, in ms
/*
============================================================================
 States Machines constants
============================================================================
*/
#define 	FIRST_SUB_STATE			1

enum eMainStateMachines						// TODO: Change names of state machines to reflect dedicated project
{
	eIDLE		= 	0,
	eSM1 		= 	1,						// Main state machine #1 - PTP
	eSM2		= 	2,						// Main state machine #2 - Home
	eSM3		= 	3,						// Main state machine #3 - Stop
	eSM4		= 	4,						// Main state machine #3 - Stop
} ;

enum eSubStateMachine_1						// TODO: Change names of sub-state machines.
{
	eSubState_SM1_PowerOff  = 1	 ,
	eSubState_SM1_WPowerOff	 ,
	eSubState_SM1_ChOPMode   ,
	eSubState_SM1_WChOPMode	 ,
	eSubState_SM1_PowerOn 	 ,
	eSubState_SM1_WPowerOn 	 ,
	eSubState_SM1_Move1 	 ,
	eSubState_SM1_WMove1 	 ,
	eSubState_SM1_Move2 	 ,
	eSubState_SM1_WMove2 	 ,
};
enum eSubStateMachine_2						// TODO: Change names of sub-state machines.
{
	eSubState_SM2_PowerOff  = 1	 ,
	eSubState_SM2_WPowerOff	 	 ,
	eSubState_SM2_ChOPModeHome   ,
	eSubState_SM2_WChOPModeHome	 ,
	eSubState_SM2_PowerOn 	 ,
	eSubState_SM2_WPowerOn 	 ,
	eSubState_SM2_DOHOME 	 ,
	eSubState_SM2_WDOHOME 	 ,
};

enum eSubStateMachine_3						// TODO: Change names of sub-state machines.
{
	eSubState_SM3_Stop  = 1	 ,
	eSubState_SM3_WStop	 	 ,
	eSubState_SM3_PowerOff ,
	eSubState_SM3_WPowerOff ,
};

enum eSubStateMachine_4						// TODO: Change names of sub-state machines.
{
	eSubState_SM4_PowerOff  = 1	 ,
	eSubState_SM4_WPowerOff	 ,
	eSubState_SM4_ChOPMode   ,
	eSubState_SM4_WChOPMode	 ,
	eSubState_SM4_PowerOn 	 ,
	eSubState_SM4_WPowerOn 	 ,
	eSubState_SM4_Move1 	 ,
	eSubState_SM4_WMove1 	 ,
	eSubState_SM4_Move2 	 ,
	eSubState_SM4_WMove2 	 ,
	eSubState_SM4_DelayCycle	 ,
};

/*
============================================================================
 Application global variables
============================================================================
*/
int 	giTerminate;		// Flag to request program termination
int		giReentrance;		// Used to detect reentrancy to the main timer function
//
int 	giTempState1;		// Holds temp state
int 	giTempState2;		// Holds temp state
int 	giState1;			// Holds the current state of the 1st main state machine
int 	giPrevState1;		// Holds the value of giState1 at previous cycle
int		giSubState1;		// Holds teh current state of the sub-state machine of 1st main state machine
//
int 	giState2;			// Holds the current state of the 2nd main state machine
int 	giPrevState2;		// Holds the value of giState2 at previous cycle
int		giSubState2;		// Holds the current state of the sub-state machine of 2nd main state machine
//
// 	Examples for data read from the GMAS core about the X, Y drives
int		giXTorque;
int		giYTorque;
int		giXInMotion;
int		giYInMotion;
int 	giStatus[MAX_AXES] ;
int 	giPos[MAX_AXES] ;
int 	giYPos ;
//
/*
============================================================================
 Global structures for Elmo's Function Blocks
============================================================================
*/
MMC_CONNECT_HNDL gConnHndl ;					// Connection Handle
CMMCConnection cConn ;
CMMCSingleAxis 	cAxes[MAX_AXES] ;
MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN 	mbus_write_in;
MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_OUT 	mbus_write_out;
MMC_MOTIONPARAMS_SINGLE 	stSingleDefault ;	// Single axis default data
MMC_HOMEDS402_IN			stDS402Home ;

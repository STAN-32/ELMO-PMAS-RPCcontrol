/*
============================================================================
 Name : 	CPP_CyclicPosHome.cpp
 Author :	Benjamin Spitzer
 Version :	1.00
 Description : The following example supports the following functionalities:

	 - Modbus callback registration.
	 - Emergency callback registration.
	 - Modbus reading and updates of axis status and positions.
	 - Dig In and out are used.
 	 - Point to Point
 	 - Homing
 	 - Stop All axes
	 - Move Pulses
	 - Start move Pulses depending on digital input

 The program works with MAX_AXES in DS402 Profile Position and DS402 Homing motion modes. These are configured automatically by
 the called functions.
 For the above functions, the following modbus 'codes' are to be sent to address 40001:

 	 - Point to Point 	- 1. Performs a Cyclic Position motion, back and fourth, and sets power off to all MAX_AXES.
 	 - Homing			- 2. Performs a Homing on index, and sets power off to all MAX_AXES.
 	 - Stop All axes	- 3. Stops current motion and sets all motors off to all MAX_AXES.
 	 - Move Pulses 		- 4. Performs synchronized motions for MAX_AXES, NUM_MOTIONS times. And then changes direction NUM_MOTIONS times.
 	  	  	  	  	  	  	  This works infinately until stopped (by calling Stop All axes). Also - Digital Outputs are set at motion end

	The following information is updated to the Modbus at address MODBUS_UPDATE_START_INDEX:
		- All positions of axes, depending on MAX_AXES.
		- Digital Inputs of axis 1(if mapped of course)

============================================================================
*/
#define ENDIAN_SELECT   123
#define OS_PLATFORM     777
#include "OS_PlatformDependSetting.h"
#include "OS_PlatformDataTypeSizeSet.h"
#include "OS_PlatformLinuxRpc64.hpp"
#include "MMC_definitions.h"
#include "hello.h" // For test, which successed.
#include "MMCPPlib.hpp"
#include "win32_motion.h"
// #include "CPP_CyclicPosHome.h"	// Application header file.
#include <iostream>
#include <stdint.h>
#include <sys/time.h>			// For time structure
#include <signal.h>				// For Timer mechanism


/* ============================================================================
  functions prototypes
============================================================================ */
int MainInit();
int CloseConnection();
void Emergency_Received(unsigned short usAxisRef, short sEmcyCode);


/* ============================================================================
 Function:		main()
 Description:    The main function of this sample project.
============================================================================ */
int main()
{
	int start;
	int end;

	int retval =0;
	int ret_stt=0;
	int i,j;
	unsigned long rc;

	if (MainInit() !=0)
	{
		printf("init failed!!!\n");
	}
	else
	{
		printf("success!!!!\n");
	}
	

	try
	{
		//enable axis and wait till axis enable is done  
		cAxis[0].PowerOn();
		while (! cAxis[0].ReadStatus() & NC_AXIS_STAND_STILL_MASK);

		
		cAxis[0].MoveVelocity(300);// uint: cnt/sec ------------- 24cnt/r
		//cAxis[0].MoveAbsolute(500);
		sleep(3000);

		//stop axis wait till its in a 'standstill' state 
		cAxis[0].Stop();
		while (! cAxis[0].ReadStatus() & NC_AXIS_STAND_STILL_MASK);

		//disable axis 
		cAxis[0].PowerOff();
	}

	catch (CMMCException exp)
	{
		cout<<"main function exception!!"<<exp.what()<< exp.error()<<endl;
	}


	CloseConnection();
	return 0;
}


/* ============================================================================
 Function:		MainInit()
 Description:	Initilaize the system, including axes, communication, etc.
============================================================================ */
int MainInit()
{

	int (*fun_ptr)(unsigned char*, short,void*);
	int retval,indx;
	int iCount;	

	fun_ptr=NULL;

	printf ("init connection\n");

	conn_param.uiTcpPort = 4000;
    strcpy((char*)conn_param.ucIp , "192.168.1.3"); //target IP

	
	g_conn_hndl  =cConn.ConnectRPCEx("192.168.1.2","192.168.1.3",0x7fffffff,NULL);
	

	// Register the callback function for Emergency:
	cConn.RegisterEventCallback(MMCPP_EMCY,(void*)Emergency_Received) ;
	
	// Set Try-Catch flag Enable\Disable
	CMMCPPGlobal::Instance()->SetThrowFlag(true);
	CMMCPPGlobal::Instance()->SetThrowWarningFlag(false);


	
	try
	{
		cAxis[0].InitAxisData("a01", g_conn_hndl);
		cAxis[1].InitAxisData("a02", g_conn_hndl);

		for(iCount = 0 ; iCount < 2 ; iCount++)
		{
			giStatus = cAxis[iCount].ReadStatus();

			if(giStatus & NC_AXIS_ERROR_STOP_MASK)
			{
				cAxis[iCount].Reset() ;
				sleep(1) ;
				giStatus 	= cAxis[iCount].ReadStatus() ;
				if(giStatus & NC_AXIS_ERROR_STOP_MASK)
				{
					//PRNT4("MainInit: axis ",iCount," status error",endl);
				}
			}
		}
	}
	catch (CMMCException exp)
	{
		cout<<"init failed!!"<<exp.what()<<endl;
	}

	
	return 0;
}

/* ============================================================================
 Function:				CloseConnection()
 Description: 
 ============================================================================ */
int CloseConnection()
{
	int retval;
	printf ("close connection\n");

	retval = MMC_CloseConnection(g_conn_hndl);

	if ( retval != 0)
	{
		printf("ERROR CloseConnection: MMC_CloseConnection fail %d\n",  retval);
		return (-1);
	}

    return (0);
}


/* ============================================================================
 Function:				Emergency_Received()
 Description:
============================================================================ */
void Emergency_Received(unsigned short usAxisRef, short sEmcyCode)
{
	printf("Emergency Message Received on Axis %d. Code: %x\n",usAxisRef,sEmcyCode) ;
}


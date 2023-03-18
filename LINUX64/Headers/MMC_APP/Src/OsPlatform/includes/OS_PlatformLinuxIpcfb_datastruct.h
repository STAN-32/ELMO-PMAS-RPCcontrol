//////////////////////////////////////////////////////////////////////////////////////////////////
/// file name   : fb_datastructs.h
/// Author      : Alex Kushnir
/// Created on  : Oct 27, 2011
/// Version     : 0.0.1
///               1.0.0 Haim Hillel
///               1.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.3.0 Haim Hillel Update 13Aug2017
///				  0.4.0 Updated 11Sep2017 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain FB data structures in order to receive FB status without IPC
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OS_PLATFORMLINUXIPCFB_DATASTRUCT_H_
#define OS_PLATFORMLINUXIPCFB_DATASTRUCT_H_

#define NC_DRV_NAME "/dev/nc0"



typedef struct
{
    ELMO_UINT8 ucDummy;
} MMC_GETSHMSIZE_IN;


typedef struct
{
    ELMO_ULINT32 ulShmSize;
    ELMO_UINT16  usStatus;
    ELMO_INT16   usErrorID;
} MMC_GETSHMSIZE_OUT;

typedef struct
{
    ELMO_UINT8	ucDummy;
} MMC_GETFBDATAOFFSET_IN;

typedef struct
{
    ELMO_UINT32 uiFBDataOffset;
	ELMO_UINT32 uiParams[20];	//space for 20 parameters
} MMC_GETFBDATAOFFSET_OUT;

typedef struct
{
	MC_PATH_REF hMemHandle;
} MMC_GETTABLEOFFSET_IN;

typedef struct
{
	ELMO_UINT32 uiHeaderOffset;
	ELMO_UINT32 uiDataOffset;
    ELMO_UINT16 usStatus;
    ELMO_INT16  usErrorID;
} MMC_GETTABLEOFFSET_OUT;


#endif      /* #define OS_PLATFORMLINUXIPCFB_DATASTRUCT_H_ */

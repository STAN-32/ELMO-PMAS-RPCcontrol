////////////////////////////////////////////////////////////////////////////////
/// Name        : OS_PlatformsSelect.h
/// Author      : Haim Hillel
/// Created on  : 29Jan2013
/// Version     : 0.0.1,
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
///               0.3.0 Updated 03Aug2015 Haim H. support Littlendian & Bigendian GMAs.
///               0.4.0 Updated 11Sep2017 Haim H.
///               0.4.1 Updated 10Jul2019 Haim H.
///               0.4.2 Updated 26Aug2019 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain Maestro global definitions for:
///               Selecting target OS (OS Platform) as well as Cpu Endian (CPU Platform type).
///               The file contain 3 parts, user MAY EDIT ONLY TWO SYMBOLS IN 'PART 2':
///                         ENDIAN_SELECT   and   OS_PLATFORM
///               Selecting/set ENDIAN_SELECT according to:
///                 IPC:
///                     ENDIAN_SELECT:
///                         Maestro proccessing the commands_requst (from applications) and the CPU
///                         running the applications (programs) are same (=> same Endian) => set:
///                                 IPC_ENDIAN_IS_TRNSP
///                     OS_PLATFORM:
///                         Select/set the Operating System, currentryl for IPC supporting only:
///                                 LINUXIPC32_PLATFORM
///                 RPC:
///                     ENDIAN_SELECT:
///                         CPU (Maestro) proccessing the commands_requst and the CPU running user
///                                 the applications (programs) are differents CPUs (may be => same
///                                 or different Endian...), investigation and set according for
///                                 Different or Same Endian is automatic and done ON RUN TIME => set:
///                                     RPC_ENDIAN_AUTO_SET
///                     OS_PLATFORM:
///                         Select/set the OS (Platform) to one of:
///                                     LINUXIPC32_PLATFORM  
///                                     WIN32_PLATFORM     
///                                     WIN64_PLATFORM     
///                                     LINUXRPC32_PLATFORM
///                                     LINUXRPC64_PLATFORM
///                                     VXWORKS32_PLATFORM   
///               ==================================================================================
///               E.g1: 
///                  /* Application is RPC on Windows 32 bits => sets */
///               #define ENDIAN_SELECT   RPC_ENDIAN_AUTO_SET
///               #define OS_PLATFORM     WIN32_PLATFORM
/// 
///               E.g2:
///                  /* Application is IPC (=> ENDIAN is transparent, same as Maestro)  */
///                  /* Application OS is on Linux 32 (our IPC)                         */
///               #define ENDIAN_SELECT   IPC_ENDIAN_IS_TRNSP
///               #define OS_PLATFORM     LINUXIPC32_PLATFORM
///               ==================================================================================
///
///                     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
///                     The TWO above SYMBOLS ('PART 2' symbols) should be define somewhere.
///                     It possible define them on Compile setting
///                     (if so they should not define in 'PART 2' see below).
///                     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
///
////////////////////////////////////////////////////////////////////////////////
#ifndef OS_PLATFORMSSELECT_H_
#define OS_PLATFORMSSELECT_H_
/* ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------ */


/* --------------------------------   PART 1: Endian & Platform Symbols definitions  -------------------------------------- */
                                    /*---------------------*\
                                    |* SHOULD NOT BE EDIT  *|
                                    \*---------------------*/
        /* CPU ENDIAN TYPE: */
                                    /* AUTOMATIC, target Endian set on run time - auto setting for be same or diff from host*/
#define RPC_ENDIAN_AUTO_SET 123
                                    /* TRANSPARENT Endian, user program and Maestro are on same CPU so they are SAME ENDIAN */
                                    /* - its Transperant - no specific or auto set/change for big or little Endian.         */
#define IPC_ENDIAN_IS_TRNSP 999


        /* SUPPORTING OS PLATFORM: */
#define LINUXIPC32_PLATFORM 333
#define WIN32_PLATFORM      444
#define WIN64_PLATFORM      555
#define LINUXRPC32_PLATFORM 666
#define LINUXRPC64_PLATFORM 777
#define VXWORKS32_PLATFORM  888
/* ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------ */




/* --------------------------------   PART 2: Endian and OS Platform Select    -------------------------------------------- */
                        /*--------------------------------------------------*\
                        |* Two below symbols (ENDIAN_SELECT & OS_PLATFORM)  *|
                        |* SHOULD BE SETTING (DEFINE) ACCORDING USING ENVI. *|
                        |*                                                  *|
                        |* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! *|
                        |* Differents possibility for define them:          *|
                        |*  1. Edit and assign in this file (below),        *|
                        |*  2. Setting in compiler setup (Visual & Eclips), *|
                        |*  3. Setting in builds make file (VxWorsk).       *|
                        |* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! *|
                        \*--------------------------------------------------*/
                        
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
// Setting of the symbols (definitions) moved (able to be moveing) to COMPILER SETUP ('2.' above)
//      not needs edit this file according change of application type (IPC/RPC), set it once in the
//      using tool (Linux Eclipse / Win Eclipse / Win Visual), which is specific for applicaiton
//      type and platform (most of all).
//      setting on Eclipse:
//          <project> / Properties / C/C++ Build / Settings / Tool Settings / Symbols:
//          ENDIAN_SELECT=999
//          OS_PLATFORM=333
//  Do not delete below setting (even they appearing as comments):
// ================================================================================================================
//                            /*  target CPU Endian (see above) */
//#define ENDIAN_SELECT   RPC_ENDIAN_AUTO_SET
// or:
//#define ENDIAN_SELECT   IPC_ENDIAN_IS_TRNSP
//
//                            /* Assign target OS (see above)   */
//#define OS_PLATFORM     WIN32_PLATFORM
/* ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------ */


/* --------------------------------   PART 3: Validation    --------------------------------------------------------------- */
                                    /*---------------------*\
                                    |* SHOULD NOT BE EDIT  *|
                                    \*---------------------*/
                            /* Validation assignments of CPU Endian type */
#if   ((ENDIAN_SELECT == RPC_ENDIAN_AUTO_SET) || (ENDIAN_SELECT == IPC_ENDIAN_IS_TRNSP))
    /* Do Nothing - its OK */
#else
    #error "***OS_PlatformsSelect.h: Symbol 'ENDIAN_SELECT' should set to one of: 'RPC_ENDIAN_AUTO_SET' or 'IPC_ENDIAN_IS_TRNSP' "
#endif
                            
                            /* Confirmation (check) for well assignment of OS Platform */
#if (                                              \
        (OS_PLATFORM == LINUXIPC32_PLATFORM)||     \
        (OS_PLATFORM == WIN32_PLATFORM)     ||     \
        (OS_PLATFORM == WIN64_PLATFORM)     ||     \
        (OS_PLATFORM == LINUXRPC32_PLATFORM)||     \
        (OS_PLATFORM == LINUXRPC64_PLATFORM)||     \
        (OS_PLATFORM == VXWORKS32_PLATFORM)        \
    )
#else
    #error "***OS_PlatformsSelect.h: Symbol 'OS_PLATFORM' should set to one of: 'LINUXIPC32_PLATFORM', 'WIN32_PLATFORM', Etc... (See OS_PlatformSelect.h) "
#endif
/* ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------ */

        /* OS_PLATFORMSSELECT_H_ */
#endif


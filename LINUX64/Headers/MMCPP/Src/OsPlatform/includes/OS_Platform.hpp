////////////////////////////////////////////////////////////////////////////////
/// Name        : Os_Platform.hpp
/// Author      : Haim Hillel
/// Created on  : 01Mar2015
/// Version     : 0.0.1
///               0.3.0 Updated 03Aug2015 Haim H. support Littlendian & Bigendian GMAs.
///				  0.4.0 Updated 11Sep2017 Haim H.
/// Copyright   : Your copyright notice
/// Description : GMAS Operating System & Platform dependencies data type and definitions.
///                 Actual loading (within this files, specific platform and specific Endian)
///                 selecting by symbols in OS_PlatformsSelect.h
////////////////////////////////////////////////////////////////////////////////

#ifndef OS_PLATFORM_HPP_
#define OS_PLATFORM_HPP_


#if   (OS_PLATFORM == LINUXIPC32_PLATFORM)
    #include "OS_PlatformLinuxIpc32.hpp"
    
#elif (OS_PLATFORM == WIN32_PLATFORM)
    #include "OS_PlatformWin32.hpp"
    
#elif (OS_PLATFORM == WIN64_PLATFORM)
    #include "OS_PlatformWin64.hpp"
    
#elif (OS_PLATFORM == LINUXRPC32_PLATFORM)
    #include "OS_PlatformLinuxRpc32.hpp"
    
#elif (OS_PLATFORM == LINUXRPC64_PLATFORM)
    #include "OS_PlatformLinuxRpc64.hpp"
    
#elif (OS_PLATFORM == VXWORKS32_PLATFORM)
    #include "OS_PlatformVxWorks32.hpp"
    
#else
    #error "***OS_Platform.hpp: Symbol 'OS_PLATFORM' should set to one of: 'LINUXIPC32_PLATFORM', 'WIN32_PLATFORM', Etc... (See OS_PlatformSelect.h) "
#endif

                            /* For Debug (Compilation sybol trace in RT variable) */
                            /* ************************************************** */
extern ELMO_INT32 gicpp_RPC_ENDIAN_AUTO_SET    ;
extern ELMO_INT32 gicpp_IPC_ENDIAN_IS_TRNSP    ;
       
extern ELMO_INT32 gicpp_LINUXIPC32_PLATFORM    ;
extern ELMO_INT32 gicpp_WIN32_PLATFORM         ;
extern ELMO_INT32 gicpp_WIN64_PLATFORM         ;
extern ELMO_INT32 gicpp_LINUXRPC32_PLATFORM    ;
extern ELMO_INT32 gicpp_LINUXRPC64_PLATFORM    ;
extern ELMO_INT32 gicpp_VXWORKS32_PLATFORM     ;
       
extern ELMO_INT32 gicpp_ENDIAN_SELECT          ;
extern ELMO_INT32 gicpp_OS_PLATFORM            ;
       
extern ELMO_INT32 gicpp_CPPOS_PLATFORMID       ;

extern DLLMMCPP_API void print_MMCPP_API_Lib3264Characteristic(
                                            ELMO_INT32 _prm_iRPC_ENDIAN_AUTO_SET,
                                            ELMO_INT32 _prm_iIPC_ENDIAN_IS_TRNSP,
                                        
                                            ELMO_INT32 _prm_iLINUXIPC32_PLATFORM,
                                            ELMO_INT32 _prm_iWIN32_PLATFORM     ,
                                            ELMO_INT32 _prm_iWIN64_PLATFORM     ,
                                            ELMO_INT32 _prm_iLINUXRPC32_PLATFORM,
                                            ELMO_INT32 _prm_iLINUXRPC64_PLATFORM,
                                            ELMO_INT32 _prm_iVXWORKS32_PLATFORM ,
                                        
                                            ELMO_INT32 _prm_iENDIAN_SELECT      ,
                                            ELMO_INT32 _prm_iOS_PLATFORM        
                                         );

        /* OS_PLATFORM_HPP_ */
#endif


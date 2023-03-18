////////////////////////////////////////////////////////////////////////////////
/// File name   : Operating System Platform Data Type Size Set (select)
/// Author      : Haim Hillel
/// Created on  : 20Oct2014
/// Version     : 0.0.1,
///               0.2.0 Updated 20Jan2015 Haim H. native Data Types (names), for supporting 64B OS.
/// Copyright   : Your copyright notice
/// Description : This file contain GMAS Operating System Platform Basic data
///                 type definitions. Specific define should set according to
///                 carry platform (32B / 64B / Win / Linux...)
////////////////////////////////////////////////////////////////////////////////

#ifndef OS_PLATFORMDATATYPESIZESET_H_
#define OS_PLATFORMDATATYPESIZESET_H_

#ifdef PROAUT_CHANGES
  #if defined(_WIN64)
    // Microsoft Windows (64-bit)
  #elif defined(_WIN32)
    // Microsoft Windows (32-bit) 
    //#include <stdint.h>
    //#define __int64 int64_t
    #define __int64 long long
  #elif defined(__linux__)
    // -- Linux --
  #endif

#endif

    #define ELMO_TRUE                    1
    #define ELMO_FALSE                   0

                        /* In GNU and Visual C++ defined:           */
                        /*      __cplusplus (Not define in GNU C)   */
                        /*      bool                                */
    #if defined(__cplusplus)
        typedef bool                    ELMO_BOOL;
    #else
        typedef unsigned char           ELMO_BOOL;
    #endif
   
                        /* In Gnu and MSV char is unsigned char...  */
    typedef          char               ELMO_INT8;

    typedef signed   char               ELMO_SINT8;
    typedef unsigned char               ELMO_UINT8;
    typedef signed   char*              ELMO_PSINT8;
    typedef          char*              ELMO_PINT8;
    typedef unsigned char*              ELMO_PUINT8;
    
    typedef          short              ELMO_INT16;
    typedef unsigned short              ELMO_UINT16;
    typedef          short*             ELMO_PINT16;
    typedef unsigned short*             ELMO_PUINT16;
    
    typedef          int                ELMO_INT32;
    typedef unsigned int                ELMO_UINT32;
    typedef          int*               ELMO_PINT32;
    typedef unsigned int*               ELMO_PUINT32;

// !!!
// Keep signe marks it was original long...
// Along GMAS interface translate the long to int.
// !!!
//    typedef long                      ELMO_LINT32;
//    typedef unsigned long             ELMO_ULINT32;
//    typedef long*                     ELMO_PLINT32;
//    typedef unsigned long*            ELMO_PULINT32;
    typedef          int                ELMO_LINT32;
    typedef unsigned int                ELMO_ULINT32;
    typedef          int*               ELMO_PLINT32;
    typedef unsigned int*               ELMO_PULINT32;
    
    typedef void*                       ELMO_PVOID;
    
    typedef float                       ELMO_FLOAT;
    typedef float*                      ELMO_PFLOAT;
    typedef double                      ELMO_DOUBLE;
    typedef double*                     ELMO_PDOUBLE;

#if   (OS_PLATFORM == LINUXIPC32_PLATFORM)
    typedef             long long int   ELMO_INT64;
    typedef unsigned    long long int   ELMO_UINT64;
    typedef             long long int*  ELMO_PINT64;
    typedef unsigned long long int*     ELMO_PUINT64;
#elif (OS_PLATFORM == WIN32_PLATFORM   )
    typedef             __int64         ELMO_INT64;
    typedef unsigned    __int64         ELMO_UINT64;
    typedef             __int64*        ELMO_PINT64;
    typedef unsigned    __int64*        ELMO_PUINT64;
#elif (OS_PLATFORM == WIN64_PLATFORM)
    typedef             __int64         ELMO_INT64;
    typedef unsigned    __int64         ELMO_UINT64;
    typedef             __int64*        ELMO_PINT64;
    typedef unsigned    __int64*        ELMO_PUINT64;
#elif (OS_PLATFORM == LINUXRPC32_PLATFORM)
    typedef             long long int   ELMO_INT64;
    typedef unsigned    long long int   ELMO_UINT64;
    typedef             long long int*  ELMO_PINT64;
    typedef unsigned    long long int*  ELMO_PUINT64;
#elif (OS_PLATFORM == LINUXRPC64_PLATFORM)
    typedef             long long int   ELMO_INT64;
    typedef unsigned    long long int   ELMO_UINT64;
    typedef             long long int*  ELMO_PINT64;
    typedef unsigned    long long int*  ELMO_PUINT64;
#elif (OS_PLATFORM == VXWORKS32_PLATFORM )
    typedef             long long int   ELMO_INT64;
    typedef unsigned    long long int   ELMO_UINT64;
    typedef             long long int*  ELMO_PINT64;
    typedef unsigned    long long int*  ELMO_PUINT64;
#else
    #error "***OS_PlatfomDataTypeSizeSet.h: Symbol 'OS_PLATFORM' should set to one of: 'LINUXIPC32_PLATFORM', 'WIN32_PLATFORM', Etc... (See OS_PlatformSelect.h) "
#endif

#endif  /* #ifndef  OS_PLATFORMDATATYPESIZESET_H_    */


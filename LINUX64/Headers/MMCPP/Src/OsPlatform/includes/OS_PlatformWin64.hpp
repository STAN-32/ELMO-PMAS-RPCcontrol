////////////////////////////////////////////////////////////////////////////////
/// File name   : os_platformWin64.hpp
/// Author      : Haim Hillel
/// Created on  : 01Mar2015
/// Version     : 0.0.1
///               0.3.0 Updated 03Aug2015 Haim H. support Littlendian & Bigendian GMAs.
///				  0.4.0 Updated 11Sep2017 Haim H.
/// Copyright   : Your copyright notice
/// Description : This file contain GMAS RPC WIN64 Operating System  Platform dependencies.
///               The file is selected to be including in OS_Platform.h in case target select to be WIN64.
////////////////////////////////////////////////////////////////////////////////

#ifndef OS_PLATFORMWIN64_HPP_
#define OS_PLATFORMWIN64_HPP_ 

#include <sys/utime.h>
    
#include <fcntl.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits>
#include <istream>
#include <Ws2tcpip.h>
#include <float.h>


#ifdef LIBMMCPPLIB_EXPORTS
    #define DLLMMCPP_API __declspec(dllexport)
#else
    #define DLLMMCPP_API __declspec(dllimport)
#endif

#ifndef PROAUT_CHANGES
	#pragma warning (disable : 4251)
#endif

        /* OS_PLATFORMWIN64_HPP_  */
#endif


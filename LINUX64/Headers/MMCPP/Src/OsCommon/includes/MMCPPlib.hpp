#ifndef MMCPPLIB_HPP_
#define MMCPPLIB_HPP_

#include "MMCAxis.hpp"          
#include "MMCBulkRead.hpp"      
#include "MMCConnection.hpp"    
#include "MMCDS401Axis.hpp"
#include "MMCDS406Axis.hpp"     
#include "MMCEcatIo.hpp"        
#include "MMCEoE.hpp"           
#include "MMCErrorCorr.hpp"     
#include "MMCGroupAxis.hpp"     
#include "MMCHostComm.hpp"      
#include "MMCMessage.hpp"       
#include "MMCModbusBuffer.hpp"  
#include "MMCModbusSwapBuffer.hpp"
#include "MMCMotionAxis.hpp"    
#include "MMCNetwork.hpp"       
#include "MMCNode.hpp"          
#include "MMCPIBulk.hpp"        
#include "MMCPIVar.hpp"         
#include "MMCPPGlobal.hpp"      
#include "MMCPPlib.hpp"         
#include "MMCSingleAxis.hpp"    
#include "MMCSocket.hpp"        
#include "MMCTcp.hpp"           
#include "MMCUdp.hpp"           
#include "MMCUserParams.hpp"    
#include "MMCRTSingleAxis.hpp"
#include "MMCRTGroupAxis.hpp"

#include "MMCPIVarRT.hpp"
#include "MMCPPGlobalRT.hpp"
#include "MMCCodesysShm.hpp"
#include "MMCPPIMU.hpp"
#include "MMCSerialPort.hpp"

//#ifndef WIN32
#if (OS_PLATFORM == LINUXIPC32_PLATFORM)
    #include "MMCEIPDataType.hpp"
    #include "MMCEIPSession.hpp"
#endif

#endif      /* #ifndef MMCPPLIB_HPP_ */































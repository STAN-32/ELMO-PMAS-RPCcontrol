/*
 * MMCPPIMU.h
 *
 *  Created on: 04/01/2018
 *      Author: zivb
 */

#ifndef MMCPPIMU_HPP_
#define MMCPPIMU_HPP_

//#ifndef WIN32
#if (OS_PLATFORM == LINUXIPC32_PLATFORM)

// ????? Really Necessary ?????
    // #include <stropts.h>
    #include <math.h>
    // #include <stropts.h>
// ????? Really Necessary ?????
    

    #include "MMC_definitions.h"
    
    #include "MMCAxis.hpp"
    #include "MMCNode.hpp"
    #include "MMCMotionAxis.hpp"
    #include "MMCPPGlobal.hpp"
    #include "MMCSingleAxis.hpp"
    

    
    #define STIM300_BAUDRATE                        1843200
    //#define   STIM300_BAUDRATE                    921600
    
    #define PAGE_SIZE                               4096UL
    #define TTY_BUF_SIZE                            PAGE_SIZE
    #define STIM300_DATAGRAM_BASE_PORT_1            0UL
    #define STIM300_DATAGRAM_BASE_PORT_2            64UL
    #define STIM300_DATAGRAM_BASE_PORT_3            128UL
    #define STIM300_DATAGRAM_BASE_PORT_4            192UL
    #define STIM300_DATAGRAM_PAYLOAD_CNT_OFFSET     35UL
    
    #define STIM300_DATAGRAM_BASE_PORT_1_RESET_IO   0x8
    #define STIM300_DATAGRAM_BASE_PORT_2_RESET_IO   0x4
    #define STIM300_DATAGRAM_BASE_PORT_3_RESET_IO   0x2
    #define STIM300_DATAGRAM_BASE_PORT_4_RESET_IO   0x1
    #define STIM300_DATAGRAM_BASE_RESET_IO_IDLE     STIM300_DATAGRAM_BASE_PORT_1_RESET_IO + STIM300_DATAGRAM_BASE_PORT_2_RESET_IO + STIM300_DATAGRAM_BASE_PORT_3_RESET_IO + STIM300_DATAGRAM_BASE_PORT_4_RESET_IO
    
    #define UDP_SIGNAL_TIME                         15 // was 19.  Changed to 15 so the duty cycle will be reduced to 40%
    #define MAMS_SIGNAL_OFFSET_FROM_SYSTEM_SYNC     0  // was 3. 5/3/2017 - Benji
    
    #define STIM300_DATAGRAM_SIZE       44UL
    
    #define NC_DRV_IOC_MAGIC            'k'
    #define NC_IOCUARTEVENT             _IOW(NC_DRV_IOC_MAGIC,  41, ELMO_UINT8)
    #define NC_DEV                      "/dev/nc0"  //for nc_proc kernel module
    
    #define STIM300_RX_DEV_1            "/dev/ttyO0"
    #define STIM300_RX_DEV_2            "/dev/ttyO1"
    #define STIM300_RX_DEV_3            "/dev/ttyO3"
    #define STIM300_RX_DEV_4            "/dev/ttyO9"
    

    typedef ELMO_PVOID (*MMC_STIM_CB_FUNC)(ELMO_PVOID);
    ELMO_PVOID STIM300SyncThreadFunc(ELMO_PVOID arg);
    
    class DLLMMCPP_API CMMCPPIMU
    {
    public:
        virtual ~CMMCPPIMU();
        CMMCPPIMU();
        void init(ELMO_UINT8 cPort_index, ELMO_INT32 iBaud, ELMO_UINT32 iSize);
    
        ELMO_INT32  m_IMU_fd;
        ELMO_PUINT8 m_pShmPtr;
        ELMO_UINT8  m_ucPortIndex;
        ELMO_INT32  m_iBaud;
        ELMO_INT32  m_iSize;
        ELMO_PINT32 m_Buff;
    
    private:
        ELMO_INT32 set_interface_attribs_custom (ELMO_INT32 fd, ELMO_INT32 speed, ELMO_INT32 parity);
    };

#endif


#endif /* MMCPPIMU_H_ */

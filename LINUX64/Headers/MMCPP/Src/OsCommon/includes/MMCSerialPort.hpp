/*
 * MMCSerialPort.h
 *
 *  Created on: 23/05/2018
 *      Author: michaelf
 */

#ifndef MMCSERIALPORT_HPP_
#define MMCSERIALPORT_HPP_


#if defined(_PLATINUM) || defined(pmas) || defined(PMAS)
#if   (OS_PLATFORM == LINUXIPC32_PLATFORM)

#include <stdint.h>

/*
* see bits/termios.h vs. asm/termios.h
* overcome re-declaration problem  on application level @YL 20190131
* definitions below were taken from termbits.h
*/
//#ifdef __ASM_ARM_TERMBITS_H
#undef CSTOPB
#undef CREAD
#undef PARENB
#undef PARODD
#undef CMSPAR

#define CSTOPB  0000100
#define CREAD   0000200
#define PARENB  0000400
#define PARODD  0001000
#define CMSPAR  010000000000
//#endif //__ASM_ARM_TERMBITS_H

#include <time.h>
#include <memory>
#include "MMCPPGlobal.hpp"

// forward declarations
class CMSP_Internal;
struct SMaestroSerialPortStat;


class DLLMMCPP_API CMaestroSerialPort {
public:

    // Normal mode - use standard /dev/ttyXX. Can be used for low speed
    //  (less that 500000 bps) and packets delineated by CR/LF
    // Enhanced mode - use ELMO-proprietary device driver that supports high speeds
    //  with fixed-length packets
    enum Mode {
        Normal,
        Enhanced
    };

    enum StopBits {
        SB_1 = 0,       // 1 stop bit
        SB_2 = CSTOPB   // 2 stop bits
    };

    enum Parity {
        NONE = 0,                       // no parity
        ODD = (PARENB|PARODD),          // enable parity and use odd
        EVEN = PARENB,                  // enable parity and use even
        MARK = (PARENB|PARODD|CMSPAR),  // mark parity
        SPACE = (PARENB|CMSPAR)         // space parity

    };

    // Timestamp fomat - selects clock to use for timestamp
    enum TsFormat {
        TS_REALTIME = CLOCK_REALTIME,
        TS_MONOTONIC = CLOCK_MONOTONIC,
        TS_MONOTONIC_RAW = CLOCK_MONOTONIC_RAW,
        TS_BOOTTIME = CLOCK_BOOTTIME,
        TS_NONE = 9999
    };

    struct SMaestroSerialPortCfg {

        // Normal/enhanced mode
        enum Mode mode;

        // blockingMode – false for blocking mode off, true for blocking mode on
        ELMO_BOOL blockingMode;
        // luneMode – false for line mode off,
        //            true for line mode on (i.e. termios canonical mode)
        ELMO_BOOL lineMode;

        enum StopBits stopBits;

        enum Parity parity;

        enum TsFormat timestampFormat;

        // speed (baud rate) - e.g. 9600, 115200, 921600, 1843200
        uint32_t speed;

        // rxFixedPacketSize – packet size for Rx in enhanced mode.
        // Not used in normal mode
        uint32_t rxFixedPacketSize;

        // default CTOR
        SMaestroSerialPortCfg() {
            mode = CMaestroSerialPort::Enhanced;
            blockingMode = false;
            lineMode = false;
            stopBits = CMaestroSerialPort::SB_1;
            parity = CMaestroSerialPort::NONE;
            timestampFormat = CMaestroSerialPort::TS_NONE;
            speed = 0;
            rxFixedPacketSize = 0;
        };
    };

    // CTOR
    CMaestroSerialPort();

    // DTOR
    virtual ~CMaestroSerialPort();

    // Open function
    // serial port must be Open'ed before use
    // ttyNum - in range 0:9
    // cfg - configuration
    // return: file descriptor (>=0)
    //         -1 on failure
    ELMO_INT32 Open(ELMO_INT32 ttyNum, SMaestroSerialPortCfg &cfg);

    // Close function
    //  It will be called automatically in DTOR if it was not called previously
    void Close();

    // Get Configuration
    // cfg - pointer to configuraion struct to fill
    // return - 0 on success, -1 on failure (e.g. not opened, cfg == NULL, ... )
    ELMO_INT32 ConfigurationGet(SMaestroSerialPortCfg *cfg);

    // Write function
    // same as C standard "write"
    ssize_t Write(const void* buf, size_t count);

    // Read function
    // in normal mode is the same as C standard "read"
    // in enhanced mode count must be equal to PacketSize,
    //      otherwise return -1
    ssize_t Read(ELMO_PVOID buf, size_t count);

    // ioctl interface
    // use it in normal mode only, using requests from <sys/ioctl.h>
    // example: FIONREAD to check number of bytes available for read
    ELMO_INT32 Ioctl(ELMO_INT32 request, ELMO_PINT8 argp);

    // returns File Descriptor of "active" (either normal or enhanced
    //      according Open's mode) interface.
    // use it for 'select'
    ELMO_INT32 FdActiveGet();

    // Timestamp of last good "Read" message
    // in normal mode - not implemented
    // in enhanced mode - timestamp of DMA's end-of-packet interrupt
    // returns 0 for success, -1 if no valid messages were received
    ELMO_INT32 Timestamp(struct timespec *ts);

    // get SMaestroSerialPortStat (in enhanced mode only)
    ELMO_INT32 StatGet(struct SMaestroSerialPortStat &msps);

private:
    std::auto_ptr<CMSP_Internal> pImpl;
};


struct SMaestroSerialPortStat {
    // statistics
    uint32_t tx_packets;
    uint32_t tx_dropped;
    uint32_t rx_packets;
    uint32_t rx_dropped;
    uint32_t rx_resync;
    uint32_t rx_skipped;
    // state
    uint32_t speed;
    uint32_t ts_format;
    uint32_t rx_packet_len;
    uint32_t blocking_mode;
    uint32_t rx_dma_burst;
    uint32_t rx_fifo_trig;
    uint32_t tx_cpu;
    uint32_t rx_cpu;
    uint32_t kern_log_level;
};


#endif

#endif  /* #if defined(_PLATINUM) || defined(pmas) || defined(PMAS) */

#endif /* MMCSERIALPORT_HPP_ */

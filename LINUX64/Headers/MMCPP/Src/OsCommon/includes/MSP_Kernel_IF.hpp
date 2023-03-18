/*
 * MSP_Kernel_IF.h
 *
 *  Created on: 28/05/2018
 *      Author: michaelf
 */

#ifndef MSP_KERNEL_IF_H_
#define MSP_KERNEL_IF_H_

//#ifndef WIN32
#if   (OS_PLATFORM == LINUXIPC32_PLATFORM)


#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(__KERNEL__)
	#include <stdint.h>
#else
	#include <linux/types.h>
#endif


// MSP - Maestro Serial Port
// RB - Ring Buffer
#define MSP_NUM_UARTS	10
#define MSP_RX_RB_SIZE	3
#define MSP_MAX_PACKET_SIZE	1024

#define MSP_DEV_NAME_PFX	"nc_drv_"


struct MSP_RB_Control {
	// Rx part
	uint32_t padding0[7];				// for keeping next index on separate cache line
	volatile uint32_t rbWrIndex;	// used by producer only (kernel)
	uint32_t padding1[7];				// for moving rbRdIndex to different cache line
	volatile uint32_t rbRdIndex; 	// used by consumer only (user)
	uint32_t padding2[7];				// for moving rbRdIndex to different cache line
	volatile uint32_t rbRdSkipCnt;	// for Performance Monitoring

	struct {
		//uint64_t timestamp;
		struct timespec timestamp;
		uint32_t bytesInRxBuf;
	} slot[MSP_RX_RB_SIZE];

	// Tx part
	volatile uint32_t tbWrCnt; 		// used by producer only (user)
	volatile uint32_t tbDoneCnt; 	// used by consumer only (kernel)
	volatile uint32_t tbWrSkipCnt;	// for Performance Monitoring
	uint32_t bytesInTxBuf;
};

struct MSP_RB_Data {
	uint8_t rxBuf[MSP_RX_RB_SIZE][MSP_MAX_PACKET_SIZE];
	uint8_t txBuf[MSP_MAX_PACKET_SIZE];
};

// Total shared memory has two parts
struct SMSP_SharedMemControl {
	uint32_t magic;
	uint32_t version;
	uint32_t size;
	struct MSP_RB_Control rbc[MSP_NUM_UARTS];
};

// get STATistics (for Performance Monitoring) and STATe
struct MSP_Enhanced_Stat {
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


//#define MSP_NEXT_RB_INDEX(x) ( ((x) + 1) % MSP_RX_RB_SIZE)
#define MSP_NEXT_RB_INDEX(x) ( ((x) + 1) >= MSP_RX_RB_SIZE ? 0 : (((x) + 1)) )


// for telling mmap which part of shared memory we want to map
#define MSP_SHM_MMAP_CTRL_ID	0x800000
#define MSP_SHM_MMAP_DATA_ID	0x700000

// Version or Magic must be changed if layout of shared memory is changed and
// becomes incompatible to kernel module
#define MSP_SHM_MAGIC   0xE1C1115E
#define MSP_SHM_VERSION 1

#define MSP_IOC_MAGIC   0xE1

#define MSP_IOC_SET_PACKET_LENGTH	_IOR( MSP_IOC_MAGIC, 1, uint32_t)
#define MSP_IOC_SET_BLOCKING_MODE	_IOR( MSP_IOC_MAGIC, 2, uint32_t)
#define MSP_IOC_SET_SPEED			_IOR( MSP_IOC_MAGIC, 3, uint32_t)
#define MSP_IOC_SET_TS_FORMAT		_IOR( MSP_IOC_MAGIC, 4, uint32_t)
#define MSP_IOC_GET_STAT			_IOR( MSP_IOC_MAGIC, 5, struct MSP_Enhanced_Stat)
#define MSP_IOC_TX_START			_IO(  MSP_IOC_MAGIC, 6)
#define MSP_IOC_TX_WAIT_DONE		_IO(  MSP_IOC_MAGIC, 7)
#define MSP_IOC_RX_WAIT_DATA_READY	_IO(  MSP_IOC_MAGIC, 8)
#define MSP_IOC_RX_START			_IO(  MSP_IOC_MAGIC, 9)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* WIN32 */

#endif /* MSP_KERNEL_IF_H_ */

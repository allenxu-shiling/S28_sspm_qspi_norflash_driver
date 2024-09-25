#ifndef _SSPM_HAL_H_
#define _SSPM_HAL_H_

#include "stdint.h"
#include "T12_reg_map.h"
#include "armv7_gic.h"

#define sspm_base_addr				(0x40006000)

#define QSPI_FLASH_TOTAL_BYTES		(16777216)
#define SECTOR_4K					(4*1024)
#define BLOCK_32K					(32*1024)
#define BLOCK_64K					(64*1024)


/*sspm_mcr register offset*/
#define TX_EN_OFFSET				(0)
#define RX_EN_OFFSET				(1)
#define TX_FIFO_CLR_OFFSET			(2)
#define RX_FIFO_CLR_OFFSET			(3)
#define SSPM_START_OFFSET			(4)
#define SSEL_EN_OFFSET				(5)
#define READ_OFFSET					(6)
#define BRG_EN_OFFSET				(8)
#define BRG_EXIT_OFFSET				(9)
#define DUMMY_CYC_OFFSET			(16)

/* sspm_cfgr register offset*/
#define WP_OFFSET					(25)
#define WAIT_EN_OFFSET				(24)
#define DFS_OFFSET					(20)
#define LSBF_OFFSET					(19)
#define FRM_FORMAT_OFFSET			(18)//whether the sel cs is pulled up or not between frames.
#define CLOCK_MODE_OFFSET			(17)//whether the clock output or not when there is no data output.
#define WORK_MODE_OFFSET			(16)//Motorola SPI mode or TI SSI mode.
#define CIOR_OFFSET					(12)
#define CAM_TYPE_OFFSET				(10)
#define DATA_TYPE_OFFSET			(8)
#define MODEBIT_CYC_OFFSET			(4)
#define CPOL_OFFSET					(1)
#define CPHA_OFFSET					(0)

/* sspm_intmr register offset */
#define RX_COMPT_EN					(21)
#define RX_ERROR_EN					(20)
#define RX_OVERRUN_EN				(19)
#define RX_FULL_EN					(18)
#define RX_HFULL_EN					(17)
#define RX_NO_EMPTY_EN				(16)
#define TX_COMPT_EN					(5)
#define LOAD_ERROR_EN				(4)
#define WE_COL_EN					(3)
#define TX_FULL_EN					(2)
#define TX_HFULL_EN					(1)
#define TX_NOEMPTY_EN				(0)

#define DMA_READ					(1)
#define DMA_WRITE					(0)


typedef struct 
{
	__IO uint32_t sspm_cr;		/*control register*/
	__IO uint32_t sspm_cfgr;	/*configuration register*/
	__IO uint32_t sspm_intmr;	/*interrupt mask register*/
	__O  uint32_t sspm_sr;		/*status register*/
	__IO uint32_t sspm_clkcfg;	/*clock configuration register*/
	__IO uint32_t sspm_cmdlen;	/*command length and address length register*/
	__IO uint32_t sspm_length;	/*data transfer length*/
	__IO uint32_t sspm_mosir;	/*master output and slave input length*/
	__IO uint32_t sspm_misor;	/*master input and slave output length*/
	__IO uint32_t sspm_brgcmd;	/*bridge command*/
}SSPM;


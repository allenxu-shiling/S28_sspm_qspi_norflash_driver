#ifndef _T12_S28_REG_MAP_H_
#define _T12_S28_REG_MAP_H_

/**
  ******************************************************************************
  * @file    T12_S28_reg_map.h
  * @author  xushl
  * @brief   T12 and S28 A5MP Register Map Device Peripheral Access Layer Header File.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - peripherals registers declarations and bits definition
  *           - Macros to access peripheral registers hardware
  *
  ******************************************************************************
**/

#include "stdint.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


#define     __O     volatile      /*!< Defines 'write only' permissions */
#define     __IO    volatile      /*!< Defines 'read / write' permissions */
#define     __I     volatile      /*!< Defines 'read only' permissions */


/**
 * ============================================================
 *
 * ****** T12 syscfg ******
 *
 * ============================================================
 */


typedef struct 
{
	__IO uint32_t GLB_CR;	      /*!< Global control register */
	__I  uint32_t GLB_SR;         /*!< Global state register */
	__IO uint32_t INT_ER;		  /*!< System interrupt enable register */
	__I  uint32_t INT_SR;		  /*!< System interrupt state register */

	__I  uint32_t A5_FILTER;      /*!< A5(M1 interface) address filter register */
	__I  uint32_t A5_PERIPHBASE;  /*!< A5 peripheral base register */
	__IO uint32_t A5_CFG;		  /*!< A5 configuration register */
	__IO uint32_t A5_DBGEN;		  /*!< A5 debug enable register */
	__I  uint32_t A5_DBGL;		  /*!< A5 debug low register */
	__I	 uint32_t A5_DBGH;		  /*!< A5 debug high register */
	__I  uint32_t Reserved1;		  /*!< Reserved1 */
	__IO uint32_t A5_SECU_CR;	  /*!< A5 Secure control register */
	__IO uint32_t A5_PCR;		  /*!< A5 Power control register */
	__I  uint32_t A5_PSR;		  /*!< A5 Power state register */
	__I  uint32_t Reserved2;		  /*!< Reserved2 */
	__IO uint32_t A5_RST_CR;	  /*!< A5 reset control register */
	
	__IO uint32_t A5_CLK_CR;	  /*!< A5 clock control register */
	__IO uint32_t SYS_CLK_CR;	  /*!< system clock register */
	__IO uint32_t ANA_CLK_CR;	  /*!< analog module clock control register */
	__IO uint32_t MODULE_CG;	  /*!< module clock gate control register */
	__IO uint32_t MODULE_RST;     /*!< module reset control register */
	__I  uint32_t Reserved3;		  /*!< Reserved3 */
	
	__IO uint32_t PLL_CR;		  /*!< PLL control register */
	__IO uint32_t PLL_CNT;		  /*!< PPL phase lock stable count register */
	__IO uint32_t LVDS_CR;		  /*!< LVDS control register */
	__IO uint32_t PVT_CR;		  /*!< PVT Sensor control register */
	__I  uint32_t PVT_DR;		  /*!< PVT Sensor data register */
}SYSCFG;

/********************  Bit definition for SYSCFG register  ********************/
/****************** GLB_CR register CKSRC_SEL bit setting *********************/
#define GLB_CR_CKSRC_SEL_DEFAULT_24MHZ		 0x00		/*!< select 24Mhz extern clock*/
#define GLB_CR_CKSRC_SEL_EXTCLOCK_24MHZ		 0x01		/*!< select 24Mhz extern clock*/
#define GLB_CR_CKSRC_SEL_PLL_1GHZ		 	 0x02	    /*!< select 1GHZ PLL output clock*/
#define GLB_CR_CKSRC_SEL_LVDS_1GHZ		  	 0x03		/*!< select 1GHZ LVDS */

/****************** GLB_CR register SW_RSTREQ bit setting *********************/
#define GLB_CR_SW_RSTREQ_Pos            	(8U)
#define GLB_CR_SW_RSTREQ            	 	(1 << 8)

/****************** GLB_CR register REMAP_N bit setting *********************/
#define GLB_CR_REMAP_N_Pos            		 (16U)
#define GLB_CR_REMAP_FLASH            		 (~(1 << 16))
#define GLB_CR_REMAP_RAM              		 (1 << 16)

/****************** GLB_SR register PLL_READY bit setting *********************/
/*!< if PLL lock phase stable, clock can be generated;*/
/*!< if PLL_RESET=1 or BYPASS = 1, PLL_READY should be 0;*/
#define GLB_SR_PLL_READY					 0x01	     


/****************** A5_CFG register A5CFG_LOCK bit setting *********************/
#define A5_CFG_UNLOCK					 	 0x00		/*!< allow A5cfg's writeable bit can be changed.*/
#define A5_CFG_LOCK					 	     0x01		/*!< no allow A5cfg's writeable bit can be changed.*/

/****************** A5_CFG register TEINIT[3:0] bit setting *********************/
/*!< it sets the SYSCFGR.TE bit, this signal is only sampled during reset of the processor.*/
#define A5_PERCORE_EXCEPTION_ARM_STATE   	 0x00		
#define A5_PERCORE_EXCEPTION_THUMB_STATE   	 0x01

/****************** A5DBGEN register A5DBGEN_LOCK bit setting *********************/
#define A5_DBGEN_UNLOCK						 0x00		/*!< allow A5DBGEN's writeable bit can be changed.*/
#define A5_DBGEN_LOCK						 0x01		/*!< no allow A5DBGEN's writeable bit can be changed.*/

/****************** A5DBGEN register SPNIDEN[3:0] bit setting *********************/
/*!< Set this signal HIGH to enable secure privileged noninvasive debug, or low to disable *******
     secure privileged noninvasive debug.*/
#define A5_DBGEN_SPNIDDISEN					 0x00		/*!< Per Core Secure Privileged noninvasive debug disable.*/
#define A5_DBGEN_SPNIDEN					 0x01		/*!< Per Core Secure Privileged noninvasive debug enable.*/

/****************** A5DBGEN register SPIDEN[3:0] bit setting *********************/
/*!< Set this signal HIGH to enable Per Core Secure Privileged invasive debug, or low to disable Per Core Secure ****
**Privileged invasive debug.*********/
#define A5_DBGEN_SPIDDISEN					 0X0		/*!< Per Core Secure Privileged invasive debug disable.*/
#define A5_DBGEN_SPIDEN		  (~A5_DBGEN_SPIDDISEN)		/*!<Per Core Secure Privileged invasive debug enable.*/

/****************** A5DBGEN register NIDEN[3:0] bit setting *********************/
/*!< Set this signal HIGH to enable Per Core noninvasive debug, or low to disable Per noninvasive debug.*
	 if you tie this signal LOW, non-invasive debug features such as the PMU are not available.**/
#define A5_DBGEN_NIDDISEN					 0x0		/*!< Per Core noninvasive debug disable.*/
#define A5_DBGEN_NIDEN		(~A5_DBGEN_NIDDISEN)		/*!< Per Core noninvasive debug enable.*/

/****************** A5DBGEN register DBGEN[3:0] bit setting *********************/
/*!< if you require debug functionality, Set this signal HIGH,for example,using RealView-ICE if you tie
     this signal LOW, debugging is not possible.***/
#define A5_DBGEN_DISABLE					 0x0		/*!< Per Core invasive debug disable.*/
#define A5_DBGEN_IDEN		 (~A5_DBGEN_DISABLE)		/*!< Per Core invasive debug enable.*/


/****************** A5_SECU_CR register A5SECUCR_LOCK bit setting *********************/
#define A5_SECU_CR_UNLOCK					0x0			/*!< allow A5_SECU_CR's writeable bit can be changed.*/
#define A5_SECU_CR_LOCK		(~A5_SECU_CR_UNLOCK)		/*!< no allow A5_SECU_CR's writeable bit can be changed.*/


/****************** A5_SECU_CR register RSTDISABLE_L bit setting *********************/
/*!< Reset to clear CPU1's L1CACHE module.*/
#define A5_SECUCR_RSTDISABLE_L				0x1

/****************** A5_SECU_CR register CFGDISABLE bit setting *********************/
/*!< Disable write access to some control processor registers.*/
#define A5_SECUCR_CFGDISABLE				0x0
#define A5_SECUCR_CFGENABLE				    (~A5_SECUCR_CFGDISABLE)

/****************** A5_SECU_CR register CF15SDISABLE bit setting *********************/
/*!< Disable write access to some control processor registers.*/
#define A5_SECUCR_CF15SDISABLE				0x0
#define A5_SECUCR_CF15SENABLE				(~A5_SECUCR_CF15SDISABLE)


/****************** A5_RST_CR register A5PERI_RSTREQ bit setting *********************/
#define A5PERI_RSTREQ						(1 << 17)			/*!< A5 peripheral reset require */
#define A5SCU_RSTREQ						(1 << 16)			/*!< A5 SCU reset require */
#define A5_CORE3_DBG_RSTREQ					(1 << 15)			/*!< A5 Core3 debug reset require */
#define A5_CORE2_DBG_RSTREQ					(1 << 14)			/*!< A5 Core2 debug reset require */
#define A5_CORE1_DBG_RSTREQ					(1 << 13)			/*!< A5 Core1 debug reset require */
#define A5_CORE0_DBG_RSTREQ					(1 << 12)			/*!< A5 Core0 debug reset require */
#define A5_CORE3_RSTREQ						(1 << 11)			/*!< A5 Core3 reset require */
#define A5_CORE2_RSTREQ						(1 << 10)			/*!< A5 Core2 reset require */
#define A5_CORE1_RSTREQ						(1 << 9)			/*!< A5 Core1 reset require */
#define A5_CORE0_RSTREQ						(1 << 8)			/*!< A5 Core0 reset require */
#define A5_CORE3_WD_RSTREQ					(1 << 3)			/*!< A5 Core3 watchdog reset require */
#define A5_CORE2_WD_RSTREQ					(1 << 2)			/*!< A5 Core2 watchdog reset require */
#define A5_CORE1_WD_RSTREQ					(1 << 1)			/*!< A5 Core1 watchdog reset require */
#define A5_CORE0_WD_RSTREQ					(1 << 0)			/*!< A5 Core0 watchdog reset require */


/****************** MODULE_CG register bit setting *********************/
#define MODULE_CG_FLASH 					(1 << 10)			/*!< MODULE_CG BIT FLASH */
#define MODULE_CG_PVT 						(1 << 9)			/*!< MODULE_CG BIT PVT */
#define MODULE_CG_RAM 						(1 << 8)			/*!< MODULE_CG BIT RAM */
#define MODULE_CG_UART 						(1 << 7)			/*!< MODULE_CG BIT UART */
#define MODULE_CG_I2C 						(1 << 6)			/*!< MODULE_CG BIT I2C */
#define MODULE_CG_DMA 						(1 << 5)			/*!< MODULE_CG BIT DMA */
#define MODULE_CG_AHB 						(1 << 4)			/*!< MODULE_CG BIT AHB */
#define MODULE_CG_AXI 						(1 << 3)			/*!< MODULE_CG BIT AXI */
#define MODULE_CG_PERI 						(1 << 2)			/*!< MODULE_CG BIT PERI */
#define MODULE_CG_DBG 						(1 << 1)			/*!< MODULE_CG BIT DBG */
#define MODULE_CG_A5 						(1 << 0)			/*!< MODULE_CG BIT A5 */

/****************** MODULE_RST register bit setting *********************/
#define MODULE_RST_FLASH 					(1 << 4)			/*!< MODULE_RST BIT FLASH */
#define MODULE_RST_RAM 						(1 << 3)			/*!< MODULE_RST BIT RAM */
#define MODULE_RST_UART 					(1 << 2)			/*!< MODULE_RST BIT UART */
#define MODULE_RST_I2C 						(1 << 1)			/*!< MODULE_RST BIT I2C */
#define MODULE_RST_DMA 						(1 << 0)			/*!< MODULE_RST BIT DMA */

/****************** PLL_CR register PLL_RESET bit setting *********************/
/*!< An active-high RESET control is provided to power down the PLL and reset it to a known state(low) */
#define PLL_CR_PLL_RESET_Pos				(31)
#define PLL_CR_PLL_RESET					(1 << PLL_CR_PLL_RESET_Pos)

/****************** PLL_CR register PLL_RANGE bit setting *********************/
/*!< This sets the PLL loop filter to work with the post-reference divider frequecy. choose the highest **
     valid range for best jitter performance, or optimize with post-silicon characterization.*/
#define PLL_CR_PLL_RANGE_POS						(28)
#define PLL_CR_PLL_RANGE_BYPASS					    (0 << 28)
#define PLL_CR_PLL_RANGE_7TO11MHZ					(1 << 28)
#define PLL_CR_PLL_RANGE_11TO18MHZ					(2 << 28)
#define PLL_CR_PLL_RANGE_18TO30MHZ					(3 << 28)
#define PLL_CR_PLL_RANGE_30TO50MHZ					(4 << 28)
#define PLL_CR_PLL_RANGE_50TO80MHZ					(5 << 28)
#define PLL_CR_PLL_RANGE_80TO130MHZ					(6 << 28)
#define PLL_CR_PLL_RANGE_130TO200MHZ				(7 << 28)

/****************** PLL_CR register PLL_DIVQ bit setting *********************/
/*!< Setting must maintain the PLL operational ranges specified in Table 1. valid devider values are ****
	 2,4,8,16,32,64,128 *****/
#define PLL_CR_PLL_DIVQ_POS							(26)
#define PLL_CR_PLL_DIVQ_2					    	(0 << PLL_CR_PLL_DIVQ_POS)
#define PLL_CR_PLL_DIVQ_4							(1 << PLL_CR_PLL_DIVQ_POS)
#define PLL_CR_PLL_DIVQ_8							(2 << PLL_CR_PLL_DIVQ_POS)
#define PLL_CR_PLL_DIVQ_16							(3 << PLL_CR_PLL_DIVQ_POS)
#define PLL_CR_PLL_DIVQ_32							(4 << PLL_CR_PLL_DIVQ_POS)
#define PLL_CR_PLL_DIVQ_64							(5 << PLL_CR_PLL_DIVQ_POS)
#define PLL_CR_PLL_DIVQ_128							(6 << PLL_CR_PLL_DIVQ_POS)

#define PLL_DIVF_POS								(8)
#define PLL_DIVF_NUM								(9)

#define PLL_DIVV_POS								(2)
#define PLL_DIVV_NUM								(6)

#define PLL_FSE_FB_PIN								(0 << 1)
#define PLL_FSE_INTERNAL_FB							(1 << 1)

#define PLL_BYPASS									(0x1)

/****************** LVDS_CR register RTERM_VAL bit setting *********************/
#define LVDS_CR_RTERM_VAL_POS						(5)
#define LVDS_CR_RTERM_VAL_79OHM					    (0 << LVDS_CR_RTERM_VAL_POS)
#define LVDS_CR_RTERM_VAL_83OHM						(1 << LVDS_CR_RTERM_VAL_POS)
#define LVDS_CR_RTERM_VAL_87OHM						(2 << LVDS_CR_RTERM_VAL_POS)
#define LVDS_CR_RTERM_VAL_92OHM						(3 << LVDS_CR_RTERM_VAL_POS)
#define LVDS_CR_RTERM_VAL_98OHM						(4 << LVDS_CR_RTERM_VAL_POS)
#define LVDS_CR_RTERM_VAL_104OHM					(5 << LVDS_CR_RTERM_VAL_POS)
#define LVDS_CR_RTERM_VAL_111OHM					(6 << LVDS_CR_RTERM_VAL_POS)
#define LVDS_CR_RTERM_VAL_120OHM					(7 << LVDS_CR_RTERM_VAL_POS)

/****************** LVDS_CR register RTERM_EN bit setting *********************/
#define LVDS_CR_RTERM_EN_POS						(4)
#define LVDS_CR_RTERM_EN 							(1 << LVDS_CR_RTERM_EN_POS)
#define LVDS_CR_RTERM_DISABLE 						(0 << LVDS_CR_RTERM_EN_POS)

/****************** LVDS_CR register RXEN bit setting *********************/
#define LVDS_CR_RXEN_POS							(3)
#define LVDS_CR_RX_EN 								(1 << LVDS_CR_RXEN_POS)
#define LVDS_CR_RX_DISABLE 							(0 << LVDS_CR_RXEN_POS)

/****************** LVDS_CR register RXEN bit setting *********************/
#define LVDS_CR_RXCMEN_POS							(2)
#define LVDS_CR_RXCM_EN 							(1 << LVDS_CR_RXCMEN_POS)
#define LVDS_CR_RXCM_DISABLE 						(0 << LVDS_CR_RXCMEN_POS)

#define LVDS_CR_BIASEN_POS							(1)
#define LVDS_CR_BIAS_EN 							(1 << LVDS_CR_BIASEN_POS)
#define LVDS_CR_BIAS_DISABLE 						(0 << LVDS_CR_BIASEN_POS)

#define LVDS_CR_BIAS_SEL							(0)
#define LVDS_CR_BIAS_SEL_EXT_BANDGAP 				(1 << LVDS_CR_BIAS_SEL)
#define LVDS_CR_BIAS_SEL_INTER_RES_DIVI 			(0 << LVDS_CR_BIAS_SEL)

/****************** PVT_CR register bit setting *********************/
#define PVT_TRIMO_POS								(16)
#define PVT_TRIMG_POS								(8)
#define PVT_VSAMPLE_POS								(3)
#define PVT_PSAMPLE_POS								(1)

#define PVT_EN_POS									(0)
#define PVT_EN										(1 << PVT_EN_POS)
#define PVT_DISABLE									(0 << PVT_EN_POS)

/**
 * ============================================================
 *
 * ****** T12 GPIO ******
 *
 * ============================================================
 */

typedef struct 
{
	__IO uint32_t GPIO_IOCR;  	  /*!< GPIO input/output control register*/
	__IO uint32_t GPIO_CFGR;	  /*!< GPIO configuration register */
	__IO uint32_t GPIO_DRCR;	  /*!< GPIO drive ability */
	__IO uint32_t GPIO_AFCR;	  /*!< GPIO AF function configuration register */
	__I  uint32_t GPIO_DIN;		  /*!< GPIO input data register */
	__IO uint32_t GPIO_DOUT;	  /*!< GPIO output data register */
	__IO uint32_t GPIO_TEST;	  /*!< SIGNEL output to enable register through GPIO */
	__I  uint32_t Reserved;		  /*!< Reserved */
	__IO uint32_t EBI_IOCR;		  /*!< EBI IO configuration register */
}GPIO_CFG_CTL;


typedef struct 
{
	__IO uint32_t GLB_USER0;	  /*!< User General Purpose Input/Ouput 0 */
	__IO uint32_t GLB_USER1;	  /*!< User General Purpose Input/Ouput 1 */
	__IO uint32_t GLB_USER2;	  /*!< User General Purpose Input/Ouput 2 */
	__IO uint32_t GLB_USER3;	  /*!< User General Purpose Input/Ouput 3 */
	__IO uint32_t GLB_USER4;	  /*!< User General Purpose Input/Ouput 4 */
	__IO uint32_t GLB_USER5;	  /*!< User General Purpose Input/Ouput 5 */
	__IO uint32_t GLB_USER6;	  /*!< User General Purpose Input/Ouput 6 */
	__IO uint32_t GLB_USER7;	  /*!< User General Purpose Input/Ouput 7 */
}GLB_USER_GPIO;

typedef enum 
{
	GPIO_NUM_0 = 0,
	GPIO_NUM_1,
	GPIO_NUM_2,
	GPIO_NUM_3,
	GPIO_NUM_4,
	GPIO_NUM_5,
	GPIO_NUM_6,
	GPIO_NUM_7,
}GPIO_NUM;

typedef enum 
{
	GPIO_INTPUT = 0,
	GPIO_OUTPUT,
}GPIO_IOC;

typedef enum 
{
	GPIO_LEVEL_LOW = 0,
	GPIO_LEVEL_HIGH = 1,
}GPIO_VAL;

typedef enum 
{
	GPIO_PULL_DOWN = 0,
	GPIO_PULL_UP = 1,
}GPIO_PULL_SELECT;


/**
 * ============================================================
 *
 * ****** T12 SCU ******
 *
 * ============================================================
 */
 
typedef struct 
{
	__IO uint32_t SCU_CONTROL;						/*!< enables the SCU and enables address filtering */
	__O  uint32_t SCU_CONFIGURATION;				/*!< enables the SCU and enables address filtering */
	__IO uint32_t SCU_CPU_POWER_STATUS;
	__IO uint32_t SCU_INVALIDATE_SECURE_STATUS;
	__I  uint32_t Reserved12[12];
	__IO uint32_t SCU_FILTER_START_ADDR;
	__IO uint32_t SCU_FILTER_END_ADDR;
	__I  uint32_t Reserved2[2];
	__IO uint32_t SCU_ACCESS_CONTROL;
	__IO uint32_t SCU_SECURE_ACCESS_CONTROL;
}SCU;

/****************** SCU_CONTROL register bit setting *********************/
#define SCU_ENABLE						(0x1)							
#define SCU_DISABLE						(0x0)		/*!< This is the default setting */

/*!< The default value is the value of FILTEREN sampled on exit from reset ***
	 This bit is always zero if the SCU is implemented in the single master port configuration.***/
#define ADDRESSING_FILTERING_Pos		(1)
#define ADDRESSING_FILTERING_ON			(0x1 << ADDRESSING_FILTERING_Pos)					
#define ADDRESSING_FILTERING_OFF		(0x0 << ADDRESSING_FILTERING_Pos)

/*!< Dynamically gate the clock to the Interrupt Controller logic when no interrupts are pending, ***
	 and no CPU core in the processor is performing a read/write request to Interrupt Controller registers *****/
#define SCU_CLK_GATING_Pos	 			(5)
#define SCU_CLK_GATING_EN		    	(0x1 << ADDRESSING_FILTERING_Pos)				
#define SCU_CLK_GATING_DISABLE			(0x0 << ADDRESSING_FILTERING_Pos)

/*!< Dynamically gate the clock to the SCU logic when all the CPU cores included in the ***
	 processor are in one of the low-power modes, that is, Standby, Dormant, or Shutdown *****/	
#define INTER_CLK_GATING_Pos	 		(6)
#define INTER_CLK_GATING_EN		    	(0x1 << ADDRESSING_FILTERING_Pos)				
#define INTER_CLK_GATING_DISABLE		(0x0 << ADDRESSING_FILTERING_Pos)

/****************** SCU_CONFIGURATION register bit setting *********************/
/*!< Number of CPUs present in the Cortex-A5 MPCore processor: */
#define CPU_NUMBER_ONE_CORE				0x0			/*!< one core, CPU0. */		
#define CPU_NUMBER_TWO_CORE				0x1			/*!< two cores, CPU0 and CPU1. */
#define CPU_NUMBER_THREE_CORE			0x2			/*!< three cores, CPU0, CPU1, and CPU2. */				
#define CPU_NUMBER_FOUR_CORE			0x3			/*!< four cores, CPU0, CPU1, CPU2, and CPU3. */	

/*!< Defines the cores that are in Symmetric Multiprocessing (SMP) or Asymmetric Multiprocessing(AMP) mode: */	
#define CPUS_SMP_CPU0_Pos				(4)
#define CPUS_SMP_CPU0_AMP_MODE			(0 << CPUS_SMP_CPU0_Pos) /*!< this core is in AMP mode not taking part in coherency or not present. */
#define CPUS_SMP_CPU0_SMP_MODE			(1 << CPUS_SMP_CPU0_Pos) /*!< this core is in SMP mode taking part in coherency. */
#define CPUS_SMP_CPU1_Pos				(5)
#define CPUS_SMP_CPU1_AMP_MODE			(0 << CPUS_SMP_CPU1_Pos) /*!< this core is in AMP mode not taking part in coherency or not present. */
#define CPUS_SMP_CPU1_SMP_MODE			(1 << CPUS_SMP_CPU1_Pos) /*!< this core is in SMP mode taking part in coherency. */
#define CPUS_SMP_CPU2_Pos				(6)
#define CPUS_SMP_CPU2_AMP_MODE			(0 << CPUS_SMP_CPU2_Pos) /*!< this core is in AMP mode not taking part in coherency or not present. */
#define CPUS_SMP_CPU2_SMP_MODE			(1 << CPUS_SMP_CPU2_Pos) /*!< this core is in SMP mode taking part in coherency. */
#define CPUS_SMP_CPU3_Pos				(7)
#define CPUS_SMP_CPU3_AMP_MODE			(0 << CPUS_SMP_CPU3_Pos) /*!< this core is in AMP mode not taking part in coherency or not present. */
#define CPUS_SMP_CPU3_SMP_MODE			(1 << CPUS_SMP_CPU3_Pos) /*!< this core is in SMP mode taking part in coherency. */

/*!< Data cache size of each core in the Cortex-A5 MPCore processor: */
typedef enum
{
	DATA_CACHE_SIZE_4KB  = 0x0,
	DATA_CACHE_SIZE_8KB  = 0x1,
	DATA_CACHE_SIZE_16KB = 0x3,
	DATA_CACHE_SIZE_32KB = 0x7,
	DATA_CACHE_SIZE_64KB = 0xf,
}DATA_CACHE_SIZE;

typedef enum
{
	CPU0_POS = (8),
	CPU1_POS = (12),
	CPU2_POS = (16),
	CPU3_POS = (20),
}CPU_POS;

#define CPU_DATA_CACHE_SIZE(CPUPos, CACHE_SIZE)  ((CACHE_SIZE) << (CPUPos))

/*!< Reflects the Accelerator Coherency Port (ACP) configuration of the Cortex-A5 MPCore processor: *****/
#define ACP_PRESENT_Pos						(30)
#define ACP_PRESENT_EN						(1 << ACP_PRESENT_Pos) /*!<  ACP present in the processor. */
#define ACP_PRESENT_DISABLE					(0 << ACP_PRESENT_Pos) /*!<  ACP not present in the processor. */

/*!< Reflects the value of the L2CPRESENT external input signal. This enables software to
	 determine the presence of an L2 cache controller in the system. **************/
#define L2C_PRESENT_PoS						(31)
#define L2C_PRESENT_EN						(1 << L2C_PRESENT_PoS)
#define L2C_PRESENT_DISABLE					(0 << L2C_PRESENT_PoS)




/**
 * ============================================================
 *
 * ****** T12 TIMER ******
 *
 * ============================================================
 */
 
typedef struct 
{
	__IO uint32_t TIMER_LOAD;
	__IO uint32_t TIMER_COUNTER;
	__IO uint32_t TIMER_CONTROL;
	__IO uint32_t TIMER_INTER_STATE;
}TIMER;

/****************** TIMER_COUNTER register bit setting *********************/
#define TIMER_EN_POS				(0)
/*!<  Timer is enabled and the counter decrements normally.  */
#define TIMER_EN					((uint32_t)(1 << TIMER_EN_POS))
/*!<  Timer is disabled and the counter does not decrement.  */
#define TIMER_DISABLE				(0 << TIMER_EN_POS)


#define TIMER_AUTO_RELOAD_POS		(1)
/*!<  Each time the Counter Register reaches zero, it is reloaded with the value 
	  contained in the Timer Load Register. ****/
#define TIMER_AUTO_RELOAD_MODE			(1 << TIMER_AUTO_RELOAD_POS)
/*!<  Counter decrements down to zero, sets the event flag and stops.  */
#define TIMER_AUTO_SINGLE_SHOT_MODE		(~((uint32_t)(1 << TIMER_AUTO_RELOAD_POS)))


#define TIMER_IT_EN_POS				(2)
#define TIMER_IT_EN					(1 << TIMER_IT_EN_POS)
#define TIMER_IT_DISABLE			(0 << TIMER_IT_EN_POS)

/*!<  The prescaler modifies the clock period for the decrementing event for the Counter Register. **
	  (Prescaler+1) x PERIPHCLK period.  PERIPHCLK is 50MHZ */
#define PRESCALER_Pos		(8)
#define PRESCALER_NUM		(0x00 << PRESCALER_Pos) /*!< user can set the prescaler number depend on using. */
#define PRESCALER_MASK		(0xFF)



/**
 * ============================================================
 *
 * ****** T12 WATCHDOG TIMER ******
 *
 * ============================================================
 */
 
typedef struct 
{
	__IO uint32_t WD_LOAD;
	__IO uint32_t WD_COUNTER;
	__IO uint32_t WD_CONTROL;
	__IO uint32_t WD_INTER_STATE;
	__IO uint32_t WD_RESET_STATE;
	__IO uint32_t WD_DISABLE;
}WATCHDOG;

/****************** WD_CONTROL register bit setting *********************/
#define WATCHDOG_EN_POS				(0)
/*!<  Watchdog is enabled and the counter decrements normally.  */
#define WATCHDOG_EN					(1)
/*!<  Watchdog is disabled and the counter does not decrement.  */
#define WATCHDOG_DISABLE			(0)


#define WD_AUTO_RELOAD_POS			(1)
/*!<  Each time the Counter Register reaches zero, it is reloaded with the value contained in the Load ****
	  Register and then continues decrementing. */
#define WD_AUTO_RELOAD_MODE			(1)
/*!<  Counter decrements down to zero, sets the event flag and stops.  */
#define WD_AUTO_SINGLE_SHOT_MODE	(0)


#define WD_IT_EN_POS				(2)
#define WD_IT_EN					(1 << WD_IT_EN_POS)
#define WD_IT_DISABLE				(0 << WD_IT_EN_POS)

#define WD_MODE_POS					(3)
#define WD_MODE_WATCHDOG			(1) 
#define WD_MODE_TIMER				(0) 


/**
 * ============================================================
 *
 * ****** T12 GLB_TIMER ******
 *
 * ============================================================
 */
 
typedef struct 
{
	__IO uint32_t GLB_TIMER_COUNTER0;			/*!< the lower 32-bit timer counter  */
	__IO uint32_t GLB_TIMER_COUNTER1;			/*!< the upper 32-bit timer counter  */
	__IO uint32_t GLB_TIMER_CONTROL;			/*!< This register controls the operation of the timer peripheral */
	__IO uint32_t GLB_TIMER_INTER_STATE;		/*!< there is one bit for event flag. */
	__IO uint32_t GLB_TIMER_COMPARATOR0;		/*!< the lower 32-bit comparator value register */
	__IO uint32_t GLB_TIMER_COMPARATOR1;		/*!< the upper 32-bit comparator value register */
	__IO uint32_t GLB_TIMER_AUTO_INCRE_COUNTER; /*!< This 32-bit register gives the increment value of the Comparator Register */
}GLB_TIM;

/****************** GLB_TIMER_CONTROL register bit setting *********************/
#define GLB_TIMER_EN_POS							(0)
#define GLB_TIMER_EN								(1 << GLB_TIMER_EN_POS)
#define GLB_TIMER_DISABLE							(0 << GLB_TIMER_EN_POS)

#define COMP_EN_POS									(1)
#define COMP_EN										(1 << COMP_EN_POS)
#define COMP_DISABLE								(0 << COMP_EN_POS)

#define IRQ_EN_POS									(2)
#define IRQ_EN										(1 << IRQ_EN_POS)
#define IRQ_DISABLE									(0 << IRQ_EN_POS)

#define AUTO_INCREMENT_POS							(3)
#define AUTO_SINGLE_SHOT_MODE						(1 << AUTO_INCREMENT_POS)
#define AUTO_INCREMENT_MODE							(0 << AUTO_INCREMENT_POS)

#define PRESCALER_Pos								(8)


/**
 * ============================================================
 *
 * ***************** I2C master control ********************
 *
 * ============================================================
 */
typedef struct 
{
	__IO uint32_t I2CMCR;			/*!< I2C control register  */
	__IO uint32_t I2CMSA;			/*!< I2C slave device address register  */
	 __I uint32_t I2CMINTMR;		/*!< I2C interrupt mask register  */
	__IO uint32_t I2CMSR;			/*!< I2C state register  */
	__IO uint32_t I2CMPR;			/*!< I2C speed seting clock register  */
	__IO uint32_t I2CMGFR;			/*!< I2C noise filter register  */
	__IO uint32_t I2CMDR;			/*!< I2C data register  */
	__IO uint32_t I2CMDLR;			/*!< I2C data length register  */
	 __I uint32_t I2CMDCNTR;		/*!< I2C data length reduce counter register  */
}I2CM;


#define		TXEMPTY_FLAG 	 (0x01 << 0)
#define		RXFULL_FLAG  	 (0x01 << 1)
#define		COMPT_FLAG   	 (0x01 << 2)
#define		NOACK_FLAG   	 (0x01 << 3)
#define		STOP_FLAG    	 (0x01 << 4)
#define		RESTART_FLAG 	 (0x01 << 5)
#define		ACK_FLAG     	 (0x01 << 6)

enum {
	RESTART_SUSPENDED_NXOP = 0X00,
	RESTART_CONTINUE_NXOP  = 0X01,
	FINATE_STOP_NXOP       = 0X10,
	CURRENT_STOP_NXOP      = 0X11,
};

#define NXOP_BIT 			(5)


/**
 * ============================================================
 *
 * ***************** uart control ********************
 *
 * ============================================================
 */
typedef struct
{
	uint32_t UART_TB;	/**TX FIFO**/
	uint32_t UART_RB;	/**RX FIFO**/
	uint32_t UART_SCT;  /**uart signal control register**/
	uint32_t UART_FCS;  /**uart fifo control/status register**/
	uint32_t UART_DST;  /**uart data interface status register**/
	uint32_t UART_DCT;  /**uart data interface control register**/
	uint32_t RESV;
	uint32_t UART_BRG;  /**uart baut rate register**/
	uint32_t UART_ERH;  /**uart error response register**/
	uint32_t resv[4];
	uint32_t UART_ABT;  /**uart auto baut rate check register**/
}UART_M;



#define RXFIFORESET				(15)
#define TXFIFORESET				(14)
#define RXEN					(13)
#define TXEN					(12)
#define STOPBITS				(9) 	/*0-1BIT, 1-2BIT*/
#define UART_IO_SPM				(4)
#define MSB						(1)		/*0-lsb, 1-msb*/

typedef enum
{
	NO_CHECK_BIT = 0,
	CHECK_RESV_BIT,
	SEND_EVEN_CHECK_BIT,
	SEND_ODD_CHECK_BIT,
	EVEN_CHECK_BIT,
	ODD_CHECK_BIT,
	CHECK_BIT_ZERO,
	CHECK_BIT_ONE,
}OP;

#define OP_BIT					(5)

#define UART_IOSPM_EN			(4)
#define MSBORLSB				(1) 	/*0-LSB(b0), 1-MSB(b7)*/




/**
 * ============================================================
 *
 * ********************** EBI ********************
 *
 * ============================================================
 */

typedef struct
{
	__IO uint32_t ctrl_ebi;
	__IO uint32_t key_data;
	__IO uint32_t key_addr;
	__IO uint32_t rev0;
	__IO uint32_t timing_bk0;
	__IO uint32_t scr_addr_bk0;
	__IO uint32_t timing_bk1;
	__IO uint32_t scr_addr_bk1;
	__IO uint32_t timing_bk2;
	__IO uint32_t scr_addr_bk2;
	__IO uint32_t timing_bk3;
	__IO uint32_t scr_addr_bk3;
	__IO uint32_t prog_addr1;
	__IO uint32_t prog_data1;
	__IO uint32_t prog_addr2;
	__IO uint32_t prog_data2;
	__IO uint32_t prog_addr3;
	__IO uint32_t prog_data3;
	__IO uint32_t prog_addr4;
	__IO uint32_t prog_data4;
	__IO uint32_t prog_addr5;
	__IO uint32_t prog_data5;
	__IO uint32_t prog_addr6;
	__IO uint32_t prog_data6;
	__IO uint32_t prog_strl;
}EBI;

#define DISABLE_BK3_LOCK_BIT					(23)
#define DISABLE_BK2_LOCK_BIT					(22)
#define DISABLE_BK1_LOCK_BIT					(21)
#define DISABLE_BK0_LOCK_BIT					(20)
#define SELECT_BK3_WIDTH_BIT					(12)
#define SELECT_BK2_WIDTH_BIT					(8)
#define SELECT_BK1_WIDTH_BIT					(4)
#define SELECT_BK0_WIDTH_BIT					(0)


//write
#define	TWAH_SHIRF_BIT 							(29)
#define TWCSH_SHIRF_BIT 						(26)
#define TWL_SHIRF_BIT 							(22)
#define TWCSS_SHIRF_BIT 						(19)
#define TWAS_SHIRF_BIT 							(16)
#define	TWAH_MASK 								(0X07)
#define TWCSH_MASK 								(0X07)
#define TWL_MASK 								(0X0F)
#define TWCSS_MASK 								(0X07)
#define TWAS_MASK 								(0X0F)


//read
#define TRAH_SHIRF_BIT 							(13)
#define TRCSH_SHIRF_BIT 						(10)
#define TRL_SHIRF_BIT 							(6)
#define TRCSS_SHIRF_BIT 						(3)
#define TRAS_SHIRF_BIT 							(0)
#define TRAH_MASK 								(0X07)
#define TRCSH_MASK 								(0X07)
#define TRL_MASK 								(0X0F)
#define TRCSS_MASK 								(0X07)
#define TRAS_MASK 								(0X07)




#define SYSCFG_BASE								(0x40001000UL)
#define GPIO_CFG_BASE							(SYSCFG_BASE + 0x90UL)
#define GPIO_CFG							    (GPIO_CFG_CTL *)GPIO_CFG_BASE
#define USER_GPIO_BASE							(0x400010e0UL)
#define A5PERIPH_BASE							(0x4e000000UL)//(((SYSCFG)SYSCFG_BASE)->A5_PERIPHBASE)
#define PPI_TIMER_BASE							(A5PERIPH_BASE + 0x600UL)
#define PPI_TIMER0								((TIMER *)PPI_TIMER_BASE)

#define WD_TIMER_BASE							(A5PERIPH_BASE + 0x620UL)
#define WD_TIMER								((WATCHDOG *)WD_TIMER_BASE)

#define GLB_TIMER_BASE							(A5PERIPH_BASE + 0x200UL)
#define GLB_TIMER								((GLB_TIM *)GLB_TIMER_BASE)


#define I2CM_BASE								((0x40004000UL))//(I2CM *)
#define UART_BASE								((0x40005000UL))
#define EBI_FLASH_BASE							((EBI * )(0x40006000UL))

#define PVT_CR_REG								(SYSCFG_BASE + 0X6C)
#define PVT_DR_REG								(SYSCFG_BASE + 0X70)

#define sspm_base_addr							(0x40006000)

#define ASIC_FLAG_ENABLE  0

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


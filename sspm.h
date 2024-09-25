#ifndef _SSPM_H_
#define _SSPM_H_

#include "stdint.h"

/**
  **********************************************************************************************************
  *
  * @file    sspm.h
  * @author  xushl 690524728@qq.com
  * @brief   the SSPM QSPI driver Header File, the programmer can use the QSPI driver api to control the QSPI 
  *          slave device.
  *
  *
  **********************************************************************************************************
**/

/**
 * @brief delay function.
*/
void delay_us(uint32_t Delay);

/**
 * @brief change the sspm mode from bridge mode to register mode.
*/
void app_sspm_normal_mode(void);

/**
 * @brief  change the sspm mode from register mode to bridge mode.
*/
void app_sspm_bridge_mode(void);

/**
 * @brief  configurate some parameter datas to sspm in bridge mode.
 *
 * @param type - the QSPI parameter type: the diferent commands have diferent comfiguration type: SPI, DSPI, QSPI;
 *        dummy_cyc - some commands maybe need some dummy cycle. 
 *        modebit_cyc - the mode cycle must be setted, it depend on the command which need the specified mode cycle. 
 */
void sspm_bridge_para_cfg(uint8_t type, uint8_t dummy_cyc, uint8_t modebit_cyc);

/**
 * @brief  configurate some parameter datas to sspm in register mode.
 *
 * @param clk_div - the sspm 's clock frequecy divider;
 *        mode_bit_num - it should be one or zero, must not great than one;
 *					     when it be setted to one, it means that the command need mode bit;
 *					     if the command do not need mode bit, the parameter is setted to zero.
 *
 *        addr_num - the address number to send to norflash, which specify the address that reading or writing data.
 *				     when the command need adress, this parameter must set to 3;
 *				     when the command do not need address, this parameter must set to zero;
 *
 *	      data_num - the data number should be configurated to sspm, which read or write data to nor flash.
 *
 */
void sspm_para_cfg_init(uint16_t clk_div, uint8_t mode_bit_num,uint8_t addr_num, uint8_t data_num);

/**
 * @brief  configurate some parameter datas to sspm in register mode.
 *
 * @param type - the QSPI parameter type: the diferent commands have diferent comfiguration type: SPI, DSPI, QSPI;
 *        dummy_cyc - some commands maybe need some dummy cycle. 
 *        modebit_cyc - the mode cycle ignores in register mode,it is setted to zero usually. 
 */
void sspm_para1_cfg_init(uint8_t type, uint8_t dummy_cyc, uint8_t modebit_cyc);

/**
 * @brief  sppm QSPI transmit data.note: this function can not be divided.
 *
 * @param cmd - the command which is sent to Norflash;
 *        addr - the address which is specified to read or write data. 
 *        mode_bit - mode bit type. 
 *        data - the data buff.
 *        num - the data buff 's number.
 */
void sspm_trans_data(uint8_t cmd, uint8_t *addr, uint8_t mode_bit,uint8_t*data, uint8_t num);

/**
 * @brief  sspm send some parameter datas to Nor flash device .
 *
 * @param cmd - the command to send to device;
 *        addr - the point of address of Norflash to send to device, sending the address should be MSB. 
 *        mode_bit - some commands maybe need mode bit,which should be sent following address. 
 */
void sspm_dma_trans_init(uint8_t cmd, uint8_t *addr, uint8_t mode_bit);

/**
 * @brief  sspm dma transmit data.
 *
 * @param rw_flag - the read or write flag: 1-read, 0-write;
 * data - the point of data to transmit. 
 * num - the size of transmision data. 
 */
void sspm_dma_trans_data(_Bool rw_flag, uint8_t*data, uint8_t num);


#endif


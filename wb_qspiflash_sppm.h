#ifndef _WB_QSPIFLASH_SPPM_H_
#define _WB_QSPIFLASH_SPPM_H_

#include "stdint.h"

/**
 * @brief  read the flash JEDEC ID by by standart SPI and DMA,the command is 0x9f according W25Q128JW datasheet..
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_dma_read_JEDEC_ID(uint8_t*data, uint8_t num);

/**
 * @brief  read the flash JEDEC ID by standart SPI, the command is 0x9f according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_read_JEDEC_ID(uint8_t*data, uint8_t num);

/**
 * @brief  read the flash device ID by standart SPI, the command is 0x92 according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_read_device_ID_Dual_IO(uint8_t*data, uint8_t num);

/**
 * @brief  read the flash device ID by standart SPI, the command is 0x90 according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_read_device_ID(uint8_t*data, uint8_t num);

/**
 * @brief  read the flash device ID by Quad SPI, the command is 0x94 according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_read_device_ID_Quad_IO(uint8_t*data, uint8_t num);


/**
 * @brief  read the flash SFDP by standart SPI, the command is 0x5a according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */

void app_read_SFDP(uint8_t*data, uint8_t num);

/**
 * @brief  ease one 64k block by the specified address, the command is 0xd8 according W25Q128JW datasheet.
 *
 * @param addr - the point of the specified address;
 *
 */
uint8_t app_block_64k_ease(uint8_t *addr);

/**
 * @brief  ease one 32k block by the specified address, the command is 0x52 according W25Q128JW datasheet.
 *
 * @param addr - the point of the specified address;
 *
 */
uint8_t app_block_32k_ease(uint8_t *addr);

/**
 * @brief  ease one 4k block by the specified address, the command is 0x20 according W25Q128JW datasheet.
 *
 * @param addr - the point of the specified address;
 *
 */
uint8_t app_sector_4k_ease(uint8_t *addr);

/**
 * @brief  ease all the flash space address, the command is 0xc7 according W25Q128JW datasheet.
 *
 */
void chip_erase(void);


/**
 * @brief  ease all the flash space address by ease each 4k sector.
 *
 */
void chip_ease_sector_4k_ease(void);

/**
 * @brief  ease all the flash space address by ease each 32k sector.
 *
 */
void chip_ease_block_32k_ease(void);

/**
 * @brief  ease all the flash space address by ease each 64k sector.
 *
 */
void chip_ease_block_64k_ease(void);

/**
 * @brief  ease all the flash space address by ease each 64k sector.
 *
 */
void page_program(uint8_t page_num, uint16_t addr, uint8_t *data,uint16_t data_num);


/**
 * @brief  program data according the specified one page and the address by quad io, 
 *         the command is 0x32 according W25Q128JW datasheet.
 *
 * @param  page_num - the page which is specified to write data;
 *         addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void quad_input_page_program(uint8_t page_num, uint16_t addr, uint8_t *data,uint16_t data_num);

/**
 * @brief  read data according the specified address by standart SPI, 
 *         the command is 0x03 according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void read_data(uint32_t addr, uint8_t *data,uint16_t data_num);

/**
 * @brief  fast read data according the specified address by standart SPI, 
 *         the command is 0x0b according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_data(uint32_t addr, uint8_t *data,uint16_t data_num);

/**
 * @brief  fast read data according the specified address by dual SPI, 
 *         the command is 0x3b according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_dual_output(uint32_t addr, uint8_t *data,uint16_t data_num);

/**
 * @brief  fast read data according the specified address by quad SPI, 
 *         the command is 0x6b according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_quad_output(uint32_t addr, uint8_t *data,uint16_t data_num);

/**
 * @brief  fast read data according the specified address by dual SPI, 
 *         the command is 0xbb according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_dual_IO(uint32_t addr, uint8_t *data,uint16_t data_num);

/**
 * @brief  fast read data according the specified address by quad SPI, 
 *         the command is 0xeb according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_quad_IO(uint32_t addr, uint8_t *data,uint16_t data_num);

/**
 * @brief  fast read data set burst with wrap, 
 *         the command is 0x77 according W25Q128JW datasheet.
 *
 * @param  byte_type - the byte type for fast read data setting burst with wrap;
 */
void fast_read_set_burst_with_wrap(uint8_t byte_type);

/**
 *
 * @brief  set individual block sector to unlock by standart SPI, 
 *         the command is 0x39 according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *
 */
void individual_block_sector_unlock(uint16_t addr);

/**
 *
 * @brief  set individual block sector to lock by standart SPI, 
 *         the command is 0x36 according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *
 */
void individual_block_sector_lock(uint16_t addr);

/**
 *
 * @brief  read_block_sector 
 *         the command is 0x3d according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data  - the reading data's buffer;
 *
 */
void read_block_sector_lock(uint16_t addr, uint8_t *data);

/**
 *
 * @brief  erase security memory according the specified area serial number.
 *         the command is 0x44 according W25Q128JW datasheet.
 *
 * @param  sn_area - the specified area serial number;
 *
 */
void erase_security_memory(uint8_t sn_area);

/**
 *
 * @brief  program security memory according the specified area serial number.
 *         the command is 0x42 according W25Q128JW datasheet.
 *
 * @param  sn_area - the specified area serial number;
 *         addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void program_security_memory(uint8_t sn_area, uint32_t addr, uint8_t *data, uint8_t data_len);

/**
 *
 * @brief  read security memory according the specified area serial number.
 *         the command is 0x42 according W25Q128JW datasheet.
 *
 * @param  sn_area - the specified area serial number;
 *         addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void read_security_memory(uint8_t sn_area, uint32_t addr, uint8_t *data, uint8_t data_len);

/**
 * @brief  lock global block sector.
 *
 */	
void global_block_sector_lock(void);

/**
 * @brief unlock global block sector.
 *
 */	
void global_block_sector_unlock(void);


#endif


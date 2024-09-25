#include "wb_qspiflash_sppm.h"
#include <stddef.h>
#include <stdint.h>
#include "sspm_hal.h"
#include "sspm.h"
#include "dma.h"

/**
  ******************************************************************************
  *
  * @file    wb_qspiflash_sppm.c
  * @author  xushl 690524728@qq.com
  * @brief   the winbond QSPI flash(W25Q128JW) dirver source File, which detail to how to use this flash driver,
  *          the SSPM QSPI controller connect to W25Q128JW flash by using QSPI, so this driver use sppm QSPI driver to 
  *          control the flash how to read and write data from flash.
  *
  *
  ******************************************************************************
**/


/**
 * @brief  read one flash register status by standart SPI.
 *
 * @param cmd - the specified command;
 *
 *	      status - the point of the status reading from flash .
 *
 */
static void app_read_reg_status(uint8_t cmd, uint8_t *status)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t mode_bit;
	
	clk_div = 2;
	mode_bit_num = 0;//0 or 1
	addr_num = 0;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, 1);
	
	type = 1;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	mode_bit = 0;
	sspm_trans_data(cmd, NULL, mode_bit, status, 1);

}

/**
 * @brief  write one register status to flash by standart SPI.
 *
 * @param cmd - the specified command;
 *
 *	      status - the status writing to flash .
 *
 */
static void app_write_reg_status(uint8_t cmd, uint8_t status)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t mode_bit;
	
	clk_div = 2;
	mode_bit_num = 0;//0 or 1
	addr_num = 0;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, 1);
	
	type = 2;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	mode_bit = 0;
	sspm_trans_data(cmd, NULL, mode_bit, &status, 1);

}

/**
 * @brief  write one instruction to flash by standart SPI.
 *
 * @param cmd - the specified instruction;
 *
 *	      status - the status writing to flash .
 *
 */
static void app_send_one_instruction(uint8_t cmd, uint8_t *addr, uint8_t addr_num)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,type,dummy_cyc,modebit_cyc;
	uint8_t mode_bit;
	
	clk_div = 2;
	mode_bit_num = 0;//0 or 1
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, 0);
	
	type = 2;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	mode_bit = 0;
	sspm_trans_data(cmd, (uint8_t *)addr, mode_bit, NULL, 0);

}

/**
 * @brief  enable the volatile status register, the command is 0x50 according W25Q128JW datasheet.
 *
 */
static void app_write_enable_volatile_status_reg(void)
{
	app_send_one_instruction(0x50, NULL, 0);
}

/**
 * @brief  enable the register for writing.
 *
 */
static uint8_t app_standard_write_enable(void)
{
	uint8_t status = 0;
	uint8_t tmp[200] = {0};
	uint8_t retry_num = 0;
	
	app_send_one_instruction(0x06, NULL, 0);
	app_read_reg_status(0x05, &status);

	if(!(status & 0x02))
	{
		while(retry_num < 2)
		{
			app_send_one_instruction(0x06, NULL, 0);
			app_read_reg_status(0x05, &status);
			
			if((status & 0x02))
				break;
			
			retry_num++;
		}
	}
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "bit1[WEL] status =0x%x \r\n", status);
	uart_polling_send(tmp, strlen(tmp));

	if((status & 0x02))
		return 1;
	else
		return 0;
}

/**
 * @brief  enable the qual io 's register for writing and reading.
 *         the W25Q128JW flash is default to enable qual io 's registers reading and writing.
 *
 */
static void app_qual_rw_enable(void)
{
	uint8_t status = 0;
	uint8_t tmp[100] = {0};

	if(!app_standard_write_enable())return;

	//app_read_reg_status(0x35, &status);
	
	//status |= (1 << 1);//enable Quad Enable (QE)
	
	//uint16_t clk_div;
	//uint8_t mode_bit_num,type,dummy_cyc,modebit_cyc;
	//uint8_t mode_bit;
	
	//clk_div = 2;
	//mode_bit_num = 0;//0 or 1
	//addr_num = 0;
	//sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, 1);
	
	//type = 2;
	//dummy_cyc = 0;
	//modebit_cyc = 0;
	//sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	//mode_bit = 0;
	//cmd = 0x31;
	//sspm_trans_data(cmd, NULL, mode_bit, &status, 1);
	
	//app_read_reg_status(0x35, &status);
}


/**
 * @brief  read the flash JEDEC ID by by standart SPI and DMA,the command is 0x9f according W25Q128JW datasheet..
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_dma_read_JEDEC_ID(uint8_t*data, uint8_t num)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint32_t addr;
	uint8_t cmd,mode_bit;
	#define SSPM_DMA_CHANNEL 3
	uint8_t tmp[100] = {0};
	
	clk_div = 2;
	mode_bit_num = 0;//0 or 1
	addr_num = 0;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, num);
	
	type = 0x0;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	
	sspm_dma_trans_data(DMA_READ, data, num);
	
	cmd = 0x9f;
	mode_bit = 0;
	sspm_dma_trans_init(cmd, NULL, mode_bit);
	
	
	dma_enable_channel(SSPM_DMA_CHANNEL);
	dma_test_info(SSPM_DMA_CHANNEL);
	
	//memset(tmp, 0, sizeof(tmp));
	//sprintf(tmp, "app_dma_read_JEDEC_ID sspm_sr=0x%x, sspm_cr = 0x%x, data=0x%x \r\n", Qspi->sspm_sr, &(Qspi->sspm_misor), data);
	//uart_polling_send(tmp, strlen(tmp));
}

/**
 * @brief  read the flash JEDEC ID by standart SPI, the command is 0x9f according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_read_JEDEC_ID(uint8_t*data, uint8_t num)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint32_t addr;
	uint8_t cmd,mode_bit;
	
	clk_div = 2;
	mode_bit_num = 0;//0 or 1
	addr_num = 0;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, num);
	
	type = 0x0;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x9f;
	//addr = 0x000000;
	mode_bit = 0;
	sspm_trans_data(cmd, NULL, mode_bit, data, num);
}

/**
 * @brief  read the flash device ID by standart SPI, the command is 0x92 according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_read_device_ID_Dual_IO(uint8_t*data, uint8_t num)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint32_t addr;
	uint8_t cmd,mode_bit;
	
	clk_div = 10;
	mode_bit_num = 1;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, num);
	
	type = 4;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x92;
	addr = 0x000000;
	mode_bit = 0xf1;
	sspm_trans_data(cmd, (uint8_t *)&addr, mode_bit, data, num);
}

/**
 * @brief  read the flash device ID by standart SPI, the command is 0x90 according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_read_device_ID(uint8_t*data, uint8_t num)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint32_t addr;
	uint8_t cmd,mode_bit;
	
	clk_div = 2;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, num);
	
	type = 0x0;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x90;
	addr = 0x000000;
	mode_bit = 0;
	sspm_trans_data(cmd, (uint8_t *)&addr, mode_bit, data, num);
}

/**
 * @brief  read the flash device ID by Quad SPI, the command is 0x94 according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */
void app_read_device_ID_Quad_IO(uint8_t*data, uint8_t num)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint32_t addr;
	uint8_t cmd,mode_bit;
	
	clk_div = 10;
	mode_bit_num = 1;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, num);
	
	type = 11;
	dummy_cyc = 4;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x94;
	addr = 0x000000;
	mode_bit = 0xf1;
	sspm_trans_data(cmd, (uint8_t *)&addr, mode_bit, data, num);
}

/**
 * @brief  read the flash SFDP by standart SPI, the command is 0x5a according W25Q128JW datasheet.
 *
 * @param data - the data buff;
 *
 *	      num - the data number which is how much read from flash .
 *
 */

void app_read_SFDP(uint8_t*data, uint8_t num)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint32_t addr;
	uint8_t cmd,mode_bit;
	
	clk_div = 10;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, num);
	
	type = 0;
	dummy_cyc = 8;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x5a;
	addr = 0x000000;
	mode_bit = 0;
	sspm_trans_data(cmd, (uint8_t *)&addr, mode_bit, data, num);
}

/**
 * @brief  ease one 64k block by the specified address, the command is 0xd8 according W25Q128JW datasheet.
 *
 * @param addr - the point of the specified address;
 *
 */
uint8_t app_block_64k_ease(uint8_t *addr)
{
	uint8_t tmp[100] = {0};
	uint8_t status = 0;
	
	if(!app_standard_write_enable())return 0;
	
	app_send_one_instruction(0xd8, addr, 3);
	app_read_reg_status(0x05, &status);

	while(status & 0x01)
	{
		delay_us(500);
		memset(tmp, 0, sizeof(tmp));
		app_read_reg_status(0x05, &status);
		sprintf(tmp, "block_64k_ease busy status =0x%x \r\n", status);
		uart_polling_send(tmp, strlen(tmp));
	}

	return 1;
}

/**
 * @brief  ease one 32k block by the specified address, the command is 0x52 according W25Q128JW datasheet.
 *
 * @param addr - the point of the specified address;
 *
 */
uint8_t app_block_32k_ease(uint8_t *addr)
{
	uint8_t tmp[100] = {0};
	uint8_t status = 0;
	
	if(!app_standard_write_enable())return 0;
	
	app_send_one_instruction(0x52, addr, 3);
	app_read_reg_status(0x05, &status);
	
	while(status & 0x01)
	{
		delay_us(500);
		memset(tmp, 0, sizeof(tmp));
		app_read_reg_status(0x05, &status);
		sprintf(tmp, "busy status =0x%x \r\n", status);
		uart_polling_send(tmp, strlen(tmp));
	}

	return 1;
}

/**
 * @brief  ease one 4k block by the specified address, the command is 0x20 according W25Q128JW datasheet.
 *
 * @param addr - the point of the specified address;
 *
 */
uint8_t app_sector_4k_ease(uint8_t *addr)
{
	uint8_t tmp[100] = {0};
	uint8_t status = 0;
	
	if(!app_standard_write_enable())return 0;
	
	app_send_one_instruction(0x20, addr, 3);
	app_read_reg_status(0x05, &status);
	while(status & 0x01)
	{
		delay_us(500);
		memset(tmp, 0, sizeof(tmp));
		app_read_reg_status(0x05, &status);
		sprintf(tmp, "busy status =0x%x \r\n", status);
		uart_polling_send(tmp, strlen(tmp));
	}

	return 1;
}

/**
 * @brief  ease all the flash space address, the command is 0xc7 according W25Q128JW datasheet.
 *
 */
void chip_erase(void)
{	
	uint8_t status = 0;
	uint8_t tmp[100] = {0};
	
	if(!app_standard_write_enable())return;

	app_send_one_instruction(0xc7, NULL, 0);
	app_read_reg_status(0x05, &status);
	while(status & 0x01)
	{
		delay_us(500);
		memset(tmp, 0, sizeof(tmp));
		app_read_reg_status(0x05, &status);
		sprintf(tmp, "chip_erase busy status =0x%x \r\n", status);
		uart_polling_send(tmp, strlen(tmp));
	}
}

/**
 * @brief  ease all the flash space address by ease each 4k sector.
 *
 */
void chip_ease_sector_4k_ease(void)
{
	uint32_t i = 0;
	for(i=0; i < QSPI_FLASH_TOTAL_BYTES/SECTOR_4K; i++)
	{
		app_sector_4k_ease(&i);
		i += SECTOR_4K;
	}
}

/**
 * @brief  ease all the flash space address by ease each 32k sector.
 *
 */
void chip_ease_block_32k_ease(void)
{
	uint32_t i = 0;
	for(i=0; i < QSPI_FLASH_TOTAL_BYTES/BLOCK_32K; i++)
	{
		app_block_32k_ease(&i);
		i += BLOCK_32K;
	}
}

/**
 * @brief  ease all the flash space address by ease each 64k sector.
 *
 */
void chip_ease_block_64k_ease(void)
{
	uint32_t i = 0;
	for(i=0; i < QSPI_FLASH_TOTAL_BYTES/BLOCK_64K; i++)
	{
		app_block_64k_ease(&i);
		i += BLOCK_64K;
	}
}

/**
 * @brief  ease all the flash space address by ease each 64k sector.
 *
 */
void page_program(uint8_t page_num, uint16_t addr, uint8_t *data,uint16_t data_num)
{
	uint32_t flash_addr = 0;
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	if(!app_standard_write_enable())return;
	
	flash_addr = page_num * 256 + addr;

	clk_div = 10;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_num);
	
	type = 2;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x02;
	mode_bit = 0;
	sspm_trans_data(cmd, (uint8_t *)&flash_addr, mode_bit, data, data_num);
}

/**
 * @brief  program data according the specified one page and the address by quad io, 
 *         the command is 0x32 according W25Q128JW datasheet.
 *
 * @param  page_num - the page which is specified to write data;
 *         addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void quad_input_page_program(uint8_t page_num, uint16_t addr, uint8_t *data,uint16_t data_num)
{
	uint32_t flash_addr = 0;
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	if(!app_standard_write_enable())return;
	
	flash_addr = page_num * 256 + addr;

	clk_div = 10;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_num);
	
	type = 14;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x32;
	mode_bit = 0;
	sspm_trans_data(cmd, (uint8_t *)&flash_addr, mode_bit, data, data_num);
}

/**
 * @brief  read data according the specified address by standart SPI, 
 *         the command is 0x03 according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void read_data(uint32_t addr, uint8_t *data,uint16_t data_num)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	clk_div = 4;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_num);
	
	type = 0x1;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x03;
	mode_bit = 0;
	sspm_trans_data(cmd, &addr, mode_bit, data, data_num);
}

/**
 * @brief  fast read data according the specified address by standart SPI, 
 *         the command is 0x0b according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_data(uint32_t addr, uint8_t *data,uint16_t data_num)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	clk_div = 8;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_num);
	
	type = 0x1;
	dummy_cyc = 8;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x0b;
	mode_bit = 0;
	sspm_trans_data(cmd, &addr, mode_bit, data, data_num);
}

/**
 * @brief  fast read data according the specified address by dual SPI, 
 *         the command is 0x3b according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_dual_output(uint32_t addr, uint8_t *data,uint16_t data_num)
{
	app_qual_rw_enable();

	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	clk_div = 8;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_num);
	
	type = 0x3;
	dummy_cyc = 8;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x3b;
	mode_bit = 0;
	sspm_trans_data(cmd, &addr, mode_bit, data, data_num);
}

/**
 * @brief  fast read data according the specified address by quad SPI, 
 *         the command is 0x6b according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_quad_output(uint32_t addr, uint8_t *data,uint16_t data_num)
{
	app_qual_rw_enable();

	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	clk_div = 8;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_num);
	
	type = 10;
	dummy_cyc = 8;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x6b;
	mode_bit = 0;
	sspm_trans_data(cmd, &addr, mode_bit, data, data_num);
}

/**
 * @brief  fast read data according the specified address by dual SPI, 
 *         the command is 0xbb according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_dual_IO(uint32_t addr, uint8_t *data,uint16_t data_num)
{
	//app_qual_rw_enable();

	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;

	//if(!app_standard_write_enable())return;
	clk_div = 8;
	mode_bit_num = 1;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_num);
	
	type = 4;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0xbb;
	mode_bit = 0xf1;
	sspm_trans_data(cmd, &addr, mode_bit, data, data_num);
}

/**
 * @brief  fast read data according the specified address by quad SPI, 
 *         the command is 0xeb according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data - the point of data buffer;
 *         data_num - the data's number;
 */
void fast_read_quad_IO(uint32_t addr, uint8_t *data,uint16_t data_num)
{
	app_qual_rw_enable();

	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	clk_div = 8;
	mode_bit_num = 1;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_num);
	
	type = 11;
	dummy_cyc = 4;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0xeb;
	mode_bit = 0xf1;
	sspm_trans_data(cmd, &addr, mode_bit, data, data_num);
}

/**
 * @brief  fast read data set burst with wrap, 
 *         the command is 0x77 according W25Q128JW datasheet.
 *
 * @param  byte_type - the byte type for fast read data setting burst with wrap;
 */
void fast_read_set_burst_with_wrap(uint8_t byte_type)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	clk_div = 8;
	mode_bit_num = 0;//0 or 1
	addr_num = 0;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, 1);
	
	type = 11;
	dummy_cyc = 6;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x77;
	mode_bit = 0;
	sspm_trans_data(cmd, NULL, mode_bit, &byte_type, 1);
}

/**
 * @brief  individual block sector need to set lock or unlock by standart SPI, 
 *
 * @param  addr - the specified address;
 *		   cmd  - the specified command;
 *
 */
static void individual_block_sector_lock_or_unlock(uint16_t addr, uint8_t cmd)
{
	uint8_t status = 0;
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t mode_bit;
	uint8_t tmp[120] = {0};
	
	app_write_enable_volatile_status_reg();

	app_read_reg_status(0x15, &status);
	
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "01 read status=0x%x \r\n", status);
	uart_polling_send(tmp, strlen(tmp));
	
	status |= (1 << 2);
	app_write_reg_status(0x11, status);
	
	status = 0;
	app_read_reg_status(0x15, &status);

	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "02 read status=0x%x \r\n", status);
	uart_polling_send(tmp, strlen(tmp));
	
	app_standard_write_enable();
	
	clk_div = 4;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, 0);
	
	type = 0x2;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	mode_bit = 0;
	sspm_trans_data(cmd, &addr, mode_bit, NULL, 0);
}

/**
 *
 * @brief  set individual block sector to unlock by standart SPI, 
 *         the command is 0x39 according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *
 */
void individual_block_sector_unlock(uint16_t addr)
{
	individual_block_sector_lock_or_unlock(addr, 0x39);
}

/**
 *
 * @brief  set individual block sector to lock by standart SPI, 
 *         the command is 0x36 according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *
 */
void individual_block_sector_lock(uint16_t addr)
{
	individual_block_sector_lock_or_unlock(addr, 0x36);
}


/**
 *
 * @brief  read_block_sector 
 *         the command is 0x3d according W25Q128JW datasheet.
 *
 * @param  addr - the specified address;
 *		   data  - the reading data's buffer;
 *
 */
void read_block_sector_lock(uint16_t addr, uint8_t *data)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	clk_div = 4;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, 1);
	
	type = 0x1;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	cmd = 0x3d;
	mode_bit = 0;
	sspm_trans_data(cmd, &addr, mode_bit, data, 1);
}

/**
 *
 * @brief  erase security memory according the specified area serial number.
 *         the command is 0x44 according W25Q128JW datasheet.
 *
 * @param  sn_area - the specified area serial number;
 *
 */
void erase_security_memory(uint8_t sn_area)
{
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc, status;
	uint8_t cmd,mode_bit;
	uint16_t addr;
	uint8_t tmp[125];
	
	app_standard_write_enable();
	
	clk_div = 4;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, 0);
	
	type = 0x2;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	if(0 == sn_area)
	{
		addr = 0x001000;
	}
	else if(1 == sn_area)
	{
		addr = 0x002000;
	}
	else if(2 == sn_area)
	{
		addr = 0x003000;
	}

	cmd = 0x44;
	mode_bit = 0;
	sspm_trans_data(cmd, &addr, mode_bit, NULL, 0);

	app_read_reg_status(0x05, &status);

	while(status & 0x01)
	{
		delay_us(500);
		memset(tmp, 0, sizeof(tmp));
		app_read_reg_status(0x05, &status);
		sprintf(tmp, "erase_security_memory busy status =0x%x \r\n", status);
		uart_polling_send(tmp, strlen(tmp));
	}
	
}

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
void program_security_memory(uint8_t sn_area, uint32_t addr, uint8_t *data, uint8_t data_len)
{
	
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	uint8_t tmp[125];
	
	app_standard_write_enable();
	
	clk_div = 4;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_len);
	
	type = 0x2;
	dummy_cyc = 0;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	if(0 == sn_area)
	{
		addr = 0x001000 | (addr & 0xff);
	}
	else if(1 == sn_area)
	{
		addr = 0x002000 | (addr & 0xff);
	}
	else if(2 == sn_area)
	{
		addr = 0x003000 | (addr & 0xff);
	}

	cmd = 0x42;
	mode_bit = 0;
	sspm_trans_data(cmd, &addr, mode_bit, data, data_len);
}

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
void read_security_memory(uint8_t sn_area, uint32_t addr, uint8_t *data, uint8_t data_len)
{
	
	uint16_t clk_div;
	uint8_t mode_bit_num,addr_num,type,dummy_cyc,modebit_cyc;
	uint8_t cmd,mode_bit;
	
	app_standard_write_enable();
	
	clk_div = 4;
	mode_bit_num = 0;//0 or 1
	addr_num = 3;
	sspm_para_cfg_init(clk_div, mode_bit_num, addr_num, data_len);
	
	type = 0x1;
	dummy_cyc = 8;
	modebit_cyc = 0;
	sspm_para1_cfg_init(type, dummy_cyc, modebit_cyc);

	if(0 == sn_area)
	{
		addr = 0x001000 | (addr & 0xff);
	}
	else if(1 == sn_area)
	{
		addr = 0x002000 | (addr & 0xff);
	}
	else if(2 == sn_area)
	{
		addr = 0x003000 | (addr & 0xff);
	}

	cmd = 0x48;
	mode_bit = 0;
	sspm_trans_data(cmd, &addr, mode_bit, data, data_len);
}

/**
 * @brief  lock global block sector.
 *
 */	
void global_block_sector_lock(void)
{
	app_standard_write_enable();
	app_send_one_instruction(0x7E, NULL, 0);
}

/**
 * @brief unlock global block sector.
 *
 */	
void global_block_sector_unlock(void)
{
	app_standard_write_enable();
	app_send_one_instruction(0x98, NULL, 0);
}


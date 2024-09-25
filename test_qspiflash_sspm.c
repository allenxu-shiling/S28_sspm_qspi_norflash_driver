#include "wb_qspiflash_sppm.h"

static uint8_t data[32] = {0};

void debug_print_info(void)
{
	uint8_t tmp_buff[64] = {0};
	
	
	uint8_t tmp[164] = {0};
	
	//uint8_t tmp_ch[20] = {0x55, 0x33, 0x77, 0xaa, 0x34, 0x73, 0x44, 0x55, 0x66, 0x77, 0x99, 0x33, 0x97};

	uint8_t tmp_ch[20] = {0x33, 0x55, 0x77, 0xaa, 0x34, 0x73, 0x44, 0x55, 0x66, 0x77, 0x99, 0x33, 0x68};
	
	
	uint8_t tmp_num = 0;
	uint32_t addr = 0;
	uint32_t reg_data = 0;
	
	global_block_sector_unlock();
	//individual_block_sector_unlock(0x000000);
	
	memset(data, 0, sizeof(data));
	//app_read_JEDEC_ID(data, 3);
	app_dma_read_JEDEC_ID(data, 3);
	for(tmp_num=0; tmp_num < 6; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "JEDEC_ID: data[%d]=0x%x \r\n", tmp_num, data[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}

	return ;

	memset(data, 0, sizeof(data));
	app_read_device_ID(data, 2);
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "device_ID: data[0]=0x%x, data[1]=0x%x \r\n", data[0], data[1]);
	uart_polling_send(tmp, strlen(tmp));

	app_standard_write_enable();
	
	memset(data, 0, sizeof(data));
	app_read_device_ID_Quad_IO(data, 12);
	for(tmp_num=0; tmp_num < 12; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "Quad_IO: data[%d]=0x%x \r\n", tmp_num, data[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}

	memset(data, 0, sizeof(data));
	app_read_device_ID_Dual_IO(data, 6);

	for(tmp_num=0; tmp_num < 6; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "device_ID_Dual_IO: data[%d]=0x%x \r\n", tmp_num, data[tmp_num]);
		uart_polling_send(tmp, strlen(tmp)
	}

	
	//chip_erase();
	addr = 0x00;
	//app_block_64k_ease(&addr);
	
	//quad_input_page_program(0, 0 ,tmp_ch, 13);
	delay_us(0x80);

	
	memset(tmp_buff, 0, sizeof(tmp_buff));
	read_data(0, tmp_buff, 13);
	for(tmp_num=0; tmp_num < 13; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "read data[%d]=0x%x \r\n", tmp_num, tmp_buff[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}

	
	memset(tmp_buff, 0, sizeof(tmp_buff));
	fast_read_data(0, tmp_buff, 13);
	for(tmp_num=0; tmp_num < 13; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "fast_read data[%d]=0x%x \r\n", tmp_num, tmp_buff[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}

	memset(tmp_buff, 0, sizeof(tmp_buff));
	fast_read_dual_output(0, tmp_buff, 13);
	for(tmp_num=0; tmp_num < 13; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "fast_read_dual_output data[%d]=0x%x \r\n", tmp_num, tmp_buff[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}

	memset(tmp_buff, 0, sizeof(tmp_buff));
	fast_read_quad_output(0, tmp_buff, 13);
	for(tmp_num=0; tmp_num < 13; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "fast_read_quad_output data[%d]=0x%x \r\n", tmp_num, tmp_buff[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}

	memset(tmp_buff, 0, sizeof(tmp_buff));
	fast_read_dual_IO(0, tmp_buff, 13);
	for(tmp_num=0; tmp_num < 13; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "fast_read_dual_IO data[%d]=0x%x \r\n", tmp_num, tmp_buff[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}

	memset(tmp_buff, 0, sizeof(tmp_buff));
	fast_read_quad_IO(0, tmp_buff, 13);
	for(tmp_num=0; tmp_num < 13; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "fast_read_quad_IO data[%d]=0x%x \r\n", tmp_num, tmp_buff[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}

#if 1
	memset(tmp_buff, 0, sizeof(tmp_buff));
	app_read_SFDP(tmp_buff, 25);
	for(tmp_num=0; tmp_num < 25; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "app_read_SFDP data[%d]=0x%x \r\n", tmp_num, tmp_buff[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}
	
	memset(tmp_buff, 0, sizeof(tmp_buff));
	read_block_sector_lock(0x000000, tmp_buff);
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "read_block_sector_lock data[0]=0x%x \r\n", tmp_buff[0]);
	uart_polling_send(tmp, strlen(tmp));

	erase_security_memory(0x02);
	
	program_security_memory(0x02, 0x00000000, tmp_ch, 13);

	memset(tmp_buff, 0, sizeof(tmp_buff));
	read_security_memory(0x02, 0x00000000, tmp_buff, 13);

	for(tmp_num=0; tmp_num < 13; tmp_num++)
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "read_security_memory data[%d]=0x%x \r\n", tmp_num, tmp_buff[tmp_num]);
		uart_polling_send(tmp, strlen(tmp));
	}
	
	reg_data = GWX_HAL_READ_UINT32(0x40001090);
	reg_data &= ~(0xff << 16);
	GWX_HAL_WRITE_UINT32(0x40001090, reg_data);

	GWX_HAL_WRITE_UINT32(0x400010a4, 0xff);

	app_standard_write_enable();
	
	#endif
	
}


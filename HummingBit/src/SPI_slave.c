/*
 * SPI.c
 *
 * Created: 2/5/2018 4:06:49 PM
 *  Author: raghu
 */ 
#include<asf.h>
#define SPI_LENGTH 4
#include "SPI_slave.h"


void configure_spi_slave(void)
{
	struct spi_config config_spi_slave;
	/* Configure, initialize and enable SERCOM SPI module */
	spi_get_config_defaults(&config_spi_slave);
	config_spi_slave.transfer_mode = SPI_TRANSFER_MODE_0;
	config_spi_slave.mode = SPI_MODE_SLAVE;
	config_spi_slave.mode_specific.slave.preload_enable = true;
	config_spi_slave.mode_specific.slave.frame_format = SPI_FRAME_FORMAT_SPI_FRAME;
	//config_spi_slave.data_order =  SPI_DATA_ORDER_LSB;
	config_spi_slave.mux_setting = SPI_SLAVE_MUX_SETTING;
	config_spi_slave.pinmux_pad0 = SPI_SLAVE_PINMUX_PAD0;
	config_spi_slave.pinmux_pad1 = SPI_SLAVE_PINMUX_PAD1;
	config_spi_slave.pinmux_pad2 = SPI_SLAVE_PINMUX_PAD2;
	config_spi_slave.pinmux_pad3 = SPI_SLAVE_PINMUX_PAD3;
	spi_init(&spi_slave_instance,  SLAVE_SPI_MODULE, &config_spi_slave);
	spi_enable(&spi_slave_instance);
}

static void spi_slave_callback(struct spi_module *const module)
{
	transfer_complete_spi_slave = true;
	//port_pin_set_output_level(PIN_PA27, false);
	//spi_transceive_buffer_job(&spi_slave_instance, transmit_value, received_value,SPI_LENGTH);
}

void configure_spi_slave_callbacks(void)
{
	spi_register_callback(&spi_slave_instance, spi_slave_callback,SPI_CALLBACK_BUFFER_TRANSCEIVED);
	spi_enable_callback(&spi_slave_instance, SPI_CALLBACK_BUFFER_TRANSCEIVED);
}

void spi_slave_init()
{
	volatile enum status_code error_code = 0x10;
	configure_spi_slave();
	configure_spi_slave_callbacks();
	cpu_irq_disable();
	do
	{
	error_code = spi_transceive_buffer_job(&spi_slave_instance, sensor_outputs, received_value,SPI_LENGTH);
	} while (error_code != STATUS_OK );
	cpu_irq_enable();
	//delay_cycles_ms(2000);
}


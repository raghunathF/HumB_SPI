/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "ORB.h"
#include "LED.h"
#include "LED_control.h"
#include "super_servo.h"
#include "sensor_control.h"
#include "sensor.h"
#include "test.h"
#include "UART_control.h"
#include "UART.h"
#include "SPI_slave.h"
#include "SPI_control.h"

volatile uint8_t sensor_outputs[4];

uint8_t* global_sensor_value = NULL;


volatile uint8_t transmit_value[20];
volatile uint8_t ring_buffer[MAX_LIMIT_RING_BUFFER];
volatile uint8_t tail_ring_buffer=0;
volatile uint8_t head_ring_buffer=0;
volatile bool received_data_updated=false;

volatile bool transfer_complete_spi_slave = false;

volatile uint8_t serial_timeout_count = 0;
volatile bool serial_timeout = false;
volatile bool transcation_start = false;
volatile uint8_t count_broadcast = 0;

#define SPI_DATA_LENGTH 20
volatile uint8_t received_value[SPI_DATA_LENGTH];

void load_input()
{
	read_all_sensors();	
}

void sensor_check()
{
	read_all_sensors();
}

int main (void)
{
	system_init();
	//cpu_irq_enable();
	delay_init();
	//spi_slave_init();
	//delay_cycles_ms(2000);
	LED_init();
	ORB_init();
	sensor_init();
	super_servo_init();
	//serial_init();
	enable_super_servo();
	enable_ORB();
	enable_LED();
	//enable_USART();
	//update_LEDS_single(0x31,0);
	//delay_cycles_ms(2000);
	spi_slave_init();
	//delay_cycles_ms(2000);
	/* Insert application code here, after the board has been initialized. */
	while(1)
	{
		port_pin_set_output_level(PIN_PA27,true);
		sensor_check();
		port_pin_set_output_level(PIN_PA27,false);
		spi_main_loop();
		//delay_cycles_us(1);
		//delay_cycles_us(1);


		//test_ORB();
		 //load_input();
		 //test_LED();
		 //test_servos();
	}
}

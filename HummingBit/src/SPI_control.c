/*
 * SPI_control.c
 *
 * Created: 2/5/2018 4:46:53 PM
 *  Author: Raghunath reddy 
 */ 

#include <asf.h>
#include "SPI_control.h"
#include "SPI_slave.h"
#include "UART.h"
#include "LED_control.h"
#include "ORB_control.h"
#include "sensor_control.h"
#include "super_servo_control.h"

void check_timeout()
{
	if(transcation_start == true)
	{
		if(serial_timeout == true)
		{
			serial_timeout_count = 0;
			serial_timeout = false;
			transcation_start = false;
			spi_transceive_buffer_job(&spi_slave_instance, sensor_outputs, received_value,SPI_LENGTH);
		}
	}
	
}


void spi_main_loop()
{
	
	volatile enum status_code error_code = 0x10;
	//volatile static uint16_t buffer_storage[500]; 
	volatile static uint16_t count_buffer = 0;
	//static  uint8_t job_done  = FAILURE;
	uint8_t i    = 0;
	uint8_t rw   = 0;
	uint8_t mode = 0;
	static bool test = true;
	transmit_value[0] = 0x88;
	transmit_value[1] = 0xAA;
	transmit_value[2] = 0xBB;
	transmit_value[3] = 0xCC;
	//do
	//{
	//error_code = spi_transceive_buffer_job(&spi_slave_instance, transmit_value, received_value,SPI_LENGTH);
	//} while (error_code != STATUS_OK )
	//while(transfer_complete_spi_slave == false)
	//{
		
	//}
	/*
	if(test == true)
	{
		update_LEDS_single(LED3_NO,0x55);
		delay_cycles_ms(100);
		test = false;
	}
	else
	{
		test = true;
		update_LEDS_single(LED3_NO,0x00);
		delay_cycles_ms(100);
	}
	*/
	check_timeout();
	if(transfer_complete_spi_slave == true)
	{
		
		//port_pin_set_output_level(PIN_PA27,true);
		/*
		buffer_storage[count_buffer] = received_value[0]; 
		count_buffer++;
		buffer_storage[count_buffer] = received_value[1];
		count_buffer++;-
		if(count_buffer == 500)
		{
			count_buffer = 0;
		}
		*/
		rw   = received_value[0] & MASK_RW ;
		mode = received_value[0] & MASK_MODE;
		if(rw == WRITE_SPI)
		{
			
			switch(mode)
			{
				case LED1_S:
					update_LEDS_single(LED1_NO,received_value[1]);
					break;
				case LED4_S:
					update_LEDS_single(LED2_NO,received_value[1]);
					break;
				
				case RGB1_S:
					
				    update_ORB_single(RGB1_NO , received_value[1] , received_value[2] , received_value[3]);
					break;
				
				case RGB2_S:
					
					update_ORB_single(RGB2_NO , received_value[1] , received_value[2] , received_value[3]);
					break;
					
				case SERVO1_S:
					update_super_servo_single(SERVO1_NO,received_value[1]);
					break;
					
				case SERVO2_S:
					update_super_servo_single(SERVO2_NO,received_value[1]);
					break;

				case SERVO3_S:
					update_super_servo_single(SERVO3_NO,received_value[1]);
					break;

				case SERVO4_S:
					update_super_servo_single(SERVO4_NO,received_value[1]);
					break;
					
				case SET_ALL:
					update_ORB(received_value[1],received_value[2] ,received_value[3] ,received_value[4] ,received_value[5] ,received_value[6]  );
					update_LEDS(received_value[7],received_value[8]);
					update_super_servo(received_value[11] , received_value[12] , received_value[13], received_value[14]);
					break;
				
				/*
				case DEVICE_VERSION:
					update_device();
				*/	
				case STOP_ALL:
					switch_off_LEDS();
					switch_off_ORB();
					break;
				
				default:
					break;
			}
			
		}
		else if(rw == READ_SPI)
		{
			
		}
		transfer_complete_spi_slave = false;
		error_code = spi_transceive_buffer_job(&spi_slave_instance, sensor_outputs, received_value,SPI_LENGTH);
		serial_timeout = false;
			
	}
	
}		
	
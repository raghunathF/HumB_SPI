/*
 * SPI_control.c
 *
 * Created: 2/5/2018 4:46:53 PM
 *  Author: Raghunath Jangam
 */ 

#include <asf.h>
#include "SPI_control.h"
#include "SPI_slave.h"
#include "ORB_control.h"
#include "sensor_control.h"
#include "super_servo_control.h"

#define   APP

void check_timeout()
{
	if(transcation_start == true)
	{
		if(serial_timeout == true)
		{
			serial_timeout_count = 0;
			serial_timeout = false;
			transcation_start = false;
			spi_reset(&spi_slave_instance);
			spi_slave_init();
			spi_transceive_buffer_job(&spi_slave_instance, sensor_outputs, received_value,SPI_LENGTH);
		}
	}
	
}


#define PORT_CLEAR_REGISTER_ADD     0x41004414UL
#define PORT_SET_REGISTER_ADD		0x41004418UL

void spi_main_loop()
{
	
	enum status_code error_code = 0x10;
	uint32_t B2_RGB = 0x08000000;
	uint32_t G2_RGB = 0x00000200;
	volatile static uint16_t count_buffer = 0;
	volatile uint32_t* const  PORT_SET		      = PORT_SET_REGISTER_ADD;
	volatile uint32_t* const PORT_CLEAR_REGISTER  = PORT_CLEAR_REGISTER_ADD;
    static uint8_t  prev_servo[4];
	static uint8_t  prev_led[2];
	static uint8_t  prev_rgb[6];
	uint8_t i    = 0;
	uint8_t rw   = 0;
	uint8_t mode = 0;
	static bool test = true;
	transmit_value[0] = 0x88;
	transmit_value[1] = 0xAA;
	transmit_value[2] = 0xBB;
	transmit_value[3] = 0xCC;
	check_timeout();
	if(transfer_complete_spi_slave == true)
	{	
		check_buffer();	
		rw   = temp_receive[0] & MASK_RW ;
		mode = temp_receive[0] & MASK_MODE;
		if(rw == WRITE_SPI)
		{	
			switch(mode)
			{
				case LED1_S:
					if( prev_led[0] != temp_receive[1])
					{
						update_LEDS_single(LED1_NO,temp_receive[1]);
						prev_led[0] = temp_receive[1];
					}
					break;
					
				case LED4_S:
					if( prev_led[1] != temp_receive[1] )
					{
						update_LEDS_single(LED2_NO,temp_receive[1]);
						prev_led[1] = temp_receive[1];
					}
					break;
				
				case RGB1_S:
					if( (prev_rgb[0] != temp_receive[1]) || (prev_rgb[1] != temp_receive[2]) || (prev_rgb[2]!= temp_receive[3]))
				    {
						update_ORB_single(RGB1_NO , temp_receive[1] , temp_receive[2] , temp_receive[3]);
						prev_rgb[0]  = temp_receive[1];
						prev_rgb[1]  = temp_receive[2];
						prev_rgb[2]  = temp_receive[3];
					}
					break;
				
				case RGB2_S:
					if( (prev_rgb[3] != temp_receive[1]) || (prev_rgb[4] != temp_receive[2]) || (prev_rgb[5]!= temp_receive[3]))
					{
						update_ORB_single(RGB2_NO , temp_receive[1] , temp_receive[2] , temp_receive[3]);
						prev_rgb[3]  = temp_receive[1];
						prev_rgb[4]  = temp_receive[2];
						prev_rgb[5]  = temp_receive[3];
					}
					break;
					
				case SERVO1_S:
				
					if(prev_servo[0] != temp_receive[1])
					{
						update_super_servo_single(SERVO1_NO,temp_receive[1]);
						prev_servo[0] = temp_receive[1];
					}
					break;
					
				case SERVO2_S:
				    //*PORT_SET						= B2_RGB;
					//if(prev_servo[1] != temp_receive[1])
					//{
						
						update_super_servo_single(SERVO2_NO,temp_receive[1]);
						//prev_servo[1] = temp_receive[1];
					//}
					//*PORT_CLEAR_REGISTER            = B2_RGB;
					break;
					
				case SERVO3_S:
					if(prev_servo[2] != temp_receive[1])
					{
						update_super_servo_single(SERVO3_NO,temp_receive[1]);
						prev_servo[2] = temp_receive[1];
					}
					break;

				case SERVO4_S:
					if(prev_servo[3] != temp_receive[1])
					{
						update_super_servo_single(SERVO4_NO,temp_receive[1]);
						prev_servo[3] = temp_receive[1];
					}
					break;
					
				case SET_ALL:
					update_ORB_LED(temp_receive[3],temp_receive[4] ,temp_receive[5] ,temp_receive[6] ,temp_receive[7] ,temp_receive[8],temp_receive[1],temp_receive[2]);
					update_super_servo(temp_receive[9] , temp_receive[10] , temp_receive[11], temp_receive[12]);
					prev_led[0] = temp_receive[1] ; prev_led[1]= temp_receive[2];
					for(i=0 ; i<6 ; i++)
					{
						prev_rgb[i]   = temp_receive[3+i];
					} 
					for(i=0 ; i<4 ; i++)
					{
						prev_servo[i]   = temp_receive[9+i];
					} 
					break;
				
				case STOP_ALL:
					switch_off_ORB_LED();
					switch_off_servos();
					prev_led[0] = 0;
					prev_led[1] = 0;
					for(i=0 ; i<6 ; i++)
					{
						prev_rgb[i]   = 0;
					}
					for(i=0 ; i<4 ; i++)
					{
						prev_servo[i] = 0xFF;
					}
					//Update previous values RGB LED to 
					
					break;
				
				default:
					break;
			}
			
		}
		else if(rw == READ_SPI)
		{
			
		}
			
	}
	
}		
	
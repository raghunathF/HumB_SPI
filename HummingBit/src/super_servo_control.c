/*
 * super_servo_control.c
 *
 * Created: 12/11/2017 10:01:41 AM
 *  Author: raghu
 */ 
#include <asf.h>
#include "super_servo_control.h"
#include "super_servo.h"
#define SERVO_OFF_VALUE 0xFF

void switch_off_servos()
{
	update_super_servo(SERVO_OFF_VALUE,SERVO_OFF_VALUE,SERVO_OFF_VALUE,SERVO_OFF_VALUE);
}
#define PORT_CLEAR_REGISTER_ADD     0x41004414UL
#define PORT_SET_REGISTER_ADD		0x41004418UL
void update_super_servo(uint8_t servo1 , uint8_t servo2 , uint8_t servo3, uint8_t servo4)
{
	static uint8_t prev_servo1 = 0;
	static uint8_t prev_servo2 = 0;
	static uint8_t prev_servo3 = 0;
	static uint8_t prev_servo4 = 0;
	
	//Servo--1
	if(servo1  != prev_servo1)
	{
		if(servo1 != 255)
		{
			tcc_set_compare_value(&tcc_ss_instance0, SERVO_1_CH, (((3520*servo1)/254) + 1280));
		}
		else
		{
			tcc_set_compare_value(&tcc_ss_instance0, SERVO_1_CH, 0);
		}
		prev_servo1 = servo1;
	}
	
	//Servo--2
	if(servo2  != prev_servo2)
	{
		if(servo2 != 255)
		{
			tcc_set_compare_value(&tcc_ss_instance0, SERVO_2_CH, (((3520*servo2)/254) + 1280));
		}
		else
		{
			tcc_set_compare_value(&tcc_ss_instance0, SERVO_2_CH, 0);
		}
		prev_servo2 = servo2;
	}
	//Servo--3
	if(servo3  != prev_servo3)
	{
		if(servo3 != 255)
		{
			tcc_set_compare_value(&tcc_ss_instance0, SERVO_3_CH, (((3520*servo3)/254) + 1280));
		}
		else
		{
			tcc_set_compare_value(&tcc_ss_instance0, SERVO_3_CH, 0);
		}
		prev_servo3 = servo3;
	}
	//Servo--4
	if(servo4  != prev_servo4)
	{
		if(servo4 != 255)
		{
			tcc_set_compare_value(&tcc_ss_instance0, SERVO_4_CH, (((3520*servo4)/254) + 1280));
		}
		else
		{
			tcc_set_compare_value(&tcc_ss_instance0, SERVO_4_CH, 0);
		}
		prev_servo4 = servo4;
	}
}

void update_super_servo_single(uint8_t port_no ,uint8_t super_servo)
{
	uint32_t B2_RGB = 0x08000000;
	uint32_t G2_RGB = 0x00000200;
	volatile uint32_t* const  PORT_SET		      = PORT_SET_REGISTER_ADD;
	volatile uint32_t* const PORT_CLEAR_REGISTER  = PORT_CLEAR_REGISTER_ADD;
	switch (port_no)
	{
		case '1':
				if(super_servo != 255)
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_1_CH, (((3520*super_servo)/254) + 1280));
				}
				else
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_1_CH, 0);
				}
				break;
		case '2':
				
				//*PORT_SET           = B2_RGB;
				if(super_servo != 255)
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_2_CH, (((3520*super_servo)/254) + 1280));
				}
				else
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_2_CH, 0);
				}
				//*PORT_CLEAR_REGISTER            = B2_RGB;
				break;
		case '3':
				if(super_servo != 255)
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_3_CH, (((3520*super_servo)/254) + 1280));
				}
				else
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_3_CH, 0);
				}
				break;
		case '4':
				if(super_servo != 255)
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_4_CH, (((3520*super_servo)/254) + 1280));
				}
				else
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_4_CH, 0);
				}
				break;	
		default:
				break;
	}
	
}
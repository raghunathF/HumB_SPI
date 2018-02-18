/*
 * super_servo_control.c
 *
 * Created: 12/11/2017 10:01:41 AM
 *  Author: raghu
 */ 
#include <asf.h>
#include "super_servo_control.h"
#include "super_servo.h"

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
				if(super_servo != 255)
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_2_CH, (((3520*super_servo)/254) + 1280));
				}
				else
				{
					tcc_set_compare_value(&tcc_ss_instance0, SERVO_2_CH, 0);
				}
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
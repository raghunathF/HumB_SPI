/*
 * ORB_control.c
 *
 * Created: 12/8/2017 9:44:53 AM
 *  Author: raghu
 */ 

#include <asf.h>
#include "ORB_control.h"
#include "ORB.h"

void update_ORB(uint8_t r1 ,uint8_t g1 ,uint8_t b1 ,uint8_t r2 ,uint8_t b2 ,uint8_t g2  )
{
 	temp_compare_array_2[0] = 255-r1;//Left -- R
 	temp_compare_array_2[1] = 255-g1;//Left  -- G
 	temp_compare_array_2[2] = 255-b1;//Left  -- B
 	temp_compare_array_2[3] = 255-r2;//Right -- R
 	temp_compare_array_2[4] = 255-b2;//Right  -- G
 	temp_compare_array_2[5] = 255-g2;//Right -- B
	initializing_pin_array();
	increasing_sort_tag();
	transfer_temp();
	update_compare_array = true;
}


void update_ORB_single(uint8_t port_no , uint8_t r , uint8_t g , uint8_t b)
{
	if(port_no == '1') //ASCII 1
	{
		temp_compare_array_2[0] = 255-r;//Left -- R
		temp_compare_array_2[1] = 255-g;//Left  -- G
		temp_compare_array_2[2] = 255-b;//Left  -- B
	}
	else if(port_no == '2')//ASCII 2
	{
		temp_compare_array_2[3] = 255-r;//Right -- R
		temp_compare_array_2[4] = 255-b;//Right  -- G
		temp_compare_array_2[5] = 255-g;//Right -- B
	}
	initializing_pin_array();
	increasing_sort_tag();
	transfer_temp();
	update_compare_array = true;
	
}

void switch_off_ORB()
{
	temp_compare_array_2[0] = 255;//Left -- R
	temp_compare_array_2[1] = 255;//Left  -- G
	temp_compare_array_2[2] = 255;//Left  -- B
	temp_compare_array_2[3] = 255;//Right -- R
	temp_compare_array_2[4] = 255;//Right  -- G
	temp_compare_array_2[5] = 255;//Right -- B
	initializing_pin_array();
	increasing_sort_tag();
	transfer_temp();
	update_compare_array = true;
}
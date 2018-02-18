/*
 * UART_control.c
 *
 * Created: 12/12/2017 8:47:35 AM
 *  Author: raghu
 */ 
#include <asf.h>
#include "UART_control.h"
#include "UART.h"
#include "LED_control.h"
#include "ORB_control.h"
#include "sensor_control.h"
#include "super_servo_control.h"

extern volatile uint8_t ring_buffer[MAX_LIMIT_RING_BUFFER];
extern volatile uint8_t tail_ring_buffer;
extern volatile uint8_t head_ring_buffer;
extern volatile bool received_data_updated;


void serial_receive_bytes(uint8_t count_receive ,uint8_t* receive_data)
{
	uint8_t i =0;
	while((head_ring_buffer - tail_ring_buffer) < count_receive )
	{
		if(serial_timeout)
		{
			//serial_timeout = false;
			return;
		}
	}
	for(i=1;i<=count_receive;i++)
	{
		receive_data[i] = ring_buffer[tail_ring_buffer];
		tail_ring_buffer++;
	}
}


void serial_main_loop_1()
{
	uint8_t received_value[MAX_REC_BYTE]; //Changed Volatile 
	static uint8_t prev_rec_value[MAX_REC_BYTE];
	uint8_t transmit_value[MAX_TRANSMIT_VALUE];
	int temp=0;
	static  bool broadcast    = false;
	static  bool notification = false;
	static  uint8_t job_done  = FAILURE;

	//usart_read_job(&usart_instance ,)
	uint8_t i =0;
	if(head_ring_buffer != tail_ring_buffer)
	{
		received_value[0] = ring_buffer[tail_ring_buffer];
		tail_ring_buffer++;
		switch(received_value[0])
		{
			
			//Set all the actuator values
			case 'u':
				serial_timeout_count = 0;
				serial_timeout = false;
				serial_receive_bytes(ALL_SET_LEN,received_value);
				if(serial_timeout == false)
				{
					if((received_value[1]^prev_rec_value[1]) || (received_value[2]^prev_rec_value[2]) || (received_value[3]^prev_rec_value[3]) || (received_value[4]^prev_rec_value[4]) || (received_value[5]^prev_rec_value[5]) || (received_value[6]^prev_rec_value[6]))
					{
						update_ORB(received_value[1] , received_value[2] , received_value[3], received_value[4] , received_value[5] , received_value[6]);
					}
					if((received_value[7]^prev_rec_value[7]) || (received_value[8]^prev_rec_value[8]) || (received_value[9]^prev_rec_value[9]) || (received_value[10]^prev_rec_value[10]) )
					{
						update_super_servo(received_value[7] , received_value[8] , received_value[9] , received_value[10]);
					}
					if((received_value[11]^prev_rec_value[11]) || (received_value[12]^prev_rec_value[12]) || (received_value[13]^prev_rec_value[13]) || (received_value[13]^prev_rec_value[13]))
					{
						//update_LEDS(received_value[11], received_value[12],received_value[13],received_value[14]);
					}
					for(i=1;i<=ALL_SET_LEN;i++)
					{
						prev_rec_value[i] = received_value[i];
					}
				}
				else
				{
					serial_timeout_count = 0;
				}
				job_done = SUCCESS; 
				break;
			
			//Get all the sensors values
			case 'v':
				serial_timeout_count = 0;
				serial_timeout = false;
				transmit_value[0] = read_sensor(SENSOR_NO_1);
				transmit_value[1] = read_sensor(SENSOR_NO_2);
				transmit_value[2] = read_sensor(SENSOR_NO_3);
				transmit_value[3] = read_sensor(SENSOR_NO_4);
				
				usart_write_buffer_wait(&usart_instance, transmit_value, SENSORS_TRANSMIT_LENGTH);

				break;
				
			//Broadcast
			case 'b':
				serial_timeout_count = 0;
				serial_timeout = false;
				serial_receive_bytes(SENSORS_GET_LEN,received_value);
				count_broadcast = 0;
				switch(received_value[1])
				{
					//Start broadcast
					case 'g':
						
						broadcast = true;
						break;	
					//Stop broadcast
					case 's':
					
						broadcast = false;
						break;
					
					default :
					
						head_ring_buffer = 0;
						tail_ring_buffer = 0;
						break;
					
				}
				break;
			
			case 'O':
				serial_timeout_count = 0;
				serial_timeout = false;
				serial_receive_bytes(ORB_SET_LEN,received_value);
				if(serial_timeout == false)
				{
					update_ORB_single(received_value[1],received_value[2], received_value[3], received_value[4]);
				}
				job_done = SUCCESS; 
				break;
				
			case 'L':
				serial_timeout_count = 0;
				serial_timeout = false;
				serial_receive_bytes(LEDS_SET_LEN,received_value);
				if(serial_timeout == false)
				{
					update_LEDS_single(received_value[1],received_value[2]);
				}
				job_done = SUCCESS; 
				break;
				
				
			case 'S':
				serial_timeout_count = 0;
				serial_timeout = false;
				serial_receive_bytes(SUPER_SERVO_SET_LEN,received_value);
				if(serial_timeout == false)
				{
					update_super_servo_single(received_value[1],received_value[2]);
				}
				job_done = SUCCESS; 
				break;
				
			case 's':
				serial_timeout_count = 0;
				serial_timeout = false;
				serial_receive_bytes(SENSORS_GET_LEN,received_value);
				volatile uint8_t temp = 0 ;
				if(serial_timeout == false)
				{
					switch(received_value[1])
					{
						case '1':
							transmit_value[0] = read_sensor(SENSOR_NO_1);
							//transmit_value[0] = sensor_outputs[i];
							usart_write_buffer_wait(&usart_instance, transmit_value ,SENSORS_SET_LEN);
							//if(transmit_value[0] == 0)
							//{
							//	transmit_value[0] = 0;
							//}
							break;
							
						case '2':
							transmit_value[0] = read_sensor(SENSOR_NO_2);
							usart_write_buffer_wait(&usart_instance, transmit_value ,SENSORS_SET_LEN);
							break;
					
						case '3':
							transmit_value[0] = read_sensor(SENSOR_NO_3);
							usart_write_buffer_wait(&usart_instance, transmit_value ,SENSORS_SET_LEN);
							break;
							
						case '4':
							transmit_value[0] = read_sensor(SENSOR_NO_4);
							usart_write_buffer_wait(&usart_instance, transmit_value ,SENSORS_SET_LEN);
							break;
							
						default:
						
							head_ring_buffer = 0;
							tail_ring_buffer = 0;
							break;
					
					}
				}
				break;
			case 't':
				serial_timeout_count = 0;
				serial_timeout = false;
				serial_receive_bytes(SENSORS_GET_LEN,received_value);
				delay_cycles_ms(MC_UART_DELAY);
				
				if(serial_timeout == false)
				{
					switch(received_value[1])
					{
						case '1':
						transmit_value[0] = read_sensor(SENSOR_NO_1);
						//transmit_value[0] = sensor_outputs[i];
						usart_write_buffer_wait(&usart_instance, transmit_value ,SENSORS_SET_LEN);
						//if(transmit_value[0] == 0)
						//{
						//	transmit_value[0] = 0;
						//}
						break;
					
						case '2':
						transmit_value[0] = read_sensor(SENSOR_NO_2);
						usart_write_buffer_wait(&usart_instance, transmit_value ,SENSORS_SET_LEN);
						break;
					
						case '3':
						transmit_value[0] = read_sensor(SENSOR_NO_3);
						usart_write_buffer_wait(&usart_instance, transmit_value ,SENSORS_SET_LEN);
						break;
					
						case '4':
						transmit_value[0] = read_sensor(SENSOR_NO_4);
						usart_write_buffer_wait(&usart_instance, transmit_value ,SENSORS_SET_LEN);
						break;
					
						default:
					
						head_ring_buffer = 0;
						tail_ring_buffer = 0;
						break;
					
					}
				}
			break;
				
			case 'R':
				serial_timeout_count = 0;
				serial_timeout = false;
				switch_off_LEDS();
				switch_off_ORB();
				//Previous received values updated
				for(i=0;i<6;i++)
				{
					prev_rec_value[i] = 0;
				}
				for(i=11;i<15;i++)
				{
					prev_rec_value[i] =0;
				}
				broadcast = false;
				job_done = SUCCESS; 
			/*		
			case 'x':
				serial_timeout_count = 0;
				serial_timeout = false;
				switch_off_LEDS();
				switch_off_ORB();
				for(i=0;i<6;i++)
				{
					prev_rec_value[i] = 0;
				}
				for(i=11;i<15;i++)
				{
					prev_rec_value[i] =0;
				}
				
				break;	
			*/	
			case 'N':
				//Notification on
				serial_timeout_count = 0;
				serial_timeout = false;
				serial_receive_bytes(SENSORS_GET_LEN,received_value);
				count_broadcast = 0;
				switch(received_value[1])
				{
					//Start notification
					case 'g':
						notification = true;
						break;
					//Stop broadcast
					case 's':
						notification = false;
						break;
					
					default :
						head_ring_buffer = 0;
						tail_ring_buffer = 0;
					break;
					
				}
				job_done = SUCCESS; 
				break;
			/*
			case 'z':
				transmit_value[0] = TEST_TRANSMIT_COUNT-1;
				transmit_value[1] = count;
				count++;
				usart_write_buffer_wait(&usart_instance, transmit_value, TEST_TRANSMIT_COUNT);
				break;
			*/
			default:
				head_ring_buffer = 0;
				tail_ring_buffer = 0;
				break;
		}
		
		if((head_ring_buffer == tail_ring_buffer) || (head_ring_buffer > MAX_LIMIT_RING_BUFFER) || (tail_ring_buffer > MAX_LIMIT_RING_BUFFER) || (serial_timeout == true))
		{
			head_ring_buffer = 0;
			tail_ring_buffer = 0;
		}
	 }		//received_data_updated = false;	
	 if(notification == true)
	 {
		 if(job_done == SUCCESS)
		 {
			 transmit_value[0] = job_done;
			 usart_write_buffer_wait(&usart_instance, transmit_value, NOTIFICATION_TRANSMIT_LENGTH);
		 }
		 job_done = FAILURE;
	 }
	 if(broadcast == true)
	 {
		if(count_broadcast > MAX_COUNT_BROADCAST)
		{
			count_broadcast = 0;
			transmit_value[0] = read_sensor(SENSOR_NO_1);
			transmit_value[1] = read_sensor(SENSOR_NO_2);
			transmit_value[2] = read_sensor(SENSOR_NO_3);
			transmit_value[3] = read_sensor(SENSOR_NO_4);
			usart_write_buffer_wait(&usart_instance, transmit_value, SENSORS_TRANSMIT_LENGTH);
		}
	 }	 
}
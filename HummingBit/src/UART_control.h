/*
 * UART_control.h
 *
 * Created: 12/12/2017 8:48:11 AM
 *  Author: raghu
 */ 


#ifndef UART_CONTROL_H_
#define UART_CONTROL_H_

#define SUCCESS 0x55
#define FAILURE 0x00

#define MAX_REC_BYTE 20
#define MAX_TRANSMIT_VALUE 20
#define NOTIFICATION_TRANSMIT_LENGTH 1
#define SENSORS_TRANSMIT_LENGTH 4
#define TEST_TRANSMIT_COUNT 2
#define SENSORS_GET_LEN 1
#define SENSORS_SET_LEN 1
#define VERSION_TRANSMIT_LENGTH 5
#define BATTERY_TRANSMIT_LENGTH 1

#define MAX_LIMIT_RING_BUFFER 255
#define  MAX_COUNT_BROADCAST 2

#define  SUPER_SERVO_SET_LEN 2
#define  ORB_SET_LEN 4
#define  LEDS_SET_LEN 2
#define  ALL_SET_LEN 14


#define SENSOR_NO_1 0
#define SENSOR_NO_2 1
#define SENSOR_NO_3 2
#define SENSOR_NO_4 3

void serial_main_loop_1();


extern volatile uint8_t serial_timeout_count;
extern volatile bool serial_timeout;
extern volatile uint8_t count_broadcast;

extern volatile uint8_t sensor_outputs[4];

#define  FW_VERSION_MSB 0x00
#define  FW_VERSION_LSB 0x01
#define  HW_VERSION_MSB 0x00
#define  HW_VERSION_LSB 0x01




#endif /* UART_CONTROL_H_ */
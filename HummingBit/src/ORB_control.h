/*
 * ORB_control.h
 *
 * Created: 12/8/2017 9:45:25 AM
 *  Author: raghu
 */ 


#ifndef ORB_CONTROL_H_
#define ORB_CONTROL_H_

void update_ORB(uint8_t r1 ,uint8_t g1 ,uint8_t b1 ,uint8_t r2 ,uint8_t b2 ,uint8_t g2  );
void update_ORB_single(uint8_t port_no , uint8_t r , uint8_t g , uint8_t b);
void switch_off_ORB();

extern uint8_t temp_compare_array[6];
extern uint8_t temp_compare_array_2[6];
extern bool update_compare_array;

#endif /* ORB_CONTROL_H_ */
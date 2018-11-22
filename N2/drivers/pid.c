// PID.c - Richard McCrae-Lauba

#include "../misc/bit_manipulation.h"
#include "../misc/macros.h"
#include "motor.h"
#include "pid.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <avr/interrupt.h>

volatile int timer_flag = 0;

//int Kp = 110;		//1.1*100
//int Ki = 10;		//1*10
//int Kd = 100; 		//Kd * 1000

ISR(TIMER3_COMPA_vect){
	//TCNT3 = 0;
	timer_flag = 1;
}

void PID_init(){
	// Set prescaler to 1/64
	TCCR3B |= (1 << CS31) | (1 << CS30);
	
	// Set the desired output compare match that will generate a timer interrupt
	// Choose dt = 0.1s=10Hz -> OCR3A = 25000 - 10Hz = 16000000/64/(OCR3A-1)
	OCR3A = 0x61A8;
	//OCR3A = 0x30D4;
	
	// Enable output compare interrupt 3A
	TIMSK3 |= (1 << OCIE3A);
}

void PID(int rot, uint8_t pos_ref){

	static int integral;
	static int speed;
	static int error_prev;
	int error;
	int derivative;
	//int dt = 1;		//0.1*10
	
	switch(timer_flag){
		case 0:
			break;
		case 1:
			error = pos_ref - rot;
			if (abs(error) > 10){
				integral = integral + error*dt;
			}
			derivative = (error - error_prev)/dt;
			speed = KP*error + KI*integral + KD*derivative;
			error_prev = error;
			timer_flag = 0;
			break;
	}
	
	speed = (int)speed/100;

	if(speed<0) {
			MOTOR_setDir(WEST);
		} else if(speed>0) {
			MOTOR_setDir(EAST);
		}
		MOTOR_setSpeed((uint8_t)speed);


/*
	if (timer_flag){
		clear_bit(TIMSK2,TOIE2); //disable interrupt while handling PID 
		int16_t motor_rot = motorRotation_read();
		double measured = (double)((motor_rot - rot_min)/(double)(rot_max))*255; //Scale to 0-255 based on calibrated values

		//Position saturation.
		if(pos_ref >240){
			pos_ref = 240;
		} else if(pos_ref<10){
			pos_ref = 10;
		}
		
		int16_t error = pos_ref - (int)measured;
		integral = integral + error * dt;

		//if abs(error) < 1
		if (error < 1 && error > -1){
			integral = 0;
		}
	
		double derivative = (error - prev_error)/dt;
		int16_t speed = 0;
		uint8_t speed_pid = 0;
		speed = error*KP + integral*KI + derivative*KD;
		prev_error = error;

		if (speed < 0){
			motorDir(WEST);
			speed_pid = -speed;
		}
		else{
			motorDir(EAST);
			speed_pid = speed;
		}

		motorSpeed_PID(speed_pid);
		printf("SPEED PID: %d\r\n", speed_pid);
		timer_flag = 0;
		set_bit(TIMSK2,TOIE2); //Enable timer interrupt again 
	}
*/
}

int PID_ref(uint8_t ref){
	int new_ref;
	// 255 is max right, 0 is max left.
	new_ref = abs(ref - 0xFF); 
	printf("NEW REF: %d\r\n", new_ref);
	return new_ref;
}
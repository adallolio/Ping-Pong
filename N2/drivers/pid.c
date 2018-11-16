// PID.c - Richard McCrae-Lauba

#include "../misc/bit_manipulation.h"
#include "../misc/macros.h"
#include "motor.h"
#include "pid.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

ISR(TIMER2_OVF_vect){
	timer_flag = 1;
}

void PID_init(void){

	cli();

	TIMSK2=(1<<TOIE2); // enable timer overflow interrupt for Timer2
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22); // start timer2 with /1024 prescaler
	
	sei();
}

void PID_cal(void){
	motorDir(LEFT);
	motorSpeed_PID(50);
	int16_t cur_rot = motorRotation_read();
	int16_t prev_rot = cur_rot+200;

	while(prev_rot != cur_rot){
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = motorRotation_read();
	}
	
	motorSpeed(0);
	_delay_us(500);
	motorEncoder_reset();

	motorDir(RIGHT);
	motorSpeed_PID(50);
	cur_rot = 0;
	prev_rot = cur_rot-200;

	while(prev_rot != cur_rot){
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = motorRotation_read();
	}
	motorSpeed(0);
	rot_max = cur_rot;
	
}
void PID(uint8_t pos_ref){
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
			motorDir(LEFT);
			speed_pid = -speed;
		}
		else{
			motorDir(RIGHT);
			speed_pid = speed;
		}

		motorSpeed_PID(speed_pid);
		timer_flag = 0;
		set_bit(TIMSK2,TOIE2); //Enable timer interrupt again 
	}
}

// Servo.c - Richard McCrae-Lauba

#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"
#include "servo.h"
#include "pwm.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void servo_init(uint32_t cpu_speed){
	float period = 0.02;
	float initial_pos = 0.0015;
	PWM_init(period,cpu_speed);
	PWM_pulse_set(initial_pos);
}

void set_servo(uint8_t servo_dir){
	//Servo has slight offset  MUST TEST OUT OWN SERVO
	//if(servo_dir-37 >= 0){
	//	servo_dir -= 37;
	//}
    // Set servo limits
	float min_pw = 0.00095;
	float max_pw = 0.00205;
	float max = 255;
	float min = 0;
	float servo_pw;
	float dir;

	if(servo_dir>160){
		servo_pw = max_pw;
	} else if(servo_dir<50) {
		servo_pw = min_pw;
	} else {
		dir = (float)servo_dir;
		servo_pw = (dir/max)*(max_pw-min_pw)+min_pw;
		//float servo_pw = dir/211666.7 + 0.0009;  // Convert joystick 0-255 position value to between min_pw and max_pw
	}

	printf("servo: %f \n\r", servo_pw);

	//Servo can never go beyond range 0.9-2.1ms
	if (servo_pw < min_pw) {
		servo_pw = min_pw;
	}
	if (servo_pw > max_pw) {
		servo_pw = max_pw;
	}

	//printf("Servo PW: %f\n\r", servo_pw);
	PWM_pulse_set(servo_pw);

}
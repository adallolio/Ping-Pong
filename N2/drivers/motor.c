// MOTOR.c - Richard McCrae-Lauba

#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"
#include "motor.h"
#include "dac.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

volatile uint8_t vel_max = 0x60;
const uint8_t vel_init = 0x60;
int16_t encoder_max;

void MOTOR_init(){
	
/*
	// Set MJ1 pins as output
	// PH4 = EN, PH1 = DIR, PH3 = SEL, PH5 = !OE, PH6 = RST
	DDRH |= (1 << PH4) | (1 << PH1) | (1 << PH3) | (1 << PH5) | (1 << PH6);
	
	// Enable motor and select direction in MJ1
	PORTH |= (1 << PH4) | (1 << PH1);
	
	// Setup encoder: set MJ2 pins as input - ADC 8-15, ADCH which is connected via MJ2
	DDRK = 0x00;

	// Reset encoder
	MOTOR_encoderReset();
	
*/

	// Enable motor
	set_bit(DDRH, PH4);
	set_bit(PORTH, PH4);
	
	// Set direction pin to output
	set_bit(DDRH, PH1);
	
	// Enable control for output enable. Remember: active low - !OE
	set_bit(DDRH, PB5);
	
	// Enable control for selection pin: SEL
	set_bit(DDRH, PH3);
	
	// Enable control for Reset pin: RST
	set_bit(DDRH, PH6);

	
	// Set data bits to input, 
	clear_bit(DDRK, PK0);
	clear_bit(DDRK, PK1);
	clear_bit(DDRK, PK2);
	clear_bit(DDRK, PK3);
	clear_bit(DDRK, PK4);
	clear_bit(DDRK, PK5);
	clear_bit(DDRK, PK6);
	clear_bit(DDRK, PK7);	

	MOTOR_encoderReset();
}


void MOTOR_setDir(motor_direction dir){
	switch (dir){
		// Change to EAST and WEST as used in N1 if we wish
		case(WEST): // WEST is joystick 0-127, 121 is selected to have a defined value for the middle
			clear_bit(PORTH, PH1); // PH1 is motor direction pin on MJ1, 0 = left
			break;
		case(EAST): // EAST is joystick 128-255
			set_bit(PORTH, PH1); // PH1 HIGH = right
			break;
	}
}

void MOTOR_setSpeed(uint8_t speed){

	uint8_t vel;

	// Velocity saturation based on max speed.
	if (speed < vel_max){
		vel = speed;
	} else{
		vel = vel_max;
	}

	//printf("vel:%d\r\n",vel);

	DAC_send(vel);

/*
	if(speed > 126){ //Limits speed based on direction
		MOTOR_setDir(EAST);
		DAC_send(speed-127);
		
	} else{
		MOTOR_setDir(WEST);
		DAC_send(126-speed);
	}
*/
}

/*
void MOTOR_setSpeedPID(uint8_t speed){
		DAC_send(speed);
}
*/

void MOTOR_encoderReset() {
	clear_bit(PORTH, PH6); // Set active low reset.
	_delay_us(200);
	set_bit(PORTH, PH6);
}

int16_t MOTOR_rotRead(void){

	//Set !OE low to enable output of encoder PH5
	clear_bit(PORTB, PH5);
	
	//Set SEL low to get high byte
	clear_bit(PORTH, PH3);
	//Set SEL high to get low byte
	//set_bit(PORTH, PH3);
	
	_delay_us(60);
	
	//Read MSB
	uint8_t MSB;
	MSB = PINK; 
	
	//Set SEL high to get low byte
	set_bit(PORTH, PH3);
	//Set SEL low to get high byte
	//clear_bit(PORTH, PH3);
	
	_delay_us(60);
	
	// Read LSB
	uint8_t LSB;
	LSB = PINK;

	//Set !OE high to disable output of encoder
	set_bit(PORTB, PH5);
	
	int16_t rot = (int16_t) ( (MSB << 8) | LSB);
	
	printf("ROT: %d\r\n",rot);
	return rot;
}


int MOTOR_rotScaled(void){
	// Scaled between 0 and 255
	float enc_min = -4200;
	float enc_max = 4200;
	float range_min = 0;
	float range_max = 255;
	float val = ((float)MOTOR_rotRead()-enc_min)*((range_max-range_min)/(enc_max-enc_min))+range_min;
	if(val<0) {
		val = 0.0;
	} else if(val>255) {
		val = 255.0;
	}
	printf("ROT SCALED: %f\r\n",val);
	return (int)val;
}


void MOTOR_cal(void){

	MOTOR_setDir(EAST);
	vel_max = vel_init;
	MOTOR_setSpeed(vel_init);
	_delay_ms(2000);
	MOTOR_setSpeed(0);
	

	// Reset encoder
	MOTOR_encoderReset();
	
	// Find max encoder value
	MOTOR_setDir(WEST);
	MOTOR_setSpeed(vel_init);
	_delay_ms(2000);
	MOTOR_setSpeed(0);
	encoder_max = MOTOR_rotRead();



/*
	MOTOR_setDir(WEST);
	MOTOR_setSpeed(50);
	int16_t cur_rot = MOTOR_rotRead();
	int16_t prev_rot = cur_rot+200;

	while(prev_rot != cur_rot){
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = MOTOR_rotRead();
	}
	
	MOTOR_setSpeed(0);
	_delay_us(500);
	motorEncoder_reset();

	MOTOR_setDir(EAST);
	MOTOR_setSpeed(50);
	cur_rot = 0;
	prev_rot = cur_rot-200;

	while(prev_rot != cur_rot){
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = MOTOR_rotRead();
	}
	MOTOR_setSpeed(0);
	rot_max = cur_rot;
*/

}


void MOTOR_encoderTest(void){
	//printf("Encoder: %d\r\n", MOTOR_rotRead());
}
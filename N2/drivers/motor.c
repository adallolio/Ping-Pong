// MOTOR.c - Richard McCrae-Lauba

#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"
#include "motor.h"
#include "dac.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void motor_init(){
	
	// Enable motor
	set_bit(DDRH, PH4);
	set_bit(PORTH, PH4);
	
	// Set direction pin to output
	set_bit(DDRH, PH1);
	
	// Enable control for output enable. Remember: active low - !OE
	set_bit(DDRB, PB5);
	
	// Enable control for selection pin: SEL
	set_bit(DDRH, PH3);
	
	// Enable control for Reset pin: RST
	set_bit(DDRH, PH6);

	// Reset encoder
	motorEncoder_reset();
	
	// Set data bits to input, ADC 8-15, ADCH which is connected via MJ2
	clear_bit(DDRK, PK0);
	clear_bit(DDRK, PK1);
	clear_bit(DDRK, PK2);
	clear_bit(DDRK, PK3);
	clear_bit(DDRK, PK4);
	clear_bit(DDRK, PK5);
	clear_bit(DDRK, PK6);
	clear_bit(DDRK, PK7);	
}


void motorDir(motor_direction dir){
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

void motorSpeed(uint8_t speed){
	if(speed > 126){ //Limits speed based on direction
		motorDir(EAST);
		DAC_send(speed-127);
		
	} else{
		motorDir(WEST);
		DAC_send(126-speed);
	}
}

void motorSpeed_PID(uint8_t speed){  // LEARN PID
		DAC_send(speed);
}

void motorEncoder_reset() {
	clear_bit(PORTH, PH6); // Set active low reset
	_delay_us(200); // WHY DELAY?
	set_bit(PORTH, PH6); // Finish reset
}

int16_t motorRotation_read(void){

	//Set !OE low to enable output of encoder PH5
	clear_bit(PORTB, PH5);
	
	//Set SEL high to get low byte
	set_bit(PORTH, PH3);
	
	_delay_us(60);
	
	//Read LSB
	uint8_t low = PINK; 
	
	//Set SEL low to get high byte
	clear_bit(PORTH, PH3);
	
	_delay_us(60);
	
	//Read MSB
	uint8_t high = PINK;

	//Set !OE high to disable output of encoder
	set_bit(PORTB, PH5);
	
	int16_t rot = (int16_t) ( (high << 8) | low);
	
	return rot;
}

void motorEncoder_test(void){
	printf("Encoder: %d\r\n", motorRotation_read());
}

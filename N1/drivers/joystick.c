// Alberto Dallolio - Ready Joystick

#include "joystick.h"
#include "adc.h"
#include "uart.h"
#include "../misc/macros.h"
//#include "../misc/bit_manipulation.h"
#include "../misc/memory_mapping.h"

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Joy_position central_pos;


// Read ADC.
Joy_position Joy_Read(){
	// Define new struct.
	Joy_position pos;
	// Read ADC values.
	pos.y = ADC_Read('y');
	_delay_ms(1);
	pos.x = ADC_Read('x');
	
	return pos;
}


// Calibrate Joystick.
void Joy_Cal() {
	
	central_pos = Joy_Read();

	
	int x_off;
	int y_off;
	Joy_position pos;
	Joy_position pos_next;

	printf("Press c to start the Joystick calibration ... \n\r");
	unsigned char character;
	
	while(character != 'c'){
		character = UART_receive();
	}

	printf("Calibration started ... \n\r");
	_delay_ms(1000);
	printf("Acquiring central position ... \n\r");
	
	_delay_ms(2000);
	printf("First reading \n\r");
	pos.y = ADC_Read('y');
	_delay_ms(1);
	pos.x = ADC_Read('x');
	_delay_ms(2000);
	printf("Second reading \n\r");
	pos_next.y = ADC_Read('y');
	_delay_ms(1);
	pos_next.x = ADC_Read('x');

	if(pos.y != pos_next.y || pos.x != pos_next.x)
		return;

	_delay_ms(2000);
	printf("Third reading \n\r");
	pos.y = ADC_Read('y');
	_delay_ms(1);
	pos.x = ADC_Read('x');

	if(pos.y != pos_next.y || pos.x != pos_next.x)
		return;

	_delay_ms(2000);
	printf("Compute offset ... \n\r");
	x_off = pos.x - 127;
	y_off = pos.y - 127;
	

	// Then I can apply the offset to all measurements!

	// This can also be done by registering the central position and then applying the offset everytime I read.

}

void Joy_Init() {

	// Calibrate the Joystick.
	Joy_Cal();
	printf("Joystick Central Position: %u, %u \n\r", central_pos.x, central_pos.y);

	// Initialize joystick button as input: PORT B - pin 3.
	//DDRB &= ~(1 << PINB3);
	//clear_bit(DDRB, PINB3);
	
	// Activate pull-up resistor for joystick button.
	//PORTB |= (1 << PB3);
	//set_bit(PORTB, PB3);
}

int Joy_Button() {
	return !(PINB & (1 << PINB3));
	//return !(test_bit(PINB, PINB3));
}

// Get Joystick position.
Joy_position Joy_getPos()
{
	Joy_position curr_pos = Joy_Read();
	
	Joy_position perc_pos;

	// Compute percentage and trim pos x.
	perc_pos.x = (curr_pos.x - central_pos.x) * 100 / central_pos.x;
	if (perc_pos.x > 100) {perc_pos.x = 100;}
	else if (perc_pos.x < -100) {perc_pos.x = -100;}

	// Compute and trim pos y.
	perc_pos.y = (curr_pos.y - central_pos.y) * 100 / central_pos.y;
	if (perc_pos.y > 100) {perc_pos.y = 100;}
	else if (perc_pos.y < -100) {perc_pos.y = -100;}

	printf("Joystick Position in percentage: x=%u, y=%u \n\r", perc_pos.x, perc_pos.y);

	return perc_pos;
}

// Get Joystick direction in human readable form.
Joy_direction Joy_getDir()
{
	Joy_position curr_pos = Joy_getPos();
	int dir;
	
	if (abs(curr_pos.x) < 30 && abs(curr_pos.y) < 30) {
		dir=CENTRAL;
	}
	else if (abs(curr_pos.x) > abs(curr_pos.y)){
		if (curr_pos.x > 0) {dir=RIGHT;}
		else {dir=LEFT;}
	}
	else {
		if (curr_pos.y > 0) {dir=UP;}
		else {dir=DOWN;}
	}

	printf("Joystick Direction: %d\n\r", dir);

	return dir;
}
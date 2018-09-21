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

//Joy_position central_pos;


static uint8_t max_pos_x = 255;
static uint8_t max_pos_y = 255;
static uint8_t x_off;
static uint8_t y_off;


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

	//central_pos = Joy_Read(); // to be used by getPos.

	Joy_position pos;
	Joy_position pos_next;

	/*
	printf("Press c to start the Joystick calibration ... \n\r");
	unsigned char character;
	while(1){
		character = UART_receive();
		if(character == 'c')
			break;
	}
	*/

	printf("Calibration started ... \n\r");
	_delay_ms(1000);
	printf("Acquiring central position ... \n\r");
	pos.y = ADC_Read('y');
	_delay_ms(1);
	pos.x = ADC_Read('x');
	_delay_ms(2000);
	printf("Compute offset ... \n\r");
	x_off = pos.x - 127;
	y_off = pos.y - 127;

	printf("X offset: %d\n\r", x_off);
	printf("Y offset: %d\n\r", y_off);
	printf("Calibrated X position: %d\n\r", pos.x-x_off);
	printf("Calibrated Y position: %d\n\r", pos.y-y_off);
	
	/* CALIBRATION UPON 3 READING STEPS - Fails because bits always slightly change!!
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

	if(pos.y != pos_next.y || pos.x != pos_next.x) {
		printf("The position changed! Did you move it?! \n\r");
		printf("Joystick NOT calibrated! \n\r");
		return;
	}

	_delay_ms(2000);
	printf("Third reading \n\r");
	pos.y = ADC_Read('y');
	_delay_ms(1);
	pos.x = ADC_Read('x');

	if(pos.y != pos_next.y || pos.x != pos_next.x){
		printf("The position changed! Did you move it?! \n\r");
		printf("Joystick NOT calibrated! \n\r");
		return;
	}

	*/

	// Then I can apply the offset to all measurements!

	// This can also be done by registering the central position and then applying the offset everytime I read.

}

void Joy_Init() {

	// Calibrate the Joystick.
	Joy_Cal();
	//printf("Joystick Central Position: %u, %u \n\r", central_pos.x, central_pos.y);

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
	Joy_position cal_pos;

	cal_pos.x = curr_pos.x - x_off;
	cal_pos.y = curr_pos.y - y_off;

	printf("X offset aa: %d\n\r", x_off);
	printf("Y offset aa: %d\n\r", y_off);
	printf("CAL X: %d\n\r", cal_pos.x);
	printf("CAL Y: %d\n\r", cal_pos.y);
	printf("MAX X: %d\n\r", max_pos_x);
	printf("MAX Y: %d\n\r", max_pos_y);
	
	Joy_position perc_pos;

	// Compute percentage and trim pos x.
	perc_pos.x = (cal_pos.x/max_pos_x)*100;

	// Compute and trim pos y.
	perc_pos.y = (cal_pos.y/max_pos_y)*100;

	printf("Joystick Position in percentage: x=%d, y=%d \n\r", perc_pos.x, perc_pos.y);

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
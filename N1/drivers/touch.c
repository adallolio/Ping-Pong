#include "touch.h"
#include "adc.h"
#include "../misc/macros.h"
//#include "../misc/bit_manipulation.h"

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void TOUCH_Init() {

	// Initialize PORT B - pin 1 and 2 as input
	//clear_bit(DDRB, PINB1); // ? Are the correct ones.
	(DDRB &= ~(1 << PB1));
	//clear_bit(DDRB, PINB2); // ? Are the correct ones.
	(DDRB &= ~(1 << PB2));

	//printf("Touch Initialized!\n\r");
}

int TOUCH_Button() {	
	/*
	if (test_bit(PINB, PB1) || test_bit(PINB, PB2)){
		return 1;
	}
	*/

	if( (PINB & (1 << PB1)) || (PINB & (1 << PB2)) ) {
		return 1;
	}

	return 0;
}

TOUCH_sliderPos TOUCH_Read() {
	TOUCH_sliderPos pos;
	pos.slider_left = ADC_Read('l');
	_delay_ms(1);
	pos.slider_right = ADC_Read('r');
	//printf("L: %d\n\r", pos.slider_left);
	//printf("R: %d\n\r", pos.slider_right);

	return pos;
}

TOUCH_sliderPos TOUCH_getPos() {
	TOUCH_sliderPos curr_pos = TOUCH_Read();

	return curr_pos;
} 
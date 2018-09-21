#include "touch.h"
#include "adc.h"
#include "../misc/macros.h"
//#include "../misc/bit_manipulation.h"

#include <util/delay.h>

void TOUCH_Init(){
	
	// Initialize PORT B - pin 1 and 2 as input
	clear_bit(DDRB, PINB1); // ? Are the correct ones.
	clear_bit(DDRB, PINB2); // ? Are the correct ones.
}

int TOUCH_Button()
{
	if (test_bit(PINB, PB1) || test_bit(PINB, PB2)){
		return 1;
	}
	return 0;
}

TOUCH_sliderPos TOUCH_Read()
{
	TOUCH_sliderPos pos;
	pos.slider_left = ADC_Read(SLIDER_LEFT_CH);
	_delay_ms(1);
	pos.slider_right = ADC_Read(SLIDER_RIGHT_CH);
	
	return pos;
}

TOUCH_sliderPos TOUCH_getPos()
{
	TOUCH_sliderPos curr_pos = TOUCH_Read();
	return curr_pos;
} 
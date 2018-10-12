// Alberto Dallolio - Ready Joystick

#include "joystick.h"
#include "adc.h"
#include "uart.h"
#include "../misc/macros.h"
//#include "../misc/bit_manipulation.h"
#include "../misc/memory_mapping.h"
#include "oled.h"

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//Joy_position central_pos;


static int max_pos_x = 255;
static int max_pos_y = 255;
int x_off;
int y_off;
static int central_x = 127;
static int central_y = 127;


// Read ADC.
Joy_position Joy_Read(){
	// Define new struct.
	Joy_position pos;
	// Read ADC values.
	pos.y = ADC_Read('y');
	_delay_ms(1);
	pos.x = ADC_Read('x');
	//printf("X position: %d\n\r", pos.x);
	//printf("Y position: %d\n\r", pos.y);
	
	return pos;
}


// Calibrate Joystick.
void Joy_Cal() {

	//central_pos = Joy_Read(); // to be used by getPos.

	Joy_position pos;
	Joy_position pos_next;

	//printf("Calibration started ... \n\r");
	//_delay_ms(1000);
	//printf("Acquiring central position ... \n\r");
	pos.y = ADC_Read('y');
	//_delay_ms(1);
	pos.x = ADC_Read('x');
	//_delay_ms(2000);
	//printf("Compute offset ... \n\r");
	x_off = abs(pos.x) - central_x;
	y_off = abs(pos.y) - central_y;

	//printf("X offset: %d\n\r", x_off);
	//printf("Y offset: %d\n\r", y_off);
	//printf("Calibrated X position: %d\n\r", pos.x-x_off);
	//printf("Calibrated Y position: %d\n\r", pos.y-y_off);

	//_delay_ms(3000);
	//printf("JOYSTICK CALIBRATED!\n\r");
}

void Joy_Init() {

	// Calibrate the Joystick.
	Joy_Cal();
	//printf("Joystick Central Position: %u, %u \n\r", central_pos.x, central_pos.y);

	// Initialize joystick button as input: PORT B - pin 3.
	DDRB &= ~(1 << PINB3);
	//clear_bit(DDRB, PINB3);
	
	// Activate pull-up resistor for joystick button.
	PORTB |= (1 << PB3);
	//set_bit(PORTB, PB3);
}

int Joy_Button() {
	if( !(PINB & (1 << PB3)) ) {
		return 1;
	}
	return 0;
}

// Get Joystick position.
Joy_position Joy_getPos()
{
	Joy_position curr_pos = Joy_Read();
	Joy_position cal_pos;

	//printf("curr X: %d\n\r", curr_pos.x);
	//printf("curr Y: %d\n\r", curr_pos.y);

	//cal_pos.x = abs(curr_pos.x) - x_off;
	//cal_pos.y = abs(curr_pos.y) - y_off;

	
	//printf("CAL X: %d\n\r", cal_pos.x);
	//printf("CAL Y: %d\n\r", cal_pos.y);
	/*
	printf("X offset aa: %d\n\r", x_off);
	printf("Y offset aa: %d\n\r", y_off);
	printf("MAX X: %d\n\r", max_pos_x);
	printf("MAX Y: %d\n\r", max_pos_y);
	*/

	
	float perc_pos_x;
	float perc_pos_y;

	
	// Compute percentage and trim pos x.
	perc_pos_x = (curr_pos.x/(float)max_pos_x)*100;

	// Compute and trim pos y.
	perc_pos_y = (curr_pos.y/(float)max_pos_y)*100;

	//printf("Joystick Position in percentage: x=%.2f, y=%.2f \n\r", perc_pos_x, perc_pos_y);
	
	
	return curr_pos;
}

// Get Joystick direction in human readable form.
Joy_direction Joy_getDir() {

	Joy_position curr_pos = Joy_getPos();
	int dir;
	
	if (curr_pos.x < 250 && curr_pos.y < 250 && curr_pos.x > 5 && curr_pos.y > 5) {
		dir=CENTRAL;
		// OLED_printf("CENTRAL\n\r");
		// _delay_ms(750);
		// OLED_reset();
	}
	else if (curr_pos.x > curr_pos.y){
		if (curr_pos.x > 250) {
			dir=EAST;
			// OLED_printf("EAST\n\r");
			// _delay_ms(750);
			// OLED_reset();
		}
	}
	
	if (curr_pos.x < 5) {
			dir=WEST;
			// OLED_printf("WEST\n\r");
			// delay_ms(750);
			// OLED_reset();
		}

	if (curr_pos.y > 250) {
			dir=NORTH;
			// OLED_printf("NORTH\n\r");
			// _delay_ms(750);
			// OLED_reset();
		}
	
	if (curr_pos.y < 5) {
			dir=SOUTH;
			// OLED_printf("SOUTH\n\r");
			// _delay_ms(750);
			// OLED_reset();
		}

	return dir;
}
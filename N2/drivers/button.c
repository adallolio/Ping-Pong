// Joystic button handling in Node 2

#include "../misc/macros.h"
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void button_init(void) {
	// Initialize joystick button as input: PORT L - pin 0.
	DDRL &= ~(1 << PL0);

	DDRL |= (1<<PL2);
}

void button_read(void) {
	if(!(PINL & (1 << PL0))) {
		PORTL &= ~(1 << PL2);
	} else {
		PORTL |= (1<<PL2);
	}
}
// IR.c - Richard McCrae-Lauba
//  IR no break > 400, break < 60


#include "ir.h"
#include "adc.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <avr/interrupt.h>

uint8_t printDelay = 0;
uint16_t IR_value;

int IR_check(){
	_delay_ms(500);
	IR_value = ADC_channelRead(IR); // Read current IR value
	//Check if the been is has been broken.
	if (IR_value < 100) {
		//lives--;
		//printf("Ouch! -1 life, you still have %d lives remaining!\n\r", lives);
		//_delay_ms(100);
		//return lives;

		// Beam broken.
		return 1;
	} else {
		//score++;
		//printf("Still %d lives!\n\r",lives);
		//return lives;

		//Beam not broken.
		return 0;
		}
}

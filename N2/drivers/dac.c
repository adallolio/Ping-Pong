// DAC.c - Richard McCrae-Lauba

#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"
#include "dac.h"
#include "TWI_Master.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void DAC_init(void){
	TWI_Master_Initialise();
}

void DAC_send(uint8_t data){
	uint8_t address = 0x50; //0b01010000; // Set slave address, add these to head file with descriptive names
	uint8_t command = 0x00; //0b0; // Setting DAC0 output
	
	uint8_t message[3];
	message[0] = address;
	message[1] = command;
	message[2] = data;

	_delay_ms(50);

	TWI_Start_Transceiver_With_Data(message, 3);
}
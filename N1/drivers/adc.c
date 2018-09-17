// Alberto Dallolio - ADC

#include "../misc/memory_mapping.h"
#include "../misc/macros.h"
#include "adc.h"
//#include "../misc/bit_manipulation.h"
#include <avr/io.h>
#include <util/delay.h>

int ADC_Init(void) {
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);

	// Set interrupt pin as input.
	PORTE &= ~(1 << PE0);
	return 0;
}

uint8_t ADC_Read(char ch){
 	
 	// Start address
	volatile char *ext_adc = (char *) ADC_DATA_ADDRESS; 
	
	// Bitwise OR
	//if (ch > 3){
	//	return 0;
	//}
	
	//*ext_adc = 0x04 | ch; // OR
	switch (ch){
		case 'x':
			*ext_adc = 0b00000100;
			break;
		case 'y':
			*ext_adc = 0b00000101;
			break;
		case 'l':
			*ext_adc = 0b00000110;
			break;
		case 'r':
			*ext_adc = 0b00000111;
			break;
		}
	
	// When the read pin is low I can read the ADC output.
	loop_until_bit_is_clear(PORTE, PE0);
	_delay_us(200);

	//printf("Read values: %u \n\r", *ext_adc);
	
	//return ext_adc[0];
	return *ext_adc;

}
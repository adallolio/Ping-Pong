// Alberto Dallolio - ADC

#include "../misc/memory_mapping.h"
#include "../misc/macros.h"
//#include "../misc/bit_manipulation.h"
#include <avr/io.h>
#include <util/delay.h>

int ADC_init(void)
{
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	
	// Interrupt pin as input.
	DDRD &= ~(1 << PD3);
	return 0;
}


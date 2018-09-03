// Alberto Dallolio
// Code for the testing the latch: set-unset pins.

#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// Port A and E (contains PE1=ALE) are output.
	DDRA = 0xFF;
	DDRE = 0xFF;

	// Set PE1
	PORTE |= (1 <<PE1);
	
	while(1)
	{
		// Toggle A0-A7.
		PORTA |= (1 << PA0)|(1 << PA1)|(1 << PA2)|(1 << PA3)|(1 << PA4)|(1 << PA5)|(1 << PA6)|(1 << PA7);
		
		_delay_ms(1000);
		
		PORTA &= ~(1 << PA0);
		PORTA &= ~(1 << PA1);
		PORTA &= ~(1 << PA2);
		PORTA &= ~(1 << PA3);
		PORTA &= ~(1 << PA4);
		PORTA &= ~(1 << PA5);
		PORTA &= ~(1 << PA6);
		PORTA &= ~(1 << PA7);
		
		_delay_ms(1000);
		
		
	}
}
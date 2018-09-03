// Exercise 1 - test
// Alberto Dallolio

//#define F_CPU 4915200 //49152MHz
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// Port A are outputs
	DDRA = 1;
	
    while(1)
    {
		// PIN A 0 is set to 1
		PORTA |= (1 << PA0);
		
		_delay_ms(1000);
		
		PORTA &= ~(1 << PA0);
		
		_delay_ms(1000);
		
    }
}

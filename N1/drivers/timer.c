// TIMER - Alberto Dallolio

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int time_curr = 0;

ISR(TIMER1_COMPA_vect){
	time_curr = time_curr + 1;
}

void TIMER_init(){
	//CTC mode
	TCCR1B |= (1 << WGM12);
	
	// Prescaler = 256
	TCCR1B |= (1 << CS12);
	
	// Set output compare value
	OCR1A = 0x4B00;		// 19200 - corresponds to match every second: 1Hz = 4915200/256/(OCR1A-1)
}

void TIMER_start(){
	TIMSK |= (1 << OCIE1A);
	/* when this bit is written to one, and the I-flag in the Status Register is set (interrupts globally
	   enabled), the Timer/Counter1 Output Compare A Match interrupt is enabled. The corresponding
	   Interrupt Vector (See “Interrupts” on page 57.) is executed when the OCF1A Flag, located in
	   TIFR, is set.
	*/
	time_curr = 0;
}

int TIMER_stop(){
	TIMSK &= ~(1 << OCIE1A);
	return time_curr;
}
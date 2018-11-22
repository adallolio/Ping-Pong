// ADC.c N2 - Richard McCrae-Lauba

#include "adc.h"

void ADC_init(void){
	clear_bit(DDRF, PF0); // Channel 0 of ADC = IR sensor, A0 is PF0
	clear_bit(DDRF, PF1); // Channel 1 for SLIDER1 position, = PF1 = A1 = input
	clear_bit(DDRF, PF3); // Channel 2 for SLIDER2 position, = PF2 = A2 = input
	set_bit(ADCSRA, ADEN); // ADC Control and Status Register A - Enable ADC, next coversion takes 25 adc clock cycles
	
	// Set prescaler to 128
	set_bit(ADCSRA, ADPS0);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS2);
	// Set voltage reference to 2.56V
	set_bit(ADMUX, REFS1);
	set_bit(ADMUX, REFS0);
}

uint16_t ADC_read(void){
/*
	set_bit(ADCSRA, ADSC); // Start single conversion
	loop_until_bit_is_set(ADCSRA, ADIF); // Wait for interrupt flag to be set
	uint8_t data_low = ADCL; // Low data bits of converted data
	uint16_t data_high = ADCH; // High data bits of converted data
	uint16_t data = (data_high << 8)|(data_low); // Combining low and high as 16 bits
	printf("ADC READING: %d \n\r", data);
	return data;
*/

	uint16_t data = 0;
	set_bit(ADCSRA, ADSC); // Start single conversion
	loop_until_bit_is_set(ADCSRA, ADIF); // Wait for interrupt flag to be set
	uint8_t data_low = ADCL; // Low data bits of converted data
	uint8_t data_high = (ADCH << 8);
	data = data_high + data_low;
	printf("ADC READING: %d \n\r", data);
	return data;

}

uint16_t ADC_channelRead(ADC_ch ch){
	switch(ch){
		case(IR):
			clear_bit(ADMUX,MUX0);
			clear_bit(ADMUX,MUX1);
			return ADC_read();
		case(JOY_AX):
			clear_bit(ADMUX,MUX0);
			set_bit(ADMUX,MUX1); 
			return ADC_read();
		case(JOY_SL_R):
			set_bit(ADMUX,MUX0);
			set_bit(ADMUX,MUX1); 
			return ADC_read();
		default:
			return 0;
	}
}
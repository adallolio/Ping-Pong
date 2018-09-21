// Alberto Dallolio - Main N1

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
//#include "drivers/sram.c"
#include "adc.h"
#include "joystick.h"
#include "../misc/memory_mapping.h"
//#include "misc/bit_manipulation.h"
#include "../misc/macros.h"

int main(void)
{	
	// Set and enable UART.
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);
	fdevopen(UART_send, UART_receive);
	
	uint8_t x;
	uint8_t y;
	ADC_Init();
	
	while(1){
		//_delay_ms(10000);
		//Joy_getDir();
		x = ADC_Read('x');
		printf("X position: %d\n\r", x);
		y = ADC_Read('y');
		printf("Y position: %d\n\r", y);
		_delay_ms(5000);
	}

		//uint8_t pos_x = ADC_Read('x');
		//printf("X POSITION: %u \n\r", pos_x);
		//_delay_ms(1);
		//uint8_t pos_y = ADC_Read('y');
		//printf("Y POSITION: %u \n\r", pos_y);
		//_delay_ms(1);
		//uint8_t left = ADC_Read('l');
		//printf("LEFT SLIDER POSITION: %u \n\r", left);
		//_delay_ms(1);
		//uint8_t right = ADC_Read('r');
		//printf("RIGHT SLIDER POSITION: %u \n\r", right);

	
	return 0;
}
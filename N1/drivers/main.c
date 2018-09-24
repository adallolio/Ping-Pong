// Alberto Dallolio - Main N1

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
//#include "drivers/sram.c"
#include "adc.h"
#include "joystick.h"
#include "touch.h"
#include "../misc/memory_mapping.h"
//#include "misc/bit_manipulation.h"
#include "../misc/macros.h"

int main(void)
{	
	// Set and enable UART.
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);
	fdevopen(UART_send, UART_receive);
	
	// JOYSTICK
	//uint8_t x;
	//uint8_t y;
	int btn;

	// TOUCH
	//uint8_t l;
	//uint8_t r;
	int touch_btn;

	_delay_ms(5000);

	ADC_Init();
	Joy_Init();
	//TOUCH_Init();

	//_delay_ms(3000);

	
	while(1){
		//_delay_ms(10000);
		
		// TEST JOYSTICK
		//x = ADC_Read('x');
		//printf("X position: %d\n\r", x);
		//y = ADC_Read('y');
		//printf("Y position: %d\n\r", y);

		Joy_getDir();
		/*
		btn = Joy_Button();
		if(btn==0){
			printf("Joystick Button Pressed!\n\r");
		}
		*/

		
		
		// TEST TOUCH
		//TOUCH_getPos();
		/*
		touch_btn = TOUCH_Button();
		if(touch_btn==1){
			printf("Touch Button Pressed!\n\r");
		}
		*/
		
		
		//l = ADC_Read('l');
		//printf("L: %d\n\r", l);
		//r = ADC_Read('r');
		//printf("R: %d\n\r", r);
		
		//_delay_ms(2000);
	}

	
	return 0;
}
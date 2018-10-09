// Alberto Dallolio - Main N1

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "adc.h"
#include "joystick.h"
#include "touch.h"
//#include "font_norm.h"
#include "oled.h"
//#include "menu.h"
//#include "spi.h"
#include "../misc/memory_mapping.h"
#include "../misc/macros.h"
//#include "misc/bit_manipulation.h"

int main(void) {
	// Set and enable UART.
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);
	fdevopen(UART_send, UART_receive);
	
	// JOYSTICK
	//uint8_t x;
	//uint8_t y;
	//int btn;

	// TOUCH
	//uint8_t l;
	//uint8_t r;
	//int touch_btn;

	//_delay_ms(5000);
	
	//DDRA = 0xFF;
	
	ADC_Init();
	//Joy_Init();
	//TOUCH_Init();
	OLED_init();
	MENU_init();

	char a[] = 'main test';
	OLED_print_char(a);

	
	while(1){
		
		//_delay_ms(2000);
 		//OLED_wrCmd(0xaf); // display on
 		//_delay_ms(2000);
 		//OLED_wrCmd(0xae);

		//_delay_ms(10000);
		
		// TEST JOYSTICK
		//x = ADC_Read('x');
		//printf("X position: %d\n\r", x);
		//y = ADC_Read('y');
		//printf("Y position: %d\n\r", y);

		//Joy_getDir();
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



		// OLED TESTING

		//OLED_printf();
		//OLED_print_arrow();
		//OLED_reset();
		//OLED_drPix(20,100);

		/*
		_delay_ms(2000);
		OLED_wrCmd(0xae);
		_delay_ms(2000);
		OLED_wrCmd(0xaf);
		*/

		/*
		for (int i = 0; i < 5; i++){
			OLED_wrData(pgm_read_byte(&font5[2][i]));
		}
		*/

		//OLED_wrData(0xFF);

		//_delay_ms(2000);

		//OLED_invert();
		
		
		//OLED_print_arrow(10, 100);

		
		// TEST SPI
		//spi_tranceive(a);

	}


	
	return 0;
}

// red is CS to the gal 
// orange is DATA/COMM to the 

// Alberto Dallolio - Main N1

#include "../misc/bit_manipulation.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include <avr/interrupt.h>
#include "adc.h"
#include "joystick.h"
#include "touch.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "mcp2515.h"
#include "can.h"
#include "../misc/memory_mapping.h"
#include "../misc/macros.h"

//#include "font_norm.h"


int main(void) {

	//------------UART------------//
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);				// Set clock speed
	fdevopen(UART_send, UART_receive);  // Connect printf

	//------------INTERRUPTS------------//
	//DDRD &= ~(1 << PIND2);
	//GICR |= (1<<INT0);
	//MCUCR |= (1<<ISC01);
	//MCUCR &= ~(1<<ISC00);
	sei();

	//------------ADC------------//
	ADC_Init();
	
	
	//------------JOYSTICK TEST------------//
	Joy_Init();
	// uint8_t x;
	// uint8_t y;
	// int btn;

	//------------TOUCH TEST------------//
	TOUCH_Init();
	//uint8_t l;
	//uint8_t r;
	//int touch_btn;
	//_delay_ms(5000);
	//DDRA = 0xFF;
	
	//------------OLED and MENU------------//
	OLED_Init();
	//MENU_Init();
	

	//------------CAN TEST------------//
	
	CAN_Init();
	CAN_message send;
	CAN_message rec;

	
	send.id=0x01;
	send.length=3;
	send.data[0]=4;
	send.data[1]=5;
	send.data[2]=6;

	//------------SPI TEST------------//
	// char SPI_MOSI = 'a';
	// uint8_t SPI_MISO;
	
	while(1){
		//------------JOYSTICK OVER CAN TEST------------//
		CAN_msgSend(&send);
		printf("sent msg:%d\r\n", send.data[0]);
		printf("sent msg:%d\r\n", send.data[1]);
		printf("sent msg:%d\r\n", send.data[2]);
		_delay_ms(1000);
		
		//------------JOYSTICK TEST------------//
		// x = ADC_Read('x');
		// printf("X position: %d\n\r", x);
		// y = ADC_Read('y');
		// printf("Y position: %d\n\r", y);

		//Joy_getDir();
		
		// int btn = Joy_Button();
		// if(btn==0){
		// 	printf("Joystick Button Pressed!\n\r");
		// }
		
		
		//------------TOUCH TEST------------//
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


		//------------OLED------------//
		//OLED_printf(can_msg_receive.data);
		//_delay_ms(2000);
		//OLED_reset();
		//_delay_ms(2000);

		//------------MENU------------//
		//MENU_nav();
		//MENU_select();
		
		
		//------------SPI TEST------------//
		//SPI_MISO = SPI_Transcieve(SPI_MOSI);
		//_delay_ms(2);
	}


	
	return 0;
}
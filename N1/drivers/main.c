// Alberto Dallolio - Main N1

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "uart.h"
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
//#include "misc/bit_manipulation.h"
//#include "font_norm.h"

volatile char data;
// CAN LOOPBACK TEST
void func(CAN_message_t msg_send);

int main(void) {
	// Set and enable UART.
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);
	fdevopen(UART_send, UART_receive);
	
	// JOYSTICK
	// uint8_t x;
	// uint8_t y;
	// int btn;

	// TOUCH
	//uint8_t l;
	//uint8_t r;
	//int touch_btn;

	//_delay_ms(5000);
	
	//DDRA = 0xFF;
	
	ADC_Init();
	Joy_Init();
	TOUCH_Init();
	OLED_Init();
	MENU_Init();
	
	// CAN LOOPBACK TEST
	
	CAN_Init();
	mcp2515_loopback();
	CAN_message_t can_msg_send;
	CAN_message_t can_msg_receive;

	can_msg_send.id=10;
	can_msg_send.length=3;
	can_msg_send.data[1]=5;

	//SPI test
	// char SPI_MOSI = 'a';
	// uint8_t SPI_MISO;
	
	while(1){
		// CAN LOOPBACK TEST
		CAN_message_send(&can_msg_send);
		can_msg_receive = CAN_data_receive();
		_delay_ms(1000);
		
		// TEST MENU
		//MENU_nav();
		//MENU_select();
		
		// TEST JOYSTICK
		// x = ADC_Read('x');
		// printf("X position: %d\n\r", x);
		// y = ADC_Read('y');
		// printf("Y position: %d\n\r", y);

		//Joy_getDir();
		
		// int btn = Joy_Button();
		// if(btn==0){
		// 	printf("Joystick Button Pressed!\n\r");
		// }
		
		
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

		// TEST SPI
		//SPI_MISO = SPI_Transcieve(SPI_MOSI);
		//_delay_ms(2);
	}


	
	return 0;
}
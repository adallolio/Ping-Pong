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
#include "can_driver.h"
#include "../misc/memory_mapping.h"
#include "../misc/macros.h"

//#include "font_norm.h"


int main(void) {

	//cli();
	//------------UART------------//
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);				// Set clock speed
	fdevopen(UART_send, UART_receive);  // Connect printf

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
	MENU_Init();
	
	//------------CAN TEST------------//
	CAN_init();

	//------------SPI TEST------------//
	// char SPI_MOSI = 'a';
	// uint8_t SPI_MISO;
	
	//------------INTERRUPTS------------//
	//DDRD &= ~(1 << PIND2);
	//sei();

	can_msg_t send;
	can_msg_t rec;
	can_msg_t joystick;

	send.id=1;
	send.length=1;
	send.data[0]=4;

	//joystick.id=JOY_POS;
	//joystick.length=2;

	
	while(1){

		CAN_send(&send);
		
		//_delay_ms(10);
		//if (CAN_int_vect()){
		//	CAN_read(&rec);
		//}
		
		_delay_ms(2000);
		//CAN_receive(&rec);
		//CAN_print(&rec);
		
		//MENU_nav();
		//MENU_select();
		
		// CAN register testing
/*		printf("CANINTF: %d",MCP_CANINTF);
		printf("\n\r");
		printf("CANSTAT: %d",MCP_CANSTAT);
		printf("\n\r");
		printf("EFLG: %d",MCP_EFLG);
		printf("\n\r");
*/
		// Joystick over CAN
/*		joystick.data[0] = Joy_Read.x;
		joystick.data[1] = Joy_Read.y;
		_delay_ms(10);
		CAN_message_send(joystick);
*/
	}

	return 0;
}

/*
Sleep mode 
Bit 5 – SE: Sleep Enable, MCUCR
The SE bit must be written to logic one to make the MCU enter the sleep mode when the SLEEP
instruction is executed. To avoid the MCU entering the sleep mode unless it is the programmer’s
purpose, it is recommended to write the Sleep Enable (SE) bit to one just before the execution of
the SLEEP instruction and to clear it immediately after waking up.
*/
// Alberto Dallolio - Main N1

#include "../misc/bit_manipulation.h"
#include "../misc/macros.h"
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"
#include "can.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

//#include "font_norm.h"


int main(void) {
	cli();

	//------------UART------------//
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);				// Set clock speed
	fdevopen(UART_send, UART_receive);  // Connect printf

	//------------ADC------------//
	//ADC_Init();
	

	//------------CAN TEST------------//
	
	CAN_Init();
	//mcp2515_Init();
	//SPI_Init();
	CAN_message send;
	CAN_message rec;

	send.id=0x01;
	send.length=1;
	send.data[0]=4;


	//DDRD &= ~(1<<PIND0);
	//GICR |= (1<<INT0);
	//MCUCR |= (0<<ISC01)|(0<<ISC00);


	//------------SPI TEST------------//
	// char SPI_MOSI = 'a';
	// uint8_t SPI_MISO;

	sei();
	
	while(1){
		
		
		CAN_msgSend(&send);
		printf("sent:%d\r\n", send.data[0]);
		rec = CAN_msgRec();
		printf("received:%d\r\n", rec.data[0]);
		_delay_ms(2000);
		
		
		/*
		mcp2515_write(MCP_CANCTRL, 7);
		_delay_ms(10);
		uint8_t a = mcp2515_read(MCP_CANCTRL);
		printf("MCP_CANCTRL: %d\r\n",a);
		_delay_ms(2000);
		*/
		

		//------------CAN TEST------------//
		// CAN_message_send(&can_msg_send);
		// can_msg_receive = CAN_data_receive();
		
		
		//------------SPI TEST------------//
		//SPI_MISO = SPI_Transcieve(SPI_MOSI);
		//_delay_ms(2);
	}


	
	return 0;
}
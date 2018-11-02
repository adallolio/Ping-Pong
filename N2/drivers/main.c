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
	send.data[0]=5;


	//DDRD &= ~(1<<PIND0);
	//GICR |= (1<<INT0);
	//MCUCR |= (0<<ISC01)|(0<<ISC00);


	//------------SPI TEST------------//
	// char SPI_MOSI = 'a';
	// uint8_t SPI_MISO;

	//sei();
	
	while(1){
		
		
		CAN_msgSend(&send);
		printf("sent to N1:%d\r\n", send.data[0]);
		_delay_ms(1000);
		
		/*
		rec = CAN_msgRec();
		_delay_ms(10);
		printf("received by N1:%d\r\n", rec.data[0]);
		_delay_ms(1000);
		*/

		/*
		uint8_t can_stat_reg = mcp2515_read(MCP_CANSTAT);
		_delay_ms(10);
		printf("CAN_STAT: %x\r\n", can_stat_reg);
		_delay_ms(1000);
		*/
		
		/*
		uint8_t can_stat_reg = mcp2515_read_status();
		_delay_ms(10);
		printf("CAN_STAT: %d\r\n", can_stat_reg);
		_delay_ms(1000);
		*/
		
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
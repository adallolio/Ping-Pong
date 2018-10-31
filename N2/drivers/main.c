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

	//------------UART------------//
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);				// Set clock speed
	fdevopen(UART_send, UART_receive);  // Connect printf

	sei();

	//------------ADC------------//
	//ADC_Init();
	

	//------------CAN TEST------------//
	
	CAN_Init();
	CAN_message send;
	CAN_message rec;

	//send.id=0x01;
	//send.length=1;
	//send.data[0]=4;

	//------------SPI TEST------------//
	// char SPI_MOSI = 'a';
	// uint8_t SPI_MISO;
	
	while(1){
		
		//CAN_msgSend(&send);
		//printf("sent:%d\r\n", send.data[0]);
		rec = CAN_msgRec();
		printf("received:%d\r\n", rec.data[0]);
		_delay_ms(2000);
		
		//------------CAN TEST------------//
		// CAN_message_send(&can_msg_send);
		// can_msg_receive = CAN_data_receive();
		
		
		//------------SPI TEST------------//
		//SPI_MISO = SPI_Transcieve(SPI_MOSI);
		//_delay_ms(2);
	}


	
	return 0;
}
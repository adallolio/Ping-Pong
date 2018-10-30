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


	//------------INTERRUPTS------------//
	sei();
	// External Interrupt Control Registers – EICRA (INT3:0). When the external
	// interrupt is enabled and is configured as level triggered, the interrupt 
	// will trigger as long as the pin is held low.
	
	// ISCn1, ISCn0 = 0,0: The low level of INTn generates an interrupt request
	//EICRA |= (0 << ISC21) | (0 << ISC20);
	// Clear INT2 flag prior to initialization
	//EIFR |= (0 << INTF2);
	// Enable external interrupts of INT2, PD2
	//EIMSK |= (1 << INT2);


	//------------ADC------------//
	//ADC_Init();
	

	//------------CAN TEST------------//
	
	CAN_Init();
	CAN_message rec;
	CAN_message rec_Prev;
	rec_Prev.id=0x00;
	rec_Prev.length=0;

	//------------SPI TEST------------//
	// char SPI_MOSI = 'a';
	// uint8_t SPI_MISO;
	

	while(1){
		//------------CAN TEST------------//
		rec = CAN_msgRec();
		//if(rec != rec_Prev){
			// printf("received msg:%d\r\n", rec.data[0]);
			// printf("received msg:%d\r\n", rec.data[1]);
			// printf("received msg:%d\r\n", rec.data[2]);
		_delay_ms(250);
		//	rec_Prev = rec;
		//}
	}
	
	return 0;
}
// Alberto Dallolio

#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart_test.h"

void main(void){

	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);
    unsigned char b;

	while(1){
		b = UART_receive();
		
		fdevopen(UART_send, UART_receive);
		printf("\r\nHello World\r\n");

		UART_send(b+1);
		
		_delay_ms(100);
	}
}
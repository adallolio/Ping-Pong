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

	while(1){
		//message = UART_receive();
		//printf("%c\n", message);
		
		UART_send('a');
		//printf("Is it transmitted?!?!?!?!?!");
		
		_delay_ms(100);

		//stdout = &uart_io;
		//stdin = &uart_io;
	}
}
// TEST DRIVER COMM.
// Alberto Dallolio

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "bit_manipulation.h"

#define BAUD_RATE 9600

//static FILE uart_io = FDEV_SETUP_STREAM(USART_trans, USART_rec, _FDEV_SETUP_WRITE);
//#define uart_io = FDEV_SETUP_STREAM(USART_trans, USART_rec, _FDEV_SETUP_RW);


void UART_Init(unsigned long clock){

	unsigned long baud = BAUD_RATE;
	unsigned char ubrr = (clock/(16*baud))-1; //31;
	/* Set baud rate */
	UBRR0H = (unsigned char) ubrr>>8;
	UBRR0L = (unsigned char) ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	//UCSR0C |= (1<<URSEL0)|(1<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);

	//fdevopen(&USART_trans, &USART_rec);
	//fdevopen(int(*)(char, FILE *) put, int(*)(FILE *) get);
}

// Function for reading received data.
unsigned char UART_receive(void){
	/* Wait for data to be received */
	//while (!(UCSR0A & (1<<RXC0)));
	loop_until_bit_is_set(UCSR0A,RXC0);
	/* Get and return received data from buffer */
	return UDR0;
}

// Function to read transmitted data.
void UART_send(unsigned char data){
	/* Wait for empty transmit buffer */
	//while (!( UCSR0A & (1<<UDRE0)));
	
	loop_until_bit_is_set(UCSR0A,UDRE0);
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

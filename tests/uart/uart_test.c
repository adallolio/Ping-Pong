// TEST DRIVER COMM.
// Alberto Dallolio

#include "uart_test.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>



void main(void){
	unsigned char message;

	USART_Init ( MYUBRR );

	while(1){
		message = UART_rec();
		printf("%c\n", msg);
		
		//UART_trans('aooooooooooooooo');
		//printf("Is it transmitted?!?!?!?!?!");
		
		_delay_ms(1000);
	}
}




void USART_Init( unsigned int ubrr ){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);

	fdevopen(&UART_trans, &UART_rec);
}

// Function for reading received data.
unsigned char UART_rec(void){
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

// Function to read transmitted data.
void UART_trans(unsigned char data){
	/* Wait for empty transmit buffer */
	while (!( UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
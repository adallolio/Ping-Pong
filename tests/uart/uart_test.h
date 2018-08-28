// TEST UART COMM
// Alberto Dallolio

// Check if correct.

#ifndef UART_H
#define UART_H

// Do we have to put cpu speed as well?
//#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void UART_Init(unsigned int ubrr);
void UART_trans (unsigned char data);
unsigned char UART_rec (void);

#endif
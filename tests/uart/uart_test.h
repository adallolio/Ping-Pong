// TEST UART COMM
// Alberto Dallolio

// Check if correct.

#ifndef UART_H
#define UART_H

#define F_CPU 4915200 // Informs the compiler: how many steps in one second.
#define FOSC 4915200  // 49152MHz
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1  //  (F_CPU / (16 * BAUD)) - 1 = (4915200/(16*9600)) - 1

void USART_Init(unsigned int ubrr);
void USART_trans (unsigned char data);
unsigned char USART_rec (void);

#endif
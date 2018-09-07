// TEST UART COMM
// Alberto Dallolio

// Check if correct.

#ifndef USART_H
#define USART_H

#define F_CPU 4915200 // Informs the compiler: how many steps in one second.
#define FOSC 4915200  // 49152MHz
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1  //  (F_CPU / (16 * BAUD)) - 1 = (4915200/(16*9600)) - 1

void USART_Init(unsigned int ubrr);
int USART_trans (unsigned char data);
int USART_rec (void);

#endif

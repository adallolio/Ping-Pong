// TEST UART COMM
// Alberto Dallolio

#ifndef UART_TEST_H
#define UART_TEST_H

void UART_Init(unsigned long clock);
int UART_send(unsigned char data);
int UART_receive(void);


//#define F_CPU 4915200UL // Informs the compiler: how many steps in one second.
//#define FOSC 4915200  // 49152MHz
//#define BAUD 9600
//#define MYUBRR (F_CPU / (16 * BAUD)) - 1 //FOSC/16/BAUD-1  //  (F_CPU / (16 * BAUD)) - 1 = (4915200/(16*9600)) - 1

#endif
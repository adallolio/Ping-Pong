// TEST UART COMM
// Alberto Dallolio

#ifndef UART_H
#define UART_H

void UART_Init(unsigned long clock);
void UART_send(unsigned char data);
unsigned char UART_receive();

#endif

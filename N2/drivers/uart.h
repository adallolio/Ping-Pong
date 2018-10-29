// Richard McCrae-Lauba - Uart Communication - Node 2

#ifndef UART_H_
#define UART_H_

void UART_Init(unsigned long clock);
unsigned char UART_receive();
void UART_send(unsigned char data);

#endif
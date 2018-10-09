// Alberto Dallolio - Uart Communication

#ifndef UART_H_
#define UART_H_

void UART_Init(unsigned long clock);
void UART_send(unsigned char data);
unsigned char UART_receive();

#endif
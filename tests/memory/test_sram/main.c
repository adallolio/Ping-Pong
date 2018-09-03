// Main

#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "sram.h"

int main(void)
{
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);				 // May this be needed? I guess yes!
	SRAM_Init();
	SRAM_Test();
	
	return 0;
}
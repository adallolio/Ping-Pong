// Alberto Dallolio - Main N1

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "drivers/uart.h"
#include "drivers/sram.c"
#include "misc/memory_mapping.h"
#include "misc/bit_manipulation.h"
#include "misc/macros.h"

int main(void)
{
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);
	fdevopen(UART_send, UART_receive);
	SRAM_Init();
	SRAM_Test();
	
	return 0;
}
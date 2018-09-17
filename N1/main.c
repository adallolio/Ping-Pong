// Alberto Dallolio - Main N1

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "drivers/uart.h"
//#include "drivers/sram.c"
#include "drivers/adc.h"
#include "misc/memory_mapping.h"
//#include "misc/bit_manipulation.h"
#include "misc/macros.h"

#define CH_Y_POS 0
#define CH_X_POS 1

int main(void)
{
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);
	fdevopen(UART_send, UART_receive);
	//SRAM_Init();
	//SRAM_Test();
	ADC_Init();
	uint8_t pos_x = ADC_Read(CH_Y_POS);
	_delay_ms(1);
	uint8_t pos_y = ADC_Read(CH_X_POS);
	
	return 0;
}
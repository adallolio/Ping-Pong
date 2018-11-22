// ADC.h N2 - Richard McCrae-Lauba


#ifndef ADC_H_
#define ADC_H_

#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

typedef enum ADC_channel {
	IR = 0,
	JOY_AX = 1,
	JOY_SL_R = 2
} ADC_ch;

void ADC_init(void);
uint16_t ADC_read(void);
uint16_t ADC_channelRead(ADC_ch ch);


#endif /* ADC_H_ */
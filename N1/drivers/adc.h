// Alberto Dallolio - ADC

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

int ADC_Init(void);
uint8_t ADC_Read(char ch);

#endif /* ADC_H_ */
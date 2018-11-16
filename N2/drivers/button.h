// Joystic button handling in Node 2

#ifndef BUTTON_H_
#define BUTTON_H_

#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void button_init(void);
void button_read(void);

#endif /* BUTTON_H_ */
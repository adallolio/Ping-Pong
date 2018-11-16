// IR.h - Richard McCrae-Lauba

#ifndef IR_H_
#define IR_H_

#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


void IR_init();
int IR_inGame(int lives);


#endif /* IR_H_ */
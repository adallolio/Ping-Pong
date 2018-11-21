// Alberto Dallolio - Ready Joystick

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <avr/io.h>

typedef enum {
	CENTRAL = 0,
	WEST = 1,
	EAST = 2,
	NORTH = 3,
	SOUTH = 4
} Joy_direction;

typedef struct JOY_pos {
	uint8_t y;
	uint8_t x;
} Joy_position;


void Joy_Init();
void Joy_Cal();
int Joy_Button();
Joy_position Joy_Read();
Joy_position Joy_getPos();
Joy_direction Joy_getDir();


#endif /* JOYSTICK_H_ */
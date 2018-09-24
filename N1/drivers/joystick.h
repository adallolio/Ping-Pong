// Alberto Dallolio - Ready Joystick

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <avr/io.h>

typedef enum {
	CENTRAL = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
} Joy_direction;

typedef struct JOY_pos {
	int y;
	int x;
} Joy_position;


void Joy_Init();
void Joy_Cal();
int Joy_Button();
Joy_position Joy_Read();
Joy_position Joy_getPos();
Joy_direction Joy_getDir();


#endif /* JOYSTICK_H_ */
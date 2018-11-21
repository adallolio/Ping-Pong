// MOTOR.h - Richard McCrae-Lauba

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

typedef enum {WEST, EAST} motor_direction;

void MOTOR_init();
void MOTOR_setDir(motor_direction dir);
void MOTOR_setSpeed(uint8_t speed);
//void MOTOR_setSpeedPID(uint8_t speed);
int16_t MOTOR_rotRead(void);
int MOTOR_rotScaled(void);
void MOTOR_encoderReset();
void MOTOR_encoderTest(void);
void MOTOR_cal();


#endif /* MOTOR_H_ */
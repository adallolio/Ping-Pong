// MOTOR.h - Richard McCrae-Lauba

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

typedef enum {WEST, EAST} motor_direction;

void motor_init();
void motorDir(motor_direction direction);
void motorSpeed(uint8_t speed);
void motorSpeed_PID(uint8_t speed);
void motor_move(int16_t rot_diff, uint8_t power);
int16_t motorRotation_read(void);
void motorEncoder_reset();
void motorEncoder_test(void);


#endif /* MOTOR_H_ */
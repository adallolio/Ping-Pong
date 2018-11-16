// Servo.h - Richard McCrae-Lauba


#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

void servo_init(uint32_t cpu_speed);
void set_servo(uint8_t servo_dir);

#endif /* SERVO_H_ */
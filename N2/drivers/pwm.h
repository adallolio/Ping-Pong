// PWM.h - Richard McCrae-Lauba

#ifndef PWM_H_
#define PWM_H_

#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

static uint16_t pwm_timer_freq;

void PWM_init(float period, uint32_t cpu_speed);
void PWM_set_period(float period);
void PWM_pulse_set(float servo_pw);

#endif /* PWM_H_ */
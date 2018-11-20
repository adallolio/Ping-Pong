// PID.h - Richard McCrae-Lauba

#ifndef PID_H_
#define PID_H_

//Tuned PID gains
#define KP 1
#define KI 10
#define KD 0.01

#define dt 0.016

static int16_t rot_max;
static int16_t rot_min = 0;
static double integral = 0;
static int16_t prev_error = 0;

static volatile uint8_t timer_flag = 0;

void PID_init(void);
void PID_cal(void);
void PID(uint8_t pos_ref);
//ISR(TIMER2_OVF_vect);

#endif /* PID_H_ */
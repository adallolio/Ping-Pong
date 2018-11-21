// PID.h - Richard McCrae-Lauba

#ifndef PID_H_
#define PID_H_

//Tuned PID gains
#define KP 100
#define KI 10
#define KD 100

#define dt 1 // 0.1*10Hz

void PID_init(void);
void PID(int rot, uint8_t pos_ref);
int PID_ref(uint8_t ref);
//ISR(TIMER2_OVF_vect);

#endif /* PID_H_ */
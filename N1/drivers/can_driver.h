#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

typedef struct {
    volatile unsigned short int id;
    volatile unsigned char length;
    volatile uint8_t data[8];
} can_msg_t;

#define ATmega2560_ID	1
#define TOUCH_BUTTON_ID	2
#define SLIDERS_ID		3
#define JOYSTICK_ID		4

void CAN_error(void);
uint8_t CAN_int_vect(void);
void CAN_send(can_msg_t* msg);
void CAN_read(can_msg_t* msg_read);
void CAN_init(void);
void CAN_sendBunch(void);
void CAN_slidersMsg(void);
void CAN_joyMsg(void);
void CAN_butt(void);
int CAN_transmit_complete(void);

#endif
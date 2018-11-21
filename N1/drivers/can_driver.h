#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

typedef struct {
    volatile unsigned short int id;
    volatile unsigned char length;
    volatile uint8_t data[8];
    //int id;
	//uint8_t length;
	//int8_t data[8];
} can_msg_t;

#define ATmega2560_ID	1
#define TOUCH_BUTTON_ID	2
#define SLIDERS_ID		3
#define JOYSTICK_ID		4
#define GAME_SPEED_ID	5

// Message types
#define CAN_JOY_POS_X		0x00
#define CAN_JOY_BUTTON		0x01
#define CAN_SLIDER_POS_L  	0x02
#define CAN_SLIDER_POS_R	0x03
#define CAN_TOUCH_BUTTON	0x04
#define CAN_LIVES			0x05
#define CAN_SPEED			0x06

//#define CAN_NO_MESSAGE	0x0A	//10

void CAN_error(void);
uint8_t CAN_transmit_complete(void);
uint8_t CAN_int_vect(void);
void CAN_send(can_msg_t* msg);
void CAN_read(can_msg_t* msg_read);
void CAN_init(void);
void CAN_sendBunch(void);
void CAN_slidersMsg(void);
void CAN_joyMsg(void);
void CAN_butt(void);

#endif
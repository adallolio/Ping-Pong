#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

typedef struct {
    volatile int id;
    volatile unsigned char length;
    volatile uint8_t data[8];
    //int id;				// 5 bytes for standard identifier
	//uint8_t length;		// Number of data bytes
	//int8_t data[8];
} can_msg_t;

#define ATmega2560_ID	1
#define TOUCH_BUTTON_ID	2
#define SLIDERS_ID		3
#define JOYSTICK_ID		4

// Message types
#define CAN_JOY_POS_X		0x00
#define CAN_JOY_BUTTON		0x01
#define CAN_SLIDER_POS_L  	0x02
#define CAN_SLIDER_POS_R	0x03
#define CAN_TOUCH_BUTTON	0x04
#define CAN_LIVES			0x05

void CAN_error();
uint8_t CAN_transmit_complete();
uint8_t CAN_int_vect();
void CAN_send(can_msg_t* msg);
void CAN_sendIR(int ir);
void CAN_read(can_msg_t* msg_read);
void CAN_init(void);

#endif
#ifndef CAN_H_
#define CAN_H_

#include <avr/io.h>

typedef struct {
	unsigned int id;
	uint8_t length;		// max 8
	uint8_t data[8];
	} CAN_message;
	
enum interrupt_flags {no_flag, RX0, RX1};

#define ATmega2560_ID	1
#define TOUCH_BUTTON_ID	2
#define SLIDER_ID		3
#define JOYSTICK_ID		4
#define GAME_SPEED_ID	5

// Message types
#define CAN_JOY_POS_X		0x00
#define CAN_JOY_BUTTON		0x01
#define CAN_SLIDER_POS_L	0x02
#define CAN_SLIDER_POS_R	0x03
#define CAN_TOUCH_BUTTON	0x04
#define CAN_LIVES			0x05
#define CAN_SPEED			0x06

#define CAN_NO_MESSAGE		0x0A	//10


void CAN_Init(void);
void CAN_msgSend(CAN_message *message);
CAN_message CAN_msgRec();
//void CAN_handle_interrupt(can_msg *msg);

#endif /* CAN_H_ */
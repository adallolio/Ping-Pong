#ifndef CAN_H_
#define CAN_H_

#include <avr/io.h>

typedef struct {
	unsigned int id;
	uint8_t length;		// max 8
	uint8_t data[1];
	} CAN_message;
	
enum interrupt_flags {no_flag, RX0, RX1};

#define ATmega2560_ID	1
#define TOUCH_BUTTON_ID	2
#define SLIDER_ID		3
#define JOYSTICK_ID		4

// Message types
#define CAN_JOY_POS_X		0x00
#define CAN_JOY_BUTTON		0x01
#define CAN_SLIDER_POS_L	0x02
#define CAN_SLIDER_POS_R	0x03
#define CAN_TOUCH_BUTTON	0x04
#define CAN_LIVES			0x05

void CAN_Init();
void CAN_msgSend(CAN_message *message);
CAN_message CAN_msgRec();

#endif /* CAN_H_ */



















/*


//CAN.h -- N2
//Richard McCrae-Lauba

#ifndef CAN_H_
#define CAN_H_


typedef struct CAN_message{
	int id;				// 5 bytes for standard identifier
	uint8_t length;		// Number of data bytes
	uint8_t data[8];
} CAN_message;

// typedef enum tag_CAN_msg_id{
// 	PONG_START = 0,
// 	PONG_STOP = 1,
// 	PONG_INSTR = 2
// }CAN_msg_id;

static volatile uint8_t CAN_RX_flag = 0;

void CAN_Init();
int CAN_message_send(CAN_message* msg);
uint8_t CAN_receive(CAN_message* msg);
void CAN_print(CAN_message* msg);
int CAN_error(void);
int CAN_transmit_complete(void);
ISR(INT2_vect);


#endif

*/
//CAN.h
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
uint8_t CAN_message_send(CAN_message* msg);
CAN_message CAN_receive(void);
void CAN_print(CAN_message* msg);
uint8_t CAN_error(void);
uint8_t CAN_transmit_complete(void);
ISR(INT2_vect);


#endif /* CAN_H_ */
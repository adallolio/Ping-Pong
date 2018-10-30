// CAN.h
// Richard McCrae-Lauba

#ifndef CAN_H_
#define CAN_H_

//volatile uint8_t rx_flag;
enum interrupt_flags {no_flag, RX0, RX1};

typedef struct {
	int id;				// 5 bytes for standard identifier
	uint8_t length;		// Number of data bytes
	int8_t data[8];
} CAN_message;

void CAN_Init(void);
void CAN_msgSend(CAN_message* message);
CAN_message CAN_msgRec();

//void CAN_intHandle(/*can_msg *msg*/)
/*
int CAN_error(void);
int CAN_transmit_complete(void);
int CAN_int_vect(void);
*/

#endif
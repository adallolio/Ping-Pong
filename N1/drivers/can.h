#ifndef CAN_H_
#define CAN_H_

//volatile uint8_t rx_flag;
enum interrupt_flags {no_flag, RX0, RX1};

typedef struct {
	int id;				// 5 bytes for standard identifier
	uint8_t length;		// Number of data bytes
	int8_t data[8];
} CAN_message;

int CAN_Init(void);
void CAN_msgSend(CAN_message* message);
CAN_message CAN_msgRec();

//void CAN_intHandle(/*can_msg *msg*/)
/*
int CAN_error(void);
int CAN_transmit_complete(void);
int CAN_int_vect(void);
*/

#endif































/*


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
uint8_t CAN_receive(CAN_message* msg);
void CAN_print(CAN_message* msg);
int CAN_error(void);
int CAN_transmit_complete(void);
ISR(INT2_vect);


#endif 


*/
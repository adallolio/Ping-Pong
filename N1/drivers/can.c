//#include "../misc/bit_manipulation.h"
#include "mcp2515.h"
#include "can.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

enum interrupt_flags interrupt_flag = no_flag;

ISR(INT0_vect){
	uint8_t interrupt = mcp2515_read(MCP_CANINTF);

	if (interrupt & MCP_RX0IF){
		printf("Send RX0\r\n");
		interrupt_flag = RX0;
		// clear CANINTF.RX0IF
		mcp2515_bit_modify(MCP_CANINTF, 0x01, 0x00);
	}
	else if (interrupt & MCP_RX1IF){
		interrupt_flag = RX1;
		printf("Send RX1\r\n");
		// clear CANINTF.RX1IF
		mcp2515_bit_modify(MCP_CANINTF, 0x02, 0x00);
	}
	if(MCP_CANINTF & 0x04){
		//printf("Send INT\r\n");
		//clear send INT
		mcp2515_bit_modify(MCP_CANINTF,0x04,0);
	}	
}

int CAN_Init(void) {
	//Enter config mode
	mcp2515_Init();
			
	//RX0 - Turn masks/filters off, rollover disabled
	//mcp2515_bit_modify(MCP_RXB0CTRL, 0b01100100, 0xFF);
	
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_FILTER_OFF, MCP_FILTER_OFF);
	mcp2515_bit_modify(MCP_RXB1CTRL, MCP_FILTER_OFF, MCP_FILTER_OFF);
	// Rollover enable
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_ROLLOVER, MCP_ROLLOVER);
	mcp2515_bit_modify(MCP_RXB1CTRL, MCP_ROLLOVER, MCP_ROLLOVER);
	
	//Enable interrupt when message is received (RX0IE = 1)
	//mcp2515_bit_modify(MCP_CANINTE, 0x01, 1);
	mcp2515_write(MCP_CANINTE, MCP_RX_INT);

	//Enable sent INT
	//mcp2515_write(MCP_CANINTE, MCP_TX_INT);

	// Low INT0 generates interrupt request
	MCUCR |= (0 << ISC01) | (0 << ISC00);
	GICR |= (1 << INT0);
	
	//Enable normal mode
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	
	//Enable loopback mode
	mcp2515_bit_modify(MCP_CANCTRL,MODE_MASK,MODE_LOOPBACK);



	return 0;
}

void CAN_msgSend(CAN_message *message) {
	uint8_t i;
	
	//Check if there is no pending transmission
	/*
	if (CAN_transmit_complete()) {
		
		//Set the message id
		//bit 7-0 SID<10:3>: Standard Identifier bits
		mcp2515_write(MCP_TXB0SIDH, (int8_t)(message->id >> 3));
		// bit 7-5 SID<2:0>: Standard Identifier bits
		mcp2515_write(MCP_TXB0SIDL, (int8_t)(message->id << 5));
		
		//Set data length and use data frame (RTR = 0)
		mcp2515_write(MCP_TXB0DLC, (0x0F) & (message->length));
		//Set data bytes (max. 8 bytes)
		for (i = 0; i < message->length; i++) {
			// write base address + data index, then data index as data
			mcp2515_write(MCP_TXB0D0 + i, message->data[i]);
		}
		
		//Request to send via TX0, 
		//Bit 0 used to request message transmission of TXB0 buffer (on falling edge)
		mcp2515_request_to_send(1);
		
	} else {
		if (CAN_error() < 0) {
			return -1;
		}
	}
	*/
	
	// Write ID to TXB0SIDH
	mcp2515_write(MCP_TXB0SIDH, (message->id) >> 3);
	// Write 0 to TXB0SIDL and extended identifier registers
	mcp2515_write(MCP_TXB0SIDL, (message->id) << 5);
	mcp2515_write(MCP_TXB0EID8, 0);
	mcp2515_write(MCP_TXB0EID0, 0);
	
	//Write data length
	mcp2515_write(MCP_TXB0DLC, message->length);
	
	for (int i = 0; i < message->length; i++){
		mcp2515_write(MCP_TXB0SIDH + 5 + i, message->data[i] );
	}
	
	//printf("CANINTF b4 RTS: %d\r\n",MCP_CANINTF);
	mcp2515_request_to_send(MCP_RTS_TX0);
	//printf("CANINTF after RTS: %d\r\n",MCP_CANINTF);

}


CAN_message CAN_msgRec() {
	
	/*
	uint8_t i;
	CAN_message message;
	
	//Check if RX buffer has a message
	if (rx_flag == 1) {
		
		//Get message id FROM SID high and SID low
		message.id  = (mcp2515_read(MCP_RXB0SIDH) << 3) | (mcp2515_read(MCP_RXB0SIDL) >> 5);
	
		// Get message length
		// RXBnDLC – RECEIVE BUFFER n DATA LENGTH CODE
		// Length held in bits 3..0
		message.length = (0x0F) & (mcp2515_read(MCP_RXB0DLC));
	
		// Get message data
		// Iterate through length of message
		for(i = 0; i < message.length; i++) {
			// MCP_RXB0D0 contains 8 data bits
			message.data[i] = mcp2515_read(MCP_RXB0D0 + i);
		}
		
		//Clear interrupt flag, message received
		rx_flag = 0;
				
	} else {
		//Message not received
		message.id = -1;
	}
	
	return message;
	*/

	CAN_message msg;

	switch(interrupt_flag){
		case no_flag:
			msg.id = 10;
			//msg->data[0] = CAN_NO_MESSAGE;
			break;
		
		case RX0:
			//printf("ENTERED RX0!!!!!!!!!!!!!!!!\r\n");
			// RXBnSIDH and RXBnSIDL (id)
			msg.id = (mcp2515_read(MCP_RXB0CTRL + 1) << 3) | (mcp2515_read(MCP_RXB0CTRL + 2) >> 5);
			// bit 0 to 3 are data length code bits. register + 5 is RXBnDLC (data length)
			msg.length = (mcp2515_read(MCP_RXB0CTRL + 5) & 0x0F ); 
			//printf("MSG LENGTH: %d\r\n", msg.length);
			
			int i = 0;
			while( (i < msg.length) && (i < 8) ){
				//RXBnDM (receive buffer)
				msg.data[i] = mcp2515_read(MCP_RXB0CTRL + 6 + i);	
				i++;
			}
			//printf("MSG DATA: %d\r\n", msg.data[0]);
			interrupt_flag = no_flag;
			break;
		
		case RX1:
			// RXBnSIDH and RXBnSIDL (id)
			msg.id = (mcp2515_read(MCP_RXB1CTRL + 1) << 3) | (mcp2515_read(MCP_RXB1CTRL + 2) >> 5);
			// bit 0 to 3 are data length code bits. register + 5 is RXBnDLC (data length)
			msg.length = (mcp2515_read(MCP_RXB1CTRL + 5) & 0x0F ); 
		
			int j = 0;
			while( (j < msg.length) && (j < 8) ){
				//RXBnDM (receive buffer)
				msg.data[j] = mcp2515_read(MCP_RXB1CTRL + 6 + j);	
				i++;
			}
			interrupt_flag = no_flag;
			break;
		
		default:
			break;
	}

	/*
	// RXBnSIDH and RXBnSIDL (id)
	msg.id = (mcp2515_read(reg + 1) << 3) | (mcp2515_read(reg + 2) >> 5);
	// bit 0 to 3 are data length code bits. register + 5 is RXBnDLC (data length)
	msg.length = (mcp2515_read(reg + 5) & 0x0F ); 
		
	int i = 0;
	while( (i < msg.length) && (i < 8) ){
		//RXBnDM (receive buffer)
		msg.data[i] = mcp2515_read(reg + 6 + i);	
		i++;
	}
	*/

	return msg;
}

/*
void CAN_intHandle(/*can_msg *msg) {
	switch(interrupt_flag){
		case no_flag:
			//msg->data[0] = CAN_NO_MESSAGE;
			break;
		case RX0:
			CAN_msgRec(MCP_RXB0CTRL);
			interrupt_flag = no_flag;
			break;
		case RX1:
			CAN_msgRec(MCP_RXB1CTRL);
			interrupt_flag = no_flag;
			break;
		default:
			break;
	}
}CAN_msgRec
*/


/*
int CAN_error(void) {
	uint8_t error = mcp2515_read(MCP_TXB0CTRL);
	
	//Transmission error detected
	if (test_bit(error, 4)) return -1;
	
	//Message lost arbitration
	if (test_bit(error, 5)) return -2;
	
	return 0;
}
int CAN_transmit_complete(void) {
	//Check if TX buffer is not pending transmission (TXREQ = 0, where TXREQ is bit 3 of TXBOCTRL)
	if (test_bit(mcp2515_read(MCP_TXB0CTRL), 3)) {
		// Return 0 if NOT pending transmission, aka clear to send
		return 0;
	} else {
		// Return 1 if pending transmission, aka wait
		return 1;
	}
}
int CAN_int_vect(void) {
	//Clear interrupt flag
	mcp2515_bit_modify(MCP_CANINTF, 0x01, 0);
	rx_flag = 1;
	return 0;
}
*/











































































/*

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "mcp2515.h"
#include "can.h"
#include "../misc/bit_manipulation.h"



void CAN_Init(){
	
	mcp2515_Init();
	
	// MCU interrupt
	set_bit(GICR,INT0); //Enable INT0 mask bit
	clear_bit(MCUCR,ISC00); // Falling edge INT0 generates interrupt
	set_bit(MCUCR,ISC01);

	mcp2515_write(MCP_CANINTE, MCP_TX_INT);//Enable send INT
	mcp2515_write(MCP_CANINTE, MCP_RX_INT);//Enable received INT on MCP2515

	// Filter and rollover for receiving messages from N2
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_FILTER_OFF, MCP_FILTER_OFF); // Filter Off for RXB0
	//mcp2515_bit_modify(MCP_RXB0CTRL, MCP_ROLLOVER, MCP_ROLLOVER); // Rollover enable

	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);	//Enable normal mode
	//mcp2515_bit_modify(MCP_CANCTRL,MODE_MASK,MODE_LOOPBACK);  //Enable loopback mode
}


uint8_t CAN_message_send(CAN_message* msg){

	if (CAN_transmit_complete()) {
		mcp2515_write(MCP_TXB0SIDH, (msg->id) >> 3); // Set message ID high bits
		mcp2515_write(MCP_TXB0SIDL, (msg->id) << 5); // Set message ID low bits 
		mcp2515_write(MCP_TXB0DLC, (msg->length)); // Set data length
	
		for (uint8_t i = 0; i < msg->length; i++){
			mcp2515_write(MCP_TXB0D0+i, msg->data[i]); // Iterate through length, Set data bits
		}
		mcp2515_request_to_send(MCP_RTS_TX0); // Sends data to TX0 buffer 

	} else {
		if (CAN_error() < 0) {
			return -1;
		printf("CAN error in RTS");
		}
	}

	return 0;
}


uint8_t CAN_receive(CAN_message* msg){ // Arg is the portion of the msg that I want
	
	if (CAN_RX_flag){
		
		msg->id = (mcp2515_read(MCP_RXB0SIDH) << 3) | (mcp2515_read(MCP_RXB0SIDL) >> 5); // Join low and high ID to complete message ID
		msg->length = (0x0F) & (mcp2515_read(MCP_RXB0DLC)); // Get number of data bytes
		
		for (uint8_t i = 0; i < msg->length; i++){	// Iterate through length
			msg->data[i] = mcp2515_read(MCP_RXB0D0 + i); // Read data bits
		}

		CAN_RX_flag = 0; // int flag = 0, message returned
		return 1;
	}
	else {
		//Message not received
		msg->id = -1;
	}

	 return 0;
}


void CAN_print(CAN_message* msg){
	printf("CAN msg ID: %d \r\n", msg->id);
	printf("CAN msg length: %d \r\n", msg->length);
	printf("CAN msg data: ");
	for (int i = 0; i < msg->length; i++){
		printf("%x, ",msg->data[i]);
	}
	printf("\r\n");
}


int CAN_error(void){

	uint8_t error = mcp2515_read(MCP_TXB0CTRL);

	if (test_bit(error, 4)) return -1; 	//Transmission error detected	
	if (test_bit(error, 5)) return -2;  //Message lost arbitration
	
	return 0;
}


int CAN_transmit_complete(void){
	//Check if TX buffer is not pending transmission (TXREQ = 0, where TXREQ is bit 3 of TXBnCTRL)
	//The TXBnCTRL.TXREQ bit must be clear (indicating the transmit buffer is not pending transmission) 
	//before writing to the transmit buffer.
	if (test_bit(mcp2515_read(MCP_TXB0CTRL), 3)) {
		// Return 0 if NOT pending transmission, aka clear to send
		return 0;
	} else {
		// Return 1 if pending transmission
		return 1;
	}
}


ISR(INT0_vect) // Interrupt handler
{
	_delay_ms(10);
	//if(MCP_CANINTF & 0x04){ //Send INT flag set
	 	printf("CAN msg sent\r\n");
	 	mcp2515_bit_modify(MCP_CANINTF,0x04,0x00);	//clear send INT flag
	//}
	//if(MCP_CANINTF & 0x01){ //INT from CAN msg received
	//printf("CAN msg received\r\n");
	//mcp2515_bit_modify(MCP_CANINTF,0x01,0x00);	//clear send INT flag
	//CAN_RX_flag = 1;
	//}	
}

*/
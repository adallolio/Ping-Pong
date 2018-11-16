//can.c
//Richard Mc>Crae-Lauba

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "mcp2515.h"
#include "can1.h"
#include "../misc/bit_manipulation.h"


/* TO DO:
	1)-check! test N1 on loopback, interrupts working?
	2) -check! Add sending buffer check, retest loopback
	3) 1-2 with N2
	4) N1 - N2 communication
*/


void CAN_Init(){
	
	mcp2515_Init();
	
	mcp2515_write(MCP_CANINTE, MCP_TX_INT);//Enable send INT
	mcp2515_write(MCP_CANINTE, MCP_RX_INT);//Enable received INT on MCP2515

	// Filter and rollover for receiving messages from N2
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_FILTER_OFF, MCP_FILTER_OFF); // Filter Off for RXB0
	//mcp2515_bit_modify(MCP_RXB0CTRL, MCP_ROLLOVER, MCP_ROLLOVER); // Rollover enable

	// MCU interrupt
	set_bit(GICR,INT0); //Enable INT0 mask bit
	clear_bit(MCUCR,ISC00); // Falling edge INT0 generates interrupt
	set_bit(MCUCR,ISC01);

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
		printf("EEEE");
		mcp2515_request_to_send(MCP_RTS_TX0); // Sends data to TX0 buffer 

	} else {
		if (CAN_error() < 0) {
			printf("CAN error in RTS");
			return -1;
		}
	}

	return 0;
}


CAN_message CAN_receive(){ // Arg is the portion of the msg that I want
	CAN_message msg;
	if (CAN_RX_flag){
		
		msg.id = (mcp2515_read(MCP_RXB0SIDH) << 3) | (mcp2515_read(MCP_RXB0SIDL) >> 5); // Join low and high ID to complete message ID
		msg.length = (0x0F) & (mcp2515_read(MCP_RXB0DLC)); // Get number of data bytes
		
		for (uint8_t i = 0; i < msg.length; i++){	// Iterate through length
			msg.data[i] = mcp2515_read(MCP_RXB0D0 + i); // Read data bits
		}

		CAN_RX_flag = 0; // int flag = 0, message returned
		
	}
	else {
		//Message not received
		//mcp2515_bit_modify(MCP_CANINTF,0x01,0x00);	//clear send INT flag
		msg.id = -1;
	}
	
	return msg;
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


uint8_t CAN_error(void){

	uint8_t error = mcp2515_read(MCP_TXB0CTRL);

	if (test_bit(error, 4)) return -1; 	//Transmission error detected	
	if (test_bit(error, 5)) return -2;  //Message lost arbitration
	
	return 0;
}


uint8_t CAN_transmit_complete(void){
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

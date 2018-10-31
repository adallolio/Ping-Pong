#include "../misc/bit_manipulation.h"
#include "../misc/macros.h"
#include "can.h"
#include "mcp2515.h"
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

enum interrupt_flags interrupt_flag = no_flag; 

ISR(INT2_vect){
	uint8_t interrupt = mcp2515_read(MCP_CANINTF);

	if (interrupt & MCP_RX0IF){
		interrupt_flag = RX0;
		//printf("RX0 entered\r\n");
		// clear CANINTF.RX0IF
		mcp2515_bit_modify(MCP_CANINTF, 0x01, 0x00);
	}
	else if (interrupt & MCP_RX1IF){
		interrupt_flag = RX1;
		//printf("RX1 entered");
		// clear CANINTF.RX1IF
		mcp2515_bit_modify(MCP_CANINTF, 0x02, 0x00);
	}
}

void CAN_Init() {
	mcp2515_Init();
	// Turn mask/filters off
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_FILTER_OFF, MCP_FILTER_OFF);
	mcp2515_bit_modify(MCP_RXB1CTRL, MCP_FILTER_OFF, MCP_FILTER_OFF);
	
	// Rollover enable
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_ROLLOVER, MCP_ROLLOVER);
	mcp2515_bit_modify(MCP_RXB1CTRL, MCP_ROLLOVER, MCP_ROLLOVER);
	
	// Interrupt pin (enable CANINTE.RXnIE)
	mcp2515_write(MCP_CANINTE, MCP_RX_INT);

	// Low INT2 generates interrupt request
	EICRA |= (0 << ISC21) | (0 << ISC20);
	// Enable external interrupts of INT2, PD2
	EIMSK |= (1 << INT2);

	// Set to normal mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

	// Set to loopback mode
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);

}

void CAN_msgSend(CAN_message *message) {
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
	mcp2515_request_to_send(MCP_RTS_TX0);
}

CAN_message CAN_msgRec() {

	CAN_message msg;

	switch(interrupt_flag){
		case no_flag:
			//msg->data[0] = CAN_NO_MESSAGE;
			printf("NO FLAG\r\n");
			break;
		case RX0:
			// RXBnSIDH and RXBnSIDL (id)
			printf("ENTERED!\r\n");
			msg.id = (mcp2515_read(MCP_RXB0CTRL + 1) << 3) | (mcp2515_read(MCP_RXB0CTRL + 2) >> 5);
			// bit 0 to 3 are data length code bits. register + 5 is RXBnDLC (data length)
			msg.length = (mcp2515_read(MCP_RXB0CTRL + 5) & 0x0F ); 
		
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
				j++;
			}
			//printf("MSG DATA: %d\r\n", msg.data[0]);
			interrupt_flag = no_flag;
			break;
		default:
			break;
		}
	return msg;
}

/*
void CAN_handle_interrupt(can_msg *msg)
{
	switch(interrupt_flag){
		case no_flag:
			msg->data[0] = CAN_NO_MESSAGE;
			break;
		case RX0:
			CAN_msg_receive(msg, MCP_RXB0CTRL);
			interrupt_flag = no_flag;
			break;
		case RX1:
			CAN_msg_receive(msg, MCP_RXB1CTRL);
			interrupt_flag = no_flag;
			break;
		default:
			break;
	}
}
*/
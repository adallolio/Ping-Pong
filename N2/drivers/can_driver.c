#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "mcp2515.h"
//#include "MCP_driver.h"
//#include "spi.h"
#include "can_driver.h"
#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"

volatile uint8_t flag = 0;

ISR(INT4_vect) {
    //printf("int\r\n");
    flag = 1;
    mcp2515_write(MCP_CANINTF, 0x00);
    mcp2515_write(MCP_CANINTF, 0x00);
    //printf("MCP_CANINTF_OUT: %2x\r\n",mcp2515_read(MCP_CANINTF));
}

void CAN_init(void){
    mcp2515_Init();
    //_delay_ms(1000);
    mcp2515_write(MCP_CANINTE, MCP_RX_INT);
    //mcp2515_write(MCP_CANINTE, MCP_TX_INT);
    mcp2515_write(MCP_CANCTRL, MODE_NORMAL);

	// Disable global interrupts
	//cli();
	// Interrupt on falling edge PD2
	set_bit(EICRB, ISC41);
	clear_bit(EICRB, ISC40);
	// Enable interrupt on PD2
	set_bit(EIMSK,INT4);
	// Enable global interrupts
    //sei();
}

// check if package in buffers
uint8_t CAN_int_vect(){
    if (flag) {
        flag = 0;
        return 1;
    }
    else return 0;
}

/*
uint8_t CAN_transmit_complete(){
    uint8_t flag = mcp2515_read(MCP_CANINTF);
    if ((flag & (MCP_TX0IF)) == MCP_TX0IF){
        return 0;
    }

    return 1;
}
*/

void CAN_send(can_msg_t* msg){

    /* Arbitration field; set ID and length */
    char id_high = msg->id >> 3;
    char id_low = msg->id << 5;
    uint8_t length = msg->length;

    mcp2515_write(MCP_TXB0SIDH, id_high);
    mcp2515_write(MCP_TXB0SIDL, id_low);
    mcp2515_write(MCP_TXB0DLC, length);
    mcp2515_write(MCP_TXB0EID8, 0);
    mcp2515_write(MCP_TXB0EID0, 0);

    // Set data
    for (uint8_t i = 0; i<length; i++) {
        mcp2515_write(MCP_TXB0D0 + i , msg->data[i]);
    }

    mcp2515_request_to_send(MCP_RTS_TX0);
    //printf("sent:%d\r\n", msg->data[0]);
}

void CAN_read(can_msg_t* msg){
    uint8_t id_high = mcp2515_read(MCP_RXB0SIDH);
    uint8_t id_low = mcp2515_read(MCP_RXB0SIDL);

    msg->length = mcp2515_read(MCP_RXB0DLC);

    id_high = id_high << 3;
    id_low = id_low >> 5;
    msg->id =  id_high + id_low;

    for (uint8_t i = 0; i < msg->length ; i++){
        msg->data[i] = mcp2515_read(MCP_RXB0D0 + i);
    }

    printf("rec:%d\r\n", msg->id);

    //mcp2515_bit_modify(MCP_CANINTF, 1, 0); // set interrupt vector 1 to 0
    //mcp2515_bit_modify(MCP_CANINTF, 1, 0); // set interrupt vector 2 to 0

    //mcp2515_write(MCP_CANINTF, 0xFF);
}

void CAN_sendIR(int ir){
    can_msg_t send;
    send.id = ATmega2560_ID;
    send.data[0] = ir;
    send.length = 1;
    CAN_send(&send);
}
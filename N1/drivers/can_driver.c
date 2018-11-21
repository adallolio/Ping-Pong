#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "mcp2515.h"
#include "can_driver.h"
#include "joystick.h"
#include "touch.h"
#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"

volatile uint8_t flag = 0;

/** Interrupt Routine
*/
ISR(INT0_vect) {
    flag = 1;
    mcp2515_write(MCP_CANINTF, 0x00);
    mcp2515_write(MCP_CANINTF, 0x00);
}

/** CAN initialization function
*/
void CAN_init(void){
    mcp2515_Init();
    mcp2515_write(MCP_CANINTE, MCP_RX_INT);

    //printf("Initializing CAN driver...\n\r");
    //_delay_ms(1000);
    mcp2515_write(MCP_CANCTRL, MODE_NORMAL);


	// Disable global interrupts
	//cli();
	// Interrupt on falling edge PD2
	set_bit(MCUCR, ISC01);
	clear_bit(MCUCR, ISC00);
	// Enable interrupt on PD2
	set_bit(GICR,INT0);
	// Enable global interrupts
    //sei();
}

// check if package in buffers
/** CAN check for interrupt.
*/
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

/* BASIC SEND AND RECEIVE FUNCTIONS */

/** CAN send message
    @param can_msg_t* msg message to be sent
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

/** CAN read function
    @param can_msg_t* msg empty message to be filled
*/
void CAN_read(can_msg_t* msg){
    uint8_t id_high = mcp2515_read(MCP_RXB0SIDH);
    uint8_t id_low = mcp2515_read(MCP_RXB0SIDL);

    msg->length = mcp2515_read(MCP_RXB0DLC);

    id_high = id_high << 3;
    id_low = id_low >> 5;
    msg->id = id_high + id_low;

    for (uint8_t i = 0; i < msg->length ; i++){
        msg->data[i] = mcp2515_read(MCP_RXB0D0 + i);
    }

    //mcp2515_bit_modify(MCP_CANINTF, 1, 0); // set interupt vector 1 to 0
    //mcp2515_bit_modify(MCP_CANINTF, 1, 0); // set interupt vector 2 to 0

    printf("received:%d\r\n", msg->data[0]);
}


/* ADVANCED SEND FUNCTIONS DURING GAME */

/** CAN send a complete message set to Node 2
*/
void CAN_sendBunch(){
        CAN_joyMsg();
        CAN_slidersMsg();
        CAN_butt();
}
/** CAN build and send a slider message
*/
void CAN_slidersMsg(){
    static TOUCH_sliderPos slider_pos_prev;
    can_msg_t msg;
    
    TOUCH_sliderPos slider_pos = TOUCH_getPos();
    //if(abs(slider_pos.slider_right - slider_pos_prev.slider_right) > 5 || abs(slider_pos.slider_left - slider_pos_prev.slider_left) > 5){
        msg.id = SLIDERS_ID;
        //msg.data[0] = CAN_SLIDERS_POS;
        msg.data[0] = slider_pos.slider_left;
        //msg.data[2] = CAN_SLIDER_POS_R;
        msg.data[1] = slider_pos.slider_right;
        msg.length = 2;
        CAN_send(&msg);
        //slider_pos_prev = slider_pos;
    //}
}

/** CAN build and send a joystick message
*/
void CAN_joyMsg(){
    static Joy_position joy_pos_prev;
    can_msg_t msg;
    
    Joy_position joy_pos = Joy_Read();
    if(abs(joy_pos.x - joy_pos_prev.x) > 5){
        msg.id = JOYSTICK_ID;
        //msg.data[0] = CAN_JOY_POS_X;
        msg.data[0] = joy_pos.x;
        msg.length = 1;
        CAN_send(&msg);
        joy_pos_prev = joy_pos;
    }
}

/** CAN build and send a button message
*/
void CAN_butt(){
    static int button_pressed_prev;
    can_msg_t msg;
    
    int button_pressed = TOUCH_Button();
    if(button_pressed == 1 && button_pressed_prev == 0){
        msg.id = TOUCH_BUTTON_ID;
        //msg.data[0] = CAN_TOUCH_BUTTON;
        msg.data[0] = button_pressed;
        msg.length = 1;
        CAN_send(&msg);
    }
    button_pressed_prev = button_pressed;
}
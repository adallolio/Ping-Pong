// Alberto Dallolio - Main N1

#include "../misc/bit_manipulation.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include <avr/interrupt.h>
#include "adc.h"
#include "joystick.h"
#include "touch.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "mcp2515.h"
#include "can_driver.h"
#include "../misc/memory_mapping.h"
#include "../misc/macros.h"

//#include "font_norm.h"


int main(void) {

	//cli();
	//------------UART------------//
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);				// Set clock speed
	fdevopen(UART_send, UART_receive);  // Connect printf

	//------------ADC------------//
	ADC_Init();
	
	//------------JOYSTICK TEST------------//
	Joy_Init();
	// uint8_t x;
	// uint8_t y;
	// int btn;

	//------------TOUCH TEST------------//
	TOUCH_Init();
	TOUCH_sliderPos sliders;
	
	//------------OLED and MENU------------//
	MENU_Init();
	menu_item_info *selected;
	
	//------------CAN TEST------------//
	CAN_init();


	can_msg_t send;
	can_msg_t rec;
	can_msg_t joystick;

	send.id=1;
	send.length=1;
	send.data[0]=4;

	//joystick.id=JOY_POS;
	//joystick.length=2;

	GAME_setOpt(menu);
	int lives = 3;

	while(1){

		switch (GAME_getOpt()){
				case menu:
						MENU_nav();
						MENU_select();
						break;
				case gameInit:
						//CAN_send(GAME_getOpt());
						MENU_printGame();
						lives = 3;
						GAME_setOpt(game);
						break;
				case game:
						//CAN_send();
						break;
				case gamePause:
						if(Joy_Button()){
							GAME_setOpt(game);
							MENU_printGame();
						}
						break;
				case gameOver:
						MENU_printGameOver();
						_delay_ms(3000);
						GAME_setOpt(menu);
						MENU_start();
						break;
				default:
						GAME_setOpt(menu);
						break;
		}
/*
		CAN_handle_interrupt(&receive);
		msg_type = receive.data[0];
		switch (msg_type){
				case CAN_LIVES:
							if(remaining_lives > 1 && STATE_OPTION_get() == game){
								score = score + TIMER_stop();
								remaining_lives = remaining_lives - 1;
								STATE_OPTION_set(game_pause);
								MENU_print_pause_screen(remaining_lives);
							}
							else if (STATE_OPTION_get() == game){
								score = score + TIMER_stop();
								STATE_OPTION_set(game_over);
							}
							break;
				default:
							break;
		}
		_delay_ms(5);
*/
























		//printf("MCP_CANINTF_OUT: %2x\r\n",mcp2515_read(MCP_CANINTF));
		//printf("MCP_EFLG_OUT: %2x\r\n",mcp2515_read(MCP_EFLG));
		//printf("MCP_CANSTAT_OUT: %2x\r\n",mcp2515_read(MCP_CANSTAT));
/*
		sliders = TOUCH_getPos();
		printf("LEFT: %d\r\n", sliders.slider_left);
		_delay_ms(20);
		printf("RIGHT: %d\r\n", sliders.slider_right);
		_delay_ms(500);

		if (CAN_int_vect()){
			//printf("MCP_CANINTF_IN: %2x\r\n",mcp2515_read(MCP_CANINTF));
			//printf("MCP_EFLG_IN: %2x\r\n",mcp2515_read(MCP_EFLG));
			CAN_read(&rec);
			_delay_ms(500);
		}
*/
	}

	return 0;
}

// Alberto Dallolio - Main N1

#include "../misc/bit_manipulation.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "adc.h"
#include "joystick.h"
#include "touch.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "mcp2515.h"
#include "can_driver.h"
#include "timer.h"
#include "../misc/memory_mapping.h"
#include "../misc/macros.h"

//#include "font_norm.h"


int main(void) {

	cli();
	//------------UART------------//
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);				// Set clock speed
	fdevopen(UART_send, UART_receive);  // Connect printf

	//------------ADC INIT------------//
	ADC_Init();
	
	//------------JOYSTICK INIT------------//
	Joy_Init();

	//------------TOUCH INIT------------//
	TOUCH_Init();
	
	//------------MENU INIT------------//
	MENU_Init();
	
	//------------CAN INIT------------//
	CAN_init();
	can_msg_t send;
	can_msg_t rec;

	//------------TIMER INIT------------//
	TIMER_init();

	//------------GAME SETTINGS INIT------------//
	GAME_setOpt(menu);
	int lives;
	int life_lost;
	int score;

	sei();

	while(1){

		switch (GAME_getOpt()){
				case menu:
						MENU_nav();
						MENU_select();
						break;
				case gameInit:
						//CAN_send(GAME_getOpt());
						lives = MENU_printGame();
						score = 0;
						TIMER_start();
						GAME_setOpt(game);
						break;
				case game:
						//lives = MENU_printGame();
						CAN_sendBunch();
						score = score + TIMER_stop();
						printf("SCORE: %d\r\n", score);
						break;
				case gamePause:
						if(Joy_Button()){
							GAME_setOpt(game);
							MENU_printGame();
							TIMER_start();
						}
						break;
				case gameOver:
						MENU_printGameOver(score);
						_delay_ms(3000);
						GAME_setOpt(menu);
						MENU_start();
						break;
				default:
						GAME_setOpt(menu);
						break;
		}

		//printf("MCP_CANINTF_OUT: %2x\r\n",mcp2515_read(MCP_CANINTF));
		//printf("MCP_EFLG_OUT: %2x\r\n",mcp2515_read(MCP_EFLG));
		//printf("MCP_CANSTAT_OUT: %2x\r\n",mcp2515_read(MCP_CANSTAT));

		if (CAN_int_vect()){
			//printf("MCP_CANINTF_IN: %2x\r\n",mcp2515_read(MCP_CANINTF));
			//printf("MCP_EFLG_IN: %2x\r\n",mcp2515_read(MCP_EFLG));
			//printf("MCP_CANSTAT_IN: %2x\r\n",mcp2515_read(MCP_CANSTAT));
			CAN_read(&rec);
			life_lost = rec.data[0];
			if(lives > 1 && life_lost==1 && GAME_getOpt() == game){
					score = score + TIMER_stop();
					lives = lives - 1;
					GAME_setOpt(gamePause);
					MENU_printPause(lives,score);
					}
			else if (lives==1 && life_lost==1 && GAME_getOpt() == game){
					score = score + TIMER_stop();
					GAME_setOpt(gameOver);
					}
		}


		_delay_ms(5);










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

// Alberto Dallolio - Main N2

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "../misc/bit_manipulation.h"
#include "../misc/macros.h"
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"
#include "can_driver.h"
#include "pwm.h"
#include "servo.h"
#include "adc.h"
#include "ir.h"
#include "button.h"
#include "motor.h"
#include "dac.h"
#include "pid.h"


int main(void) {
	
	//------------INITIALIZE------------//
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);				// Set clock speed
	fdevopen(UART_send, UART_receive);  // Connect printf

	CAN_init();
	ADC_init();
	servo_init(cpu_speed);

	//------------INTERRUPTS------------//
	//sei();

	//-------------CAN TEST-------------//
	can_msg_t send;
	can_msg_t rec;
	can_msg_t joystick;

	send.id=1;
	send.length=1;
	send.data[0]=4;

	//button_init();

	DAC_init();
	motor_init();
	PID_init();
	//PID_cal();

/*
	rec.id=0;
	rec.length=0;
	rec.data[8] = {0};

	send.id=0x01;
	send.length=3;
	send.data[0]=10;
	send.data[1]=11;
	send.data[2]=12;

	joystick.id = 0;
	joystick.length = 0;
	joystick.data[8] = {0};
*/
	_delay_ms(2500);

	int lives = 10;

	while(1){
		//-------------IR GAME TEST-------------//
		
		//ADC_channelRead(IR);
/*	
		if (lives>1){
			lives = IR_inGame(lives);
		}
		else{
			printf("Game over!\r\n");
			break;
		}
*/
		
		//_delay_ms(500);
		
		//_delay_ms(2500);

		//button_read();

		//-------------PWM/SERVO TEST-------------//

		//set_servo(ADC_channelRead(JOY_SL));
		//motorSpeed(ADC_channelRead(JOY_SL1));
		
		//motorSpeed(ADC_channelRead(JOY_SL_L));
		//PID(ADC_channelRead(JOY_SL_L));
		//PID(130);
		motorSpeed(126);
		_delay_ms(20);
		//set_servo(ADC_channelRead(JOY_SL_R));
		//ADC_channelRead(JOY_SL2);
		//_delay_ms(500);


		//-------------MOTOR TEST-------------//

/*
		motorSpeed(ADC_channelRead(JOY_AX));
		//ADC_channelRead(JOY_SL);
		_delay_ms(500);
*/

		//-------------CAN TEST-------------//
		//_delay_ms(2000);
		//CAN_message_send(&send);
		//CAN_msgSend(&send);
		//printf("sent:%d\r\n", send.data[0]);
		//rec = CAN_msgRec();
		//printf("received:%d\r\n", rec.data[0]);
		//_delay_ms(2000);
		//CAN_print(&print);


		//CAN_send(&send);

		//_delay_ms(10);
		//if (CAN_int_vect()){
		//	CAN_read(&rec);
		//}
		//_delay_ms(2000);

		// CAN register tests
/*		printf("CANINTF: %x",MCP_CANINTF);
		printf("\n\r");
		printf("CANSTAT: %x",MCP_CANSTAT);
		printf("\n\r");
		printf("EFLG: %x",MCP_EFLG);
		printf("\n\r");
*/
		// Joystick position over CAN
/*		CAN_receive(&msg);
		if msg.id == JOY_POS{
			printf("Booyah bitches\n\r");
			CAN_print(&msg);
			printf("\n\r");
		}
		else{
			printf("Joystick positions not received\n\r");
			CAN_print(&msg);
			printf("\n\r");
		}
*/
	}

	return 0;
}
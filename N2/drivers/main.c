// Alberto Dallolio - Main N2

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
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
#include "TWI_Master.h"


int main(void) {
	
	cli();
	//------------UART INIT------------//
	unsigned long cpu_speed = F_CPU;
    UART_Init(cpu_speed);
    fdevopen(UART_send, UART_receive);

    //------------ADC INIT------------//
	ADC_init();


	//------------CAN INIT------------//
	CAN_init();
	can_msg_t send;
	can_msg_t rec;
	int msg_type;

	//------------SERVO INIT------------//
	servo_init(cpu_speed);

	//------------BUTTON INIT------------//
	button_init();

	//------------DAC INIT------------//
	DAC_init();

	//------------MOTOR INIT------------//
	MOTOR_init();
	int rot;
	int speed = 0;
	int ir = 0;
	int pos_reference = 127;

	//------------MOTOR CALIBRATION------------//
	//MOTOR_cal();

	//------------PID INIT------------//
	PID_init();
	//PID_ref(pos_reference);

	sei();

	//int lives = 10;

	while(1){

		_delay_ms(5000);
		CAN_sendIR(1);
		
		//MOTOR_encoderTest();
		//MOTOR_rotScaled();
		//PID_ref(0);
		//ADC_channelRead(IR);
		//ADC_channelRead(JOY_AX);
		//pos_reference = PID_ref(127);
		//MOTOR_setSpeed(10);
		//set_servo(ADC_channelRead(JOY_SL_R));

		
/*
		if (CAN_int_vect()){
			CAN_read(&rec);

			msg_type = rec.id;
			switch(msg_type){
				case JOYSTICK_ID:
					pos_reference = PID_ref(rec.data[0]);
					break;
				case SLIDERS_ID:
					set_servo(rec.data[1]); // 1=right slider, 0=left slider.
					break;
				case TOUCH_BUTTON_ID:
					button_shoot();
					break;
				default:
					break;
			}

		}

		ir = IR_check();
		CAN_sendIR(ir);


		rot = MOTOR_rotScaled();
		if(rot < 0){
			rot = 0;
		}
		if(rot > 255){
			rot = 255;
		}
		
		//PID(rot, pos_reference);
*/
	}


//                             CAN TEST IN LOOPBACK MODE
/*
		CAN_send(&send);
		printf("MCP_CANINTF: %2x\r\n",mcp2515_read(MCP_CANINTF));
		printf("MCP_EFLG: %2x\r\n",mcp2515_read(MCP_EFLG));
		printf("MCP_CANSTAT: %2x\r\n",mcp2515_read(MCP_CANSTAT));
		if (CAN_int_vect()){
			//printf("MCP_CANINTF_IN: %2x\r\n",mcp2515_read(MCP_CANINTF));
			//printf("MCP_EFLG_IN: %2x\r\n",mcp2515_read(MCP_EFLG));
			CAN_read(&rec);
			_delay_ms(500);
		}
*/

		return 0;
}
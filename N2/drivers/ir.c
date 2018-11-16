// IR.c - Richard McCrae-Lauba
//  IR no break > 400, break < 60


#include "ir.h"
#include "adc.h"

uint8_t score = 0;
uint8_t printDelay = 0;
uint16_t IR_value;

void IR_init(){
	//If game started and lives not zero
	//IR_inGame();
	//else
	//IR_off();
}

int IR_inGame(int lives){
	_delay_ms(500);
	IR_value = ADC_channelRead(IR); // Read current IR value
	//Check for the ball, No break in IR_value =>400
	if (IR_value < 100) {
		lives--;
		printf("Ouch! -1 life, you still have %d lives remaining!\n\r", lives);
		//_delay_ms(100);
		return lives;
		
		//lives--; // IR beam broken, decrement lives count
		//control_set_timer_flag(0); // reset timer counter
						
		//Send the score to node 1
		//CAN_message.data[0] = lives; //ID CAN messages by name, for exaample LIVES
		//CAN_message_send(&CAN_message);
						
		//Wait until the ball is removed, avoid double counting with ball bounce

	}
	// Count time ball is live for score
	else {
		//Increment score counter
		score++;
		printf("Still %d lives!\n\r",lives);
		return lives;
		//printf("You still have %d lives!\n\r", lives);
		// print score to OLED
		// Consider high score
		// Speaker beeps when high score achieved during game play?
		}
}

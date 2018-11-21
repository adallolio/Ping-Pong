// Alberto Dallolio - MENU

#include "../misc/macros.h"
#include "menu.h"
#include "oled.h"
#include "joystick.h"
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <stdarg.h>

state state_ = menu;
int speed;
int lives=0;

menu_item_info *currMenu;
menu_item_info *currChild;
int line;


menu_item_info mainMenu, playGame, settings, stop, livesToDeath, levelEasy, levelMedium, levelHard, contrastLevel, contrastLow, contrastMedium, contrastHigh, invertScreen; // scores, gameSpeed, normalSpeed, fastSpeed, clearScores,
/*
mainMenu, playGame, scores, settings, stop, normalSpeed, fastSpeed, 
clearScores, contrastLevel, contrastLow, contrastMedium, contrastHigh, invertScreen;
*/



menu_item_info mainMenu ={
	.name = "Main menu",
	.child[0] = &playGame,
	.child[1] = &settings,
	.child_num = 2,
};

menu_item_info playGame = {
	.name = "Play game",
	.parent = &mainMenu,
	.child_num = 0,
	.fcnPoint = &GAME_playGame,
};

/*
menu_item_info scores ={
	.name = "Scores",
	.parent = &playGame,
	.child_num = 0,
	//.fcnPoint = &HIGHSCORE_print,
};
*/

menu_item_info settings ={
	.name = "Settings",
	.parent = &mainMenu,
	.child[0] = &contrastLevel,
	.child[1] = &invertScreen,
	.child[2] = &livesToDeath,
	.child_num = 3,
};

menu_item_info livesToDeath ={
	.name = "Difficulty",
	.parent = &settings,
	.child[0] = &levelEasy,
	.child[1] = &levelMedium,
	.child[2] = &levelHard,
	.child_num = 3,
};

menu_item_info levelEasy ={
	.name = "Beginner",
	.parent = &livesToDeath,
	.child_num = 0,
	.fcnPoint = &GAME_levelEasy,
};

menu_item_info levelMedium ={
	.name = "Advanced",
	.parent = &livesToDeath,
	.child_num = 0,
	.fcnPoint = &GAME_levelMedium,
};

menu_item_info levelHard ={
	.name = "Expert",
	.parent = &livesToDeath,
	.child_num = 0,
	.fcnPoint = &GAME_levelHard,
};

menu_item_info contrastLevel ={
	.name = "Contrast level",
	.parent = &settings,
	.child[0] = &contrastLow,
	.child[1] = &contrastMedium,
	.child[2] = &contrastHigh,
	.child_num = 3,
};

menu_item_info invertScreen ={
	.name = "Invert screen",
	.parent = &settings,
	.child_num = 0,
	.fcnPoint = &OLED_invert,
};

menu_item_info contrastLow ={
	.name = "Low",
	.parent = &contrastLevel,
	.child_num = 0,
	.fcnPoint = &MENU_contrLowFcn,
};
menu_item_info contrastMedium ={
	.name = "Medium",
	.parent = &contrastLevel,
	.child_num = 0,
	.fcnPoint = &MENU_contrMedFcn,
};
menu_item_info contrastHigh ={
	.name = "High",
	.parent = &contrastLevel,
	.child_num = 0,
	.fcnPoint = &MENU_contrHighFcn,
};


void MENU_Init() {
	OLED_Init();
	MENU_start();
}

void MENU_start() {
	currMenu = &mainMenu;
	currChild = mainMenu.child[0];
	line = 1;
	MENU_print();
	MENU_highlight();
}

void MENU_print() {
	OLED_reset();
	OLED_printf("%s",currMenu->name); //referencing to pointer!!
	if (currChild!= NULL){
		MENU_highlight();
	}
	for (int i = 0; i < currMenu->child_num; i++){
		OLED_pos(i + 1, 10);
		OLED_gotoCol(10);
		OLED_printf("%s", currMenu->child[i]->name);
	}
}

int MENU_printGame(){
	OLED_reset();
	OLED_pos(3,30);
	OLED_printf("Time to play!");
	return lives;
}

void MENU_configApplied(){
	OLED_reset();
	OLED_pos(3,30);
	OLED_printf("Difficulty Set!");
}

void MENU_printGameOver(int score){
	OLED_reset();
	OLED_pos(1,35);
	OLED_printf("Game over!");
	OLED_pos(4,12);
	OLED_printf("Your last score was %d !",score);
}

void MENU_printPause(int lives_left, int score){
	OLED_reset();
	OLED_pos(1, 12);
	OLED_printf("You have %d lives left!", lives_left);
	OLED_pos(4, 25);
	OLED_printf("Your score is: %d", score);
}

/*
void MENU_printScore(int score){
	OLED_reset();
	OLED_pos(3, 10);
	OLED_printf("Your score is: %d", score);
	OLED_pos(5, 10);
	OLED_printf("Press joystick to resume...");
}
*/

void MENU_printWarning(){
	OLED_reset();
	OLED_pos(2,25);
	OLED_printf("Set difficulty");
	OLED_pos(3,25);
	OLED_printf("before playing!");
}

void MENU_highlight(){
	for (int i = 1; i < currMenu->child_num + 1; i++){
		OLED_pos(i, 0);
		OLED_printf("  ");
	}
	OLED_pos(line, 0);
	OLED_print_arrow(line, 0);
}


// Going EAST selects.
void MENU_select() {
	if ((Joy_Button() || Joy_getDir() == EAST) && currChild!= NULL){
		if (currChild->child[0] != NULL){
			currMenu = currChild;
			currChild = currChild->child[0];
			line = 1;
			MENU_print();
		} else if (currChild->fcnPoint != NULL){
			currChild->fcnPoint();
		}
		while(Joy_Button() || Joy_getDir() == EAST);
	}
}

// Going EAST is not in navigation!
void MENU_nav() {
	switch (Joy_getDir()){
		case WEST:	
			if (currMenu->parent != NULL){
				line = 1;
				currMenu = currMenu->parent;
				currChild = currMenu->child[0];
				MENU_print();
				while(Joy_getDir() == WEST){}
			}
			break;

		case NORTH:
			if (line > 1){
				line = line - 1;
				currChild = currMenu->child[line - 1];
				MENU_highlight();
				while(Joy_getDir() == NORTH){}
			}
			break;

		case SOUTH:
			if (line < currMenu->child_num){
				line = line + 1;
				currChild = currMenu->child[line - 1];
				MENU_highlight();
				while(Joy_getDir() == SOUTH){}
			}
			break;

		default:
			break;
	}

	
}

void GAME_playGame(){
	if (lives==0){
		MENU_printWarning();
		_delay_ms(3000);
		MENU_print();
	} else{
		GAME_setOpt(gameInit);
	}
}

// Set contrast levels.
void MENU_contrLowFcn(){ 
	OLED_setCont(LOW_CONTRAST);
}

void MENU_contrMedFcn(){
	OLED_setCont(MEDIUM_CONTRAST);
}

void MENU_contrHighFcn(){
	OLED_setCont(HIGH_CONTRAST);
}

// Game options.
void GAME_setOpt(state newState){
	state_ = newState;
}

state GAME_getOpt(){
	return state_;
}

void GAME_levelEasy(){
	GAME_setLives(10);
	MENU_configApplied();
	_delay_ms(3000);
	MENU_print();
}

void GAME_levelMedium(){
	GAME_setLives(6);
	MENU_configApplied();
	_delay_ms(3000);
	MENU_print();
}

void GAME_levelHard(){
	GAME_setLives(3);
	MENU_configApplied();
	_delay_ms(3000);
	MENU_print();
}

void GAME_setLives(int new_lives){
	lives = new_lives;
}

/*
void GAME_setSpeedOpt(int new_speed){
	speed = new_speed;
}

int GAME_getSpeedOpt(){
	return speed;
}

void GAME_normalSpeedFcn(){
	GAME_setSpeedOpt(1); 
	GAME_setOpt(gameInit);
}

void GAME_fastSpeedFcn(){
	GAME_setSpeedOpt(2);
	GAME_setOpt(gameInit);
}
*/
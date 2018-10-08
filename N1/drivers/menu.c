// Alberto Dallolio - MENU

#include "../misc/macros.h"
#include "menu.h"
#include "oled.h"
#include "joystick.h"
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

state state_ = menu;
int speed;

menu_item_info *currMenu;
menu_item_info *currChild;
int line;

menu_item_info mainMenu, playGame, scores, settings, stop, normalSpeed, fastSpeed, clearScores, contrastLevel, contrastLow, contrastMedium, contrastHigh, invertScreen;


menu_item_info mainMenu ={
	.name = "Main menu",
	.child[0] = &playGame,
	.child[1] = &scores,
	.child[1] = &settings,
	.child_num = 3,
};

menu_item_info playGame = {
	.name = "Play game",
	.parent = &mainMenu,
	.child[0] = &normalSpeed,
	.child[1] = &fastSpeed,
	.child_num = 2,
};


menu_item_info scores ={
	.name = "Scores",
	.parent = &mainMenu,
	.child_num = 0,
	//.fcnPoint = &HIGHSCORE_print,
};


menu_item_info settings ={
	.name = "Settings",
	.parent = &mainMenu,
	.child[0] = &clearScores,
	.child[0] = &contrastLevel,
	.child[1] = &invertScreen,
	.child_num = 3,
};

menu_item_info normalSpeed = {
	.name = "Normal",
	.parent = &playGame,
	.child_num = 0,
	.fcnPoint = &GAME_normalSpeedFcn,
};

menu_item_info fastSpeed = {
	.name = "Fast",
	.parent = &playGame,
	.child_num = 0,
	.fcnPoint = &GAME_fastSpeedFcn,
};


menu_item_info clearScores ={
	.name = "Clear Scores",
	.parent = &settings,
	.child_num = 0,
	//.fcnPoint = &HIGHSCORE_clear,
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

void MENU_init() {
	OLED_init();
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
			if(currChild == &clearScores){
				//MENU_print_cleared_highscores();
				MENU_print();
			}
			else if(currChild == &scores){
				currMenu = currChild;
				currChild = currChild->child[0];
				line = 1;
			}
		}
		while(Joy_Button() || Joy_getDir() == EAST);
	}
}

// Going EAST is not in navigation!
void MENU_nav() {
	switch (Joy_getDir()){
		case WEST:
			while(Joy_getDir() == WEST){}
			if (currMenu->parent != NULL){
				line = 1;
				currMenu = currMenu->parent;
				currChild = currMenu->child[0];
				MENU_print();
			}
			break;
		case NORTH:
			while(Joy_getDir() == NORTH){}
			if (line > 1){
				line = line - 1;
				currChild = currMenu->child[line - 1];
				MENU_highlight();
			}
			break;
		case SOUTH:
			while(Joy_getDir() == SOUTH){}
			if (line < currMenu->child_num){
				line = line + 1;
				currChild = currMenu->child[line - 1];
				MENU_highlight();
			}
			break;
		default:
			break;
	}
}

void MENU_highlight() {
	for (int i = 1; i < currMenu->child_num + 1; i++){
		OLED_pos(i, 0);
		OLED_printf("  ");
	}
	OLED_pos(line, 0);
	//OLED_print_arrow();
}


// Set contrast levels.
void MENU_contrLowFcn() { 
	OLED_setCont(LOW_CONTRAST);
}

void MENU_contrMedFcn() {
	OLED_setCont(MEDIUM_CONTRAST);
}

void MENU_contrHighFcn() {
	OLED_setCont(HIGH_CONTRAST);
}

// Game options.
void GAME_setOpt(state newState) {
	state_ = newState;
}

state GAME_getOpt() {
	return state_;
}

void GAME_setSpeedOpt(int new_speed) {
	speed = new_speed;
}

int GAME_getSpeedOpt() {
	return speed;
}

void GAME_normalSpeedFcn() {
	GAME_setSpeedOpt(1); 
	GAME_setOpt(gameInit);
}

void GAME_fastSpeedFcn() {
	GAME_setSpeedOpt(2);
	GAME_setOpt(gameInit);
}
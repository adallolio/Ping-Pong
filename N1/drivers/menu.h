// Alberto Dallolio - MENU

#ifndef MENU_H_
#define MENU_H_


typedef struct menu_item_info menu_item_info;

typedef struct menu_item_info {
	char *name;
	menu_item_info *parent;
	menu_item_info *child[4];
	int child_num;
	void (*fcnPoint)(void);
}menu_item_info;


void MENU_Init();
void MENU_start();
void MENU_print();
int MENU_printGame();
void MENU_printGameOver(int score);
void MENU_printPause(int lives_left, int score);
void MENU_select();
void MENU_nav();
void MENU_highlight();
void MENU_contrLowFcn();
void MENU_contrMedFcn();
void MENU_contrHighFcn();


// Game options.
typedef enum{menu, gameInit, game, gamePause, gameOver} state;
	
void GAME_setOpt(state newState);
state GAME_getOpt();
void GAME_playGame();
void GAME_levelEasy();
void GAME_levelMedium();
void GAME_levelHard();
void GAME_setLives(int new_live);

/*
void GAME_setSpeedOpt(int newSpeed);
int GAME_getSpeedOpt();
void GAME_normalSpeedFcn();
void GAME_fastSpeedFcn();
*/


#endif /* MENU_H_ */
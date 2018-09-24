#ifndef TOUCH_H_
#define TOUCH_H_

#define BUTTON_LEFT 0
#define BUTTON_RIGHT 1

#define SLIDER_RIGHT_CH 'r'
#define SLIDER_LEFT_CH 'l'

typedef struct Slider_pos {
	int slider_left;
	int slider_right;
	} TOUCH_sliderPos;

void TOUCH_Init();
int TOUCH_Button();
TOUCH_sliderPos TOUCH_Read();
TOUCH_sliderPos TOUCH_getPos();

#endif /* TOUCH_H_ */
#ifndef TOUCH_H_
#define TOUCH_H_

#define BUTTON_LEFT 0
#define BUTTON_RIGHT 1

#define SLIDER_RIGHT_CH 2
#define SLIDER_LEFT_CH 3

typedef struct Slider_pos {
	int slider_left;
	int slider_right;
	} TOUCH_sliderPos;

void TOUCH_Init();
int TOUCH_Button();
TOUCH_sliderPos TOUCH_Read();
TOUCH_sliderPos TOUCH_getPos();

#endif /* TOUCH_H_ */
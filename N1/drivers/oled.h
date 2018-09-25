// Alberto Dallolio - OLED

#ifndef OLED_H_
#define OLED_H_

#include <avr/io.h>

#define SEGMENT_REMAP						0xA1
#define ENTIRE_DISPLAY_ON					0xA4
#define SET_NORMAL_DISPLAY					0xA6
#define SET_INVERSE_DISPLAY					0xA7
#define SET_MULTIPLEX_RATIO					0xA8

/* Contrast levels */
#define LOW_CONTRAST						0x10
#define MEDIUM_CONTRAST						0x50
#define HIGH_CONTRAST						0xF0

#define SET_COM_OUT_SCAN_DIR				0xC8	// com63 to com0
#define SET_DISPLAY_CLK_DIV_RATIO			0xD5
#define SET_PRECHARGE_PERIOD				0xD9
#define SET_COM_PIN_HW_CONFIG				0xDA
#define SET_VCOM_DESELECT_LVL				0xDB

#define SELECT_IREF							0xAD
#define DISPLAY_OFF							0xAE
#define DISPLAY_ON							0xAF

#define SET_MEMORY_ADDRESSING_MODE			0x20
#define HORIZONTAL_ADDR_MODE				0x00
#define VERTICAL_ADDR_MODE					0x01
#define PAGE_ADDR_MODE						0x02

#define SET_COLUMN_ADDRESS					0x21	//0-127 or 0x00-0x7F
#define SET_PAGE_ADDRESS					0x22	//0-7 or 0x0 to 0x7

#define SET_CONTRAST_CONTROL				0x81	//256 contrast: from 0x00 to 0xFF

#define NUM_LINES							8		//page!
#define NUM_COLUMNS							128


void OLED_init();
void OLED_wrCmd(uint8_t command);
void OLED_wrData(uint8_t data);
char OLED_rdData();
void OLED_gotoCol(uint8_t col);
void OLED_gotoLine(uint8_t line);
void OLED_pos(uint8_t row, uint8_t col);
void OLED_goHome();
void OLED_clLine(uint8_t line);
void OLED_reset( void );
void OLED_setCont(uint8_t level);
void OLED_invert();
void OLED_print_char(char ch);
void OLED_print_arrow();
void OLED_printf(); // THINK!!!!
void OLED_emoticon(); //?

// Functions for pixels.
void OLED_drPix(int x,int y);
int OLED_rdPix(int x, int y);
void OLED_clPix(int x, int y);
void OLED_invPix(int x, int y);
void OLED_drLine(int x1, int y1, int x2, int y2);
void OLED_drCircle(int x, int y, int r);



#endif /* OLED_H_ */
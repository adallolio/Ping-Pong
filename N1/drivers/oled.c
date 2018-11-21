// Alberto Dallolio - OLED

#include "oled.h"
//#include "font_norm.h"
#include "fonts.h"
#include "uart.h"
#include "../misc/memory_mapping.h"
#include "menu.h"

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <math.h>
#include <avr/pgmspace.h>



// Start addresses for the OLED
volatile uint8_t *oled_cmd = (uint8_t *) OLED_COMMAND_ADDRESS;
volatile uint8_t *oled_data = (uint8_t *) OLED_DATA_ADDRESS;

// to be tested
static FILE oled_stdout = FDEV_SETUP_STREAM(OLED_print_char, NULL, _FDEV_SETUP_WRITE); // maybe printf?
static uint8_t line = 0;



void OLED_Init() {

 OLED_wrCmd(0xae); // display off
 OLED_wrCmd(0xa1); //segment remap
 OLED_wrCmd(0xda); //common pads hardware: alternative
 OLED_wrCmd(0x12);
 OLED_wrCmd(0xc8); //common output scan direction:com63~com0
 OLED_wrCmd(0xa8); //multiplex ration mode:63
 OLED_wrCmd(0x3f);
 OLED_wrCmd(0xd5); //display divide ratio/osc. freq. mode
 OLED_wrCmd(0x80);
 OLED_wrCmd(0x81); //contrast control
 OLED_wrCmd(0x50);
 OLED_wrCmd(0xd9); //set pre-charge period
 OLED_wrCmd(0x21);
 OLED_wrCmd(0x20); //Set Memory Addressing Mode
 OLED_wrCmd(0x02);
 OLED_wrCmd(0xdb); //VCOM deselect level mode
 OLED_wrCmd(0x30);
 OLED_wrCmd(0xad); //master configuration
 OLED_wrCmd(0x00);
 OLED_wrCmd(0xa4); //out follows RAM content
 OLED_wrCmd(0xa6); //set normal display
 
 OLED_wrCmd(0xaf); // display on
 //OLED_wrCmd(0xa5); //full on

	OLED_reset();

	//printf("OLED INITIALIZED!\n\r");
}

void OLED_wrCmd(uint8_t cmd) {
	*oled_cmd = cmd;
}

void OLED_wrData(uint8_t data) {
	*oled_data = data;
}


void OLED_print_arrow(uint8_t row, uint8_t col){
OLED_pos(row, col);
OLED_wrData(0b00011000);
OLED_wrData(0b00011000);
OLED_wrData(0b01111110);
OLED_wrData(0b00111100);
OLED_wrData(0b00011000);
}


void OLED_pos(uint8_t l, uint8_t c) {
	OLED_gotoLine(l);
	OLED_gotoCol(c);
}


void OLED_gotoLine(uint8_t line) {
	if (line < NUM_LINES){
		OLED_wrCmd(SET_PAGE_ADDRESS);
		OLED_wrCmd(line);
		OLED_wrCmd(7);
	}
}

void OLED_gotoCol(uint8_t col) {
	if (col < NUM_COLUMNS){
		OLED_wrCmd(SET_COLUMN_ADDRESS);
		OLED_wrCmd(col);
		OLED_wrCmd(0x7F);
	}
}


void OLED_reset() {
	// Clear every line and go home!
	for (uint8_t line = 0; line < NUM_LINES; line++){
		OLED_clLine(line);
	}
	
	OLED_goHome();
}

void OLED_goHome() {
	OLED_pos(0,0);
}


void OLED_clLine(uint8_t line) {
	OLED_pos(line, 0);
	
	for (uint8_t col = 0; col < NUM_COLUMNS; col++){
		OLED_wrData(0x00); //write 8 bits to each column
	}
}


void OLED_invert() {
	static int inverted;
	if (!inverted){
		OLED_wrCmd(SET_INVERSE_DISPLAY);
		inverted = 1;
		} else {
		OLED_wrCmd(SET_NORMAL_DISPLAY);
		inverted = 0;
	}
}

void OLED_printf(const char* fmt, ...) {
	// Maybe I can use vfprintf ?
	// vfprintf: wrap printf().
	// This fcn needs to have variable arguments.
	// Then collect those into a va_list, do processing, 
	// and call vprintf() on the va_list to get the printout happening.

	// THINK!!!!

	va_list args;
	va_start(args, fmt);
	vfprintf(&oled_stdout, fmt, args);
	va_end(args);
}


void OLED_print_char(char ch) {
	// THINK!!!!
	for (int i = 0; i < 5; i++){
		OLED_wrData(pgm_read_byte(&font5[ch - ' '][i]));
	}
}


void OLED_setCont(uint8_t lev) {
	OLED_wrCmd(0x81);
	OLED_wrCmd(lev);
}

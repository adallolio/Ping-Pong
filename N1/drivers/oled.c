// Alberto Dallolio - OLED

#include "oled.h"
#include "fonts.h"
#include "uart.h"
#include "../misc/memory_mapping.h"

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Start addresses for the OLED
volatile uint8_t *oled_cmd = (uint8_t *) OLED_COMMAND_ADDRESS;
volatile uint8_t *oled_data = (uint8_t *) OLED_DATA_ADDRESS;

// to be tested
static FILE oled_stdout = FDEV_SETUP_STREAM(OLED_print_char, NULL, _FDEV_SETUP_WRITE);
static uint8_t line = 0;



void OLED_init() {

	OLED_wrCmd(DISPLAY_OFF);
	OLED_wrCmd(SEGMENT_REMAP);
	OLED_wrCmd(SET_COM_PIN_HW_CONFIG);        // Common  pads  hardware:  alternative
	OLED_wrCmd(0x12);						  // 0x12 = bx00010010, meaning A[5] = 0, A[4] = 1
	OLED_wrCmd(SET_COM_OUT_SCAN_DIR);		  // Common output scan direction:com63~com0
	OLED_wrCmd(SET_MULTIPLEX_RATIO);
	OLED_wrCmd(0x3f);						  // Multiplex  ratio  mode: 63
	OLED_wrCmd(SET_DISPLAY_CLK_DIV_RATIO);    // Display divide ratio/osc. freq. mode
	OLED_wrCmd(0x80);
	OLED_wrCmd(SET_CONTRAST_CONTROL);
	OLED_wrCmd(0x50);
	OLED_wrCmd(SELECT_IREF);				  // Master configuration cmd - select external or internal Iref
	OLED_wrCmd(0x00);						  // 0x00: external, 0x01: internal
	OLED_wrCmd(ENTIRE_DISPLAY_ON);			  // Out RAM content
	OLED_wrCmd(SET_NORMAL_DISPLAY);
	OLED_wrCmd(DISPLAY_ON);
	OLED_wrCmd(SET_PRECHARGE_PERIOD);
	OLED_wrCmd(0x21);						  // Period!
	OLED_wrCmd(SET_MEMORY_ADDRESSING_MODE);
	OLED_wrCmd(HORIZONTAL_ADDR_MODE);
	OLED_wrCmd(SET_VCOM_DESELECT_LVL);
	OLED_wrCmd(0x30);
	
	OLED_reset();
	
	// Set display offset
	OLED_wrCmd(0xD3);
	// OLED_wrCmd(0x20);
	OLED_wrCmd(0x00);
}

void OLED_wrCmd(int8_t cmd) {
	*oled_cmd = cmd;
}

void OLED_wrData(uint8_t data) {
	*oled_data = data;
}

char OLED_rdData() {
	return 0x00; // null?
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
		OLED_write_command(SET_COLUMN_ADDRESS);
		OLED_write_command(col);
		OLED_write_command(0x7F);
	}
}

void OLED_pos(uint8_t l, uint8_t c) {
	OLED_gotoLine(l);
	OLED_gotoCol(c);
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

void OLED_reset() {
	// Clear every line and go home!
	for (uint8_t line = 0; line < NUM_LINES; line++){
		OLED_clLine(line);
	}
	
	OLED_goHome();
}

void OLED_setCont(uint8_t lev) {
	OLED_wrCmd(SET_CONTRAST_CONTROL);
	OLED_wrCmd(lev);
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

void OLED_print_char(char ch) {
	// THINK!!!!

	if ((ch) == '\n'){
		OLED_pos((line + 1), 0);
	}
	else{
		for (int i = 0; i < 5; i++){
			OLED_write_data(pgm_read_byte(&font5[character - ' '][i]));
		}
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

void OLED_print_arrow() {
	OLED_wrData(0b00011000);
	OLED_wrData(0b00011000);
	OLED_wrData(0b00011000);
	OLED_wrData(0b00011000);
	OLED_wrData(0b00011000);
	OLED_wrData(0b11111111);
	OLED_wrData(0b01111110);
	OLED_wrData(0b00111100);
	OLED_wrData(0b00011000);
	OLED_wrData(0b00000000);
}

// Fuctions for pixels.

void OLED_drPix(int x, int y) {
	OLED_gotoCol(x);
	OLED_gotoLine(y/NUM_LINES); // not sure: OLED_gotoLine(y);
	OLED_wrData((1 << (y % NUM_LINES)) | OLED_rdData()); // OLED_wrData((1 << y) | OLED_rdData());
}

int OLED_rdPix(int x, int y) {
	OLED_gotoCol(x);
	OLED_gotoLine(y/NUM_LINES); // OLED_gotoLine(y);
	return ((1 << (y % NUM_LINES)) & OLED_rdData()); // return ((1 << y) & OLED_rdData());
}

void OLED_clPix(int x, int y) {
	OLED_gotoCol(x);
	OLED_gotoLine(y/NUM_LINES); // OLED_gotoLine(y);
	OLED_wrData(~(1 << (y % NUM_LINES)) & OLED_rdData()); // OLED_wrData(~(1 << y) & OLED_rdData());
}

void OLED_invPix(int x, int y) {
	OLED_gotoCol(x);
	OLED_gotoLine(y/NUM_LINES); // OLED_gotoLine(y);
	OLED_wrData((1 << (y % NUM_LINES)) ^ OLED_rdData()); // XOR. OLED_wrData((1 << y) ^ OLED_rdData());
}

void OLED_drLine(int x1, int y1, int x2, int y2) {
	
	if ((y2-y1)<=(x2-x1)){
		float m = (float)(y2-y1)/(float)(x2-x1); // slope.
		for (int x = 0; x < (x2-x1); x++){
			int y = (int)(m*x+0.5);
			OLED_drPix(x1+x,y1+y);
		}
	} else {
		float m = (float)(x2-x1)/(float)(y2-y1); // slope.
		for (int y = 0; y < (y2-y1); y++){
			int x = (int)(m*y+0.5);
			OLED_drPix(x1+x,y1+y);
		}
	}
}

void OLED_drCircle(int x, int y, int r) {
	for (i=0; i<=2*r; i++)
    {
        for (j=0; j<=2*r; j++)
        {
            double dist = sqrt((double)(i-r)*(i-r) + (j-r)*(j-r));
            if (dist>r-0.5 && dist<r+0.5)
            {
                printf("*");
            }
            else
            { printf(" ");}
        }
        printf("\n");
    }
}
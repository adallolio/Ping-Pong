// MCP2515.c
// Richard McCrae-Lauba

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
//#include "../misc/bit_manipulation.h"
#include "../misc/memory_mapping.h"
#include "../misc/macros.h"
#include "spi.h"
#include "mcp2515.h"


uint8_t mcp2515_Init(void) {
	volatile uint8_t value;
	
	SPI_Init();             //Initialize SPI driver
	mcp2515_reset();        //Reset the CAN controller
	
	//Self-test
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in configuration mode after reset!\r\n");
		
        return 1;
	}
	
	return 0;
}


void mcp2515_N1_select(void) {
    // Select CAN-controller, pull CS low
    PORTB &= ~(1 << PB4);
}


void mcp2515_N1_deselect(void) {
    // Deselect CAN-controller, pull CS high
    PORTB |= (1 << PB4);
}


int mcp2515_read(uint8_t address) {
    uint8_t rec;
    mcp2515_N1_select();
    SPI_Transcieve(MCP_READ);         // Send read instruction
    SPI_Transcieve(address); // Send address
    rec = SPI_Transcieve(0);
    mcp2515_N1_deselect();
    
    return rec;
}


void mcp2515_write(uint8_t address, uint8_t data) {
    mcp2515_N1_select();
    SPI_Transcieve(MCP_WRITE);      // Send write instruction
    SPI_Transcieve(address);        // Send address to write to
    SPI_Transcieve(data);            // Send atleast one byte of data
    mcp2515_N1_deselect();
}


uint8_t mcp2515_reset(void) {
    mcp2515_N1_select();
    SPI_Transcieve(MCP_RESET);      // Send reset  instruction
    mcp2515_N1_deselect();
    
    return 0;
}


uint8_t mcp2515_request_to_send(uint8_t buffer) {
    mcp2515_N1_select();
    SPI_Transcieve(buffer);
    mcp2515_N1_deselect();
}


uint8_t mcp2515_read_status(void) {
    uint8_t status;
    
    mcp2515_N1_select();
    SPI_Transcieve(MCP_READ_STATUS); // Send read status command byte, return status
    status =  SPI_Transcieve(0);
    mcp2515_N1_deselect();
    
    return status;
}


int mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
    mcp2515_N1_select();
    SPI_Transcieve(MCP_BITMOD);       // Send bit modify command to MCP2515
    SPI_Transcieve(address);          // send register address
    SPI_Transcieve(0xFF);
    //SPI_Transcieve(mask);             // send mask byte. This mask decides which bits in REG to change. "1" allows change, "0" does not
    SPI_Transcieve(data);             // send data byte. Data determines the values of the register to be changed to. 1= set, 0=clear
    mcp2515_N1_deselect();

    return 0;
}
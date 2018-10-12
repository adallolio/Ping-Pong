// Richard McCrae-Lauba, MCP2515

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "../misc/memory_mapping.h"
#include "../misc/macros.h"
#include "spi.h"
#include "can.h"
#include <avr/interrupt.h>


uint8_t mcp2515_init()
{
    uint8_t value;
    SPI_Init(); // Initialize SPI
    mcp2515_reset(); // Send reset-command
    // Self-test
    mcp2515_read(MCP_CANSTAT, &value);
    if ((value & MODE_MASK) != MODE_CONFIG) {
        printf(”MCP2515 is NOT in configuration mode after reset!\n”);
        return 1;
    }

    // More initialization

    return 0;
}

uint8_t mcp2515_read(uint8_t address)
{
    uint8_t result;
    PORTB &= ~(1<<PB7); // Select CAN-controller
    SPI_Transcieve(MCP_READ); // Send read instruction
    result = SPI_Transcieve(address); // Send address
    PORTB |= (1<<PB7); // Deselect CAN-controller
    return result;
}

mcp2515_write()






mcp2515_request_to_send()
mcp2515_bit_modify()
mcp2515_reset()
mcp2515_read_status()
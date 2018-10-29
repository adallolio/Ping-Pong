// Richard McCrae-Lauba, SPI - Node 2

#include "../misc/bit_manipulation.h"
#include "../misc/macros.h"
#include "spi.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdint.h>



int SPI_Init(void) {
    /* Set MOSI, SCK, SS output, all others input */
    DDRB |= (1 << DDB2)|(1 << DDB1)|(1 << DDB0) | (1 << DDB7);
    
    // Enable SPI, Master, set clock rate
    SPCR = (1 << MSTR)|(1 << SPR0);
    
    SPCR |= (1 << SPE);

    /* Clock polarity = 0, clk phase = 0 */
    SPCR &= ~(1 << CPOL);
    SPCR &= ~(1 << CPHA);

    return 0;
}

//Function to send and receive data for both master and slave
uint8_t SPI_Transcieve(uint8_t data) {
    // Load data into the buffer
    SPDR = data;

    /* Wait until transmission complete. The SPI Interrupt 
    Flag is set whenever a serial transfer is complete */
    while(!(SPSR & (1<<SPIF) ));
 
    // Return received data
    return(SPDR);
}


// SPI Transmission/reception complete ISR
/*
char ISR(SPI_STC_vect)
{
    // Code to execute
    // whenever transmission/reception
    // is complete.
    // Do I need to disable global interrupts here?
    cli();
    data = SPDR;
    return(data);
    sei();
}
*/
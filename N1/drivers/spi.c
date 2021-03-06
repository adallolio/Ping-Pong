// Richard McCrae-Lauba, SPI

//#include "../misc/bit_manipulation.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "../misc/memory_mapping.h"
#include "../misc/macros.h"
#include "spi.h"



int SPI_Init(void) {
    /* Set MOSI, SCK, SS output, all others input */
    DDRB = (1<<PB5)|(1<<PB7)|(1<<PB4);
    
    /* Enable SPI, Master, set clock rate fck/16 (this is adjustable, consider) */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    //|(1<<SPIE)
    /* Clock polarity = 0, clk phase = 0 */
    SPCR &= ~(1 << CPOL);
    SPCR &= ~(1 << CPHA);

    return 0;
}

//Function to send and receive data for both master and slave
uint8_t SPI_Transcieve(uint8_t data) {
    // Load data into the buffer
    SPDR = data;
    //printf("SPI data out: %d\r\n",data);

    /* Wait until transmission complete. The SPI Interrupt 
    Flag is set whenever a serial transfer is complete */
    while(!(SPSR & (1<<SPIF) ));
 
    //printf("SPI data in: %d\r\n",SPDR);
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
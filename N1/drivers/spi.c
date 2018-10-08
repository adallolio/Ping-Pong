// Richard McCrae-Lauba, SPI

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "../misc/memory_mapping.h"
#include "../misc/macros.h"
#include "spi.h"
//#include <avr/interrupt.h>


void SPI_init(void)
{
    /* Set MOSI, SCK, SS output, all others input */
    // DDRB = (1<<DDB5)|(1<<DDB7);
    DDRB |= (1 << DDB5);
    DDRB |= (1 << DDB7);
    /* SS */
    DDRB |= (1 << DDB4);
    /* Enable SPI, Master, set clock rate fck/16 (this is adjustable, consider) */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    /* Clock polarity = 0, clk phase = 0 */
    SPCR &= ~(1 << CPOL);
    SPCR &= ~(1 << CPHA);

    /* Enable global interrupts */
    //sei();
}

unsigned char spi_tranceive(char cData)
{
    /* Drive slave select pin low */
    DDRB &= ~(1 << DDB4);

    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    //while(!(SPSR & (1<<SPIF)));
    while(!(SPSR & (1 << SPIF)))

    /* Return data register */
    return SPDR;

    /* set SS pin */
    DDRB |= (1 << DDB4);
}

// char SPI_read(void)
// {
//     /* Wait for reception complete */
//     //while(!(SPSR & (1<<SPIF)));
//     loop_until_bit_is_set(SPSR,SPIF)
//     /* Return data register */
//     return SPDR;
// }


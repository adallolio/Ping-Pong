// GAME.c - Richard McCrae-Lauba

#include "../misc/macros.h"
#include "../misc/bit_manipulation.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

void game_Init(){
    //set correct bits as inputs, init to LOW
    clear_bit(DDRL,PL6); //fast
	clear_bit(DDRGL,PG0); //normal
    clear_bit(PORTL,PL6);
    clear_bit(PORTG,PG0);

}

void gameplay(){
    // Read game speed bits on PG0 and PL6, set motor speed accordingly and start game
    if ((PINL & (1 << PL6)){
        // set motor fast


    }
}
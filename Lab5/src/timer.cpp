/*
Lab 5 Group 15
Nickolas Murachanian, Jalea Dashiell, Braden Means
4/27/2020


Creates a repeatable 1ms timer using timer1 on the Arduino Mega AT2560 board
*/

#include "timer.h"
#include <avr/io.h>


void initTimer1(){
//Setting timer 1 into CTC mode 
TCCR1A &= ~( 1 << WGM10 );
TCCR1A |=  ( 1 << WGM11 );
TCCR1B &= ~( 1 << WGM12 );
OCR1A = 250; //set OCR1A to 250 to get a 1ms delay timer1
}


void delayMs(unsigned int delay){
    int count = 0;

    
    while (count < delay){ // iterates loop for number of desired mS to delay for
        TIFR1 |= (1 << OCF1A);
        TCNT1 = 0;
        TCCR1B |= (1 << CS10) | (1 << CS11);
        TCCR1B &= ~(1 << CS12);

        //while flag is down do nothing
        while (! (TIFR1 & (1 << OCF1A)));
        //exits when flag is up and turn clock off
        count++;

    }
}

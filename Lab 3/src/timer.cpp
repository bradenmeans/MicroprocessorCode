// Author: Braden Means
// Net ID: bradenmeans
// Date: 3/25/20
// Assignment: Lab 3
//----------------------------------------------------------------------//

#include "timer.h"

/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
    // CTC mode enabled
    TCCR1A &= ~(1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B &= ~(1 << WGM13);
}

/* This delays the program an amount specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
    unsigned int count = 0;

    TCCR1B &= ~((1 << CS12)| (1 << CS10));
    TCCR1B |=  (1 << CS11);
    //OCR1A = 2; // Prescaler of 8
    OCR1AH = 0;
    OCR1AL = 2;
    TIFR1 |= (1<<OCR1A);
    TCNT1 = 0;


    while (count < delay) {
        if(TIFR1 & (1<<OCF1A)) {
            count++;
            TIFR1 |= (1<<OCF1A);
        }
    } 
}
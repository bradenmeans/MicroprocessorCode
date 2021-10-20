// Description: This file implements functions that utilize the timers
//----------------------------------------------------------------------//

#include "timer.h"

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
TCCR0A &= ~( 1 << WGM00 ); //Place 0 into WGM00 & WGM02, then a 1 into WGM01
TCCR0A |=  ( 1 << WGM01 );
TCCR0B &= ~( 1 << WGM02 );
TCCR0B |= (1<<CS00) | (1<<CS01); 
TCCR0B &= ~(1<<CS02); // Prescaler = 64
OCR0A = 250; // OCR0A = (Td * freq)/ Prescaler
}

// Delay for 1ms
void delayMs(unsigned int delay){
    unsigned int count = 0;

    TCNT0 = 0;
    TIFR0 |=  (1 << OCF0A);
    while (count < delay){
        if (TIFR0 &  (1 << OCF0A)) {
            count++;
            TIFR0 |=  (1 << OCF0A);
        }
    }
}

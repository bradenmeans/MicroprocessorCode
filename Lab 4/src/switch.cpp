#include "switch.h"

void initSwitchPE5() {
    //Setup for ISR
    EICRB |= (ISC50);
    EICRB &= ~(ISC51);
    EIMSK |= (1 << INT5);

    DDRE &= ~(1 << DDE5); // Pin 3 as input
    PORTE |= (1 << PORTE5);
}
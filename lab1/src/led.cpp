#include <avr/io.h>
#include "led.h"

void initLED() {
    DDRG |= (1 << DDG5); 
    DDRE |= (1 << DDE3);
    DDRH |= (1 << DDH3);
    DDRH |= (1 << DDH4);
    DDRH |= (1 << DDH5);
    DDRH |= (1 << DDH6);
    DDRB |= (1 << DDB4);
    DDRB |= (1 << DDB5); 
    /*
    PORTG |= (1 << PORTG5);
    PORTE |= (1 << PORTE3);
    PORTH |= (1 << PORTH3);
    PORTH |= (1 << PORTH4);
    PORTH |= (1 << PORTH5);
    PORTH |= (1 << PORTH6);
    PORTB |= (1 << PORTB4);
    PORTB |= (1 << PORTB5); */

}

void testLED(int led) {
    switch(led) {
        case 4:
        case 11:
            turnOffLed(5);
            turnOffLed(6);
            turnOffLed(7);
            turnOffLed(8);
            turnOffLed(9);
            turnOffLed(10);
            turnOnLed(4);
            turnOnLed(11);
            break;
        case 5:
        case 10:
            turnOffLed(4);
            turnOffLed(6);
            turnOffLed(7);
            turnOffLed(8);
            turnOffLed(9);
            turnOffLed(11);
            turnOnLed(5);
            turnOnLed(10);
            break;
        case 6:
        case 9:
            turnOffLed(5);
            turnOffLed(4);
            turnOffLed(7);
            turnOffLed(8);
            turnOffLed(11);
            turnOffLed(10);
            turnOnLed(6);
            turnOnLed(9);
            break;
        case 7:
        case 8:
            turnOffLed(5);
            turnOffLed(6);
            turnOffLed(4);
            turnOffLed(11);
            turnOffLed(9);
            turnOffLed(10);
            turnOnLed(7);
            turnOnLed(8);
            break;

    }
}

void turnOnLed(int led) {
    switch(led) {
        case 4:
            PORTG |= (1 << PORTG5);
            break;
        case 5:
            PORTE |= (1 << PORTE3);
            break;
        case 6:
            PORTH |= (1 << PORTH3);
            break;
        case 7: 
            PORTH |= (1 << PORTH4);
            break;
        case 8: 
            PORTH |= (1 << PORTH5);
            break;
        case 9: 
            PORTH |= (1 << PORTH6);
            break;
        case 10: 
            PORTB |= (1 << PORTB4);
            break;
        case 11:
            PORTB |= (1 << PORTB5);
            break;
    
    }
    

}

void turnOffLed(unsigned int led) {
        switch(led) {
        case 4:
            PORTG &= ~(1 << PORTG5);
            break;
        case 5:
            PORTE &= ~(1 << PORTE3);
            break;
        case 6:
            PORTH &= ~(1 << PORTH3);
            break;
        case 7: 
            PORTH &= ~(1 << PORTH4);
            break;
        case 8: 
            PORTH &= ~(1 << PORTH5);
            break;
        case 9: 
            PORTH &= ~(1 << PORTH6);
            break;
        case 10: 
            PORTB &= ~(1 << PORTB4);
            break;
        case 11:
            PORTB &= ~(1 << PORTB5);
            break;
        }
}
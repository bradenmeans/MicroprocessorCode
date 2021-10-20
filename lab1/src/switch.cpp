#include <avr/io.h>

void initSwitch () {
    DDRA &= ~(1 << DDA0);
    PORTA |= (1 << PORTA0);
}
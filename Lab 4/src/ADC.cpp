#include "ADC.h"

void initADC() {
    //Set voltage references to be AVCC
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    //ADLAR = 0 (RIGHT JUSTIFIED)
    ADMUX &= ~(1 << ADLAR);

    //Set ADC0 as single-ended input with MUX[5:0] = 0b000000
    ADMUX &=  ~(1 << MUX0);
    ADMUX &=  ~(1 << MUX1);
    ADMUX &=  ~(1 << MUX2);
    ADMUX &=  ~(1 << MUX3);
    ADMUX &=  ~(1 << MUX4);
    ADCSRB &= ~(1 << MUX5);

    ADCSRB &= ~(1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0);
    
    //Enable auto-triggering and turn-on ADC
    ADCSRA |= ((1 << ADATE) |(1 << ADEN));

    //Set the pre-scaler to 128
    //ADC clock frequency is 16 Mhz divided by pre-scaler = 125KHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    //Disable ADC0 pin digital input - pin A0 on board
    DIDR0 |= (1 << ADC0D);
  
    //Start the first conversion
    ADCSRA |= (1 << ADSC);
}
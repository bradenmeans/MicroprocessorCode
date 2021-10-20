#include "PWM.h"

void initPWMTimer3() {
  
  /* Waveform generation mode bit from Table 17-2
  Sets it to Fast PWM 10bit with TOP 0x03FF */
  TCCR3A |= (1<<WGM30) | (1<<WGM31);
  TCCR3B |= (1<<WGM32);
  TCCR3B &= ~(1<<WGM33);

  //Table 17-4, Fast PWM non-inverting mode
  TCCR3A &= ~(1<<COM3A0); 
  TCCR3A |= (1<<COM3A1);

  //Table 17-6, set prescaler to 1
  TCCR3B |= (1<<CS30);
  TCCR3B &= ~(1<<CS31);
  TCCR3B &= ~(1<<CS32);

  //To use 0C3A E3 Pin5, we set E3 to output
  DDRE |= (1<<DDE3);
}

void changeDutyCycle(unsigned int result) {
    OCR3A = result;
}


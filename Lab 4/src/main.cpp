// Author:         
// Net ID:         
// Date:           
// Assignment:     Lab 4
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//

  #include <Arduino.h>
  #include <avr/io.h>
  #include <avr/interrupt.h>
  #include "ADC.h"
  #include "PWM.h"
  #include "switch.h"
  #include "timer.h"

  typedef enum stateEnum_enum {
    wait_press, debounce_press, wait_release, debounce_release
  } stateType;

  volatile stateType state = wait_press;
  
  boolean on = true;
  

int main(){
  DDRE |= (1 << PORTE4);
  PORTE |= (1 << PORTE4);

  initADC();
  initPWMTimer3();
  initSwitchPE5();
  initTimer0();
  sei();
  unsigned int result = 0;

  while(1){
      switch(state) {
      case wait_press:
      break;

      case debounce_press:
      delayMs(1);
      state = wait_release;
      break;

      case wait_release:
      break;

      case debounce_release:
      delayMs(1);
      state = wait_press;
    } 

    result = ADCL;
    result += ((unsigned int) ADCH) << 8;

    if (on) {
      PORTE |= (1 << PORTE4);
      changeDutyCycle(result);
    }
    else {
      PORTE &= ~(1 << PORTE4);
    }

  }

  return 0;
}

ISR(INT5_vect) {
  if (state == wait_press) {
    state = debounce_press;
  }
  else if (state == wait_release) {
    if (on) {
      on = false;
      
    }
    else {
      on = true;
    }
    state = debounce_release;
  }
}
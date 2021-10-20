// Author: Braden Means        
// Net ID: bradenmeans         
// Date: 2/5/2020          
// Assignment:     Lab 1
//
// Description: Digital Input and Output

// Requirements: Produce LED pattern given to us in the lab requirements
//----------------------------------------------------------------------//

#include "led.h"
#include "switch.h"
#include <util/delay.h>
#include <avr/io.h>
#define LONG_DELAY 1000
#define SHORT_DELAY 100


int main(){

  initLED(); // initialize the LED
  initSwitch(); // initialize switch

  int ledNum = 4;
  int count = 0;

  while(1){
    // Switch not pressed
    if (PINA & (1 << PINA0)) {
      if (count != 0 && ledNum == 4) {
        ledNum++;
        testLED(ledNum);
        _delay_ms(SHORT_DELAY);
      }
      else {
        testLED(ledNum);
        _delay_ms(SHORT_DELAY);

      }
    }
    // Switch pressed
    else {
        testLED(ledNum);
        _delay_ms(LONG_DELAY);
    }
    if (ledNum == 7) {
      ledNum++;
    }
    if (ledNum == 11) {
      ledNum = 4;
      count++;
    }
    else {
      ledNum++;
    }
  }

  return 0;
}

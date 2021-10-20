// Name: Braden Means
// NetID: bradenmeans
// Date: 2/22/2020
// Assignment: Lab 2

//Description: Timers

// Requirements: Create a timer that counts to 15 in binary through LEDs. This timer has two modes: fast and slow.

#include <Arduino.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "led.h"
#include "switch.h"

#define SHORT_DELAY 100
#define LONG_DELAY 200

typedef enum stateEnum_enum {
  wait_press, debounce_press, wait_release, debounce_release
  } stateType;

  volatile stateType state = wait_press;

int main() {
  unsigned char ledNum = 0;
  boolean fast = false;

  initLED();
  initSwitchPB3();
  initTimer0();
  sei();

  // Speed of timer
  while(1) {
    if (!fast) {
      turnOnLEDWithChar(ledNum);
      delayMs(SHORT_DELAY);
    }
    else {
      turnOnLEDWithChar(ledNum);
      delayMs(LONG_DELAY);
    }

    // State machine
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
        if (!fast) {
          fast = true;
        }
        else if (fast) {
          fast = false;
        }
        state = wait_press;
      break;
    }
    // LED resets at 15
       if (ledNum == 15) {
        ledNum = 0;
      }
      else {
        ledNum++;
      }
  }
}

// ISR so count keeps current count when button pressed.
ISR(PCINT0_vect) {
  if(state == wait_press) {
    state = debounce_press;
  }
  else if (state == wait_release) {
    state = debounce_release;
  }
}
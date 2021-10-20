// Author: Braden Means
// Net ID: bradenmeans
// Date: 3/25/20
// Assignment: Lab 3
//
// Description: This code interfaces with an LCD, allowing the user to input
// a string and have it be displayed onto the LCD.
//
// Requirements: Write a string to an LCD. Must initialize the LCD
// and using both four and eight bit commands. Also includes 
// the usage of a 1 microsecond timer, using Timer 1 in CTC mode.
//----------------------------------------------------------------------//

#include <avr/io.h>
#include "lcd.h"
#include "timer.h"


int main(){

  // Initialze timer, LCD, and write Hello!
  initTimer1();
  initLCD();
  moveCursor(0, 4);
  writeString("Hello!");

  /*
  * No state machine this time around.
  */
  while(1){

  }

  return 0;
}
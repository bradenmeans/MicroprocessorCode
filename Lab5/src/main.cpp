/*
Lab 5 Group 15
Nickolas Murachanian, Jalea Dashiell, Braden Means
4/27/2020


This program uses the Arduino Mega AT2560 board and the ADX1345 accelerometer to create a circuit that uses I2C communication
to read X, Y, and Z data from the accelerometer. The data is then printed to the terminal using Serial commands.

This file initializes I2C communications and the timer, enables measurements from the accelerometer, and infinitely loops printing the X, Y, and Z data every second.
*/

#include"i2c.h"
#include "timer.h"
#include "Arduino.h"
#include <avr/io.h>
//define addresses for slave address, wakeup command, power control register, and X/Y/Z registers
#define SLA 0x53
#define WAKEUP 0x08
#define PWR_MGMT 0x2D
#define SL_MEMA_XAX_HIGH  0x33
#define SL_MEMA_XAX_LOW   0x32
#define SL_MEMA_YAX_HIGH  0x35
#define SL_MEMA_YAX_LOW   0x34
#define SL_MEMA_ZAX_HIGH  0x37
#define SL_MEMA_ZAX_LOW   0x36
int main(){

 initTimer1();   //turn on timer and enable serial usage
Serial.begin(9600);

sei(); // enable interrupts
initI2C(); // enable I2C communications

signed int Xval = 0; // define X/Y/Z variables for data retrieval and printing
float Xc = 0.00;
signed int Yval = 0;
float Yc = 0.00;
signed int Zval = 0;
float Zc = 0.00;


StartI2C_Trans(SLA); // bring the device out of standby mode and into measurement mode
write(PWR_MGMT); // register 0x2D
write(WAKEUP); //sets measurement bit to 1, all others to 0
StopI2C_Trans();



while (1){
delayMs(1000); // 1sec delay that inserts one second between each data read




Read_from(SLA, SL_MEMA_XAX_HIGH); // fetch X data
Xval = Read_data();
Read_from(SLA, SL_MEMA_XAX_LOW);
Xval = (Xval << 8) | Read_data(); //append high and low X data
Xc = float(Xval);

Read_from(SLA, SL_MEMA_YAX_HIGH); // fetch Y data
Yval = Read_data();
Read_from(SLA, SL_MEMA_YAX_LOW);
Yval = (Yval << 8) | Read_data(); // append high and low Y data
Yc = float(Yval);

Read_from(SLA, SL_MEMA_ZAX_HIGH); // fetch Z data
Zval = Read_data();
Read_from(SLA, SL_MEMA_ZAX_LOW);
Zval = (Zval << 8) | Read_data(); // append high and low Z data
Zc = float(Zval);

Serial.print("\n\n\nX = "); // serial commands to print out the X/Y/Z measurements
Serial.print(Xc);
Serial.print("\nY = ");
Serial.print(Yc);
Serial.print("\nZ = ");
Serial.print(Zc);
StopI2C_Trans();
}

return 0;
}
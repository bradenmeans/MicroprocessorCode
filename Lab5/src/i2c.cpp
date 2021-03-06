/*
Lab 5 Group 15
Nickolas Murachanian, Jalea Dashiell, Braden Means
4/27/2020


Contains all functions for I2C communications for use with the ADX1345 accelerometer chip

Allows for initialization, reading, and writing using I2C protocols
*/

#include "i2c.h"
#include <avr/io.h>
#include "Arduino.h"


#define wait_for_completion while(!(TWCR & (1 << TWINT)));
void initI2C() { //initializes I2C communications
  
  PRR0 &= ~(1<<PRTWI);  // wake up I2C module on AT2560 power management register
  TWSR |= (1 << TWPS0);  // prescaler power = 1
  TWSR &= ~(1 << TWPS1); // prescaler power = 1 
  //πππ΅π=((πΆππ πΆππππ πππππ’ππππ¦)/(ππΆπΏ πππππ’ππππ¦)β16)/(2βγ(4)γ^ππππ )
  TWBR = 0x12; // bit rate generator = 100k 

  TWCR |= (1 << TWINT )| (1 << TWEN); // enable two wire interface

}

void StartI2C_Trans(unsigned char SLA) { //Begins I2C communications after I2C has been initialized
// this function initiates a start condition and calls slave device with SLA
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // clear TWINT, intiate a start condition and enable
  wait_for_completion;
  TWDR = (SLA << 1); // slave address + write bit '0'
  TWCR = (1<<TWINT)|(1<<TWEN);  // trigger action:clear flag and enable TWI
  wait_for_completion;
}

void StopI2C_Trans() { // halts I2C comms
  // this function sends a stop condition to stop I2C transmission

  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //trigger action:  send stop condition

}

void write(unsigned char data){//Writes to a given register or address
  // this function loads the data passed into the I2C data register and transmits
  TWDR = data; //load data into TWDR register
  TWCR = (1<<TWINT)|(1<<TWEN);  // trigger action:  clear flag and enable TWI
  wait_for_completion;
}

void Read_from(unsigned char SLA, unsigned char MEMADDRESS){ //retrieves data from slave chip to be retrieved using the Read_data() function
  // this function sets up reading from SLA at the SLA MEMADDRESS 

  StartI2C_Trans(SLA);
 
  write(MEMADDRESS);
  
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // restart to switch to read mode
  wait_for_completion;
  TWDR = (SLA << 1) | 0x01; // 7 bit address for slave plus read bit
  TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWEA);// trigger with master sending ack
  wait_for_completion;
  TWCR = (1<< TWINT) | (1 << TWEN);  // master can send a nack now
  wait_for_completion;
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Stop condition
// after this function is executed the TWDR register has the data from SLA that Master wants to read
}

unsigned char Read_data() // Returns the last byte  from the data register
{

  return TWDR;
}
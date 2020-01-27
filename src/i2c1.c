
#include <xc.h>
#include "hardware.h"

#include <stdio.h>
#include <stdint.h>
#include "i2c1.h"





void i2c1_init(void)
{
  //set up the pins
  
  I2C1CONbits.ON = 0; //shut down the I2C module to allow us to configure it
  
  //these bits are valid in slave mode only
  I2C1CONbits.PCIE = 0; //stop detection interrupts are disabled
  I2C1CONbits.SCIE = 0; //start detection interrupts are disabled
  I2C1CONbits.BOEN = 1; //ignore buffer overwrite
  I2C1CONbits.SBCDE = 0; //slave bus collision interrupts are disabled
  I2C1CONbits.STRICT = 0; //strict address rule disabled
  I2C1CONbits.GCEN = 0; //general call address disabled
  
  //SMBUS 2.0 support, this needs to be 1
  I2C1CONbits.SDAHT = 0; //minimum of 100 ns hold time on SDAx after falling SCLx
  I2C1CONbits.SMEN = 0; //disable SMBus input level
  
  //general
  I2C1CONbits.SIDL = 0; //continue in idle mode
  I2C1CONbits.A10M = 0; //address register is 7 bit slave address
  I2C1CONbits.DISSLW = 0; //slew rate control enabled for high speed mode 400kHz
  I2C1CONbits.STREN = 0; //stretching is not enabled
  
  I2C1CONbits.ACKDT = 0; //ack is sent
  I2C1CONbits.ACKEN = 1; //ack sequence enabled (in master mode)
  I2C1CONbits.RCEN = 1; //enabled rx mode for i2c
  I2C1CONbits.PEN = 0; //stop condition is idle
  I2C1CONbits.RSEN = 0; //restart condition is idle
  I2C1CONbits.SEN = 0; //start condition is idle
  
  
  //release control bit
  I2C1CONbits.SCLREL = 0; //clock stretching
  
  //clear status register
  I2C1STAT = 0;
  
  //slave address register
  I2C1ADD = 0;
  
  //address mask register
  I2C1MSK = 0xFFFFFFFF;
  
  //clear status register
  I2C1BRG = 27; //set for 400 kHz operation
  
  I2C1CONbits.ON = 1; //shut down the I2C module to allow us to configure it
}


#include "application.h"
#include "hardware.h"
#include "mb85rs64v.h"

#include <stdio.h>
#include <stdbool.h>

#include "debug.h"

//static uint32_t readDeviceID(void);
//static uint32_t readStatusRegister(void);

static void dumpFRAM(void);
static void fillFRAM(void);

//static void writeEnable(bool enable);
//static void write8(uint32_t address, uint8_t value);


void FRAM_init(void)
{
    
    //fillFRAM();
    //dumpFRAM();
    FRAM_HOLD = 1; //SPI command hold is off (active low)
  
}

void FRAM_service(void)
{
    //readStatusRegister();
    readDeviceID();
    //dumpFRAM();
}


void writeEnable(bool enable)
{
  FRAM_CS = 0; //deselect the FRAM (active low)
  FRAM_WP = 1; //deactivate the write protect
  
  if(enable)
  {
      SPI1_tx8(FRAM_OP_WREN);
      
      while(SPI1STATbits.SPIBUSY)
        {
            //wait while the SPI transmits
        }
  }
  else
  {
      SPI1_tx8(FRAM_OP_WRDI);
      while(SPI1STATbits.SPIBUSY)
        {
            //wait while the SPI transmits
        }
  }
  FRAM_CS = 1; //deselect the FRAM (active low)
  FRAM_WP = 0; //activate the write protect
}

void write8(uint32_t address, uint8_t value)
{
  writeEnable(true);
  
  //this function will write an 8 bit value to any address given as 16 bits
   
  FRAM_CS = 0; //select the FRAM (active low)
  FRAM_WP = 1; //disable write protect (active low)
 
  
  uint8_t addrH = (uint8_t) (((address & 0x0000FF00) >> 8));
  uint8_t addrL = (uint8_t) (address & 0x000000FF);
  
  uint32_t txPKT = 0xFFFFFFFF;
  
  txPKT = FRAM_OP_WRITE;
  txPKT <<= 8;
  
  txPKT += addrH;
  txPKT <<= 8;
  
  txPKT += addrL;
  txPKT <<= 8;
  
  txPKT += value;
  
  SPI1_tx32(txPKT);
  
  while(SPI1STATbits.SRMT != 1)
  {
      //wait for us to transmit
  }
  
  
//  while(SPI1STATbits.SPIBUSY)
//    {
//        //wait while the SPI transmits
//    }
  
  FRAM_CS = 1; //deselect the FRAM (active low)
  
  writeEnable(false);
  
}


void write_test_8(uint16_t address, uint8_t value)
{
  FRAM_CS = 0; //select the FRAM (active low)
  FRAM_WP = 1; //disable write protect (active low)
 
  SPI1_tx8_ret(FRAM_OP_WREN);
  
  
  uint8_t addrH = (uint8_t) (((address & 0xFF00) >> 8));
  uint8_t addrL = (uint8_t) (address & 0x00FF);
  
  uint32_t txPKT = 0xFFFFFFFF;
  
  txPKT = FRAM_OP_WRITE;
  txPKT <<= 8;
  
  txPKT += addrH;
  txPKT <<= 8;
  
  txPKT += addrL;
  txPKT <<= 8;
  
  txPKT += value;
  
  SPI1_tx32_ret(txPKT);
  
  //this will also re-lock the chip
  FRAM_CS = 1; //select the FRAM (active low)
  
}



uint8_t read_test_8(uint16_t address)
{
  uint8_t ret = 0xFF;
  
  //this function will write an 8 bit value to any address given as 16 bits
   
  FRAM_CS = 0; //deselect the FRAM (active low)
  
  uint8_t addrH = (uint8_t) (((address & 0xFF00) >> 8));
  uint8_t addrL = (uint8_t) (address & 0x00FF);
  
  uint32_t txPKT = 0xFFFFFFFF;
  
  txPKT = FRAM_OP_READ;
  txPKT <<= 8;
  
  txPKT += addrH;
  txPKT <<= 8;
  
  txPKT += addrL;
  txPKT <<= 8;
  
  txPKT += 0xFF;
  
  
  ret = (uint8_t)SPI1_tx32_ret(txPKT);
  
  
  
  FRAM_CS = 1; //deselect the FRAM (active low)
  
  return ret;
}





uint8_t byte_read_at_index(uint16_t index)
{
    //this function will issue an read command to the FRAM and return the data value
    FRAM_CS = 0; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on (active low)
    
    SPI1_tx8(FRAM_OP_READ);

    while(SPI1STATbits.SPIBUSY)
    {
        //wait while the SPI transmits
    }

    //the lowest 8 bits should contain our data now

    uint8_t data = (SPI1BUF & 0x000000FF);
    
    FRAM_CS = 1; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on
    
    return data;
}
uint8_t byte_write_at_index(uint16_t index, uint8_t data)
{
    //this function will issue an read command to the FRAM and return the data value
    FRAM_CS = 0; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on (active low)
    
     //we need to send the write enable FRAM command
    
    uint8_t txCode = FRAM_OP_WREN;

    SPI1_tx8(txCode);

    while(SPI1STATbits.SPIBUSY)
    {
        //wait while the SPI transmits
    }
    
    //now lets send the write command
    uint32_t txOpCode = FRAM_OP_WRITE;
    txOpCode <<= 16; //left shift this value by 16
    txOpCode += index;
    txOpCode <<= 8; //left shift so the value will be this:

    //|OPCODE|ADDRESS1|ADDRESS2|DATA
    txOpCode += data;

    SPI1_tx32(txOpCode);
    
    while(SPI1STATbits.SPIBUSY)
    {
        //wait while the SPI transmits
    }
    
    //this function will issue an read command to the FRAM and return the data value
    FRAM_CS = 1; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on (active low)
}


////////////////////////////////////////////////////////////////////////////////
// private functions
////////////////////////////////////////////////////////////////////////////////

//#define FRAM_WP   LATCbits.LATC3
//#define FRAM_CS   LATCbits.LATC4
//#define FRAM_HOLD LATCbits.LATC5

uint32_t readDeviceID(void)
{
    FRAM_CS = 0; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 0; //write protect off
    
    //this command requires 40 clocks from the SPI bus
    //8 to send the OPCODE
    //32 to rx the device id
    
    uint8_t txCode = FRAM_OP_RDID;
    
    SPI1_tx8_ret(txCode);
    
    uint32_t ret = (SPI1_tx32_ret(0));
    
    FRAM_CS = 1;
    
    return ret;
    
    
//    SPI1_tx8(txCode);
//    while(SPI1STATbits.SPIBUSY)
//    {
//        //wait while the SPI transmits
//    }
//    SPI1_tx32(0);
//    
//    //read 8 bits from SPI
//    
//    
//    
//    while(SPI1STATbits.SPIBUSY)
//    {
//        //wait while the SPI transmits
//    }
//    
//    uint32_t status = SPI1_rx32();
//    
//    FRAM_CS = 1; //select the chip (active low)
//    FRAM_HOLD = 1; //SPI command hold is off (active low)
//    FRAM_WP = 1; //write protect on
//    
//    printf("FRAM Device ID: %lu\r\n", status);
//    return status;
    
    
}

uint32_t readStatusRegister(void)
{
    FRAM_CS = 0; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 0; //write protect off
    
    //this command requires 16 clocks from the SPI bus
    //8 to send the OPCODE
    //8 to rx the status register
    
    SPI1_tx8_ret(FRAM_OP_RDSR);
    
    uint8_t ret = SPI1_tx8_ret(0xFF);
    
   
    FRAM_CS = 1; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on
    
    return (uint32_t) ret;

}

static void dumpFRAM(void)
{
    FRAM_CS = 0; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 0; //write protect on (active low)
    
    uint16_t address = 0;
    
    for(address = FRAM_ADDRESS_START; address < FRAM_ADDRESS_END; address++)
    {
        FRAM_CS = 0; //select the chip (active low)
        
        uint32_t txCode = FRAM_OP_READ;
  
        txCode <<= 16; //left shift it by 16 so we can get the opcode in the upper byte
        txCode += address;
    
        txCode <<= 8;
        
        SPI1_tx32(txCode);
        
        while(SPI1STATbits.SPIBUSY)
        {
            //wait while the SPI transmits
        }
        
        //the lowest 8 bits should contain our data now
        
        uint8_t data = (SPI1BUF & 0x000000FF);
        
        printf("0x%X: %lu\r\n", address, data);
        
        FRAM_CS = 1; //select the chip (active low)
        
        DelayUs(100);
    }
    
    FRAM_CS = 1; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on
    
}

static void fillFRAM(void)
{
     //we need to send the write enable FRAM command
        
        uint8_t txCode = FRAM_OP_WREN;
        
        SPI1_tx8(txCode);
        
        //now that this is complete, we can send data to write to the FRAM
    
    uint16_t address = 0;
    
    for(address = FRAM_ADDRESS_START; address < FRAM_ADDRESS_END; address++)
    {
 
        FRAM_CS = 0; //select the chip (active low)
        FRAM_HOLD = 1; //SPI command hold is off (active low)
        FRAM_WP = 1; //write protect on (active low)
              
        if(address = 0)
        {
            uint32_t txOpCode = FRAM_OP_WRITE;
            txOpCode <<= 16; //left shift this value by 16
            txOpCode += 0x0000;
            txOpCode <<= 8; //left shift so the value will be this:

            //|OPCODE|ADDRESS1|ADDRESS2|DATA
            txOpCode += address;

            SPI1_tx32(txOpCode);

            //for the first write command, we can send a 32 bit transmission
           
        }
        else //after the first address, we can just send it byte by byte
        {
           uint8_t txDataByte = (address & 0x00FF);
           SPI1_tx8(txDataByte);
           
           
        }
        
    }
    
    FRAM_CS = 1; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 0; //write protect on
    
}


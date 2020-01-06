

#include "application.h"
#include "hardware.h"
#include "mb85rs64v.h"

#include <stdio.h>

#include "debug.h"

static uint32_t readDeviceID(void);
static uint32_t readStatusRegister(void);
static void dumpFRAM(void);
static void fillFRAM(void);


void FRAM_init(void)
{
    
    //fillFRAM();
    //dumpFRAM();
    
}

void FRAM_service(void)
{
    //readStatusRegister();
    readDeviceID();
    //dumpFRAM();
}



uint8_t byte_read_at_index(uint16_t index)
{
    //this function will issue an read command to the FRAM and return the data value
    FRAM_CS = 0; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on (active low)
    
    uint32_t txCode = FRAM_OP_READ;

    txCode <<= 16; //left shift it by 16 so we can get the opcode in the upper byte
    txCode += index;

    txCode <<= 8;

    SPI1_tx32(txCode);

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

static uint32_t readDeviceID(void)
{
    FRAM_CS = 0; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on
    
    //this command requires 40 clocks from the SPI bus
    //8 to send the OPCODE
    //32 to rx the device id
    
    uint8_t txCode = FRAM_OP_RDID;
    
    SPI1_tx8(txCode);
    while(SPI1STATbits.SPIBUSY)
    {
        //wait while the SPI transmits
    }
    SPI1_tx32(0);
    
    //read 8 bits from SPI
    
    
    
    while(SPI1STATbits.SPIBUSY)
    {
        //wait while the SPI transmits
    }
    
    uint32_t status = SPI1_rx32();
    
    FRAM_CS = 1; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on
    
    printf("FRAM Device ID: %lu\r\n", status);
    return status;
    
    
}

static uint32_t readStatusRegister(void)
{
    FRAM_CS = 0; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 0; //write protect on
    
    //this command requires 16 clocks from the SPI bus
    //8 to send the OPCODE
    //8 to rx the status register
    
    uint16_t txCode = FRAM_OP_RDSR;
    txCode <<= 8; //left shift it by 8 so we can get the opcode in the upper byte
    
    SPI1_tx16(txCode);
    
    //read 8 bits from SPI
    
    uint32_t status = SPI1_rx8();
    
    while(SPI1STATbits.SPIBUSY)
    {
        //wait while the SPI transmits
    }
    
    FRAM_CS = 1; //select the chip (active low)
    FRAM_HOLD = 1; //SPI command hold is off (active low)
    FRAM_WP = 1; //write protect on
    
    printf("FRAM Status Register: %lu\r\n", status);
    return status;
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


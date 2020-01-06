
#include <stdint.h>

#include "hardware.h"
#include "spi2.h"


void SPI2_init()
{
    //main config
    SPI2CONbits.ON = 0; //disable the SPI2 peripheral
    SPI2CONbits.SIDL = 0; //continue operation in idle mode
    SPI2CONbits.MSTEN = 1; //master mode
    SPI2CON2bits.AUDEN = 0; //audio disabled
    SPI2CONbits.ENHBUF = 0; //enhanced buffers
    
    //frame support stuff
    SPI2CONbits.FRMEN = 0; // framed support disabled
    SPI2CONbits.FRMSYNC = 0; //master mode, but not used when FRMEN is 0
    SPI2CONbits.FRMPOL = 1; //active high, but not used when FRMEN is 0
    SPI2CONbits.MSSEN = 0; //auto slave select SPI is disabled
    SPI2CONbits.FRMSYPW = 0; //frame sync pulse is one clock wide
    SPI2CONbits.FRMCNT = 0b000; //frame sync pulse counter is every data character
    SPI2CONbits.SPIFE = 1; //frame sync pulse at the same time with the first bit clock
    
    //clock stuff
    SPI2CONbits.MCLKSEL = 1; //MCLK is used by the baud rate generator
    
    //IO
    SPI2CONbits.DISSDI = 0; //SDI1 pin is controlled by the module
    SPI2CONbits.DISSDO = 0; //SDO1 pin is controlled by the module
    SPI2CONbits.SSEN = 1; //SSx pin used for slave mode
    
    //SPI mode set to 8 bit
    SPI2CONbits.MODE32 = 0;
    SPI2CONbits.MODE16 = 0;
    
    //sampling and polarity
    SPI2CONbits.SMP = 1; //sample at the end of data output time
    SPI2CONbits.CKE = 0; //serial output data changes from idle to active
    SPI2CONbits.CKP = 0; //active high clock polarity
    
    //interrupt configuration
    SPI2CONbits.STXISEL = 0b00; //SPI2TXIF set when last transfer is shifted out
    SPI2CONbits.SRXISEL = 0b00; //SPI2RXIF set when last word in rx buffer is read
    
    SPI2CON2bits.SPISGNEXT = 0; //RX data is not sign extended
    SPI2CON2bits.FRMERREN = 0; //frame error does not generate interrupt
    SPI2CON2bits.SPIROVEN = 1; //RX overflow does generate interrupt
    SPI2CON2bits.SPITUREN = 0; //TX underrun does not generate interrupt
    
    //audio stuff
    SPI2CON2bits.IGNROV = 1; //ignore receive overflow bit
    SPI2CON2bits.IGNTUR = 1; //ignore transmit underrun bit
    SPI2CON2bits.AUDMONO = 0; //audio data is stereo
    SPI2CON2bits.AUDMOD = 0b00; //i2s mode
    
    
    //configure and clear interrupts
    
    
    //configure SPI baud rate
    
    SPI2BRG = 11; //set for 1MHZ operation
    
    
    
    
    //now finally, turn it on
    SPI2CONbits.ON = 1; //enable the SPI2 peripheral
    
}


void SPI2_tx8(uint8_t dataTx)
{
	//SPI mode set to 8 bit
    SPI2CONbits.MODE32 = 0;
    SPI2CONbits.MODE16 = 0;
    SPI2BUF = (uint32_t)dataTx;
}
void SPI2_tx16(uint16_t dataTx)
{
	//SPI mode set to 16 bit
    SPI2CONbits.MODE32 = 0;
    SPI2CONbits.MODE16 = 1;
    SPI2BUF = (uint32_t)dataTx;
}
void SPI2_tx32(uint32_t dataTx)
{
	//SPI mode set to 32 bit
    SPI2CONbits.MODE32 = 1;
    SPI2CONbits.MODE16 = 0;
    SPI2BUF = (uint32_t)dataTx;
}
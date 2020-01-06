
#include <stdint.h>

#include "hardware.h"
#include "spi3.h"


void SPI3_init()
{
    //main config
    SPI3CONbits.ON = 0; //disable the SPI3 peripheral
    SPI3CONbits.SIDL = 0; //continue operation in idle mode
    SPI3CONbits.MSTEN = 1; //master mode
    SPI3CON2bits.AUDEN = 0; //audio disabled
    SPI3CONbits.ENHBUF = 0; //enhanced buffers
    
    //frame support stuff
    SPI3CONbits.FRMEN = 0; // framed support disabled
    SPI3CONbits.FRMSYNC = 0; //master mode, but not used when FRMEN is 0
    SPI3CONbits.FRMPOL = 1; //active high, but not used when FRMEN is 0
    SPI3CONbits.MSSEN = 0; //auto slave select SPI is disabled
    SPI3CONbits.FRMSYPW = 0; //frame sync pulse is one clock wide
    SPI3CONbits.FRMCNT = 0b000; //frame sync pulse counter is every data character
    SPI3CONbits.SPIFE = 1; //frame sync pulse at the same time with the first bit clock
    
    //clock stuff
    SPI3CONbits.MCLKSEL = 1; //MCLK is used by the baud rate generator
    
    //IO
    SPI3CONbits.DISSDI = 0; //SDI1 pin is controlled by the module
    SPI3CONbits.DISSDO = 0; //SDO1 pin is controlled by the module
    SPI3CONbits.SSEN = 1; //SSx pin used for slave mode
    
    //SPI mode set to 8 bit
    SPI3CONbits.MODE32 = 0;
    SPI3CONbits.MODE16 = 0;
    
    //sampling and polarity
    SPI3CONbits.SMP = 1; //sample at the end of data output time
    SPI3CONbits.CKE = 0; //serial output data changes from idle to active
    SPI3CONbits.CKP = 0; //active high clock polarity
    
    //interrupt configuration
    SPI3CONbits.STXISEL = 0b00; //SPI3TXIF set when last transfer is shifted out
    SPI3CONbits.SRXISEL = 0b00; //SPI3RXIF set when last word in rx buffer is read
    
    SPI3CON2bits.SPISGNEXT = 0; //RX data is not sign extended
    SPI3CON2bits.FRMERREN = 0; //frame error does not generate interrupt
    SPI3CON2bits.SPIROVEN = 1; //RX overflow does generate interrupt
    SPI3CON2bits.SPITUREN = 0; //TX underrun does not generate interrupt
    
    //audio stuff
    SPI3CON2bits.IGNROV = 1; //ignore receive overflow bit
    SPI3CON2bits.IGNTUR = 1; //ignore transmit underrun bit
    SPI3CON2bits.AUDMONO = 0; //audio data is stereo
    SPI3CON2bits.AUDMOD = 0b00; //i2s mode
    
    
    //configure and clear interrupts
    
    
    //configure SPI baud rate
    
    SPI3BRG = 11; //set for 1MHZ operation
    
    
    
    
    //now finally, turn it on
    SPI3CONbits.ON = 1; //enable the SPI3 peripheral
    
}


void SPI3_tx8(uint8_t dataTx)
{
    SPI3CONbits.MODE32 = 0;
    SPI3CONbits.MODE16 = 0;
    SPI3BUF = (uint32_t)dataTx;
}
void SPI3_tx16(uint16_t dataTx)
{
	SPI3CONbits.MODE32 = 0;
    SPI3CONbits.MODE16 = 1;
    SPI3BUF = (uint32_t)dataTx;
}
void SPI3_tx32(uint32_t dataTx)
{
	SPI3CONbits.MODE32 = 1;
    SPI3CONbits.MODE16 = 0;
    SPI3BUF = (uint32_t)dataTx;
}

#include <stdint.h>

#include "hardware.h"
#include "spi1.h"


void SPI1_init()
{
    //main config
    SPI1CONbits.ON = 0; //disable the SPI1 peripheral
    SPI1CONbits.SIDL = 0; //continue operation in idle mode
    SPI1CONbits.MSTEN = 1; //master mode
    SPI1CON2bits.AUDEN = 0; //audio disabled
    SPI1CONbits.ENHBUF = 1; //enhanced buffers
    
    //frame support stuff
    SPI1CONbits.FRMEN = 0; // framed support disabled
    SPI1CONbits.FRMSYNC = 0; //master mode, but not used when FRMEN is 0
    SPI1CONbits.FRMPOL = 1; //active high, but not used when FRMEN is 0
    SPI1CONbits.MSSEN = 0; //auto slave select SPI is disabled
    SPI1CONbits.FRMSYPW = 0; //frame sync pulse is one clock wide
    SPI1CONbits.FRMCNT = 0b000; //frame sync pulse counter is every data character
    SPI1CONbits.SPIFE = 1; //frame sync pulse at the same time with the first bit clock
    
    //clock stuff
    SPI1CONbits.MCLKSEL = 0; //PBCLK is used by the baud rate generator
    
    //IO
    SPI1CONbits.DISSDI = 0; //SDI1 pin is controlled by the module
    SPI1CONbits.DISSDO = 0; //SDO1 pin is controlled by the module
    SPI1CONbits.SSEN = 1; //SSx pin used for slave mode
    
    //SPI mode set to 8 bit
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.MODE16 = 0;
    
    //sampling and polarity
    SPI1CONbits.SMP = 1; //sample at the end of data output time
    SPI1CONbits.CKE = 0; //serial output data changes from idle to active
    SPI1CONbits.CKP = 0; //active high clock polarity
    
    //interrupt configuration
    SPI1CONbits.STXISEL = 0b00; //SPI1TXIF set when last transfer is shifted out
    SPI1CONbits.SRXISEL = 0b00; //SPI1RXIF set when last word in rx buffer is read
    
    SPI1CON2bits.SPISGNEXT = 0; //RX data is not sign extended
    SPI1CON2bits.FRMERREN = 0; //frame error does not generate interrupt
    SPI1CON2bits.SPIROVEN = 1; //RX overflow does generate interrupt
    SPI1CON2bits.SPITUREN = 0; //TX underrun does not generate interrupt
    
    //audio stuff
    SPI1CON2bits.IGNROV = 1; //ignore receive overflow bit
    SPI1CON2bits.IGNTUR = 1; //ignore transmit underrun bit
    SPI1CON2bits.AUDMONO = 0; //audio data is stereo
    SPI1CON2bits.AUDMOD = 0b00; //i2s mode
    
    
    //configure and clear interrupts
    
    
    //configure SPI baud rate
    
    SPI1BRG = 11; //set for 1MHZ operation
    
    
    //now finally, turn it on
    SPI1CONbits.ON = 1; //enable the SPI1 peripheral
    
}


void SPI1_tx8(uint8_t dataTx)
{
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.MODE16 = 0;
    SPI1BUF = (uint32_t)dataTx;
    
}
void SPI1_tx16(uint16_t dataTx)
{
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.MODE16 = 1;
    SPI1BUF = (uint32_t)dataTx;
    
}
void SPI1_tx32(uint32_t dataTx)
{
    SPI1CONbits.MODE32 = 1;
    SPI1CONbits.MODE16 = 0;
    SPI1BUF = (uint32_t)dataTx;
    
}

uint8_t SPI1_rx8(void)
{
    uint8_t rxData = 0;
    
    rxData = SPI1BUF;
    
    return rxData;
}

uint32_t SPI1_rx32(void)
{
    //printf("SPI buf count:" )
    
    uint32_t rxData = 0xFFFFFFFF;
    
    rxData = SPI1BUF;
    
    return rxData;
}
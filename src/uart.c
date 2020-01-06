/* 
 * File:   uart.c
 * Author: Jacob
 *
 * Created on November 7, 2018, 10:19 PM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "hardware.h"
#include "hardware_config.h"
#include "uart.h"




//local function prototypes
void UART1_PPS();
void UART2_PPS();

void initUARTS()
{
    initUART1();
    initUART2();
}


void initUART1()
{
    UART1_PPS();
    
    //ensure the ANSEL is not set for this uart
    ANSELAbits.ANSA6 = 0;
    
    U1MODEbits.ACTIVE = 0; //allow configuration
    U1MODEbits.ON = 0;     //Peripheral OFF      
    
    U1MODE = 0;                                 //Default values
    U1STA = 0;                                  //Default values
    
    U1BRG = (SYS_CLOCK / (4 * UartBAUD)) - 1;   //Setting Baud Rate for BRGH = 1 (high speed)

    U1MODEbits.SLPEN = 0; //UART off during sleep mode
    U1MODEbits.OVFDIS = 0; //legacy mode don't accept more bits on overflow
    U1MODEbits.SIDL = 0; //keep device active during idle mode
    U1MODEbits.IREN = 0; //NO IRDA mode
    U1MODEbits.CLKSEL = 0b01;                   //Uses SYSCLOCK 
    U1MODEbits.RTSMD = 1; //Simplex Mode
    U1MODEbits.UEN = 0; //utx and urx lines are controlled
    U1MODEbits.WAKE = 0; //wakeup disabled
    U1MODEbits.LPBACK = 0; //Loopback disabled
    U1MODEbits.ABAUD = 0; //autobaud disabled
    U1MODEbits.BRGH = 1;                        //High speed mode
    U1MODEbits.PDSEL = 0; //8 bits no parity
    U1MODEbits.STSEL = 1; //1 stop bit
    
    U1STAbits.MASK = 0;
    U1STAbits.ADDR = 0;
    
    U1STAbits.UTXISEL = 0b10; //when all have been TX
    U1STAbits.UTXISEL = 0b00; //when something has been RX
    
    U1STAbits.UTXEN = 1;                        //Enables TX
    U1STAbits.URXEN = 1;                        //Enables RX
    
    //IFS1<21> IEC1<21> IPC13<12:10> IPC13<9:8>
    //enable rx interrupt
    IPC13bits.U1RXIP = 1; //priority 5
    IPC13bits.U1RXIS = 0; //subpriority 1
    IFS1bits.U1RXIF = 0; //clear the flag
    IFS1bits.U1TXIF = 0; //clear the flag
    IFS1bits.U1EIF = 0;
    IEC1bits.U1RXIE = 1; //enable the interrupt
    
    
    U1MODEbits.ACTIVE = 1; //disallow configuration
    U1MODEbits.ON = 1;     //Peripheral ON 
    
}

void initUART2()
{
    UART2_PPS();
    U2MODE = 0;                                 //Default values
    U2STA = 0;                                  //Default values
    U2MODEbits.ON = 0;                          //Peripheral OFF        
    U2MODEbits.CLKSEL = 0b01;                   //Uses SYSCLOCK 
    U2MODEbits.BRGH = 1;                        //High speed mode
    U2STAbits.UTXEN = 1;                        //Enables UTX. 
    U2STAbits.URXEN = 1;                        //Enables URX. 
    U2STAbits.URXISEL = 0b00;                   //Interrupt occurs upon receipt of each byte
    U2BRG = (SYS_CLOCK / (4 * UartBAUD)) - 1;  //Setting Baud Rate for BRGH = 1 (high speed)
    
    //IFS1<24> IEC1<24> IPC14<4:2> IPC14<1:0>
    //enable rx interrupt
    IPC14bits.U2RXIP = 1; //priority 5
    IPC14bits.U2RXIS = 0; //subpriority 1
    IFS1bits.U2RXIF = 0; //clear the flag
    IEC1bits.U2RXIE = 1; //enable the interrupt
    
    U2MODEbits.ON = 1;                          //Peripheral ON 
    
}

    
void UART1send(char c)
{
    
}

void UART2send(char c)
{
    
}




void UART1_PPS()
{
    
}

void UART2_PPS()
{

}



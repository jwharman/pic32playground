#include <xc.h>

#include <sys/attribs.h> //contains the interrupt stuff   

#include <stdio.h>
#include <stdint.h>

#include "hardware.h"
#include "uart_handler.h"
#include "application.h"


//here we want to handle the interrupts and buffers for the UART

#define U1RX_BUF_SIZE 255
#define U2RX_BUF_SIZE 255
#define U1_CMD_END_CHAR 0x0D
#define U2_CMD_END_CHAR 0x0D

char u1RXBuf[U1RX_BUF_SIZE] = {0}; //receive buffer
uint32_t u1BufIndex = 0;

char u2RXBuf[U2RX_BUF_SIZE] = {0}; //receive buffer
uint32_t u2BufIndex = 0;


uint32_t getBufferCount()
{
    return u1BufIndex;
}


//IFS1<21> IEC1<21> IPC13<12:10> IPC13<9:8>
void __ISR(U1RX_INT_VECTOR, IPL1AUTO) _U1RX_Interrupt(void)
{
    u1RXBuf[u1BufIndex] = U1RXREG;
    u1BufIndex++;
    
    if(u1BufIndex > U1RX_BUF_SIZE)
    {
        u1BufIndex = 0;
    }
 
    IFS1bits.U1RXIF = 0; //clear the flag
    
}

//IFS1<24> IEC1<24> IPC14<4:2> IPC14<1:0>
void __ISR(U2RX_INT_VECTOR, IPL1AUTO) _U2RX_Interrupt(void)
{
    u2RXBuf[u2BufIndex] = U2RXREG;
    u2BufIndex++;
    
    if(u2BufIndex > U2RX_BUF_SIZE)
    {
        u2BufIndex = 0;
    }

    IFS1bits.U2RXIF = 0; //clear the flag
    
}
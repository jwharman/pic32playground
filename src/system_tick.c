
#include <xc.h>
#include <sys/attribs.h>
#include <stdint.h>
#include <stdio.h>
#include <p32xxxx.h>
#include "system_tick.h"

#define T1_INT_VECTOR 17



static uint32_t global_sys_tick;


void sys_tick_init(void)
{
    
    global_sys_tick = 0;
    
    //we want to initialize timer 1 on the system to give us 1ms ticks
    
    //24 Mhz (for system clock)
    
    T1CON = 0x0; // Stop the timer and clear the control register,
    // prescaler at 1:1,internal clock source
    
    TMR1 = 0x0; // Clear the timer register
    
    PR1 = 24000UL; // Load the period register
    
    //configure interrupts
    
    IPC4bits.T1IP = 5; //interrupt priority 5
    IPC4bits.T1IS = 0; //interrupt sub-priority 0
    
    IFS0bits.T1IF = 0; //clear the flag
    
    IEC0bits.T1IE = 1; //enable the interrupt
    
    
     
    T1CONSET = 0x8000; // Start the timer
    
    
    
    
}




uint32_t get_sys_tick(void)
{
    return global_sys_tick;
}

//timer 1 interrupt
/*
void __ISR(_Timer_1_Vector,ipl3)Timer1Handler(void)
{
... perform application specific operations in response to the interrupt
IFS0CLR = 0x00000010; // Be sure to clear the Timer1 interrupt status
}
*/


/*
 IFS0<17> IEC0<17> IPC4<12:10> IPC4<9:8> No
 */


void __ISR(T1_INT_VECTOR, IPL5AUTO) _T1_ErrInterrupt(void)
{
    
    
    global_sys_tick++;
    
    IFS0bits.T1IF = 0; //clear the flag
    
}

#include <xc.h>
#include "timer1.h"

void timer1_init(void)
{
    //this will set up timer 1 to be 1 millisecond timer
    
    
    T1CONbits.ON = 0; //turn off the timer
    T1CONbits.SIDL = 0; //continues when idle
    T1CONbits.TWDIS = 0; //legacy mode
    
    
    
    
}

//this is the timer ISR
//void __ISR(_TIMER_1_VECTOR, IPL2AUTO) Timer1ISR(void)
//{
//    IFS0bits.T1IF = 0;
//    do something here
//}
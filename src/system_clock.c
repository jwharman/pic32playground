
#include "system_clock.h"

#include <stdint.h>

#include <xc.h>
#include <sys/attribs.h>


volatile uint16_t g_tmr_tick;

void system_clock_init (void)
{
    //we need to set up the system timer
}
uint16_t system_clock_get_tick (void)
{
    return g_tmr_tick;
}


//we need to set up the system timer to run our main tick

//the isr will go there

void __ISR(_TIMER_1_VECTOR, IPL2AUTO) Timer1ISR(void)
{
    IFS0bits.T1IF = 0;
    g_tmr_tick++;
}
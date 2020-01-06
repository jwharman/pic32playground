#include <xc.h>
#include <sys/attribs.h>


void system_interrupt_config()
{
    //we need to configure the interrupt system 
    IEC0bits.T1IE = 1;
    
}

void system_enable_interrupts()
{
    
}

void system_disable_interrupts()
{
    
}


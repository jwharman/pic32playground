
#include "hardware.h"
#include "application.h"
#include <xc.h>
#include <stdio.h>

#include <sys/attribs.h> //contains the interrupt stuff   


void __ISR(0,IPL0AUTO) _DefaultInterrupt (void)
{
    
}



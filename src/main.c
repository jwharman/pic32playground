#include <xc.h>

#include <stdio.h>
#include <stdlib.h>

#include "config_bits.h"
#include "hardware.h"
#include "application.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    hardware_init();
    application_init();
    
    while(1)
    {
        hardware_service();
        application_service();
    }
    
}


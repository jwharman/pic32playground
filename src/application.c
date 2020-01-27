#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "application.h"
#include "user_timer.h"

uint64_t counter = 0;

 uint16_t  set_point;       //how many ms before resetting.
 uint16_t  enabled;         //signifies whether the timer is running or not...

static user_tmr m_main_tmr = {.enabled = false, .set_point = 0};


static bool pinState;

static uint8_t spiCounter;

static uint16_t dataCounter;

static uint16_t address;

void application_init(void)
{
    pinState = false;
    
    spiCounter = 0;
    
    dataCounter = 0;
    
    printf("***Application Initialized***\r\n");

    
}

void application_service(void)
{
     if(user_timer_interval(&m_main_tmr, 100)) //every 100 ms
        {   
         
           
         pinState = !pinState;
            
         
            
            counter++;
        }
     
     BLUE_LED = pinState;
}

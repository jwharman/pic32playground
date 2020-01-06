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

void application_init(void)
{
    pinState = false;
    
    spiCounter = 0;
    
    dataCounter = 0;
    
    printf("***Application Initialized***\r\n");
    
    printf("writing FRAM values: 0x5A at 0x000 \r\n");
    
    byte_write_at_index(0,0x5A);
    
}

void application_service(void)
{
     if(user_timer_interval(&m_main_tmr, 100)) //every 100 ms
        {
            counter++;
      
            pinState = !pinState;
            
             //printf("counter: %llu\r\n", counter);
             
             
             
             if(dataCounter < 0x1FFF)
             {
                 
//                 byte_write_at_index(dataCounter, (uint8_t)(dataCounter & 0xFF));
//                 
//                 uint8_t data = byte_read_at_index(dataCounter);
//                 printf("FRAM address: 0x%X : 0x%X \r\n", dataCounter, data);
//                 dataCounter++;
             }
             else
             {
                 dataCounter = 0;
             }
            
             
             //FRAM_service();
             
        }
     
    
     
     BLUE_LED = pinState;
}

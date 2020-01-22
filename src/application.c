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
    
    //init the FRAM PINS to a good state
    FRAM_HOLD = 1;
    FRAM_CS = 1;
    FRAM_WP = 0;
    
    address = 0;
   
    
    
    
}

void application_service(void)
{
     if(user_timer_interval(&m_main_tmr, 100)) //every 100 ms
        {   
            
            //write8(1, 1);
         
            uint32_t devID = readDeviceID();
         
            printf("Attempting to read device ID: 0x%lX\r\n", devID);
            
//            uint32_t status = readStatusRegister();
//            
//            printf("Attempting to read status register: 0x%lX\r\n", status);
         
            pinState = !pinState;

            
            
            counter++;
        }
     
     BLUE_LED = pinState;
}

#ifndef _HARDWARE_H_    /* Guard against multiple inclusion */
#define _HARDWARE_H_

#define DEBUG    

#include <xc.h>
//this is where we will include the configuration for all main hardware systems
#include "hardware_pin_assignments.h"
#include "system_tick.h"
#include "uart.h"
#include "spi1.h"
#include "spi2.h"
#include "spi3.h"
#include "timer1.h"


#include "mb85rs64v.h"

#define SYS_CLOCK          24000000    //Clock speed 24 Mhz
#define UartBAUD           115200    

////////////////

#define U1RX_INT_VECTOR  53
#define U1TX_INT_VECTOR  54
#define U1ERR_INT_VECTOR 55

#define U2RX_INT_VECTOR  56
#define U2TX_INT_VECTOR  57
#define U2ERR_INT_VECTOR 58

#define U3RX_INT_VECTOR  59
#define U3TX_INT_VECTOR  60
#define U3ERR_INT_VECTOR 61    

void hardware_init(void);
void hardware_service(void);


#endif /*_HARDWARE_H_*/

/* *****************************************************************************
 End of File
 */

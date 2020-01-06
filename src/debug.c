
#include "debug.h"
#include <xc.h> 



#define GetSystemClock()    (24000000ULL) 
   
void DelayUs( uint32_t delay_in_us ) 
 { 
     uint32_t tWait = ( GetSystemClock() / 2000000 ) * delay_in_us; 
     uint32_t tStart = _CP0_GET_COUNT(); 
     while( ( _CP0_GET_COUNT() - tStart ) < tWait ); 
 }  
void DelayMs( uint32_t delay_in_ms )
 {
     uint32_t tWait = ( GetSystemClock() / 2000 ) * delay_in_ms;
     uint32_t tStart = _CP0_GET_COUNT();
     while( ( _CP0_GET_COUNT() - tStart ) < tWait );
 }
 

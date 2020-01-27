#include <xc.h>
#include "hardware.h"

#include <stdio.h>
#include <stdint.h>
//includes for hardware stuff



static uint32_t counter;
static uint32_t status;



static void uart_init(void);
static void sys_interrupt_config(void);
static void sys_clock_config(void);
static void sys_raw_io_config(void);

void hardware_init(void)
{
    sys_raw_io_config();
    
    __XC_UART = 1;  // printf is configured to use UART1 
   
    sys_interrupt_config();
    sys_clock_config();
    sys_tick_init();
    
    initUARTS();
    SPI1_init();
    
   __builtin_enable_interrupts();
   
    counter = 0;
    status = 0;
   

    printf("***Hardware Initialized***\r\n");
    
    FRAM_init();
    
    write8(0,0xA5);
    write8(1,0x5A);
    
    
}
void hardware_service(void)
{
  
}

static void sys_raw_io_config()
{
    //set all pins up to be outputs
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    
    //all outputs off
    LATA = 0;
    LATB = 0;
    LATC = 0;
    LATD = 0;
    
    //ANSEL bits
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    
    
    //we will need to configure the pins we want for analog with ANSEL registers
    
    
    //set TRIS B 14 to be input for SDI - SPI1
    TRISBbits.TRISB14 = 1; //make it an input
    
}



void sys_clock_config()
{
    // --------------- Stock config to run from PLLFRC -------------------------//
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    OSCCONCLR = _OSCCON_FRCDIV_MASK | _OSCCON_NOSC_MASK;
    OSCCONSET = _OSCCON_OSWEN_MASK;
    while ( OSCCONbits.OSWEN == 1 )
        Nop ();
    
    //FP:    SPLLCON = 0x02050080; (the READABLE code bellow is equivalent to this garbage)
    SPLLCONbits.PLLICLK = 1;            //FRC as clock to the system PLL. 8 Mhz
    SPLLCONbits.PLLMULT = 0b0000101;    //Multiply 12x to 96 Mhz (for USB)
    SPLLCONbits.PLLODIV = 0b010;        //Divide by 4x to 24 Mhz (for system clock)
    
    OSCCONSET = ( 0b001 << _OSCCON_NOSC_POSITION ) | _OSCCON_OSWEN_MASK;
    
    while ( OSCCONbits.OSWEN == 1 )
        Nop ();

    OSCTUN = 0x00009000;
    
    CFGCONbits.BMXARB = 0b10;
    
    SYSKEY = 0;
    // --------------- Stock config to run from PLLFRC -------------------------//
}

static void uart_init()
{
    U1MODE = 0;                                 //Default values
    U1STA = 0;                                  //Default values
    U1MODEbits.ON = 0;                          //Peripheral OFF        
    U1MODEbits.CLKSEL = 0b01;                   //Uses SYSCLOCK 
    U1MODEbits.BRGH = 1;                        //High speed mode
    U1STAbits.UTXEN = 1;                        //Enables UTX. 
    U1STAbits.URXEN = 1;                        //Enables URX
    U1BRG = (SYS_CLOCK / (4 * UartBAUD)) - 1;   //Setting Baud Rate for BRGH = 1 (high speed)
    U1MODEbits.ON = 1;                          //Peripheral ON 
}

static void sys_interrupt_config()
{
    //interrupt controller config
    INTCONbits.VS = 1; //eight bytes between vector
    INTCONbits.MVEC = 1; //Multivector configuration bit
    INTCONbits.TPC = 000; //disable proximity timer
    
    INTCONbits.INT0EP = 1; //rising edge for external interrupt
    INTCONbits.INT1EP = 1; //rising edge for external interrupt
    INTCONbits.INT2EP = 1; //rising edge for external interrupt
    INTCONbits.INT3EP = 1; //rising edge for external interrupt
    INTCONbits.INT4EP = 1; //rising edge for external interrupt
    
    
    //shadow set configuration
    PRISSbits.PRI1SS = 1; //use shadow set 1
    PRISSbits.PRI2SS = 1; //use shadow set 1
    PRISSbits.PRI3SS = 1; //use shadow set 1
    PRISSbits.PRI4SS = 1; //use shadow set 1
    PRISSbits.PRI5SS = 1; //use shadow set 1
    PRISSbits.PRI6SS = 1; //use shadow set 1
    PRISSbits.PRI7SS = 1; //use shadow set 1
    
    PRISSbits.SEVCSS = 0; //single vector mode does not get a shadow set
    
   
    
    
    
    
}
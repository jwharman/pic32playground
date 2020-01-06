/* 
 * File:   hardware_config.h
 * Author: Jacob
 *
 * Created on November 7, 2018, 10:22 PM
 */

#ifndef HARDWARE_CONFIG_H
#define	HARDWARE_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>



////////////////////////////////////////////////////////////////////////////////
// System definitions

#define SYSTEM_Halt()                       asm volatile ( "sdbbp 0")
#define SYSTEM_AddrToPhysical( x )          ((uint32_t)( x ) & 0x1FFFFFFF )
#define SYSTEM_AddrToVirtual( x )           ((void*)(( x ) | 0xA0000000 ))

////////////////////////////////////////////////////////////////////////////////
// System clock Configuration

#define SYSTEM_GetSystemClock()             24000000ul
#define SYSTEM_GetInstructionClock()        SysGetClock()
#define SYSTEM_GetPeripheralClock()         SysGetClock()
#define SysGetClock()                       SYSTEM_GetSystemClock()
#define SysGetInstructionClock()            SYSTEM_GetInstructionClock()
#define SysGetPeripheralClock()             SYSTEM_GetPeripheralClock()
#define GetPeripheralClock()                SYSTEM_GetPeripheralClock()

// system timer should be uint16_t value with half-overflow rate of >= 10ms
// optimal clock is <= 3.2 MHz
// high-res / high-speed timers can be recalculated on-the-fly
#define SYSTEM_GetTimer()                   (uint16_t)( _CP0_GET_COUNT () / 16 )
#define SYSTEM_GetTimerClock()              ( SYSTEM_GetInstructionClock () / 2 / 16 )
    
////////////////////////////////////////////////////////////////////////////////
// NVM Configuration
#define NVM_PAGE_SIZE                       2048 //4096

////////////////////////////////////////////////////////////////////////////////
// ADC Definitions

#define SYSTEM_AD_CHN_KEY0                  0x00050000  // AN5
#define SYSTEM_AD_CHN_VBUS                  0x00040000  // AN4
#define SYSTEM_DEVICEDETECT_TREDHOLD        3 //v
#define SYSTEM_AD_MAX                       0x0FFF
#define SYSTEM_AD_MID                       0x8000

////////////////////////////////////////////////////////////////////////////////
// Users Interface

#define KEY_COUNT                           5       // 3 buttons and 2 is button simulated potentiometer

#define SYSTEM_KEY_AD_DELTA                 512
#define SYSTEM_KEY_AD_DEBOUNCE              3       // 30 ms
#define SYSTEM_LED_ALL                      0b00000111
#define SYSTEM_LED_BLUE                     0b00000001
#define SYSTEM_LED_RED                      0b00000010
#define SYSTEM_LED_VIOLET                   0b00000011
#define SYSTEM_LED_GREEN                    0b00000100 
#define SYSTEM_LED_CYAN                     0b00000101
#define SYSTEM_LED_YELLOW                   0b00000110 
#define SYSTEM_LED_WHITE                    0b00000111

////////////////////////////////////////////////////////////////////////////////
// I2C Definitions

#define SYSTEM_MAIN_I2C_SPEED               100000
#define SYSTEM_MAIN_I2C_MODULE              I2C1


////////////////////////////////////////////////////////////////////////////////
// USB Device Definitions

#define self_power                          1
#define USB_BUS_SENSE                       1
#define USB_CURRENT_DRAW                    100

////////////////////////////////////////////////////////////////////////////////
// I2S driver configuration
      
#define SYSTEM_REFO_SOURCE                  REFO_SOURCE_SYSPLL

#define SYSTEM_I2S_SPI                      SPI2
#define SYSTEM_I2S_DMA_TX                   DMA0
#define SYSTEM_I2S_DMA_RX                   DMA1

////////////////////////////////////////////////////////////////////////////////

#define AK4642_I2C_MODULE                   I2C3
#define AK4642_AssertReset()                LATCCLR = 0b0100000000000000
#define AK4642_DeassertReset()              LATCSET = 0b0100000000000000

////////////////////////////////////////////////////////////////////////////////

#define REFOCON                             REFO1CON
#define REFOCONCLR                          REFO1CONCLR
#define REFOCONSET                          REFO1CONSET
#define REFOCONbits                         REFO1CONbits

#define _REFOCON_ON_MASK                    _REFO1CON_ON_MASK
#define _REFOCON_DIVSWEN_MASK               _REFO1CON_DIVSWEN_MASK

#define REFOTRIM                            REFO1TRIM
#define REFOTRIMbits                        REFO1TRIMbits

////////////////////////////////////////////////////////////////////////////////

#define _SPI1_RX_IRQ                        _SPI1_RX_VECTOR
#define _SPI1_TX_IRQ                        _SPI1_TX_VECTOR
#define _SPI2_RX_IRQ                        _SPI2_RX_VECTOR
#define _SPI2_TX_IRQ                        _SPI2_TX_VECTOR
#define _SPI3_RX_IRQ                        _SPI3_RX_VECTOR
#define _SPI3_TX_IRQ                        _SPI3_TX_VECTOR

#ifdef	__cplusplus
}
#endif

#endif	/* HARDWARE_CONFIG_H */


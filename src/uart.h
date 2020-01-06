/* 
 * File:   uart.h
 * Author: Jacob
 *
 * Created on November 7, 2018, 10:19 PM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initUARTS(void);
    
    void initUART1(void);
    void initUART2(void);
    
    void UART1send(char);
    void UART2send(char);

    
    

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */


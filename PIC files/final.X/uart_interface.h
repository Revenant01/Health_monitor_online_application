/* 
 * File:   uart_interface.h
 * Author: User
 *
 * Created on October 23, 2023, 7:18 PM
 */

#ifndef UART_INTERFACE_H
#define	UART_INTERFACE_H

#ifdef	__cplusplus
extern "C" {
#endif

char uart_read ();
void uart_write (int data);
void uart_init();


#ifdef	__cplusplus
}
#endif

#endif	/* UART_INTERFACE_H */


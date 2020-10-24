/*
 *  uart.h
 *
 * Created: 23/10/2020 21:53:52
 *  Author: Cliff
 */


#ifndef UART_H_
#define UART_H_

#include "stdio.h"
#include <avr/io.h>

class Uart {
public:
    Uart(uint32_t baud);
    static int putChar(char c, FILE * f = NULL);
    static int getChar(FILE * f = NULL);
    void connectStdio();
private:
    FILE mUartStream;
};



#endif /* UART_H_ */
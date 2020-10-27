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
    Uart(uint8_t num, uint32_t baud);
    static int putChar0(char c, FILE * f = NULL);
    static int getChar0(FILE * f = NULL);
    static int putChar1(char c, FILE * f = NULL);
    static int getChar1(FILE * f = NULL);
    void connectStdio();
private:
    uint8_t mUartNum;
    FILE mUartStream;
};



#endif /* UART_H_ */
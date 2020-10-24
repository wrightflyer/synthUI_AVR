/*
 *  uart.cpp
 *
 * Created: 23/10/2020 21:53:28
 *  Author: Cliff
 */

#include "uart.h"

Uart::Uart(uint32_t baud) {
    uint16_t ubrr = (F_CPU / (16 * baud)) - 1;
    UCSRB = (1 << TXEN) | (1 << RXEN);
    UBRRH = ubrr >> 8;
    UBRRL = ubrr & 0xFF;
}

int Uart::putChar(char c, FILE * f) {
    while(!(UCSRA & (1 << UDRE)));
    UDR = c;
    return 0;
}

int Uart::getChar(FILE * f) {
    while(!(UCSRA & (1 << RXC)));
    return UDR;
}

void Uart::connectStdio() {
    fdev_setup_stream(&mUartStream, putChar, getChar, _FDEV_SETUP_RW);
    stdout = &mUartStream;
}


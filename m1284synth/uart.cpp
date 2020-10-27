/*
 *  uart.cpp
 *
 * Created: 23/10/2020 21:53:28
 *  Author: Cliff
 */

#include "uart.h"

Uart::Uart(uint8_t num, uint32_t baud) : mUartNum(num) {
    uint16_t ubrr = (F_CPU / (16 * baud)) - 1;
    if (mUartNum == 0) {
        UCSR0B = (1 << TXEN0) | (1 << RXEN0);
        UBRR0H = ubrr >> 8;
        UBRR0L = ubrr & 0xFF;
    }
    else {
        UCSR1B = (1 << TXEN1) | (1 << RXEN1);
        UBRR1H = ubrr >> 8;
        UBRR1L = ubrr & 0xFF;
    }
}

int Uart::putChar0(char c, FILE * f) {
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
    return 0;
}

int Uart::putChar1(char c, FILE * f) {
    while(!(UCSR1A & (1 << UDRE1)));
    UDR1 = c;
    return 0;
}

int Uart::getChar0(FILE * f) {
    while(!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

int Uart::getChar1(FILE * f) {
    while(!(UCSR1A & (1 << RXC1)));
    return UDR1;
}

void Uart::connectStdio() {
    if (mUartNum == 0) {
        fdev_setup_stream(&mUartStream, putChar0, getChar0, _FDEV_SETUP_RW);
    }
    else {
        fdev_setup_stream(&mUartStream, putChar1, getChar1, _FDEV_SETUP_RW);
    }
    stdout = &mUartStream;
}


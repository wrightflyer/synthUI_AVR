/*
 * button.cpp
 *
 * Created: 25/10/2020 18:58:39
 *  Author: Cliff
 */

#include <stdio.h>
#include "button.h"

Button::Button(volatile uint8_t * port, uint8_t pin, uint8_t pullup) : mCount(0) {
    mPORT = port;
    mDDR  = port - 1;
    mPIN  = port - 2;
    mPinMask = (1 << pin);
    *mDDR &= ~mPinMask; // input
    if (pullup) {
        *mPORT |= mPinMask; // pulled up
    }
    else {
        *mPORT &= ~mPinMask;
    }
    mPrev = *mPIN & mPinMask;
    mState = mPrev;
}

// this called back from timer interrupt.
void Button::update() {
    uint8_t in;
    in = *mPIN;
    //printf("raw=%02X ", in);
    in = in & mPinMask;
    //printf("masked=%02X, prev=%02X\r\n", in, mPrev);
    if (in == mPrev) {
        mCount++;
        if (mCount >= 4) {
            //printf("state=%02X\r\n", in);
            mState = in;
            mCount = 0;
        }
    }
    else {
        mCount = 0;
        mPrev = in;
    }
}

uint8_t Button::read() {
    return mState ? 1 : 0;
}

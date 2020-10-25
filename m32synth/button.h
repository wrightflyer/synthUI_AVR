/*
 * button.h
 *
 * Created: 25/10/2020 18:59:11
 *  Author: Cliff
 */


#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>

class Button {
public:
    static const uint8_t PULL_UP = 1;
    static const uint8_t NO_PULL_UP = 0;
    Button(volatile uint8_t * port, uint8_t pin, uint8_t pullup = PULL_UP);
    void update();
    uint8_t read();
private:
    volatile uint8_t * mPORT;
    volatile uint8_t * mDDR;
    volatile uint8_t * mPIN;
    uint8_t mPinMask;
    uint8_t mCount;
    uint8_t mPrev;
    uint8_t mState;
};


#endif /* BUTTON_H_ */
/*
 *  encoder.cpp
 *
 * Created: 23/10/2020 20:56:45
 *  Author: Cliff
 */
#include <stdio.h>
#include "encoder.h"

Encoder::Encoder(volatile uint8_t * port, uint8_t pin1, uint8_t pin2) :
                mPos(0)
{
    mPin1 = (1 << pin1);
    mPin2 = (1 << pin2);
    mPORT = port;
    mDDR  = port - 1;
    mPIN  = port - 2;
    // this uses the "trick" that GPIO ports in memory are laid out as:
    // n + 0: PINx
    // n + 1: DDRx
    // n + 2: PORTx
    //
    // so given PORTx you can write DDR with (PORT-1) and PIN with (PORT-2)
    *mDDR  &= ~(mPin1 | mPin2); // DDR bits to input
    *mPORT |=   mPin1 | mPin2; // write to PORT to enable pull-ups
    // read initial state..
    uint8_t s = 0;
    if (*mPIN & mPin1) s |= 1;
    if (*mPIN & mPin2) s |= 2;
    mState = s;
}

void Encoder::update() {
    /* blatant theft from Teensy encoder lib ;-)...
                               _______         _______
                   Pin1 ______|       |_______|       |______ Pin1
     negative <---         _______         _______         __      --> positive
                   Pin2 __|       |_______|       |_______|   Pin2

        new    new    old    old
        pin2   pin1   pin2   pin1   Result
        ----   ----   ----   ----   ------
        0      0      0      0       0: no movement
        0      0      0      1       1: +1
        0      0      1      0       2: -1
        0      0      1      1       3: +2  (assume pin1 edges only)
        0      1      0      0       4: -1
        0      1      0      1       5: no movement
        0      1      1      0       6: -2  (assume pin1 edges only)
        0      1      1      1       7: +1
        1      0      0      0       8: +1
        1      0      0      1       9: -2  (assume pin1 edges only)
        1      0      1      0      10: no movement
        1      0      1      1      11: -1
        1      1      0      0      12: +2  (assume pin1 edges only)
        1      1      0      1      13: -1
        1      1      1      0      14: +1
        1      1      1      1      15: no movement

    // Simple, easy-to-read "documentation" version :-)
    //
    void update(void) {
        uint8_t s = state & 3;
        if (digitalRead(pin1)) s |= 4;
        if (digitalRead(pin2)) s |= 8;
        switch (s) {
            case 0: case 5: case 10: case 15:
                break;
            case 1: case 7: case 8: case 14:
                position++; break;
            case 2: case 4: case 11: case 13:
                position--; break;
            case 3: case 12:
                position += 2; break;
            default:
                position -= 2; break;
        }
        state = (s >> 2);
    }
*/
    uint8_t sin, p1in = 0, p2in = 0, scase;
    int8_t change;
    uint8_t s = mState & 3;
    sin = s;
    if (*mPIN & mPin1) {
        p1in = 1;
        s |= 4;
    }
    if (*mPIN & mPin1) {
        p2in = 1;;
        s |= 8;
    }
    scase = s;
    switch (s) {
        case 0:
        case 5:
        case 10:
        case 15:
            change = 0;
            break;

        case 1:
        case 7:
        case 8:
        case 14:
            change = 1;
            mPos++;
            break;

        case 2:
        case 4:
        case 11:
        case 13:
            change = -1;
            mPos--;
            break;

        case 3:
        case 12:
            change = 2;
            mPos += 2;
            break;

        default: // 6 or 9
            change = -2;
            mPos -= 2;
            break;
    }
    mState = (s >> 2);
    printf("sin = %u, p1 = %u, p2 = %u, case = %u, change = %d, sout = %u\r\n", sin, p1in, p2in, scase, change, mState);
}

void Encoder::intUpdate(void) {
    update();
}

int32_t Encoder::read() {
    //update();
    return mPos;
}

int32_t Encoder::readAndReset() {
    int32_t ret = read();
    mPos = 0;
    return ret;
}

void Encoder::write(int32_t p) {
    mPos = p;
}

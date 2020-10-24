/*
 *  encoder.h
 *
 * Created: 23/10/2020 20:59:18
 *  Author: Cliff
 */


#ifndef ENCODER_H_
#define ENCODER_H_

#include <avr/io.h>

class Encoder {
public:
    Encoder(volatile uint8_t * port, uint8_t pin1, uint8_t pin2);
    void update();
    int32_t read();
    int32_t readAndReset();
    void write(int32_t p);
    void intUpdate();
private:
    volatile uint8_t * mPORT;
    volatile uint8_t * mPIN;
    volatile uint8_t * mDDR;
    uint8_t mPin1;
    uint8_t mPin2;
    uint8_t mState;
    int32_t mPos;
};



#endif /* ENCODER_H_ */
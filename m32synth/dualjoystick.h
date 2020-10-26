/*
 * dualjoystick.h
 *
 * Created: 25/10/2020 21:11:07
 *  Author: Cliff
 */ 


#ifndef DUALJOYSTICK_H_
#define DUALJOYSTICK_H_

#include <avr/io.h>
#include "adc.h"

class DualJoystick : Adc{
public:
    typedef struct {
        uint16_t x;
        uint16_t y;
    } reading_t;
    DualJoystick(uint8_t chanX, uint8_t chanY, uint8_t divider, adc_ref_t ref = ADC_AVCC_REF, adc_align_t align = ADC_RIGHT);
    reading_t read();
private:
    uint8_t mChanX;
    uint8_t mChanY;
    Adc mAdc;
};



#endif /* DUALJOYSTICK_H_ */
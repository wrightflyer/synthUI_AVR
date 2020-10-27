/*
 * dualjoystick.cpp
 *
 * Created: 25/10/2020 21:11:39
 *  Author: Cliff
 */ 

 #include "dualjoystick.h"

DualJoystick::DualJoystick(uint8_t chanX, uint8_t chanY, uint8_t divider, adc_ref_t ref, adc_align_t align)
    : mChanX(chanX), mChanY(chanY) {
    mAdc.setSpeed(divider);
    mAdc.setAlign(align);
    mAdc.setRef(ref);
};

DualJoystick::reading_t DualJoystick::read() {
    reading_t retval;
    retval.x = mAdc.read(mChanX);
    retval.y = mAdc.read(mChanY);
    return retval;
}

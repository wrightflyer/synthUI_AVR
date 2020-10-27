/*
 * adc.cpp
 *
 * Created: 25/10/2020 21:11:23
 *  Author: Cliff
 */

#include "adc.h"

Adc::Adc(uint8_t divider, Adc::adc_ref_t ref, Adc::adc_align_t align) : mRefAlign(0), mScale(0) {
    setRef(ref);
    setAlign(align);
    setSpeed(divider);
    ADMUX = mRefAlign; // defaults to chan 0
    ADCSRA = (1 << ADEN) | mScale; 
    read(0); // discard first reading after setting ref
}

void Adc::setSpeed(uint8_t divider) {
    mScale = 0;
    switch (divider) {
    case 2:
        mScale = 0b001;
        break;
    case 4:
        mScale = 0b010;
        break;
    case 8:
        mScale = 0b011;
        break;
    case 16:
        mScale = 0b100;
        break;
    case 32:
        mScale = 0b101;
        break;
    case 64:
        mScale = 0b110;
        break;
    case 128:
        mScale = 0b111;
        break;
    }
}

void Adc::setRef(adc_ref_t ref) {
    mRef = ref;
    mRefAlign &= ~((1 < REFS1) | (1 << REFS0));
    switch (mRef) {
    case ADC_AREF:
        // do nothing as AREF bits already 00
        break;
    case ADC_AVCC_REF:
        mRefAlign |= (1 << REFS0);
        break;
    case ADC_INT_2V56:
        mRefAlign |= (1 < REFS1) | (1 << REFS0);
        break;
    }
}

void Adc::setAlign(adc_align_t align) {
    mAlign = align;
    mRefAlign &= ~(1 << ADLAR);
    if (mAlign == ADC_LEFT) {
        mRefAlign |= (1 << ADLAR);
    }
}

uint16_t Adc::read(uint8_t channel) {
    channel &= 7;
    ADMUX = mRefAlign | channel;
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

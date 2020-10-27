/*
 * adc.h
 *
 * Created: 25/10/2020 21:10:44
 *  Author: Cliff
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

class Adc {
public:
    typedef enum {
        ADC_AREF,
        ADC_AVCC_REF,
        ADC_INT_2V56,
    } adc_ref_t;

    typedef enum {
        ADC_LEFT,
        ADC_RIGHT
    } adc_align_t;

    Adc(uint8_t divider = 64, adc_ref_t ref = ADC_AVCC_REF, adc_align_t align = ADC_RIGHT);
    void setSpeed(uint8_t divider);
    void setRef(adc_ref_t ref);
    void setAlign(adc_align_t align);
    uint16_t read(uint8_t channel);
private:
    adc_ref_t mRef;
    adc_align_t mAlign;
    uint8_t mRefAlign;
    uint8_t mScale;
};



#endif /* ADC_H_ */
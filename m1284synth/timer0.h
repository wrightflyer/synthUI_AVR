/*
 *  timer0.h
 *
 * Created: 24/10/2020 18:24:30
 *  Author: Cliff
 */


#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>
#include <avr/interrupt.h>

class Timer0 {
public:
    typedef void (*tim_cback)(void);
    enum timer0_mode_t {
        TIM0_NORM,
        TIM0_PC_PWM,
        TIM0_CTC,
        TIM0_FAST_PWM,
        TIM0_PC_PWM_FREQ,
        TIM0_FAST_PWM_FREQ
    };
    enum timer0_int_t {
        TIM0_COMPA_ISR,
        TIM0_COMPB_ISR,
        TIM0_OVF_ISR
    };
    Timer0(timer0_mode_t mode, uint8_t range);
    void start(uint16_t prescale);
    void stop();
    void attachInterrupt(timer0_int_t type, tim_cback fn);
    tim_cback mOvfCback;
    tim_cback mCompACback;
    tim_cback mCompBCback;
};

#endif /* TIMER0_H_ */
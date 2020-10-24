/*
 *  timer0.cpp
 *
 * Created: 24/10/2020 18:23:46
 *  Author: Cliff
 */

#include "timer0.h"

Timer0 * pTimer0;

Timer0::Timer0(timer0_mode_t mode, uint8_t range) {
    switch (mode) {
    case TIM0_NORM:
        TCCR0 = (0 << WGM01) | (0 << WGM00);
        break;
    case TIM0_PC_PWM:
        TCCR0 = (0 << WGM01) | (1 << WGM00);
        break;
    case TIM0_CTC:
        TCCR0 = (1 << WGM01) | (0 << WGM00);
        break;
    case TIM0_FAST_PWM:
        TCCR0 = (1 << WGM01) | (1 << WGM00);
        break;
    };
    OCR0 = range - 1;
    pTimer0 = this; // hopefully there's only 1 instance ;-)
}

void Timer0::start(uint16_t prescale) {
    TCCR0 &= 0xF8;
    TCNT0 = 0;
    switch(prescale) {
    case 1:
        TCCR0 = (1 << CS00);
        break;
    case 8:
        TCCR0 = (1 << CS01);
        break;
    case 64:
        TCCR0 = (1 << CS01) | (1 << CS00);
        break;
    case 256:
        TCCR0 = (1 << CS02);
        break;
    case 1024:
        TCCR0 = (1 << CS02) | (1 << CS00);
        break;
    };
}

void Timer0::stop() {
    TCCR0 &= 0xF8;
}

void Timer0::attachInterrupt(timer0_int_t type, tim_cback fn) {
    if (type == TIM0_COMP_ISR) {
        if (fn) {
            mCompCback = fn;
            TIMSK |= (1 << OCIE0);
            sei();
        }
        else {
            TIMSK &= ~(1 << OCIE0);
        }
    }
    else if (type == TIM0_OVF_ISR) {
        if (fn) {
            mOvfCback = fn;
            TIMSK |= (1 << TOIE0);
            sei();
        }
        else {
            TIMSK &= ~(1 << TOIE0);
        }
    }
};

ISR(TIMER0_COMP_vect) {
    if (pTimer0) {
        if (pTimer0->mCompCback) {
            pTimer0->mCompCback();
        }
    }
}

ISR(TIMER0_OVF_vect) {
    if (pTimer0) {
        if (pTimer0->mOvfCback) {
            pTimer0->mOvfCback();
        }
    }
}
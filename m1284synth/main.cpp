#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "encoder.h"
#include "uart.h"
#include "timer0.h"
#include "button.h"
#include "dualjoystick.h"

void timerUpdate(void);

Encoder enc1(&PORTC, 0, 1);
Encoder enc2(&PORTC, 6, 7);
Encoder enc3(&PORTD, 0, 1);
Encoder enc4(&PORTD, 2, 3);
Encoder enc5(&PORTD, 4, 5);
Encoder enc6(&PORTD, 6, 7);
Encoder enc7(&PORTB, 0, 1);
Encoder enc8(&PORTB, 2, 3);
Button but1(&PORTC, 2, Button::NO_PULL_UP);
Button but2(&PORTC, 3, Button::NO_PULL_UP);
Button but3(&PORTC, 4, Button::NO_PULL_UP);
Button but4(&PORTC, 5, Button::NO_PULL_UP);
Button but5(&PORTA, 4, Button::NO_PULL_UP);
Button but6(&PORTA, 5, Button::NO_PULL_UP);
Button but7(&PORTA, 6, Button::NO_PULL_UP);
Button but8(&PORTA, 7, Button::NO_PULL_UP);
Uart uart(1, 9600);
Timer0 tim(Timer0::TIM0_CTC, 100);
DualJoystick joy(0, 1, 64);

int main(void) {
    int32_t prev1 = 0, prev2 = 0, pos;
    uint16_t prevX = 0, prevY = 0;

    // allow a start with JTAG on to "break in"
    _delay_ms(4000);
    // but if we don't then skip these JTAG will be disabled.
    MCUCR = (1 << JTD);
    MCUCR = (1 << JTD);

    uart.connectStdio();
    printf("Hello World\r\n");

    tim.start(64);
    tim.attachInterrupt(Timer0::TIM0_COMPA_ISR, timerUpdate);

    while(1) {
        pos = enc1.read();
        if (pos != prev1) {
            printf("Pos1 = %ld\r\n", pos);
            prev1 = pos;
        }
        pos = enc2.read();
        if (pos != prev2) {
            printf("Pos2 = %ld\r\n", pos);
            prev2 = pos;
        }
        if (but1.read() == 0) {
            printf("Reset1");
            enc1.readAndReset();
        }
        if (but2.read() == 0) {
            printf("Reset2");
            enc2.readAndReset();
        }
        DualJoystick::reading_t reading;
        reading = joy.read();
        if (abs(reading.x - prevX) > 4 || abs(reading.y - prevY) > 4) {
            printf("Joy X=%d, Y=%d\r\n", reading.x, reading.y);
            prevX = reading.x;
            prevY = reading.y;
        }
    }
}

void timerUpdate(void) {
    enc1.intUpdate();
    enc2.intUpdate();
    enc3.intUpdate();
    enc4.intUpdate();
    enc5.intUpdate();
    enc6.intUpdate();
    enc7.intUpdate();
    enc8.intUpdate();
    but1.update();
    but2.update();
    but3.update();
    but4.update();
    but5.update();
    but6.update();
    but7.update();
    but8.update();
}

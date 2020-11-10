#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "encoder.h"
#include "uart.h"
#include "timer0.h"
#include "button.h"
#include "dualjoystick.h"

void timerUpdate(void);

///////////// PORT A //////////////
DualJoystick joy(0, 1, 64); // on A0/A1
// A2 - unused
Button  butJoy(&PORTA, 3, Button::NO_PULL_UP);
Button  but1(  &PORTA, 4, Button::NO_PULL_UP);
Button  but2(  &PORTA, 5, Button::NO_PULL_UP);
Button  but3(  &PORTA, 6, Button::NO_PULL_UP);
Button  but4(  &PORTA, 7, Button::NO_PULL_UP);

///////////// PORT B //////////////
Encoder enc1(  &PORTB, 0, 1);
Encoder enc2(  &PORTB, 2, 3);
Encoder enc3(  &PORTB, 4, 5); // SPI on 5/6/7 (with SS on 4)
// B6 / B7 - unused

///////////// PORT C //////////////
Encoder enc4(  &PORTC, 0, 1);
Button  but5(  &PORTC, 2, Button::NO_PULL_UP); // 2..5 are the JTAG pins
Button  but6(  &PORTC, 3, Button::NO_PULL_UP);
Button  but7(  &PORTC, 4, Button::NO_PULL_UP);
Button  but8(  &PORTC, 5, Button::NO_PULL_UP);
Encoder enc5(  &PORTC, 6, 7);

///////////// PORT D //////////////
Uart uart(9600); // on D0 / D1
Encoder enc6(  &PORTD, 2, 3);
Encoder enc7(  &PORTD, 4, 5);
Encoder enc8(  &PORTD, 6, 7);

Timer0  tim(Timer0::TIM0_CTC, 100);

int main(void) {
    int32_t prev1 = 0, prev2 = 0, pos;
    uint16_t prevX = 0, prevY = 0;

    _delay_ms(4000);
    MCUCSR = (1 << JTD);
    MCUCSR = (1 << JTD);

    uart.connectStdio();
    printf("Hello World\r\n");

    tim.start(64);
    tim.attachInterrupt(Timer0::TIM0_COMP_ISR, timerUpdate);
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
            printf("Reset1\r\n");
            enc1.readAndReset();
            _delay_ms(1000);
        }
        if (but2.read() == 0) {
            printf("Reset2\r\n");
            enc2.readAndReset();
            _delay_ms(1000);
        }
        DualJoystick::reading_t reading;
        reading = joy.read();
        //reading.x = 0;
        //reading.y = 0;
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

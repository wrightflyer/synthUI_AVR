#include <avr/io.h>

#include "encoder.h"
#include "uart.h"
#include "timer0.h"

Encoder enc(&PORTC, 0, 1);
Uart uart(9600);
Timer0 tim(Timer0::TIM0_CTC, 36);

int main(void) {
    int32_t prev = 0, pos;
    uart.connectStdio();
    printf("Hello\r\n");
    tim.start(1024);
    tim.attachInterrupt(Timer0::TIM0_COMP_ISR, (Timer0::tim_cback)&Encoder::intUpdate);
    while(1) {
        pos = enc.read();
        if (pos != prev) {
            printf("Pos = %ld\r\n", pos);
            prev = pos;
        }
    }
}

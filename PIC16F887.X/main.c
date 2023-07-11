#include <xc.h>
#include "header.h"

void system_init() {
    //        IO cho blink_led
    TRISC = 0x00;
    PORTC = 0x00;
    //        IO cho button
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB6 = 1;
    //    IO cho led7seg
    TRISD = 0x00;
    PORTD = 0x00;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    //    IO cho uart
    TRISC6 = 0; //TX
    TRISC7 = 1; //RX
    //    IO cho ADC
    TRISEbits.TRISE2 = 1;
}

void main() {
    ANSEL = 0x00;
    ANSELH = 0x00;
    nRBPU = 0;
    WPUB = 0xFF;
    system_init();
//    app_blink_led_init();
//    app_btn1_init();
//    app_timer0_init();
//    app_btn2_init();
    app_led7_init();
    app_uart_init();
    while (1) {
//        app_blink_led_task();
//        app_btn1_task();
//        app_timer0_task();
//        app_btn2_task();
        app_led7_task();
        app_uart_task();
    }
}

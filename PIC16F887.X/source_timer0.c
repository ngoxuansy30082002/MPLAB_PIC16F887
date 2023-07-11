#include <xc.h>
#include "header.h"

timer0_data appTimer0Data;

void app_timer0_init() {
    OPTION_REG = 0b00000101;
    TMR0 = 100;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    // co the viet gon la GIE = 1;
    INTCONbits.PEIE = 1;
    appTimer0Data.timer0_count = 0;
    appTimer0Data.timer0_delayValue = 100;
    appTimer0Data.state = timer0_init;
//    PEIE = 0;
}

void __interrupt() timer_isr(void) {
    if (TMR0IF == 1) {
        TMR0 = 101;
        TMR0IF = 0;
        appTimer0Data.timer0_count++;
    }
}

void app_timer0_task() {
    switch (appTimer0Data.state) {
        case timer0_init:
        {
            appTimer0Data.state = timer0_start;
            break;
        }
        case timer0_start:
        {
            if (appTimer0Data.timer0_count == appTimer0Data.timer0_delayValue)
                appTimer0Data.state = timer0_end;
            break;
        }
        case timer0_end:
        {
            appTimer0Data.state = timer0_start;
            appTimer0Data.timer0_count = 0;
            break;
        }
    }

}

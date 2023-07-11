#include <xc.h>
#include "header.h"

Led_data appledData;

void app_blink_led_init() {
    appledData.state = Led_init;
    appledData.led_value = 0;
};

void app_blink_led_task() {
    PORTC = appledData.led_value;
    switch (appledData.state) {
        case Led_init:
        {
            appledData.state = Led_wait;
            break;
        }
        case Led_wait:
        {
            if (appTimer0Data.state == timer0_end)
                if (appledData.state != Led_off)
                    appledData.state = Led_change;
            break;
        }
        case Led_change:
        {
            appledData.led_value = ~appledData.led_value;
            appledData.state = Led_wait;
            break;
        }
        case Led_off:
        {
            appledData.led_value = 0b01010101;
            break;
        }
        default: break;
    }
};


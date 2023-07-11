#include <xc.h>
#include "header.h"

btn1_data appBtn1Data;
int pressed = 0;

void app_btn1_init() {
    appBtn1Data.state = btn1_init;
    appBtn1Data.btn1_count = 0;
};

void app_btn1_task() {
    appBtn1Data.btn1_count++;
    switch (appBtn1Data.state) {
        case btn1_init:
        {
            if (RB7 == 1)
                appBtn1Data.state = btn1_high;
            if (RB7 == 0)
                appBtn1Data.state = btn1_low;
            break;
        }
        case btn1_high:
        {
            if (RB7 == 0) {
                appBtn1Data.state = btn1_debounce;
            }
            appBtn1Data.btn1_count = 0;
            break;
        }
        case btn1_low:
        {
            if (RB7 == 1) {
                appBtn1Data.state = btn1_debounce;
                pressed = 1;
            }
            appBtn1Data.btn1_count = 0;
            break;
        }
        case btn1_debounce:
        {
            if (appBtn1Data.btn1_count == 20) {
                if (RB7 == 0)
                    appBtn1Data.state = btn1_low;
                if (RB7 == 1)
                    appBtn1Data.state = btn1_done;
                appBtn1Data.btn1_count = 0;
            }
            break;
        }
        case btn1_done:
        {
            if (pressed == 1) {
                if (appledData.state == Led_off)
                    appledData.state = Led_change;
                else appledData.state = Led_off;
                pressed = 0;
            }
            appBtn1Data.state = btn1_high;
            break;
        }
        default: break;
    }
};

#include <xc.h>
#include "header.h"

btn2_data appBtn2Data;
int pressed = 0;

void app_btn2_init() {
    appBtn2Data.state = btn2_init;
    appBtn2Data.btn2_count = 0;
};

void app_btn2_task() {
    appBtn2Data.btn2_count++;
    switch (appBtn2Data.state) {
        case btn2_init:
        {
            if (RB6 == 1)
                appBtn2Data.state = btn2_high;
            if (RB6 == 0)
                appBtn2Data.state = btn2_low;
            break;
        }
        case btn2_high:
        {
            if (RB6 == 0) {
                appBtn2Data.state = btn2_debounce;
            }
            appBtn2Data.btn2_count = 0;
            break;
        }
        case btn2_low:
        {
            if (RB6 == 1) {
                appBtn2Data.state = btn2_debounce;
                pressed = 1;
            }
            appBtn2Data.btn2_count = 0;
            break;
        }
        case btn2_debounce:
        {
            if (appBtn2Data.btn2_count == 20) {
                if (RB6 == 0)
                    appBtn2Data.state = btn2_low;
                if (RB6 == 1)
                    appBtn2Data.state = btn2_done;
                appBtn2Data.btn2_count = 0;
            }
            break;
        }
        case btn2_done:
        {
            if (pressed == 1) {
                appled7Data.value++;
                appled7Data.state = led7seg_init;
                pressed = 0;
            }
            appBtn2Data.state = btn2_high;
            break;
        }
        default: break;
    }
};



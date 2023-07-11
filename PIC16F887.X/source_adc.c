#include <xc.h>
#include "header.h"

adc_data app_adcData;

int count_delay = 0;

void app_adc_init() {
    ADCON0 = 0b10011101;
    ADCON1 = 0b00000000;
    ANSELbits.ANS7 = 1;
    app_adcData.state = adc_init;
};

int read_value() {
    ADCON0bits.GO_nDONE = 1;
    while (GO_nDONE);
    return ((ADRESH << 8) + ADRESL);
};

void app_adc_task() {
    switch (app_adcData.state) {
        case adc_init:
        {
            count_delay = 0;
            __delay_ms(2);
            app_adcData.state = adc_read;
            break;
        }
        case adc_read:
        {
            count_delay = 0;
            app_adcData.value = read_value();
            app_adcData.state = adc_done;
            break;
        }
        case adc_done:
        {
            //
            //
            app_adcData.state = adc_wait;
            count_delay = 0;
            break;
        }
        case adc_wait:
        {
            if (count_delay == 50)
                app_adcData.state = adc_read;
            break;
        }
    }
};
#include <xc.h>
#include "header.h"

led7seg_data appled7Data;

#define so_0 0X3F
#define so_1 0X06
#define so_2 0X5B
#define so_3 0X4F
#define so_4 0X66
#define so_5 0X6D
#define so_6 0X7D
#define so_7 0X07
#define so_8 0X7F
#define so_9 0X6F

#define led1 RB0 
#define led2 RB1 
#define led3 RB2 
#define led4 RB3 


int count_time = 0;
int values[5];
int next_index_led;
unsigned int seg_data[] = {so_0, so_1, so_2, so_3, so_4, so_5, so_6, so_7, so_8, so_9};

void handle_value(int value) {
    values[4] = value % 10;
    values[3] = (value / 10) % 10;
    values[2] = (value / 100) % 10;
    values[1] = (value / 1000) % 10;
}

void display(int i) {
    PORTD = seg_data[i];
}

void app_led7_init() {
    appled7Data.state = led7seg_init;
    appled7Data.value = 0000;
}

void app_led7_task() {
    count_time++;
    switch (appled7Data.state) {
        case led7seg_init:
        {
            appled7Data.state = led7seg_1;
            handle_value(appled7Data.value);
            break;
        }
        case led7seg_1:
        {
            led1 = 0;
            led2 = 1;
            led3 = 1;
            led4 = 1;
            display(values[1]);
            next_index_led = 2;
            appled7Data.state = led7seg_wait;
            count_time = 0;
            break;
        }
        case led7seg_2:
        {
            led1 = 1;
            led2 = 0;
            led3 = 1;
            led4 = 1;
            display(values[2]);
            next_index_led = 3;
            appled7Data.state = led7seg_wait;
            count_time = 0;
            break;
        }
        case led7seg_3:
        {
            led1 = 1;
            led2 = 1;
            led3 = 0;
            led4 = 1;
            display(values[3]);
            next_index_led = 4;
            appled7Data.state = led7seg_wait;
            count_time = 0;
            break;
        }
        case led7seg_4:
        {
            led1 = 1;
            led2 = 1;
            led3 = 1;
            led4 = 0;
            display(values[4]);
            next_index_led = 1;
            appled7Data.state = led7seg_wait;
            count_time = 0;
            break;
        }
        case led7seg_wait:
        {
            //            __delay_ms(1000);
            if (count_time == 100)
                appled7Data.state = next_index_led;
            break;
        }
    }

}



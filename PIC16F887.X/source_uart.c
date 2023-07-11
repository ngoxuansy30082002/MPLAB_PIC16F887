#include <xc.h>
#include "header.h"
#define BaudRate 9600
#define INT2POINTER(a) ((char*)(intptr_t)(a))
#define POINTER2INT(a) ((int)(intptr_t)(a))
//!@1234a

uart_data app_uartData;

int do_actionn = 0;
char datas[6];
int index_data = 0;

int data_receiving = 0;
char pre_data = ' ';
char cur_data = ' ';
int pass = 0;

void common_init() {
    BRGH = 1;
    BRG16 = 0;
    SYNC = 0;
    SPEN = 1;
    SPBRG = ((_XTAL_FREQ / 16) / BaudRate) - 1;
    //    SPBRG = 51;
    PEIE = 1;
    GIE = 1;
}

void transmit_init() {
    TX9 = 0;
    TXEN = 1;
    TXIE = 0;
}

void receive_init() {
    RX9 = 0;
    CREN = 1;
    RCIE = 0;
}

char getdata() {
    if (OERR) {
        CREN = 0;
        CREN = 1;
    }
    while (!RCIF);
    return RCREG;
}

void send_chardata(char data) {
    while (!TXIF);
    TXREG = data;
}

void send_stringdata(char *s) {
    while (*s)
        send_chardata(*s++);
}

void check_err() {
    int i = 4;
    while (i) {
        if (datas[i] < 48 || datas[i] > 57) {
            app_uartData.is_err = '1';
            return;
        }
        i--;
    }
    if (datas[5] != 'a') {
        app_uartData.is_err = '1';
        return;
    }
    app_uartData.is_err == '0';
}

void action(char data) {
    cur_data = data;
    if (cur_data == '@' && pre_data == '!') {
        data_receiving = 1;
        pass = 1;
        index_data = 0;
        app_uartData.is_err = '0';
    }
    pre_data = cur_data;

    if (data_receiving) {
        datas[index_data] = data;
        index_data++;
        if (index_data == 6)
            data_receiving = 0;
    }
    if (data == 'a' && index_data == 6) {
        do_actionn = 1;
        pre_data = ' ';
        cur_data = ' ';
        index_data = 0;
    }
    if (do_actionn) {
        check_err();
        if (app_uartData.is_err == '0') {
            int a = datas[1] - '0';
            int b = datas[2] - '0';
            int c = datas[3] - '0';
            int d = datas[4] - '0';
            appled7Data.value = a * 1000 + b * 100 + c * 10 + d * 1;
            appled7Data.state = led7seg_init;
        }
    }
}

void app_uart_init() {
    common_init();
    transmit_init();
    receive_init();
    app_uartData.state = uart_init;
}

void app_uart_task() {
    switch (app_uartData.state) {
        case uart_init:
        {
            app_uartData.receive_state = wait_receive;
            app_uartData.is_err = '0';
            app_uartData.state = uart_wait;
            break;
        }
        case uart_getdata:
        {
            app_uartData.value = getdata();
            action(app_uartData.value);
            //            receive_state(app_uartData.value);
            app_uartData.state = uart_wait;
            break;
        }
        case uart_senddata:
        {
            if (pass) {
                if (app_uartData.is_err == '0') {
                    send_chardata(datas[1]);
                    send_chardata(datas[2]);
                    send_chardata(datas[3]);
                    send_chardata(datas[4]);
                }
                if (app_uartData.is_err == '1')
                    send_stringdata("Error");
                pass = 0;
            }
            app_uartData.state = uart_wait;
            break;
        }
        case uart_wait:
        {
            if (!RCIDL)
                app_uartData.state = uart_getdata;
            if (do_actionn) {
                app_uartData.state = uart_senddata;
                do_actionn = 0;
            }
            break;
        }
        default: break;
    }
}
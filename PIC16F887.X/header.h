/* 
 * File:   header_led.h
 * Author: dell
 *
 * Created on February 17, 2023, 3:47 PM
 */

#ifndef HEADER_LED_H
#define	HEADER_LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#pragma config FOSC = HS        
#pragma config WDTE = OFF      
#pragma config PWRTE = OFF      
#pragma config BOREN = ON       
#pragma config LVP = OFF       
#pragma config CPD = OFF        
#pragma config WRT = OFF       
#pragma config CP = OFF        
#define _XTAL_FREQ 8000000 

    // ----------------------header cho blink_led---------------------------------//

    typedef enum {
        Led_init,
        Led_wait,
        Led_change,
        Led_off
    } led_states;

    typedef struct {
        led_states state;
        int led_value;
    } Led_data;
    extern Led_data appledData;
    void app_blink_led_init();
    void app_blink_led_task();

    //   --------------------- header cho timer0 -----------------------------//

    typedef enum {
        timer0_init,
        timer0_start,
        timer0_end
    } timer0_states;

    typedef struct {
        timer0_states state;
        int timer0_count;
        int timer0_delayValue;
    } timer0_data;
    extern timer0_data appTimer0Data;
    void app_timer0_init();
    void app_timer0_task();

    //  ----------------------  header cho keyinput1 --------------------------//

    typedef enum {
        btn1_init,
        btn1_high,
        btn1_debounce,
        btn1_low,
        btn1_done
    } btn1_states;

    typedef struct {
        btn1_states state;
        int btn1_count;
    } btn1_data;
    extern btn1_data appBtn1Data;
    void app_btn1_init();
    void app_btn1_task();

    //  ----------------------  header cho keyinput2 --------------------------//

    typedef enum {
        btn2_init,
        btn2_high,
        btn2_debounce,
        btn2_low,
        btn2_done
    } btn2_states;

    typedef struct {
        btn2_states state;
        int btn2_count;
    } btn2_data;
    extern btn2_data appBtn2Data;
    void app_btn2_init();
    void app_btn2_task();

    //  -------------------------- header cho led7seg -----------------------//

    typedef enum {
        led7seg_init,
        led7seg_1,
        led7seg_2,
        led7seg_3,
        led7seg_4,
        led7seg_wait
    } led7seg_states;

    typedef struct {
        led7seg_states state;
        int value;
    } led7seg_data;
    extern led7seg_data appled7Data;
    void app_led7_init();
    void app_led7_task();

     //-----------------------------header cho uart--------------------------//

    typedef enum {
        uart_init,
        uart_getdata,
        uart_senddata,
        uart_wait
    } uart_states;

    typedef enum {
        wait_receive,
        data_receive,
        check_error,
        do_action
    } receive_states;

    typedef struct {
        uart_states state;
        receive_states receive_state;
        char is_err;
        char value;
    } uart_data;
    extern uart_data app_uartData;
    void app_uart_init();
    void app_uart_task();
    
    //----------------------------- header cho ADC -----------------------//

    typedef enum {
        adc_init,
        adc_read,
        adc_done,
        adc_wait
    } adc_states;

    typedef struct {
        adc_states state;
        int value;
    } adc_data;
    extern adc_data app_adcData;
    void app_adc_init();
    void app_adc_task();

#ifdef	__cplusplus
}
#endif

#endif	

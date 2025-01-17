//
// Created by Yan_X on 2022/3/21.
//

#ifndef ESP_RTOS_LEDS_H
#define ESP_RTOS_LEDS_H

#include "esp_common.h"
#include "gpio.h"

#define HIGH 1
#define LOW 0
#define LED_BUILTIN GPIO_Pin_2

enum LedStatus {
    LED_OFF, LED_ALWAYS_ON, LED_BLINK_FAST, LED_BLINK_ONCE
};

xTaskHandle blinkFastTaskHandle = 0;
enum LedStatus ledStatus = LED_OFF;

void init_led() {
    GPIO_AS_OUTPUT(LED_BUILTIN);
    ledStatus = LED_ALWAYS_ON;
}

void set_builtin_led_on() {
    GPIO_OUTPUT(GPIO_Pin_2, LOW);
}

void set_builtin_led_off() {
    GPIO_OUTPUT(GPIO_Pin_2, HIGH);
}

void led_prepare() {
    if (ledStatus == LED_OFF)
        return;

    switch (ledStatus) {
        case LED_BLINK_FAST:
            vTaskDelete(blinkFastTaskHandle);
            break;
        default:
            break;
    }
    set_builtin_led_off();
}

_Noreturn void task_blink_fast(void *ignore) {
    portTickType xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

    while (true) {
        set_builtin_led_on();
        vTaskDelayUntil(&xLastWakeTime, 250 / portTICK_RATE_MS);

        set_builtin_led_off();
        vTaskDelayUntil(&xLastWakeTime, 250 / portTICK_RATE_MS);
    }

    vTaskDelete(NULL);
}

_Noreturn void task_blink_once(void *ignore) {
    set_builtin_led_on();
    vTaskDelay(40 / portTICK_RATE_MS);
    set_builtin_led_off();

    ledStatus = LED_OFF;
    vTaskDelete(NULL);
}

void led_blink_fast() {
    int result;

    led_prepare();

    result = xTaskCreate(&task_blink_fast, (const signed char *) "blink_fast", 512, NULL, 3, &blinkFastTaskHandle);
    if (result == pdTRUE) {
        ledStatus = LED_BLINK_FAST;
    }
}

void led_always_on() {
    led_prepare();
    set_builtin_led_on();
    ledStatus = LED_ALWAYS_ON;
}


void led_blink_once() {
    if (ledStatus != LED_OFF) {
        led_prepare();
        vTaskDelay(40 / portTICK_RATE_MS);
    }
    ledStatus = LED_BLINK_ONCE;

    xTaskCreate(&task_blink_once, (const signed char *) "blink_once", 512, NULL, 3, NULL);
}


void led_off() {
    led_prepare();
    ledStatus = LED_OFF;
}

#endif //ESP_RTOS_LEDS_H

#include "scheduler.h"

#include "ti_msp_dl_config.h"

#include "driver/adc.h"
#include "driver/gpio.h"
#include "driver/timer.h"
#include "driver/uart.h"
#include "handler/communication.h"

static enum power_mode_t current_power_mode;

void scheduler_init() {
    gpio_init();                                // in addition to what is done in ti_msp_dl_config.c
    adc_init();
    timer_init();
    // uart_init();                                // now called by comm. init

    adc_convert();

    communication_init();

    current_power_mode = HIGH_POWER;
}

void scheduler_high_power() {
    while (current_power_mode == HIGH_POWER) {
        // while (has_permtick_elapsed() == 0 && has_systick_elapsed()) {
        //     __WFI();
        // }

        // if (has_permtick_elapsed() == 1) {
        //     permtick_count();
        //     gpio_toggle();
        // }

        // if (has_systick_elapsed() == 1) {
        //     //
        // }
    }
}

void scheduler_low_power() {
    //
}

void scheduler_power_down() {
    //
}

enum power_mode_t get_power_mode() {
    return current_power_mode;
}

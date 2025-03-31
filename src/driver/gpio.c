#include "gpio.h"
// #include "driver/gpio.h"
#include "../ti_msp_dl_config.h"

void gpio_init() {
    //
}

void gpio_toggle() {
    DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_0);
}

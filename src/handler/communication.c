#include "communication.h"
#include "../driver/uart.h"
#include <sys/_stdint.h>
#include "../ti_msp_dl_config.h"
#define START_BYTE  0x55

enum state_t {
    IDLE,
    PAYLOAD,
    END
};

enum state_t current_state = IDLE;

static uint8_t cache = 0;
// static uint8_t timeout_count = 0;

static void uart_callback(uint8_t data);

void communication_init() {
    uart_init(&uart_callback);
}

static void uart_callback(uint8_t data) {
    switch (current_state) {
        case IDLE:
        if (data == 0x61) {
            current_state = PAYLOAD;
        }
        break;

        case PAYLOAD:
        cache = data;
        current_state = END;
        break;

        case END:
        if (data == 0x63) {
            DL_TimerA_setCaptureCompareValue(PWM_0_INST, (250 - cache), DL_TIMER_CC_0_INDEX);
            if (cache == 250) {
                DL_GPIO_clearPins(LED_PORT, LED_PIN_0_PIN);
            }
            else {
                DL_GPIO_setPins(LED_PORT, LED_PIN_0_PIN);
            }
        }
        current_state = IDLE;
        break;

        default:
        break;
    }
}

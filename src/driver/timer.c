#include "timer.h"
// #include "driver/timer.h"
#include "../ti_msp_dl_config.h"

static volatile uint8_t permtick_temp;
static volatile uint8_t systick_temp;
static uint32_t permtick_cnt;
static uint32_t systick_cnt;
static uint32_t permtick_cnt_accumulated;
static uint32_t systick_cnt_accumulated;

void timer_init() {
    SYSCFG_DL_SYSTICK_init();
    SYSCFG_DL_PERMTICK_init();

    NVIC_EnableIRQ(PERMTICK_INST_INT_IRQN);
}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gSYSTICKClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * SYSTICK_INST_LOAD_VALUE = (0 ms * 32000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gSYSTICKTimerConfig = {
    .period     = SYSTICK_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void) {

    DL_TimerG_setClockConfig(SYSTICK_INST,
        (DL_TimerG_ClockConfig *) &gSYSTICKClockConfig);

    DL_TimerG_initTimerMode(SYSTICK_INST,
        (DL_TimerG_TimerConfig *) &gSYSTICKTimerConfig);
    DL_TimerG_enableClock(SYSTICK_INST);





}

/*
 * Timer clock configuration to be sourced by LFCLK /  (32768 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32768 Hz = 32768 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPERMTICKClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_LFCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * PERMTICK_INST_LOAD_VALUE = (1000 ms * 32768 Hz) - 1
 */
static const DL_TimerG_TimerConfig gPERMTICKTimerConfig = {
    .period     = PERMTICK_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_PERMTICK_init(void) {

    DL_TimerG_setClockConfig(PERMTICK_INST,
        (DL_TimerG_ClockConfig *) &gPERMTICKClockConfig);

    DL_TimerG_initTimerMode(PERMTICK_INST,
        (DL_TimerG_TimerConfig *) &gPERMTICKTimerConfig);
    DL_TimerG_enableInterrupt(PERMTICK_INST , DL_TIMERG_INTERRUPT_LOAD_EVENT);
    DL_TimerG_enableClock(PERMTICK_INST);
}

void PERMTICK_INST_IRQHandler() {
    permtick_temp++;
}

void permtick_count() {
    if (permtick_temp > 0) {
        permtick_temp--;
        permtick_cnt++;
        permtick_cnt_accumulated++;
    }
}
uint8_t has_permtick_elapsed() {
    uint8_t ret = false;
    if (permtick_temp > 0) {
        ret = 1;
    }
    return ret;
}

void SYSTICK_INST_IRQHandler() {
    systick_temp++;
}

void systick_count() {
    if (systick_temp > 0) {
        systick_temp--;
        systick_cnt++;
        systick_cnt_accumulated++;
    }
}

uint8_t has_systick_elapsed() {
    bool ret = false;
    if (systick_temp > 0) {
        ret = true;
    }
    return ret;
}

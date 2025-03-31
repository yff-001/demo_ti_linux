/* MSPM0L1306 */

#include "ti_msp_dl_config.h"

#include "scheduler.h"

#define DSSM_BASE       (0x40028000U)  // Base address of DSSM
#define DSSM_TXDATA     (*(volatile uint32_t *)(DSSM_BASE + 0x0C))  // TX Data Register
#define DSSM_STATUS     (*(volatile uint32_t *)(DSSM_BASE + 0x04))  // Status Register
#define DSSM_TXREADY    (1 << 1)  // TX Ready flag

void dssm_send(uint32_t data) {
    while (!(DSSM_STATUS & DSSM_TXREADY));  // Wait until TX is ready
    DSSM_TXDATA = data;  // Send data
}

int main(void)
{
    SYSCFG_DL_init();

    // dssm_send(0xDEADBEEF);

    scheduler_init();

    while (1) {
        dssm_send(0xDEADBEEF);
        switch(get_power_mode()) {
            case HIGH_POWER:
                // scheduler_start();
                scheduler_high_power();
                // scheduler_stop();
                break;
            case LOW_POWER:
                scheduler_low_power();
                break;
            case POWER_DOWN:
                scheduler_power_down();
                break;
            default:
                break;
            }
    }
}

/* MSPM0L1306 */

#include "ti_msp_dl_config.h"

#include "scheduler.h"

int main(void)
{
    SYSCFG_DL_init();

    scheduler_init();

    while (1) {
        switch (get_power_mode()) {
            case HIGH_POWER:
            scheduler_high_power();
            break;

            default:
            break;
        }
    }
}

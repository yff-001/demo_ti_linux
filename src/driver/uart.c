#include "uart.h"
// #include "driver/uart.h"
#include "../ti_msp_dl_config.h"
#include <sys/_stdint.h>

static volatile uint8_t rx_data = 0;
static void (*write_buffer)(uint8_t);

void uart_init(void(*callback)(uint8_t)) {
    // SYSCFG_DL_UART_0_init();
    // NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    // write_buffer = callback;
}

// static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
//     .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
//     .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
// };

// static const DL_UART_Main_Config gUART_0Config = {
//     .mode        = DL_UART_MAIN_MODE_NORMAL,
//     .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
//     .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
//     .parity      = DL_UART_MAIN_PARITY_NONE,
//     .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
//     .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
// };

// SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
// {
//     DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

//     DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
//     /*
//      * Configure baud rate by setting oversampling and baud rate divisors.
//      *  Target baud rate: 9600
//      *  Actual baud rate: 9600.24
//      */
//     DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
//     DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_32_MHZ_9600_BAUD, UART_0_FBRD_32_MHZ_9600_BAUD);



//     DL_UART_Main_enable(UART_0_INST);
// }

// void uart_send_byte(uint8_t data) {
//     DL_UART_Main_transmitDataBlocking(UART_0_INST, data);
// }

// void UART_0_INST_IRQHandler() {

//     switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
//         case DL_UART_IIDX_RX:
//         rx_data = DL_UART_Main_receiveData(UART_0_INST);
//         write_buffer(rx_data);
//         break;

//         default:
//         break;
//     }
// }

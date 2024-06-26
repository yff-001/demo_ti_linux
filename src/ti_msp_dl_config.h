#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0L130X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for SYSTICK */
#define SYSTICK_INST                                                     (TIMG14)
#define SYSTICK_INST_IRQHandler                                 TIMG1_IRQHandler
#define SYSTICK_INST_INT_IRQN                                   (TIMG1_INT_IRQn)
#define SYSTICK_INST_LOAD_VALUE                                             (0U)
/* Defines for PERMTICK */
#define PERMTICK_INST                                                    (TIMG8)
#define PERMTICK_INST_IRQHandler                                TIMG0_IRQHandler
#define PERMTICK_INST_INT_IRQN                                  (TIMG0_INT_IRQn)
#define PERMTICK_INST_LOAD_VALUE                                            (0U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_18
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_17
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM19)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM18)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM19_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM18_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_0_FBRD_32_MHZ_9600_BAUD                                        (21)





/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOA)

/* Defines for PIN_0: GPIOA.0 with pinCMx 1 on package pin 1 */
#define LED_PIN_0_PIN                                            (DL_GPIO_PIN_0)
#define LED_PIN_0_IOMUX                                           (IOMUX_PINCM1)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_SYSTICK_init(void);
void SYSCFG_DL_PERMTICK_init(void);
void SYSCFG_DL_UART_0_init(void);



#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */

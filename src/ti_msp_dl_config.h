#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0C110X

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


#define CPUCLK_FREQ                                                     24000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA0
#define PWM_0_INST_IRQHandler                                   TIMA0_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             12000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                          DL_GPIO_PIN_2
#define GPIO_PWM_0_C0_IOMUX                                       (IOMUX_PINCM3)
#define GPIO_PWM_0_C0_IOMUX_FUNC                      IOMUX_PINCM3_PF_TIMA0_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_CMPL_PORT                                            GPIOA
#define GPIO_PWM_0_C0_CMPL_PIN                                    DL_GPIO_PIN_17
#define GPIO_PWM_0_C0_CMPL_IOMUX                                 (IOMUX_PINCM18)
#define GPIO_PWM_0_C0_CMPL_IOMUX_FUNC           IOMUX_PINCM18_PF_TIMA0_CCP0_CMPL




/* Defines for SYSTICK */
#define SYSTICK_INST                                                    (TIMG14)
#define SYSTICK_INST_IRQHandler                                TIMG14_IRQHandler
#define SYSTICK_INST_INT_IRQN                                  (TIMG14_INT_IRQn)
#define SYSTICK_INST_LOAD_VALUE                                           (159U)
/* Defines for PERMTICK */
#define PERMTICK_INST                                                    (TIMG8)
#define PERMTICK_INST_IRQHandler                                TIMG8_IRQHandler
#define PERMTICK_INST_INT_IRQN                                  (TIMG8_INT_IRQn)
#define PERMTICK_INST_LOAD_VALUE                                        (15999U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_26
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_27
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM27)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM28)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM27_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM28_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (250000)
#define UART_0_IBRD_24_MHZ_250000_BAUD                                       (6)
#define UART_0_FBRD_24_MHZ_250000_BAUD                                       (0)





/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOA)

/* Defines for PIN_0: GPIOA.4 with pinCMx 5 on package pin 9 */
#define LED_PIN_0_PIN                                            (DL_GPIO_PIN_4)
#define LED_PIN_0_IOMUX                                           (IOMUX_PINCM5)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_SYSTICK_init(void);
void SYSCFG_DL_PERMTICK_init(void);
void SYSCFG_DL_UART_0_init(void);



#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */

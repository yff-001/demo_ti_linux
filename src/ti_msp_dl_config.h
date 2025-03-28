/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0L130X
 *  by the SysConfig tool.
 */
 #ifndef ti_msp_dl_config_h
 #define ti_msp_dl_config_h

 #define CONFIG_MSPM0L130X
 #define CONFIG_MSPM0L1306

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




 /* Defines for ADC12_0 */
 #define ADC12_0_INST                                                        ADC0
 #define ADC12_0_INST_IRQHandler                                  ADC0_IRQHandler
 #define ADC12_0_INST_INT_IRQN                                    (ADC0_INT_IRQn)
 #define ADC12_0_ADCMEM_BAT                                    DL_ADC12_MEM_IDX_0
 #define ADC12_0_ADCMEM_BAT_REF                 DL_ADC12_REFERENCE_VOLTAGE_INTREF
 #define ADC12_0_ADCMEM_BAT_REF_VOLTAGE_V                                    2.50
 #define ADC12_0_ADCMEM_CHG                                    DL_ADC12_MEM_IDX_1
 #define ADC12_0_ADCMEM_CHG_REF                 DL_ADC12_REFERENCE_VOLTAGE_INTREF
 #define ADC12_0_ADCMEM_CHG_REF_VOLTAGE_V                                    2.50
 #define ADC12_0_ADCMEM_NTC                                    DL_ADC12_MEM_IDX_2
 #define ADC12_0_ADCMEM_NTC_REF                 DL_ADC12_REFERENCE_VOLTAGE_INTREF
 #define ADC12_0_ADCMEM_NTC_REF_VOLTAGE_V                                    2.50
 #define ADC12_0_ADCMEM_MOT                                    DL_ADC12_MEM_IDX_3
 #define ADC12_0_ADCMEM_MOT_REF                 DL_ADC12_REFERENCE_VOLTAGE_INTREF
 #define ADC12_0_ADCMEM_MOT_REF_VOLTAGE_V                                    2.50
 #define GPIO_ADC12_0_C8_PORT                                               GPIOA
 #define GPIO_ADC12_0_C8_PIN                                       DL_GPIO_PIN_16
 #define GPIO_ADC12_0_C0_PORT                                               GPIOA
 #define GPIO_ADC12_0_C0_PIN                                       DL_GPIO_PIN_27
 #define GPIO_ADC12_0_C7_PORT                                               GPIOA
 #define GPIO_ADC12_0_C7_PIN                                       DL_GPIO_PIN_18


 /* Defines for VREF */
 #define VREF_VOLTAGE_MV                                                     2500
 #define VREF_READY_DELAY                                                   (320)




 /* Port definition for Pin Group IN */
 #define IN_PORT                                                          (GPIOA)

 /* Defines for MODE: GPIOA.2 with pinCMx 3 on package pin 6 */
 #define IN_MODE_PIN                                              (DL_GPIO_PIN_2)
 #define IN_MODE_IOMUX                                             (IOMUX_PINCM3)
 /* Port definition for Pin Group OUT */
 #define OUT_PORT                                                         (GPIOA)

 /* Defines for LDO: GPIOA.6 with pinCMx 7 on package pin 10 */
 #define OUT_LDO_PIN                                              (DL_GPIO_PIN_6)
 #define OUT_LDO_IOMUX                                             (IOMUX_PINCM7)
 /* Defines for ENOP: GPIOA.7 with pinCMx 8 on package pin 11 */
 #define OUT_ENOP_PIN                                             (DL_GPIO_PIN_7)
 #define OUT_ENOP_IOMUX                                            (IOMUX_PINCM8)
 /* Defines for LED_BAT: GPIOA.1 with pinCMx 2 on package pin 2 */
 #define OUT_LED_BAT_PIN                                          (DL_GPIO_PIN_1)
 #define OUT_LED_BAT_IOMUX                                         (IOMUX_PINCM2)
 /* Defines for LED_OP1: GPIOA.0 with pinCMx 1 on package pin 1 */
 #define OUT_LED_OP1_PIN                                          (DL_GPIO_PIN_0)
 #define OUT_LED_OP1_IOMUX                                         (IOMUX_PINCM1)

 /* clang-format on */

 void SYSCFG_DL_init(void);
 void SYSCFG_DL_initPower(void);
 void SYSCFG_DL_GPIO_init(void);
 void SYSCFG_DL_SYSCTL_init(void);
 void SYSCFG_DL_ADC12_0_init(void);
 void SYSCFG_DL_VREF_init(void);



 #ifdef __cplusplus
 }
 #endif

 #endif /* ti_msp_dl_config_h */

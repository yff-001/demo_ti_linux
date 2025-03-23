#include "adc.h"

#include "../ti_msp_dl_config.h"

volatile bool gCheckADC = false;
volatile uint16_t ADCResult[4];

void adc_init() {
  NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
}

void adc_convert() {
  while (1) {
    DL_ADC12_startConversion(ADC12_0_INST);

    while (gCheckADC == false) {
      __WFE();
    }

    gCheckADC = false;

    ADCResult[0] = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);
    ADCResult[1] = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_1);
    ADCResult[2] = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_2);
    ADCResult[3] = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_3);

    DL_ADC12_enableConversions(ADC12_0_INST);
  }
  // DL_ADC12_startConversion(ADC12_0_INST);

  // while (gCheckADC == false) {
  //   __WFE();
  // }

  // x = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);

  // DL_ADC12_enableConversions(ADC12_0_INST);
}

void ADC12_0_INST_IRQHandler(void)
{
  switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
    case DL_ADC12_IIDX_MEM3_RESULT_LOADED:
      gCheckADC = true;

      /*
        used to examine ADC sampling frequency
        DL_ADC12_setSampleTime0() sets entire duration of sampling
        f = f_ADC / integer value passed to function
      */
      DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_0);
      break;
    default:
      break;
  }
}

//
// Created by Oguz Kagan YAGLIOGLU on Oct 17, 2022.
// www.oguzkagan.xyz
//

/**
 * GPIO driver ADC test code
 * If the read analog value is more significant than or equal to 2048, the green led will blink constantly.
 * Otherwise, LED will preserve its last state.
 * 
 * NOTE: In this test, a pot connected to the AN0(PE3)
 * */


#include "tm4c123gh6pm.h"

void softDelay() {
  uint32_t i;
  for (i = 0; i < 200000; ++i) asm("nop");
}

void GPIOF_IntHandler() {}

int main(void)
{
  GPIO_Handle_t LED_GPIO;
  LED_GPIO.pGPIOx_BaseAddress = GPIOF_AHB;
  LED_GPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_3;
  LED_GPIO.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
  LED_GPIO.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
  GPIO_Init(&LED_GPIO);

  GPIO_Handle_t POT;
  POT.pGPIOx_BaseAddress = GPIO_PORT_AHB_AN0;
  POT.GPIO_PinConfig.PinNumber = GPIO_PIN_AN0;
  POT.GPIO_PinConfig.PinCNF = GPIO_CNF_IN_AN;
  POT.GPIO_PinConfig.PinPuPdControl = GPIO_PU;
  POT.pADCx_BaseAddress = ADC0;
  POT.ADC_PinConfig.ADC_Number = AN0;
  POT.ADC_PinConfig.SR = ADC_SAMPLING_RATE_125K;
  POT.ADC_PinConfig.SS = ADC_SS3;
  POT.ADC_PinConfig.SSCTL = ADC_SSCTL_SIE | ADC_SSCTL_EOS;

  GPIO_Init(&POT);

  uint32_t adc_value;

  while (true) {
    POT.pADCx_BaseAddress->PSSI |= (1 << POT.ADC_PinConfig.SS);
    while ((POT.pADCx_BaseAddress->RIS & (1 << 3)) == 0);
    adc_value = POT.pADCx_BaseAddress->SS[POT.ADC_PinConfig.SS].SSFIFO;
    POT.pADCx_BaseAddress->ISC |= (1 << POT.ADC_PinConfig.SS);
    if (adc_value >= 2048) GPIO_TogglePin_H(&LED_GPIO);
    softDelay();
  }

  return 0;
}

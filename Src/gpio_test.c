//
// Created by Oguz Kagan YAGLIOGLU on Oct 9, 2022.
// www.oguzkagan.xyz
//

/**
 * GPIO driver test code
 * As long as the button is pressed, the green LED will blink.
 * LED will preserve its last state when the button is released.
 * */

#include "tm4c123gh6pm.h"

void softDelay() {
  uint32_t i;
  for (i = 0; i < 200000; ++i) asm("nop");
}

int main(void)
{
  GPIO_Handle_t LED_GPIO;
  LED_GPIO.pGPIOx_BaseAddress = GPIOF_AHB;
  LED_GPIO.GPIO_PinConfig.BusControl = GPIO_BUS_AHB;
  LED_GPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_3;
  LED_GPIO.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
  LED_GPIO.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
  GPIO_Init(&LED_GPIO);

  GPIO_Handle_t BUTTON_GPIO;
  BUTTON_GPIO.pGPIOx_BaseAddress = GPIOF_AHB;
  BUTTON_GPIO.GPIO_PinConfig.BusControl = GPIO_BUS_AHB;
  BUTTON_GPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_4;
  BUTTON_GPIO.GPIO_PinConfig.PinCNF = GPIO_CNF_IN;
  BUTTON_GPIO.GPIO_PinConfig.PinPuPdControl = GPIO_PU;
  GPIO_Init(&BUTTON_GPIO);

  while (true) {
    if (!GPIO_ReadPin_H(&BUTTON_GPIO)) {
      GPIO_TogglePin_H(&LED_GPIO);
      softDelay();
    }
  }

  return 0;
}

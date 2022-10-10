//
// Created by Oguz Kagan YAGLIOGLU on Oct 9, 2022.
// www.oguzkagan.xyz
//

/**
 * GPIO driver IRQ test code
 * The red led will blink constantly.
 * When the sw1 button is pressed blue led will toggle
 * */

#include "tm4c123gh6pm.h"

void softDelay() {
    uint32_t i;
    for (i = 0; i < 200000; ++i) asm("nop");
}

GPIO_Handle_t RED_LED_GPIO;
GPIO_Handle_t BLUE_LED_GPIO;
GPIO_Handle_t BUTTON_GPIO;


int main(void)
{
    RED_LED_GPIO.pGPIOx_BaseAddress = GPIOF_AHB;
    RED_LED_GPIO.GPIO_PinConfig.BusControl = GPIO_BUS_AHB;
    RED_LED_GPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_1;
    RED_LED_GPIO.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
    RED_LED_GPIO.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
    GPIO_Init(&RED_LED_GPIO);

    BLUE_LED_GPIO.pGPIOx_BaseAddress = GPIOF_AHB;
    BLUE_LED_GPIO.GPIO_PinConfig.BusControl = GPIO_BUS_AHB;
    BLUE_LED_GPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_2;
    BLUE_LED_GPIO.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
    BLUE_LED_GPIO.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
    GPIO_Init(&BLUE_LED_GPIO);

    BUTTON_GPIO.pGPIOx_BaseAddress = GPIOF_AHB;
    BUTTON_GPIO.GPIO_PinConfig.BusControl = GPIO_BUS_AHB;
    BUTTON_GPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_4;
    BUTTON_GPIO.GPIO_PinConfig.PinCNF = GPIO_CNF_IN;
    BUTTON_GPIO.GPIO_PinConfig.PinPuPdControl = GPIO_PU;
    BUTTON_GPIO.GPIO_PinConfig.IRQ_trigger = GPIO_IRQ_TRIG_FE;
    GPIO_Init(&BUTTON_GPIO);
    GPIO_IRQConfig_H(&BUTTON_GPIO, ENABLE);
    GPIO_IRQSetPriority(GPIOF_AHB, NVIC_IRQ_PRIORITY_3);

    while (true) {
        GPIO_TogglePin_H(&RED_LED_GPIO);
        softDelay();
    }

    return 0;
}


void GPIOF_IntHandler() {
    //check if interrupt caused by PF4
    if (GPIO_IRQCausedByThis_H(&BUTTON_GPIO)) {
        GPIO_TogglePin_H(&BLUE_LED_GPIO);
        GPIO_IRQHandling_H(&BUTTON_GPIO);
    }
}

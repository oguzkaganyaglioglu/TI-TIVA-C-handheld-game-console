//
// Created by Oguz Kagan YAGLIOGLU on Oct 20, 2022.
// www.oguzkagan.xyz
//

/**
 * SPI driver write test code
 * This code sends Hello World message repeatedly
 * 
 * PINS:
 *      MISO -> D2 // not used in this example
 *      MOSI -> D3
 *      CLK  -> D0
 * 
 * NOTE: You can use a logic analyzer to see the output
 * */

#include "string.h"
#include "tm4c123gh6pm.h"

void softDelay() {
    uint32_t i;
    for (i = 0; i < 200000; ++i) asm("nop");
}

void GPIOF_IntHandler() {}

GPIO_Handle_t SPI_MISO;
GPIO_Handle_t SPI_MOSI;
GPIO_Handle_t SPI_CLK;

SPI_Handle_t mySPI;

int main(void)
{
    SPI_CLK.pGPIOx_BaseAddress = GPIOD_AHB;
    SPI_CLK.GPIO_PinConfig.PinNumber = GPIO_PIN_0;
    SPI_CLK.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
    SPI_CLK.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
    SPI_CLK.GPIO_PinConfig.PinAltFuncMode = 2;

    SPI_MOSI.pGPIOx_BaseAddress = GPIOD_AHB;
    SPI_MOSI.GPIO_PinConfig.PinNumber = GPIO_PIN_3;
    SPI_MOSI.GPIO_PinConfig.PinCNF = GPIO_CNF_OUT_PP;
    SPI_MOSI.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
    SPI_MOSI.GPIO_PinConfig.PinAltFuncMode = 2;

    SPI_MISO.pGPIOx_BaseAddress = GPIOD_AHB;
    SPI_MISO.GPIO_PinConfig.PinNumber = GPIO_PIN_2;
    SPI_MISO.GPIO_PinConfig.PinCNF = GPIO_CNF_IN;
    SPI_MISO.GPIO_PinConfig.PinPuPdControl = GPIO_NO_PU_PD;
    SPI_MISO.GPIO_PinConfig.PinAltFuncMode = 2;

    mySPI.pSPI = SPI1;
    mySPI.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
    mySPI.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
    mySPI.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV_4;
    mySPI.SPI_Config.SPI_DeviceMode = SPI_DeviceMode_MASTER;
    mySPI.SPI_Config.SPI_DFF = SPI_DFF_8BITS;

    GPIO_Init(&SPI_MISO);
    GPIO_Init(&SPI_MOSI);
    GPIO_Init(&SPI_CLK);

    SPI_Init(&mySPI);

    char buffer[] = "Hello World\r\n";
    while (true) {

        softDelay();
        SPI_SendData_blocking(mySPI.pSPI, (uint8_t*)buffer, strlen(buffer));

    }
    return 0;
}

//
// Created by Oguz Kagan YAGLIOGLU on Oct 19, 2022.
// www.oguzkagan.xyz
//

#include "tm4c123gh6pm_spi.h"

void SPI_Init(SPI_Handle_t* pSPIHandle) {
    // enable peripheral clock
    SPI_PeriClockControl(pSPIHandle->pSPI, true);

    // disable peripheral
    SPI_PeriControl(pSPIHandle->pSPI, false);

    // set device mode
    switch (pSPIHandle->SPI_Config.SPI_DeviceMode) {
    case SPI_DeviceMode_MASTER:
        pSPIHandle->pSPI->CR1 &= ~(1 << SPI_CR1_MS);
        break;
    case SPI_DeviceMode_SLAVE:
        pSPIHandle->pSPI->CR1 |= (1 << SPI_CR1_MS);
        break;
    case SPI_DeviceMode_SLAVE_RX_ONLY:
        // DATASHEET->SSI->Initialization and Configuration,
        // For slave mode (output disabled), set the SSICR1 register to 0x0000.000C. 
        pSPIHandle->pSPI->CR1 |= (1 << SPI_CR1_MS);

        // this is a reserved bit but initialization section points that i should set it
        pSPIHandle->pSPI->CR1 |= (1 << 3);
        break;
    }

    // set clock source 
    pSPIHandle->pSPI->CC = 0; //system clock

    //set clock divider
    pSPIHandle->pSPI->CPSR = pSPIHandle->SPI_Config.SPI_SclkSpeed;

    // set serial clock rate as 0
    pSPIHandle->pSPI->CR0 = ~(0xFF << SPI_CR0_SCR);

    //set SPI clock phase
    if (pSPIHandle->SPI_Config.SPI_CPHA == SPI_CPHA_LOW) pSPIHandle->pSPI->CR0 &= ~(1 << SPI_CR0_SPH);
    else pSPIHandle->pSPI->CR0 |= (1 << SPI_CR0_SPH);

    // set SPI clock polarity
    if (pSPIHandle->SPI_Config.SPI_CPOL == SPI_CPOL_LOW) pSPIHandle->pSPI->CR0 &= ~(1 << SPI_CR0_SPO);
    else pSPIHandle->pSPI->CR0 |= (1 << SPI_CR0_SPO);

    // select Freescale SPI Frame Format
    pSPIHandle->pSPI->CR0 &= ~(0b11 << SPI_CR0_FRF);

    // set data size
    pSPIHandle->pSPI->CR0 &= ~(0b1111 << SPI_CR0_DSS); // clear
    pSPIHandle->pSPI->CR0 |= (pSPIHandle->SPI_Config.SPI_DFF << SPI_CR0_DSS); // set

    // enable peripheral
    SPI_PeriControl(pSPIHandle->pSPI, true);
}

void SPI_PeriClockControl(SPI_RegDef_t* pSPIx, bool EnOrDi) {
    if (EnOrDi) {
        if (pSPIx == SSI0) SPI0_PCLK_EN_W(true);
        else if (pSPIx == SSI1) SPI1_PCLK_EN_W(true);
        else if (pSPIx == SSI2) SPI2_PCLK_EN_W(true);
        else if (pSPIx == SSI3) SPI3_PCLK_EN_W(true);
    }
    else {
        if (pSPIx == SSI0) SPI0_PCLK_DI();
        else if (pSPIx == SSI1) SPI1_PCLK_DI();
        else if (pSPIx == SSI2) SPI2_PCLK_DI();
        else if (pSPIx == SSI3) SPI3_PCLK_DI();
    }
}


void SPI_PeriControl(SPI_RegDef_t* pSPIx, bool EnOrDi) {
    if (EnOrDi) pSPIx->CR1 |= (1 << SPI_CR1_SSE);
    else pSPIx->CR1 &= ~(1 << SPI_CR1_SSE);
}

void SPI_SendData_blocking(SPI_RegDef_t* pSPIx, uint8_t* pTxBuffer, uint32_t len) {
    uint8_t* buffer = pTxBuffer;
    uint32_t _len = len;
    while (len > 0 && _len >= len) {
        // wait for fifo to be not full
        while (!(pSPIx->SR & (1 << SPI_SR_TNF)));

        // send data
        if (((pSPIx->CR0 >> SPI_CR0_DSS) & 0xF) == SPI_DFF_16BITS) {
            //16bit data
            pSPIx->DR = *((uint16_t*)buffer++);
            len--;
        }
        else {
            //8bit data
            pSPIx->DR = *((uint8_t*)buffer++);
        }
        len--;

        //wait untill transmition complete
        while ((pSPIx->SR & (1 << SPI_SR_BSY)));

    }
}


void SPI_ReceiveData_blocking(SPI_RegDef_t* pSPIx, uint8_t* pRxBuffer, uint32_t len) {

}

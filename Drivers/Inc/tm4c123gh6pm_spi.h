//
// Created by Oguz Kagan YAGLIOGLU on Oct 19, 2022.
// www.oguzkagan.xyz
//

#ifndef DRIVERS_INC_TM4C123GH6PM_SPI_H_
#define DRIVERS_INC_TM4C123GH6PM_SPI_H_

#include "tm4c123gh6pm.h"

/**
 * @SPI_DeviceModes
 * */
#define SPI_DeviceMode_MASTER               0
#define SPI_DeviceMode_SLAVE                1
#define SPI_DeviceMode_SLAVE_RX_ONLY        2


/**
 * @SPI_ClkSpeed
 * */
#define SPI_SCLK_SPEED_DIV_2        2
#define SPI_SCLK_SPEED_DIV_4        4
#define SPI_SCLK_SPEED_DIV_8        8
#define SPI_SCLK_SPEED_DIV_16       16
#define SPI_SCLK_SPEED_DIV_32       32
#define SPI_SCLK_SPEED_DIV_64       64
#define SPI_SCLK_SPEED_DIV_128      128
#define SPI_SCLK_SPEED_DIV_254      254

/**
 * @SPI_DFF
 * */
#define SPI_DFF_8BITS       0x7
#define SPI_DFF_16BITS      0xF

/**
 * @SPI_CPOL
 * */
#define SPI_CPOL_LOW        0
#define SPI_CPOL_HIGH       1

/**
 * @SPI_CPHA
 * */
#define SPI_CPHA_LOW        0
#define SPI_CPHA_HIGH       1

/**
 * @SPI_SSM
 * */
#define SPI_SSM_EN          1
#define SPI_SSM_DI          0


/*
 * Configuration structure for SPIx peripheral
 * */
typedef struct {
    uint8_t SPI_DeviceMode;     /** possible values from @SPI_DeviceModes */
    uint8_t SPI_SclkSpeed;      /** possible values from @SPI_ClkSpeed */
    uint8_t SPI_DFF;            /** possible values from @SPI_DFF */
    uint8_t SPI_CPOL;           /** possible values from @SPI_CPOL */
    uint8_t SPI_CPHA;           /** possible values from @SPI_CPHA */
} SPI_Config_t;

/*
 * Handle structure for SPIx peripheral
 * */
typedef struct {
    SPI_RegDef_t* pSPI;         // This pointer holds the base address of the SPIx peripheral 
    SPI_Config_t SPI_Config;    // This variable holds the SPI configuration settings
} SPI_Handle_t;



/**
 * @fn          SPI_Init
 *
 * @brief       This function initializes the given SPI peripheral
 *
 * @param[in]   pSPIHandle
 *
 * @return      none
 *
 * @note        none
 * */
void SPI_Init(SPI_Handle_t* pSPIHandle);

/**
 * @fn          SPI_PeriClockControl
 *
 * @brief       This function enables or disables peripheral clock for the given SPI peripheral
 *
 * @param[in]   pSPIx    base address of the SPI peripheral
 * @param[in]   EnOrDi   ENABLE or DISABLE macros
 *
 * @return      none
 *
 * @note        none
 * */
void SPI_PeriClockControl(SPI_RegDef_t* pSPIx, bool EnOrDi);

/**
 * @fn          SPI_PeriControl
 *
 * @brief       This function enables or disables the given SPI peripheral
 *
 * @param[in]   pSPIx    base address of the SPI peripheral
 * @param[in]   EnOrDi   ENABLE or DISABLE macros
 *
 * @return      none
 *
 * @note        none
 * */
void SPI_PeriControl(SPI_RegDef_t* pSPIx, bool EnOrDi);

/**
 * @fn          SPI_SendData_blocking
 *
 * @brief       Sends len bytes from pTxBuffer
 *
 * @param[in]   pSPIx       base address of the SPI peripheral
 * @param[in]   pTxBuffer   data buffer to send
 * @param[in]   len         data buffer length
 *
 * @return      none
 *
 * @note        blocks until all data is transferred
 * */
void SPI_SendData_blocking(SPI_RegDef_t* pSPIx, uint8_t* pTxBuffer, uint32_t len);

#endif /* DRIVERS_INC_TM4C123GH6PM_SPI_H_ */

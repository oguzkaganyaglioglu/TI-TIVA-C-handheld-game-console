//
// Created by Oguz Kagan YAGLIOGLU on Oct 6, 2022.
// www.oguzkagan.xyz
//

#ifndef DRIVERS_INC_TM4C123GH6PM_GPIO_H_
#define DRIVERS_INC_TM4C123GH6PM_GPIO_H_

#include "tm4c123gh6pm.h"

/**
 * @GPIO_PIN_NUMBERS
 * GPIO pin numbers
 * */
#define GPIO_PIN_0                          0
#define GPIO_PIN_1                          1
#define GPIO_PIN_2                          2
#define GPIO_PIN_3                          3
#define GPIO_PIN_4                          4
#define GPIO_PIN_5                          5
#define GPIO_PIN_6                          6
#define GPIO_PIN_7                          7


/**
 * @GPIO_PIN_PU_PD
 * */
#define GPIO_NO_PU_PD                       0
#define GPIO_PU                             1
#define GPIO_PD                             2

/**
 * @GPIO_PIN_CNF
 * */
#define GPIO_CNF_IN                         0 // General purpose input
#define GPIO_CNF_IN_A                       1 // Analog mode

#define GPIO_CNF_OUT_PP                     4 // General purpose output push-pull
#define GPIO_CNF_OUT_OD                     5 // General purpose output Open-drain
#define GPIO_CNF_OUT_AF_PP                  6 // Alternate function output Push-pull
#define GPIO_CNF_OUT_AF_OD                  7 // Alternate function output Open-drain

/**
 * @GPIO_BUS
 * */
#define GPIO_BUS_APB                        0 // Advanced Peripheral Bus (APB). This bus is the legacy bus.
#define GPIO_BUS_AHB                        1 // Advanced High-Performance Bus (AHB)

typedef struct {
    uint8_t PinNumber;                 /** possible values from @GPIO_PIN_NUMBERS */
    uint8_t PinCNF;                    /** possible values from @GPIO_PIN_CNF */
    uint8_t PinPuPdControl;            /** possible values from @GPIO_PIN_PU_PD */
    uint8_t PinAltFuncMode;
    uint8_t BusControl;                /** possible values from @GPIO_BUS */
} GPIO_PinConfig_t;

typedef struct {
    GPIO_RegDef_t* pGPIOx_BaseAddress;      //This pointer holds the base address of the GPIO port
    GPIO_PinConfig_t GPIO_PinConfig;        //This pointer holds the GPIO pin configuration settings
} GPIO_Handle_t;


/**
 * @fn          GPIO_Init
 *
 * @brief       This function initializes the GPIO peripheral for the given port
 *
 * @param[in]   pGPIOHandle
 *
 * @return      none
 *
 * @note        none
 * */
void GPIO_Init(GPIO_Handle_t* pGPIOHandle);

/**
 * @fn          GPIO_DeInit
 *
 * @brief       This function deinitializes the GPIO peripheral
 *
 * @param[in]   GPIO_RegDef_t base address of the GPIO peripheral for the given port
 *
 * @return      none
 *
 * @note        none
 * */
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx);

/**
 * @fn          GPIO_PeriClockControl
 *
 * @brief       This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]   pGPIOx   base address of the GPIO peripheral
 * @param[in]   EnOrDi   ENABLE or DISABLE macros
 *
 * @return      none
 *
 * @note        none
 * */
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, bool EnOrDi);
void GPIO_PeriClockControl_H(GPIO_Handle_t* pGPIOHandle, bool EnOrDi);

/**
 * @fn          GPIO_ReadPin
 *
 * @brief       This function reads the value from a specified GPIO pin
 *
 * @param[in]   pGPIOx      base address of the GPIO peripheral
 * @param[in]   PinNumber   pin number, possible values from @GPIO_PIN_NUMBERS
 *
 * @return      GPIO pin value: true (HIGH) or false (LOW)
 *
 * @note        none
 * */
bool GPIO_ReadPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);
bool GPIO_ReadPin_H(GPIO_Handle_t* pGPIOHandle);

/**
 * @fn          GPIO_ReadPort
 *
 * @brief       This function reads the value from a specified GPIO port
 *
 * @param[in]   pGPIOx      base address of the GPIO peripheral
 *
 * @return      GPIO port value: uint8_t
 *
 * @note        none
 * */
uint8_t GPIO_ReadPort(GPIO_RegDef_t* pGPIOx);
uint8_t GPIO_ReadPort_H(GPIO_Handle_t* pGPIOHandle);

/**
 * @fn          GPIO_WritePin
 *
 * @brief       This function writes a value to the specified GPIO pin
 *
 * @param[in]   pGPIOx      base address of the GPIO peripheral
 * @param[in]   PinNumber   pin number, possible values from @GPIO_PIN_NUMBERS
 * @param[in]   Value       true: HIGH, false: LOW
 *
 * @return      none
 *
 * @note        if the pin is configured as INPUT; value(true) enable pull-up resistor, value(false) enable pull-down resistor
 * */
void GPIO_WritePin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, bool Value);
void GPIO_WritePin_H(GPIO_Handle_t* pGPIOHandle, bool Value);

/**
 * @fn          GPIO_WritePort
 *
 * @brief       This function writes the value to the specified GPIO port
 *
 * @param[in]   pGPIOx      base address of the GPIO peripheral
 * @param[in]   Value       value to be written to the GPIO port. 1:HIGH, 0:LOW
 *
 * @return      none
 *
 * @note        if a pin is configured as INPUT; 1 enable pull-up resistor, 0 enable pull-down resistor
 * */
void GPIO_WritePort(GPIO_RegDef_t* pGPIOx, uint8_t Value);
void GPIO_WritePort_H(GPIO_Handle_t* pGPIOHandle, uint8_t Value);

/**
 * @fn          GPIO_TogglePin
 *
 * @brief       This function toggles the specified GPIO pin
 *
 * @param[in]   pGPIOx      base address of the GPIO peripheral
 * @param[in]   PinNumber   pin number, possible values from @GPIO_PIN_NUMBERS
 *
 * @return      none
 *
 * @note        none
 * */
void GPIO_TogglePin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);
void GPIO_TogglePin_H(GPIO_Handle_t* pGPIOHandle);

#endif /* DRIVERS_INC_TM4C123GH6PM_GPIO_H_ */

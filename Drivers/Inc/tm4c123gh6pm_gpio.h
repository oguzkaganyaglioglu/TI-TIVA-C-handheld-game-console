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
#define GPIO_PIN_0              0
#define GPIO_PIN_1              1
#define GPIO_PIN_2              2
#define GPIO_PIN_3              3
#define GPIO_PIN_4              4
#define GPIO_PIN_5              5
#define GPIO_PIN_6              6
#define GPIO_PIN_7              7


/**
 * @GPIO_PIN_PU_PD
 * */
#define GPIO_NO_PU_PD           0
#define GPIO_PU                 1
#define GPIO_PD                 2

/**
 * @GPIO_PIN_CNF
 * */
#define GPIO_CNF_IN             0 // General purpose input
#define GPIO_CNF_IN_A           1 // Analog mode

#define GPIO_CNF_OUT_PP         4 // General purpose output push-pull
#define GPIO_CNF_OUT_OD         5 // General purpose output Open-drain
#define GPIO_CNF_OUT_AF_PP      6 // Alternate function output Push-pull
#define GPIO_CNF_OUT_AF_OD      7 // Alternate function output Open-drain

/**
 * @GPIO_BUS
 * */
#define GPIO_BUS_APB            0 // Advanced Peripheral Bus (APB). This bus is the legacy bus.
#define GPIO_BUS_AHB            1 // Advanced High-Performance Bus (AHB)

/**
 * @GPIO_IRQ_TRIG
 * */
#define GPIO_IRQ_DISABLE        0 // Disable interrupt
#define GPIO_IRQ_TRIG_FE        1 // Interrupt trigger Falling Edge
#define GPIO_IRQ_TRIG_RE        2 // Interrupt trigger Rising Edge
#define GPIO_IRQ_TRIG_LL        4 // Interrupt trigger Low Level
#define GPIO_IRQ_TRIG_HL        8 // Interrupt trigger High Level

typedef struct {
    uint8_t PinNumber;            /** possible values from @GPIO_PIN_NUMBERS */
    uint8_t PinCNF;               /** possible values from @GPIO_PIN_CNF */
    uint8_t PinPuPdControl;       /** possible values from @GPIO_PIN_PU_PD */
    uint8_t PinAltFuncMode;
    uint8_t BusControl;           /** possible values from @GPIO_BUS */
    uint8_t IRQ_trigger;          /** possible values from @GPIO_IRQ_TRIG */
} GPIO_PinConfig_t;

typedef struct {
    GPIO_RegDef_t* pGPIOx_BaseAddress;  //This pointer holds the base address of the GPIO port
    GPIO_PinConfig_t GPIO_PinConfig;    //This pointer holds the GPIO pin configuration settings
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
 * @param[in]   pGPIOx  base address of the GPIO peripheral
 * @param[in]   EnOrDi  ENABLE or DISABLE macros
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
 * @param[in]   pGPIOx    base address of the GPIO peripheral
 * @param[in]   PinNumber  pin number, possible values from @GPIO_PIN_NUMBERS
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
 * @param[in]   pGPIOx  base address of the GPIO peripheral
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
 * @param[in]   pGPIOx    base address of the GPIO peripheral
 * @param[in]   PinNumber  pin number, possible values from @GPIO_PIN_NUMBERS
 * @param[in]   Value    true: HIGH, false: LOW
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
 * @param[in]   pGPIOx  base address of the GPIO peripheral
 * @param[in]   Value  value to be written to the GPIO port. 1:HIGH, 0:LOW
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
 * @param[in]   pGPIOx    base address of the GPIO peripheral
 * @param[in]   PinNumber  pin number, possible values from @GPIO_PIN_NUMBERS
 *
 * @return      none
 *
 * @note        none
 * */
void GPIO_TogglePin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);
void GPIO_TogglePin_H(GPIO_Handle_t* pGPIOHandle);

/**
 * @fn          GPIO_IRQConfig
 *
 * @brief       This function configures the specified IRQ
 *
 * @param[in]   pGPIOx    base address of the GPIO peripheral
 * @param[in]   PinNumber  pin number, possible values from @GPIO_PIN_NUMBERS
 * @param[in]   EnOrDi    ENABLE or DISABLE macros
 *
 * @return      none
 *
 * @note        DISABLE will not disable the interrupt, it will only mask the interrupt for the given pin.
 * */
void GPIO_IRQConfig(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t IRQ_trigger, bool EnOrDi);
void GPIO_IRQConfig_H(GPIO_Handle_t* pGPIOHandle, bool EnOrDi);

/**
 * @fn          GPIO_IRQSetPriority
 *
 * @brief       This function sets the priority of the specified IRQ
 *
 * @param[in]   pGPIOx    base address of the GPIO peripheral
 * @param[in]   IRQPriority  irq priority, possible values from @IRQ_PRIORITES
 *
 * @return      none
 *
 * @note        none
 * */
void GPIO_IRQSetPriority(GPIO_RegDef_t* pGPIOx, uint8_t IRQPriority);

/**
 * @fn          GPIO_IRQHandling
 *
 * @brief       This function handles the triggered IRQ
 *
 * @param[in]   pGPIOx    base address of the GPIO peripheral
 * @param[in]   PinNumber  pin number, possible values from @GPIO_PIN_NUMBERS
 *
 * @return      none
 *
 * @note        none
 * */
void GPIO_IRQHandling(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);
void GPIO_IRQHandling_H(GPIO_Handle_t* pGPIOHandle);

/**
 * @fn          GPIO_IRQCausedByThis
 *
 * @brief       This function checks if the interrupt is caused by given GPIO pin
 *
 * @param[in]   pGPIOx    base address of the GPIO peripheral
 * @param[in]   PinNumber  pin number, possible values from @GPIO_PIN_NUMBERS
 *
 * @return      bool    true: if interrupt caused by given gpio pin
 *
 * @note        none
 * */
bool GPIO_IRQCausedByThis(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);
bool GPIO_IRQCausedByThis_H(GPIO_Handle_t* pGPIOHandle);

#endif /* DRIVERS_INC_TM4C123GH6PM_GPIO_H_ */

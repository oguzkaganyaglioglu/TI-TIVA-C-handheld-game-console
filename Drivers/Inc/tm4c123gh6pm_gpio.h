//
// Created by Oguz Kagan YAGLIOGLU on Oct 6, 2022.
// www.oguzkagan.xyz
//

#ifndef DRIVERS_INC_TM4C123GH6PM_GPIO_H_
#define DRIVERS_INC_TM4C123GH6PM_GPIO_H_

#include "tm4c123gh6pm.h"

/**
 * @ADC_PORTS
 * */
#define GPIO_PORT_APB_AN0           GPIOE_APB
#define GPIO_PORT_APB_AN1           GPIOE_APB
#define GPIO_PORT_APB_AN2           GPIOE_APB
#define GPIO_PORT_APB_AN3           GPIOE_APB
#define GPIO_PORT_APB_AN4           GPIOD_APB
#define GPIO_PORT_APB_AN5           GPIOD_APB
#define GPIO_PORT_APB_AN6           GPIOD_APB
#define GPIO_PORT_APB_AN7           GPIOD_APB
#define GPIO_PORT_APB_AN8           GPIOE_APB
#define GPIO_PORT_APB_AN9           GPIOE_APB
#define GPIO_PORT_APB_AN10          GPIOB_APB
#define GPIO_PORT_APB_AN11          GPIOB_APB

#define GPIO_PORT_AHB_AN0           GPIOE_AHB
#define GPIO_PORT_AHB_AN1           GPIOE_AHB
#define GPIO_PORT_AHB_AN2           GPIOE_AHB
#define GPIO_PORT_AHB_AN3           GPIOE_AHB
#define GPIO_PORT_AHB_AN4           GPIOD_AHB
#define GPIO_PORT_AHB_AN5           GPIOD_AHB
#define GPIO_PORT_AHB_AN6           GPIOD_AHB
#define GPIO_PORT_AHB_AN7           GPIOD_AHB
#define GPIO_PORT_AHB_AN8           GPIOE_AHB
#define GPIO_PORT_AHB_AN9           GPIOE_AHB
#define GPIO_PORT_AHB_AN10          GPIOB_AHB
#define GPIO_PORT_AHB_AN11          GPIOB_AHB

/**
 * @ADC_Numbers
 * */
#define AN0            0
#define AN1            1
#define AN2            2
#define AN3            3
#define AN4            4
#define AN5            5
#define AN6            6
#define AN7            7
#define AN8            8
#define AN9            9
#define AN10           10
#define AN11           11

/**
 * @ADC_TRIGERS
 * */
#define ADC_TRIG_PROCESSOR            0x0
#define ADC_TRIG_ANALOG_CMP_0         0x1
#define ADC_TRIG_ANALOG_CMP_1         0x2
#define ADC_TRIG_EXT_GPIO             0x4
#define ADC_TRIG_TIMER                0x5
#define ADC_TRIG_PWM_GEN_0            0x6
#define ADC_TRIG_PWM_GEN_1            0x7
#define ADC_TRIG_PWM_GEN_2            0x8
#define ADC_TRIG_PWM_GEN_3            0x9
#define ADC_TRIG_ALWAYS               0xF

/**
 * @ADC_SS_Numbers
 * */
#define ADC_SS0            0
#define ADC_SS1            1
#define ADC_SS2            2
#define ADC_SS3            3

/**
 * @ADC_SS_CTL
 * */
#define ADC_SSCTL_SDIS      0b0001      // Sample Differential Input Select
#define ADC_SSCTL_EOS       0b0010      // End of Sequenc
#define ADC_SSCTL_SIE       0b0100      // Sample Interrupt Enable
#define ADC_SSCTL_STSS      0b1000      // 1st Sample Temp Sensor Select

/**
 * @ADC_SAMPLING_RATES
 * */
#define ADC_SAMPLING_RATE_125K       0x1 // 125 ksps
#define ADC_SAMPLING_RATE_250K       0x3 // 250 ksps
#define ADC_SAMPLING_RATE_500K       0x5 // 500 ksps
#define ADC_SAMPLING_RATE_1M         0x7 // 1 Msps

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
 * ADC pin numbers
 * */
#define GPIO_PIN_AN0    3
#define GPIO_PIN_AN1    2
#define GPIO_PIN_AN2    1
#define GPIO_PIN_AN3    0
#define GPIO_PIN_AN4    3
#define GPIO_PIN_AN5    2
#define GPIO_PIN_AN6    1
#define GPIO_PIN_AN7    0
#define GPIO_PIN_AN8    5
#define GPIO_PIN_AN9    4
#define GPIO_PIN_AN10   4
#define GPIO_PIN_AN11   5


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
#define GPIO_CNF_IN_AN          1 // Analog mode

#define GPIO_CNF_OUT_PP         4 // General purpose output push-pull
#define GPIO_CNF_OUT_OD         5 // General purpose output Open-drain
// #define GPIO_CNF_OUT_AF_PP      6 // Alternate function output Push-pull
// #define GPIO_CNF_OUT_AF_OD      7 // Alternate function output Open-drain

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
    uint8_t ADC_Number;             /** Possible values from @ADC_Numbers */
    uint8_t SS;                     /** Sample Sequencer. Possible values from @ADC_SS_Numbers */
    uint8_t SSCTL;                  /** Sample Sequencer Controller. Possible values from @ADC_SS_CTL */
    uint8_t SR;                     /** Sample Rate. Possible values from @ADC_SAMPLING_RATES */
    uint8_t TRIG;                   /** Trigger Source. Possible values from @ADC_TRIGERS */
} ADC_Config_t;

typedef struct {
    GPIO_RegDef_t* pGPIOx_BaseAddress;  //This pointer holds the base address of the GPIO port
    ADC_RegDef_t* pADCx_BaseAddress;    //This pointer holds the base address of the ADC port.
    ADC_Config_t ADC_PinConfig;         //This variable holds the ADC configuration settings
    GPIO_PinConfig_t GPIO_PinConfig;    //This variable holds the GPIO pin configuration settings
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

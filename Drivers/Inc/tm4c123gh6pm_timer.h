//
// Created by Oguz Kagan YAGLIOGLU on Oct 23, 2022.
// www.oguzkagan.xyz
//

#ifndef DRIVERS_INC_TM4C123GH6PM_TIMER_H_
#define DRIVERS_INC_TM4C123GH6PM_TIMER_H_

#include "tm4c123gh6pm.h"

/**
 * @SUBTIMERS
 * */
#define SUBTIMER_A      0
#define SUBTIMER_B      1
#define SUBTIMER_AB     2

/**
 * @TIMER_CFG
 * */
#define TIMER_CFG_16BIT         0x4
#define TIMER_CFG_32BIT         0x0
#define TIMER_CFG_32BIT_RTC     0x1

#define WTIMER_CFG_32BIT        0x4
#define WTIMER_CFG_64BIT        0x0
#define WTIMER_CFG_64BIT_RTC    0x1

/**
 * @TIMER_MODE
 * */
#define TIMER_MODE_ONE_SHOT     0x1
#define TIMER_MODE_PERIODIC     0x2
#define TIMER_MODE_CAPTURE      0x3

typedef struct {
    uint8_t subtimer;       /** possible values from @SUBTIMERS */
    uint8_t cfg;            /** possible values from @TIMER_CFG */
    uint8_t mode;           /** possible values from @TIMER_MODE */
    uint16_t prescaleA;     /** possible values between 0-255, in case of wide timer 0-65535 */
    uint16_t prescaleB;     /** possible values between 0-255, in case of wide timer 0-65535 */

    /** When a 32/64-bit Wide GPTM is configured to one of the 64-bit modes, intervalLoadA contains bits
    31:0 of the 64-bit count and the intervalLoadB contains bits 63:32.*/
    uint32_t intervalLoadA; /** possible values: 16bit timer => 0-65535, 32bit timer => 0-4294967295*/
    uint32_t intervalLoadB; /** possible values: 16bit timer => 0-65535, 32bit timer => 0-4294967295*/
} TIMER_Config_t;

typedef struct {
    TIMER_RegDef_t* pTIMERx_BaseAddress;    //This pointer holds the base address of the TIMERx
    TIMER_Config_t TIMER_Config;            //This variable holds the TIMER configuration settings
} TIMER_Handle_t;


/**
 * @fn          TIMER_Init
 *
 * @brief       This function initializes the given TIMER
 *
 * @param[in]   pTIMERHandle
 *
 * @return      none
 *
 * @note        none
 * */
void TIMER_Init(TIMER_Handle_t* pTIMERHandle);

/**
 * @fn          TIMER_PeriClockControl
 *
 * @brief       This function enables or disables peripheral clock for the given TIMER
 *
 * @param[in]   pTIMERx  base address of the TIMER peripheral
 * @param[in]   EnOrDi   ENABLE or DISABLE macros
 *
 * @return      none
 *
 * @note        none
 * */
void TIMER_PeriClockControl(TIMER_RegDef_t* pTIMERx, bool EnOrDi);
void TIMER_PeriClockControl_H(TIMER_Handle_t* pTIMERHandle, bool EnOrDi);

/**
 * @fn          TIMER_IRQConfig
 *
 * @brief       This function configures the specified IRQ
 *
 * @param[in]   pTIMERx    base address of the TIMER
 * @param[in]   subtimer   subtimer, possible values from @SUBTIMERS
 * @param[in]   EnOrDi     ENABLE or DISABLE macros
 *
 * @return      none
 *
 * @note        none
 * */
void TIMER_IRQConfig(TIMER_RegDef_t* pTIMERx, uint8_t subtimer, bool EnOrDi);
void TIMER_IRQConfig_H(TIMER_Handle_t* pTIMERHandle, bool EnOrDi);


/**
 * @fn          TIMER_IRQHandling
 *
 * @brief       This function handles the triggered IRQ
 *
 * @param[in]   pTIMERx   base address of the the TIMER
 * @param[in]   subtimer  subtimer, possible values from @SUBTIMERS
 *
 * @return      none
 *
 * @note        none
 * */
void TIMER_IRQHandling(TIMER_RegDef_t* pTIMERx, uint8_t subtimer);
void TIMER_IRQHandling_H(TIMER_Handle_t* pTIMERHandle);

/**
 * @fn          TIMER_IRQSuspend
 *
 * @brief       This function disables the NVIC for the specified IRQ
 *
 * @param[in]   pTIMERx    base address of the the TIMER
 * @param[in]   subtimer   subtimer, possible values from @SUBTIMERS
 *
 * @return      none
 *
 * @note        none
 * */
void TIMER_IRQSuspend(TIMER_RegDef_t* pTIMERx, uint8_t subtimer);
void TIMER_IRQSuspend_H(TIMER_Handle_t* pTIMERHandle);


/**
 * @fn          TIMER_IRQResume
 *
 * @brief       This function enables the NVIC for the specified IRQ
 *
 * @param[in]   pTIMERx    base address of the the TIMER
 * @param[in]   subtimer   subtimer, possible values from @SUBTIMERS
 *
 * @return      none
 *
 * @note        none
 * */
void TIMER_IRQResume(TIMER_RegDef_t* pTIMERx, uint8_t subtimer);
void TIMER_IRQResume_H(TIMER_Handle_t* pTIMERHandle);


/**
 * @fn          TIMER_IRQSetPriority
 *
 * @brief       This function sets the priority of the specified IRQ
 *
 * @param[in]   pTIMERx    base address of the TIMER
 * @param[in]   subtimer   subtimer, possible values from @SUBTIMERS
 * @param[in]   IRQPriority  irq priority, possible values from @IRQ_PRIORITES
 *
 * @return      none
 *
 * @note        none
 * */
void TIMER_IRQSetPriority(TIMER_RegDef_t* pTIMERx, uint8_t subtimer, uint8_t IRQPriority);
void TIMER_IRQSetPriority_H(TIMER_Handle_t* pTIMERHandle, uint8_t IRQPriority);


#endif /* DRIVERS_INC_TM4C123GH6PM_TIMER_H_ */

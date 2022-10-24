//
// Created by Oguz Kagan YAGLIOGLU on Oct 23, 2022.
// www.oguzkagan.xyz
//

#include "tm4c123gh6pm_timer.h"


/****************************************************************
 *                       HELPER FUNCTIONS
 ****************************************************************/
bool getIRQNumAndIDX(TIMER_RegDef_t* pTIMERx, uint8_t subtimer, uint8_t* num, uint8_t* idx) {
    if (pTIMERx == TIMER0) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_16_32_Bit_Timer_0A; *idx = 0; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_16_32_Bit_Timer_0B; *idx = 0; return true; }
    }
    else if (pTIMERx == TIMER1) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_16_32_Bit_Timer_1A; *idx = 0; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_16_32_Bit_Timer_1B; *idx = 0; return true; }
    }
    else if (pTIMERx == TIMER2) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_16_32_Bit_Timer_2A; *idx = 0; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_16_32_Bit_Timer_2B; *idx = 0; return true; }
    }
    else if (pTIMERx == TIMER3) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_16_32_Bit_Timer_3A; *idx = 1; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_16_32_Bit_Timer_3B; *idx = 1; return true; }
    }
    else if (pTIMERx == TIMER4) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_16_32_Bit_Timer_4A; *idx = 2; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_16_32_Bit_Timer_4B; *idx = 2; return true; }
    }
    else if (pTIMERx == TIMER5) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_16_32_Bit_Timer_5A; *idx = 2; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_16_32_Bit_Timer_5B; *idx = 2; return true; }
    }
    if (pTIMERx == WTIMER0) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_32_64_Bit_Timer_0A; *idx = 2; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_32_64_Bit_Timer_0B; *idx = 2; return true; }
    }
    else if (pTIMERx == WTIMER1) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_32_64_Bit_Timer_1A; *idx = 3; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_32_64_Bit_Timer_1B; *idx = 3; return true; }
    }
    else if (pTIMERx == WTIMER2) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_32_64_Bit_Timer_2A; *idx = 3; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_32_64_Bit_Timer_2B; *idx = 3; return true; }
    }
    else if (pTIMERx == WTIMER3) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_32_64_Bit_Timer_3A; *idx = 3; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_32_64_Bit_Timer_3B; *idx = 3; return true; }
    }
    else if (pTIMERx == WTIMER4) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_32_64_Bit_Timer_4A; *idx = 3; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_32_64_Bit_Timer_4B; *idx = 3; return true; }
    }
    else if (pTIMERx == WTIMER5) {
        if (subtimer == SUBTIMER_A) { *num = IRQ_NUM_32_64_Bit_Timer_5A; *idx = 3; return true; }
        else if (subtimer == SUBTIMER_B) { *num = IRQ_NUM_32_64_Bit_Timer_5B; *idx = 3; return true; }
    }


    ASSERT(false);
    return false;
}

/****************************************************************/

void TIMER_Init(TIMER_Handle_t* pTIMERHandle) {
    //Enable peripheral clock
    TIMER_PeriClockControl_H(pTIMERHandle, ENABLE);


    // Disable timer's output
    if (pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_AB || pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_A)
        pTIMERHandle->pTIMERx_BaseAddress->CTL &= ~(1 << TIMER_CTL_TAEN);

    if (pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_AB || pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_B)
        pTIMERHandle->pTIMERx_BaseAddress->CTL &= ~(1 << TIMER_CTL_TBEN);

    // Set configuration
    pTIMERHandle->pTIMERx_BaseAddress->CFG = pTIMERHandle->TIMER_Config.cfg;

    if (pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_AB || pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_A) {
        //Set timer mode
        pTIMERHandle->pTIMERx_BaseAddress->TAMR &= ~(0x11 << TIMER_TxMR_TxMR);
        pTIMERHandle->pTIMERx_BaseAddress->TAMR |= (pTIMERHandle->TIMER_Config.mode << TIMER_TxMR_TxMR);

        // Set prescalar value
        pTIMERHandle->pTIMERx_BaseAddress->TAPR = pTIMERHandle->TIMER_Config.prescaleA;

        // Set Interval Load value
        pTIMERHandle->pTIMERx_BaseAddress->TAILR = pTIMERHandle->TIMER_Config.intervalLoadA;

        // Clear timeout flag
        pTIMERHandle->pTIMERx_BaseAddress->ICR |= (1 << TIMER_ICR_TATOCINT);
    }

    if (pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_AB || pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_B) {
        //Set timer mode
        pTIMERHandle->pTIMERx_BaseAddress->TBMR &= ~(0x11 << TIMER_TxMR_TxMR);
        pTIMERHandle->pTIMERx_BaseAddress->TBMR |= (pTIMERHandle->TIMER_Config.mode << TIMER_TxMR_TxMR);

        // Set prescalar value
        pTIMERHandle->pTIMERx_BaseAddress->TBPR = pTIMERHandle->TIMER_Config.prescaleB;

        // Set Interval Load value
        pTIMERHandle->pTIMERx_BaseAddress->TBILR = pTIMERHandle->TIMER_Config.intervalLoadB;

        // Clear timeout flag
        pTIMERHandle->pTIMERx_BaseAddress->ICR |= (1 << TIMER_ICR_TBTOCINT);
    }

    // Enable timer's output
    if (pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_AB || pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_A)
        pTIMERHandle->pTIMERx_BaseAddress->CTL |= (1 << TIMER_CTL_TAEN);

    if (pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_AB || pTIMERHandle->TIMER_Config.subtimer == SUBTIMER_B)
        pTIMERHandle->pTIMERx_BaseAddress->CTL |= (1 << TIMER_CTL_TBEN);
}

void TIMER_PeriClockControl_H(TIMER_Handle_t* pTIMERHandle, bool EnOrDi) { return TIMER_PeriClockControl(pTIMERHandle->pTIMERx_BaseAddress, EnOrDi); }
void TIMER_PeriClockControl(TIMER_RegDef_t* pTIMERx, bool EnOrDi) {
    if (EnOrDi) {
        if (pTIMERx == TIMER0) TIMER0_PCLK_EN_W(true);
        else if (pTIMERx == TIMER1) TIMER1_PCLK_EN_W(true);
        else if (pTIMERx == TIMER2) TIMER2_PCLK_EN_W(true);
        else if (pTIMERx == TIMER3) TIMER3_PCLK_EN_W(true);
        else if (pTIMERx == TIMER4) TIMER4_PCLK_EN_W(true);
        else if (pTIMERx == TIMER5) TIMER5_PCLK_EN_W(true);
        else if (pTIMERx == WTIMER0) WTIMER0_PCLK_EN_W(true);
        else if (pTIMERx == WTIMER1) WTIMER1_PCLK_EN_W(true);
        else if (pTIMERx == WTIMER2) WTIMER2_PCLK_EN_W(true);
        else if (pTIMERx == WTIMER3) WTIMER3_PCLK_EN_W(true);
        else if (pTIMERx == WTIMER4) WTIMER4_PCLK_EN_W(true);
        else if (pTIMERx == WTIMER5) WTIMER5_PCLK_EN_W(true);
    }
    else {
        if (pTIMERx == TIMER0) TIMER0_PCLK_DI();
        else if (pTIMERx == TIMER1) TIMER1_PCLK_DI();
        else if (pTIMERx == TIMER2) TIMER2_PCLK_DI();
        else if (pTIMERx == TIMER3) TIMER3_PCLK_DI();
        else if (pTIMERx == TIMER4) TIMER4_PCLK_DI();
        else if (pTIMERx == TIMER5) TIMER5_PCLK_DI();
        else if (pTIMERx == WTIMER0) WTIMER0_PCLK_DI();
        else if (pTIMERx == WTIMER1) WTIMER1_PCLK_DI();
        else if (pTIMERx == WTIMER2) WTIMER2_PCLK_DI();
        else if (pTIMERx == WTIMER3) WTIMER3_PCLK_DI();
        else if (pTIMERx == WTIMER4) WTIMER4_PCLK_DI();
        else if (pTIMERx == WTIMER5) WTIMER5_PCLK_DI();
    }
}

void TIMER_IRQConfig_H(TIMER_Handle_t* pTIMERHandle, bool EnOrDi) { return TIMER_IRQConfig(pTIMERHandle->pTIMERx_BaseAddress, pTIMERHandle->TIMER_Config.subtimer, EnOrDi); }
void TIMER_IRQConfig(TIMER_RegDef_t* pTIMERx, uint8_t subtimer, bool EnOrDi) {
    uint8_t NVIC_IDXA;
    uint8_t NVIC_IDXB;
    uint8_t IRQ_NUMA;
    uint8_t IRQ_NUMB;


    if (EnOrDi) {
        if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_A) {
            getIRQNumAndIDX(pTIMERx, SUBTIMER_A, &IRQ_NUMA, &NVIC_IDXA);

            NVIC->EN[NVIC_IDXA] |= (1 << IRQ_NUMA);
            pTIMERx->IMR |= (1 << TIMER_IMR_TATOIM);
        }

        if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_B) {
            getIRQNumAndIDX(pTIMERx, SUBTIMER_B, &IRQ_NUMB, &NVIC_IDXB);

            NVIC->EN[NVIC_IDXB] |= (1 << IRQ_NUMB);
            pTIMERx->IMR |= (1 << TIMER_IMR_TBTOIM);
        }
    }
    else {
        if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_A) {
            getIRQNumAndIDX(pTIMERx, SUBTIMER_A, &IRQ_NUMA, &NVIC_IDXA);

            pTIMERx->IMR &= ~(1 << TIMER_IMR_TATOIM);
            NVIC->EN[NVIC_IDXA] &= ~(1 << IRQ_NUMA);
        }

        if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_B) {
            getIRQNumAndIDX(pTIMERx, SUBTIMER_B, &IRQ_NUMB, &NVIC_IDXB);

            pTIMERx->IMR &= ~(1 << TIMER_IMR_TBTOIM);
            NVIC->EN[NVIC_IDXB] &= ~(1 << IRQ_NUMB);
        }
    }

}

void TIMER_IRQHandling_H(TIMER_Handle_t* pTIMERHandle) { return TIMER_IRQHandling(pTIMERHandle->pTIMERx_BaseAddress, pTIMERHandle->TIMER_Config.subtimer); }
void TIMER_IRQHandling(TIMER_RegDef_t* pTIMERx, uint8_t subtimer) {
    if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_A)
        // clear timer A timeout flag bit
        pTIMERx->ICR |= (1 << TIMER_ICR_TATOCINT);

    if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_B)
        // clear timer B timeout flag bit
        pTIMERx->ICR |= (1 << TIMER_ICR_TBTOCINT);
}

void TIMER_IRQSuspend_H(TIMER_Handle_t* pTIMERHandle) { return TIMER_IRQSuspend(pTIMERHandle->pTIMERx_BaseAddress, pTIMERHandle->TIMER_Config.subtimer); }
void TIMER_IRQSuspend(TIMER_RegDef_t* pTIMERx, uint8_t subtimer) {
    uint8_t NVIC_IDXA;
    uint8_t NVIC_IDXB;
    uint8_t IRQ_NUMA;
    uint8_t IRQ_NUMB;

    if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_A) {
        getIRQNumAndIDX(pTIMERx, SUBTIMER_A, &IRQ_NUMA, &NVIC_IDXA);

        NVIC->EN[NVIC_IDXA] &= ~(1 << IRQ_NUMA);
    }

    if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_B) {
        getIRQNumAndIDX(pTIMERx, SUBTIMER_B, &IRQ_NUMB, &NVIC_IDXB);

        NVIC->EN[NVIC_IDXB] &= ~(1 << IRQ_NUMB);
    }
}

void TIMER_IRQResume_H(TIMER_Handle_t* pTIMERHandle) { return TIMER_IRQResume(pTIMERHandle->pTIMERx_BaseAddress, pTIMERHandle->TIMER_Config.subtimer); }
void TIMER_IRQResume(TIMER_RegDef_t* pTIMERx, uint8_t subtimer) {
    uint8_t NVIC_IDXA;
    uint8_t NVIC_IDXB;
    uint8_t IRQ_NUMA;
    uint8_t IRQ_NUMB;

    if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_A) {
        getIRQNumAndIDX(pTIMERx, SUBTIMER_A, &IRQ_NUMA, &NVIC_IDXA);

        NVIC->EN[NVIC_IDXA] |= (1 << IRQ_NUMA);
    }

    if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_B) {
        getIRQNumAndIDX(pTIMERx, SUBTIMER_B, &IRQ_NUMB, &NVIC_IDXB);

        NVIC->EN[NVIC_IDXB] |= (1 << IRQ_NUMB);
    }
}

void TIMER_IRQSetPriority_H(TIMER_Handle_t* pTIMERHandle, uint8_t IRQPriority) { return TIMER_IRQSetPriority(pTIMERHandle->pTIMERx_BaseAddress, pTIMERHandle->TIMER_Config.subtimer, IRQPriority); }
void TIMER_IRQSetPriority(TIMER_RegDef_t* pTIMERx, uint8_t subtimer, uint8_t IRQPriority) {
    // Detect irq number
    uint8_t NVIC_IDXA;
    uint8_t NVIC_IDXB;
    uint8_t IRQ_NUMA;
    uint8_t IRQ_NUMB;

    // set irq priority
    if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_A) {
        getIRQNumAndIDX(pTIMERx, SUBTIMER_A, &IRQ_NUMA, &NVIC_IDXA);

        NVIC->PRI[NVIC_IDXA] &= ~(0b111 << ((IRQ_NUMA % 4) * 8) + 5);      //clear
        NVIC->PRI[NVIC_IDXA] |= (IRQPriority << ((IRQ_NUMA % 4) * 8) + 5);  //set
    }

    if (subtimer == SUBTIMER_AB || subtimer == SUBTIMER_B) {
        getIRQNumAndIDX(pTIMERx, SUBTIMER_B, &IRQ_NUMB, &NVIC_IDXB);

        NVIC->PRI[NVIC_IDXB] &= ~(0b111 << ((IRQ_NUMB % 4) * 8) + 5);      //clear
        NVIC->PRI[NVIC_IDXB] |= (IRQPriority << ((IRQ_NUMB % 4) * 8) + 5);  //set
    }

}
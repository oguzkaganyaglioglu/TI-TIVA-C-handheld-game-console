//
// Created by Oguz Kagan YAGLIOGLU on Oct 6, 2022.
// www.oguzkagan.xyz
//

#include "tm4c123gh6pm_gpio.h"

/****************************************************************
 *                     VALIDATION FUNCTIONS
 ****************************************************************/
bool validatePort(GPIO_RegDef_t* pGPIOx) {
    if (pGPIOx == GPIOA_APB || pGPIOx == GPIOA_AHB) return true;
    else if (pGPIOx == GPIOB_APB || pGPIOx == GPIOB_AHB) return true;
    else if (pGPIOx == GPIOC_APB || pGPIOx == GPIOC_AHB) return true;
    else if (pGPIOx == GPIOD_APB || pGPIOx == GPIOD_AHB) return true;
    else if (pGPIOx == GPIOE_APB || pGPIOx == GPIOE_AHB) return true;
    else if (pGPIOx == GPIOF_APB || pGPIOx == GPIOF_AHB) return true;
    return false;
}

bool validatePin(uint8_t pinNumber) {
    if (pinNumber < 8) return true;
    else return false;
}


bool validatePortAndPin(GPIO_Handle_t* pGPIOHandle) {
    return validatePort(pGPIOHandle->pGPIOx_BaseAddress) && validatePin(pGPIOHandle->GPIO_PinConfig.PinNumber);
}

bool validateIRQTRIG(uint8_t IRQ_trigger) {
    return IRQ_trigger == GPIO_IRQ_DISABLE || ((GPIO_IRQ_TRIG_FE | GPIO_IRQ_TRIG_RE | GPIO_IRQ_TRIG_LL | GPIO_IRQ_TRIG_HL) & IRQ_trigger) > 0;
}

bool validateIRQPRI(uint8_t IRQ_PRI) {
    return IRQ_PRI < 8;
}
/****************************************************************/

/****************************************************************
 *                       HELPER FUNCTIONS
 ****************************************************************/
uint8_t portToNumber(GPIO_RegDef_t* pGPIOx) {
    if (pGPIOx == GPIOA_APB || pGPIOx == GPIOA_AHB) return 0;
    else if (pGPIOx == GPIOB_APB || pGPIOx == GPIOB_AHB) return 1;
    else if (pGPIOx == GPIOC_APB || pGPIOx == GPIOC_AHB) return 2;
    else if (pGPIOx == GPIOD_APB || pGPIOx == GPIOD_AHB) return 3;
    else if (pGPIOx == GPIOE_APB || pGPIOx == GPIOE_AHB) return 4;
    else if (pGPIOx == GPIOF_APB || pGPIOx == GPIOF_AHB) return 5;
    ASSERT(false);
    return 0;
}

uint8_t getGPIO_BUS(GPIO_RegDef_t* pGPIOx) {
    if (pGPIOx == GPIOA_AHB) return GPIO_BUS_AHB;
    else if (pGPIOx == GPIOB_AHB) return GPIO_BUS_AHB;
    else if (pGPIOx == GPIOC_AHB) return GPIO_BUS_AHB;
    else if (pGPIOx == GPIOD_AHB) return GPIO_BUS_AHB;
    else if (pGPIOx == GPIOE_AHB) return GPIO_BUS_AHB;
    else if (pGPIOx == GPIOF_AHB) return GPIO_BUS_AHB;
    return GPIO_BUS_APB;
}
/****************************************************************/


void GPIO_Init(GPIO_Handle_t* pGPIOHandle) {

    //check the arguments
    ASSERT(validatePortAndPin(pGPIOHandle));

    //enable the peripheral clock
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx_BaseAddress, ENABLE);

    // Detect GPIO bus
    pGPIOHandle->GPIO_PinConfig.BusControl = getGPIO_BUS(pGPIOHandle->pGPIOx_BaseAddress);

    // select the bus
    if (pGPIOHandle->GPIO_PinConfig.BusControl == GPIO_BUS_AHB) {
        // select the AHB bus
        SYSCTL->GPIOHBCTL |= (1 << portToNumber(pGPIOHandle->pGPIOx_BaseAddress));
    }
    else {
        // select the APB bus
        SYSCTL->GPIOHBCTL &= ~(1 << portToNumber(pGPIOHandle->pGPIOx_BaseAddress));
    }

    // unlock the given GPIO port
    GPIOx_UNLOCK_MACRO(pGPIOHandle->pGPIOx_BaseAddress);

    //The corresponding GPIOAFSEL, GPIOPUR, GPIOPDR, or GPIODEN bits can be written
    pGPIOHandle->pGPIOx_BaseAddress->CR |= (1 << pGPIOHandle->GPIO_PinConfig.PinNumber);

    if (pGPIOHandle->GPIO_PinConfig.PinCNF != GPIO_CNF_IN_AN) {
        // disable analog functionality for this pin
        pGPIOHandle->pGPIOx_BaseAddress->AMSEL &= ~(1 << pGPIOHandle->GPIO_PinConfig.PinNumber);

        //todo alternate functionality modes
        if (pGPIOHandle->GPIO_PinConfig.PinCNF == GPIO_CNF_OUT_PP || pGPIOHandle->GPIO_PinConfig.PinCNF == GPIO_CNF_OUT_OD) {
            pGPIOHandle->pGPIOx_BaseAddress->PCTL &= ~(0xF << pGPIOHandle->GPIO_PinConfig.PinNumber);

            //disable alternate functionality for this pin
            pGPIOHandle->pGPIOx_BaseAddress->AFSEL &= ~(1 << pGPIOHandle->GPIO_PinConfig.PinNumber);

            if (pGPIOHandle->GPIO_PinConfig.PinCNF != GPIO_CNF_OUT_PP) {
                //enable open-drain
                pGPIOHandle->pGPIOx_BaseAddress->ODR |= (1 << pGPIOHandle->GPIO_PinConfig.PinNumber);
            }
            else {
                //disable open-drain
                pGPIOHandle->pGPIOx_BaseAddress->ODR &= ~(1 << pGPIOHandle->GPIO_PinConfig.PinNumber);
            }

        }

        if (pGPIOHandle->GPIO_PinConfig.PinCNF >= 4) {
            // pin is output
            pGPIOHandle->pGPIOx_BaseAddress->DIR |= (1 << pGPIOHandle->GPIO_PinConfig.PinNumber);
        }
        else {
            // pin is input
            pGPIOHandle->pGPIOx_BaseAddress->DIR &= ~(1 << pGPIOHandle->GPIO_PinConfig.PinNumber);
        }
    }
    else {

        if (pGPIOHandle->pADCx_BaseAddress == ADC1) ADC1_PCLK_EN_W(true);
        else ADC0_PCLK_EN_W(true);

        // enable alternate functionality for this pin
        pGPIOHandle->pGPIOx_BaseAddress->AFSEL |= (1 << pGPIOHandle->GPIO_PinConfig.PinNumber);

        // disable digital functionality
        pGPIOHandle->pGPIOx_BaseAddress->DEN &= ~(1 << pGPIOHandle->GPIO_PinConfig.PinNumber);

        // enable analog functionality
        pGPIOHandle->pGPIOx_BaseAddress->AMSEL |= (1 << pGPIOHandle->GPIO_PinConfig.PinNumber);

        // disable sample sequencer
        pGPIOHandle->pADCx_BaseAddress->ACTSS &= ~(1 << pGPIOHandle->ADC_PinConfig.SS);

        // set trigger
        pGPIOHandle->pADCx_BaseAddress->EMUX &= ~(0xF << (pGPIOHandle->ADC_PinConfig.SS * 4));
        pGPIOHandle->pADCx_BaseAddress->EMUX |= (pGPIOHandle->ADC_PinConfig.TRIG << (pGPIOHandle->ADC_PinConfig.SS * 4));

        // select analog channel 
        pGPIOHandle->pADCx_BaseAddress->SS[pGPIOHandle->ADC_PinConfig.SS].SSMUX = pGPIOHandle->ADC_PinConfig.ADC_Number;

        // configure sample sequencer control register
        pGPIOHandle->pADCx_BaseAddress->SS[pGPIOHandle->ADC_PinConfig.SS].SSCTL = pGPIOHandle->ADC_PinConfig.SSCTL;

        // set sampling rate
        pGPIOHandle->pADCx_BaseAddress->PC = pGPIOHandle->ADC_PinConfig.SR;

        // start sampling
        pGPIOHandle->pADCx_BaseAddress->PSSI |= (1 << pGPIOHandle->ADC_PinConfig.SS);

        // enable sample sequencer
        pGPIOHandle->pADCx_BaseAddress->ACTSS |= (1 << pGPIOHandle->ADC_PinConfig.SS);

    }

    if (pGPIOHandle->GPIO_PinConfig.PinPuPdControl == GPIO_PU) {
        pGPIOHandle->pGPIOx_BaseAddress->PUR |= (1 << pGPIOHandle->GPIO_PinConfig.PinNumber);  // enable pull-up resistor
    }
    else if (pGPIOHandle->GPIO_PinConfig.PinPuPdControl == GPIO_PD) {
        pGPIOHandle->pGPIOx_BaseAddress->PDR |= (1 << pGPIOHandle->GPIO_PinConfig.PinNumber);  // enable pull-down resistor
    }
    else {
        pGPIOHandle->pGPIOx_BaseAddress->PUR &= ~(1 << pGPIOHandle->GPIO_PinConfig.PinNumber);  // disable pull-up resistor
        pGPIOHandle->pGPIOx_BaseAddress->PDR &= ~(1 << pGPIOHandle->GPIO_PinConfig.PinNumber);  // disable pull-down resistor
    }

    if (pGPIOHandle->GPIO_PinConfig.PinCNF != GPIO_CNF_IN_AN) {
        // disable analog functionality
        pGPIOHandle->pGPIOx_BaseAddress->AMSEL &= ~(1 << pGPIOHandle->GPIO_PinConfig.PinNumber);

        // enable digital functionality
        pGPIOHandle->pGPIOx_BaseAddress->DEN |= (1 << pGPIOHandle->GPIO_PinConfig.PinNumber);
    }

    //The corresponding GPIOAFSEL, GPIOPUR, GPIOPDR, or GPIODEN bits cannot be written
    pGPIOHandle->pGPIOx_BaseAddress->CR &= ~(1 << pGPIOHandle->GPIO_PinConfig.PinNumber);

}

void GPIO_DeInit(GPIO_RegDef_t* pGPIOx) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));

    // reset the given GPIO port
    if (pGPIOx == GPIOA_APB || pGPIOx == GPIOA_AHB) GPIOA_REG_RST();
    else if (pGPIOx == GPIOB_APB || pGPIOx == GPIOB_AHB) GPIOB_REG_RST();
    else if (pGPIOx == GPIOC_APB || pGPIOx == GPIOC_AHB) GPIOC_REG_RST();
    else if (pGPIOx == GPIOD_APB || pGPIOx == GPIOD_AHB) GPIOD_REG_RST();
    else if (pGPIOx == GPIOE_APB || pGPIOx == GPIOE_AHB) GPIOE_REG_RST();
    else if (pGPIOx == GPIOF_APB || pGPIOx == GPIOE_AHB) GPIOF_REG_RST();
}


void GPIO_PeriClockControl_H(GPIO_Handle_t* pGPIOHandle, bool EnOrDi) { return GPIO_PeriClockControl(pGPIOHandle->pGPIOx_BaseAddress, EnOrDi); }
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, bool EnOrDi) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));

    // enable/disable the peripheral clock of the given GPIO port
    if (EnOrDi) {
      // after enabling the peripheral clock, wait until GPIO peripheral get ready
        if (pGPIOx == GPIOA_APB || pGPIOx == GPIOA_AHB) GPIOA_PCLK_EN_W(true);
        else if (pGPIOx == GPIOB_APB || pGPIOx == GPIOB_AHB) GPIOB_PCLK_EN_W(true);
        else if (pGPIOx == GPIOC_APB || pGPIOx == GPIOC_AHB) GPIOC_PCLK_EN_W(true);
        else if (pGPIOx == GPIOD_APB || pGPIOx == GPIOD_AHB) GPIOD_PCLK_EN_W(true);
        else if (pGPIOx == GPIOE_APB || pGPIOx == GPIOE_AHB) GPIOE_PCLK_EN_W(true);
        else if (pGPIOx == GPIOF_APB || pGPIOx == GPIOF_AHB) GPIOF_PCLK_EN_W(true);
    }
    else {
        if (pGPIOx == GPIOA_APB || pGPIOx == GPIOA_AHB) GPIOA_PCLK_DI();
        else if (pGPIOx == GPIOB_APB || pGPIOx == GPIOB_AHB) GPIOB_PCLK_DI();
        else if (pGPIOx == GPIOC_APB || pGPIOx == GPIOC_AHB) GPIOC_PCLK_DI();
        else if (pGPIOx == GPIOD_APB || pGPIOx == GPIOD_AHB) GPIOD_PCLK_DI();
        else if (pGPIOx == GPIOE_APB || pGPIOx == GPIOE_AHB) GPIOE_PCLK_DI();
        else if (pGPIOx == GPIOF_APB || pGPIOx == GPIOF_AHB) GPIOF_PCLK_DI();
    }
}

bool GPIO_ReadPin_H(GPIO_Handle_t* pGPIOHandle) { return GPIO_ReadPin(pGPIOHandle->pGPIOx_BaseAddress, pGPIOHandle->GPIO_PinConfig.PinNumber); }
bool GPIO_ReadPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));
    ASSERT(validatePin(PinNumber));

    // read the pin value
    return (bool)(pGPIOx->DATA >> PinNumber) & 1;
}

uint8_t GPIO_ReadPort_H(GPIO_Handle_t* pGPIOHandle) { return GPIO_ReadPort(pGPIOHandle->pGPIOx_BaseAddress); }
uint8_t GPIO_ReadPort(GPIO_RegDef_t* pGPIOx) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));

    // read the port value
    return (uint8_t)(pGPIOx->DATA);
}

void GPIO_WritePin_H(GPIO_Handle_t* pGPIOHandle, bool Value) { return GPIO_WritePin(pGPIOHandle->pGPIOx_BaseAddress, pGPIOHandle->GPIO_PinConfig.PinNumber, Value); }
void GPIO_WritePin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, bool Value) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));
    ASSERT(validatePin(PinNumber));

    // write value to the pin
    if (Value) pGPIOx->DATA |= (1 << PinNumber);  // set
    else pGPIOx->DATA &= ~(1 << PinNumber);       // clear
}

void GPIO_WritePort_H(GPIO_Handle_t* pGPIOHandle, uint8_t Value) { return GPIO_WritePort(pGPIOHandle->pGPIOx_BaseAddress, Value); }
void GPIO_WritePort(GPIO_RegDef_t* pGPIOx, uint8_t Value) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));

    // write value to the port
    pGPIOx->DATA = Value;
}

void GPIO_TogglePin_H(GPIO_Handle_t* pGPIOHandle) { return GPIO_TogglePin(pGPIOHandle->pGPIOx_BaseAddress, pGPIOHandle->GPIO_PinConfig.PinNumber); }
void GPIO_TogglePin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));
    ASSERT(validatePin(PinNumber));

    // toggle the pin
    pGPIOx->DATA ^= (uint8_t)(1 << PinNumber);
}

void GPIO_IRQConfig_H(GPIO_Handle_t* pGPIOHandle, bool EnOrDi) { return GPIO_IRQConfig(pGPIOHandle->pGPIOx_BaseAddress, pGPIOHandle->GPIO_PinConfig.PinNumber, pGPIOHandle->GPIO_PinConfig.IRQ_trigger, EnOrDi); }
void GPIO_IRQConfig(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t IRQ_trigger, bool EnOrDi) {

    //check the arguments
    ASSERT(validatePort(pGPIOx));
    ASSERT(validatePin(PinNumber));
    ASSERT(validateIRQTRIG(IRQ_trigger));

    // Detect irq number
    uint32_t irqNum;
    if (pGPIOx == GPIOA_APB || pGPIOx == GPIOA_AHB) irqNum = IRQ_NUM_GPIO_Port_A;
    else if (pGPIOx == GPIOB_APB || pGPIOx == GPIOB_AHB) irqNum = IRQ_NUM_GPIO_Port_B;
    else if (pGPIOx == GPIOC_APB || pGPIOx == GPIOC_AHB) irqNum = IRQ_NUM_GPIO_Port_C;
    else if (pGPIOx == GPIOD_APB || pGPIOx == GPIOD_AHB) irqNum = IRQ_NUM_GPIO_Port_D;
    else if (pGPIOx == GPIOE_APB || pGPIOx == GPIOE_AHB) irqNum = IRQ_NUM_GPIO_Port_E;
    else if (pGPIOx == GPIOF_APB || pGPIOx == GPIOF_AHB) irqNum = IRQ_NUM_GPIO_Port_F;
    else return;

    if (EnOrDi && IRQ_trigger != GPIO_IRQ_DISABLE) {
      //Enable interrupt for given GPIO port
        NVIC->EN[irqNum / 32] = (uint32_t)(1 << (irqNum % 32));

        // Remove the interrupt mask for the given pin
        pGPIOx->IM |= (1 << PinNumber);

        if (((GPIO_IRQ_TRIG_LL | GPIO_IRQ_TRIG_HL) & IRQ_trigger) > 0) {
            // Level sensitive IRQ
            pGPIOx->IS |= (1 << PinNumber);
        }
        else {
            // edge sensitive IRQ
            pGPIOx->IS &= ~(1 << PinNumber);
        }

        if ((GPIO_IRQ_TRIG_RE | GPIO_IRQ_TRIG_FE) == IRQ_trigger) {
            // IRQ trigger FALLING EDGE and RISING EDGE
            pGPIOx->IBE |= (1 << PinNumber);
        }
        else if (((GPIO_IRQ_TRIG_RE | GPIO_IRQ_TRIG_HL) & IRQ_trigger) > 0) {
            // make sure IRQ trigger controlled by IEV
            pGPIOx->IBE &= ~(1 << PinNumber);
            // IRQ trigger HIGH LEVEl / RISING EDGE
            pGPIOx->IEV |= (1 << PinNumber);
        }
        else {
            // make sure IRQ trigger controlled by IEV
            pGPIOx->IBE &= ~(1 << PinNumber);
            // IRQ trigger LOW LEVEl / FALLING EDGE
            pGPIOx->IEV &= ~(1 << PinNumber);
        }
    }
    else {
        // mask the interrupt for the given pin
        pGPIOx->IM &= ~(1 << PinNumber);
    }
}

void GPIO_IRQSetPriority(GPIO_RegDef_t* pGPIOx, uint8_t IRQPriority) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));
    ASSERT(validateIRQPRI(IRQPriority));

    // Detect irq number
    uint32_t irqNum;
    if (pGPIOx == GPIOA_APB || pGPIOx == GPIOA_AHB) irqNum = IRQ_NUM_GPIO_Port_A;
    else if (pGPIOx == GPIOB_APB || pGPIOx == GPIOB_AHB) irqNum = IRQ_NUM_GPIO_Port_B;
    else if (pGPIOx == GPIOC_APB || pGPIOx == GPIOC_AHB) irqNum = IRQ_NUM_GPIO_Port_C;
    else if (pGPIOx == GPIOD_APB || pGPIOx == GPIOD_AHB) irqNum = IRQ_NUM_GPIO_Port_D;
    else if (pGPIOx == GPIOE_APB || pGPIOx == GPIOE_AHB) irqNum = IRQ_NUM_GPIO_Port_E;
    else if (pGPIOx == GPIOF_APB || pGPIOx == GPIOF_AHB) irqNum = IRQ_NUM_GPIO_Port_F;
    else return;

    // set irq priority
    NVIC->PRI[irqNum / 4] &= ~(0b111 << ((irqNum % 4) * 8) + 5);      //clear
    NVIC->PRI[irqNum / 4] |= (IRQPriority << ((irqNum % 4) * 8) + 5);  //set
}

void GPIO_IRQHandling_H(GPIO_Handle_t* pGPIOHandle) { return GPIO_IRQHandling(pGPIOHandle->pGPIOx_BaseAddress, pGPIOHandle->GPIO_PinConfig.PinNumber); }
void GPIO_IRQHandling(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));
    ASSERT(validatePin(PinNumber));

    // clear interrupt
    pGPIOx->ICR = (1 << PinNumber);
}

bool GPIO_IRQCausedByThis_H(GPIO_Handle_t* pGPIOHandle) { return GPIO_IRQCausedByThis(pGPIOHandle->pGPIOx_BaseAddress, pGPIOHandle->GPIO_PinConfig.PinNumber); }
bool GPIO_IRQCausedByThis(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber) {
    //check the arguments
    ASSERT(validatePort(pGPIOx));
    ASSERT(validatePin(PinNumber));

    // return GPIO Masked Interrupt Status
    return (bool)(pGPIOx->MIS & (1 << PinNumber));
}
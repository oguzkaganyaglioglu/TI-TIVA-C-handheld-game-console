//
// Created by Oguz Kagan YAGLIOGLU on 6 October 2022.
// www.oguzkagan.xyz
//

#ifndef DRIVERS_INC_TM4C123GH6PM_H_
#define DRIVERS_INC_TM4C123GH6PM_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************
 *                          DEBUG ONLY
 ****************************************************************/

// #define DEBUG

// ASSERT calls this function if the condition is false
inline void __error__(char* pFilename, uint32_t line) { while (true); };

#ifdef DEBUG
// Assertion check macro
#define ASSERT(condition) do{ if(!condition) __error__(__FILE__, __LINE__); } while(0)
#else
#define ASSERT(condition)
#endif
/****************************************************************/


#define __I      volatile
#define __O      volatile
#define __IO    volatile

/**
 * @IRQ_PRIORITES
 * IRQ(Interrupt Request) priorities
 * */
#define NVIC_IRQ_PRIORITY_0     0
#define NVIC_IRQ_PRIORITY_1     1
#define NVIC_IRQ_PRIORITY_2     2
#define NVIC_IRQ_PRIORITY_3     3
#define NVIC_IRQ_PRIORITY_4     4
#define NVIC_IRQ_PRIORITY_5     5
#define NVIC_IRQ_PRIORITY_6     6
#define NVIC_IRQ_PRIORITY_7     7

/**
 *  Bit SET/CLEAR macros
 * */
#define SET_BIT(REGISTER, POS)    (REGISTER |= (POS))
#define CLEAR_BIT(REGISTER, POS)  (REGISTER &= ~(POS))

/**
 * Base addresses offset macro
 * This macro adds offset to the given base address
 * */
#define BASEADDR_ADD_OFFSET(BASE,OFFSET)         ((BASE) + (OFFSET))

#define SYSCTL_ADD_OFFSET(OFFSET)                (*((volatile uint32_t *)(BASEADDR_ADD_OFFSET(SYSCTL_BASE_ADDR, OFFSET))))
#define GPIOx_ADD_OFFSET(GPIOx_BASE,OFFSET)      (*((volatile uint32_t *)(BASEADDR_ADD_OFFSET(GPIOx_BASE, OFFSET))))

/**
 * Base addresses of Flash and SRAM memories
 */
#define FLASH_BASE_ADDR                  0x00000000UL
#define SRAM_BASE_ADDR                   0x20000000UL

/**
 * Core Peripherals base address
 * */
#define CORE_PERIPHERALS_BASEADDR        0xE000E000UL
#define NVIC_BASEADDR                    BASEADDR_ADD_OFFSET(CORE_PERIPHERALS_BASEADDR, 0X100UL)

/**
 * AHBx and APBx Bus Peripheral base addresses
 * */
#define PERIPHERAL_BASE_ADDR            0x40000000UL
#define PERIPHERAL_ADD_OFFSET(OFFSET)   (PERIPHERAL_BASE_ADDR + (OFFSET))

/**
 * Base addresses of GPIOx peripherals which are hanging on APB bus
 * */
#define GPIOA_APB_BASE_ADDR           0x40004000UL
#define GPIOB_APB_BASE_ADDR           0x40005000UL
#define GPIOC_APB_BASE_ADDR           0x40006000UL
#define GPIOD_APB_BASE_ADDR           0x40007000UL
#define GPIOE_APB_BASE_ADDR           0x40024000UL
#define GPIOF_APB_BASE_ADDR           0x40025000UL

/**
 * Base addresses of GPIOx peripherals which are hanging on AHB bus
 * */
#define GPIOA_AHB_BASE_ADDR           0x40058000UL
#define GPIOB_AHB_BASE_ADDR           0x40059000UL
#define GPIOC_AHB_BASE_ADDR           0x4005A000UL
#define GPIOD_AHB_BASE_ADDR           0x4005B000UL
#define GPIOE_AHB_BASE_ADDR           0x4005C000UL
#define GPIOF_AHB_BASE_ADDR           0x4005D000UL

/**
 * Base addresses of peripherals which are hanging on APB bus
 * */
#define SSI0_BASE_ADDR                0x40008000UL
#define SSI1_BASE_ADDR                0x40009000UL
#define SSI2_BASE_ADDR                0x4000A000UL
#define SSI3_BASE_ADDR                0x4000B000UL

#define UART0_BASE_ADDR               0x4000C000UL
#define UART1_BASE_ADDR               0x4000D000UL
#define UART2_BASE_ADDR               0x4000E000UL
#define UART3_BASE_ADDR               0x4000F000UL
#define UART4_BASE_ADDR               0x40010000UL
#define UART5_BASE_ADDR               0x40011000UL
#define UART6_BASE_ADDR               0x40012000UL
#define UART7_BASE_ADDR               0x40013000UL

#define I2C0_BASE_ADDR                0x40020000UL
#define I2C1_BASE_ADDR                0x40021000UL
#define I2C2_BASE_ADDR                0x40022000UL
#define I2C3_BASE_ADDR                0x40023000UL

#define SYSCTL_BASE_ADDR              0x400FE000UL
#define ADC0_BASE_ADDR                0x40038000UL
#define ADC1_BASE_ADDR                0x40039000UL

#define TIMER0_BASE_ADDR              0x40030000UL
#define TIMER1_BASE_ADDR              0x40031000UL
#define TIMER2_BASE_ADDR              0x40032000UL
#define TIMER3_BASE_ADDR              0x40033000UL
#define TIMER4_BASE_ADDR              0x40034000UL
#define TIMER5_BASE_ADDR              0x40035000UL

#define WTIMER0_BASE_ADDR             0x40036000UL
#define WTIMER1_BASE_ADDR             0x40037000UL
#define WTIMER2_BASE_ADDR             0x4004C000UL
#define WTIMER3_BASE_ADDR             0x4004D000UL
#define WTIMER4_BASE_ADDR             0x4004E000UL
#define WTIMER5_BASE_ADDR             0x4004F000UL


/**
 *  TIMER Register definition structure
 * */
#pragma pack (4)
typedef struct {
    __IO uint32_t CFG;         // GPTM Configuration
    __IO uint32_t TAMR;        // GPTM Timer A Mode
    __IO uint32_t TBMR;        // GPTM Timer B Mode
    __IO uint32_t CTL;         // GPTM Control
    __IO uint32_t SYNC;        // GPTM Synchronize
    uint32_t RESERVED;
    __IO uint32_t IMR;         // GPTM Interrupt Mask
    __I  uint32_t RIS;         // GPTM Raw Interrupt Status
    __I  uint32_t MIS;         // GPTM Masked Interrupt Status
    __O  uint32_t ICR;         // GPTM Interrupt Clear
    __IO uint32_t TAILR;       // GPTM Timer A Interval Load
    __IO uint32_t TBILR;       // GPTM Timer B Interval Load
    __IO uint32_t TAMATCHR;    // GPTM Timer A Match
    __IO uint32_t TBMATCHR;    // GPTM Timer B Match
    __IO uint32_t TAPR;        // GPTM Timer A Prescale
    __IO uint32_t TBPR;        // GPTM Timer B Prescale
    __IO uint32_t TAPMR;       // GPTM TimerA Prescale Match
    __IO uint32_t TBPMR;       // GPTM TimerB Prescale Match
    __I  uint32_t TAR;         // GPTM Timer A
    __I  uint32_t TBR;         // GPTM Timer B
    __IO uint32_t TAV;         // GPTM Timer A Value
    __IO uint32_t TBV;         // GPTM Timer B Value
    __I  uint32_t RTCPD;       // GPTM RTC Predivide
    __I  uint32_t TAPS;        // GPTM Timer A Prescale Snapshot
    __I  uint32_t TBPS;        // GPTM Timer B Prescale Snapshot
    __I  uint32_t TAPV;        // GPTM Timer A Prescale Value
    __I  uint32_t TBPV;        // GPTM Timer B Prescale Value
    uint32_t RESERVED1[981];
    __I  uint32_t PP;          // GPTM Peripheral Properties
} TIMER_RegDef_t;

/**
 *  SSI Register definition structure
 * */
#pragma pack (4)
typedef struct {
    __IO uint32_t CR0;           // SSI Control 0
    __IO uint32_t CR1;           // SSI Control 1
    __IO uint32_t DR;            // SSI Data
    __I  uint32_t SR;            // SSI Status
    __IO uint32_t CPSR;          // SSI Clock Prescale
    __IO uint32_t IM;            // SSI Interrupt Mask
    __I  uint32_t RIS;           // SSI Raw Interrupt Status
    __I  uint32_t MIS;           // SSI Masked Interrupt Status
    __O  uint32_t ICR;           // SSI Interrupt Clear
    __IO uint32_t DMACTL;        // SSI DMA Control
    uint32_t RESERVED[1000];
    __IO uint32_t CC;            // SSI Clock Configuration
    __I  uint32_t PeriphID4;     // SSI Peripheral Identification 4
    __I  uint32_t PeriphID5;     // SSI Peripheral Identification 5
    __I  uint32_t PeriphID6;     // SSI Peripheral Identification 6
    __I  uint32_t PeriphID7;     // SSI Peripheral Identification 7
    __I  uint32_t PeriphID0;     // SSI Peripheral Identification 0
    __I  uint32_t PeriphID1;     // SSI Peripheral Identification 1
    __I  uint32_t PeriphID2;     // SSI Peripheral Identification 2
    __I  uint32_t PeriphID3;     // SSI Peripheral Identification 3
    __I  uint32_t PCellID0;      // SSI PrimeCell Identification 0
    __I  uint32_t PCellID1;      // SSI PrimeCell Identification 1
    __I  uint32_t PCellID2;      // SSI PrimeCell Identification 2
    __I  uint32_t PCellID3;      // SSI PrimeCell Identification 3
} SSI_RegDef_t;

typedef SSI_RegDef_t SPI_RegDef_t;

/**
 *  System Control Register definition structure
 * */
#pragma pack (4)
typedef struct {
    __I  uint32_t DID0;               // Device Identification 0
    __I  uint32_t DID1;               // Device Identification 1
    __I  uint32_t LEGACY_DC0;         // Device Capabilities 0
    uint32_t RESERVED;
    __I  uint32_t LEGACY_DC1;         // Device Capabilities 1
    __I  uint32_t LEGACY_DC2;         // Device Capabilities 2
    __I  uint32_t LEGACY_DC3;         // Device Capabilities 3
    __I  uint32_t LEGACY_DC4;         // Device Capabilities 4
    __I  uint32_t LEGACY_DC5;         // Device Capabilities 5
    __I  uint32_t LEGACY_DC6;         // Device Capabilities 6
    __I  uint32_t LEGACY_DC7;         // Device Capabilities 7
    __I  uint32_t LEGACY_DC8;         // Device Capabilities 8
    __IO uint32_t PBORCTL;            // Brown-Out Reset Control
    uint32_t RESERVED1[3];
    __I  uint32_t LEGACY_SRCR0;       // Software Reset Control 0
    __I  uint32_t LEGACY_SRCR1;       // Software Reset Control 1
    __I  uint32_t LEGACY_SRCR2;       // Software Reset Control 2
    uint32_t RESERVED2;
    __I  uint32_t RIS;                // Raw Interrupt Status 50
    __IO uint32_t IMC;                // Raw Interrupt Status
    __IO uint32_t MISC;               // Masked Interrupt Status and Clear
    __IO uint32_t RESC;               // Reset Cause
    __IO uint32_t RCC;                // Run-Mode Clock Configuration
    uint32_t RESERVED3[2];
    __IO uint32_t GPIOHBCTL;          // GPIO High-Performance Bus Control
    __IO uint32_t RCC2;               // Run-Mode Clock Configuration 2
    uint32_t RESERVED4[2];
    __IO uint32_t MOSCCTL;            // Main Oscillator Control
    uint32_t RESERVED5[32];
    __I  uint32_t LEGACY_RCGC0;       // Run Mode Clock Gating Control Register 0
    __I  uint32_t LEGACY_RCGC1;       // Run Mode Clock Gating Control Register 1
    __I  uint32_t LEGACY_RCGC2;       // Run Mode Clock Gating Control Register 2
    uint32_t RESERVED6;
    __I  uint32_t LEGACY_SCGC0;       // Sleep Mode Clock Gating Control Register 0
    __I  uint32_t LEGACY_SCGC1;       // Sleep Mode Clock Gating Control Register 1
    __I  uint32_t LEGACY_SCGC2;       // Sleep Mode Clock Gating Control Register 2
    uint32_t RESERVED7;
    __I  uint32_t LEGACY_DCGC0;       // Deep Sleep Mode Clock Gating Control Register 0
    __I  uint32_t LEGACY_DCGC1;       // Deep-Sleep Mode Clock Gating Control Register 1
    __I  uint32_t LEGACY_DCGC2;       // Deep Sleep Mode Clock Gating Control Register 2
    uint32_t RESERVED8[6];
    __IO uint32_t DSLPCLKCFG;         // Deep Sleep Clock Configuration
    uint32_t RESERVED9;
    __I  uint32_t SYSPROP;            // System Properties
    __IO uint32_t PIOSCCAL;           // Precision Internal Oscillator Calibration
    __I  uint32_t PIOSCSTAT;          // Precision Internal Oscillator Statistics
    uint32_t RESERVED10[2];
    __I  uint32_t PLLFREQ0;           // PLL Frequency 0
    __I  uint32_t PLLFREQ1;           // PLL Frequency 1
    __I  uint32_t PLLSTAT;            // PLL Status
    uint32_t RESERVED11[7];
    __IO uint32_t SLPPWRCFG;          // Sleep Power Configuration
    __IO uint32_t DSLPPWRCFG;         // Deep-Sleep Power Configuration
    __I  uint32_t LEGACY_DC9;         // Device Capabilities 9
    uint32_t RESERVED12[3];
    __I  uint32_t LEGACY_NVMSTAT;     // Non-Volatile Memory Information
    uint32_t RESERVED13[4];
    __IO uint32_t LDOSPCTL;           // LDO Sleep Power Control
    __I  uint32_t LDOSPCAL;           // LDO Sleep Power Calibration
    __IO uint32_t LDODPCTL;           // LDO Deep-Sleep Power Control
    __I  uint32_t LDODPCAL;           // LDO Deep-Sleep Power Calibration
    uint32_t RESERVED14[2];
    __I  uint32_t SDPMST;             // Sleep / Deep-Sleep Power Mode Status
    uint32_t RESERVED15[76];
    __I  uint32_t PPWD;               // Watchdog Timer Peripheral Present
    __I  uint32_t PPTIMER;            // 16/32-Bit General-Purpose Timer Peripheral Present
    __I  uint32_t PPGPIO;             // General-Purpose Input/Output Peripheral Present
    __I  uint32_t PPDMA;              // Micro Direct Memory Access Peripheral Present
    uint32_t RESERVED16;
    __I  uint32_t PPHIB;              // Hibernation Peripheral Present
    __I  uint32_t PPUART;             // Universal Asynchronous Receiver/Transmitter Peripheral Present
    __I  uint32_t PPSSI;              // Synchronous Serial Interface Peripheral Present
    __I  uint32_t PPI2C;              // Inter-Integrated Circuit Peripheral Present
    uint32_t RESERVED17;
    __I  uint32_t PPUSB;              // Universal Serial Bus Peripheral Present
    uint32_t RESERVED18[2];
    __I  uint32_t PPCAN;              // Controller Area Network Peripheral Present
    __I  uint32_t PPADC;              // Analog-to-Digital Converter Peripheral Present
    __I  uint32_t PPACMP;             // Analog Comparator Peripheral Present
    __I  uint32_t PPPWM;              // Pulse Width Modulator Peripheral Present
    __I  uint32_t PPQEI;              // Quadrature Encoder Interface Peripheral Present
    uint32_t RESERVED19[4];
    __I  uint32_t PPEEPROM;           // EEPROM Peripheral Present
    __I  uint32_t PPWTIMER;           // 32/64-Bit Wide General-Purpose Timer Peripheral Present
    uint32_t RESERVED20[104];
    __IO uint32_t SRWD;               // Watchdog Timer Software Reset
    __IO uint32_t SRTIMER;            // 16/32-Bit General-Purpose Timer Software Reset
    __IO uint32_t SRGPIO;             // General-Purpose Input/Output Software Reset
    __IO uint32_t SRDMA;              // Micro Direct Memory Access Software Reset
    uint32_t RESERVED21;
    __IO uint32_t SRHIB;              // Hibernation Software Reset
    __IO uint32_t SRUART;             // Universal Asynchronous Receiver/Transmitter Software Reset
    __IO uint32_t SRSSI;              // Synchronous Serial Interface Software Reset
    __IO uint32_t SRI2C;              // Inter-Integrated Circuit Software Reset
    uint32_t RESERVED22;
    __IO uint32_t SRUSB;              // Universal Serial Bus Software Reset
    uint32_t RESERVED23[2];
    __IO uint32_t SRCAN;              // Controller Area Network Software Reset
    __IO uint32_t SRADC;              // Analog-to-Digital Converter Software Reset
    __IO uint32_t SRACMP;             // Analog Comparator Software Reset
    __IO uint32_t SRPWM;              // Pulse Width Modulator Software Reset
    __IO uint32_t SRQEI;              // Quadrature Encoder Interface Software Reset
    uint32_t RESERVED24[4];
    __IO uint32_t SREEPROM;           // EEPROM Software Reset
    __IO uint32_t SRWTIMER;           // 32/64-Bit Wide General-Purpose Timer Software Reset
    uint32_t RESERVED25[40];
    __IO uint32_t RCGCWD;             // Watchdog Timer Run Mode Clock Gating Control
    __IO uint32_t RCGCTIMER;          // 16/32-BitGeneral-Purpose Timer Run Mode Clock Gating Control
    __IO uint32_t RCGCGPIO;           // General-Purpose Input/Output Run Mode Clock Gating Control
    __IO uint32_t RCGCDMA;            // Micro Direct Memory Access Run Mode Clock Gating Control
    uint32_t RESERVED26;
    __IO uint32_t RCGCHIB;            // Hibernation Run Mode Clock Gating Control
    __IO uint32_t RCGCUART;           // Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control
    __IO uint32_t RCGCSSI;            // Synchronous Serial Interface Run Mode Clock Gating Control
    __IO uint32_t RCGCI2C;            // Inter-Integrated Circuit Run Mode Clock Gating Control
    uint32_t RESERVED27;
    __IO uint32_t RCGCUSB;            // Universal Serial Bus Run Mode Clock Gating Control
    uint32_t RESERVED28[2];
    __IO uint32_t RCGCCAN;            // Controller Area Network RunMode Clock Gating Control
    __IO uint32_t RCGCADC;            // Analog-to-Digital Converter Run Mode Clock Gating Control
    __IO uint32_t RCGCACMP;           // Analog Comparator Run Mode Clock Gating Control
    __IO uint32_t RCGCPWM;            // Pulse Width Modulator Run Mode Clock Gating Control
    __IO uint32_t RCGCQEI;            // Quadrature Encoder Interface Run Mode Clock Gating Control
    uint32_t RESERVED29[4];
    __IO uint32_t RCGCEEPROM;         // EEPROM Run Mode Clock Gating Control
    __IO uint32_t RCGCWTIMER;         // 32/64-BitWide General-Purpose Timer Run Mode Clock Gating Control
    uint32_t RESERVED30[40];
    __IO uint32_t SCGCWD;             // Watchdog Timer Sleep Mode Clock Gating Control
    __IO uint32_t SCGCTIMER;          // 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control
    __IO uint32_t SCGCGPIO;           // General-Purpose Input/Output Sleep Mode Clock Gating Control
    __IO uint32_t SCGCDMA;            // Micro Direct Memory Access Sleep Mode Clock Gating Control
    uint32_t RESERVED31;
    __IO uint32_t SCGCHIB;            // Hibernation Sleep Mode Clock Gating Control
    __IO uint32_t SCGCUART;           // Universal Asynchronous Receiver/Transmitter Sleep Mode Clock Gating Control
    __IO uint32_t SCGCSSI;            // Synchronous Serial Interface Sleep Mode Clock Gating Control
    __IO uint32_t SCGCI2C;            // Inter-Integrated Circuit Sleep Mode Clock Gating Control
    uint32_t RESERVED32;
    __IO uint32_t SCGCUSB;            // Universal Serial Bus Sleep Mode Clock Gating Control
    uint32_t RESERVED33[2];
    __IO uint32_t SCGCCAN;            // Controller Area Network Sleep Mode Clock Gating Control
    __IO uint32_t SCGCADC;            // Analog-to-Digital Converter Sleep Mode Clock Gating Control
    __IO uint32_t SCGCACMP;           // Analog Comparator Sleep Mode Clock Gating Control
    __IO uint32_t SCGCPWM;            // PulseWidthModulator Sleep Mode Clock Gating Control
    __IO uint32_t SCGCQEI;            // Quadrature Encoder Interface Sleep Mode Clock Gating Control
    uint32_t RESERVED34[4];
    __IO uint32_t SCGCEEPROM;         // EEPROM Sleep Mode Clock Gating Control
    __IO uint32_t SCGCWTIMER;         // 32/64-BitWideGeneral-Purpose Timer SleepMode Clock Gating Control
    uint32_t RESERVED35[40];
    __IO uint32_t DCGCWD;             // Watchdog Timer Deep-SleepMode Clock Gating Control
    __IO uint32_t DCGCTIMER;          // 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control
    __IO uint32_t DCGCGPIO;           // General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control
    __IO uint32_t DCGCDMA;            // Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control
    uint32_t RESERVED36;
    __IO uint32_t DCGCHIB;            // Hibernation Deep-Sleep Mode Clock Gating Control
    __IO uint32_t DCGCUART;           // Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode Clock Gating Control
    __IO uint32_t DCGCSSI;            // Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control
    __IO uint32_t DCGCI2C;            // Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control
    uint32_t RESERVED37;
    __IO uint32_t DCGCUSB;            // Universal Serial Bus Deep-Sleep Mode Clock Gating Control
    uint32_t RESERVED38[2];
    __IO uint32_t DCGCCAN;            // Controller Area Network Deep-SleepMode Clock Gating Control
    __IO uint32_t DCGCADC;            // Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control
    __IO uint32_t DCGCACMP;           // Analog Comparator Deep-Sleep Mode Clock Gating Control
    __IO uint32_t DCGCPWM;            // Pulse Width Modulator Deep-Sleep Mode Clock Gating Control
    __IO uint32_t DCGCQEI;            // Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control
    uint32_t RESERVED39[4];
    __IO uint32_t DCGCEEPROM;         // EEPROM Deep-Sleep Mode Clock Gating Control
    __IO uint32_t DCGCWTIMER;         // 32/64-BitWideGeneral-Purpose Timer Deep-Sleep Mode Clock Gating Control
    uint32_t RESERVED40[104];
    __I  uint32_t PRWD;               // Watchdog Timer Peripheral Ready
    __I  uint32_t PRTIMER;            // 16/32-Bit General-Purpose Timer Peripheral Ready
    __I  uint32_t PRGPIO;             // General-Purpose Input/Output Peripheral Ready
    __I  uint32_t PRDMA;              // Micro Direct Memory Access Peripheral Ready
    uint32_t RESERVED41;
    __I  uint32_t PRHIB;              // Hibernation Peripheral Ready
    __I  uint32_t PRUART;             // Universal Asynchronous Receiver/Transmitter Peripheral Ready
    __I  uint32_t PRSSI;              // Synchronous Serial Interface Peripheral Ready
    __I  uint32_t PRI2C;              // Inter-Integrated Circuit Peripheral Ready
    uint32_t RESERVED42;
    __I  uint32_t PRUSB;              // Universal Serial Bus Peripheral Ready
    uint32_t RESERVED43[2];
    __I  uint32_t PRCAN;              // Controller Area Network Peripheral Ready
    __I  uint32_t PRADC;              // Analog-to-Digital Converter Peripheral Ready
    __I  uint32_t PRACMP;             // Analog Comparator Peripheral Ready
    __I  uint32_t PRPWM;              // Pulse Width Modulator Peripheral Ready
    __I  uint32_t PRQEI;              // Quadrature Encoder Interface Peripheral Ready
    uint32_t RESERVED44[4];
    __I  uint32_t PREEPROM;           // EEPROM Peripheral Ready
    __I  uint32_t PRWTIMER;           // 32/64-BitWide General-Purpose Timer Peripheral Ready
} SYSCTL_RegDef_t;

/**
 *  System Control Register Map
 * */
#define SYSCTL_DID0                 SYSCTL_ADD_OFFSET(0x000UL) // Device Identification 0
#define SYSCTL_DID1                 SYSCTL_ADD_OFFSET(0x004UL) // Device Identification 1
#define SYSCTL_PBORCTL              SYSCTL_ADD_OFFSET(0x030UL) // Brown-Out Reset Control
#define SYSCTL_RIS                  SYSCTL_ADD_OFFSET(0x050UL) // Raw Interrupt Status
#define SYSCTL_IMC                  SYSCTL_ADD_OFFSET(0x054UL) // Raw Interrupt Status
#define SYSCTL_MISC                 SYSCTL_ADD_OFFSET(0x058UL) // Masked Interrupt Status and Clear
#define SYSCTL_RESC                 SYSCTL_ADD_OFFSET(0x05CUL) // Reset Cause
#define SYSCTL_RCC                  SYSCTL_ADD_OFFSET(0x060UL) // Run-Mode Clock Configuration
#define SYSCTL_GPIOHBCTL            SYSCTL_ADD_OFFSET(0x06CUL) // GPIO High-Performance Bus Control
#define SYSCTL_RCC2                 SYSCTL_ADD_OFFSET(0x070UL) // Run-Mode Clock Configuration 2
#define SYSCTL_MOSCCTL              SYSCTL_ADD_OFFSET(0x07CUL) // Main Oscillator Control
#define SYSCTL_DSLPCLKCFG           SYSCTL_ADD_OFFSET(0x144UL) // Deep Sleep Clock Configuration
#define SYSCTL_SYSPROP              SYSCTL_ADD_OFFSET(0x14CUL) // System Properties
#define SYSCTL_PIOSCCAL             SYSCTL_ADD_OFFSET(0x150UL) // Precision Internal Oscillator Calibration
#define SYSCTL_PIOSCSTAT            SYSCTL_ADD_OFFSET(0x154UL) // Precision Internal Oscillator Statistics
#define SYSCTL_PLLFREQ0             SYSCTL_ADD_OFFSET(0x160UL) // PLL Frequency 0
#define SYSCTL_PLLFREQ1             SYSCTL_ADD_OFFSET(0x164UL) // PLL Frequency 1
#define SYSCTL_PLLSTAT              SYSCTL_ADD_OFFSET(0x168UL) // PLL Status
#define SYSCTL_SLPPWRCFG            SYSCTL_ADD_OFFSET(0x188UL) // Sleep Power Configuration
#define SYSCTL_DSLPPWRCFG           SYSCTL_ADD_OFFSET(0x18CUL) // Deep-Sleep Power Configuration
#define SYSCTL_LDOSPCTL             SYSCTL_ADD_OFFSET(0x1B4UL) // LDO Sleep Power Control
#define SYSCTL_LDOSPCAL             SYSCTL_ADD_OFFSET(0x1B8UL) // LDO Sleep Power Calibration
#define SYSCTL_LDODPCTL             SYSCTL_ADD_OFFSET(0x1BCUL) // LDO Deep-Sleep Power Control
#define SYSCTL_LDODPCAL             SYSCTL_ADD_OFFSET(0x1C0UL) // LDO Deep-Sleep Power Calibration
#define SYSCTL_SDPMST               SYSCTL_ADD_OFFSET(0x1CCUL) // Sleep / Deep-Sleep Power Mode Status
#define SYSCTL_PPWD                 SYSCTL_ADD_OFFSET(0x300UL) // Watchdog Timer Peripheral Present
#define SYSCTL_PPTIMER              SYSCTL_ADD_OFFSET(0x304UL) // 16/32-Bit General-Purpose Timer Peripheral Present
#define SYSCTL_PPGPIO               SYSCTL_ADD_OFFSET(0x308UL) // General-Purpose Input/Output Peripheral Present
#define SYSCTL_PPDMA                SYSCTL_ADD_OFFSET(0x30CUL) // Micro Direct Memory Access Peripheral Present
#define SYSCTL_PPHIB                SYSCTL_ADD_OFFSET(0x314UL) // Hibernation Peripheral Present
#define SYSCTL_PPUART               SYSCTL_ADD_OFFSET(0x318UL) // Universal Asynchronous Receiver/Transmitter Peripheral Present
#define SYSCTL_PPSSI                SYSCTL_ADD_OFFSET(0x31CUL) // Synchronous Serial Interface Peripheral Present
#define SYSCTL_PPI2C                SYSCTL_ADD_OFFSET(0x320UL) // Inter-Integrated Circuit Peripheral Present
#define SYSCTL_PPUSB                SYSCTL_ADD_OFFSET(0x328UL) // Universal Serial Bus Peripheral Present
#define SYSCTL_PPCAN                SYSCTL_ADD_OFFSET(0x334UL) // Controller Area Network Peripheral Present
#define SYSCTL_PPADC                SYSCTL_ADD_OFFSET(0x338UL) // Analog-to-Digital Converter Peripheral Present
#define SYSCTL_PPACMP               SYSCTL_ADD_OFFSET(0x33CUL) // Analog Comparator Peripheral Present
#define SYSCTL_PPPWM                SYSCTL_ADD_OFFSET(0x340UL) // Pulse Width Modulator Peripheral Present
#define SYSCTL_PPQEI                SYSCTL_ADD_OFFSET(0x344UL) // Quadrature Encoder Interface Peripheral Present
#define SYSCTL_PPEEPROM             SYSCTL_ADD_OFFSET(0x358UL) // EEPROM Peripheral Present
#define SYSCTL_PPWTIMER             SYSCTL_ADD_OFFSET(0x35CUL) // 32/64-Bit Wide General-Purpose Timer Peripheral Present
#define SYSCTL_SRWD                 SYSCTL_ADD_OFFSET(0x500UL) // Watchdog Timer Software Reset
#define SYSCTL_SRTIMER              SYSCTL_ADD_OFFSET(0x504UL) // 16/32-Bit General-Purpose Timer Software Reset
#define SYSCTL_SRGPIO               SYSCTL_ADD_OFFSET(0x508UL) // General-Purpose Input/Output Software Reset
#define SYSCTL_SRDMA                SYSCTL_ADD_OFFSET(0x50CUL) // Micro Direct Memory Access Software Reset
#define SYSCTL_SRHIB                SYSCTL_ADD_OFFSET(0x514UL) // Hibernation Software Reset
#define SYSCTL_SRUART               SYSCTL_ADD_OFFSET(0x518UL) // Universal Asynchronous Receiver/Transmitter Software Reset
#define SYSCTL_SRSSI                SYSCTL_ADD_OFFSET(0x51CUL) // Synchronous Serial Interface Software Reset
#define SYSCTL_SRI2C                SYSCTL_ADD_OFFSET(0x520UL) // Inter-Integrated Circuit Software Reset
#define SYSCTL_SRUSB                SYSCTL_ADD_OFFSET(0x528UL) // Universal Serial Bus Software Reset
#define SYSCTL_SRCAN                SYSCTL_ADD_OFFSET(0x534UL) // Controller Area Network Software Reset
#define SYSCTL_SRADC                SYSCTL_ADD_OFFSET(0x538UL) // Analog-to-Digital Converter Software Reset
#define SYSCTL_SRACMP               SYSCTL_ADD_OFFSET(0x53CUL) // Analog Comparator Software Reset
#define SYSCTL_SRPWM                SYSCTL_ADD_OFFSET(0x540UL) // Pulse Width Modulator Software Reset
#define SYSCTL_SRQEI                SYSCTL_ADD_OFFSET(0x544UL) // Quadrature Encoder Interface Software Reset
#define SYSCTL_SREEPROM             SYSCTL_ADD_OFFSET(0x558UL) // EEPROM Software Reset
#define SYSCTL_SRWTIMER             SYSCTL_ADD_OFFSET(0x55CUL) // 32/64-Bit Wide General-Purpose Timer Software Reset
#define SYSCTL_RCGCWD               SYSCTL_ADD_OFFSET(0x600UL) // Watchdog Timer Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER            SYSCTL_ADD_OFFSET(0x604UL) // 16/32-BitGeneral-Purpose Timer Run Mode Clock Gating Control
#define SYSCTL_RCGCGPIO             SYSCTL_ADD_OFFSET(0x608UL) // General-Purpose Input/Output Run Mode Clock Gating Control
#define SYSCTL_RCGCDMA              SYSCTL_ADD_OFFSET(0x60CUL) // Micro Direct Memory Access Run Mode Clock Gating Control
#define SYSCTL_RCGCHIB              SYSCTL_ADD_OFFSET(0x614UL) // Hibernation Run Mode Clock Gating Control
#define SYSCTL_RCGCUART             SYSCTL_ADD_OFFSET(0x618UL) // Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control
#define SYSCTL_RCGCSSI              SYSCTL_ADD_OFFSET(0x61CUL) // Synchronous Serial Interface Run Mode Clock Gating Control
#define SYSCTL_RCGCI2C              SYSCTL_ADD_OFFSET(0x620UL) // Inter-Integrated Circuit Run Mode Clock Gating Control
#define SYSCTL_RCGCUSB              SYSCTL_ADD_OFFSET(0x628UL) // Universal Serial Bus Run Mode Clock Gating Control
#define SYSCTL_RCGCCAN              SYSCTL_ADD_OFFSET(0x634UL) // Controller Area Network RunMode Clock Gating Control
#define SYSCTL_RCGCADC              SYSCTL_ADD_OFFSET(0x638UL) // Analog-to-Digital Converter Run Mode Clock Gating Control
#define SYSCTL_RCGCACMP             SYSCTL_ADD_OFFSET(0x63CUL) // Analog Comparator Run Mode Clock Gating Control
#define SYSCTL_RCGCPWM              SYSCTL_ADD_OFFSET(0x640UL) // Pulse Width Modulator Run Mode Clock Gating Control
#define SYSCTL_RCGCQEI              SYSCTL_ADD_OFFSET(0x644UL) // Quadrature Encoder Interface Run Mode Clock Gating Control
#define SYSCTL_RCGCEEPROM           SYSCTL_ADD_OFFSET(0x658UL) // EEPROM Run Mode Clock Gating Control
#define SYSCTL_RCGCWTIMER           SYSCTL_ADD_OFFSET(0x65CUL) // 32/64-BitWide General-Purpose Timer Run Mode Clock Gating Control
#define SYSCTL_SCGCWD               SYSCTL_ADD_OFFSET(0x700UL) // Watchdog Timer Sleep Mode Clock Gating Control
#define SYSCTL_SCGCTIMER            SYSCTL_ADD_OFFSET(0x704UL) // 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control
#define SYSCTL_SCGCGPIO             SYSCTL_ADD_OFFSET(0x708UL) // General-Purpose Input/Output Sleep Mode Clock Gating Control
#define SYSCTL_SCGCDMA              SYSCTL_ADD_OFFSET(0x70CUL) // Micro Direct Memory Access Sleep Mode Clock Gating Control
#define SYSCTL_SCGCHIB              SYSCTL_ADD_OFFSET(0x714UL) // Hibernation Sleep Mode Clock Gating Control
#define SYSCTL_SCGCUART             SYSCTL_ADD_OFFSET(0x718UL) // Universal Asynchronous Receiver/Transmitter Sleep Mode Clock Gating Control
#define SYSCTL_SCGCSSI              SYSCTL_ADD_OFFSET(0x71CUL) // Synchronous Serial Interface Sleep Mode Clock Gating Control
#define SYSCTL_SCGCI2C              SYSCTL_ADD_OFFSET(0x720UL) // Inter-Integrated Circuit Sleep Mode Clock Gating Control
#define SYSCTL_SCGCUSB              SYSCTL_ADD_OFFSET(0x728UL) // Universal Serial Bus Sleep Mode Clock Gating Control
#define SYSCTL_SCGCCAN              SYSCTL_ADD_OFFSET(0x734UL) // Controller Area Network Sleep Mode Clock Gating Control
#define SYSCTL_SCGCADC              SYSCTL_ADD_OFFSET(0x738UL) // Analog-to-Digital Converter Sleep Mode Clock Gating Control
#define SYSCTL_SCGCACMP             SYSCTL_ADD_OFFSET(0x73CUL) // Analog Comparator Sleep Mode Clock Gating Control
#define SYSCTL_SCGCPWM              SYSCTL_ADD_OFFSET(0x740UL) // PulseWidthModulator Sleep Mode Clock Gating Control
#define SYSCTL_SCGCQEI              SYSCTL_ADD_OFFSET(0x744UL) // Quadrature Encoder Interface Sleep Mode Clock Gating Control
#define SYSCTL_SCGCEEPROM           SYSCTL_ADD_OFFSET(0x758UL) // EEPROM Sleep Mode Clock Gating Control
#define SYSCTL_SCGCWTIMER           SYSCTL_ADD_OFFSET(0x75CUL) // 32/64-BitWideGeneral-Purpose Timer SleepMode Clock Gating Control
#define SYSCTL_DCGCWD               SYSCTL_ADD_OFFSET(0x800UL) // Watchdog Timer Deep-SleepMode Clock Gating Control
#define SYSCTL_DCGCTIMER            SYSCTL_ADD_OFFSET(0x804UL) // 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCGPIO             SYSCTL_ADD_OFFSET(0x808UL) // General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCDMA              SYSCTL_ADD_OFFSET(0x80CUL) // Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCHIB              SYSCTL_ADD_OFFSET(0x814UL) // Hibernation Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCUART             SYSCTL_ADD_OFFSET(0x818UL) // Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCSSI              SYSCTL_ADD_OFFSET(0x81CUL) // Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCI2C              SYSCTL_ADD_OFFSET(0x820UL) // Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCUSB              SYSCTL_ADD_OFFSET(0x828UL) // Universal Serial Bus Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCCAN              SYSCTL_ADD_OFFSET(0x834UL) // Controller Area Network Deep-SleepMode Clock Gating Control
#define SYSCTL_DCGCADC              SYSCTL_ADD_OFFSET(0x838UL) // Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCACMP             SYSCTL_ADD_OFFSET(0x83CUL) // Analog Comparator Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCPWM              SYSCTL_ADD_OFFSET(0x840UL) // Pulse Width Modulator Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCQEI              SYSCTL_ADD_OFFSET(0x844UL) // Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCEEPROM           SYSCTL_ADD_OFFSET(0x858UL) // EEPROM Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCWTIMER           SYSCTL_ADD_OFFSET(0x85CUL) // 32/64-BitWideGeneral-Purpose Timer Deep-Sleep Mode Clock Gating Control
#define SYSCTL_PRWD                 SYSCTL_ADD_OFFSET(0xA00UL) // Watchdog Timer Peripheral Ready
#define SYSCTL_PRTIMER              SYSCTL_ADD_OFFSET(0xA04UL) // 16/32-Bit General-Purpose Timer Peripheral Ready
#define SYSCTL_PRGPIO               SYSCTL_ADD_OFFSET(0xA08UL) // General-Purpose Input/Output Peripheral Ready
#define SYSCTL_PRDMA                SYSCTL_ADD_OFFSET(0xA0CUL) // Micro Direct Memory Access Peripheral Ready
#define SYSCTL_PRHIB                SYSCTL_ADD_OFFSET(0xA14UL) // Hibernation Peripheral Ready
#define SYSCTL_PRUART               SYSCTL_ADD_OFFSET(0xA18UL) // Universal Asynchronous Receiver/Transmitter Peripheral Ready
#define SYSCTL_PRSSI                SYSCTL_ADD_OFFSET(0xA1CUL) // Synchronous Serial Interface Peripheral Ready
#define SYSCTL_PRI2C                SYSCTL_ADD_OFFSET(0xA20UL) // Inter-Integrated Circuit Peripheral Ready
#define SYSCTL_PRUSB                SYSCTL_ADD_OFFSET(0xA28UL) // Universal Serial Bus Peripheral Ready
#define SYSCTL_PRCAN                SYSCTL_ADD_OFFSET(0xA34UL) // Controller Area Network Peripheral Ready
#define SYSCTL_PRADC                SYSCTL_ADD_OFFSET(0xA38UL) // Analog-to-Digital Converter Peripheral Ready
#define SYSCTL_PRACMP               SYSCTL_ADD_OFFSET(0xA3CUL) // Analog Comparator Peripheral Ready
#define SYSCTL_PRPWM                SYSCTL_ADD_OFFSET(0xA40UL) // Pulse Width Modulator Peripheral Ready
#define SYSCTL_PRQEI                SYSCTL_ADD_OFFSET(0xA44UL) // Quadrature Encoder Interface Peripheral Ready
#define SYSCTL_PREEPROM             SYSCTL_ADD_OFFSET(0xA58UL) // EEPROM Peripheral Ready
#define SYSCTL_PRWTIMER             SYSCTL_ADD_OFFSET(0xA5CUL) // 32/64-BitWide General-Purpose Timer Peripheral Ready

/**
 *  System Control Legacy Register Map
 * */
#define SYSCTL_LEGACY_DC0            SYSCTL_ADD_OFFSET(0x008UL) // Device Capabilities 0
#define SYSCTL_LEGACY_DC1            SYSCTL_ADD_OFFSET(0x010UL) // Device Capabilities 1
#define SYSCTL_LEGACY_DC2            SYSCTL_ADD_OFFSET(0x014UL) // Device Capabilities 2
#define SYSCTL_LEGACY_DC3            SYSCTL_ADD_OFFSET(0x018UL) // Device Capabilities 3
#define SYSCTL_LEGACY_DC4            SYSCTL_ADD_OFFSET(0x01CUL) // Device Capabilities 4
#define SYSCTL_LEGACY_DC5            SYSCTL_ADD_OFFSET(0x020UL) // Device Capabilities 5
#define SYSCTL_LEGACY_DC6            SYSCTL_ADD_OFFSET(0x024UL) // Device Capabilities 6
#define SYSCTL_LEGACY_DC7            SYSCTL_ADD_OFFSET(0x028UL) // Device Capabilities 7
#define SYSCTL_LEGACY_DC8            SYSCTL_ADD_OFFSET(0x02CUL) // Device Capabilities 8
#define SYSCTL_LEGACY_SRCR0          SYSCTL_ADD_OFFSET(0x040UL) // Software Reset Control 0
#define SYSCTL_LEGACY_SRCR1          SYSCTL_ADD_OFFSET(0x044UL) // Software Reset Control 1
#define SYSCTL_LEGACY_SRCR2          SYSCTL_ADD_OFFSET(0x048UL) // Software Reset Control 2
#define SYSCTL_LEGACY_RCGC0          SYSCTL_ADD_OFFSET(0x100UL) // Run Mode Clock Gating Control Register 0
#define SYSCTL_LEGACY_RCGC1          SYSCTL_ADD_OFFSET(0x104UL) // Run Mode Clock Gating Control Register 1
#define SYSCTL_LEGACY_RCGC2          SYSCTL_ADD_OFFSET(0x108UL) // Run Mode Clock Gating Control Register 2
#define SYSCTL_LEGACY_SCGC0          SYSCTL_ADD_OFFSET(0x110UL) // Sleep Mode Clock Gating Control Register 0
#define SYSCTL_LEGACY_SCGC1          SYSCTL_ADD_OFFSET(0x114UL) // Sleep Mode Clock Gating Control Register 1
#define SYSCTL_LEGACY_SCGC2          SYSCTL_ADD_OFFSET(0x118UL) // Sleep Mode Clock Gating Control Register 2
#define SYSCTL_LEGACY_DCGC0          SYSCTL_ADD_OFFSET(0x120UL) // Deep Sleep Mode Clock Gating Control Register 0
#define SYSCTL_LEGACY_DCGC1          SYSCTL_ADD_OFFSET(0x124UL) // Deep-Sleep Mode Clock Gating Control Register 1
#define SYSCTL_LEGACY_DCGC2          SYSCTL_ADD_OFFSET(0x128UL) // Deep Sleep Mode Clock Gating Control Register 2
#define SYSCTL_LEGACY_DC9            SYSCTL_ADD_OFFSET(0x190UL) // Device Capabilities 9
#define SYSCTL_LEGACY_NVMSTAT        SYSCTL_ADD_OFFSET(0x1A0UL) // Non-Volatile Memory Information

/**
 *  ADC Register Register definition structure
 * */
#pragma pack (4)
typedef struct {
    __IO uint32_t SSMUX;       // ADC Sample Sequence Input Multiplexer Select 
    __IO uint32_t SSCTL;       // ADC Sample Sequence Control 
    __I  uint32_t SSFIFO;      // ADC Sample Sequence Result FIFO 
    __I  uint32_t SSFSTAT;     // ADC Sample Sequence FIFO Status
    __IO uint32_t SSOP;        // ADC Sample Sequence Operation
    __IO uint32_t SSDC;        // ADC Sample Sequence Digital Comparator Select
    uint32_t RESERVED[2];
}ADC_SS_RegDef_t;

#pragma pack (4)
typedef struct {
    __IO uint32_t ACTSS;        // ADC Active Sample Sequencer
    __I  uint32_t RIS;          // ADC Raw Interrupt Status
    __IO uint32_t IM;           // Interrupt Mask
    __IO uint32_t ISC;          // ADC Interrupt Status and Clear
    __IO uint32_t OSTAT;        // ADC Overflow Status
    __IO uint32_t EMUX;         // ADC Event Multiplexer Select
    __IO uint32_t USTAT;        // ADC Underflow Status
    __IO uint32_t TSSEL;        // ADC Trigger Source Select
    __IO uint32_t SSPRI;        // ADC Sample Sequencer Priority
    __IO uint32_t SPC;          // ADC Sample Phase Control
    __IO uint32_t PSSI;         // ADC Processor Sample Sequence Initiate
    uint32_t RESERVED;
    __IO uint32_t SAC;          // ADC Sample Averaging Control
    __IO uint32_t DCISC;        // ADC Digital Comparator Interrupt Status and Clear
    __IO uint32_t CTL;          // ADC Control
    uint32_t RESERVED1;
    __IO ADC_SS_RegDef_t SS[4]; // Sample Sequencer
    uint32_t RESERVED5[784];
    __O  uint32_t DCRIC;        // ADC Digital Comparator Reset Initial Conditions
    uint32_t RESERVED6[63];
    __IO uint32_t DCCTL[8];     // 0: ADC Digital Comparator Control 0
                                // 1: ADC Digital Comparator Control 1
                                // 2: ADC Digital Comparator Control 2
                                // 3: ADC Digital Comparator Control 3
                                // 4: ADC Digital Comparator Control 4
                                // 5: ADC Digital Comparator Control 5
                                // 6: ADC Digital Comparator Control 6
                                // 7: ADC Digital Comparator Control 7
    uint32_t RESERVED7[8];
    __IO uint32_t DCCMP[8];     // 0: ADC Digital Comparator Range 0
                                // 1: ADC Digital Comparator Range 1
                                // 2: ADC Digital Comparator Range 2
                                // 3: ADC Digital Comparator Range 3
                                // 4: ADC Digital Comparator Range 4
                                // 5: ADC Digital Comparator Range 5
                                // 6: ADC Digital Comparator Range 6
                                // 7: ADC Digital Comparator Range 7
    uint32_t RESERVED8[88];
    __I  uint32_t PP;           // ADC Peripheral Properties
    __IO uint32_t PC;           // ADC Peripheral Configuration
    __IO uint32_t CC;           // ADC Clock Configuration
} ADC_RegDef_t;

/**
 *  GPIO Register Register definition structure
 * */
#pragma pack (4)
typedef struct {
    uint32_t RESERVED[255];
    __IO uint32_t DATA;           // GPIO Data
    __IO uint32_t DIR;            // GPIO Direction
    __IO uint32_t IS;             // GPIO Interrupt Sense
    __IO uint32_t IBE;            // GPIO Interrupt Both Edges
    __IO uint32_t IEV;            // GPIO Interrupt Event
    __IO uint32_t IM;             // GPIO Interrupt Mask
    __IO uint32_t RIS;            // GPIO Raw Interrupt Status
    __I  uint32_t MIS;            // GPIO Masked Interrupt Status
    __I  uint32_t ICR;            // GPIO Interrupt Clear
    __O  uint32_t AFSEL;          // GPIO Alternate Function Select
    uint32_t RESERVED1[55];
    __IO uint32_t DR2R;           // GPIO 2-mA Drive Select
    __IO uint32_t DR4R;           // GPIO 4-mA Drive Select
    __IO uint32_t DR8R;           // GPIO 8-mA Drive Select
    __IO uint32_t ODR;            // GPIO Open Drain Select
    __IO uint32_t PUR;            // GPIO Pull-Up Select
    __IO uint32_t PDR;            // GPIO Pull-Down Select
    __IO uint32_t SLR;            // GPIO Slew Rate Control Select
    __IO uint32_t DEN;            // GPIO Digital Enable
    __IO uint32_t LOCK;           // GPIO Lock
    __IO uint32_t CR;             // GPIO Commit
    __IO uint32_t AMSEL;          // GPIO Analog Mode Select
    __IO uint32_t PCTL;           // GPIO Port Control
    __IO uint32_t ADCCTL;         // GPIO ADC Control
    __IO uint32_t DMACTL;         // GPIO DMA Control
    uint32_t RESERVED2[678];
    __I  uint32_t PeriphID4;      // GPIO Peripheral Identification 4
    __I  uint32_t PeriphID5;      // GPIO Peripheral Identification 5
    __I  uint32_t PeriphID6;      // GPIO Peripheral Identification 6
    __I  uint32_t PeriphID7;      // GPIO Peripheral Identification 7
    __I  uint32_t PeriphID0;      // GPIO Peripheral Identification 0
    __I  uint32_t PeriphID1;      // GPIO Peripheral Identification 1
    __I  uint32_t PeriphID2;      // GPIO Peripheral Identification 2
    __I  uint32_t PeriphID3;      // GPIO Peripheral Identification 3
    __I  uint32_t PCellID0;       // GPIO PrimeCell Identification 0
    __I  uint32_t PCellID1;       // GPIO PrimeCell Identification 1
    __I  uint32_t PCellID2;       // GPIO PrimeCell Identification 2
    __I  uint32_t PCellID3;       // GPIO PrimeCell Identification 3
} GPIO_RegDef_t;

/**
 *  GPIO Register Map
 * */
#define GPIOx_DATA(GPIOx_BASEADDR)            GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x000UL) // GPIO Data
#define GPIOx_DIR(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x400UL) // GPIO Direction
#define GPIOx_IS(GPIOx_BASEADDR)              GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x404UL) // GPIO Interrupt Sense
#define GPIOx_IBE(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x408UL) // GPIO Interrupt Both Edges
#define GPIOx_IEV(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x40CUL) // GPIO Interrupt Event
#define GPIOx_IM(GPIOx_BASEADDR)              GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x410UL) // GPIO Interrupt Mask
#define GPIOx_RIS(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x414UL) // GPIO Raw Interrupt Status
#define GPIOx_MIS(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x418UL) // GPIO Masked Interrupt Status
#define GPIOx_ICR(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x41CUL) // GPIO Interrupt Clear
#define GPIOx_AFSEL(GPIOx_BASEADDR)           GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x420UL) // GPIO Alternate Function Select
#define GPIOx_DR2R(GPIOx_BASEADDR)            GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x500UL) // GPIO 2-mA Drive Select
#define GPIOx_DR4R(GPIOx_BASEADDR)            GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x504UL) // GPIO 4-mA Drive Select
#define GPIOx_DR8R(GPIOx_BASEADDR)            GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x508UL) // GPIO 8-mA Drive Select
#define GPIOx_ODR(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x50CUL) // GPIO Open Drain Select
#define GPIOx_PUR(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x510UL) // GPIO Pull-Up Select
#define GPIOx_PDR(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x514UL) // GPIO Pull-Down Select
#define GPIOx_SLR(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x518UL) // GPIO Slew Rate Control Select
#define GPIOx_DEN(GPIOx_BASEADDR)             GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x51CUL) // GPIO Digital Enable
#define GPIOx_LOCK(GPIOx_BASEADDR)            GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x520UL) // GPIO Lock
#define GPIOx_CR(GPIOx_BASEADDR)              GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x524UL) // GPIO Commit
#define GPIOx_AMSEL(GPIOx_BASEADDR)           GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x528UL) // GPIO Analog Mode Select
#define GPIOx_PCTL(GPIOx_BASEADDR)            GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x52CUL) // GPIO Port Control
#define GPIOx_ADCCTL(GPIOx_BASEADDR)          GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x530UL) // GPIO ADC Control
#define GPIOx_DMACTL(GPIOx_BASEADDR)          GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0x534UL) // GPIO DMA Control
#define GPIOx_PeriphID4(GPIOx_BASEADDR)       GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFD0UL) // GPIO Peripheral Identification 4
#define GPIOx_PeriphID5(GPIOx_BASEADDR)       GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFD4UL) // GPIO Peripheral Identification 5
#define GPIOx_PeriphID6(GPIOx_BASEADDR)       GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFD8UL) // GPIO Peripheral Identification 6
#define GPIOx_PeriphID7(GPIOx_BASEADDR)       GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFDCUL) // GPIO Peripheral Identification 7
#define GPIOx_PeriphID0(GPIOx_BASEADDR)       GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFE0UL) // GPIO Peripheral Identification 0
#define GPIOx_PeriphID1(GPIOx_BASEADDR)       GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFE4UL) // GPIO Peripheral Identification 1
#define GPIOx_PeriphID2(GPIOx_BASEADDR)       GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFE8UL) // GPIO Peripheral Identification 2
#define GPIOx_PeriphID3(GPIOx_BASEADDR)       GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFECUL) // GPIO Peripheral Identification 3
#define GPIOx_PCellID0(GPIOx_BASEADDR)        GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFF0UL) // GPIO PrimeCell Identification 0
#define GPIOx_PCellID1(GPIOx_BASEADDR)        GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFF4UL) // GPIO PrimeCell Identification 1
#define GPIOx_PCellID2(GPIOx_BASEADDR)        GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFF8UL) // GPIO PrimeCell Identification 2
#define GPIOx_PCellID3(GPIOx_BASEADDR)        GPIOx_ADD_OFFSET(GPIOx_BASEADDR,0xFFCUL) // GPIO PrimeCell Identification 3

/*
 * Clock enable/disable macros for GPIOx peripherals
 * */
#define GPIOA_PCLK_EN()        (SYSCTL_RCGCGPIO |= (1 << 0))
#define GPIOB_PCLK_EN()        (SYSCTL_RCGCGPIO |= (1 << 1))
#define GPIOC_PCLK_EN()        (SYSCTL_RCGCGPIO |= (1 << 2))
#define GPIOD_PCLK_EN()        (SYSCTL_RCGCGPIO |= (1 << 3))
#define GPIOE_PCLK_EN()        (SYSCTL_RCGCGPIO |= (1 << 4))
#define GPIOF_PCLK_EN()        (SYSCTL_RCGCGPIO |= (1 << 5))

#define GPIOA_PCLK_EN_W(WAIT)  do{ GPIOA_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRGPIO >> 0) & 1));} while(false)
#define GPIOB_PCLK_EN_W(WAIT)  do{ GPIOB_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRGPIO >> 1) & 1));} while(false)
#define GPIOC_PCLK_EN_W(WAIT)  do{ GPIOC_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRGPIO >> 2) & 1));} while(false)
#define GPIOD_PCLK_EN_W(WAIT)  do{ GPIOD_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRGPIO >> 3) & 1));} while(false)
#define GPIOE_PCLK_EN_W(WAIT)  do{ GPIOE_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRGPIO >> 4) & 1));} while(false)
#define GPIOF_PCLK_EN_W(WAIT)  do{ GPIOF_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRGPIO >> 5) & 1));} while(false)

#define GPIOA_PCLK_DI()        (SYSCTL_RCGCGPIO &= ~(1 << 0))
#define GPIOB_PCLK_DI()        (SYSCTL_RCGCGPIO &= ~(1 << 1))
#define GPIOC_PCLK_DI()        (SYSCTL_RCGCGPIO &= ~(1 << 2))
#define GPIOD_PCLK_DI()        (SYSCTL_RCGCGPIO &= ~(1 << 3))
#define GPIOE_PCLK_DI()        (SYSCTL_RCGCGPIO &= ~(1 << 4))
#define GPIOF_PCLK_DI()        (SYSCTL_RCGCGPIO &= ~(1 << 5))

/*
 * Clock enable/disable macros for ADCx peripherals
 * */
#define ADC0_PCLK_EN()        (SYSCTL->RCGCADC |= (1 << 0))
#define ADC1_PCLK_EN()        (SYSCTL->RCGCADC |= (1 << 1))

#define ADC0_PCLK_EN_W(WAIT)  do{ ADC0_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRADC >> 0) & 1));} while(false)
#define ADC1_PCLK_EN_W(WAIT)  do{ ADC1_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRADC >> 1) & 1));} while(false)

#define ADC0_PCLK_DI()        (SYSCTL->RCGCADC &= ~(1 << 0))
#define ADC1_PCLK_DI()        (SYSCTL->RCGCADC &= ~(1 << 1))

/*
 * Clock enable/disable macros for SSIx peripherals
 * */
#define SPI0_PCLK_EN()        (SYSCTL->RCGCSSI |= (1 << 0))
#define SPI1_PCLK_EN()        (SYSCTL->RCGCSSI |= (1 << 1))
#define SPI2_PCLK_EN()        (SYSCTL->RCGCSSI |= (1 << 2))
#define SPI3_PCLK_EN()        (SYSCTL->RCGCSSI |= (1 << 3))

#define SPI0_PCLK_EN_W(WAIT)  do{ SPI0_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRSSI >> 0) & 1));} while(false)
#define SPI1_PCLK_EN_W(WAIT)  do{ SPI1_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRSSI >> 1) & 1));} while(false)
#define SPI2_PCLK_EN_W(WAIT)  do{ SPI2_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRSSI >> 2) & 1));} while(false)
#define SPI3_PCLK_EN_W(WAIT)  do{ SPI3_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRSSI >> 3) & 1));} while(false)

#define SPI0_PCLK_DI()        (SYSCTL->RCGCSSI &= ~(1 << 0))
#define SPI1_PCLK_DI()        (SYSCTL->RCGCSSI &= ~(1 << 1))
#define SPI2_PCLK_DI()        (SYSCTL->RCGCSSI &= ~(1 << 2))
#define SPI3_PCLK_DI()        (SYSCTL->RCGCSSI &= ~(1 << 3))

/*
 * Clock enable/disable macros for TIMER peripherals
 * */
#define TIMER0_PCLK_EN()        (SYSCTL->RCGCTIMER |= (1 << 0))
#define TIMER1_PCLK_EN()        (SYSCTL->RCGCTIMER |= (1 << 1))
#define TIMER2_PCLK_EN()        (SYSCTL->RCGCTIMER |= (1 << 2))
#define TIMER3_PCLK_EN()        (SYSCTL->RCGCTIMER |= (1 << 3))
#define TIMER4_PCLK_EN()        (SYSCTL->RCGCTIMER |= (1 << 4))
#define TIMER5_PCLK_EN()        (SYSCTL->RCGCTIMER |= (1 << 5))

#define TIMER0_PCLK_EN_W(WAIT)  do{ TIMER0_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRTIMER >> 0) & 1));} while(false)
#define TIMER1_PCLK_EN_W(WAIT)  do{ TIMER1_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRTIMER >> 1) & 1));} while(false)
#define TIMER2_PCLK_EN_W(WAIT)  do{ TIMER2_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRTIMER >> 2) & 1));} while(false)
#define TIMER3_PCLK_EN_W(WAIT)  do{ TIMER3_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRTIMER >> 3) & 1));} while(false)
#define TIMER4_PCLK_EN_W(WAIT)  do{ TIMER4_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRTIMER >> 4) & 1));} while(false)
#define TIMER5_PCLK_EN_W(WAIT)  do{ TIMER5_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRTIMER >> 5) & 1));} while(false)

#define TIMER0_PCLK_DI()        (SYSCTL->RCGCTIMER &= ~(1 << 0))
#define TIMER1_PCLK_DI()        (SYSCTL->RCGCTIMER &= ~(1 << 1))
#define TIMER2_PCLK_DI()        (SYSCTL->RCGCTIMER &= ~(1 << 2))
#define TIMER3_PCLK_DI()        (SYSCTL->RCGCTIMER &= ~(1 << 3))
#define TIMER4_PCLK_DI()        (SYSCTL->RCGCTIMER &= ~(1 << 4))
#define TIMER5_PCLK_DI()        (SYSCTL->RCGCTIMER &= ~(1 << 5))

/*
 * Clock enable/disable macros for WIDE TIMER peripherals
 * */
#define WTIMER0_PCLK_EN()        (SYSCTL->RCGCWTIMER |= (1 << 0))
#define WTIMER1_PCLK_EN()        (SYSCTL->RCGCWTIMER |= (1 << 1))
#define WTIMER2_PCLK_EN()        (SYSCTL->RCGCWTIMER |= (1 << 2))
#define WTIMER3_PCLK_EN()        (SYSCTL->RCGCWTIMER |= (1 << 3))
#define WTIMER4_PCLK_EN()        (SYSCTL->RCGCWTIMER |= (1 << 4))
#define WTIMER5_PCLK_EN()        (SYSCTL->RCGCWTIMER |= (1 << 5))

#define WTIMER0_PCLK_EN_W(WAIT)  do{ WTIMER0_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRWTIMER >> 0) & 1));} while(false)
#define WTIMER1_PCLK_EN_W(WAIT)  do{ WTIMER1_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRWTIMER >> 1) & 1));} while(false)
#define WTIMER2_PCLK_EN_W(WAIT)  do{ WTIMER2_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRWTIMER >> 2) & 1));} while(false)
#define WTIMER3_PCLK_EN_W(WAIT)  do{ WTIMER3_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRWTIMER >> 3) & 1));} while(false)
#define WTIMER4_PCLK_EN_W(WAIT)  do{ WTIMER4_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRWTIMER >> 4) & 1));} while(false)
#define WTIMER5_PCLK_EN_W(WAIT)  do{ WTIMER5_PCLK_EN(); while((bool)WAIT && !((SYSCTL->PRWTIMER >> 5) & 1));} while(false)

#define WTIMER0_PCLK_DI()        (SYSCTL->RCGCWTIMER &= ~(1 << 0))
#define WTIMER1_PCLK_DI()        (SYSCTL->RCGCWTIMER &= ~(1 << 1))
#define WTIMER2_PCLK_DI()        (SYSCTL->RCGCWTIMER &= ~(1 << 2))
#define WTIMER3_PCLK_DI()        (SYSCTL->RCGCWTIMER &= ~(1 << 3))
#define WTIMER4_PCLK_DI()        (SYSCTL->RCGCWTIMER &= ~(1 << 4))
#define WTIMER5_PCLK_DI()        (SYSCTL->RCGCWTIMER &= ~(1 << 5))

/**
 *  GPIO Register Register definition structure
 * */
#pragma pack (4)
typedef struct {
    __IO uint32_t EN[5];      // 0: Interrupt 0-31 Set Enable
                              // 1: Interrupt 32-63 Set Enable
                              // 2: Interrupt 64-95 Set Enable
                              // 3: Interrupt 96-127 Set Enable
                              // 4: Interrupt 128-138 Set Enable
    uint32_t RESERVED2[27];
    __IO uint32_t DIS[5];     // 0: Interrupt 0-31 Clear Enable
                              // 1: Interrupt 32-63 Clear Enable
                              // 2: Interrupt 64-95 Clear Enable
                              // 3: Interrupt 96-127 Clear Enable
                              // 4: Interrupt 128-138 Clear Enable
    uint32_t RESERVED3[27];
    __IO uint32_t PEND[5];    // 0: Interrupt 0-31 Set Pending
                              // 1: Interrupt 32-63 Set Pending
                              // 2: Interrupt 64-95 Set Pending
                              // 3: Interrupt 96-127 Set Pending
                              // 4: Interrupt 128-138 Set Pending
    uint32_t RESERVED4[27];
    __IO uint32_t UNPEND[5];  // 0: Interrupt 0-31 Clear Pending
                              // 1: Interrupt 32-63 Clear Pending
                              // 2: Interrupt 64-95 Clear Pending
                              // 3: Interrupt 96-127 Clear Pending
                              // 4: Interrupt 128-138 Clear Pending
    uint32_t RESERVED5[27];
    __I  uint32_t ACTIVE[5];  // 0: Interrupt 0-31 Active Bit
                              // 1: Interrupt 32-63 Active Bit
                              // 2: Interrupt 64-95 Active Bit
                              // 3: Interrupt 96-127 Active Bit
                              // 4: Interrupt 128-138 Active Bit
    uint32_t RESERVED6[59];
    __IO uint32_t PRI[35];    //  0: Interrupt 0-3 Priority
                              //  1: Interrupt 4-7 Priority
                              //  2: Interrupt 8-11 Priority
                              //  3: Interrupt 12-15 Priority
                              //  4: Interrupt 16-19 Priority
                              //  5: Interrupt 20-23 Priority
                              //  6: Interrupt 24-27 Priority
                              //  7: Interrupt 28-31 Priority
                              //  8: Interrupt 32-35 Priority
                              //  9: Interrupt 36-39 Priority
                              // 10: Interrupt 40-43 Priority
                              // 11: Interrupt 44-47 Priority
                              // 12: Interrupt 48-51 Priority
                              // 13: Interrupt 52-55 Priority
                              // 14: Interrupt 56-59 Priority
                              // 15: Interrupt 60-63 Priority
                              // 16: Interrupt 64-67 Priority
                              // 17: Interrupt 68-71 Priority
                              // 18: Interrupt 72-75 Priority
                              // 19: Interrupt 76-79 Priority
                              // 20: Interrupt 80-83 Priority
                              // 21: Interrupt 84-87 Priority
                              // 22: Interrupt 88-91 Priority
                              // 23: Interrupt 92-95 Priority
                              // 24: Interrupt 96-99 Priority
                              // 25: Interrupt 100-103 Priority
                              // 26: Interrupt 104-107 Priority
                              // 27: Interrupt 108-111 Priority
                              // 28: Interrupt 112-115 Priority
                              // 29: Interrupt 116-119 Priority
                              // 30: Interrupt 120-123 Priority
                              // 31: Interrupt 124-127 Priority
                              // 32: Interrupt 128-131 Priority
                              // 33: Interrupt 132-135 Priority
                              // 34: Interrupt 136-138 Priority
    uint32_t RESERVED7[669];
    __O  uint32_t SWTRIG;     // Software Trigger Interrupt 156

} NVIC_RegDef_t;

/**
 * @IRQ_Numbers
 * */
#define  IRQ_NUM_GPIO_Port_A                                   0
#define  IRQ_NUM_GPIO_Port_B                                   1
#define  IRQ_NUM_GPIO_Port_C                                   2
#define  IRQ_NUM_GPIO_Port_D                                   3
#define  IRQ_NUM_GPIO_Port_E                                   4
#define  IRQ_NUM_UART0                                         5
#define  IRQ_NUM_UART1                                         6
#define  IRQ_NUM_SSI0                                          7
#define  IRQ_NUM_I2C0                                          8
#define  IRQ_NUM_PWM0_Fault                                    9
#define  IRQ_NUM_PWM0_Generator_0                              10
#define  IRQ_NUM_PWM0_Generator_1                              11
#define  IRQ_NUM_PWM0_Generator_2                              12
#define  IRQ_NUM_QEI0                                          13
#define  IRQ_NUM_ADC0_Sequence_0                               14
#define  IRQ_NUM_ADC0_Sequence_1                               15
#define  IRQ_NUM_ADC0_Sequence_2                               16
#define  IRQ_NUM_ADC0_Sequence_3                               17
#define  IRQ_NUM_Watchdog_Timers_0_and_1                       18
#define  IRQ_NUM_16_32_Bit_Timer_0A                            19
#define  IRQ_NUM_16_32_Bit_Timer_0B                            20
#define  IRQ_NUM_16_32_Bit_Timer_1A                            21
#define  IRQ_NUM_16_32_Bit_Timer_1B                            22
#define  IRQ_NUM_16_32_Bit_Timer_2A                            23
#define  IRQ_NUM_16_32_Bit_Timer_2B                            24
#define  IRQ_NUM_Analog_Comparator_0                           25
#define  IRQ_NUM_Analog_Comparator_1                           26
#define  IRQ_NUM_System_Control                                28
#define  IRQ_NUM_Flash_Memory_Control_and_EEPROM_Control       29
#define  IRQ_NUM_GPIO_Port_F                                   30
#define  IRQ_NUM_UART2                                         33
#define  IRQ_NUM_SSI1                                          34
#define  IRQ_NUM_16_32_Bit_Timer_3A                            35
#define  IRQ_NUM_16_32_Bit_Timer_3B                            36
#define  IRQ_NUM_I2C1                                          37
#define  IRQ_NUM_QEI1                                          38
#define  IRQ_NUM_CAN0                                          39
#define  IRQ_NUM_CAN1                                          40
#define  IRQ_NUM_Hibernation_Module                            43
#define  IRQ_NUM_USB                                           44
#define  IRQ_NUM_PWM_Generator_3                               45
#define  IRQ_NUM_??DMA_Software                                 46
#define  IRQ_NUM_??DMA_Error                                    47
#define  IRQ_NUM_ADC1_Sequence_0                               48
#define  IRQ_NUM_ADC1_Sequence_1                               49
#define  IRQ_NUM_ADC1_Sequence_2                               50
#define  IRQ_NUM_ADC1_Sequence_3                               51
#define  IRQ_NUM_SSI2                                          57
#define  IRQ_NUM_SSI3                                          58
#define  IRQ_NUM_UART3                                         59
#define  IRQ_NUM_UART4                                         60
#define  IRQ_NUM_UART5                                         61
#define  IRQ_NUM_UART6                                         62
#define  IRQ_NUM_UART7                                         63
#define  IRQ_NUM_I2C2                                          68
#define  IRQ_NUM_I2C3                                          69
#define  IRQ_NUM_16_32_Bit_Timer_4A                            70
#define  IRQ_NUM_16_32_Bit_Timer_4B                            71
#define  IRQ_NUM_16_32_Bit_Timer_5A                            92
#define  IRQ_NUM_16_32_Bit_Timer_5B                            93
#define  IRQ_NUM_32_64_Bit_Timer_0A                            94
#define  IRQ_NUM_32_64_Bit_Timer_0B                            95
#define  IRQ_NUM_32_64_Bit_Timer_1A                            96
#define  IRQ_NUM_32_64_Bit_Timer_1B                            97
#define  IRQ_NUM_32_64_Bit_Timer_2A                            98
#define  IRQ_NUM_32_64_Bit_Timer_2B                            99
#define  IRQ_NUM_32_64_Bit_Timer_3A                            100
#define  IRQ_NUM_32_64_Bit_Timer_3B                            101
#define  IRQ_NUM_32_64_Bit_Timer_4A                            102
#define  IRQ_NUM_32_64_Bit_Timer_4B                            103
#define  IRQ_NUM_32_64_Bit_Timer_5A                            104
#define  IRQ_NUM_32_64_Bit_Timer_5B                            105
#define  IRQ_NUM_SystemException                               106
#define  IRQ_NUM_PWM1_Generator_0                              134
#define  IRQ_NUM_PWM1_Generator_1                              135
#define  IRQ_NUM_PWM1_Generator_2                              136
#define  IRQ_NUM_PWM1_Generator_3                              137
#define  IRQ_NUM_PWM1_Fault                                    138

/*
 * Peripheral definitions
 * */
#define GPIOA_APB ((GPIO_RegDef_t *) GPIOA_APB_BASE_ADDR)
#define GPIOB_APB ((GPIO_RegDef_t *) GPIOB_APB_BASE_ADDR)
#define GPIOC_APB ((GPIO_RegDef_t *) GPIOC_APB_BASE_ADDR)
#define GPIOD_APB ((GPIO_RegDef_t *) GPIOD_APB_BASE_ADDR)
#define GPIOE_APB ((GPIO_RegDef_t *) GPIOE_APB_BASE_ADDR)
#define GPIOF_APB ((GPIO_RegDef_t *) GPIOF_APB_BASE_ADDR)

#define GPIOA_AHB ((GPIO_RegDef_t *) GPIOA_AHB_BASE_ADDR)
#define GPIOB_AHB ((GPIO_RegDef_t *) GPIOB_AHB_BASE_ADDR)
#define GPIOC_AHB ((GPIO_RegDef_t *) GPIOC_AHB_BASE_ADDR)
#define GPIOD_AHB ((GPIO_RegDef_t *) GPIOD_AHB_BASE_ADDR)
#define GPIOE_AHB ((GPIO_RegDef_t *) GPIOE_AHB_BASE_ADDR)
#define GPIOF_AHB ((GPIO_RegDef_t *) GPIOF_AHB_BASE_ADDR)

#define ADC0      ((ADC_RegDef_t *) ADC0_BASE_ADDR)
#define ADC1      ((ADC_RegDef_t *) ADC1_BASE_ADDR)

#define SYSCTL    ((SYSCTL_RegDef_t *)  SYSCTL_BASE_ADDR)
#define NVIC      ((NVIC_RegDef_t *)    NVIC_BASEADDR)

#define SSI0      ((SSI_RegDef_t *)    SSI0_BASE_ADDR)
#define SSI1      ((SSI_RegDef_t *)    SSI1_BASE_ADDR)
#define SSI2      ((SSI_RegDef_t *)    SSI2_BASE_ADDR)
#define SSI3      ((SSI_RegDef_t *)    SSI3_BASE_ADDR)

#define SPI0       SSI0
#define SPI1       SSI1
#define SPI2       SSI2
#define SPI3       SSI3

#define TIMER0     ((TIMER_RegDef_t *) TIMER0_BASE_ADDR)
#define TIMER1     ((TIMER_RegDef_t *) TIMER1_BASE_ADDR)
#define TIMER2     ((TIMER_RegDef_t *) TIMER2_BASE_ADDR)
#define TIMER3     ((TIMER_RegDef_t *) TIMER3_BASE_ADDR)
#define TIMER4     ((TIMER_RegDef_t *) TIMER4_BASE_ADDR)
#define TIMER5     ((TIMER_RegDef_t *) TIMER5_BASE_ADDR)

#define WTIMER0    ((TIMER_RegDef_t *) WTIMER0_BASE_ADDR)
#define WTIMER1    ((TIMER_RegDef_t *) WTIMER1_BASE_ADDR)
#define WTIMER2    ((TIMER_RegDef_t *) WTIMER2_BASE_ADDR)
#define WTIMER3    ((TIMER_RegDef_t *) WTIMER3_BASE_ADDR)
#define WTIMER4    ((TIMER_RegDef_t *) WTIMER4_BASE_ADDR)
#define WTIMER5    ((TIMER_RegDef_t *) WTIMER5_BASE_ADDR)

/*
 * GPIOx peripheral reset macros
 * */
#define GPIOA_REG_RST_W(WAIT)    do{(SYSCTL->SRGPIO |= (1 << 0)); (SYSCTL->SRGPIO &= ~(1 << 0)); while((bool)WAIT && !((SYSCTL->PRGPIO >> 0) & 1));} while(false)
#define GPIOB_REG_RST_W(WAIT)    do{(SYSCTL->SRGPIO |= (1 << 1)); (SYSCTL->SRGPIO &= ~(1 << 1)); while((bool)WAIT && !((SYSCTL->PRGPIO >> 1) & 1));} while(false)
#define GPIOC_REG_RST_W(WAIT)    do{(SYSCTL->SRGPIO |= (1 << 2)); (SYSCTL->SRGPIO &= ~(1 << 2)); while((bool)WAIT && !((SYSCTL->PRGPIO >> 2) & 1));} while(false)
#define GPIOD_REG_RST_W(WAIT)    do{(SYSCTL->SRGPIO |= (1 << 3)); (SYSCTL->SRGPIO &= ~(1 << 3)); while((bool)WAIT && !((SYSCTL->PRGPIO >> 3) & 1));} while(false)
#define GPIOE_REG_RST_W(WAIT)    do{(SYSCTL->SRGPIO |= (1 << 4)); (SYSCTL->SRGPIO &= ~(1 << 4)); while((bool)WAIT && !((SYSCTL->PRGPIO >> 4) & 1));} while(false)
#define GPIOF_REG_RST_W(WAIT)    do{(SYSCTL->SRGPIO |= (1 << 5)); (SYSCTL->SRGPIO &= ~(1 << 5)); while((bool)WAIT && !((SYSCTL->PRGPIO >> 5) & 1));} while(false)

#define GPIOA_REG_RST() do{GPIOA_REG_RST_W(false);} while(false)
#define GPIOB_REG_RST() do{GPIOB_REG_RST_W(false);} while(false)
#define GPIOC_REG_RST() do{GPIOC_REG_RST_W(false);} while(false)
#define GPIOD_REG_RST() do{GPIOD_REG_RST_W(false);} while(false)
#define GPIOE_REG_RST() do{GPIOE_REG_RST_W(false);} while(false)
#define GPIOF_REG_RST() do{GPIOF_REG_RST_W(false);} while(false)

// GPIO unlock value
#define GPIO_UNLOCK_VALUE      0x4C4F434BUL
#define GPIO_LOCK_VALUE        0x00000001UL

/*
 * GPIOx peripheral unlock/lock macros
 * */
#define GPIOx_UNLOCK_MACRO(pGPIOx)      (pGPIOx->LOCK = GPIO_UNLOCK_VALUE)
#define GPIOx_LOCK_MACRO(pGPIOx)        (pGPIOx->LOCK = GPIO_LOCK_VALUE)

#define GPIOA_APB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOA_APB)
#define GPIOB_APB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOB_APB)
#define GPIOC_APB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOC_APB)
#define GPIOD_APB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOD_APB)
#define GPIOE_APB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOE_APB)
#define GPIOF_APB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOF_APB)

#define GPIOA_AHB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOA_AHB)
#define GPIOB_AHB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOB_AHB)
#define GPIOC_AHB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOC_AHB)
#define GPIOD_AHB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOD_AHB)
#define GPIOE_AHB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOE_AHB)
#define GPIOF_AHB_UNLOCK()      GPIOx_UNLOCK_MACRO(GPIOF_AHB)

#define GPIOA_APB_LOCK()        GPIOx_LOCK_MACRO(GPIOA_APB)
#define GPIOB_APB_LOCK()        GPIOx_LOCK_MACRO(GPIOB_APB)
#define GPIOC_APB_LOCK()        GPIOx_LOCK_MACRO(GPIOC_APB)
#define GPIOD_APB_LOCK()        GPIOx_LOCK_MACRO(GPIOD_APB)
#define GPIOE_APB_LOCK()        GPIOx_LOCK_MACRO(GPIOE_APB)
#define GPIOF_APB_LOCK()        GPIOx_LOCK_MACRO(GPIOF_APB)

#define GPIOA_AHB_LOCK()        GPIOx_LOCK_MACRO(GPIOA_AHB)
#define GPIOB_AHB_LOCK()        GPIOx_LOCK_MACRO(GPIOB_AHB)
#define GPIOC_AHB_LOCK()        GPIOx_LOCK_MACRO(GPIOC_AHB)
#define GPIOD_AHB_LOCK()        GPIOx_LOCK_MACRO(GPIOD_AHB)
#define GPIOE_AHB_LOCK()        GPIOx_LOCK_MACRO(GPIOE_AHB)
#define GPIOF_AHB_LOCK()        GPIOx_LOCK_MACRO(GPIOF_AHB)


/**
 * Bit position definitions for SPIx peripheral
 * */

/* SPI CR0 */
#define SPI_CR0_DSS             0 // SSI Data Size Select
#define SPI_CR0_FRF             4 // SSI Frame Format Select
#define SPI_CR0_SPO             6 // SSI Serial Clock Polarity
#define SPI_CR0_SPH             7 // SSI Serial Clock Phase
#define SPI_CR0_SCR             8 // SSI Serial Clock Rate

/* SPI CR1 */
#define SPI_CR1_LBM             0 // SSI Loopback Mode
#define SPI_CR1_SSE             1 // SSI Synchronous Serial Port Enable
#define SPI_CR1_MS              2 // SSI Master/Slave Select
#define SPI_CR1_EOT             4 // End of Transmission

/* SPI SR */
#define SPI_SR_TFE              0 // SSI Transmit FIFO Empty
#define SPI_SR_TNF              1 // SSI Transmit FIFO Not Full
#define SPI_SR_RNE              2 // SSI Receive FIFO Not Empty
#define SPI_SR_RFF              3 // SSI Receive FIFO Full
#define SPI_SR_BSY              4 // SSI Busy Bit

// generic macros
#define ENABLE                  1
#define DISABLE                 0
#define SET                     ENABLE
#define RESET                   DISABLE
#define CLEAR                   RESET
#define GPIO_PIN_SET            SET
#define GPIO_PIN_RESET          RESET

/**
 * Bit position definitions for (W)TIMERx peripheral
 * */
#define TIMER_CTL_TAEN          0  // GPTM Timer A Enable
#define TIMER_CTL_TASTALL       1  // GPTM Timer A Stall Enable
#define TIMER_CTL_TAEVENT       2  // GPTM Timer A Event Mode
#define TIMER_CTL_RTCEN         4  // GPTM RTC Stall Enable
#define TIMER_CTL_TAOTE         5  // GPTM Timer A Output Trigger Enable
#define TIMER_CTL_TAPWML        6  // GPTM Timer A PWM Output Level
#define TIMER_CTL_TBEN          8  // GPTM Timer B Enable
#define TIMER_CTL_TBSTALL       9  // GPTM Timer B Stall Enable
#define TIMER_CTL_TBEVENT       10 // GPTM Timer B Event Mode
#define TIMER_CTL_TBOTE         13 // GPTM Timer B Output Trigger Enable
#define TIMER_CTL_TBPWML        14 // GPTM Timer B PWM Output Level

#define TIMER_TxMR_TxMR         0  // GPTM Timer x Mode
#define TIMER_TxMR_TxCMR        2  // GPTM Timer x Capture Mode
#define TIMER_TxMR_TxAMS        3  // GPTM Timer x Alternate Mode Select
#define TIMER_TxMR_TxCDIR       4  // GPTM Timer x Count Direction
#define TIMER_TxMR_TxMIE        5  // GPTM Timer x Match Interrupt Enable
#define TIMER_TxMR_TxWOT        6  // GPTM Timer x Wait-on-Trigger
#define TIMER_TxMR_TxSNAPS      7  // GPTM Timer x Snap-Shot Mode
#define TIMER_TxMR_TxILD        8  // GPTM Timer x Interval Load Write
#define TIMER_TxMR_TxPWMIE      9  // GPTM Timer x PWM Interrupt Enable
#define TIMER_TxMR_TxMRSU       10 // GPTM Timer x Match Register Update
#define TIMER_TxMR_TxPLO        11 // GPTM Timer x PWM Legacy Operation

#define TIMER_ICR_TATOCINT      0  // GPTM Timer A Time-Out Raw Interrupt
#define TIMER_ICR_CAMCINT       1  // GPTM Timer A Capture Mode Match Interrupt Clear
#define TIMER_ICR_CAECINT       2  // GPTM Timer A Capture Mode Event Interrupt Clear
#define TIMER_ICR_RTCCINT       3  // GPTM RTC Interrupt Clear
#define TIMER_ICR_TAMCINT       4  // GPTM Timer A Match Interrupt Clear
#define TIMER_ICR_TBTOCINT      8  // GPTM Timer B Time-Out Interrupt Clear
#define TIMER_ICR_CBMCINT       9  // GPTM Timer B Capture Mode Match Interrupt Clear
#define TIMER_ICR_CBECINT       10 // GPTM Timer B Capture Mode Event Interrupt Clear
#define TIMER_ICR_TBMCINT       11 // GPTM Timer B Match Interrupt Clear
#define TIMER_ICR_WUECINT       16 // 32/64-Bit Wide GPTM Write Update Error Interrupt Clear

#define TIMER_IMR_TATOIM        0  // GPTM Timer A Time-Out Interrupt Mask
#define TIMER_IMR_CAMIM         1  // GPTM Timer A Capture Mode Match Interrupt Mask
#define TIMER_IMR_CAEIM         2  // GPTM Timer A Capture Mode Event Interrupt Mask
#define TIMER_IMR_RTCIM         3  // GPTM RTC Interrupt Mask
#define TIMER_IMR_TAMIM         4  // GPTM Timer A Match Interrupt Mask
#define TIMER_IMR_TBTOIM        8  // GPTM Timer B Time-Out Interrupt Mask
#define TIMER_IMR_CBMIM         9  // GPTM Timer B Capture Mode Match Interrupt Mask
#define TIMER_IMR_CBEIM         10 // GPTM Timer B Capture Mode Event Interrupt Mask
#define TIMER_IMR_TBMIM         11 // GPTM Timer B Match Interrupt Mask
#define TIMER_IMR_WUEIM         16 // 32/64-Bit Wide GPTM Write Update Error Interrupt Mask

#define TIMER_MIS_TATOMIS       0  // GPTM Timer A Time-Out Masked Interrupt
#define TIMER_MIS_CAMMIS        1  // GPTM Timer A Capture Mode Match Masked Interrupt
#define TIMER_MIS_CAEMIS        2  // GPTM Timer A Capture Mode Event Masked Interrupt
#define TIMER_MIS_RTCMIS        3  // GPTM RTC Masked Interrupt
#define TIMER_MIS_TAMMIS        4  // GPTM Timer A Match Masked Interrupt
#define TIMER_MIS_TBTOMIS       8  // GPTM Timer B Time-Out Masked Interrupt
#define TIMER_MIS_CBMMIS        9  // GPTM Timer B Capture Mode Match Masked Interrupt
#define TIMER_MIS_CBEMIS        10 // GPTM Timer B Capture Mode Event Masked Interrupt
#define TIMER_MIS_TBMMIS        11 // GPTM Timer B Match Masked Interrupt
#define TIMER_MIS_WUEMIS        16 // 32/64-Bit Wide GPTM Write Update Error Masked Interrupt Status

/**
 * Driver includes
 * */
#include "tm4c123gh6pm_gpio.h"
#include "tm4c123gh6pm_spi.h"
#include "tm4c123gh6pm_timer.h"

#endif /* DRIVERS_INC_TM4C123GH6PM_H_ */

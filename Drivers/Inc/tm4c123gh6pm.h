//
// Created by Oguz Kagan YAGLIOGLU on 6 October 2022.
// www.oguzkagan.xyz
//

#ifndef DRIVERS_INC_TM4C123GH6PM_H_
#define DRIVERS_INC_TM4C123GH6PM_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * Base addresses of Flash and SRAM memories
 */
#define FLASH_BASE_ADDR            0x00000000UL
#define SRAM_BASE_ADDR             0x20000000UL

/**
 * AHBx and APBx Bus Peripheral base addresses
 * */
#define PERIPHERAL_BASE_ADDR                0x40000000UL
#define PERIPHERAL_ADD_OFFSET(OFFSET)      (PERIPHERAL_BASE_ADDR + (OFFSET))

/**
 * Base addresses of GPIOx peripherals which are hanging on APB bus
 * */
#define GPIOA_APB_BASE_ADDR                      0x40004000UL
#define GPIOB_APB_BASE_ADDR                      0x40005000UL
#define GPIOC_APB_BASE_ADDR                      0x40006000UL
#define GPIOD_APB_BASE_ADDR                      0x40007000UL
#define GPIOE_APB_BASE_ADDR                      0x40024000UL
#define GPIOF_APB_BASE_ADDR                      0x40025000UL

/**
 * Base addresses of GPIOx peripherals which are hanging on AHB bus
 * */
#define GPIOA_AHB_BASE_ADDR                      0x40058000UL
#define GPIOB_AHB_BASE_ADDR                      0x40059000UL
#define GPIOC_AHB_BASE_ADDR                      0x4005A000UL
#define GPIOD_AHB_BASE_ADDR                      0x4005B000UL
#define GPIOE_AHB_BASE_ADDR                      0x4005C000UL
#define GPIOF_AHB_BASE_ADDR                      0x4005D000UL

/**
 * Base addresses of peripherals which are hanging on APB bus
 * */
#define SSI0_BASE_ADDR                           0x40008000UL
#define SSI1_BASE_ADDR                           0x40009000UL
#define SSI2_BASE_ADDR                           0x4000A000UL
#define SSI3_BASE_ADDR                           0x4000B000UL

#define UART0_BASE_ADDR                          0x4000C000UL
#define UART1_BASE_ADDR                          0x4000D000UL
#define UART2_BASE_ADDR                          0x4000E000UL
#define UART3_BASE_ADDR                          0x4000F000UL
#define UART4_BASE_ADDR                          0x40010000UL
#define UART5_BASE_ADDR                          0x40011000UL
#define UART6_BASE_ADDR                          0x40012000UL
#define UART7_BASE_ADDR                          0x40013000UL

#define I2C0_BASE_ADDR                           0x40020000UL
#define I2C1_BASE_ADDR                           0x40021000UL
#define I2C2_BASE_ADDR                           0x40022000UL
#define I2C3_BASE_ADDR                           0x40023000UL

#define SYSCTL_BASE_ADDR                         0x400FE000UL
#define ADC0_BASE_ADDR                           0x40038000UL
#define ADC1_BASE_ADDR                           0x40039000UL

/**
 * Base addresses offset macro
 * This macro adds offset to the given base address
 * */
#define BASEADDR_ADD_OFFSET(BASE,OFFSET)         ((BASE) + (OFFSET))

#define SYSCTL_ADD_OFFSET(OFFSET)                (*((volatile uint32_t *)(BASEADDR_ADD_OFFSET(SYSCTL_BASE_ADDR, OFFSET))))

/**
 *  System Control Register Map
 * */
#define SYSCTL_DID0                              SYSCTL_ADD_OFFSET(0x000UL) // Device Identification 0
#define SYSCTL_DID1                              SYSCTL_ADD_OFFSET(0x004UL) // Device Identification 1
#define SYSCTL_PBORCTL                           SYSCTL_ADD_OFFSET(0x030UL) // Brown-Out Reset Control
#define SYSCTL_RIS                               SYSCTL_ADD_OFFSET(0x050UL) // Raw Interrupt Status
#define SYSCTL_IMC                               SYSCTL_ADD_OFFSET(0x054UL) // Raw Interrupt Status
#define SYSCTL_MISC                              SYSCTL_ADD_OFFSET(0x058UL) // Masked Interrupt Status and Clear
#define SYSCTL_RESC                              SYSCTL_ADD_OFFSET(0x05CUL) // Reset Cause
#define SYSCTL_RCC                               SYSCTL_ADD_OFFSET(0x060UL) // Run-Mode Clock Configuration
#define SYSCTL_GPIOHBCTL                         SYSCTL_ADD_OFFSET(0x06CUL) // GPIO High-Performance Bus Control
#define SYSCTL_RCC2                              SYSCTL_ADD_OFFSET(0x070UL) // Run-Mode Clock Configuration 2
#define SYSCTL_MOSCCTL                           SYSCTL_ADD_OFFSET(0x07CUL) // Main Oscillator Control
#define SYSCTL_DSLPCLKCFG                        SYSCTL_ADD_OFFSET(0x144UL) // Deep Sleep Clock Configuration
#define SYSCTL_SYSPROP                           SYSCTL_ADD_OFFSET(0x14CUL) // System Properties
#define SYSCTL_PIOSCCAL                          SYSCTL_ADD_OFFSET(0x150UL) // Precision Internal Oscillator Calibration
#define SYSCTL_PIOSCSTAT                         SYSCTL_ADD_OFFSET(0x154UL) // Precision Internal Oscillator Statistics
#define SYSCTL_PLLFREQ0                          SYSCTL_ADD_OFFSET(0x160UL) // PLL Frequency 0
#define SYSCTL_PLLFREQ1                          SYSCTL_ADD_OFFSET(0x164UL) // PLL Frequency 1
#define SYSCTL_PLLSTAT                           SYSCTL_ADD_OFFSET(0x168UL) // PLL Status
#define SYSCTL_SLPPWRCFG                         SYSCTL_ADD_OFFSET(0x188UL) // Sleep Power Configuration
#define SYSCTL_DSLPPWRCFG                        SYSCTL_ADD_OFFSET(0x18CUL) // Deep-Sleep Power Configuration
#define SYSCTL_LDOSPCTL                          SYSCTL_ADD_OFFSET(0x1B4UL) // LDO Sleep Power Control
#define SYSCTL_LDOSPCAL                          SYSCTL_ADD_OFFSET(0x1B8UL) // LDO Sleep Power Calibration
#define SYSCTL_LDODPCTL                          SYSCTL_ADD_OFFSET(0x1BCUL) // LDO Deep-Sleep Power Control
#define SYSCTL_LDODPCAL                          SYSCTL_ADD_OFFSET(0x1C0UL) // LDO Deep-Sleep Power Calibration
#define SYSCTL_SDPMST                            SYSCTL_ADD_OFFSET(0x1CCUL) // Sleep / Deep-Sleep Power Mode Status
#define SYSCTL_PPWD                              SYSCTL_ADD_OFFSET(0x300UL) // Watchdog Timer Peripheral Present
#define SYSCTL_PPTIMER                           SYSCTL_ADD_OFFSET(0x304UL) // 16/32-Bit General-Purpose Timer Peripheral Present
#define SYSCTL_PPGPIO                            SYSCTL_ADD_OFFSET(0x308UL) // General-Purpose Input/Output Peripheral Present
#define SYSCTL_PPDMA                             SYSCTL_ADD_OFFSET(0x30CUL) // Micro Direct Memory Access Peripheral Present
#define SYSCTL_PPHIB                             SYSCTL_ADD_OFFSET(0x314UL) // Hibernation Peripheral Present
#define SYSCTL_PPUART                            SYSCTL_ADD_OFFSET(0x318UL) // Universal Asynchronous Receiver/Transmitter Peripheral Present
#define SYSCTL_PPSSI                             SYSCTL_ADD_OFFSET(0x31CUL) // Synchronous Serial Interface Peripheral Present
#define SYSCTL_PPI2C                             SYSCTL_ADD_OFFSET(0x320UL) // Inter-Integrated Circuit Peripheral Present
#define SYSCTL_PPUSB                             SYSCTL_ADD_OFFSET(0x328UL) // Universal Serial Bus Peripheral Present
#define SYSCTL_PPCAN                             SYSCTL_ADD_OFFSET(0x334UL) // Controller Area Network Peripheral Present
#define SYSCTL_PPADC                             SYSCTL_ADD_OFFSET(0x338UL) // Analog-to-Digital Converter Peripheral Present
#define SYSCTL_PPACMP                            SYSCTL_ADD_OFFSET(0x33CUL) // Analog Comparator Peripheral Present
#define SYSCTL_PPPWM                             SYSCTL_ADD_OFFSET(0x340UL) // Pulse Width Modulator Peripheral Present
#define SYSCTL_PPQEI                             SYSCTL_ADD_OFFSET(0x344UL) // Quadrature Encoder Interface Peripheral Present
#define SYSCTL_PPEEPROM                          SYSCTL_ADD_OFFSET(0x358UL) // EEPROM Peripheral Present
#define SYSCTL_PPWTIMER                          SYSCTL_ADD_OFFSET(0x35CUL) // 32/64-Bit Wide General-Purpose Timer Peripheral Present
#define SYSCTL_SRWD                              SYSCTL_ADD_OFFSET(0x500UL) // Watchdog Timer Software Reset
#define SYSCTL_SRTIMER                           SYSCTL_ADD_OFFSET(0x504UL) // 16/32-Bit General-Purpose Timer Software Reset
#define SYSCTL_SRGPIO                            SYSCTL_ADD_OFFSET(0x508UL) // General-Purpose Input/Output Software Reset
#define SYSCTL_SRDMA                             SYSCTL_ADD_OFFSET(0x50CUL) // Micro Direct Memory Access Software Reset
#define SYSCTL_SRHIB                             SYSCTL_ADD_OFFSET(0x514UL) // Hibernation Software Reset
#define SYSCTL_SRUART                            SYSCTL_ADD_OFFSET(0x518UL) // Universal Asynchronous Receiver/Transmitter Software Reset
#define SYSCTL_SRSSI                             SYSCTL_ADD_OFFSET(0x51CUL) // Synchronous Serial Interface Software Reset
#define SYSCTL_SRI2C                             SYSCTL_ADD_OFFSET(0x520UL) // Inter-Integrated Circuit Software Reset
#define SYSCTL_SRUSB                             SYSCTL_ADD_OFFSET(0x528UL) // Universal Serial Bus Software Reset
#define SYSCTL_SRCAN                             SYSCTL_ADD_OFFSET(0x534UL) // Controller Area Network Software Reset
#define SYSCTL_SRADC                             SYSCTL_ADD_OFFSET(0x538UL) // Analog-to-Digital Converter Software Reset
#define SYSCTL_SRACMP                            SYSCTL_ADD_OFFSET(0x53CUL) // Analog Comparator Software Reset
#define SYSCTL_SRPWM                             SYSCTL_ADD_OFFSET(0x540UL) // Pulse Width Modulator Software Reset
#define SYSCTL_SRQEI                             SYSCTL_ADD_OFFSET(0x544UL) // Quadrature Encoder Interface Software Reset
#define SYSCTL_SREEPROM                          SYSCTL_ADD_OFFSET(0x558UL) // EEPROM Software Reset
#define SYSCTL_SRWTIMER                          SYSCTL_ADD_OFFSET(0x55CUL) // 32/64-Bit Wide General-Purpose Timer Software Reset
#define SYSCTL_RCGCWD                            SYSCTL_ADD_OFFSET(0x600UL) // Watchdog Timer Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER                         SYSCTL_ADD_OFFSET(0x604UL) // 16/32-BitGeneral-Purpose Timer Run Mode Clock Gating Control
#define SYSCTL_RCGCGPIO                          SYSCTL_ADD_OFFSET(0x608UL) // General-Purpose Input/Output Run Mode Clock Gating Control
#define SYSCTL_RCGCDMA                           SYSCTL_ADD_OFFSET(0x60CUL) // Micro Direct Memory Access Run Mode Clock Gating Control
#define SYSCTL_RCGCHIB                           SYSCTL_ADD_OFFSET(0x614UL) // Hibernation Run Mode Clock Gating Control
#define SYSCTL_RCGCUART                          SYSCTL_ADD_OFFSET(0x618UL) // Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control
#define SYSCTL_RCGCSSI                           SYSCTL_ADD_OFFSET(0x61CUL) // Synchronous Serial Interface Run Mode Clock Gating Control
#define SYSCTL_RCGCI2C                           SYSCTL_ADD_OFFSET(0x620UL) // Inter-Integrated Circuit Run Mode Clock Gating Control
#define SYSCTL_RCGCUSB                           SYSCTL_ADD_OFFSET(0x628UL) // Universal Serial Bus Run Mode Clock Gating Control
#define SYSCTL_RCGCCAN                           SYSCTL_ADD_OFFSET(0x634UL) // Controller Area Network RunMode Clock Gating Control
#define SYSCTL_RCGCADC                           SYSCTL_ADD_OFFSET(0x638UL) // Analog-to-Digital Converter Run Mode Clock Gating Control
#define SYSCTL_RCGCACMP                          SYSCTL_ADD_OFFSET(0x63CUL) // Analog Comparator Run Mode Clock Gating Control
#define SYSCTL_RCGCPWM                           SYSCTL_ADD_OFFSET(0x640UL) // Pulse Width Modulator Run Mode Clock Gating Control
#define SYSCTL_RCGCQEI                           SYSCTL_ADD_OFFSET(0x644UL) // Quadrature Encoder Interface Run Mode Clock Gating Control
#define SYSCTL_RCGCEEPROM                        SYSCTL_ADD_OFFSET(0x658UL) // EEPROM Run Mode Clock Gating Control
#define SYSCTL_RCGCWTIMER                        SYSCTL_ADD_OFFSET(0x65CUL) // 32/64-BitWide General-Purpose Timer Run Mode Clock Gating Control
#define SYSCTL_SCGCWD                            SYSCTL_ADD_OFFSET(0x700UL) // Watchdog Timer Sleep Mode Clock Gating Control
#define SYSCTL_SCGCTIMER                         SYSCTL_ADD_OFFSET(0x704UL) // 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control
#define SYSCTL_SCGCGPIO                          SYSCTL_ADD_OFFSET(0x708UL) // General-Purpose Input/Output Sleep Mode Clock Gating Control
#define SYSCTL_SCGCDMA                           SYSCTL_ADD_OFFSET(0x70CUL) // Micro Direct Memory Access Sleep Mode Clock Gating Control
#define SYSCTL_SCGCHIB                           SYSCTL_ADD_OFFSET(0x714UL) // Hibernation Sleep Mode Clock Gating Control
#define SYSCTL_SCGCUART                          SYSCTL_ADD_OFFSET(0x718UL) // Universal Asynchronous Receiver/Transmitter Sleep Mode Clock Gating Control
#define SYSCTL_SCGCSSI                           SYSCTL_ADD_OFFSET(0x71CUL) // Synchronous Serial Interface Sleep Mode Clock Gating Control
#define SYSCTL_SCGCI2C                           SYSCTL_ADD_OFFSET(0x720UL) // Inter-Integrated Circuit Sleep Mode Clock Gating Control
#define SYSCTL_SCGCUSB                           SYSCTL_ADD_OFFSET(0x728UL) // Universal Serial Bus Sleep Mode Clock Gating Control
#define SYSCTL_SCGCCAN                           SYSCTL_ADD_OFFSET(0x734UL) // Controller Area Network Sleep Mode Clock Gating Control
#define SYSCTL_SCGCADC                           SYSCTL_ADD_OFFSET(0x738UL) // Analog-to-Digital Converter Sleep Mode Clock Gating Control
#define SYSCTL_SCGCACMP                          SYSCTL_ADD_OFFSET(0x73CUL) // Analog Comparator Sleep Mode Clock Gating Control
#define SYSCTL_SCGCPWM                           SYSCTL_ADD_OFFSET(0x740UL) // PulseWidthModulator Sleep Mode Clock Gating Control
#define SYSCTL_SCGCQEI                           SYSCTL_ADD_OFFSET(0x744UL) // Quadrature Encoder Interface Sleep Mode Clock Gating Control
#define SYSCTL_SCGCEEPROM                        SYSCTL_ADD_OFFSET(0x758UL) // EEPROM Sleep Mode Clock Gating Control
#define SYSCTL_SCGCWTIMER                        SYSCTL_ADD_OFFSET(0x75CUL) // 32/64-BitWideGeneral-Purpose Timer SleepMode Clock Gating Control
#define SYSCTL_DCGCWD                            SYSCTL_ADD_OFFSET(0x800UL) // Watchdog Timer Deep-SleepMode Clock Gating Control
#define SYSCTL_DCGCTIMER                         SYSCTL_ADD_OFFSET(0x804UL) // 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCGPIO                          SYSCTL_ADD_OFFSET(0x808UL) // General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCDMA                           SYSCTL_ADD_OFFSET(0x80CUL) // Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCHIB                           SYSCTL_ADD_OFFSET(0x814UL) // Hibernation Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCUART                          SYSCTL_ADD_OFFSET(0x818UL) // Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCSSI                           SYSCTL_ADD_OFFSET(0x81CUL) // Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCI2C                           SYSCTL_ADD_OFFSET(0x820UL) // Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCUSB                           SYSCTL_ADD_OFFSET(0x828UL) // Universal Serial Bus Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCCAN                           SYSCTL_ADD_OFFSET(0x834UL) // Controller Area Network Deep-SleepMode Clock Gating Control
#define SYSCTL_DCGCADC                           SYSCTL_ADD_OFFSET(0x838UL) // Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCACMP                          SYSCTL_ADD_OFFSET(0x83CUL) // Analog Comparator Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCPWM                           SYSCTL_ADD_OFFSET(0x840UL) // Pulse Width Modulator Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCQEI                           SYSCTL_ADD_OFFSET(0x844UL) // Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCEEPROM                        SYSCTL_ADD_OFFSET(0x858UL) // EEPROM Deep-Sleep Mode Clock Gating Control
#define SYSCTL_DCGCWTIMER                        SYSCTL_ADD_OFFSET(0x85CUL) // 32/64-BitWideGeneral-Purpose Timer Deep-Sleep Mode Clock Gating Control
#define SYSCTL_PRWD                              SYSCTL_ADD_OFFSET(0xA00UL) // Watchdog Timer Peripheral Ready
#define SYSCTL_PRTIMER                           SYSCTL_ADD_OFFSET(0xA04UL) // 16/32-Bit General-Purpose Timer Peripheral Ready
#define SYSCTL_PRGPIO                            SYSCTL_ADD_OFFSET(0xA08UL) // General-Purpose Input/Output Peripheral Ready
#define SYSCTL_PRDMA                             SYSCTL_ADD_OFFSET(0xA0CUL) // Micro Direct Memory Access Peripheral Ready
#define SYSCTL_PRHIB                             SYSCTL_ADD_OFFSET(0xA14UL) // Hibernation Peripheral Ready
#define SYSCTL_PRUART                            SYSCTL_ADD_OFFSET(0xA18UL) // Universal Asynchronous Receiver/Transmitter Peripheral Ready
#define SYSCTL_PRSSI                             SYSCTL_ADD_OFFSET(0xA1CUL) // Synchronous Serial Interface Peripheral Ready
#define SYSCTL_PRI2C                             SYSCTL_ADD_OFFSET(0xA20UL) // Inter-Integrated Circuit Peripheral Ready
#define SYSCTL_PRUSB                             SYSCTL_ADD_OFFSET(0xA28UL) // Universal Serial Bus Peripheral Ready
#define SYSCTL_PRCAN                             SYSCTL_ADD_OFFSET(0xA34UL) // Controller Area Network Peripheral Ready
#define SYSCTL_PRADC                             SYSCTL_ADD_OFFSET(0xA38UL) // Analog-to-Digital Converter Peripheral Ready
#define SYSCTL_PRACMP                            SYSCTL_ADD_OFFSET(0xA3CUL) // Analog Comparator Peripheral Ready
#define SYSCTL_PRPWM                             SYSCTL_ADD_OFFSET(0xA40UL) // Pulse Width Modulator Peripheral Ready
#define SYSCTL_PRQEI                             SYSCTL_ADD_OFFSET(0xA44UL) // Quadrature Encoder Interface Peripheral Ready
#define SYSCTL_PREEPROM                          SYSCTL_ADD_OFFSET(0xA58UL) // EEPROM Peripheral Ready
#define SYSCTL_PRWTIMER                          SYSCTL_ADD_OFFSET(0xA5CUL) // 32/64-BitWide General-Purpose Timer Peripheral Ready

/**
 *  System Control Legacy Register Map
 * */
#define SYSCTL_LEGACY_DC0                        SYSCTL_ADD_OFFSET(0x008UL) // Device Capabilities 0
#define SYSCTL_LEGACY_DC1                        SYSCTL_ADD_OFFSET(0x010UL) // Device Capabilities 1
#define SYSCTL_LEGACY_DC2                        SYSCTL_ADD_OFFSET(0x014UL) // Device Capabilities 2
#define SYSCTL_LEGACY_DC3                        SYSCTL_ADD_OFFSET(0x018UL) // Device Capabilities 3
#define SYSCTL_LEGACY_DC4                        SYSCTL_ADD_OFFSET(0x01CUL) // Device Capabilities 4
#define SYSCTL_LEGACY_DC5                        SYSCTL_ADD_OFFSET(0x020UL) // Device Capabilities 5
#define SYSCTL_LEGACY_DC6                        SYSCTL_ADD_OFFSET(0x024UL) // Device Capabilities 6
#define SYSCTL_LEGACY_DC7                        SYSCTL_ADD_OFFSET(0x028UL) // Device Capabilities 7
#define SYSCTL_LEGACY_DC8                        SYSCTL_ADD_OFFSET(0x02CUL) // Device Capabilities 8
#define SYSCTL_LEGACY_SRCR0                      SYSCTL_ADD_OFFSET(0x040UL) // Software Reset Control 0
#define SYSCTL_LEGACY_SRCR1                      SYSCTL_ADD_OFFSET(0x044UL) // Software Reset Control 1
#define SYSCTL_LEGACY_SRCR2                      SYSCTL_ADD_OFFSET(0x048UL) // Software Reset Control 2
#define SYSCTL_LEGACY_RCGC0                      SYSCTL_ADD_OFFSET(0x100UL) // Run Mode Clock Gating Control Register 0
#define SYSCTL_LEGACY_RCGC1                      SYSCTL_ADD_OFFSET(0x104UL) // Run Mode Clock Gating Control Register 1
#define SYSCTL_LEGACY_RCGC2                      SYSCTL_ADD_OFFSET(0x108UL) // Run Mode Clock Gating Control Register 2
#define SYSCTL_LEGACY_SCGC0                      SYSCTL_ADD_OFFSET(0x110UL) // Sleep Mode Clock Gating Control Register 0
#define SYSCTL_LEGACY_SCGC1                      SYSCTL_ADD_OFFSET(0x114UL) // Sleep Mode Clock Gating Control Register 1
#define SYSCTL_LEGACY_SCGC2                      SYSCTL_ADD_OFFSET(0x118UL) // Sleep Mode Clock Gating Control Register 2
#define SYSCTL_LEGACY_DCGC0                      SYSCTL_ADD_OFFSET(0x120UL) // Deep Sleep Mode Clock Gating Control Register 0
#define SYSCTL_LEGACY_DCGC1                      SYSCTL_ADD_OFFSET(0x124UL) // Deep-Sleep Mode Clock Gating Control Register 1
#define SYSCTL_LEGACY_DCGC2                      SYSCTL_ADD_OFFSET(0x128UL) // Deep Sleep Mode Clock Gating Control Register 2
#define SYSCTL_LEGACY_DC9                        SYSCTL_ADD_OFFSET(0x190UL) // Device Capabilities 9
#define SYSCTL_LEGACY_NVMSTAT                    SYSCTL_ADD_OFFSET(0x1A0UL) // Non-Volatile Memory Information

#endif /* DRIVERS_INC_TM4C123GH6PM_H_ */
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

#endif /* DRIVERS_INC_TM4C123GH6PM_H_ */

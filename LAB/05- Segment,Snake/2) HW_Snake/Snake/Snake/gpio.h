/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date: Tuesday, October 27, 2020                                                                                 ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef GPIO_H
#define GPIO_H

/***********************************************************************
 * 
 * GPIO library for AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 **********************************************************************/

/**
 * @file  gpio.h
 * @brief GPIO library for AVR-GCC.
 *
 * @details
 * The library contains functions for controlling AVRs' gpio pin(s).
 *
 * @note
 * Based on AVR Libc Reference Manual. Tested on ATmega328P (Arduino Uno),
 * 16 MHz, AVR 8-bit Toolchain 3.6.2.
 */
 
/* Includes ----------------------------------------------------------*/
#include <avr/io.h>

/* Function prototypes -----------------------------------------------*/
/**
 * @brief Configure one output pin in Data Direction Register.
 * @param reg_name - Address of Data Direction Register, such as &DDRA,
 *                   &DDRB, ...
 * @param pin_num - Pin designation in the interval 0 to 7
 */
void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num);

void GPIO_config_input_nopull(volatile uint8_t *reg_name, uint8_t pin_num);

void GPIO_config_input_pullup(volatile uint8_t *reg_name, uint8_t pin_num);

void GPIO_write_low(volatile uint8_t *reg_name, uint8_t pin_num);

void GPIO_write_high(volatile uint8_t *reg_name, uint8_t pin_num); // Declaration of function (To assign it a value of 1) with parameters *reg_name and pin_num (void does not return any value)

void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num); // Declaration of function (To toggle pin) with parameters *reg_name and pin_num (void does not return any value)
/* GPIO_toggle */

uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num);

#endif
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date: Tuesday, October 20, 2020                                                                                 ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/***********************************************************************
 * 
 * GPIO library for AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include "gpio.h"

/* Function definitions ----------------------------------------------*/
void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name | (1<<pin_num); // Set bit (or)
}

/*--------------------------------------------------------------------*/
/* GPIO_config_input_nopull */
void GPIO_config_input_nopull(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name & ~(1<<pin_num);  // Data Direction Register
    *reg_name++;                    // Change pointer to Data Register
    *reg_name = *reg_name & ~(1<<pin_num);   // Data Register
}
/*--------------------------------------------------------------------*/
void GPIO_config_input_pullup(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name & ~(1<<pin_num);  // Data Direction Register
    *reg_name++;                    // Change pointer to Data Register
    *reg_name = *reg_name | (1<<pin_num);   // Data Register
}

/*--------------------------------------------------------------------*/
void GPIO_write_low(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name & ~(1<<pin_num); //Clear bit (and not)
}

/*--------------------------------------------------------------------*/
/* GPIO_write_high */
void GPIO_write_high(volatile uint8_t *reg_name, uint8_t pin_num)
{
	 *reg_name = *reg_name | (1<<pin_num); // Set bit (or)
}

/*--------------------------------------------------------------------*/
/* GPIO_toggle */

void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name ^ (1<<pin_num); // Toggle bit (xor)
}

/*--------------------------------------------------------------------*/
/* GPIO_read */
uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num)
{
	uint8_t result = 0; // Initializing result with 0
	if (*reg_name == pin_num) // If PIN is pressed
	{
		result = 1; // Value of result becomes 1 if PD0 is pressed.
	}
	return result; // Return the value stored in result (1 OR 0)
}
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date: Monday, October 12, 2020                                                                                  ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed. Use 
 * functions from GPIO library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *

 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5		 // AVR pin where green LED is connected
#define LED_RED		PC0 
#define BTN			PD0    
#define BLINK_DELAY 500
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include "gpio.h"           // GPIO library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed. Functions from user-defined GPIO
 * library is used instead of low-level logic operations.
 */
int main(void)
{
    /* GREEN LED */
    GPIO_config_output(&DDRB, LED_GREEN);
    GPIO_write_low(&PORTB, LED_GREEN);  // LED off, because active-high

    /* second LED */
    // WRITE YOUR CODE HERE

 GPIO_config_output(&DDRC, LED_RED);
 GPIO_write_low(&PORTC, LED_RED);  // LED off, because active-high

    /* push button */
    // WRITE YOUR CODE HERE
	GPIO_config_input_pullup(&DDRD, BTN);


    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);

        // WRITE YOUR CODE HERE
		if(GPIO_read(&PORTD, BTN)== 1) // This will check if the button (PIN 0 OF PORTD) has been pressed (Return value is 1 in the function)
		{
		GPIO_toggle(&PORTB, LED_GREEN); // Toggle Green LED PIN 5 of PORTB
		GPIO_toggle(&PORTC, LED_RED);   // Toggle RED LED PIN 0 of PORTC
		}
    }

    // Will never reach this
    return 0;
}
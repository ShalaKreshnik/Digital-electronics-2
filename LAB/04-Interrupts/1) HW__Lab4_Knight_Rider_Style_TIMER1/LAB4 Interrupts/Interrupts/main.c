/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date: Tuesday, October 20, 2020                                                                                 ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* Defines -----------------------------------------------------------*/
#define LED_D1  PB5
#define LED_D2  PB4
#define LED_D3  PB3
#define LED_D4  PB2
#define BTN     PD0

/* Includes ----------------------------------------------------------*/

#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC

#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC

uint8_t arr[] = {LED_D1,LED_D2,LED_D3,LED_D4};
uint8_t count =0;
uint8_t last_count = -1;
uint8_t back = 0;
/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle one LED
 * on the Multi-function shield using the internal 8- or 16-bit 
 * Timer/Counter.
 */
int main(void)
{
    /* Configuration of LED(s) */
	
	//MAKING LED_D2 AS AN OUTPUT PIN 
    GPIO_config_output(&DDRB, LED_D2);
    GPIO_write_low(&PORTB, LED_D2);
		
	// WRITE YOUR CODE HERE
	
	//MAKING LED_D1 AS AN OUTPUT PIN 
	GPIO_config_output(&DDRB, LED_D1);
	GPIO_write_low(&PORTB, LED_D1);
	
	//MAKING LED_D3 AS AN OUTPUT PIN 
	GPIO_config_output(&DDRB, LED_D3);
	GPIO_write_low(&PORTB, LED_D3);
	
	//MAKING LED_D4 AS AN OUTPUT PIN 
	GPIO_config_output(&DDRB, LED_D4);
	GPIO_write_low(&PORTB, LED_D4);
	
	//PDO as a BUTTON
	GPIO_config_input_pullup(&DDRD, BTN);
	
	
 /* Configuration of 8-bit Timer/Counter0*/
  // WRITE YOUR CODE HERE
/*
  TIM0_overflow_16ms();
  TIM0_overflow_interrupt_enable();*/
	

    /* Configuration of 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
    TIM1_overflow_1s();
    TIM1_overflow_interrupt_enable();
	

 /* Configuration of 8-bit Timer/Counter2 */
  // WRITE YOUR CODE HERE
/*
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();*/
	

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
 
 /* ISR starts when Timer/Counter1 overflows. Toggle D1 LED on 
 * Multi-function shield. */

ISR(TIMER1_OVF_vect)
{
	
	// Checking button status to control the speed of LEDs
	if(GPIO_read(&PIND,BTN)==1)
	{
		TIM1_overflow_262ms(); // If button is pressed the state will change after 262ms
	}
	else if(GPIO_read(&PIND,BTN)==0)
	{
		TIM1_overflow_1s();   // If button is not pressed the state will change after 1 second
	}
	
	
	 GPIO_toggle(&PORTB, arr[last_count]);  // TURN OFF THE PREVIOUS LED
	 GPIO_toggle(&PORTB, arr[count]);   // TURN ON THE LED (Because it was off)
	 
	 
	 
	 // Deciding the movement of LEDs (forward or backward)
	 if (count == 3) // Checking maximum size 
	 {
		 back =1;  // If it has reached maximum size then LEDs will move backwards
	 }
	 else if (count == 0)  // Checking minimum size
	 {
		 back =0; // If it has reached minimum size then LEDs will move in forward direction
	 }
	 
	 
	 
	 // Increasing or decreasing the index of array depending upon its direction
	 if (back == 0) // Direction is forward
	 {
		 last_count =count; // Index to turn off the Last LED
		count++; // Index increasing because of forward direction
	 }
	 else if (back == 1) // Direction is backwards
	 {
		 last_count=count; // Index to turn off the Last LED
		 count--; // Index decreasing because of backward direction
	 }
	 
	 
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date: Tuesday, October 27, 2020                                                                                 ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-
#include "Pinchange_interrupt.h"

#define BTN PC1
/* Variables ---------------------------------------------------------*/

uint8_t cnt0 = 0;			// Decimal counter value
uint8_t cnt1 = 0;			// TEN counter value
uint8_t cnt2 = 0;			// HUNDRED counter value
uint8_t cnt3 = 0;			// THOUSAND counter value
static uint8_t pos = 0;		// POSITION OF SSD

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Display decimal 
 * counter values on SSD (Seven-segment display) when 16-bit 
 * Timer/Counter1 overflows.
 */
int main(void)
{
    // Configure SSD signals
    SEG_init();

    // Test of SSD: display number '3' at position 0

    /* Configure 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
	TIM1_overflow_1s ();
	TIM1_overflow_interrupt_enable ();

	/* Configure 8-bit Timer/Counter0
     * Set prescaler and enable overflow interrupt */
	TIM0_overflow_4ms ();
	TIM0_overflow_interrupt_enable ();
	
	PCINT9_Enable();
	PCINT_interrupt_enable();
	
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
/**
 * ISR starts when Timer/Counter1 overflows. Increment decimal counter
 * value and display it on SSD.
 */
ISR(TIMER1_OVF_vect)
{
    // WRITE YOUR CODE HERE
	cnt0++;
	
	if (cnt0 >= 10) // Reached 10 seconds
	{
		cnt0 = 0;
		cnt1++;
	}
	if (cnt1 >= 6) // If the stopwatch has reached 60 seconds
	{
		cnt0 = 0; // Decimal value 0
		cnt1 = 0; // Ten value 0 (Ten value of seconds)
		cnt2++; // Increase in minute (60 seconds has passed)
	}
	if (cnt2 >= 10) // If 10 minute have passed
	{
		cnt0 = 0; 
		cnt1 = 0;
		cnt2 = 0; // Decimal value of minutes = 0
		cnt3++; // Ten value of minutes increased 
	}
	if (cnt3 >= 6) // IF 60 minutes have passed
	{
		// INITIALIZE THE COMPLETE WATCH STORE 00.00
		cnt0 = 0; 
		cnt1 = 0;
		cnt2 = 0;
		cnt3 = 0;
	}
}
ISR(TIMER0_OVF_vect)
{
	if (pos == 0)
	{
		SEG_update_shift_regs(cnt0, pos); 
		pos = 1; // Ready to move to second SSD
	}
	else if (pos == 1)
	{
		SEG_update_shift_regs(cnt1, pos);
		pos = 2; // Position changed to third SSD
	}
	else if (pos == 2)
	{
		SEG_update_shift_regs(cnt2, pos);
		pos = 3; // POSITION CHANGED TO 4TH SSD
	}
	else if (pos == 3)
	{
		SEG_update_shift_regs(cnt3, pos);
		pos = 0; // POSITION CHANGED TO FIRST SSD
	}
}

ISR (PCINT1_vect)
{
		SEG_clear(); // CLEAR SSD FUNCTION
}
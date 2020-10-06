/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5 // AVR pin where green LED is connected
#define LED_RED PC0
#define BTN PD0
#define BLINK_DELAY 500
#ifndef F_CPU
#define F_CPU 16000000 // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h> // Functions for busy-wait delay loops
#include <avr/io.h> // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**
* Main function where the program execution begins. Toggle two LEDs
* when a push button is pressed.
*/
int main(void)
{
	/* GREEN LED */
	// Set pin as output in Data Direction Register...
	DDRB = DDRB | (1<<LED_GREEN);
	// ...and turn LED off in Data Register
	PORTB = PORTB & ~(1<<LED_GREEN); // Turn OFF

	/*RED LED*/
	DDRC = DDRC | (1<<LED_RED); // Output
	PORTC = PORTC & ~(1<<LED_RED); // Turn ON
	/*PUSH BUTTON*/
	DDRD = DDRD & ~(1<<BTN); // Input
	PORTD = PORTD | (1<<BTN); // enable internal pull-up


	// Infinite loop
	while (1)
	{
		// Pause several milliseconds
		_delay_ms(BLINK_DELAY);


		if (bit_is_clear(PIND, BTN))
		{

			PORTB = PORTB ^ (1<<LED_GREEN);
			PORTC = PORTC ^ (1<<LED_RED);
		}

	}

	// Will never reach this
	return 0;
}
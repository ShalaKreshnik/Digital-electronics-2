/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date: Tuesday, October 06, 2020                                                                                 ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///      
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/* Defines -----------------------------------------------------------*/
#define LED_GREEN PC0 // AVR pin where green LED is connected
#define LED_RED PC1  // AVR pin where red LED is connected
#define LED_BLUE PC2 // AVR pin where blue LED is connected
#define LED_RED2 PC3 // AVR pin where red2 LED is connected
#define LED_GREEN2 PC4  // AVR pin where green2 LED is connected
#define BTN PD0
#define BLINK_DELAY 500
#define SMALL_DELAY 250
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
	int LED =0;
	int back=0;
	/* GREEN LED */
	// Set pin as output in Data Direction Register...
	//DDRB = DDRB | (1<<LED_GREEN);
	// ...and turn LED off in Data Register
	//PORTB = PORTB & ~(1<<LED_GREEN); // Turn OFF

	/*RED LED*/
	DDRC = DDRC |(1<<LED_GREEN) | (1<<LED_RED) | (1<<LED_RED2) | (1<<LED_BLUE) | (1<<LED_GREEN2); // Outputs
	PORTC = PORTC & ~(1<<LED_GREEN); // TURN OFF
	PORTC = PORTC & ~(1<<LED_RED); // Turn OFF
	PORTC = PORTC & ~(1<<LED_RED2); // Turn OFF
	PORTC = PORTC & ~(1<<LED_BLUE); // Turn OFF
	PORTC = PORTC & ~(1<<LED_GREEN2); // Turn OFF
	/*PUSH BUTTON*/
	DDRD = DDRD & ~(1<<BTN); // Input
	PORTD = PORTD | (1<<BTN); // enable internal pull-up

	// Infinite loop
	while (1)
	{
		LED =0;
		back=0;
		// Pause several milliseconds
		//_delay_ms(BLINK_DELAY);
		while (bit_is_clear(PIND,BTN))
		{
			
			PORTC = PORTC ^ (1<<LED); // TURN ON THE LED
			_delay_ms(SMALL_DELAY);
			PORTC = PORTC & ~(1<<LED); // TURN OFF THE LED
			if (LED==0) // CHECK FOR PC0
			{
				back =0; // IT HAS TO MOVE FORWARD
			}
			else if (LED == 4)
			{
				back = 1; // IT HAS TO MOVE BACKWARDS
			}
			if (back == 0)  // MOVING IN FORWARD DIRECTION
			{
				LED++;
			}
			else if (back == 1) // MOVING BACKWARDS
			{
				LED--;
			}
			
		}

	}

	// Will never reach this
	return 0;
}
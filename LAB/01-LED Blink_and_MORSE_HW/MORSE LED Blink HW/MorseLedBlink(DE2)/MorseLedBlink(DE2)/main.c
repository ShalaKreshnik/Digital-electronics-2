/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date:  Monday, September 28, 2020                                                                               ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///      
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <avr/io.h>         // AVR Basic I/O Header


/* We can just use #define F_CPU 16000000UL
But In order to avoid duplicate definition, we have defined as follows. If F_CPU is not defined previously, define here.
*/
#ifndef F_CPU
#define F_CPU 16000000
#endif
#include <util/delay.h>     // AVR Delay Header (For _delay_ms function)


#define LED_GREEN PB5
#define ONE_UNIT_DELAY 400
#define THREE_UNITS_DELAY 1200
#define SEVEN_UNITS_DELAY 2100




void dot() // Function whenever it will be called in the main it will perform these three lines of code
{
	PORTB = PORTB | (1<<LED_GREEN); // Turn ON LED PB5
	_delay_ms(ONE_UNIT_DELAY); // length of dot is one unit
	PORTB = PORTB & ~(1<<LED_GREEN); // Turn OFF LED PB5
}

void dash()
{
	PORTB = PORTB | (1<<LED_GREEN); // Turn ON LED PB5
	_delay_ms(THREE_UNITS_DELAY); // length of dash is three units
	PORTB = PORTB & ~(1<<LED_GREEN); // Turn OFF LED PB5
}

void space()
{
	PORTB = PORTB & ~(1<<LED_GREEN); // Turn OFF LED PB5 (SPACE BETWEEN TWO WORDS)
	_delay_ms(SEVEN_UNITS_DELAY); // Length between words is SEVEN units
}



int main(void)
{
	// DDRB = DDRB or 0010 0000
	DDRB = DDRB | (1<<LED_GREEN); // Making pin5 of PORTB as an output pin

	// PORTB = PORTB and 1101 1111
	PORTB = PORTB & ~(1<<LED_GREEN); // Initially storing 0 on PB5



	// Infinite loop
	while (1)
	{

		/*^^^^^^(DE2 = -.. . ..---)^^^^^^^*/
		

		/*1. Letter "D" -> (-..)*/
		dash();
		_delay_ms(ONE_UNIT_DELAY); // length between different parts is one unit
		dot();
		_delay_ms(ONE_UNIT_DELAY); // length between different parts is one unit
		dot();
		
		// SHORT GAP (between letters)
		_delay_ms(THREE_UNITS_DELAY);
		/* Alphabet “D” completed */

		
		/*2. Letter "E" -> (.)*/
		dot();
		
		// SHORT GAP (between letters)
		_delay_ms(THREE_UNITS_DELAY);
		/* Alphabet “E” completed */

		
		/*2. Number "2" -> (..---)*/
		dot();
		_delay_ms(ONE_UNIT_DELAY); // length between different parts is one unit
		dot();
		_delay_ms(ONE_UNIT_DELAY); // length between different parts is one unit
		dash();
		_delay_ms(ONE_UNIT_DELAY); // length between different parts is one unit
		dash();
		_delay_ms(ONE_UNIT_DELAY); // length between different parts is one unit
		dash();	// NUMBER 2 completed (..---)

		// SHORT GAP (between letters)
		_delay_ms(THREE_UNITS_DELAY);
		/* NUMBER “2” completed */
		
		
		// MEDIUM GAP (between words)
		space();
		
		
	}

	return 0;
}



/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function

#define COL1 1
#define COL2 11

uint8_t customChar[8*8] = {
	// address 0
	0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
	// address 1
	0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000,
	// address 2
	0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000,
	// address 3
	0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100,
	// address 4
	0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110,
	// address 5
	0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111,
	//6
	0b11110, 0b11000, 0b10100, 0b10010,	0b00001, 0b00000, 0b00000, 0b00000,
	
	//7
	0b01111, 0b00011, 0b00101, 0b01001, 0b10000, 0b00000, 0b00000, 0b00000
};



/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON_CURSOR);

    // Put string(s) at LCD display
    lcd_gotoxy(COL1, 0); lcd_puts("00:00.0");  // Stopwatch
	lcd_gotoxy(COL2, 0); lcd_putc('0');		   // Seconds^2
	lcd_gotoxy(COL1, 1); lcd_putc('b');		   // Progress bar
	lcd_gotoxy(COL2, 1); lcd_putc('c');		   // Rotating text

	// Custom character generator
	lcd_command(1 << LCD_CGRAM);
	for (uint8_t i = 0; i < 8*8; i++)
	{
		lcd_data(customChar[i]); // Storing all new characters to memory line by line
	}
	
	// Set pointer to beginning of DDRAM memory
	lcd_command(1 << LCD_CGRAM);
	lcd_gotoxy(COL1, 1);
	lcd_putc(0);
	// spaeter hinzugefuegt
	
	lcd_gotoxy(0,0);
	lcd_putc(6);
 	lcd_gotoxy(8,0); 
 	lcd_putc(7);
	
	// ende

	// Configure 8-bit Timer/Counter0 for Stopwatch
	// Set prescaler and enable overflow interrupt every 16 ms
	
	
	
	TIM0_overflow_16ms();
 	TIM0_overflow_interrupt_enable();  



    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set prescaler and enable overflow interrupt every 16 ms
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();

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
 * ISR starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16 ms = 100 ms).
 */
ISR(TIMER2_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
	static uint8_t tens = 0; // Tenth of a second
	static uint8_t secs = 0; // Seconds
	static uint8_t mins = 0; // Minutes
	char lcd_string[2] = "00"; // Strings for converting numbers by itoa
	

    number_of_overflows++;
    if (number_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        number_of_overflows = 0;

		tens++; // Update tenth of a second
		if(tens >= 10)
		{
			tens = 0;
			// Updating secs
			secs++;
			if (secs >31) // Square is of 4 digits (i.e. 32*32 = 1024)
			{
				lcd_gotoxy(COL2, 0); lcd_putc(((secs*secs)/1000)+48);
				lcd_gotoxy(COL2+1, 0); lcd_putc((((secs*secs)/100)%10)+48);
				lcd_gotoxy(COL2+2, 0); lcd_putc(((((secs*secs)/10)%10)%10)+48);
				lcd_gotoxy(COL2+3, 0); lcd_putc(((((secs*secs)%100)%10)%10)+48);
			}
			
			else if(secs>9) // Square is of 3 digits (i.e. 13*13 = 169)
			{
				lcd_gotoxy(COL2, 0); lcd_putc(((secs*secs)/100)+48);
				lcd_gotoxy(COL2+1, 0); lcd_putc((((secs*secs)/10)%10)+48);
				lcd_gotoxy(COL2+2, 0); lcd_putc((((secs*secs)%10)%10)+48);
			}
			
			else if(secs>3) // Square is of 2 digits (i.e. 4*4 = 16)
			{
				lcd_gotoxy(COL2, 0); lcd_putc(((secs*secs)/10)+48);
				lcd_gotoxy(COL2+1, 0); lcd_putc(((secs*secs)%10)+48);
			} 
			
			else
			{
			lcd_gotoxy(COL2, 0); lcd_putc(((secs*secs)+48));
			}
			
			if(secs >= 60)
			{	
				secs = 0;
				// Updating minutes
				mins++;
				if(mins >= 60)
				{
					mins = 0;
				}
				
				// Display minutes
				lcd_gotoxy(COL1, 0);
				if(mins < 10)
				{
					lcd_putc('0');
				}
				itoa(mins, lcd_string, 10);
				lcd_puts(lcd_string);
				
				//Clearing seconds^2
				lcd_gotoxy(COL2, 0);
				lcd_puts("    ");
				lcd_gotoxy(COL2, 0);
				lcd_putc(((secs*secs)+48));
			}
			// Display seconds
			lcd_gotoxy(COL1+3,0);
			if (secs < 10)
			{
				lcd_putc('0');
			}
			itoa(secs, lcd_string, 10);
			lcd_puts(lcd_string);
		}
		
		// Display hundredth of a second
		lcd_gotoxy(COL1+6, 0);
		
		// Convert cnt0 in decimal to string
		itoa(tens, lcd_string, 10);
		lcd_puts(lcd_string);

    }
}

ISR (TIMER0_OVF_vect)

{
	static uint8_t symbol = 0;
	static uint8_t position = 0;
	
	lcd_gotoxy(COL1 + position, 1);
	lcd_putc(symbol);

	symbol++;
	if (symbol >= 6)
	{
		symbol = 0;
		// Moving to next position
		position++;
		if (position >= 10)
		{
			position = 0;
			// Clearing progress bar
			lcd_gotoxy(COL1, 1);
			lcd_puts("          ");
		}
	}
}
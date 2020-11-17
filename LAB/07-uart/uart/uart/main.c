

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library
#ifndef F_CPU
#define F_CPU   16000000
#endif
/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Use Timer/Counter1
 * and start ADC conversion four times per second. Send value to LCD
 * and UART.
 */

uint8_t parity = 0;

// Hex values of every single bit  for example 0b0000000000000010 is defined as(0x0002) and 0b1000000000000000 is defined as (0x8000)
uint16_t arr[16] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
	0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000
};
void parity_display(int a)
{
		
		uint8_t parity_count = 0;
		
			for (uint16_t i =0; i<16; i++)
			{
				if ((arr[i]&a)!=0)
				{
					parity_count++; // counting number of 1s in a value
				}
				
			}
			if(parity_count == 0) // If the count is 0 (No 1 bit)
			{
					parity = 0;
			}
			else if(parity_count%2 == 0) // If sum of 1's is an even number
			{
				parity = 1;
			}
			
			else if(parity_count%2 == 1) // If the sum of 1's is an odd number
			{
				parity = 0;
			}
		
			lcd_gotoxy(15, 1); // Parity display location
			lcd_putc(parity+48); // Converting to character
};

int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(1, 0);  
    lcd_puts ("value:");
    lcd_gotoxy(3, 1);
    lcd_puts ("key:");
	lcd_gotoxy(8, 1);
	lcd_puts ("none");
	

    // Configure ADC to convert PC0[A0] analog value
    // Set ADC reference to AVcc
    ADMUX |= (1 << REFS0);
    // Set input channel to ADC0
    ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0)); // 0000: ADC0 
    // Enable ADC module
    ADCSRA |= (1<< ADEN);
    // Enable conversion complete interrupt
    ADCSRA |= (1<<ADEN);
    // Set clock prescaler to 128
    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE);
	
	//ADCSRA |= (1<<ADEN) | (1<<ADATE)  | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Enable interrupt and set the overflow prescaler to 262 ms
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Initialize UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

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
 * ISR starts when Timer/Counter1 overflows. Use single conversion mode
 * and start conversion four times per second.
 */
ISR(TIMER1_OVF_vect)
{
    // Start ADC conversion
    ADCSRA |= (1<< ADSC);
}

/* -------------------------------------------------------------------*/
/**
 * ISR starts when ADC completes the conversion. Display value on LCD
 * and send it to UART.
 */
ISR(ADC_vect)
{
    // WRITE YOUR CODE HERE
    uint16_t value = 0;
    char lcd_string[4] = "0000"; 

	// Displaying parity bit of value
	parity_display(value);
	
	// Sending data to UART1
	uint8_t c;
	c = uart_getc();
	if(c != '\0')
	{
		if (c == '1')
		{
		uart_putc(c);
		}
	}

	
    value = ADC;                 // Copy ADC result to 16-bit variable
	
    itoa(value, lcd_string, 10); //Convert to string in decimal
    lcd_gotoxy(8, 0);
    lcd_puts("    ");   
    lcd_gotoxy(8, 0);
    lcd_puts(lcd_string);

    if (value < 700)
    {
		uart_puts("Button was pressed: ");
		uart_puts(lcd_string);    
		uart_puts("\r\n");
    }

    itoa(value, lcd_string, 16); //Convert to string in hexa
    lcd_gotoxy(13, 0);
    lcd_puts("    ");
    lcd_gotoxy(13, 0);
    lcd_puts(lcd_string);
	
	
	lcd_gotoxy(8, 1);
	if (value == 0) // If the right button was pressed
	{
		lcd_puts("      ");
		lcd_gotoxy(8, 1);
		lcd_puts("Right");
		parity_display(value);
	}
	if (value == 101) // If the right button was pressed
	{
		lcd_puts("      ");
		lcd_gotoxy(8, 1);
		lcd_puts("Up");
		parity_display(value);
	}
	if (value == 245) // If the right button was pressed
	{
		lcd_puts("      ");
		lcd_gotoxy(8, 1);
		lcd_puts("Down");
		parity_display(value);
	}
	if (value == 402) // If the right button was pressed
	{
		lcd_puts("      ");
		lcd_gotoxy(8, 1);
		lcd_puts("Left");
		parity_display(value);
	}
	if (value == 650) // If the right button was pressed
	{
		lcd_puts("      ");
		lcd_gotoxy(8, 1);
		lcd_puts("Select");
		parity_display(value);
	}
	
	// Displaying parity data on UART
	if (value < 700)
	{
		uart_puts("Parity bit of value is: ");
		uart_putc(parity+48);
		uart_puts("\r\n");
	}
	
}


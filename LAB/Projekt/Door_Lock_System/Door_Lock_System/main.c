/*
 * Door_lock_system.c
 *
 * Created: 13.12.2020 20:28:51
 * Author : Nadir Osman Al-Wattar & Kreshnik Shala
 */ 

/* Includes ----------------------------------------------------------*/

#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library
#include <avr/interrupt.h>
#include "keypad.h"
#include "gpio.h"

#ifndef F_CPU
#define F_CPU  16000000
#endif

/*----------------------------------Variables used in program-------------------------------------------*/

int correct = 0; // Correct Password or not
int correct_1 = 0;
int correct_2 = 0;
int count_1 = 0; 
int count = 0; // Count for total number of keys for password
char pass[4]; // Entered values will be stored here
int password[4] = {2,3,4,5}; // Password for Mr. Thomas
int password_1[4] = {4,3,4,5}; // Password for Mr. Al-Wattar
int password_2[4] = {1,2,3,4}; // Password for Mr. Shala
int position = 5; // Initial position on display
int time_check = 0;
int countdown = 9; // Countdown for closing door
int countdown_1 = 9; // Countdown for entering the password
int countdown_2 = 3; // For freezing the display
int countdown_flag = 0; // Door is opened

/*------------------------------------------------Main---------------------------------------------*/
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(1, 0);  
    lcd_puts ("Enter Password");
    lcd_gotoxy(position, 1);
	
	// Setting output pins and initializing to low value
	GPIO_config_output(&DDRC, 3);
	GPIO_write_low(&PORTC,3);
	GPIO_config_output(&DDRC, 5);
	GPIO_write_low(&PORTC,5);
	
	GPIO_config_output(&DDRD, 0);
	GPIO_config_output(&DDRD, 1);
	GPIO_config_output(&DDRD, 2);	



	// Timer 0 interrupt enabling
	TIM0_overflow_4ms();
	TIM0_overflow_interrupt_enable();
	
    // Enable interrupt and set the overflow prescaler to 1 s
    
	TIM1_overflow_1s();
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
 * ISR starts when Timer/Counter1 overflows
 */

ISR (TIMER0_OVF_vect)
{
	keypad();
	if (time_check > 100)
	{
		char lcd_string[4] = "0000";
		
		if (count < 4 && countdown_2 == 3) // If all 4 keys are not pressed (length of password)
		{
			itoa(pass[count], lcd_string, 10); //Convert to string in decimal
			if (count_1 != 0)
			{
				lcd_gotoxy(position, 1); // Position for entering password
				if (pass[count] != '*' && pass[count] != '#') // if (* or # is not pressed)
				{
					lcd_putc('*'); // For password's privacy
					
					// Sending status to uart
					uart_puts("Key pressed was: ");
					uart_puts(lcd_string);
					uart_puts("\r\n");
				}
				
				else if (pass[count] == '*' || pass[count] == '#') // If (* or # was pressed)
				{
					lcd_putc('*');
			
					// Sending status to Uart
					uart_puts("Key pressed was: ");
					uart_putc(pass[count]);
					uart_puts("\r\n");
				
				}
				count_1 = 0; // Resetting the value for the next key to be entered
				position++; // Next position for key
				count++;
			}
			
		}
		
		else if (count == 4 && countdown_2 == 3 && countdown == 9) // Limit for pass code
		{
			
			Check_password(); // Checking password for person 1
			Check_password_1(); // Checking password for person 2
			Check_password_2(); // Checking password for person 3
			
			if (correct == 0 && correct_1 == 0 && correct_2 == 0) // The password entered was wrong
			{
				// Sending status to UART
				uart_puts("You entered a wrong password");
				uart_puts("\r\n");
				uart_puts("Please try again");
				uart_puts("\r\n");
				
				// NO entry
				entry_denied(); // Function defined in keypad.h
			}
			
			else if (correct == 1|| correct_1 == 1 || correct_2 == 1) // The password entered was correct by any of the 3 persons.
			{
				// Door will be opened for 9 seconds
				entry_accepted();
			}
		}
		time_check = 0;
	}
	else
	{
		time_check++;
	}
}

ISR(TIMER1_OVF_vect) // 1 second time delay
{
    
    if (countdown == -1 && countdown_2 == 3) // Countdown has been completed
	{
        uart_puts("Door is now closed"); // displaying at UART
        uart_puts("\r\n");
        uart_puts("Enter password again");
        uart_puts("\r\n");
    			
        GPIO_write_low(&PORTC, 5); // Closing relay
    			
        // Clearing the LCD
        lcd_gotoxy(0,0);
        lcd_puts("                ");
        lcd_gotoxy(0,1);
        lcd_puts("                ");
    			
        // Displaying door closed message
        lcd_gotoxy(1, 0);
        lcd_puts("Door Closed");
        countdown_2 = 2;
	}
    		
	if (countdown_flag == 1 && countdown_2 == 3) // Correct password has been entered
	{
		if (countdown == 9) // This will display it only one time on uart
		{
			uart_puts("You entered a Correct password");
			uart_puts("\r\n");
			uart_puts("Door is open for 9 seconds!");
			uart_puts("\r\n");
		}
		
		lcd_gotoxy(15,1); // Position for countdown (bottom right)
		lcd_putc(countdown+48); // Converting decimal value to character value (ASCII)
		countdown--; // decrease in a second
	}

	if (count < 4 && countdown_2 == 3) // Keys pressed are less than the total length of password
	{
		
		if (countdown_1 == -1) // Countdown completed
		{
			reset(); // Reset the display
		}

        if (count > 0) // First key for password has been pressed
        {
            lcd_gotoxy(15,1); // Bottom right for seconds
            lcd_putc(countdown_1+48); // Displaying its character value
            countdown_1--; //  Decrease in a second
        }
	}
	if (countdown_2 < 3) // freezes the screen (acting as a delay)
	{
		if (countdown_2 == -1)
		{
			countdown_2 = 3;
			reset(); // Reset the display
			return;
		}
		else
		{
		countdown_2--;
		}
	}
}
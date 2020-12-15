#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"          // Peter Fleury's UART library
#include "keypad.h"
#include "gpio.h"
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU  16000000
#endif

char keys[4][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,9},
		{'*',0,'#'}};

void keypad()
{
	for (uint8_t j =0; j <3; j++)
	{
		GPIO_write_low(&PORTD, 0);
		GPIO_write_low(&PORTD, 1);
		GPIO_write_low(&PORTD, 2);
		
		GPIO_write_high(&PORTD, j);
		
		for (uint8_t k = 0; k < 4; k++)
		{
			if(GPIO_read(&PINB, k+2) == 1)
			{
				pass[count] = keys[k][j];
				count_1 = 1;
				while(GPIO_read(&PINB, k+2) == 1)
				{
					// do nothing and wait for key to be released 
				}
			}
		}
	}
	
}
void Check_password()
{
	for(int i = 0; i<4; i++)
	{
		if(pass[i] == password[i]) // Comparing entered password with the password stored in array(password[])
		{
			correct = 1;
		}
		else if(pass[i] != password[i]) // If any value is different
		{
			correct = 0;
			break;
		}
	}	
	
}

void Check_password_1()
{
	for(int i = 0; i<4; i++)
	{
		if(pass[i] == password_1[i]) // Comparing entered password with the password stored in array(password[])
		{
			correct_1 = 1;
		}
		else if(pass[i] != password_1[i]) // If any value is different
		{
			correct_1 = 0;
			break;
		}
	}
	
}

void Check_password_2()
{
	for(int i = 0; i<4; i++)
	{
		if(pass[i] == password_2[i]) // Comparing entered password with the password stored in array(password[])
		{
			correct_2 = 1;
		}
		else if(pass[i] != password_2[i]) // If any value is different
		{
			correct_2 = 0;
			break;
		}
	}
	
}

void reset()
{
	count = 0;
	count_1 = 0;
	position = 5;
	countdown = 9;
	countdown_1 = 9;
	time_check = 0;
    countdown_flag = 0; // Countdown completed.
	lcd_gotoxy(0,0);
	lcd_puts("                    ");
	lcd_gotoxy(0,1);
	lcd_puts("                    ");
	lcd_gotoxy(1, 0);
	lcd_puts ("Enter Password");
	lcd_gotoxy(15, 1);
	lcd_puts("  ");
	lcd_gotoxy(position, 1);
	lcd_puts("     ");
	GPIO_write_low(&PORTC,3);
}



void entry_denied()
{
	lcd_gotoxy(1, 0);
	lcd_puts("              ");
	lcd_gotoxy(5, 1);
	lcd_puts("         ");
	lcd_gotoxy(1, 0);
	lcd_puts("Wrong Password");
	GPIO_write_high(&PORTC,3);
	countdown_2 = 0;
	lcd_gotoxy(15,1);
	lcd_puts(" ");
	
}


void entry_accepted()
{
	lcd_gotoxy(1, 0);
	lcd_puts("              ");
	lcd_gotoxy(5, 1);
	lcd_puts("      ");
	lcd_gotoxy(0, 0);
	lcd_puts("Welcome");
	
	lcd_gotoxy(0, 1);
	if (correct == 1)
	{
		lcd_puts("Mr. Thomas");
	}
	else if(correct_1 == 1)
	{
		lcd_puts("Mr. Al-Wattar");
	}
	else if(correct_2 == 1)
	{
		lcd_puts("Mr. Shala");
	}
	
	GPIO_write_high(&PORTC,5);
	countdown_flag = 1; 
	
}

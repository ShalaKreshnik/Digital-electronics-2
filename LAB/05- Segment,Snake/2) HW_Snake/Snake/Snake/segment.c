/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date: Tuesday, October 27, 2020                                                                                 ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Includes ----------------------------------------------------------*/
#define F_CPU 16000000
#include <util/delay.h>
#include "gpio.h"
#include "segment.h"

/* Variables ---------------------------------------------------------*/
// Active-low digits 0 to 9
uint8_t clear_flag = 0;
uint8_t segment_value[] = {
	// abcdefgDP
	0b01111111,      // Only a
	0b10111111,      // Only b
	0b11011111,      // Only c
	0b11101111,      // Only d
	0b11101111,      // Only d
	0b11110111,      // Only e
	0b11111011,      // Only f
	0b01111111,      // Only a
	};

// Active-high position 0 to 3
uint8_t segment_position[] = {
	// p3p2p1p0....
	0b00010000,     // Position 0
	0b00100000,     // Position 1
	0b0100000,		// Position 2
	0b10000000};	// Position 3


/* Function definitions ----------------------------------------------*/
void SEG_init(void)
{
    /* Configuration of SSD signals */
    GPIO_config_output(&DDRD, SEGMENT_LATCH);
    GPIO_config_output(&DDRD, SEGMENT_CLK);
    GPIO_config_output(&DDRB, SEGMENT_DATA);
}

/*--------------------------------------------------------------------*/
void SEG_update_shift_regs(uint8_t segments, uint8_t position)
{
    uint8_t bit_number;

	 segments = segment_value[segments];	 // 0, 1, ..., 9
	 position = segment_position[position];  // 0, 1, 2, 3
    // Pull LATCH, CLK, and DATA low
	GPIO_write_low(&PORTD, SEGMENT_LATCH);  // LATCH
	GPIO_write_low(&PORTD, SEGMENT_CLK);    // CLK
	GPIO_write_low(&PORTB, SEGMENT_DATA);   // DATA
    // Wait 1 us
	_delay_us(1);

    // Loop through the 1st byte (segments)
    // a b c d e f g DP (active low values)
    for (bit_number = 0; bit_number < 8; bit_number++)
    {           
		// Output DATA value (bit 0of "segments")		
		if ((segments % 2) == 0)  // LSB is 0 
			GPIO_write_low(&PORTB, SEGMENT_DATA);
		else
			GPIO_write_high (&PORTB, SEGMENT_DATA);
		// Wait 1 us
		_delay_us(1);		
        // Pull CLK high
		GPIO_write_high(&PORTD, SEGMENT_CLK); 
        // Wait 1 us
		_delay_us(1);
        // Pull CLK low
		GPIO_write_low(&PORTD, SEGMENT_CLK); 
        // Shift "segments"
        segments = segments >> 1;
    }

    // Loop through the 2nd byte (position)
    // p3 p2 p1 p0 . . . . (active high values)
	
    for (bit_number = 0; bit_number < 8; bit_number++)
    {
        // Output DATA value (bit 0 of "position")
       if ((position % 2) == 0)  // LSB is 0
			 GPIO_write_low(&PORTB, SEGMENT_DATA);
       else
			 GPIO_write_high(&PORTB, SEGMENT_DATA);
       // Wait 1 us
       _delay_us(1);
       // Pull CLK high
       GPIO_write_high(&PORTD, SEGMENT_CLK);
       // Wait 1 us
       _delay_us(1);
       // Pull CLK low
       GPIO_write_low(&PORTD, SEGMENT_CLK);
       // Shift "position"
       position = position >> 1;
    }
	
    // Pull LATCH high
	GPIO_write_high(&PORTD, SEGMENT_LATCH);  // LATCH
    // Wait 1 us
	_delay_us(1);
}

/*--------------------------------------------------------------------*/
/* SEG_clear */

void SEG_clear(void)
{
	//clear_flag = 1;
}

/*--------------------------------------------------------------------*/
/* SEG_clk_2us */
void SEG_clk_2us()
{
	/*1 instruction performed in(by a clock of 800kHz freq) = 1/800k = 1.25us;
	we need 2us delay. No of instructions = 2u/1.25u = 1.6
	TCNT0 value = 256 - 1.6 = 254.4 (Subtracting from 256 because 8 bit timer can perform maximum 256 instructions)*/
	
	TCNT0 = 254;
	TCCR0A = 0; //Normal mode
	TCCR0B = 2; //prescaler of 1
	
	while((TIFR0&(1<<OCF0A))==0)
	{ } //wait until OCF0A is set
	
	TCCR0B = 0; //stop timer0
	TIFR0 = 1<<OCF0A;//clear flag

}
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date: Tuesday, October 27, 2020                                                                                 ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>

/* Defines -----------------------------------------------------------*/
/*
 * @brief Defines prescaler CPU frequency values for Timer/Counter0.
 * @note  F_CPU = 16 MHz
 */
#define  PCINT9_Enable()	PCMSK1 |= (1<<PCINT9);
/**
 * @brief Defines interrupt enable/disable modes for Timer/Counter0.
 */
#define PCINT_interrupt_enable()    PCICR |= (1<<PCIE1);
#define PCINT_interrupt_disable()   PCICR &= ~(1<<PCIE1);


#endif /* INTERRUPT_H_ */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                ///
VUT FEKT                                                 Name and Surname: Kreshnik Shala                       ///
[BPA-DE2] Digital Electronics 2                                        Person ID: 226108                        ///
Date: Tuesday, October 20, 2020                                                                                 ///
GitHub: https://github.com/ShalaKreshnik                                                                        ///
                                                                                                                ///
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TIMER_H
#define TIMER_H


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>

/* Defines -----------------------------------------------------------*/
/*
 * @brief Defines prescaler CPU frequency values for Timer/Counter0.
 * @note  F_CPU = 16 MHz
 */
#define  TIM0_stop()			 TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
#define TIM0_overflow_16us()     TCCR0B &= ~((1<<CS02) | (1<<CS01)); TCCR0B |= (1<<CS00);
#define TIM0_overflow_128us()    TCCR0B &= ~((1<<CS02) | (1<<CS00)); TCCR0B |= (1<<CS01);
#define TIM0_overflow_1ms()      TCCR0B &= ~(1<<CS02); TCCR0B |= (1<<CS01) | (1<<CS00);
#define TIM0_overflow_4ms()      TCCR0B &= ~((1<<CS01) | (1<<CS00)); TCCR0B |= (1<<CS02);
#define TIM0_overflow_16ms()     TCCR0B &= ~(1<<CS01); TCCR0B |= (1<<CS02) | (1<<CS00);


/**
 * @brief Defines interrupt enable/disable modes for Timer/Counter0.
 */
#define TIM0_overflow_interrupt_enable()    TIMSK0 |= (1<<TOIE0);
#define TIM0_overflow_interrupt_disable()   TIMSK0 &= ~(1<<TOIE0);


/**
 * @brief Defines prescaler CPU frequency values for Timer/Counter1.
 * @note  F_CPU = 16 MHz
 */
#define TIM1_stop()             TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
#define TIM1_overflow_4ms()     TCCR1B &= ~((1<<CS12) | (1<<CS11)); TCCR1B |= (1<<CS10);
#define TIM1_overflow_33ms()    TCCR1B &= ~((1<<CS12) | (1<<CS10)); TCCR1B |= (1<<CS11);
#define TIM1_overflow_262ms()   TCCR1B &= ~(1<<CS12); TCCR1B |= (1<<CS11) | (1<<CS10);
#define TIM1_overflow_1s()      TCCR1B &= ~((1<<CS11) | (1<<CS10)); TCCR1B |= (1<<CS12);
#define TIM1_overflow_4s()      TCCR1B &= ~(1<<CS11); TCCR1B |= (1<<CS12) | (1<<CS10);

/*
 * @brief Defines interrupt enable/disable modes for Timer/Counter1.
 */
#define TIM1_overflow_interrupt_enable()    TIMSK1 |= (1<<TOIE1);
#define TIM1_overflow_interrupt_disable()   TIMSK1 &= ~(1<<TOIE1);



/*
 * @brief Defines prescaler CPU frequency values for Timer/Counter2.
 * @note  F_CPU = 16 MHz
 */
#define  TIM2_stop()			 TCCR2B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
#define TIM2_overflow_16us()     TCCR2B &= ~((1<<CS02) | (1<<CS01)); TCCR2B |= (1<<CS00);
#define TIM2_overflow_128us()    TCCR2B &= ~((1<<CS02) | (1<<CS00)); TCCR2B |= (1<<CS01);
#define TIM2_overflow_512us()    TCCR2B &= ~(1<<CS02); TCCR2B |= (1<<CS01) | (1<<CS00);
#define TIM2_overflow_1ms()      TCCR2B &= ~((1<<CS01) | (1<<CS00)); TCCR2B |= (1<<CS02);
#define TIM2_overflow_2ms()      TCCR2B &= ~(1<<CS01); TCCR2B |= (1<<CS02) | (1<<CS00);
#define TIM2_overflow_4ms()      TCCR2B &= ~(1<<CS20); TCCR2B |= (1<<CS22) | (1<<CS21);
#define TIM2_overflow_16ms()     TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);


/**
 * @brief Defines interrupt enable/disable modes for Timer/Counter2.
 */
#define TIM2_overflow_interrupt_enable()    TIMSK2 |= (1<<TOIE2);
#define TIM2_overflow_interrupt_disable()   TIMSK2 &= ~(1<<TOIE2);



#endif
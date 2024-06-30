/**************************************************/
/*Desc   : timer driver							  */
/*Author : Youssef Taha Moawad		              */
/*Date   : 16 sep 2023                            */
/*Version: 1.0V                                   */
/**************************************************/
#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_macros.h"
#include "STD_Types.h"


void timer0_initializeCTC(void);


void timer0_stop(void);


void timer_initializefastpwm(void);


void change_dutycycle(float64 duty);


#endif /* TIMER_DRIVER_H_ */

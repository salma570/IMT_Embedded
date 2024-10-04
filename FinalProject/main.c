/*
 * main.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_int.h"
#include "LCD_int.h"
#include "GIE_int.h"
#include "EXTI_int.h"
#include "KPD_int.h"
#include "RTC_int.h"
#include "stopwatch_int.h"

#define TimeClock  1
#define Alarm  	   2
#define StopWatch  3
#define CountDown  4

void StopWatch_EXTI(void);

void main(void)
{
	//inits
	TWI_voidMasterInit();
	RTC_voidInit();
	LCD_init();
	EXTI_SetTriggerMode();
	EXTI0_CallBackFunc(StopWatch_EXTI);
	EXTI_Enable(EXTI0); //stopwatch
	GIE_Enable();
	KPD_init();

	//current node
	RTC_val * current;
	u8 mode = 0;

	//print welcome messages and start program

	//choose mode
	mode = KPD_GetKey();
	switch (mode)
	{
		case TimeClock:

			break;
		case Alarm:

			break;
		case StopWatch:
			DIO_SetPinDirection(PORTD,PIN_2,Input); //push button connected to exti0
			DIO_SetPinValue(PORTD,PIN_2,HIGH); //pullup

			break;
		case CountDown:

			break;
		default:
			break;
	}
}


void StopWatch_EXTI(void)
{
	STOPWATCH_voidToggle();
	if(STOPWATCH_u8CheckFlag()==1)
	{
		STOPWATCH_voidRun();
	}
	else
	{
		STOPWATCH_voidStop();
	}
}

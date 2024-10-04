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
#include "TWI_Interface.h"
#include "EXTI_int.h"
#include "KPD_int.h"
#include "RTC_int.h"
#include "stopwatch_int.h"
#include "RTOS/FreeRTOS.h"
#include "RTOS/task.h"
#include "util/delay.h"

#define TimeClock  1
#define Alarm  	   2
#define StopWatch  3
#define CountDown  4

void StopWatch_Task(void *ptr);
void StopWatch_EXTI(void);
void StopWatch_Reset_EXTI(void);
xTaskHandle StopWatchHandle=NULL;

void main(void)
{
	//inits
	TWI_voidMasterInit(1);
//	RTC_voidInit();
	LCD_init();
	KPD_init();

	LCD_WriteString("Welcome To Program");
	_delay_ms(2000);
//	//current node
//	RTC_val * current;
	u8 mode = 0;

	//print welcome messages and start program

	//choose mode
	//mode = KPD_GetKey();
	mode=3;
	switch (mode)
	{
	case TimeClock:

		break;
	case Alarm:

		break;
	case StopWatch:
		//pause and resume stopwatch
		LCD_WriteCommand(lcd_Clear);
		DIO_SetPinDirection(PORTD,PIN_2,Input); //push button on INT0
		DIO_SetPinValue(PORTD,PIN_2,HIGH); //pull up
		EXTI_SetTriggerMode();
		EXTI0_CallBackFunc(StopWatch_EXTI);
		EXTI_Enable(EXTI0);

		//reset stopwatch
		DIO_SetPinDirection(PORTD,PIN_3,Input); //push button on INT0
		DIO_SetPinValue(PORTD,PIN_3,HIGH); //pull up
		EXTI1_CallBackFunc(StopWatch_Reset_EXTI);
		EXTI_Enable(EXTI1);
		GIE_Enable();

		xTaskCreate(StopWatch_Task,NULL,configMINIMAL_STACK_SIZE,NULL,0,&StopWatchHandle);
		vTaskStartScheduler();
		break;
	case CountDown:

		break;
	default:
		break;
	}


	while(1){}
}


//void StopWatch_Task(void *ptr)
//{
//	STOPWATCH_voidToggle();
//	while(1)
//	{
//		if(STOPWATCH_u8CheckFlag()==1)
//		{
//			STOPWATCH_voidRun();
//		}
//		else
//		{
//			STOPWATCH_voidStop();
//		}
//		vTaskDelay(1000);
//	}
//}

void StopWatch_Task(void *ptr)
{
	while(1)
	{
		STOPWATCH_voidRun();
		STOPWATCH_voidDisplay();
		vTaskDelay(1000);
	}
}

static u8 flag = 0;

void StopWatch_EXTI(void)
{
	if (flag == 0)
	{
		vTaskSuspend(StopWatchHandle);
		flag=1;
	}
	else
	{
		vTaskResume(StopWatchHandle);
		flag=0;
	}
}

void StopWatch_Reset_EXTI(void)
{
	STOPWATCH_voidSReset();
	flag = 1 ;
	vTaskSuspend(StopWatchHandle);
	//stop task
	//vTaskDelete(StopWatchHandle);
}

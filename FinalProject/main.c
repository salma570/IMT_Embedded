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

static u8 flag = 0;
void StopWatch_Task(void *ptr);
void Countdown_Task(void *ptr);
void StopWatch_EXTI(void);
xTaskHandle StopWatchHandle=NULL;

void main(void)
{
	//inits
	TWI_voidMasterInit(1);
	RTC_voidInit();
	LCD_init();
	KPD_init();

	//print welcome messages and start program
	LCD_WriteString("Welcome To Program");
	_delay_ms(1000);
	//	//current node
	//	RTC_val * current;
	u8 mode = 0;


	//choose mode
	//mode = KPD_GetKey();
	mode=4;
	switch (mode)
	{
	case TimeClock:

		break;
	case Alarm:

		break;
	case StopWatch:
		//pause and resume stop watch
		LCD_WriteCommand(lcd_Clear);
		DIO_SetPinDirection(3,PIN_2,Input); //push button on INT0
		DIO_SetPinValue(3,PIN_2,HIGH); //pull up
		EXTI_SetTriggerMode();
		EXTI0_CallBackFunc(StopWatch_EXTI);
		EXTI_Enable(EXTI0);
		GIE_Enable();
		xTaskCreate(StopWatch_Task,NULL,configMINIMAL_STACK_SIZE,NULL,0,&StopWatchHandle);
		break;
	case CountDown:
		LCD_WriteCommand(lcd_Clear);
		xTaskCreate(Countdown_Task,NULL,configMINIMAL_STACK_SIZE,NULL,0,NULL);
		//interrupt for going to input (reset button)
		//ok button inside the fn
		break;
	default:
		break;
	}

	vTaskStartScheduler();

	while(1)
	{

	}
}

void StopWatch_Task(void *ptr)
{
	while(1)
	{
		STOPWATCH_voidRun();
		STOPWATCH_voidDisplay();
		vTaskDelay(500);
	}
}

void StopWatch_EXTI(void)
{
	if (flag == 0)
	{
		vTaskSuspend(StopWatchHandle);
		STOPWATCH_voidSReset();
		flag=1;
	}
	else
	{
		vTaskResume(StopWatchHandle);
		flag=0;
	}
	return;
}

void Countdown_Task(void *ptr)
{
	static u8 CDstate = 0;
	DIO_SetPinDirection(1,4,Output);
	while(1)
	{
		CDstate = CountDown_u8Run();
		STOPWATCH_voidDisplay();
		if(CDstate==1)
		{
			DIO_SetPinValue(1,4,HIGH);
		}
		vTaskDelay(500);
	}
}

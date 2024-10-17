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
#include "Alarm_int.h"
#include "RTOS/FreeRTOS.h"
#include "RTOS/task.h"
#include "util/delay.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

#define TimeClock  1
#define Alarm  	   2
#define StopWatch  3
#define CountDown  4

static u8 flag = 0;
void StopWatch_Task(void *ptr);
void Countdown_Task(void *ptr);
void StopWatch_EXTI(void);
void Countdown_Task(void *ptr);
void CD_IncrementTemp_EXTI(void);
void CD_IncrementOK_EXTI(void);
void Alarm_IncrementTemp_EXTI(void);
void Alarm_IncrementOK_EXTI(void);
void increment_mode_exti(void);
void end_prg_exti(void);
xTaskHandle StopWatchHandle=NULL;
static u8 mode;

void main(void)
{
	//inits
	LCD_init();
	KPD_init();
	TWI_voidMasterInit(1);
	LCD_WriteString("Init RTC");
	_delay_ms(1000);
	RTC_voidInit();
	EXTI_SetTriggerMode();
	GIE_Enable();

	//but1: used for increments
	DIO_SetPinDirection(3,PIN_2,Input);
	DIO_SetPinValue(3,PIN_2,HIGH); //pull up
	//but2: to submit
	DIO_SetPinDirection(3,PIN_3,Input);
	DIO_SetPinValue(3,PIN_3,HIGH); //pull up
	//but3: end program
	DIO_SetPinDirection(1,PIN_2,Input);
	DIO_SetPinValue(1,PIN_2,HIGH); //pull up
	EXTI2_CallBackFunc(end_prg_exti);
	EXTI_Enable(EXTI2);

	//print welcome messages and start program
	LCD_WriteCommand(lcd_Clear);
	_delay_ms(1000);
	LCD_WriteString("Welcome To Program");
	_delay_ms(1000);
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Adjust Date & Time");
	_delay_ms(1000);
	LCD_WriteCommand(lcd_Clear);
	///WRITE RTC ADJUST LOGIC HERE
	LCD_WriteString("Choose Mode: ");
	_delay_ms(1000);
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("1.RTC 2.Alarm");
	LCD_GoTo(line_2,0);
	LCD_WriteString("3.StopWatch 4.CD");
	_delay_ms(2000);
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Choose, press ok");
	LCD_GoTo(line_2,0);
	LCD_WriteString("Choice: ");

	EXTI0_CallBackFunc(increment_mode_exti); //increment
	EXTI_Enable(EXTI0);
	static u8 pressed_ok = 1;
	mode = 1;
	while(pressed_ok==1)
	{
		LCD_GoTo(line_2,11);
		LCD_WriteChar((mode+48));
		pressed_ok = DIO_GetPinValue(3,PIN_3);
		_delay_ms(50);
	}
	EXTI_Disable(EXTI0);

	//	//current node
	//	RTC_val * current;
	//	mode=4;
	switch (mode)
	{
	case TimeClock:

		break;
	case Alarm:
		LCD_WriteCommand(lcd_Clear);
		//prompt user to enter value to Set Alarm
		//using 2 buttons
		//but1: increments and rolls back
		DIO_SetPinDirection(3,PIN_2,Input); //push button on INT0
		DIO_SetPinValue(3,PIN_2,HIGH); //pull up
		EXTI0_CallBackFunc(Alarm_IncrementTemp_EXTI); //increment
		//but2: to submit
		DIO_SetPinDirection(3,PIN_3,Input); //push button on INT1
		DIO_SetPinValue(3,PIN_3,HIGH); //pull up
		EXTI1_CallBackFunc(Alarm_IncrementOK_EXTI); //okays
		//enable interrupts
		EXTI_Enable(EXTI0);
		EXTI_Enable(EXTI1);
		Alarm_InitTemp();
		while(Alarm_u8GetCurrentButtonCount()<=4) //no action until user fully enters his data
		{
			Alarm_voidTempDisplay();
		}
		Alarm_AdjustTime();
		while(1)
		{
			if(RTC_voidGetHour()==Alarm_GetHr() && RTC_voidGetMin()==Alarm_GetMin())
			{
				DIO_SetPinDirection(1,4,Output);
				DIO_SetPinValue(1,4,HIGH);
			}
		}
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
		vTaskStartScheduler();
		break;
	case CountDown:
		LCD_WriteCommand(lcd_Clear);
		//prompt user to enter value to countdown from
		//using 2 buttons
		//but1: increments and rolls back
		DIO_SetPinDirection(3,PIN_2,Input); //push button on INT0
		DIO_SetPinValue(3,PIN_2,HIGH); //pull up
		EXTI0_CallBackFunc(CD_IncrementTemp_EXTI); //increment
		//but2: to submit
		DIO_SetPinDirection(3,PIN_3,Input); //push button on INT1
		DIO_SetPinValue(3,PIN_3,HIGH); //pull up
		EXTI1_CallBackFunc(CD_IncrementOK_EXTI); //okays
		//enable interrupts
		EXTI_SetTriggerMode();
		EXTI_Enable(EXTI0);
		EXTI_Enable(EXTI1);
		GIE_Enable();
		//validation happens, if validation fails -> reset
		init_alltemp();
		while(GetCurrentButton_count()<=6) //no action until user fully enters his data
		{
			CountDown_voidTempDisplay();
		}
		CountDownu8_SetCurrent_Values();
		//now the last okay is pressed and task should start
		xTaskCreate(Countdown_Task,NULL,configMINIMAL_STACK_SIZE,NULL,0,NULL);
		vTaskStartScheduler();
		//interrupt for going to input (reset button)
		break;
	default:
		break;
	}

	while(1)
	{

	}
}
void end_prg_exti(void)
{
	DIO_SetPinValue(1,4,LOW);
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Program Ended");
	while(1){}
}
void increment_mode_exti(void)
{
	mode ++;
	if(mode>4)
		mode = 1;
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
		CountDown_voidDisplay();
		if(CDstate==1)
		{
			DIO_SetPinValue(1,4,HIGH);
		}
		vTaskDelay(500);
	}
}
void CD_IncrementTemp_EXTI(void)
{
	CountDown_u8IncrementCurrentTemp();
}
void CD_IncrementOK_EXTI(void)
{
	CountDown_u8IncrementOK();
}
void Alarm_IncrementTemp_EXTI(void)
{
	Alarm_u8IncrementCurrentTemp();
}
void Alarm_IncrementOK_EXTI(void)
{
	Alarm_voidIncrementOK();
}

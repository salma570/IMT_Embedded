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
//#include "RTC_int.h"
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
void Countdown_Task(void *ptr);
void CD_IncrementTemp_EXTI(void);
void CD_IncrementOK_EXTI(void);
xTaskHandle StopWatchHandle=NULL;

void main(void)
{
	//inits
	TWI_voidMasterInit(1);
//	RTC_voidInit();
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

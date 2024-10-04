/*
 * stopwatch_prg.c
 *
 *  Created on: Oct 3, 2024
 *      Author: hp
 */

#include "Std_Types.h"
#include "Bit_math.h"
#include "LCD_int.h"
#include "stopwatch_int.h"


static u8 u8CurrentSec = 0;
static u8 u8CurrentMin = 0;
static u8 u8CurrentHr = 0;
static u8 u8StopwatchFlag = 0;


void STOPWATCH_voidToggle()
{
	u8StopwatchFlag ^= (1<<0);
	LCD_GoTo(line_1,0);
	LCD_WriteString("Stopwatch:");
}

void STOPWATCH_voidRun(void){
	u8CurrentSec ++;
	if (u8CurrentSec  == 60)
	{
		u8CurrentSec = 0;
		u8CurrentMin ++;
	}
	if (u8CurrentMin   == 60)
	{
		u8CurrentMin = 0;
		u8CurrentHr ++;
	}
	if (u8CurrentHr    ==24)
	{
		u8CurrentHr= 0;
	}
}

void STOPWATCH_voidDisplay(void)  // akenou bydisplay bs no increment
{
	LCD_GoTo(line_1,0);
	LCD_WriteString("Stopwatch:");
	/*Hours*/
	LCD_GoTo(line_2,0);
	LCD_WriteChar((u8CurrentHr/10)+48);
	LCD_WriteChar((u8CurrentHr%10)+48);
	LCD_WriteChar(':');
	/*Minutes*/
	LCD_GoTo(line_2,5);
	LCD_WriteChar((u8CurrentMin/10)+48);
	LCD_WriteChar((u8CurrentMin%10)+48);
	LCD_WriteChar(':');
	/*Seconds*/
	LCD_GoTo(line_2,10);
	LCD_WriteChar((u8CurrentSec/10)+48);
	LCD_WriteChar((u8CurrentSec%10)+48);
}

void STOPWATCH_voidSReset(void)
{
	u8CurrentSec = 0;
	u8CurrentMin = 0;
	u8CurrentHr = 0;
	STOPWATCH_voidDisplay();
}

u8 STOPWATCH_u8CheckFlag(void)
{
	return u8StopwatchFlag;
}

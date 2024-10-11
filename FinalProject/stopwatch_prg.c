/*
 * stopwatch_prg.c
 *
 *  Created on: Oct 3, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "Bit_math.h"
#include "LCD_int.h"
#include "stopwatch_int.h"

static u8 u8CurrentSec= 0;
static u8 u8CurrentMin= 0;
static u8 u8CurrentHr= 0;


static u8 u8tempHr_1 = 0;
static u8 u8tempHr_2 = 0;

static u8 u8tempmin_1 = 0;
static u8 u8tempmin_2 = 0;

static u8 u8tempsec_1 = 0;
static u8 u8tempsec_2 = 0;


static u8 count_button_pressed =0; //OK button
// static u8 increment_Current_digit =0;

//khalihom array ahsan 3l4an we need pointers mi4 hynfa3 n3mel pass by value
static u8 *ALLtemp[6];

//initialise array values
void init_alltemp(void) {
	ALLtemp[0]=&u8tempHr_1;
	ALLtemp[1]=&u8tempHr_2;
	ALLtemp[2]=&u8tempmin_1;
	ALLtemp[3]=&u8tempmin_2;
	ALLtemp[4]=&u8tempsec_1;
	ALLtemp[5]=&u8tempsec_2;
}

//when increment button is pressed 
void CountDown_u8IncrementCurrentTemp(void)
{
	// Ensure count_button_pressed is within valid range
	if (count_button_pressed < 0 || count_button_pressed >= 6) {
		// Handle out of bounds case (optional)
		return; // or some error handling
	}
	// Reset if the current number is 9
	if(count_button_pressed%2 ==0) //tens
	{
		if (*ALLtemp[count_button_pressed] >= 5) //maybe remove =
		{
			*ALLtemp[count_button_pressed] = 0;
		}
		else
		{ // Otherwise increment it
			(*ALLtemp[count_button_pressed])++;
		}
	}
	else //units
	{
		if (*ALLtemp[count_button_pressed] >= 9) //maybe remove =
		{
			*ALLtemp[count_button_pressed] = 0;
		}
		else
		{ // Otherwise increment it
			(*ALLtemp[count_button_pressed])++;
		}
	}
}

void CountDown_u8IncrementOK(void)
{
	count_button_pressed++;
}

u8 GetCurrentButton_count(void)
{
	return count_button_pressed;
}

void CountDownu8_SetCurrent_Values(void)
{
	u8CurrentHr = u8tempHr_1*10+ u8tempHr_2;
	u8CurrentMin = u8tempmin_1*10+u8tempmin_2;
	u8CurrentSec = u8tempsec_1*10+u8tempsec_2;
}

u8 CountDown_u8Run(void)
{
	if (u8CurrentHr <= 0 && u8CurrentMin <=0 && u8CurrentSec <=0)
	{
		return 1;
	}
	u8CurrentSec --;
	if (u8CurrentSec  == 0 && u8CurrentMin>0)
	{
		u8CurrentSec = 59;
		u8CurrentMin --;
	}
	if (u8CurrentMin  == 0 && u8CurrentHr>0)
	{
		u8CurrentMin = 59;
		u8CurrentHr --;
	}
	return 0;
}

void CountDown_voidDisplay(void)
{
	LCD_GoTo(line_1,0);
	LCD_WriteString("Countdown:");
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
	return;
}

void CountDown_voidTempDisplay(void)
{
	LCD_GoTo(line_1,0);
	LCD_WriteString("Countdown:");
	/*Hours*/
	LCD_GoTo(line_2,0);
	LCD_WriteChar(u8tempHr_1+48);
	LCD_WriteChar(u8tempHr_2+48);
	LCD_WriteChar(':');
	/*Minutes*/
	LCD_GoTo(line_2,5);
	LCD_WriteChar(u8tempmin_1+48);
	LCD_WriteChar(u8tempmin_2+48);
	LCD_WriteChar(':');
	/*Seconds*/
	LCD_GoTo(line_2,10);
	LCD_WriteChar(u8tempsec_1+48);
	LCD_WriteChar(u8tempsec_2+48);
	return;
}

void STOPWATCH_voidRun(void)
{
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
	return;
}

void STOPWATCH_voidDisplay(void)
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
	return;
}

void STOPWATCH_voidSReset(void)
{
	u8CurrentSec = 0;
	u8CurrentMin = 0;
	u8CurrentHr = 0;
	return;
}


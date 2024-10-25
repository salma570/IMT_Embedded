/*
 * Alarm_prg.c
 *
 *  Created on: Oct 13, 2024
 *      Author: HP
 */

#include "STD_Types.h"
#include "Alarm_int.h"
#include "LCD_int.h"

static u8 HrTens=0;
static u8 HrUnits=0;

static u8 MinTens=0;
static u8 MinUnits=0;

static u8 count_button_pressed =0; //OK button

static u8 u8tempHr_1 = 0;
static u8 u8tempHr_2 = 0;

static u8 u8tempmin_1 = 0;
static u8 u8tempmin_2 = 0;


static u8 *ALLtemp[4];

//initialise array values
void Alarm_InitTemp(void) {
	ALLtemp[0]=&u8tempHr_1;
	ALLtemp[1]=&u8tempHr_2;
	ALLtemp[2]=&u8tempmin_1;
	ALLtemp[3]=&u8tempmin_2;
}

void Alarm_AdjustTime(void)
{
	HrTens=u8tempHr_1;
	HrUnits=u8tempHr_2;
	MinTens=u8tempmin_1;
	MinUnits=u8tempmin_2;
}

u8 Alarm_GetHr(void)
{
	return ((HrTens*10)+HrUnits);
}

u8 Alarm_GetMin(void)
{
	return ((MinTens*10)+MinUnits);
}

void Alarm_voidIncrementOK(void)
{
	count_button_pressed++;
}

u8 Alarm_u8GetCurrentButtonCount(void)
{
	return count_button_pressed;
}

void Alarm_u8IncrementCurrentTemp(void)
{
	// Ensure count_button_pressed is within valid range
	if (count_button_pressed < 0 || count_button_pressed >= 4) {
		// Handle out of bounds case (optional)
		return; // or some error handling
	}
	// Reset if the current number is 9
	if(count_button_pressed ==0) //Hrstens
	{
		if (*ALLtemp[count_button_pressed] >= 2) //maybe remove =
		{
			*ALLtemp[count_button_pressed] = 0;
		}
		else
		{ // Otherwise increment it
			(*ALLtemp[count_button_pressed])++;
		}
	}
	else if(count_button_pressed ==1) //HrsUnits
	{
		if (*ALLtemp[count_button_pressed] >= 4 && *ALLtemp[0] == 2)
		{
			*ALLtemp[count_button_pressed] = 0;
		}
		else if (*ALLtemp[count_button_pressed] >= 9)
		{ // Otherwise increment it
			*ALLtemp[count_button_pressed] = 0;
		}
		else
		{
			(*ALLtemp[count_button_pressed])++;
		}
	}
	else if (count_button_pressed == 2) //MinTens
	{
		if (*ALLtemp[count_button_pressed] >= 5)
		{
			*ALLtemp[count_button_pressed] = 0;
		}
		else
		{ // Otherwise increment it
			(*ALLtemp[count_button_pressed])++;
		}
	}
	else if (count_button_pressed == 3) //MinUnits
	{
		if (*ALLtemp[count_button_pressed] >= 9)
		{
			*ALLtemp[count_button_pressed] = 0;
		}
		else
		{ // Otherwise increment it
			(*ALLtemp[count_button_pressed])++;
		}
	}
	else
	{
		return;
	}
}

void Alarm_DisplaySet(void)
{
	LCD_GoTo(line_2,0);
	LCD_WriteString("Alarm:");
	/*Hours*/
	LCD_GoTo(line_2,7);
	LCD_WriteChar(HrTens+48);
	LCD_WriteChar(HrUnits+48);
	LCD_WriteChar(':');
	/*Minutes*/
	LCD_GoTo(line_2,12);
	LCD_WriteChar(MinTens+48);
	LCD_WriteChar(MinUnits+48);
	return;
}

void Alarm_voidTempDisplay(void)
{
	LCD_GoTo(line_2,0);
	LCD_WriteString("Alarm:");
	/*Hours*/
	LCD_GoTo(line_2,7);
	LCD_WriteChar(u8tempHr_1+48);
	LCD_WriteChar(u8tempHr_2+48);
	LCD_WriteChar(':');
	/*Minutes*/
	LCD_GoTo(line_2,12);
	LCD_WriteChar(u8tempmin_1+48);
	LCD_WriteChar(u8tempmin_2+48);
	return;
}

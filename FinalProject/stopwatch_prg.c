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

static u8 u8CurrentSec= 0;
static u8 u8CurrentMin= 0;
static u8 u8CurrentHr= 0;


static u8 u8tempHr_1 = 0;
static u8 u8tempHr_2 = 0;

static u8 u8tempmin_1 = 0;
static u8 u8tempmin_2 = 0;

static u8 u8tempmsec_1 = 0;
static u8 u8tempmsec_2 = 0;


//khalihom array ahsan 3l4an we need pointers mi4 hynfa3 n3mel pass by value
int ALLtemp[5];

//initialise array values
&ALLtemp[0]=u8tempHr_1;
&ALLtemp[1]=u8tempHr_2;
&ALLtemp[2]=u8tempmin_1;
&ALLtemp[3]=u8tempmin_2;
&ALLtemp[4]=u8tempsec_1;
&ALLtemp[5]=u8tempsec_2;

static u8 count_button_pressed =0; //OK button
static u8 increment_Current_digit =0;

void CountDownu8_SetTemp(void)
{
	int x = GetCurrentButton_count(); //ok button 
	if(x>6){
	    CountDownu8_validateTemp(); 
		count_button_pressed =0;
	}else{
		count_button_pressed++;
	}
}
//when increment button is pressed 
void ValueSet(void)
{
	//reset if the current number is 9
	if(ALLtemp[count_button_pressed]>=9){
		ALLtemp[count_button_pressed] =0;
	}else{//otherwise increment it
		ALLtemp[count_button_pressed]++;
	}
}

void CountDownu8_validateTemp(void)
{
	u8 flag_valid = 1;
	
	//IF CONDITONS TO VALIDATE
	if((u8tempHr_1+ u8tempHr_2 >24) || (u8tempmin_1+u8tempmin_2>59) || (u8tempmsec_1+u8tempmsec_2>59))
		flag_valid = 0;
	if(flag_valid ==1)
	{
		CountDownu8_SetCurrent_Values();
		CountDown_u8Run();
	}else{
		STOPWATCH_voidSReset();
	}

	//reset temp values
	u8tempHr_1 =0;
	u8tempHr_2 =0;
	
	u8tempmin_1 =0;
	u8tempmin_2 =0;
	
	u8tempsec_1 =0;
	u8tempsec_2 =0;
}
void CountDownu8_SetCurrent_Values(void)
{
	u8CurrentHr = u8tempHr_1+ u8tempHr_2;
	u8CurrentMin = u8tempmin_1+u8tempmin_2;
	u8CurrentSec = u8tempmsec_1+u8tempmsec_2;
}

u8 GetCurrentButton_count(void)
{
	return count_button_pressed;
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


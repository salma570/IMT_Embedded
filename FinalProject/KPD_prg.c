/*
 * KPD_prg.c
 *
 *  Created on: Aug 14, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_int.h"
#include "KPD_cfg.h"
#include "KPD_int.h"
#include "util/delay.h"

u8 arr[4][4]=
{
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11},
		{12,13,14,15}
};

void KPD_init(void)
{
	u8 i=0;
	//4 pins input pull up rows
	for(i=Row_Start;i<=Row_End;i++)
	{
		DIO_SetPinDirection(KPD_Port,i,Input);
		DIO_SetPinValue(KPD_Port,i,HIGH);
	}
	//4 pins output high columns
	for(i=Col_Start;i<=Col_End;i++)
	{
		DIO_SetPinDirection(KPD_Port,i,Output);
		DIO_SetPinValue(KPD_Port,i,HIGH);
	}
}

u8 KPD_GetKey(void)
{
	u8 value=0;
	u8 key = 16; //if no button pressed
	u8 flag =0;
	//nested for loops -> micro notes
	for(u8 i=0; i<NoCols;i++)
	{
		DIO_SetPinValue(KPD_Port, Col_Start+i, LOW);
		for(u8 j=0; j<NoRows;j++)
		{
			value = DIO_GetPinValue(KPD_Port,Row_Start+j);
			_delay_ms(20);
			if(value==0)
			{
				key = arr[j][i];
				flag = 1;
				break;
			}
		}
		DIO_SetPinValue(KPD_Port, Col_Start+i, HIGH);
		if(flag==1)
		{
			break;
		}
	}
	return key;
}

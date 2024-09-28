/*
 * main.c
 *
 *  Created on: Aug 9, 2024
 *      Author: hp
 */
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_int.h"
#include "OS_int.h"

void led1(void)
{
	static u8 i=0;

	if(i==0)
	{
		DIO_SetPinValue(PORTA,PIN_0,HIGH);
		i=1;
	}
	else
	{
		DIO_SetPinValue(PORTA,PIN_0,LOW);
		i=0;
	}
}

void main(void)
{
	u8 x = 1;
}

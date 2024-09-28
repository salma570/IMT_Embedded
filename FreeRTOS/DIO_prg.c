/*
 * DIO_prg.c
 *
 *  Created on: Aug 9, 2024
 *      Author: hp
 */
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_prv.h"
#include "DIO_int.h"

void DIO_SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
	switch(Copy_u8Port)
	{
	case PORTA:
		if(Copy_u8Direction==Input)
			CLR_BIT(DDRA,Copy_u8Pin);
		else if(Copy_u8Direction==Output)
			SET_BIT(DDRA,Copy_u8Pin);
		break;
	case PORTB:
		if(Copy_u8Direction==Input)
			CLR_BIT(DDRB,Copy_u8Pin);
		else if(Copy_u8Direction==Output)
			SET_BIT(DDRB,Copy_u8Pin);
		break;
	case PORTC:
		if(Copy_u8Direction==Input)
			CLR_BIT(DDRC,Copy_u8Pin);
		else if(Copy_u8Direction==Output)
			SET_BIT(DDRC,Copy_u8Pin);
		break;
	case PORTD:
		if(Copy_u8Direction==Input)
			CLR_BIT(DDRD,Copy_u8Pin);
		else if(Copy_u8Direction==Output)
			SET_BIT(DDRD,Copy_u8Pin);
		break;
	default:
		break;
	}
}


void DIO_SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	switch(Copy_u8Port)
	{
	case PORTA:
		if(Copy_u8Value==LOW)
			CLR_BIT(PORTA_Register,Copy_u8Pin);
		else if(Copy_u8Value==HIGH)
			SET_BIT(PORTA_Register,Copy_u8Pin);
		break;
	case PORTB:
		if(Copy_u8Value==LOW)
			CLR_BIT(PORTB_Register,Copy_u8Pin);
		else if(Copy_u8Value==HIGH)
			SET_BIT(PORTB_Register,Copy_u8Pin);
		break;
	case PORTC:
		if(Copy_u8Value==LOW)
			CLR_BIT(PORTC_Register,Copy_u8Pin);
		else if(Copy_u8Value==HIGH)
			SET_BIT(PORTC_Register,Copy_u8Pin);
		break;
	case PORTD:
		if(Copy_u8Value==LOW)
			CLR_BIT(PORTD_Register,Copy_u8Pin);
		else if(Copy_u8Value==HIGH)
			SET_BIT(PORTD_Register,Copy_u8Pin);
		break;
	default:
		break;
	}
}

u8 DIO_GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	u8 Copy_u8LocalVariable;
	switch(Copy_u8Port)
	{
	case PORTA:
		Copy_u8LocalVariable = GET_BIT(PINA, Copy_u8Pin);
		break;
	case PORTB:
		Copy_u8LocalVariable = GET_BIT(PINB, Copy_u8Pin);
		break;
	case PORTC:
		Copy_u8LocalVariable = GET_BIT(PINC, Copy_u8Pin);
		break;
	case PORTD:
		Copy_u8LocalVariable = GET_BIT(PIND, Copy_u8Pin);
		break;
	}
	return Copy_u8LocalVariable;
}


void DIO_GetPinValueByPtr(u8 Copy_u8Port, u8 Copy_u8Pin, u8 * Copy_u8ptr)
{
	switch(Copy_u8Port)
	{
	case PORTA:
		*Copy_u8ptr = GET_BIT(PINA, Copy_u8Pin);
		break;
	case PORTB:
		*Copy_u8ptr = GET_BIT(PINB, Copy_u8Pin);
		break;
	case PORTC:
		*Copy_u8ptr = GET_BIT(PINC, Copy_u8Pin);
		break;
	case PORTD:
		*Copy_u8ptr = GET_BIT(PIND, Copy_u8Pin);
		break;
	default:
		break;
	}
}

void DIO_SetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction)
{
	switch(Copy_u8Port)
	{
	case PORTA:
		DDRA = Copy_u8Direction;
		break;
	case PORTB:
		DDRB = Copy_u8Direction;
		break;
	case PORTC:
		DDRC = Copy_u8Direction;
		break;
	case PORTD:
		DDRD = Copy_u8Direction;
		break;
	default:
		break;
	}
}
void DIO_SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	switch(Copy_u8Port)
	{
	case PORTA:
		PORTA_Register = Copy_u8Value;
		break;
	case PORTB:
		PORTB_Register = Copy_u8Value;
		break;
	case PORTC:
		PORTC_Register = Copy_u8Value;
		break;
	case PORTD:
		PORTD_Register = Copy_u8Value;
		break;
	default:
		break;
	}
}

/*
 * Timer_prg.c
 *
 *  Created on: Aug 29, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "Timer_int.h"
#include "Timer_prv.h"

void (*TIM0_OVF_GlobalPtr)(void)=0;
void (*TIM1_CTC_GlobalPtr)(void)=0;

void TIM0_OFinit(void)
{
	//Normal Mode
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);

	//prescalar = 8
	CLR_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
}

void TIM0_CTCinit(void)
{
	//CTC Mode
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

	//prescalar = 8
	CLR_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);

	//OC0 (B3) --> toggle
	SET_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
}


void TIM0_PWMinit(void)
{
	//FAST PWM Mode
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

	//prescalar = 8
	CLR_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);

	//OC0 (B3) --> toggle
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}

void TIM0_OFInterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}

void TIM0_OFSetRegValue(u8 Copy_u8PreLoadValue)
{
	TCNT0=Copy_u8PreLoadValue;
}

void TIM0_CTCSetRegValue(u8 Copy_u8CompareMatchValue)
{
	OCR0 = Copy_u8CompareMatchValue;
}

void TIM0_OFCallBack(void(*ptr)(void))
{
	TIM0_OVF_GlobalPtr=ptr;
}

void __vector_11 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_11 (void)
{
	TIM0_OVF_GlobalPtr();
}


/*****************************************************************/

void TIM1_init(void)
{
	//OC1A --> clear on compare
	SET_BIT(TTCR1A,COM1A1);
	CLR_BIT(TTCR1A,COM1A0);

	//Mode 14 selection
	CLR_BIT(TTCR1A,WGM10);
	SET_BIT(TTCR1A,WGM11);
	SET_BIT(TTCR1B,WGM12);
	SET_BIT(TTCR1B,WGM13);

	//prescaler = 8
	CLR_BIT(TTCR1B,CS10);
	SET_BIT(TTCR1B,CS11);
	CLR_BIT(TTCR1B,CS12);
}


// Initialize Timer1 in Fast PWM mode for servo control
void TIM1_initServoPWM(void)
{
    // Set Fast PWM mode with ICR1 as TOP (Mode 14)
    CLR_BIT(TTCR1A, WGM10);
    SET_BIT(TTCR1A, WGM11);
    SET_BIT(TTCR1B, WGM12);
    SET_BIT(TTCR1B, WGM13);

    // Set non-inverting mode on OC1A (Clear OC1A on Compare Match)
    SET_BIT(TTCR1A, COM1A1);
    CLR_BIT(TTCR1A, COM1A0);

    // Set prescaler to 64
    SET_BIT(TTCR1B, CS10);
    SET_BIT(TTCR1B, CS11);
    CLR_BIT(TTCR1B, CS12);

    // Set TOP value for 20 ms period (50 Hz PWM frequency)
    ICR1 = 4999;

    // Set initial Compare Match value for 1 ms pulse width (0 degrees)
    OCR1A = 249;
}

void TIM1_initNormal(void)
{

	//Mode 0 selection
	CLR_BIT(TTCR1A,WGM10);
	CLR_BIT(TTCR1A,WGM11);
	CLR_BIT(TTCR1B,WGM12);
	CLR_BIT(TTCR1B,WGM13);

	//prescaler = 8
	CLR_BIT(TTCR1B,CS10);
	SET_BIT(TTCR1B,CS11);
	CLR_BIT(TTCR1B,CS12);
}

void TIM1_initCTC(void)
{
	//Mode 4 selection
	CLR_BIT(TTCR1A,WGM10);
	CLR_BIT(TTCR1A,WGM11);
	SET_BIT(TTCR1B,WGM12);
	CLR_BIT(TTCR1B,WGM13);

	//prescaler = 8
	CLR_BIT(TTCR1B,CS10);
	SET_BIT(TTCR1B,CS11);
	CLR_BIT(TTCR1B,CS12);
}

void TIM1_CTCInterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}

void TIM1_CTC_A_SetRegValue(u16 Copy_u8CompareValue)
{
	OCR1A = Copy_u8CompareValue;
}

u16 TIM1_CTC_A_GetRegValue(void)
{
	return OCR1A;
}

void TIM1_ICRSetRegValue(u16 Copy_u8TopValue)
{
	ICR1 = Copy_u8TopValue;
}

void TIM1_TCNTSetRegValue(u16 Copy_u8TValue)
{
	TCNT1=Copy_u8TValue;
}

u16 TIM1_TCNTGetRegValue(void)
{
	return TCNT1;
}

void TIM1_CTCCallBack(void(*ptr)(void))
{
	TIM1_CTC_GlobalPtr=ptr;
}

void __vector_7 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_7 (void)
{
	TIM1_CTC_GlobalPtr();
}

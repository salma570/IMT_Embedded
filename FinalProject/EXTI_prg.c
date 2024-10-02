/*
 * EXTI_prg.c
 *
 *  Created on: Aug 21, 2024
 *      Author: midoy
 */
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "EXTI_prv.h"
#include "EXTI_cfg.h"
#include "EXTI_int.h"

void(*EXTI0_GlobalPtr)(void)=0;
void(*EXTI1_GlobalPtr)(void)=0;
void(*EXTI2_GlobalPtr)(void)=0;


void EXTI_SetTriggerMode(void)
{

#if(EXTI0_mode==FallingEdge)
	SET_BIT(MCUCR_Register,ISC01);
	CLR_BIT(MCUCR_Register,ISC00);

#elif(EXTI0_mode==RisingEdge)
	SET_BIT(MCUCR_Register,ISC01);
	SET_BIT(MCUCR_Register,ISC00);

#elif(EXTI0_mode==OnChange)
	SET_BIT(MCUCR_Register,ISC00);
	CLR_BIT(MCUCR_Register,ISC01);

#elif(EXTI0_mode==LowLevel)
	CLR_BIT(MCUCR_Register,ISC00);
	CLR_BIT(MCUCR_Register,ISC01);

#endif

#if(EXTI1_mode==FallingEdge)
	SET_BIT(MCUCR_Register,ISC11);
	CLR_BIT(MCUCR_Register,ISC10);

#elif(EXTI1_mode==RisingEdge)
	SET_BIT(MCUCR_Register,ISC11);
	SET_BIT(MCUCR_Register,ISC10);

#elif(EXTI1_mode==OnChange)
	SET_BIT(MCUCR_Register,ISC10);
	CLR_BIT(MCUCR_Register,ISC11);

#elif(EXTI1_mode==LowLevel)
	CLR_BIT(MCUCR_Register,ISC10);
	CLR_BIT(MCUCR_Register,ISC11);

#endif

#if(EXTI2_mode==FallingEdge)
	CLR_BIT(MCUCSR_Register,ISC2);

#elif(EXTI2_mode==RisingEdge)
	SET_BIT(MCUCSR_Register,ISC2);

#endif

}

void EXTI0_ChangeTriggerMode(u8 Copy_u8Mode)
{
	switch (Copy_u8Mode)
	{
		case FallingEdge:
			SET_BIT(MCUCR_Register,ISC01);
			CLR_BIT(MCUCR_Register,ISC00);
			break;
		case RisingEdge:
			SET_BIT(MCUCR_Register,ISC01);
			SET_BIT(MCUCR_Register,ISC00);
			break;
		case OnChange:
			SET_BIT(MCUCR_Register,ISC00);
			CLR_BIT(MCUCR_Register,ISC01);
			break;
		case LowLevel:
			CLR_BIT(MCUCR_Register,ISC00);
			CLR_BIT(MCUCR_Register,ISC01);
			break;
		default:
			break;
	}
}


void EXTI_Enable(u8 Copy_u8IntNumber)
{
	switch (Copy_u8IntNumber) {
	case EXTI0:
		SET_BIT(GICR_Register,INT0);
		break;
	case EXTI1:
		SET_BIT(GICR_Register,INT1);
		break;
	case EXTI2:
		SET_BIT(GICR_Register,INT2);
		break;
	default:
		break;
	}

}
void EXTI_Disable(u8 Copy_u8IntNumber)
{
	switch (Copy_u8IntNumber) {
	case EXTI0:
		CLR_BIT(GICR_Register,INT0);
		break;
	case EXTI1:
		CLR_BIT(GICR_Register,INT1);
		break;
	case EXTI2:
		CLR_BIT(GICR_Register,INT2);
		break;
	default:
		break;
	}

}


void EXTI0_CallBackFunc(void(*ptr)(void))
{
	EXTI0_GlobalPtr=ptr;
}
void EXTI1_CallBackFunc(void(*ptr)(void))
{
	EXTI1_GlobalPtr=ptr;

}
void EXTI2_CallBackFunc(void(*ptr)(void))
{
	EXTI2_GlobalPtr=ptr;
}

void __vector_1 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_1 (void)
{
	EXTI0_GlobalPtr();
}

void __vector_2 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_2 (void)
{
	EXTI1_GlobalPtr();
}

void __vector_3 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_3 (void)
{
	EXTI2_GlobalPtr();
}




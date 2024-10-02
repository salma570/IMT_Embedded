/*
 * GIE_prg.c
 *
 *  Created on: Aug 21, 2024
 *      Author: midoy
 */
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "GIE_prv.h"
#include "GIE_int.h"



void GIE_Enable(void)
{
SET_BIT(SREG_Register,I);
}
void GIE_Disable(void)
{
CLR_BIT(SREG_Register,I);
}


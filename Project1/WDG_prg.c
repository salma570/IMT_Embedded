/*
 * WDG_prg.c
 *
 *  Created on: Aug 30, 2024
 *      Author: hp
 */
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "WDG_prv.h"
#include "WDG_int.h"

void WDG_TurnOn(void)
{
	SET_BIT(WDTCR,WDE);
}

void WDG_TurnOff(void)
{
	WDTCR = (1<<WDTOE) | (1<<WDE);
	WDTCR = 0x00;
}

void WDG_Sleep(u8 Copy_u8Time)
{
	WDTCR = (WDTCR&11111000)|Copy_u8Time;
}
void WDG_Refresh(void)
{
	//WDR -> WDG Refresh
	asm("wdr");
}

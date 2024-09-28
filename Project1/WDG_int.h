/*
 * WDG_int.h
 *
 *  Created on: Aug 30, 2024
 *      Author: hp
 */

#ifndef WDG_INT_H_
#define WDG_INT_H_


#define MS_16_3  0
#define MS_32_5  1
#define MS_65    2
#define MS_130   3
#define MS_260   4
#define MS_520   5
#define M5_1000  6
#define MS_2100  7

void WDG_TurnOn(void);
void WDG_TurnOff(void);
void WDG_Sleep(u8 Copy_u8Time);
void WDG_Refresh(void);

#endif /* WDG_INT_H_ */

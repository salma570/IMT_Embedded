/*
 * Alarm_int.h
 *
 *  Created on: Oct 13, 2024
 *      Author: HP
 */

#ifndef ALARM_INT_H_
#define ALARM_INT_H_

void Alarm_AdjustTime(void);
u8 Alarm_GetHr(void);
u8 Alarm_GetMin(void);

void Alarm_InitTemp(void);
void Alarm_voidIncrementOK(void);
u8 Alarm_u8GetCurrentButtonCount(void);
void Alarm_u8IncrementCurrentTemp(void);

void Alarm_DisplaySet(void);
void Alarm_voidTempDisplay(void);

#endif /* ALARM_INT_H_ */

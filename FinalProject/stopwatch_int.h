/*
 * stopwatch_int.h
 *
 *  Created on: Oct 3, 2024
 *      Author: hp
 */

#ifndef STOPWATCH_INT_H_
#define STOPWATCH_INT_H_


u8 CountDown_u8Run(void);
void CountDownu8_SetCurrent_Values(void);
u8 GetCurrentButton_count(void);

void CountDown_voidTempDisplay(void);
void init_alltemp(void);
void CountDown_u8IncrementCurrentTemp(void);
void CountDown_u8IncrementOK(void);

void STOPWATCH_voidRun(void);
void STOPWATCH_voidDisplay(void);
void STOPWATCH_voidSReset(void);


#endif /* STOPWATCH_INT_H_ */

/*
 * Timer_int.h
 *
 *  Created on: Aug 29, 2024
 *      Author: hp
 */

#ifndef TIMER_INT_H_
#define TIMER_INT_H_

void TIM0_OFinit(void);
void TIM0_CTCinit(void);
void TIM0_PWMinit(void);

void TIM0_OFInterruptEnable(void);
void TIM0_OFSetRegValue(u8 Copy_u8PreLoadValue);
void TIM0_CTCSetRegValue(u8 Copy_u8CompareMatchValue);
void TIM0_OFCallBack(void(*ptr)(void));

/****************************************************************/

void TIM1_init(void);
void TIM1_initNormal(void);
void TIM1_initCTC(void);
void TIM1_ICRSetRegValue(u16 Copy_u8TopValue);
void TIM1_CTC_A_SetRegValue(u16 Copy_u8CompareValue);
void TIM1_TCNTSetRegValue(u16 Copy_u8Value);
u16 TIM1_TCNTGetRegValue(void);

#endif /* TIMER_INT_H_ */

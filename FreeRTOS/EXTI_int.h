/*
 * EXTI_int.h
 *
 *  Created on: Aug 21, 2024
 *      Author: midoy
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_


#define EXTI0  0
#define EXTI1  1
#define EXTI2  2

#define FallingEdge 0
#define RisingEdge  1
#define OnChange    2
#define LowLevel    3

void EXTI_SetTriggerMode(void);
void EXTI0_ChangeTriggerMode(u8 Copy_u8Mode);
void EXTI_Enable(u8 Copy_u8IntNumber);
void EXTI_Disable(u8 Copy_u8IntNumber);
void EXTI0_CallBackFunc(void(*ptr)(void));
void EXTI1_CallBackFunc(void(*ptr)(void));
void EXTI2_CallBackFunc(void(*ptr)(void));


#endif /* EXTI_INT_H_ */

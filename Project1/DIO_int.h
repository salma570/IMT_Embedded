/*
 * DIO_int.h
 *
 *  Created on: Aug 9, 2024
 *      Author: hp
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_

/* PORT Macros */
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

/* Mode Macros */
#define Output    1
#define Input     0
#define PortOut 255
#define PortIn    0


/* PIN Macros */
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

/* Value Macros */
#define LOW 0
#define HIGH 1


void DIO_SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
void DIO_SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

u8 DIO_GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);
void DIO_GetPinValueByPtr(u8 Copy_u8Port, u8 Copy_u8Pin, u8 * Copy_u8ptr);

void DIO_SetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
void DIO_SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);

#endif /* DIO_INT_H_ */

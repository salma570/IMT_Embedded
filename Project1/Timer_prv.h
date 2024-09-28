/*
 * Timer_prv.h
 *
 *  Created on: Aug 29, 2024
 *      Author: hp
 */

#ifndef TIMER_PRV_H_
#define TIMER_PRV_H_

#define TCCR0    *((volatile u8*)(0x53))
#define TCNT0    *((volatile u8*)(0x52))
#define OCR0     *((volatile u8*)(0x5C))
#define TIMSK    *((volatile u8*)(0x59))
#define TIFR     *((volatile u8*)(0x58))

#define TOIE0 0
#define OCIE0 1

#define TOV0 0
#define OCF0 1

#define FOV0  7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02  2
#define CS01  1
#define CS00  0

/**************************************************/

#define TTCR1A     *((volatile u8*)(0x4F))
#define TTCR1B     *((volatile u8*)(0x4E))
#define OCR1A      *((volatile u16*)(0x4A))
#define ICR1       *((volatile u16*)(0x46))
#define TCNT1      *((volatile u16*)(0x4C))

#define OCIE1A  4

#define COM1A1  7
#define COM1A0  6
#define WGM11   1
#define WGM10   0

#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0


#endif /* TIMER_PRV_H_ */

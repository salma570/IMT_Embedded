/*
 * DIO_prv.h
 *
 *  Created on: Aug 9, 2024
 *      Author: hp
 */

#ifndef DIO_PRV_H_
#define DIO_PRV_H_

#define PORTA_Register   *((volatile u8 *)(0x3B))
#define DDRA    *((volatile u8 *)(0x3A))
#define PINA    *((volatile u8 *)(0x39))

#define PORTB_Register   *((volatile u8 *)(0x38))
#define DDRB    *((volatile u8 *)(0x37))
#define PINB    *((volatile u8 *)(0x36))

#define PORTC_Register   *((volatile u8 *)(0x35))
#define DDRC    *((volatile u8 *)(0x34))
#define PINC    *((volatile u8 *)(0x33))

#define PORTD_Register   *((volatile u8 *)(0x32))
#define DDRD    *((volatile u8 *)(0x31))
#define PIND    *((volatile u8 *)(0x30))


#endif /* DIO_PRV_H_ */

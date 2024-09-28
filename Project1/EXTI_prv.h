/*
 * EXTI_prv.h
 *
 *  Created on: Aug 21, 2024
 *      Author: midoy
 */

#ifndef EXTI_PRV_H_
#define EXTI_PRV_H_

#define MCUCR_Register    *((volatile u8*)(0x55))
#define MCUCSR_Register   *((volatile u8*)(0x54))
#define GICR_Register     *((volatile u8*)(0x5B))
#define GIFR_Register     *((volatile u8*)(0x5A))

#define ISC11  3
#define ISC10  2
#define ISC01  1
#define ISC00  0

#define ISC2   6

#define INT1   7
#define INT0   6
#define INT2   5

#define INTF1   7
#define INTF0   6
#define INTF2   5


#endif /* EXTI_PRV_H_ */

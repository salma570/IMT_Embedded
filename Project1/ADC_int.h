/*
 * ADC_int.h
 *
 *  Created on: Aug 24, 2024
 *      Author: hp
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_

#define Channel_0 0
#define Channel_1 1
#define Channel_2 2
#define Channel_3 3
#define Channel_4 4
#define Channel_5 5
#define Channel_6 6
#define Channel_7 7

#define Bit_Musk 0b11100000

void ADC_init(void);
u16 ADC_Read(u8 Copy_u8Channel);
u32 Mapping(u32 Range1_max,u32 Range1_min,u32 Range2_max,u32 Range2_min,u32 Range1_reading);

#endif /* ADC_INT_H_ */

/*
 * ADC_prg.c
 *
 *  Created on: Aug 29, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "ADC_int.h"
#include "ADC_prv.h"


void ADC_init(void)
{
	//mode
	SET_BIT(ADMUX_Register,REFS0);
	CLR_BIT(ADMUX_Register,REFS1);

	//right or left
	CLR_BIT(ADMUX_Register,ADLAR);

	//clk -> prescaler = 128
	SET_BIT(ADCSRA_Register,ADPS2);
	SET_BIT(ADCSRA_Register,ADPS1);
	SET_BIT(ADCSRA_Register,ADPS0);

	//enable
	SET_BIT(ADCSRA_Register,ADEN);
}


u16 ADC_Read(u8 Copy_u8Channel)
{
	//select channel
	ADMUX_Register=((ADMUX_Register&Bit_Musk)|Copy_u8Channel);

	//start conversion
	SET_BIT(ADCSRA_Register,ADSC);

	//wait on flag
	while(GET_BIT(ADCSRA_Register,ADIF)==0);

	//clear flag
	SET_BIT(ADCSRA_Register,ADIF);

	//return digital value
	return ADC_Register;
}

u32 Mapping(u32 Range1_max,u32 Range1_min,u32 Range2_max,u32 Range2_min,u32 Range1_reading)
{

	return (Range2_max-((Range2_max-Range2_min)*(Range1_max-Range1_reading)/(Range1_max-Range1_min)));
}

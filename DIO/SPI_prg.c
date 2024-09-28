/*
 * SPI_prg.c
 *
 *  Created on: Sep 7, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "SPI_prv.h"
#include "SPI_int.h"

void SPI_MasterInit(void)
{
	//select master
	SET_BIT(SPCR_Register,MSTR);

	//enable SPI
	SET_BIT(SPCR_Register,SPE);
}

void SPI_SlaveInit(void)
{
	//select slave
	CLR_BIT(SPCR_Register,MSTR);

	//enable SPI
	SET_BIT(SPCR_Register,SPE);
}

u8 SPI_Tranceive(u8 Copy_u8Data)
{
	SPDR_Register=Copy_u8Data;
	while(GET_BIT(SPSR_Register,SPIF)==0);
	return SPDR_Register;
}

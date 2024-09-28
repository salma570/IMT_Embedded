/*
 * TWI_prg.c
 *
 *  Created on: Sep 8, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "TWI_Register.h"
#include "TWI_Interface.h"

void TWI_voidMasterInit(u8 Copy_MasterAddress)
{
	//200kHz clk speed
	TWBR=12;
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);

	//enable Ack
	SET_BIT(TWCR, TWCR_TWEA);

	//set Master Address
	TWAR=Copy_MasterAddress<<1;

	//enable TWI
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidSlaveInit(u8 Copy_SlaveAddress)
{
	//enable Ack
	SET_BIT(TWCR, TWCR_TWEA);

	//set Slave Address
	TWAR=Copy_SlaveAddress<<1;

	//enable TWI
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidStartCondition()
{
	//start condition
	SET_BIT(TWCR,TWCR_TWSTA);

	//clear flag
	SET_BIT(TWCR,TWCR_TWINT);

	//wait on the flag
	while (GET_BIT(TWCR,TWCR_TWINT)==0);

}

void TWI_voidSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	//send slave address
	TWDR=Copy_u8SlaveAddress<<1;

	//write
	CLR_BIT(TWDR,0);

	//clear start condition
	CLR_BIT(TWCR,TWCR_TWSTA);

	//clear flag
	SET_BIT(TWCR,TWCR_TWINT);

	//wait on the flag
	while (GET_BIT(TWCR,TWCR_TWINT)==0);
}

void TWI_voidSendSLaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	//send slave address
	TWDR=Copy_u8SlaveAddress<<1;

	//read
	SET_BIT(TWDR,0);

	//clear start condition
	CLR_BIT(TWCR,TWCR_TWSTA);

	//clear flag
	SET_BIT(TWCR,TWCR_TWINT);

	//wait on the flag
	while (GET_BIT(TWCR,TWCR_TWINT)==0);
}

void TWI_voidSendData(u8 Copy_u8Data)
{
	//send data
	TWDR=Copy_u8Data;

	//clear flag
	SET_BIT(TWCR,TWCR_TWINT);

	//wait on the flag
	while (GET_BIT(TWCR,TWCR_TWINT)==0);
}

u8 TWI_u8RecieveData()
{
	//clear flag
	SET_BIT(TWCR,TWCR_TWINT);

	//wait on the flag
	while (GET_BIT(TWCR,TWCR_TWINT)==0);

	//read data
	return TWDR;
}

void TWI_voidStopCondition()
{
	SET_BIT(TWCR,TWCR_TWSTO);
}


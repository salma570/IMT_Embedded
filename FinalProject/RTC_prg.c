/*
 * RTC_prg.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "RTC_prv.h"
#include "RTC_int.h"
#include "TWI_Interface.h"

void RTC_init(void)
{
	//enable oscillator
	//how does it know the reg?
	CLR_BIT(Sec_Reg,7);

	//choose 24-hour mode
	CLR_BIT(Hrs_Reg,6);

	//
}

//What is the slave address ?
void RTC_Write(u16 Copy_u16ByteAddress, u8 Copy_u8Data, u8 Copy_u8Device)
{
	//prep slave address
	u8 SlaveAddress = 0;
	SlaveAddress = 0b01010000|(Copy_u8Device<<2)|(u8)(Copy_u16ByteAddress>>8);

	//start
	TWI_voidStartCondition();

	//send slave address with write
	TWI_voidSendSlaveAddressWithWrite(SlaveAddress);

	//send byte number
	TWI_voidSendData((u8)Copy_u16ByteAddress);

	//send data
	TWI_voidSendData((u8)Copy_u8Data);

	//stop
	TWI_voidStopCondition();

	//delay
	_delay_ms(10);
}

u8   RTC_Read(u16 Copy_u16ByteAddress, u8 Copy_u8Device)
{
	//prep slave address
	u8 SlaveAddress = 0;
	SlaveAddress = 0b01010000|(Copy_u8Device<<2)|(u8)(Copy_u16ByteAddress>>8);

	//start
	TWI_voidStartCondition();

	//send slave address with write
	TWI_voidSendSlaveAddressWithWrite(SlaveAddress);

	//send byte number
	TWI_voidSendData((u8)Copy_u16ByteAddress);

	//repeated start
	TWI_voidStartCondition();

	//send slave address with write
	TWI_voidSendSLaveAddressWithRead(SlaveAddress);

	//read data
	u8 Data = 0;
	Data = TWI_u8RecieveData();

	//stop
	TWI_voidStopCondition();

	return Data;
}
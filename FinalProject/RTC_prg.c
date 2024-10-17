/*
 * RTC_prg.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "LCD_int.h"
#include "RTC_prv.h"
#include "RTC_int.h"
#include "TWI_Interface.h"
#include "util/delay.h"

//7otto el validations barra
void RTC_voidInit(void) //can add option to user to choose mode 12 or 24
{
	//enable oscillator
	//CLR_BIT(Sec_Reg,7);
	u8 oscillator_enable = ((RTC_Read(Sec_Reg))&(0b01111111));

	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Write");
	_delay_ms(1000);
	RTC_Write(Sec_Reg,oscillator_enable);

	//choose 24-hour mode -> by default: can be changed later by user
	//CLR_BIT(Hrs_Reg,6);
	u8 mode_selector_24 = (RTC_Read(Hrs_Reg))&(0b10111111);
	TWI_Reset();
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Write2");
	_delay_ms(1000);
	RTC_Write(Hrs_Reg,mode_selector_24);
}

void RTC_Write(u8 Copy_u16RegAddress, u8 Copy_u8Data) //MCU writes on RTC
{
	//prep slave address
	u8 SlaveAddress = 0b01101000;

	u8 status = TWI_u8GetStatus();
	char statusStr[4];
	sprintf(statusStr, "%02X", status);
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString(statusStr);
	_delay_ms(1000);
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Entering TWI Start");
	_delay_ms(500);
	//start
	TWI_voidStartCondition();
	status = TWI_u8GetStatus();
	sprintf(statusStr, "%02X", status);
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString(statusStr);
	_delay_ms(1000);

	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Send Slave Write");
	_delay_ms(500);
	//send slave address with write
	TWI_voidSendSlaveAddressWithWrite(SlaveAddress);

	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Send Data 1");
	_delay_ms(500);
	//send register number
	TWI_voidSendData((u8)Copy_u16RegAddress);

	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Send Data 2");
	_delay_ms(500);
	//send data
	TWI_voidSendData((u8)Copy_u8Data);

	//stop
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Stop");
	_delay_ms(500);
	TWI_voidStopCondition();

	//delay
	_delay_ms(10);
}

u8   RTC_Read(u8 Copy_u16RegAddress) //MCU reads from RTC
{
	//prep slave address
	u8 SlaveAddress = 0b01101000;

	//start
	TWI_voidStartCondition();
	//status 08 -> start cond transmitted

	//send slave address with write
	TWI_voidSendSlaveAddressWithWrite(SlaveAddress);
	//status 08 -> SLA+W transmitted, ACK received.

	//send register number
	TWI_voidSendData((u8)Copy_u16RegAddress);
	//0x28: Data byte transmitted, ACK received.

	//delay
	_delay_us(10); //lw bazet emsa7o da

	//repeated start
	TWI_voidStartCondition();
	//0x10: Repeated start condition transmitted.

	//send slave address with read
	TWI_voidSendSLaveAddressWithRead(SlaveAddress);
	//0x40: SLA+R transmitted, ACK received.

	//read data
	u8 Data = 0;
	Data = TWI_u8RecieveData();
	//0x50: Data byte received, ACK returned.

	//stop
	TWI_voidStopCondition();
	//0x50: Data byte received, ACK returned.
	return Data;
}

void RTC_voidSetSec(RTC_val* rtc)
{
	if(rtc->u8Seconds>=0 && rtc->u8Seconds<=59)
		RTC_Write(Sec_Reg,rtc->u8Seconds);
}
void RTC_voidSetMin(RTC_val* rtc)
{
	if(rtc->u8Minutes>=0 && rtc->u8Minutes<=59)
		RTC_Write(Min_Reg,rtc->u8Minutes);
}
void RTC_voidSetHour(RTC_val* rtc)
{
	if(rtc->u8Hours>=0 && rtc->u8Hours<=24)
		RTC_Write(Hrs_Reg,rtc->u8Hours);
}
void RTC_voidSetYr(RTC_val* rtc)
{
	if(rtc->u8Years>=0 && rtc->u8Years<=24)
		RTC_Write(Year_Reg,rtc->u8Years);
}
void RTC_voidSetMonth(RTC_val* rtc)
{
	if(rtc->u8Months>=1 && rtc->u8Months<=12)
		RTC_Write(Month_Reg,rtc->u8Months);
}
void RTC_voidSetDay(RTC_val* rtc)
{
	if ((rtc->u8Months == 1 || rtc->u8Months == 3 || rtc->u8Months == 5 || rtc->u8Months == 7 || rtc->u8Months == 8 || rtc->u8Months == 10 || rtc->u8Months == 12) && (rtc->u8Days >= 1 && rtc->u8Days <= 31))
	{
		RTC_Write(Day_Reg,rtc->u8Days);
	}
	else if ((rtc->u8Months == 4 || rtc->u8Months == 6 || rtc->u8Months == 9 || rtc->u8Months == 11) && (rtc->u8Days >= 1 && rtc->u8Days <= 30))
	{
		RTC_Write(Day_Reg,rtc->u8Days);
	}
	else if (rtc->u8Months == 2)
	{
		if (rtc->u8Years % 4 == 0)
		{
			if (rtc->u8Days >= 1 && rtc->u8Days <= 29)
				RTC_Write(Day_Reg,rtc->u8Days);
		}
		else
		{
			if (rtc->u8Days >= 1 && rtc->u8Days <= 28)
				RTC_Write(Day_Reg,rtc->u8Days);
		}
	}
}
void RTC_voidSetWeekDay(RTC_val* rtc)
{
	if(rtc->u8DayOfWeek>=1 && rtc->u8DayOfWeek<=7)
		RTC_Write(WeekDay_Reg,rtc->u8DayOfWeek);
}
//getters
u8 RTC_voidGetSec(void)
{
	u8 reg_val = RTC_Read(Sec_Reg);
	u8 tens = BCD_to_DEC(reg_val && 0b01110000);
	u8 units = BCD_to_DEC(reg_val && 0b00001111);
	return ((tens*10) + units);
}
u8 RTC_voidGetMin(void)
{
	u8 reg_val = RTC_Read(Min_Reg);
	u8 tens = BCD_to_DEC(reg_val && 0b01110000);
	u8 units = BCD_to_DEC(reg_val && 0b00001111);
	return ((tens*10) + units);
}
u8 RTC_voidGetHour(void)
{
	u8 reg_val = RTC_Read(Hrs_Reg);
	u8 tens = BCD_to_DEC(reg_val && 0b00010000);
	u8 units = BCD_to_DEC(reg_val && 0b00001111);
	return ((tens*10) + units);
}
u8 RTC_voidGetYr(void)
{
	u8 reg_val = RTC_Read(Year_Reg);
	u8 tens = BCD_to_DEC(reg_val && 0b11110000);
	u8 units = BCD_to_DEC(reg_val && 0b00001111);
	return ((tens*10) + units);
}
u8 RTC_voidGetMonth(void)
{
	u8 reg_val = RTC_Read(Month_Reg);
	u8 tens = BCD_to_DEC(reg_val && 0b00010000);
	u8 units = BCD_to_DEC(reg_val && 0b00001111);
	return ((tens*10) + units);
}
u8 RTC_voidGetDay(void)
{
	u8 reg_val = RTC_Read(Day_Reg);
	u8 tens = BCD_to_DEC(reg_val && 0b00110000);
	u8 units = BCD_to_DEC(reg_val && 0b00001111);
	return ((tens*10) + units);
}
u8 RTC_voidGetWeekDay(void)
{
	u8 reg_val = RTC_Read(WeekDay_Reg);
	u8 day = BCD_to_DEC(reg_val && 0b00000111);
	return day;
}
//converters
u8 DEC_to_BCD(u8 val)
{
	return (val + 6*(val/10));
}
u8 BCD_to_DEC(u8 val)
{
	return (val - 6*(val>>4));
}


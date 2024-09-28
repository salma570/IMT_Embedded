/*
 * LCD_prg.c
 *
 *  Created on: Aug 13, 2024
 *      Author: hp
 */
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_int.h"
#include "LCD_int.h"
#include "LCD_cfg.h"
#include "util/delay.h"

void LCD_init(void)
{
	//Port -> Out, Data, Command
	DIO_SetPortDirection(LCD_DataPort,PortOut);
	//3 Pins -> out
	DIO_SetPinDirection(LCD_CtrlPort,RS_Pin,Output);
	DIO_SetPinDirection(LCD_CtrlPort,RW_Pin,Output);
	DIO_SetPinDirection(LCD_CtrlPort,E_Pin,Output);
	//ensure E is low
	DIO_SetPinValue(LCD_CtrlPort,E_Pin,LOW);
	//init -> datasheet
	_delay_ms(30);
	LCD_WriteCommand(lcd_FunctionSet8bit);
	_delay_ms(5);
	LCD_WriteCommand(lcd_DisplayOn);
	_delay_ms(5);
	LCD_WriteCommand(lcd_Clear);
	_delay_ms(5);
	LCD_WriteCommand(lcd_EntryMode);
}

void LCD_WriteCommand(u8 Copy_u8Command)
{
	//RS -> 0 COMMAND
	DIO_SetPinValue(LCD_CtrlPort,RS_Pin,LOW);
	//RW -> 0 WRITE
	DIO_SetPinValue(LCD_CtrlPort,RW_Pin,LOW);
	//E -> 0 ENSURE
	DIO_SetPinValue(LCD_CtrlPort,E_Pin,LOW);
	//Write Command
	DIO_SetPortValue(LCD_DataPort,Copy_u8Command);
	//GIVE PULSE
	//E -> 1
	DIO_SetPinValue(LCD_CtrlPort,E_Pin,HIGH);
	//Delay
	_delay_ms(5);
	//E -> 0
	DIO_SetPinValue(LCD_CtrlPort,E_Pin,LOW);
}

void LCD_WriteChar(u8 Copy_u8Char)
{
	//RS -> 1 DATA
	DIO_SetPinValue(LCD_CtrlPort,RS_Pin,HIGH);
	//RW -> 0 WRITE
	DIO_SetPinValue(LCD_CtrlPort,RW_Pin,LOW);
	//E -> 0 ENSURE
	DIO_SetPinValue(LCD_CtrlPort,E_Pin,LOW);
	//Write Command
	DIO_SetPortValue(LCD_DataPort,Copy_u8Char);
	//GIVE PULSE
	//E -> 1
	DIO_SetPinValue(LCD_CtrlPort,E_Pin,HIGH);
	//Delay
	_delay_ms(5);
	//E -> 0
	DIO_SetPinValue(LCD_CtrlPort,E_Pin,LOW);
}

void LCD_WriteString(const u8 * Copy_u8Ptr)
{
	u8 i = 0;
	while(Copy_u8Ptr[i]!='\0')
	{
		LCD_WriteChar(Copy_u8Ptr[i]);
		i++;
	}
}

void LCD_GoTo(u8 Copy_u8Line, u8 Copy_u8Column)
{
	u8 Copy_u8LocalVariable;
	if(Copy_u8Column>=0 && Copy_u8Column<=15)
	{
		switch (Copy_u8Line) {
			case line_1:
				Copy_u8LocalVariable=128+Copy_u8Column;
				break;
			case line_2:
				Copy_u8LocalVariable=192+Copy_u8Column;
				break;
			default:
				break;
		}
	}
	LCD_WriteCommand(Copy_u8LocalVariable);
}

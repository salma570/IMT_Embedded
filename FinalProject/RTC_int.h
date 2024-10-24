/*
 * RTC_int.h
 *
 *  Created on: Oct 2, 2024
 *      Author: hp
 */

#ifndef RTC_INT_H_
#define RTC_INT_H_

#include "STD_Types.h"
#include "util/delay.h"
#include "TWI_Register.h"
#include <stdio.h>

#define F_CPU 8000000UL  // clock frequency is 8 MHz
#define SCL_CLOCK 100000L // I2C clock 100 kHz

// DS1307 Address
#define DS1307_ADDRESS 0x68

// Function prototypes
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(u8 data);
u8 I2C_ReadAck(void);
u8 I2C_ReadNack(void);
void RTC_SetTime(u8 sec, u8 min, u8 hour);
void RTC_GetTime(u8 *sec, u8 *min, u8 *hour);
u8 BCD_to_Dec(u8 bcd);
u8 Dec_to_BCD(u8 dec);
void RTC_SetDate(u8 day, u8 date, u8 month, u8 year);
void RTC_GetDate(u8 *day, u8 *date, u8 *month, u8 *year);

#endif /* RTC_INT_H_ */

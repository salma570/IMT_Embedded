/*
 * RTC_prv.h
 *
 *  Created on: Oct 2, 2024
 *      Author: hp
 */

#ifndef RTC_PRV_H_
#define RTC_PRV_H_

#define Sec_Reg  		*((volatile u8*)(0x00))
#define Min_Reg 		*((volatile u8*)(0x01))
#define Hrs_Reg			*((volatile u8*)(0x02))
#define WeekDay_Reg 	*((volatile u8*)(0x03))
#define Day_Reg			*((volatile u8*)(0x04))
#define Month_Reg  		*((volatile u8*)(0x05))
#define Year_Reg  		*((volatile u8*)(0x06))
#define Ctrl_Reg  		*((volatile u8*)(0x07))


// Bits inside registers
#define  REGISTER_INIT_STATUS           0X08
#define  REGISTER_SNAP0_VACANCY         0X09
#define  RAM_START                      0X08
#define  RAM_END                        0X3F
#define  BIT_SETTING_CH                 0X07
#define  BIT_SETTING_RS0                0X00
#define  BIT_SETTING_RS1                0X01
#define  BIT_SETTING_SQWE               0X04
#define  BIT_SETTING_OUT                0X07
#define  BIT_SETTING_AMPM               0X06
#define  TIMEKEEPER_REGISTERS_START     0X00
#define  TIMEKEEPER_REGISTERS_END       0X07
#define  REGISTER_SECONDS_DEFAULT       0X00
#define  REGISTER_MINUTES_DEFAULT       0X00
#define  REGISTER_HOURS_DEFAULT         0X00
#define  REGISTER_DAY_OF_WEEK_DEFAULT   0X01
#define  REGISTER_DATE_DEFAULT          0X01
#define  REGISTER_MONTH_DEFAULT         0X01
#define  REGISTER_YEAR_DEFAULT          0X00
#define  REGISTER_CONTROL_DEFAULT       0X00
#define  RAM_BLOCK_DEFAULT              0x00
#define  SNAP0_ADDRESS					0x39

//extra configs -> in progress
#define DS1307_I2C_ADDRESS                    0X68
#define CLOCK_RUN                             0X01
#define CLOCK_HALT                            0X00
#define FORCE_RESET                           0X00
#define NO_FORCE_RESET                        0X01
#define DS1307_IS_RUNNING                     0X01
#define DS1307_IS_STOPPED                     0X00
#define OPERATION_DONE                        0X01
#define OPERATION_FAILED                      0X00
#define DS1307_NOT_INITIALIZED                0X00
#define DS1307_INITIALIZED                    0X2C
#define OCCUPIED                              0X01
#define NOT_OCCUPIED                          0X00

#endif /* RTC_PRV_H_ */

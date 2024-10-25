/*
 * RTC_prg.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "RTC_int.h"
#include "TWI_Register.h"
#include "LCD_int.h"
#include "util/delay.h"

u8 RTC_buttonCount = 0;
static u8 RTCtemp[13];
void RTC_InitTemp(void)
{
	for(int i=0; i<13; i++)
	{
		(RTCtemp[i])=0;
	}
}

// I2C Initialization
void I2C_Init(void) {
	// Set SCL frequency
	TWSR = 0x00; // Prescaler set to 1
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2; // Set bit rate register
}

// Start I2C communication
void I2C_Start(void) {
	TWCR = (1 << TWCR_TWSTA) | (1 << TWCR_TWEN) | (1 << TWCR_TWINT); // Send START condition
	while (!(TWCR & (1 << TWCR_TWINT))); // Wait for START condition to be transmitted
}

// Stop I2C communication
void I2C_Stop(void) {
	TWCR = (1 << TWCR_TWSTO) | (1 << TWCR_TWEN) | (1 << TWCR_TWINT); // Send STOP condition
}

// Write data to I2C bus
void I2C_Write(u8 data) {
	TWDR = data; // Load data into data register
	TWCR = (1 << TWCR_TWEN) | (1 << TWCR_TWINT); // Clear TWINT to start transmission
	while (!(TWCR & (1 << TWCR_TWINT))); // Wait for data to be transmitted
}

// Read data from I2C bus with ACK
u8 I2C_ReadAck(void) {
	TWCR = (1 << TWCR_TWEN) | (1 << TWCR_TWINT) | (1 << TWCR_TWEA); // Enable TWI and ACK
	while (!(TWCR & (1 << TWCR_TWINT))); // Wait for data reception
	return TWDR; // Return received data
}

// Read data from I2C bus with NACK
u8 I2C_ReadNack(void) {
	TWCR = (1 << TWCR_TWEN) | (1 << TWCR_TWINT); // Enable TWI without ACK
	while (!(TWCR & (1 << TWCR_TWINT))); // Wait for data reception
	return TWDR; // Return received data
}

// Convert BCD to decimal
u8 BCD_to_Dec(u8 bcd) {
	return ((bcd / 16 * 10) + (bcd % 16));
}

// Convert decimal to BCD
u8 Dec_to_BCD(u8 dec) {
	return ((dec / 10 * 16) + (dec % 10));
}

// Set time in DS1307 RTC
void RTC_SetTime(u8 sec, u8 min, u8 hour) {
	sec = Dec_to_BCD(sec);
	min = Dec_to_BCD(min);
	hour = Dec_to_BCD(hour);

	I2C_Start();
	I2C_Write(DS1307_ADDRESS << 1); // Address the DS1307 in write mode
	I2C_Write(0x00); // Set pointer to seconds register
	I2C_Write(sec);  // Write seconds
	I2C_Write(min);  // Write minutes
	I2C_Write(hour); // Write hours
	I2C_Stop();
}

// Get time from DS1307 RTC
void RTC_GetTime(u8 *sec, u8 *min, u8 *hour) {
	I2C_Start();
	I2C_Write(DS1307_ADDRESS << 1); // Address DS1307 in write mode
	I2C_Write(0x00); // Set pointer to seconds register
	I2C_Stop();

	I2C_Start();
	I2C_Write((DS1307_ADDRESS << 1) | 1); // Address DS1307 in read mode
	*sec = BCD_to_Dec(I2C_ReadAck()); // Read seconds
	*min = BCD_to_Dec(I2C_ReadAck()); // Read minutes
	*hour = BCD_to_Dec(I2C_ReadNack()); // Read hours
	I2C_Stop();
}

// Set the day, date, month, and year in DS1307
void RTC_SetDate(u8 day, u8 date, u8 month, u8 year) {
	day = Dec_to_BCD(day);
	date = Dec_to_BCD(date);
	month = Dec_to_BCD(month);
	year = Dec_to_BCD(year);

	I2C_Start();
	I2C_Write(DS1307_ADDRESS << 1); // Address the DS1307 in write mode
	I2C_Write(0x03); // Set pointer to day register
	I2C_Write(day);  // Write day of the week
	I2C_Write(date); // Write date
	I2C_Write(month); // Write month
	I2C_Write(year); // Write year
	I2C_Stop();
}

// Get the day, date, month, and year from DS1307
void RTC_GetDate(u8 *day, u8 *date, u8 *month, u8 *year) {
	I2C_Start();
	I2C_Write(DS1307_ADDRESS << 1); // Address DS1307 in write mode
	I2C_Write(0x03); // Set pointer to day register
	I2C_Stop();

	I2C_Start();
	I2C_Write((DS1307_ADDRESS << 1) | 1); // Address DS1307 in read mode
	*day = BCD_to_Dec(I2C_ReadAck());   // Read day of the week
	*date = BCD_to_Dec(I2C_ReadAck());  // Read date
	*month = BCD_to_Dec(I2C_ReadAck()); // Read month
	*year = BCD_to_Dec(I2C_ReadNack()); // Read year
	I2C_Stop();
}

u8 RTC_u8GetCurrentButtonCount(void)
{
	return RTC_buttonCount;
}

void RTC_incButtonCount(void)
{
	RTC_buttonCount++;
	return;
}

void RTC_IncrementCurrentTemp(void)
{
	// Ensure count_button_pressed is within valid range
	if (RTC_buttonCount < 0 || RTC_buttonCount >= 13) {
		// Handle out of bounds case (optional)
		return; // or some error handling
	}
	// Reset if the current number is 9
	if(RTC_buttonCount ==0) //Hrstens
	{
		if (RTCtemp[RTC_buttonCount] >= 2)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if(RTC_buttonCount ==1) //HrsUnits
	{
		if (RTCtemp[RTC_buttonCount] >= 4 && RTCtemp[0] == 2)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else if (RTCtemp[RTC_buttonCount] >= 9)
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 2) //MinTens
	{
		if (RTCtemp[RTC_buttonCount] >= 5)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 3) //MinUnits
	{
		if (RTCtemp[RTC_buttonCount] >= 9)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 4) //SecTens
	{
		if (RTCtemp[RTC_buttonCount] >= 5)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 5) //SecUnits
	{
		if (RTCtemp[RTC_buttonCount] >= 9)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 6 || RTC_buttonCount == 7) //YearTens & Units
	{
		if (RTCtemp[RTC_buttonCount] >= 9)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 8) //MonthTens
	{
		if (RTCtemp[RTC_buttonCount] >= 1)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 9) //MonthUnits
	{
		if (RTCtemp[RTC_buttonCount] >= 2 && RTCtemp[8] == 1)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else if (RTCtemp[RTC_buttonCount] >= 9)
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 10) //DayTens
	{
		if (RTCtemp[RTC_buttonCount] >= 2 && (((RTCtemp[8])*10)+(RTCtemp[9]))== 2) //feb
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else if (RTCtemp[RTC_buttonCount] >= 3) //any other month
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 11) //DayUnits
	{
		u8 year = (((RTCtemp[6])*10)+(RTCtemp[7]));
		u8 month = (((RTCtemp[8])*10)+(RTCtemp[9]));
		u8 DayTens = (RTCtemp[10]);
		//if dayTens = 2 -> Units can go till 9 except feb, according to year
		if (DayTens==2 && month == 2 && year%4!=0)
		{
			if (RTCtemp[RTC_buttonCount] >= 8)
			{
				RTCtemp[RTC_buttonCount] = 0;
			}
		}
		//if dayTens = 3 -> Units can be 0 or 1 according to month
		else if (DayTens==3)
		{
			if (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
			{
				if (RTCtemp[RTC_buttonCount] >= 1)
				{
					RTCtemp[RTC_buttonCount] = 0;
				}
			}
			else if (month==4 || month==6 || month==9 || month==11)
			{
				RTCtemp[RTC_buttonCount] = 0;
			}
		}
		//if dayTens = 0 or 1 or 2 -> Units can go till 9
		else if((DayTens==0 || DayTens==1 || DayTens==2) && (RTCtemp[RTC_buttonCount] >= 9))
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{
			RTCtemp[RTC_buttonCount]++;
		}
	}
	else if (RTC_buttonCount == 12) //WeekDay
	{
		if (RTCtemp[RTC_buttonCount] >= 7)
		{
			RTCtemp[RTC_buttonCount] = 0;
		}
		else
		{ // Otherwise increment it
			RTCtemp[RTC_buttonCount]++;
		}
	}

	else
	{
		return;
	}
}

void RTC_SetVals(void)
{
	u8 hour = ((RTCtemp[0])*10)+(RTCtemp[1]);
	u8 min = ((RTCtemp[2])*10)+(RTCtemp[3]);
	u8 sec = ((RTCtemp[4])*10)+(RTCtemp[5]);
	RTC_SetTime(sec, min, hour);
	u8 year = ((RTCtemp[6])*10)+(RTCtemp[7]);
	u8 month = ((RTCtemp[8])*10)+(RTCtemp[9]);
	u8 date = ((RTCtemp[10])*10)+(RTCtemp[11]);
	u8 day = (RTCtemp[12]);
	RTC_SetDate(day, date, month, year);
}

char* MapDay(u8 num)
{
	switch (num) {
	case 0:
		return "Sat";
	case 1:
		return "Sun";
	case 2:
		return "Mon";
	case 3:
		return "Tues";
	case 4:
		return "Wed";
	case 5:
		return "Thurs";
	case 6:
		return "Fri";
	default:
		return "N/A";
	}
}

void RTC_Display(void)
{
	u8 hour, min, sec;
	u8 day, date, month, year;
	char buffer[10];
	LCD_GoTo(line_1,0);
	RTC_GetTime(&sec, &min, &hour);
	RTC_GetDate(&day, &date, &month, &year);

	// Display time
	sprintf(buffer, "%02d", hour);
	LCD_WriteString(buffer);
	LCD_WriteChar(':');

	sprintf(buffer, "%02d", min);
	LCD_WriteString(buffer);
	LCD_WriteChar(':');

	sprintf(buffer, "%02d", sec);
	LCD_WriteString(buffer);
	LCD_WriteChar(' ');

	LCD_GoTo(line_2,0);
	char * WeekDay = MapDay(day);
	LCD_WriteString(WeekDay);
	LCD_WriteChar('-');

	// Display date (DD-MM-YY)
	sprintf(buffer, "%02d", date);
	LCD_WriteString(buffer);
	LCD_WriteChar('-');

	sprintf(buffer, "%02d", month);
	LCD_WriteString(buffer);
	LCD_WriteChar('-');

	sprintf(buffer, "%02d", year);
	LCD_WriteString(buffer);

}

void RTC_DisplayTemp(void)
{
	u8 hour = ((RTCtemp[0])*10)+(RTCtemp[1]);
	u8 min = ((RTCtemp[2])*10)+(RTCtemp[3]);
	u8 sec = ((RTCtemp[4])*10)+(RTCtemp[5]);
	u8 year = ((RTCtemp[6])*10)+(RTCtemp[7]);
	u8 month = ((RTCtemp[8])*10)+(RTCtemp[9]);
	u8 date = ((RTCtemp[10])*10)+(RTCtemp[11]);
	u8 day = (RTCtemp[12]);
	char buffer[10];

	LCD_GoTo(line_1,0);
	// Display time
	sprintf(buffer, "%02d", hour);
	LCD_WriteString(buffer);
	LCD_WriteChar(':');

	sprintf(buffer, "%02d", min);
	LCD_WriteString(buffer);
	LCD_WriteChar(':');

	sprintf(buffer, "%02d", sec);
	LCD_WriteString(buffer);
	LCD_WriteChar(' ');

	u8 button = RTC_u8GetCurrentButtonCount();
	LCD_WriteChar((button+48));

	LCD_GoTo(line_2,0);
	char * WeekDay = MapDay(day);
	LCD_WriteString(WeekDay);
	LCD_WriteChar('-');

	// Display date (DD-MM-YY)
	sprintf(buffer, "%02d", date);
	LCD_WriteString(buffer);
	LCD_WriteChar('-');

	sprintf(buffer, "%02d", month);
	LCD_WriteString(buffer);
	LCD_WriteChar('-');

	sprintf(buffer, "%02d", year);
	LCD_WriteString(buffer);
	return;
}

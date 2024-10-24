/*
 * RTC_prg.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "RTC_int.h"
#include "TWI_Interface.h"
#include "util/delay.h"

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


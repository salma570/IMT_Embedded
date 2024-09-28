/*
 * EEPROM_int.h
 *
 *  Created on: Sep 8, 2024
 *      Author: hp
 */

#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_

#define Device_0   0
#define Device_1   1

void EEPROM_Write(u16 Copy_u16ByteAddress, u8 Copy_u8Data, u8 Copy_u8Device);

u8   EEPROM_Read(u16 Copy_u16ByteAddress, u8 Copy_u8Device);

#endif /* EEPROM_INT_H_ */

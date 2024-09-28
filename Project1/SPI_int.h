/*
 * SPI_int.h
 *
 *  Created on: Sep 7, 2024
 *      Author: hp
 */

#ifndef SPI_INT_H_
#define SPI_INT_H_

void SPI_MasterInit(void);
void SPI_SlaveInit(void);
u8 SPI_Tranceive(u8 Copy_u8Data);

#endif /* SPI_INT_H_ */

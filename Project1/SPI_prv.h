/*
 * SPI_prv.h
 *
 *  Created on: Sep 7, 2024
 *      Author: hp
 */

#ifndef SPI_PRV_H_
#define SPI_PRV_H_

#define SPCR_Register   *((volatile u8*)(0x2D))
#define SPSR_Register   *((volatile u8*)(0x2E))
#define SPDR_Register   *((volatile u8*)(0x2F))

#define MSTR   4
#define SPE    6
#define SPIF   7

#endif /* SPI_PRV_H_ */

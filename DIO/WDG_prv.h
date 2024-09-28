/*
 * WDG_prv.h
 *
 *  Created on: Aug 30, 2024
 *      Author: hp
 */

#ifndef WDG_PRV_H_
#define WDG_PRV_H_

#define WDTCR    *((volatile u8*)(0x41))

#define WDTOE   4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0

#endif /* WDG_PRV_H_ */

/*
 * stopwatch_int.h
 *
 *  Created on: Oct 3, 2024
 *      Author: hp
 */

#ifndef STOPWATCH_INT_H_
#define STOPWATCH_INT_H_

u8 STOPWATCH_u8CheckFlag(void);
void STOPWATCH_voidToggle(void);
void STOPWATCH_voidRun(void);
void STOPWATCH_voidDisplay(void);  // returns the current time in memory w implement stop funct
void STOPWATCH_voidSReset(void);


#endif /* STOPWATCH_INT_H_ */

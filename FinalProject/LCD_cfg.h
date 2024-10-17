/*
 * LCD_cfg.h
 *
 *  Created on: Aug 13, 2024
 *      Author: hp
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define LCD_DataPort PORTA /* Select PORTA or PORTB or PORTC or PORTD */
#define LCD_CtrlPort PORTB /* Select PORTA or PORTB or PORTC or PORTD */

#define RS_Pin PIN_3 /* Select a pin from PIN_0 to PIN_7 */
#define RW_Pin PIN_1 /* Select a pin from PIN_0 to PIN_7 */
#define E_Pin  PIN_0 /* Select a pin from PIN_0 to PIN_7 */

#endif /* LCD_CFG_H_ */

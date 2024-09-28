/*
 * LCD_int.h
 *
 *  Created on: Aug 13, 2024
 *      Author: hp
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* return cursor to first position on first line                   */
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0x80          // set cursor position

#define line_1 0
#define line_2 1

void LCD_init(void);
void LCD_WriteCommand(u8 Copy_u8Command);
void LCD_WriteChar(u8 Copy_u8Char);
void LCD_WriteString(const u8 * Copy_u8Ptr);
void LCD_GoTo(u8 Copy_u8Line, u8 Copy_u8Column);

#endif /* LCD_INT_H_ */

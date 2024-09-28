/*
 * Seg7_prg.c
 *
 *  Created on: Aug 13, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_int.h"
#include "SEG7_int.h"
#include "SEG7_cfg.h"


static u8 Arr[10] =   {0b00111111,   /* 0 */
                       0b00000110,   /* 1 */
                       0b01011011,   /* 2 */
                       0b01001111,   /* 3 */
                       0b01100110,   /* 4 */
                       0b01101101,   /* 5 */
                       0b01111101,   /* 6 */
                       0b00000111,   /* 7 */
                       0b01111111,   /* 8 */
                       0b01101111    /* 9 */
					  };

void SEG7_init(void)
{
#if(ComType==ComAnode)
	//Pin->Output, Pin->High
	DIO_SetPinDirection(Seg7_ComPort, Seg7_ComPin,Output);
	DIO_SetPinValue(Seg7_ComPort, Seg7_ComPin, HIGH);

#elif(ComType==ComCathode)
	//Pin->Output, Pin->Low
	DIO_SetPinDirection(Seg7_ComPort, Seg7_ComPin,Output);
	DIO_SetPinValue(Seg7_ComPort, Seg7_ComPin, LOW);
#endif
DIO_SetPortDirection(Seg7_DisplayPort,PortOut);
}

void SEG7_DisplayNumber(u8 Copy_u8Number)
{
#if(ComType==ComAnode)
	DIO_SetPortValue(Seg7_DisplayPort,~Arr[Copy_u8Number]);
#elif(ComType==ComCathode)
	DIO_SetPortValue(Seg7_DisplayPort,Arr[Copy_u8Number]);
#endif

}

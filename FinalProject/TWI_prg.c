/*
 * TWI_prg.c
 *
 *  Created on: Sep 8, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "TWI_Register.h"
#include "TWI_Interface.h"
#include "LCD_int.h"
#include "util/delay.h"

void TWI_voidMasterInit(u8 Copy_MasterAddress)
{
	//100kHz clk speed
	TWBR=32;
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);

	//enable Ack
	SET_BIT(TWCR, TWCR_TWEA);

	//set Master Address
	TWAR=Copy_MasterAddress<<1;

	//enable TWI
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidSlaveInit(u8 Copy_SlaveAddress)
{
	//enable Ack
	SET_BIT(TWCR, TWCR_TWEA);

	//set Slave Address
	TWAR=Copy_SlaveAddress<<1;

	//enable TWI
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_Reset() //TWI is stuck or unresponsive.
{
    // Disable the TWI (set the TWEN bit to 0)
    CLR_BIT(TWCR, TWCR_TWEN);

    // You might want to wait a bit to ensure TWI is properly disabled
    _delay_ms(1);

    // Enable the TWI again (set the TWEN bit to 1)
    SET_BIT(TWCR, TWCR_TWEN);
}


void TWI_voidStartCondition() {
    // Check if the bus is busy
    if (GET_BIT(TWCR, TWCR_TWSTA)) {
        // If busy
        LCD_WriteCommand(lcd_Clear);
        LCD_WriteString("Bus is Busy");
        _delay_ms(1000);
        return;
    }

    // Optional: Clear TWINT before setting start condition
    CLR_BIT(TWCR, TWCR_TWINT); // Make sure TWINT is cleared

    // Start condition
    SET_BIT(TWCR, TWCR_TWSTA);

    // Clear flag to initiate the start condition
    SET_BIT(TWCR, TWCR_TWINT);

    // Optional: Wait for a brief moment to stabilize
    _delay_ms(1); // Small delay

    // Wait until the start condition has been transmitted
    while (GET_BIT(TWCR, TWCR_TWINT) == 0) {
        u8 status = TWI_u8GetStatus();
        LCD_WriteCommand(lcd_Clear);
        LCD_WriteString("Status: ");
        char statusStr[4];
        sprintf(statusStr, "%02X", status);
        LCD_WriteString(statusStr);
        _delay_ms(1000); // Slow down the loop to observe
    }

}


void TWI_voidStopCondition()
{
	//	SET_BIT(TWCR,TWCR_TWSTO);

	// Send Stop Condition
	SET_BIT(TWCR, TWCR_TWSTO);

	// Clear flag
	SET_BIT(TWCR, TWCR_TWINT);

	// Wait until stop condition execution is complete
	while (GET_BIT(TWCR, TWCR_TWSTO) == 1);
}

void TWI_voidSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	//send slave address
	TWDR=Copy_u8SlaveAddress<<1;

	//write
	CLR_BIT(TWDR,0);

	//clear start condition
	CLR_BIT(TWCR,TWCR_TWSTA);

	//clear flag
	SET_BIT(TWCR,TWCR_TWINT);

	//wait on the flag
	while (GET_BIT(TWCR,TWCR_TWINT)==0);
}

void TWI_voidSendSLaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	//send slave address
	TWDR=Copy_u8SlaveAddress<<1;

	//read
	SET_BIT(TWDR,0);

	//clear start condition
	CLR_BIT(TWCR,TWCR_TWSTA);

	//clear flag
	SET_BIT(TWCR,TWCR_TWINT);

	//wait on the flag
	while (GET_BIT(TWCR,TWCR_TWINT)==0);
}

void TWI_voidSendData(u8 Copy_u8Data)
{
	//send data
	TWDR=Copy_u8Data;

	//clear flag
	SET_BIT(TWCR,TWCR_TWINT);

	//wait on the flag
	while (GET_BIT(TWCR,TWCR_TWINT)==0);
}

u8 TWI_u8RecieveData()
{
	//clear flag
	SET_BIT(TWCR,TWCR_TWINT);

	//wait on the flag
	while (GET_BIT(TWCR,TWCR_TWINT)==0);

	//read data
	return TWDR;
}

u8 TWI_u8GetStatus(void)
{
	// Mask the prescaler bits (lower 3 bits) and return only the status bits (upper 5 bits)
	return (TWSR & 0xF8);
}
/*
	0x08: Start condition transmitted.
	0x10: Repeated start condition transmitted.
	0x18: SLA+W transmitted, ACK received.
	0x20: SLA+W transmitted, NACK received.
	0x28: Data byte transmitted, ACK received.
	0x30: Data byte transmitted, NACK received.
	0x38: Arbitration lost.
	0x40: SLA+R transmitted, ACK received.
	0x48: SLA+R transmitted, NACK received.
	0x50: Data byte received, ACK returned.
	0x58: Data byte received, NACK returned.
	0xF8: Bus error
	0x00: No relevant information

	u8 status = TWI_u8GetStatus();
	char statusStr[4];
	sprintf(statusStr, "%02X", status);
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString(statusStr);
 */

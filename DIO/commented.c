/*
 * commented.c
 *
 *  Created on: Sep 7, 2024
 *      Author: hp
 */

/*u8 value =0;
	DIO_SetPortDirection(PORTA,PortOut);

	TWI_voidMasterInit(1);
	EEPROM_Write(5,7,Device_0);
	value=EEPROM_Read(5,Device_0);

	DIO_SetPortValue(PORTA,value);

 * //main master
void main(void)
{
	//pins
	//MOSI
	DIO_SetPinDirection(PORTB,PIN_5,Output);
	//MISO
	DIO_SetPinDirection(PORTB,PIN_6,Input);
	//SCK
	DIO_SetPinDirection(PORTB,PIN_7,Output);
	//SS
	DIO_SetPinDirection(PORTB,PIN_4,Input);
	DIO_SetPinValue(PORTB,PIN_4,HIGH);

	SPI_MasterInit();

	while(1)
	{
		SPI_Tranceive(10);
	}
 */

/*//main slave
void main(void)
{
	u8 x=0;
	//pins
	//MOSI
	DIO_SetPinDirection(PORTB,PIN_5,Input);
	//MISO
	DIO_SetPinDirection(PORTB,PIN_6,Output);
	//SCK
	DIO_SetPinDirection(PORTB,PIN_7,Input);
	//SS
	DIO_SetPinDirection(PORTB,PIN_4,Input);

	SPI_SlaveInit();

	//led
	DIO_SetPinDirection(PORTA,PIN_0,Output);
	DIO_SetPinValue(PORTA,PIN_0,LOW);

	while(1)
	{
		x=SPI_Tranceive(70);
		if(x==10)
		{
			DIO_SetPinValue(PORTA,PIN_0,HIGH);
		}
	}


/*u8 x=0;
	DIO_SetPortDirection(PORTA,PortOut);

	DIO_SetPinDirection(PORTD,PIN_0,Input); //RX ->D0
	UART_init();


	while(1)
	{
		x=UART_receive();
		switch (x) {
		case '1':
			DIO_SetPinValue(PORTA,PIN_0,HIGH);
			break;
		case '2':
			DIO_SetPinValue(PORTA,PIN_1,HIGH);
			break;
		case '3':
			DIO_SetPinValue(PORTA,PIN_2,HIGH);
			break;
		default:
			break;
		}
		_delay_ms(1000);
		DIO_SetPortValue(PORTA,0);
	}


/*UART_init();
	DIO_SetPinDirection(PORTD,PIN_1,Output); //TXD Config

	while(1)
	{
		UART_transmit('H');
	}

/*u16 reading =0;
	u16 value =0;

	// Initialize PWM for servo control
	TIM1_init();
	ADC_init();

	// Set PD5 (OC1A) as output
	DIO_SetPinDirection(PORTD,PIN_5, Output);
	DIO_SetPinDirection(PORTA,PIN_0,Input);

	// Set Top Value
	TIM1_ICRSetRegValue(20000); //20ms

	while (1)
	{
		reading=ADC_Read(Channel_0);
		value = Mapping(1023,0,2500,500,reading);
		TIM1_CTC_A_SetRegValue(value);
	}
///////////////// POTENTIOMETER TO CONTROL SERVO POSITION ///////////////
void main(void)
{

	u16 reading =0;
	u16 value =0;

	// Initialize PWM for servo control
	TIM1_init();
	ADC_init();

	// Set PD5 (OC1A) as output
	DIO_SetPinDirection(PORTD,PIN_5, Output);
	DIO_SetPinDirection(PORTA,PIN_0,Input);

	// Set Top Value
	TIM1_ICRSetRegValue(20000); //20ms

	while (1)
	{
		reading=ADC_Read(Channel_0);
		value = Mapping(1023,0,2500,500,reading);
		TIM1_CTC_A_SetRegValue(value);
	}
}





/*
void SW_ICU(void);
u16 Tperiod = 0;
u16 onTicks = 0;
u16 dutyCycle = 0;

void main(void)
{

/*******************  GENERATE PWM using TIM0   **************************/
/*TIM0_PWMinit();
	//overflow time -> period
	//compare time -> Ton
	TIM0_CTCSetRegValue(100);
	//OC0 -> output
	DIO_SetPinDirection(PORTB,PIN_3,Output);

	//Tperiod = TOVF = 256 usec
	//Duty Cycle = TON/Tperiod = 200/265 = 78%

/*******************  Measure PWM using TIM1 & EXTI0   **************************/
//config external interrupt to start in RisingEdge
/*EXTI_SetTriggerMode();
	//PD2->Input
	DIO_SetPinDirection(PORTD,PIN_2,Input);

	//ISR ACTION
	EXTI0_CallBackFunc(SW_ICU);

	//enables
	EXTI_Enable(EXTI0);
	GIE_Enable();
	TIM1_initNormal();

/******************************** LCD *******************************/
//enty 3rfa bt3mleha ezay di

/*while(1)
	{
		if(onTicks!=0 && Tperiod!=0)
		{
			dutyCycle=(100*onTicks)/Tperiod; //multiply first to not get zero
			//display on LCD
		}
	}

}

void SW_ICU(void)
{
	static counter =0;
	counter++;
	if(counter==1)
	{
		//reset
		TIM1_TCNTSetRegValue(0);
	}
	if(counter==2)
	{
		Tperiod=TIM1_TCNTGetRegValue();
		EXTI0_ChangeTriggerMode(FallingEdge);
	}
	if(counter==3)
	{
		onTicks=TIM1_TCNTGetRegValue();
		onTicks=onTicks-Tperiod;
		EXTI_Disable(EXTI0);
	}
}
 */



/*u16 reading =0;
	u32 millivolt=0;
	ADC_init();

	DIO_SetPinDirection(PORTC,PIN_5,Output);
	DIO_SetPinValue(PORTC,PIN_5,LOW);

	DIO_SetPortDirection(PORTA,Input);

	while (1)
	{
		reading = ADC_Read(Channel_0);
		millivolt = (((u32)reading*5000)/1024);
		//printf("%u\n",reading);
		if(millivolt < 1500)
		{
			DIO_SetPinValue(PORTC,PIN_5,HIGH);
		}
		else
		{
			DIO_SetPinValue(PORTC,PIN_5,LOW);
		}
		_delay_ms(1500);
	}

/*GIE_Enable();

	EXTI_Enable(EXTI0);
	EXTI_SetTriggerMode();

	DIO_SetPinDirection(PORTD,PIN_2,Input);
	DIO_SetPinValue(PORTD,PIN_2,HIGH);

	DIO_SetPinDirection(PORTA,PIN_0,Output);
	DIO_SetPinValue(PORTA,PIN_0,LOW);

	u8 button = 0;
	while(1)
	{
		button = DIO_GetPinValue(PORTD,PIN_2);
		if (button ==0)
		{EXTI0_CallBackFunc(func);}
	}

}

void func(void)
{
	static u8 i=0;
	if(i==0)
	{
		DIO_SetPinValue(PORTA,PIN_0,HIGH);
		i=1;
	}
	else if(i==1)
	{
		DIO_SetPinValue(PORTA,PIN_0,LOW);
		i=0;
	}
}


/*u16 reading =0;
	u16 value =0;
	//init
	ADC_init();
	TIM1_init();

	//ADC Pin
	DIO_SetPinDirection(PORTA,PIN_0,Input);

	//OC1A pin
	DIO_SetPinDirection(PORTD,PIN_5,Output);

	//top value = 20ms
	TIM1_ICRSetRegValue(20000);

	while(1)
	{
		reading = ADC_Read(Channel_0);
		Mapping(1023,0,2500,500,reading);
		TIM1_CTC_A_SetRegValue(value);
	}



/*

/*void func (void)
{
	static u32 counter=1;
	if (counter==3907)
	{
		//Action
		static u8 i=0;
		if(i==0)
		{
			DIO_SetPinValue(PORTB,PIN_0,HIGH);
			i=1;
		}
		else if(i==1)
		{
			DIO_SetPinValue(PORTB,PIN_0,LOW);
			i=0;
		}
		counter=0;
		TIM0_OFSetRegValue(192);
	}
	else
	{
		counter++;
	}
}


/*TIM0_CTCinit();

	//led
	DIO_SetPinDirection(PORTB,PIN_3,Output);
	DIO_SetPinValue(PORTB,PIN_3,HIGH);

	TIM0_CTCSetRegValue(200);


/*
1 sec ---›toggle led
tick time --> 8 prescaler
ticktime lusec
overflow time 256 usec
overflow count 1/256*10exp (-6);
ovfc=3906.25
preload (1-.25)8*265=192
counter - - > 3907
 */

/*TIM0_init();

	//led
	DIO_SetPinDirection(PORTB,PIN_0,Output);
	DIO_SetPinValue(PORTB,PIN_0,HIGH);

	TIM0_OFSetRegValue(192);
	TIM0_OFCallBack(func);
	//PIE
	TIM0_OFInterruptEnable();
	//GIE
	GIE_Enable();
 */

/*u32 Temp;
	u32 millivolt;
	u16 reading;

	ADC_init();
	LCD_init();

	DIO_SetPinDirection(PORTA,PIN_0,Input);
	while(1)
	{
		reading = ADC_Read(Channel_0);
		millivolt = ((u32)reading*5000)/1024;
		Temp = millivolt/10;

		LCD_WriteCommand(lcd_Clear);
		LCD_WriteChar((Temp/10)+48);
		LCD_WriteChar((Temp%10)+48);
	}


/*DIO_SetPortDirection(PORTB, 0b00001111); //in low, out high
	//Pull-Up
	DIO_SetPinValue(PORTB,PIN_7,HIGH);
	DIO_SetPinValue(PORTB,PIN_0,HIGH);
	u8 val;
	while(1)
	{
		val = DIO_GetPinValue(PORTB,PIN_7);
		if(val == 0)
		{
			DIO_SetPinValue(PORTB,PIN_0,LOW);
		}
		else
		{
			DIO_SetPinValue(PORTB,PIN_0,HIGH);
		}
	}

/*void LCD_DisplayCount(u8 count)
{
	switch (count) {
		case 0:
			LCD_WriteChar('0');
			break;
		case 1:
			LCD_WriteChar('1');
			break;
		case 2:
			LCD_WriteChar('2');
			break;
		case 3:
			LCD_WriteChar('3');
			break;
		case 4:
			LCD_WriteChar('4');
			break;
		case 5:
			LCD_WriteChar('5');
			break;
		case 6:
			LCD_WriteChar('6');
			break;
		case 7:
			LCD_WriteChar('7');
			break;
		case 8:
			LCD_WriteChar('8');
			break;
		default:
			break;
	}
}*/

/*
 * LCD_init();
	DIO_SetPortDirection(PORTB, 0b00001111); //in low, out high
	DIO_SetPinValue(PORTB,PIN_7,HIGH); //Pullup
	u8 button_state = 0;
	u8 current_state = 0;
	u8 Tcount = 0;
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString("Program Starts");
	_delay_ms(3000);
	while(1)
	{
		LCD_WriteCommand(lcd_Clear);
		LCD_DisplayCount(Tcount);
		_delay_ms(1000);
		button_state=DIO_GetPinValue(PORTB,PIN_7); //either high or low
		if(button_state!=current_state) //toggle happened
		{
			DIO_SetPinValue(PORTB,PIN_0,current_state);
			Tcount++;
			if(Tcount==9)
			{
				LCD_WriteCommand(lcd_Clear);
				LCD_WriteString("LED is ON");
				DIO_SetPinValue(PORTB,PIN_0,HIGH);
				while(1){}
			}
		}
		current_state=button_state;
	}
 */


/*
 * LCD_init();
	//LCD_WriteChar('A');
	LCD_WriteCommand(lcd_Clear);
	LCD_WriteString((u8*)"HEY,");
	LCD_GoTo(line_2,6);
	LCD_WriteString((u8*)"Family");
 *
 */



//SEG7_init();
//SEG7_DisplayNumber(2);

/*  //LED A0
	//DIO_SetPinDirection(PORTA,PIN_0,Output);
	//DIO_SetPinValue(PORTA,PIN_0,LOW);
	DIO_SetPortDirection(PORTA,PortOut);
	DIO_SetPortValue(PORTA,0);

	//Button B0
	//DIO_SetPinDirection(PORTB,PIN_0,Input);
	//Pull-Up
	//DIO_SetPinValue(PORTB,PIN_0,HIGH);

	u8 LocalVariable;
	while(1){
		DIO_GetPinValueByPtr(PORTB,PIN_0,&LocalVariable);
		if(LocalVariable==0)
		{
			//DIO_SetPortValue(PORTA,255);
			DIO_SetPinValue(PORTA,PIN_0,HIGH);
		}
		else
		{
			//DIO_SetPortValue(PORTA,0);
			DIO_SetPinValue(PORTA,PIN_0,LOW);
		}
	}
 */

/*DIO_SetPortDirection(PORTB, 0b00001111); //in low, out high
	DIO_SetPinValue(PORTB,PIN_5,HIGH);
	//Button B0
	DIO_SetPinDirection(PORTB,PIN_0,Input);
	//Pull-Up
	DIO_SetPinValue(PORTB,PIN_0,HIGH);*/



/*
 * u16 digital=0;
	u32 analogue=0;

	//LEDS
	DIO_SetPinDirection(PORTB,PIN_0,Output);
	DIO_SetPinValue(PORTB,PIN_0,LOW);

	DIO_SetPinDirection(PORTB,PIN_1,Output);
	DIO_SetPinValue(PORTB,PIN_1,LOW);

	DIO_SetPinDirection(PORTB,PIN_2,Output);
	DIO_SetPinValue(PORTB,PIN_2,LOW);

	//ADC PIN
	DIO_SetPinDirection(PORTA,PIN_2,Input);

	ADC_init();


	while(1)
	{
		digital=ADC_Read(Channel_2);
		analogue=(((u32)digital*5000)/1024);
		if(analogue>=0 && analogue<1500)
		{
			DIO_SetPinValue(PORTB,PIN_0,HIGH);
			DIO_SetPinValue(PORTB,PIN_1,LOW);
			DIO_SetPinValue(PORTB,PIN_2,LOW);
		}
		else if(analogue>=1500 && analogue<3000)
		{
			DIO_SetPinValue(PORTB,PIN_0,LOW);
			DIO_SetPinValue(PORTB,PIN_1,HIGH);
			DIO_SetPinValue(PORTB,PIN_2,LOW);
		}
		else
		{
			DIO_SetPinValue(PORTB,PIN_0,LOW);
			DIO_SetPinValue(PORTB,PIN_1,LOW);
			DIO_SetPinValue(PORTB,PIN_2,HIGH);
		}
		_delay_ms(1000);
	}
 */

////////////////////////////    OS     //////////////////////////
/*
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_int.h"
#include "OS_int.h"

void led1(void)
{
	static u8 i=0;
		if(i==0)
		{
			DIO_SetPinValue(PORTA,PIN_0,HIGH);
			i=1;
		}
		else
		{
			DIO_SetPinValue(PORTA,PIN_0,LOW);
			i=0;
		}

}

void led2(void)
{
	static u8 i=0;

		if(i==0)
		{
			DIO_SetPinValue(PORTA,PIN_1,HIGH);
			i=1;
		}
		else
		{
			DIO_SetPinValue(PORTA,PIN_1,LOW);
			i=0;
		}
}

void led3(void)
{
	static u8 i=0;
		if(i==0)
		{
			DIO_SetPinValue(PORTA,PIN_2,HIGH);
			i=1;
		}
		else
		{
			DIO_SetPinValue(PORTA,PIN_2,LOW);
			i=0;
		}
}
void main(void)
{
	DIO_SetPortDirection(PORTA,PortOut);
	DIO_SetPinValue(PORTA,PIN_3,HIGH);
	OS_CreateTask(led1,1,0,0);
	OS_CreateTask(led2,2,1,1);
	OS_CreateTask(led3,3,2,0);

	OS_Start();

	while(1)
	{

	}
}
 */

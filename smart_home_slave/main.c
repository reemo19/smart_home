/*
 * main.c
 *
 *  Created on: Aug 24, 2023
 *      Author: hp
 */

#include "STD_TYPES.h"
#include <math.h>
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "SPIMASTER.h"
#include "ADC.h"
#include <avr/io.h>
#include"util/delay.h"
//s
int main()
{


	//slave
	DIO_u8SetPinDir(DIO_PORTB,DIO_PIN4,DIO_PIN_IN);
		DIO_u8SetPinDir(DIO_PORTB,DIO_PIN5,DIO_PIN_IN);
		DIO_u8SetPinDir(DIO_PORTB,DIO_PIN6,DIO_PIN_OUT);
		DIO_u8SetPinDir(DIO_PORTB,DIO_PIN7,DIO_PIN_IN);
	//ROOM
	DIO_u8SetPinDir(DIO_PORTC,DIO_PIN0,DIO_PIN_OUT);

//motor
	DIO_u8SetPinDir(DIO_PORTC,DIO_PIN6,DIO_PIN_OUT);
//COND
	DIO_u8SetPinDir(DIO_PORTC,DIO_PIN4,DIO_PIN_OUT);

	//tv
	DIO_u8SetPinDir(DIO_PORTC,DIO_PIN5,DIO_PIN_OUT);
	//DIO_u8SetPortDir(DIO_PORTC,DIO_PORT_OUT);
	//TEMP
	DIO_u8SetPinDir(DIO_PORTA,DIO_PIN0,DIO_PIN_IN);

	//DIO_u8SetPortDir(DIO_PORTC,DIO_PORT_OUT);
	u8 x;
	u16 v,al;
	SPI_voidSlaveInit();

	ADC_voidInt();

		while(1)
		{



			x=SPI_voidRecive();
			if(x==1){
				SET_BIT(PORTC,0);}
            if(x==2)
				CLEAR_BIT(PORTC,0);
            if(x==3)
           		TOGGLE_BIT(PORTC,5);

            v=ADC_u16Read(0);
              				al=(v*4.88);
              				al=al/10;
              				if(al>=30)
              				{
              				SET_BIT(PORTC,4);
              				SET_BIT(PORTC,6);
              				}
              				else if(al<30){
              				CLEAR_BIT(PORTC,4);
              				CLEAR_BIT(PORTC,6);
              				}




		}
}

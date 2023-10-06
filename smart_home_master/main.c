/*
 * main.c
 *
 *  Created on: Sep 23, 2023
 *      Author: hp
 */
#include "STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "TIMER_TEST_interface.h"
#include "GIE.h"
#include "TWI.h"
#include "EEPROM.h"
#include"ADC.h"
#include "SPIMASTER.h"
#include"util/delay.h"
#include "avr/interrupt.h"
//#include<avr/io.h>
u8 va, v1;
u8 value,valu, flag = -1, start = 0;
u8 firstDigit, sDigit, thDigit, lastDigit, pass = 0, passvisit = 0, trypass = 0,
		trypassvisit = 0, c = 1, cv = 1, x, block, v;
int main() {
	//MASTER
	DIO_u8SetPinDir(DIO_PORTB, DIO_PIN4, DIO_PIN_IN);
	DIO_u8SetPinValue(DIO_PORTB, DIO_PIN4, DIO_HIGH);

	DIO_u8SetPinDir(DIO_PORTB, DIO_PIN5, DIO_PIN_OUT);
	DIO_u8SetPinDir(DIO_PORTB, DIO_PIN6, DIO_PIN_IN);
	DIO_u8SetPinDir(DIO_PORTB, DIO_PIN7, DIO_PIN_OUT);
	SPI_voidMasterInit();

	//SPI_voidTransmit(i);
	//twi
	TWI_voidMasterInit();
	//led
	DIO_u8SetPinDir(DIO_PORTC, DIO_PIN2, DIO_PIN_OUT);	//G
	DIO_u8SetPinDir(DIO_PORTC, DIO_PIN3, DIO_PIN_OUT);	//R

	//TIMER 0
	TIMER0_voidOfInit();
	TIMER0_voidPreLoadValue(192);
	GIE_voidEnable();
	//LCD
	DIO_u8SetPortDir(DIO_PORTA, DIO_PORT_OUT);
	DIO_u8SetPinDir(DIO_PORTC, DIO_PIN5, DIO_PIN_OUT);
	DIO_u8SetPinDir(DIO_PORTC, DIO_PIN6, DIO_PIN_OUT);
	//kpd
	DIO_u8SetPortDir(DIO_PORTD, 0b00000111);
	DIO_u8SetPortValue(DIO_PORTD, 0xff);
	CLCD_voidInit();
	//var

	CLCD_voidSendString("welcome to");
	CLCD_voidGoToXY(1, 0);
	CLCD_voidSendString("Smart Home");
	c = 1;
	cv = 1;

	while (1) {
		x = EEPROM_read(0x111);
		v = EEPROM_read(0x112);
		block = EEPROM_read(0x100);
		_delay_ms(150);
		if (start == 0) {
			CLCD_voidSendCommand(0x01);
			CLCD_voidSendString("press 0:admein");
			CLCD_voidGoToXY(1, 0);
			CLCD_voidSendString("1:visit");
			start = 1;
		}
		do {
			valu = KPD_u8GetPressedKey();
		} while (valu== KPD_NO_PRESSED_KEY);
		if (x == 0xff && valu == 0) {

			CLCD_voidSendCommand(0x01);
			CLCD_voidSendString("password admin");
			CLCD_voidGoToXY(1, 0);
			CLCD_voidSendString("password=----");
			CLCD_voidGoToXY(1, 9);
			_delay_ms(500);
			do {
				firstDigit = KPD_u8GetPressedKey();

			} while (firstDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidWriteNumber(firstDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(1, 9);
			CLCD_voidSendData('*');
			do {
				sDigit = KPD_u8GetPressedKey();

			} while (sDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(1, 10);
			CLCD_voidWriteNumber(sDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(1, 10);
			CLCD_voidSendData('*');

			CLCD_voidGoToXY(1, 11);
			do {
				thDigit = KPD_u8GetPressedKey();

			} while (thDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(1, 11);
			CLCD_voidWriteNumber(thDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(1, 11);
			CLCD_voidSendData('*');
			do {
				lastDigit = KPD_u8GetPressedKey();

			} while (lastDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(1, 12);
			CLCD_voidWriteNumber(lastDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(1, 12);
			CLCD_voidSendData('*');
			pass = (lastDigit) + 1000 * (thDigit) + 100 * (sDigit)
					+ 10 * (firstDigit);
			EEPROM_write(0x111, pass);
			_delay_ms(100);
			x = EEPROM_read(0x111);

			CLCD_voidSendCommand(0x01);

		} else if (x != 0xff && c < 4 && valu == 0) {
			CLCD_voidSendCommand(0x01);
			CLCD_voidSendString("pass admin");
			_delay_ms(150);
			CLCD_voidSendCommand(0x01);
			CLCD_voidGoToXY(0, 0);
			CLCD_voidSendString("pass");
			CLCD_voidWriteNumber(c);
			CLCD_voidSendString("=----");
			CLCD_voidGoToXY(0, 6);
			_delay_ms(500);
			do {

				firstDigit = KPD_u8GetPressedKey();

			} while (firstDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(0, 6);
			CLCD_voidWriteNumber(firstDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(0, 6);
			CLCD_voidSendData('*');
			do {
				sDigit = KPD_u8GetPressedKey();

			} while (sDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(0, 7);
			CLCD_voidWriteNumber(sDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(0, 7);
			CLCD_voidSendData('*');

			do {
				thDigit = KPD_u8GetPressedKey();

			} while (thDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(0, 8);
			CLCD_voidWriteNumber(thDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(0, 8);
			CLCD_voidSendData('*');
			do {
				lastDigit = KPD_u8GetPressedKey();

			} while (lastDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(0, 9);
			CLCD_voidWriteNumber(lastDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(0, 9);
			CLCD_voidSendData('*');
			c++;
			trypass = (lastDigit) + 1000 * (thDigit) + 100 * (sDigit)
					+ 10 * (firstDigit);
			CLCD_voidSendCommand(0x01);

			if (x == trypass) {

				DIO_u8SetPinValue(DIO_PORTD, DIO_PIN5, DIO_LOW);
				DIO_u8SetPinValue(DIO_PORTC, DIO_PIN2, DIO_HIGH);
				DIO_u8SetPinValue(DIO_PORTC, DIO_PIN3, DIO_LOW);

				c = 1;
				CLCD_voidSendCommand(0x01);
				CLCD_voidSendString("open ^_^");
				flag = 1;
				_delay_ms(150);
////////////////////////////////////////////////////////////
				while (flag == 1) {
					CLCD_voidSendCommand(0x01);
					CLCD_voidSendString("1:led on 2:led");
					CLCD_voidGoToXY(1, 0);
					CLCD_voidSendString("off 3:tv 0:back");
					do {
						value = KPD_u8GetPressedKey();
						SPI_voidTransmit(0);
					} while (value == KPD_NO_PRESSED_KEY);
					if (value == 0) {
						flag = 0;
						start = 0;
					} else {
						SPI_voidTransmit(value);
					}
				}

//////////////////////////	    ///////////////

			} else {

				//led
				DIO_u8SetPinValue(DIO_PORTC, DIO_PIN2, DIO_LOW);
				DIO_u8SetPinValue(DIO_PORTC, DIO_PIN3, DIO_HIGH);
				CLCD_voidSendCommand(0x01);
				if (c < 4) {
					CLCD_voidSendString("TRY AGAIN");
					DIO_u8SetPinDir(DIO_PORTD, DIO_PIN7, DIO_PIN_OUT);
					SET_BIT(PORTD, 7);
					_delay_ms(500);
					CLCD_voidSendCommand(0x01);
					DIO_u8SetPinDir(DIO_PORTD, DIO_PIN7, DIO_PIN_IN);
					CLEAR_BIT(PORTD, 7);
					start=0;
				} else {

					CLCD_voidSendString("wrong password");
					CLCD_voidGoToXY(1, 7);
					CLCD_voidSendString("-_-");
					DIO_u8SetPinDir(DIO_PORTD, DIO_PIN7, DIO_PIN_OUT);
					SET_BIT(PORTD, 7);
					EEPROM_write(0x100, 0x00);
					block = EEPROM_read(0x100);
					_delay_ms(150);
					c = 1;
				}

			}

		}
//visit
		else if (v == 0xff && valu == 1) {
			CLCD_voidSendCommand(0x01);
			CLCD_voidSendString("password visit");
			//	CLCD_voidSendCommand(0x01);
			CLCD_voidGoToXY(1, 0);
			CLCD_voidSendString("password=----");
			CLCD_voidGoToXY(1, 9);
			_delay_ms(500);
			do {
				firstDigit = KPD_u8GetPressedKey();

			} while (firstDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidWriteNumber(firstDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(1, 9);
			CLCD_voidSendData('*');
			do {
				sDigit = KPD_u8GetPressedKey();

			} while (sDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(1, 10);
			CLCD_voidWriteNumber(sDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(1, 10);
			CLCD_voidSendData('*');

			CLCD_voidGoToXY(1, 11);
			do {
				thDigit = KPD_u8GetPressedKey();

			} while (thDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(1, 11);
			CLCD_voidWriteNumber(thDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(1, 11);
			CLCD_voidSendData('*');
			do {
				lastDigit = KPD_u8GetPressedKey();

			} while (lastDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(1, 12);
			CLCD_voidWriteNumber(lastDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(1, 12);
			CLCD_voidSendData('*');
			passvisit = (lastDigit) + 1000 * (thDigit) + 100 * (sDigit)
					+ 10 * (firstDigit);
			EEPROM_write(0x112, passvisit);
			_delay_ms(100);
			v = EEPROM_read(0x112);

			CLCD_voidSendCommand(0x01);

		} else if (v != 0xff && cv < 4 && valu == 1) {
			CLCD_voidSendCommand(0x01);
			CLCD_voidSendString("pass visit");
			_delay_ms(150);
			CLCD_voidSendCommand(0x01);
			CLCD_voidGoToXY(0, 0);
			CLCD_voidSendString("pass");
			CLCD_voidWriteNumber(cv);
			CLCD_voidSendString("=----");
			CLCD_voidGoToXY(0, 6);
			_delay_ms(500);
			do {

				firstDigit = KPD_u8GetPressedKey();

			} while (firstDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(0, 6);
			CLCD_voidWriteNumber(firstDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(0, 6);
			CLCD_voidSendData('*');
			do {
				sDigit = KPD_u8GetPressedKey();

			} while (sDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(0, 7);
			CLCD_voidWriteNumber(sDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(0, 7);
			CLCD_voidSendData('*');

			do {
				thDigit = KPD_u8GetPressedKey();

			} while (thDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(0, 8);
			CLCD_voidWriteNumber(thDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(0, 8);
			CLCD_voidSendData('*');
			do {
				lastDigit = KPD_u8GetPressedKey();

			} while (lastDigit == KPD_NO_PRESSED_KEY);
			CLCD_voidGoToXY(0, 9);
			CLCD_voidWriteNumber(lastDigit);
			_delay_ms(300);
			CLCD_voidGoToXY(0, 9);
			CLCD_voidSendData('*');
			cv++;
			trypassvisit = (lastDigit) + 1000 * (thDigit) + 100 * (sDigit)
					+ 10 * (firstDigit);
			CLCD_voidSendCommand(0x01);

			if (v == trypassvisit) {

				DIO_u8SetPinValue(DIO_PORTD, DIO_PIN5, DIO_LOW);
				DIO_u8SetPinValue(DIO_PORTC, DIO_PIN2, DIO_HIGH);
				DIO_u8SetPinValue(DIO_PORTC, DIO_PIN3, DIO_LOW);

				cv = 4;
				CLCD_voidSendCommand(0x01);
				CLCD_voidSendString("open ^_^");
				flag = 1;
				_delay_ms(150);
				while (flag == 1) {
					CLCD_voidSendCommand(0x01);
					CLCD_voidSendString("1:led on 2:led");
					CLCD_voidGoToXY(1, 0);
					CLCD_voidSendString("off 0:back");
					do {
						value = KPD_u8GetPressedKey();
						SPI_voidTransmit(0);
					} while (value == KPD_NO_PRESSED_KEY);
					if (value == 0) {
						flag = 0;
						start = 0;
					} else if (value == 1 || value == 2) {
						SPI_voidTransmit(value);
					}
				}

			} else {

				//led
				DIO_u8SetPinValue(DIO_PORTC, DIO_PIN2, DIO_LOW);
				DIO_u8SetPinValue(DIO_PORTC, DIO_PIN3, DIO_HIGH);
				CLCD_voidSendCommand(0x01);
				if (cv < 4) {
					CLCD_voidSendString("TRY AGAIN");
					DIO_u8SetPinDir(DIO_PORTD, DIO_PIN7, DIO_PIN_OUT);
					SET_BIT(PORTD, 7);
					_delay_ms(500);
					CLCD_voidSendCommand(0x01);
					DIO_u8SetPinDir(DIO_PORTD, DIO_PIN7, DIO_PIN_IN);
					CLEAR_BIT(PORTD, 7);
					start=0;
				} else {

					CLCD_voidSendString("wrong password");
					CLCD_voidGoToXY(1, 7);
					CLCD_voidSendString("-_-");
					DIO_u8SetPinDir(DIO_PORTD, DIO_PIN7, DIO_PIN_OUT);
					SET_BIT(PORTD, 7);
					EEPROM_write(0x100, 0x00);
					block = EEPROM_read(0x100);
					_delay_ms(150);
					cv = 1;
				}

			}

		}

	}
}
ISR(TIMER0_OVF_vect) {
	static u16 a = 0;
	a++;
	if (a == 3907) {
		TCNT0 = 192;
		a = 0;
		if (block != 0xff) {
			// CLCD_voidSendCommand(0x01);
			CLCD_voidGoToXY(1, 0);
			CLCD_voidSendString("wait 30s!!!");
			DIO_u8SetPinDir(DIO_PORTD, DIO_PIN7, DIO_PIN_IN);
			CLEAR_BIT(PORTD, 7);
			_delay_ms(3000);
			if (c== 1)
				c = 1;
			else if (v == 1)
				cv = 1;
			EEPROM_write(0x100, 0xff);
			block = EEPROM_read(0x100);
			CLCD_voidGoToXY(1, 0);
			CLCD_voidSendString("try know");
			start=0;

		}

	}
}


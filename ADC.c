/*
 * ADC.c
 *
 *  Created on: Aug 17, 2023
 *      Author: hp
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"util/delay.h"
#include"ADC.h"
#include<avr/io.h>
void ADC_voidInt()
{
	//reference by 128
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	/*reference voltage as avcc*/
    SET_BIT(ADMUX,REFS0);
    CLEAR_BIT(ADMUX,REFS1);
    /*8 BIT right*/
   CLEAR_BIT(ADMUX,ADLAR);

    /*10 bit  left*/
   // SET_BIT(ADMUX,ADLAR);

    //ENABLE
    SET_BIT(ADCSRA,ADEN);
}
u16 ADC_u16Read(u8 Copy_u8Channed)
{
	//mask
	Copy_u8Channed&=0x07;
	ADMUX&=0xE0;
	ADMUX|=Copy_u8Channed;
//start Conversion
	SET_BIT(ADCSRA,ADSC);
	while(GET_BIT(ADCSRA,ADIF)!=1);
//flag clear //polling
	SET_BIT(ADCSRA,ADIF);
  //8bit
	return ADC;
	//10bit
//	return ADCH;
}

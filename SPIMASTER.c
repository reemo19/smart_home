/*
 * ICPMASTER.c
 *
 *  Created on: Aug 24, 2023
 *      Author: hp
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"

#include <avr/io.h>
void SPI_voidMasterInit()
{
	//enable spi,M-S-select;ect,16clk
	SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_voidSlaveInit()
{
	//enable spi
	SPCR=(1<<SPE);
}
void SPI_voidTransmit(u8 Copu_u8Data)
{
	SPDR=Copu_u8Data;
	while(GET_BIT(SPSR,SPIF)!=1);
}
u8 SPI_voidRecive()
{

	while(GET_BIT(SPSR,SPIF)!=1);
	return SPDR;
}

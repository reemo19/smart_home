/*
 * ICPMASTER.h
 *
 *  Created on: Aug 24, 2023
 *      Author: hp
 */

#ifndef SPIMASTER_H_
#define SPIMASTER_H_

void SPI_voidMasterInit();
void SPI_voidSlaveInit();
void SPI_voidTransmit(u8 Copu_u8Data);
u8 SPI_voidRecive();
#endif /* SPIMASTER_H_ */

/*
 * ITG3205.c
 *
 *  Created on: 2022. 5. 9.
 *      Author: user
 */

#include "ITG3205.h"



void Gyro_Writebyte(uint8_t address, uint8_t data){
	uint8_t Trans[2] = {address, data};

	// |Start bit|AD+W|   |Register Address|   |DATA|   |P|
	// |		 |	  |ACK|				   |ACK|	|ACK| |




	I2C_Transmit(I2C1, ITG3200_ADDR_AD0_LOW, 0x00, 1);
	I2C_Transmit(I2C1, address, Trans, 2);

	LL_I2C_DisableIT_TX(I2C);				// Disable Interrupt

	if(!LL_I2C_IsEnabled(I2C)){				// Enable I2C
		LL_I2C_Enable(I2C);
	}
	LL_I2C_DisableBitPOS(I2C);				// Disable bit Position

	while(LL_I2C_IsActiveFlag_BUSY(I2C));	// wait for Ready

	LL_I2C_GenerateStartCondition(I2C);		// Start bit

	while(!LL_I2C_IsActiveFlag_SB(I2C));	// wait start bit
	LL_I2C_TransmitData8(I2C, address);		// transmit address

	while(!LL_I2C_IsActiveFlag_ADDR(I2C));	// wait for transmitting address
	LL_I2C_ClearFlag_ADDR(I2C);				// clear address flag

	for(uint16_t i=0; i<size; i++){
		LL_I2C_TransmitData8(I2C, data[i]);	// transmit data array
		while(!LL_I2C_IsActiveFlag_TXE(I2C));	// wait to complete transmitting data
	}
	while(!LL_I2C_IsActiveFlag_BTF(I2C));	// wait Byte Transfer Finished flag.

	LL_I2C_GenerateStopCondition(I2C);		// Stop bit



}

uint8_t Gyro_Readbyte(uint8_t address){
	uint8_t Trans[1] = {address};
	uint8_t Receive[1];

	// |Start bit|AD+W|   |Register Address|   |Start Bit|AD+R|	  |	   |NACK|P|
	// |		 |	  |ACK|				   |ACK|		 |	  |ACK|DATA|   	| |
	I2C_Transmit(I2C1, address, Trans, 1);
	I2C_Receive(I2C1, address, Receive, 1);

	return Receive[0];
}

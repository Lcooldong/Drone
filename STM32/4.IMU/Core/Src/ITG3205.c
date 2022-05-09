/*
 * ITG3205.c
 *
 *  Created on: 2022. 5. 9.
 *      Author: user
 */

#include "ITG3205.h"



void Gyro_Writebyte(ITG3205* itg3205, uint8_t register_address, uint8_t data){
	/////////////////////////////////////////////////////////
	// |Start bit|AD+W|   |Register Address|   |DATA|   |P|//
	// |		 |	  |ACK|				   |ACK|	|ACK| |//
	/////////////////////////////////////////////////////////
	uint8_t Trans[2] = {register_address, data};

	I2C_Transmit(&(itg3205->I2C), itg3205->gyro_address, Trans, 2);

}

uint8_t Gyro_Readbyte(ITG3205* itg3205, uint8_t register_address){
	/////////////////////////////////////////////////////////////////////////////
	// |Start bit|AD+W|   |Register Address|   |Start Bit|AD+R|	  |	   |NACK|P|//
	// |		 |	  |ACK|				   |ACK|		 |	  |ACK|DATA|   	| |//
	/////////////////////////////////////////////////////////////////////////////
	uint8_t Trans[1] = {register_address};
	uint8_t Receive[1];

	I2C_Transmit(&(itg3205->I2C), itg3205->gyro_address, Trans, 1);
	I2C_Receive(&(itg3205->I2C), itg3205->gyro_address, Receive, 1);

	return Receive[0];
}



void Gyro_Init(ITG3205* itg3205, I2C_TypeDef* i2c){

	itg3205->I2C.I2C = i2c;
	itg3205->I2C.i2c_busy = 0;
	itg3205->I2C.i2c_IsRx = 0;

	printf("Gyro_Init -> GET : 0x%X\r\n", itg3205->gyro_address);

    Gyro_Writebyte(itg3205,PWR_MGM,0x00);

    LL_mDelay(10);
    Gyro_Writebyte(itg3205, PWR_MGM,0x01);

    Gyro_Writebyte(itg3205, SMPLRT_DIV,0X00);

    Gyro_Writebyte(itg3205, DLPFFS_FS_SEL, RANGE2000 << 3);

    Gyro_Writebyte(itg3205, DLPFFS_DLPF_CFG, BW256_SR8);

    Gyro_Writebyte(itg3205, PWRMGM_CLK_SEL, PLL_ZGYRO_REF);

    Gyro_Writebyte(itg3205, INTCFG_ITG_RDY_EN, INTSTATUS_ITG_RDY);

    Gyro_Writebyte(itg3205, INTCFG_RAW_RDY_EN, INTSTATUS_RAW_DATA_RDY);

    LL_mDelay(GYROSTART_UP_DELAY);


}







































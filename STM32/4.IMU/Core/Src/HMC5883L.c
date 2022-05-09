/*
 * HMC5883L.c
 *
 *  Created on: 2022. 5. 9.
 *      Author: user
 */

#ifndef INC_HMC5883L_H_
#include "HMC5883L.h"
#endif

void Magneto_Writebyte(HMC5883L* hmc5883l, uint8_t register_address, uint8_t data)
{
    uint8_t Trans[2]={register_address, data};
    I2C_Transmit(&(hmc5883l->I2C), hmc5883l->compass_address, Trans,2);
}

uint8_t Magneto_Readbyte(HMC5883L * hmc5883l, uint8_t register_address)
{
    uint8_t Trans[1]={register_address};
    uint8_t Receive[1];

    I2C_Transmit(&(hmc5883l->I2C), hmc5883l->compass_address,Trans,1);
    I2C_Receive(&(hmc5883l->I2C), hmc5883l->compass_address, Receive,1);

    if(LL_I2C_IsActiveFlag_RXNE(hmc5883l->I2C.I2C)|LL_I2C_IsActiveFlag_BUSY(hmc5883l->I2C.I2C))	// not empty, busy
    {
    	hmc5883l->status = 0;
    	hmc5883l->error_code = 1;

    	//while(HAL_I2C_GetState(&(hmc5883l->i2c)) != HAL_I2C_STATE_READY);
    }


    return Receive[0];
}

void Magneto_Init(HMC5883L* hmc5883l, float gauss)
{
	hmc5883l->error_code = SetScale(hmc5883l, gauss);
	if(hmc5883l->error_code == 1)
	{
		printf("Set Scale Error.\r\n");
	}
	hmc5883l->error_code = SetMeasurementMode(hmc5883l, Measurement_Continuous);
	if(hmc5883l->error_code == 1)
	{
		printf("Set Mode Error.\r\n");
	}

}

uint8_t SetScale(HMC5883L* hmc5883l, float gauss)
{
	uint8_t regValue = 0x00;
	if(gauss == 0.88)
	{
		regValue = 0x00;
		hmc5883l->m_Scale = 0.73;
	}
	else if(gauss == 1.3)
	{
		regValue = 0x01;
		hmc5883l->m_Scale = 0.92;
	}
	else if(gauss == 1.9)
	{
		regValue = 0x02;
		hmc5883l->m_Scale = 1.22;
	}
	else if(gauss == 2.5)
	{
		regValue = 0x03;
		hmc5883l->m_Scale = 1.52;
	}
	else if(gauss == 4.0)
	{
		regValue = 0x04;
		hmc5883l->m_Scale = 2.27;
	}
	else if(gauss == 4.7)
	{
		regValue = 0x05;
		hmc5883l->m_Scale = 2.56;
	}
	else if(gauss == 5.6)
	{
		regValue = 0x06;
		hmc5883l->m_Scale = 3.03;
	}
	else if(gauss == 8.1)
	{
		regValue = 0x07;
		hmc5883l->m_Scale = 4.35;
	}
	else
		return ErrorCode_1_Num;

	regValue = regValue << 5;
	Magneto_Writebyte(hmc5883l, ConfigurationRegisterB, regValue);

	return regValue;
}


uint8_t SetMeasurementMode(HMC5883L* hmc5883l , uint8_t mode)
{
	Magneto_Writebyte(hmc5883l, ModeRegister, mode);
	if((mode == 0x00) | (mode == 0x01) | (mode == 0x03)) return 0;
	else return ErrorCode_1_Num;

}

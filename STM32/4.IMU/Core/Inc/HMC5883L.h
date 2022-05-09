/*
 * HMC5883L.h
 *
 *  Created on: 2022. 5. 9.
 *      Author: user
 */

#ifndef __MAIN_H
#include "main.h"
#endif

#ifndef __I2C_H__
#include "I2C.h"
#endif

#ifndef _MATH_H_
#include "math.h"
#endif

#include "stdio.h"


#ifndef INC_HMC5883L_H_
#define INC_HMC5883L_H_



#define HMC5883L_Address 0x1E
#define ConfigurationRegisterA 0x00
#define ConfigurationRegisterB 0x01
#define ModeRegister 0x02
#define DataRegisterBegin 0x03

#define Measurement_Continuous 0x00
#define Measurement_SingleShot 0x01
#define Measurement_Idle 0x03

#define ErrorCode_1 "Entered scale was not valid, valid gauss values are: 0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1"
#define ErrorCode_1_Num 1

typedef struct __HMC5883L{
	I2C_struct I2C;
	uint8_t compass_address;

	float m_Scale;

	uint8_t status;
	uint8_t error_code;
}HMC5883L;

uint8_t SetScale(HMC5883L* hmc5883l, float gauss);
uint8_t SetMeasurementMode(HMC5883L* hmc5883l , uint8_t mode);

#endif /* INC_HMC5883L_H_ */

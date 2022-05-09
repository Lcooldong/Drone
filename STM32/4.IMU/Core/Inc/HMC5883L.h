/*
 * HMC5883L.h
 *
 *  Created on: 2022. 5. 9.
 *      Author: user
 */

#ifndef INC_HMC5883L_H_
#define INC_HMC5883L_H_

#include "main.h"

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



#endif /* INC_HMC5883L_H_ */

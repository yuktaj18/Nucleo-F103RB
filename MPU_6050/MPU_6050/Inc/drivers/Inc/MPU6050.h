/*
 * MPU6050.h
 *
 *  Created on: 24-Jan-2026
 *      Author: yukta
 */



#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_


#include "stm32f103xx.h"
#include <string.h>
#include <math.h>

extern I2C_Handle_t pI2CHandle;

#define MpuSlaveAddress				0x68

#define SMPLRT_DIV 					0x19
#define CONFIG						0x1A
#define	GYRO_CONFIG					0x1B
#define	ACCEL_CONFIG				0x1C
#define	FIFO_EN						0x23
#define INT_PIN_CONFIG				0x37
#define	INT_ENABLE					0x38
#define	INT_STATUS					0x3A
#define	ACCEL_XOUT_H				0x3B
#define	ACCEL_YOUT_H				0x3D
#define ACCEL_ZOUT_H				0x3F
#define	TEMP_OUT_H					0x41
#define GYRO_XOUT_H					0x43
#define GYRO_YOUT_H					0x45
#define	GYRO_ZOUT_H					0x47
#define SIGNAL_PATH_RESET			0x68
#define USER_CTRL					0x6A
#define PWR_MGMT_1					0x6B
#define PWR_MGMT_2					0x6C
#define FIFO_COUNT_H				0x72
#define FIFO_COUNT_L				0x73
#define FIFO_R_W					0x74
#define WHO_AM_I					0x75

//MPU Config

typedef struct
{
	uint8_t ClockSource;
	uint8_t GyroFullScale;
	uint8_t AccelFullScale;
	uint8_t ConfigDLPF;
	uint8_t SampleRate;
	uint8_t SleepModeCtrl;
	uint8_t ExtFsync;

}MPU_Config;

//Power clock sorce
enum MpuClkSrc_ENUM
{
	    InternalOscillator_8Mhz   = 0x00,
		PLL_XG   				  = 0x01,
		PLL_YG 					  = 0x02,
		PLL_ZG 					  = 0x03,
		PLL_32KHz		 	      = 0x04,
		PLL_19Mhz				  = 0x05,
		ResetGeneartor 			  = 0x07



};
//Enum Config for DLPF

enum DLPF_CFG_ENUM
{
	    DLPF_260A_256G_Hz   = 0x00,
		DLPF_184A_188G_Hz   = 0x01,
		DLPF_94A_98G_Hz 	= 0x02,
		DLPF_44A_42G_Hz 	= 0x03,
		DLPF_21A_20G_Hz 	= 0x04,
		DLPF_10_Hz 			= 0x05,
		DLPF_5_Hz 			= 0x06



};

//EXT_FSYNC_Bit_Location enum
enum EXT_FSYNC_Bit_Location
{

	Input_Disable		=0x00,
	 TEMP_OUT_L			=0x01,
	 GYRO_XOUT_L		=0x02,
	 GYRO_YOUT_L		=0x03,
	 GYRO_ZOUT_L		=0x04,
	 ACCEL_XOUT_L		=0x05,
	 ACCEL_YOUT_L		=0x06,
	 ACCEL_ZOUT_L		=0x07

};

//Gyro Full Scale Enum


enum GYRO_FSEL
{

	GYRO_SCALE_RANGE_250		=0x00,
	GYRO_SCALE_RANGE_500		=0x01,
	GYRO_SCALE_RANGE_1000		=0x02,
	GYRO_SCALE_RANGE_2000		=0x03

};

//Accelometer Full Scale Enum

enum Accelo_FSEL
{

	ACCEL_SCALE_RANGE_2g		=0x00,
	ACCEL_SCALE_RANGE_4g		=0x01,
	ACCEL_SCALE_RANGE_8g		=0x02,
	ACCEL_SCALE_RANGE_16g		=0x03

};


//Raw Data Accelometer
typedef struct
{
	int16_t x_accel;
	int16_t y_accel;
	int16_t z_accel;


}RawData_Handle_Accelometer;

//Raw Data Gyroscope
typedef struct
{
	int16_t x_gyro;
	int16_t y_gyro;
	int16_t z_gyro;


}RawData_Handle_Gyrometer;



//Scaled Data Accelometer

typedef struct
{

	float x_scaled_accel;
	float y_scaled_accel;
	float z_scaled_accel;



}ScaledData_Handle_Accelometer;

//Scaled Data Accelometer

typedef struct
{

	float x_scaled_gyro;
	float y_scaled_gyro;
	float z_scaled_gyro;



}ScaledData_Handle_Gyrometer;


//Device Identity
void DeviceIdentity(uint8_t MPU_Addr,uint8_t Reg_Addr);

void MPU6050_Init(MPU_Config *MPU_Config);

void MPU6050_GetRawData(RawData_Handle_Accelometer *rawDataAccel,RawData_Handle_Gyrometer *rawDataGyro);

void MPU6050_GetScaledData(ScaledData_Handle_Accelometer *ScaledDataAccel,ScaledData_Handle_Gyrometer *ScaledDataGyro);


#endif /* INC_MPU6050_H_ */

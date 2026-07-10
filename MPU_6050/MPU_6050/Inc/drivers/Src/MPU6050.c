/*
 * MPU6050.c
 *
 *  Created on: 25-Jan-2026
 *      Author: yukta
 */


#include <MPU6050.h>


extern I2C_Handle_t I2C1_Handle;

uint8_t RxBuffer =0 ;

uint8_t TxBuffer =0;


float AccelScalingFactor,GyroScalingFactor;

static void delay()
{

	for(uint32_t i = 0 ; i < 500000/2 ; i ++);


}


//verify device
//here device id is slave address according to ado logic 0x68 for ad0 at low and 0x69 for ad0 at high
void DeviceIdentity(uint8_t MPU_Addr,uint8_t Reg_Addr)
{
	I2C_MasterReceiveData_OneByteMem(&I2C1_Handle, &RxBuffer, MPU_Addr,Reg_Addr);
}


void MPU6050_Init(MPU_Config *MPU_Config)
{
//Get device information
	DeviceIdentity(MpuSlaveAddress,WHO_AM_I);

//Reset the device
	TxBuffer =0;
	TxBuffer = 0x80;
	I2C_MasterOneByteSendMem(&I2C1_Handle,&TxBuffer,MpuSlaveAddress,PWR_MGMT_1);


//Config the clock source
	TxBuffer =0;
	TxBuffer |= (MPU_Config->ClockSource & 0x07);
	TxBuffer |= ((MPU_Config->SleepModeCtrl << 6) & 0x40);
	I2C_MasterOneByteSendMem(&I2C1_Handle,&TxBuffer,MpuSlaveAddress,PWR_MGMT_1);


//Config the dlpf

	TxBuffer =0;
	TxBuffer |= (MPU_Config->ConfigDLPF & 0x07);
	I2C_MasterOneByteSendMem(&I2C1_Handle,&TxBuffer,MpuSlaveAddress,CONFIG);


//Config Gyro full scale range

	TxBuffer =0;
	TxBuffer |= ((MPU_Config->GyroFullScale<<3) & 0x18);
	I2C_MasterOneByteSendMem(&I2C1_Handle,&TxBuffer,MpuSlaveAddress,GYRO_CONFIG);


//Config Accel full scale range

		TxBuffer =0;
		TxBuffer |= ((MPU_Config->AccelFullScale<<3) & 0x18);
		I2C_MasterOneByteSendMem(&I2C1_Handle,&TxBuffer,MpuSlaveAddress,ACCEL_CONFIG);

//Config Sample Rate

		TxBuffer =0;
		TxBuffer |= MPU_Config->SampleRate;
		I2C_MasterOneByteSendMem(&I2C1_Handle,&TxBuffer,MpuSlaveAddress,SMPLRT_DIV);


		switch (MPU_Config->AccelFullScale)
		{
			case ACCEL_SCALE_RANGE_2g :
			AccelScalingFactor = (2000.0f/32768.0f);
			break;

			case ACCEL_SCALE_RANGE_4g :
			AccelScalingFactor = (4000.0f/32768.0f);
			break;

			case ACCEL_SCALE_RANGE_8g :
			AccelScalingFactor = (8000.0f/32768.0f);
			break;

			case ACCEL_SCALE_RANGE_16g :
			AccelScalingFactor = (16000.0f/32768.0f);
			break;

			default :
			break;

		}

		switch(MPU_Config->GyroFullScale)
		{

			case GYRO_SCALE_RANGE_250 :
			GyroScalingFactor = (250.0f/32768.0f);
			break;

			case GYRO_SCALE_RANGE_500 :
			GyroScalingFactor = (500.0f/32768.0f);
			break;

			case GYRO_SCALE_RANGE_1000 :
			GyroScalingFactor = (1000.0f/32768.0f);
			break;

			case GYRO_SCALE_RANGE_2000 :
			GyroScalingFactor = (2000.0f/32768.0f);
			break;


			default :
			break;

		}

}



void MPU6050_GetRawData(RawData_Handle_Accelometer *rawDataAccel,RawData_Handle_Gyrometer *rawDataGyro)
{
  uint8_t state;

  uint8_t AccelArr[6],GyroArr[6];

  I2C_MasterReceiveData_OneByteMem(&I2C1_Handle, &state, MpuSlaveAddress, INT_STATUS);

  if((state && 0x01))
  {
	  I2C_MasterReceiveData_MultiByteMem(&I2C1_Handle, AccelArr, MpuSlaveAddress, ACCEL_XOUT_H, 6);

	  rawDataAccel->x_accel = ((AccelArr[0]<<8)|AccelArr[1]);
	  rawDataAccel->y_accel = ((AccelArr[2]<<8)|AccelArr[3]);
	  rawDataAccel->z_accel = ((AccelArr[4]<<8)|AccelArr[5]);



	  I2C_MasterReceiveData_MultiByteMem(&I2C1_Handle, GyroArr, MpuSlaveAddress, GYRO_XOUT_H, 6);

	  rawDataGyro->x_gyro = ((GyroArr[0]<<8)|GyroArr[1]);
	  rawDataGyro->y_gyro = ((GyroArr[2]<<8)|GyroArr[3]);
	  rawDataGyro->z_gyro = ((GyroArr[4]<<8)|GyroArr[5]);

  }

}


void MPU6050_GetScaledData(ScaledData_Handle_Accelometer *ScaledDataAccel,ScaledData_Handle_Gyrometer *ScaledDataGyro)
{

	RawData_Handle_Accelometer getRawDataAccel;
	RawData_Handle_Gyrometer   getRawDataGyro;

	MPU6050_GetRawData(&getRawDataAccel,&getRawDataGyro);



	ScaledDataAccel->x_scaled_accel = (float)((getRawDataAccel.x_accel* AccelScalingFactor)/1000);
	ScaledDataAccel->y_scaled_accel = (float)((getRawDataAccel.y_accel* AccelScalingFactor)/1000);
	ScaledDataAccel->z_scaled_accel = (float)((getRawDataAccel.z_accel* AccelScalingFactor)/1000);

	ScaledDataGyro->x_scaled_gyro   = (float)((getRawDataGyro.x_gyro * GyroScalingFactor )/1000);
	ScaledDataGyro->y_scaled_gyro   = (float)((getRawDataGyro.y_gyro * GyroScalingFactor )/1000);
	ScaledDataGyro->z_scaled_gyro   = (float)((getRawDataGyro.z_gyro * GyroScalingFactor )/1000);


}





/*
 * 008_I2C_ArduinoMasterSend.c
 *
 *  Created on: 28-Dec-2025
 *      Author: yukta
 */
/*
 * I2C PINS
 * PB8 - SCL
 * PB9 - SDA
 *
 *
 *
 */
#include <MPU6050.h>
# include "stm32f103xx.h"
# include <string.h>
# include <stdio.h>



 I2C_Handle_t I2C1_Handle;
MPU_Config mpu6050;

RawData_Handle_Accelometer rawDataaccel;
RawData_Handle_Gyrometer rawDatagyro;

ScaledData_Handle_Accelometer accel_scaled_data;
ScaledData_Handle_Gyrometer gyro_scaled_data;

USART_Handle_t USART2_Config;



int _write(int file, char *ptr, int len)
{
 (void)file;
 int DataIdx;


 for (DataIdx = 0; DataIdx < len; DataIdx++)
 {
   while(!(USART2->USART_SR & USART_TXE_FLAG));

   USART2->USART_DR = (uint8_t)ptr[DataIdx];
 }
 return len;
}




void delay()
{
	for (volatile uint32_t i =0; i < 500000/2 ;i++);
}

void I2C1_Handle_Init (void)
{

	I2C1_Handle.pI2Cx =I2C_1 ;
	I2C1_Handle.I2C_Config.I2C_ReMap = 1;
	I2C1_Handle.I2C_Config.I2C_ACKControl = I2C_ACK_EN;
	I2C1_Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1_Handle.I2C_Config.I2C_SCLSpeed = I2C_SCLSpeed_STD;
	I2C1_Handle.I2C_Config.I2C_DeviceAddress=0x61;

	I2C_Init(&I2C1_Handle);

}



void I2C1_Handle_GPIO_Init(void)
{
	GPIO_Handle_t I2C1_Handle_Pin;

	I2C1_Handle_Pin.pGPIOx = GPIOB;
	I2C1_Handle_Pin.GPIO_PinConfig.GPIO_AFIOControl =1;
	I2C1_Handle_Pin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN_OpenDrain ;

	//SCL
	I2C1_Handle_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GPIO_Init(&I2C1_Handle_Pin);


	//SDA
	I2C1_Handle_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&I2C1_Handle_Pin);

}

void PressButton()
{
		GPIO_Handle_t GpioBtn;

		GpioBtn.pGPIOx = GPIOA ;
		GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN_PullUpDwn;
		GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8 ;
		GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PinPullUp_ODR;

		GPIO_Init(&GpioBtn);



}

void MPU6050_Config()
{

	mpu6050.AccelFullScale = ACCEL_SCALE_RANGE_4g;
	mpu6050.ClockSource = InternalOscillator_8Mhz;
	mpu6050.ConfigDLPF = DLPF_184A_188G_Hz;
	mpu6050.GyroFullScale = GYRO_SCALE_RANGE_500;
	mpu6050.SampleRate = 4 ;

	MPU6050_Init(&mpu6050);

}

void USART2_GPIOInit()
{

	 //PA2 -Tx
	 //PA3 -Rx

	GPIO_Handle_t USART_Pin;


	//Tx
	USART_Pin.pGPIOx = GPIOA ;
	USART_Pin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN_PushPull ;
	USART_Pin.GPIO_PinConfig.GPIO_PinNumber = 2 ;
	GPIO_Init(&USART_Pin);

	//Rx
	USART_Pin.pGPIOx = GPIOA ;
	USART_Pin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN_Float ;
	USART_Pin.GPIO_PinConfig.GPIO_PinNumber = 3 ;
	GPIO_Init(&USART_Pin);
}

void USART2_Init()
{


 USART2_Config.pUSARTx = USART2;
 USART2_Config.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
 USART2_Config.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
 USART2_Config.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
 USART2_Config.USART_Config.USART_NoOfStopBits= USART_STOPBITS_1;
 USART2_Config.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
 USART2_Config.USART_Config.USART_BaudRate = USART_STD_BAUD_115200;

 USART_Init(&USART2_Config);

}


int main (void)
{


//Enable I2C1_Handle peripheral pins
I2C1_Handle_GPIO_Init();
//Config usart pin
USART2_GPIOInit();
// Config USART
USART2_Init();
//Enable USART()
USART_PeripheralControl(USART2, 1);
//Enable I2C Configuration
I2C1_Handle_Init();
//Enable I2C CR1 Enable bit
EnableI2C(I2C_1,1);

//Config Mpu via I2C
MPU6050_Config();


while(1)
{

	MPU6050_GetScaledData(&accel_scaled_data, &gyro_scaled_data);
	printf("Accel: X = %.2f Y = %.2f Z = %.2f\r\n", accel_scaled_data.x_scaled_accel, accel_scaled_data.y_scaled_accel, accel_scaled_data.z_scaled_accel);
	printf("=================================\r\n");
	printf("Gyro: X = %.2f Y = %.2f Z = %.2f\r\n", gyro_scaled_data.x_scaled_gyro, gyro_scaled_data.y_scaled_gyro, gyro_scaled_data.z_scaled_gyro);
	printf("=================================\r\n");
	delay();

}

return 0;
}

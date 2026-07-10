# Nucleo-F103RB

## Overview

This repository contains low-level peripheral drivers developed for the **STM32F103RB** microcontroller on the **STM32 Nucleo-F103RB** development board.

The project implements register-level drivers for commonly used peripherals including **GPIO, RCC, SPI, I2C, and USART**, without relying on STM32 HAL libraries. It is intended as a learning resource for understanding the STM32F1 architecture and embedded driver development.

The repository also includes an **MPU6050 interface library** and several example applications demonstrating peripheral communication with external hardware.

---

## Features

- Register-level peripheral drivers
- GPIO driver
- RCC (Clock) driver
- SPI driver
- I2C driver
- USART driver
- External interrupt (EXTI) support
- MPU6050 sensor interface
- Example applications for each peripheral
- Developed and tested using **STM32CubeIDE**

---

## Drivers Implemented

| Peripheral | Header | Source |
|------------|--------|--------|
| GPIO | `drivers/Inc/stm32f103xx_gpio_driver.h` | `drivers/Src/stm32f103xx_gpio_driver.c` |
| RCC | `drivers/Inc/stm32f103xx_rcc_driver.h` | `drivers/Src/stm32f103xx_rcc_driver.c` |
| SPI | `drivers/Inc/stm32f103xx_spi_driver.h` | `drivers/Src/stm32f103xx_spi_driver.c` |
| I2C | `drivers/Inc/stm32f103xx_i2c_driver.h` | `drivers/Src/stm32f103xx_i2c_driver.c` |
| USART | `drivers/Inc/stm32f103xx_usart_driver.h` | `drivers/Src/stm32f103xx_usart_driver.c` |

The common MCU register definitions, peripheral base addresses, and utility macros are available in:

```text
drivers/Inc/stm32f103xx.h
```

---

# Demonstrations

## MPU6050 Demonstration

<p align="center">
  <img src="media/MPU6050.gif" width="700">
</p>

---

## Logic Analyzer Output (Sigrok)

<p align="center">
  <img src="media/image.png" width="800">
</p>

---

## Example Applications (`Src/`)

| File | Description | Demo |
|------|-------------|------|
| `001_LedBlink.c` | Toggle the on-board LED using the GPIO driver. | [🎥 Video](https://github.com/user-attachments/assets/54fc14a5-6183-47e0-9a7a-f529a35130f1) |
| `002_ButtonLedInterface.c` | Read the on-board push button and control the on-board LED. | - |
| `003_ExternalButtonLedInterface.c` | Interface an external push button to control an LED. | - |
| `004_ButtonLedInterruptInterface.c` | Toggle the LED using GPIO external interrupts (EXTI). | - |
| `005_SPI_SendDataTesting.c` | Basic SPI communication test. | - |
| `006_ArduinoSPISendOnly.c` | SPI Master (STM32) transmitting data to an Arduino SPI Slave. | - |
| `007_UARTSend.c` | USART transmission to a serial terminal (e.g., PuTTY). | - |
| `008_I2C_ArduinoMasterSend.c` | I2C Master (STM32) communicating with an Arduino I2C Slave. | - |

---

## Additional Demonstration Videos

Complete hardware demonstrations are available here:

📹 https://drive.google.com/drive/folders/1PlHLK_qdBC3YYLz9OHBDXSHNoAvFO0gn

---

## Project Structure

```text
Nucleo-F103RB/
│
├── drivers/
│   ├── Inc/
│   │   ├── stm32f103xx.h
│   │   ├── stm32f103xx_gpio_driver.h
│   │   ├── stm32f103xx_rcc_driver.h
│   │   ├── stm32f103xx_spi_driver.h
│   │   ├── stm32f103xx_i2c_driver.h
│   │   └── stm32f103xx_usart_driver.h
│   │
│   └── Src/
│       ├── stm32f103xx_gpio_driver.c
│       ├── stm32f103xx_rcc_driver.c
│       ├── stm32f103xx_spi_driver.c
│       ├── stm32f103xx_i2c_driver.c
│       └── stm32f103xx_usart_driver.c
│
├── Src/
│   ├── 001_LedBlink.c
│   ├── 002_ButtonLedInterface.c
│   ├── 003_ExternalButtonLedInterface.c
│   ├── 004_ButtonLedInterruptInterface.c
│   ├── 005_SPI_SendDataTesting.c
│   ├── 006_ArduinoSPISendOnly.c
│   ├── 007_UARTSend.c
│   └── 008_I2C_ArduinoMasterSend.c
│
├── MPU6050/
│   ├── Inc/
│   └── Src/
│
├── Startup/
│   └── startup_stm32f103rbtx.s
│
├── media/
│   ├── MPU6050.gif
│   └── image.png
│
├── STM32F103RBTX_FLASH.ld
└── README.md
```

---

## Development Environment

- STM32 Nucleo-F103RB
- STM32CubeIDE
- STM32F103RB Microcontroller
- Sigrok Logic Analyzer
- PuTTY (USART Testing)
- Arduino Uno (SPI/I2C Communication)
- MPU6050 IMU Sensor

---

## Notes

- This project is intended for educational purposes and embedded systems learning.
- Drivers are implemented using direct register access without STM32 HAL.
- Additional peripherals and example applications will be added over time.

---

## License

This project is released under the MIT License. Feel free to use, modify, and extend it for educational and personal projects.

# Nucleo-F103RB
driver library from scratch in embedded C for stm32f103 microcontroller

Implementation of  driver libraries to configure Nucleo-F103RB registers and 
implement various API's like read from pin, write to pin, interrupt control,commuincation protocol ,etc. from scratch in embedded C using stm32 cube ide.
The implementation is in progress , will be updating the project.
Here is the drive link for video demonstration of the example code.
https://drive.google.com/drive/u/1/folders/1PlHLK_qdBC3YYLz9OHBDXSHNoAvFO0gn

## Overview

This project implements low-level drivers for core STM32F103 peripherals, exposing a small, consistent API (init/de-init, read/write, interrupt configuration, flag status, etc.) similar in spirit to a hand-rolled HAL. It's built and debugged using **STM32CubeIDE**.

A video demonstration of the example applications running on hardware is available [here](https://drive.google.com/drive/u/1/folders/1PlHLK_qdBC3YYLz9OHBDXSHNoAvFO0gn).

## Drivers implemented

| Peripheral | Header | Source |
|---|---|---|
| GPIO | `drivers/Inc/stm32f103xx_gpio_driver.h` | `drivers/Src/stm32f103xx_gpio_driver.c` |
| RCC (clocks) | `drivers/Inc/stm32f103xx_rcc_driver.h` | `drivers/Src/stm32f103xx_rcc_driver.c` |
| SPI | `drivers/Inc/stm32f103xx_spi_driver.h` | `drivers/Src/stm32f103xx_spi_driver.c` |
| I2C | `drivers/Inc/stm32f103xx_i2c_driver.h` | `drivers/Src/stm32f103xx_i2c_driver.c` |
| USART | `drivers/Inc/stm32f103xx_usart_driver.h` | `drivers/Src/stm32f103xx_usart_driver.c` |

Each driver exposes functions for peripheral clock control, initialization/de-initialization, data transfer, flag/status checks, and (where applicable) interrupt configuration and handling — for example `GPIO_Init`, `GPIO_ReadFromInputPin`, `SPI_SendData`, `I2C_MasterSendData`, `USART_SendData`, `USART_ReceiveDataIT`, `*_IRQInterruptConfig`, `*_IRQHandling`.

Common register definitions and base addresses for the MCU live in `drivers/Inc/stm32f103xx.h`.

## Example applications (`Src/`)

| File | Description |
|---|---|
| `001_LedBlink.c` | Toggle an on-board LED using the GPIO driver |
| `002_ButtonLedInterface.c` | Read a button (on-board) and drive an LED accordingly |
| `003_ExternalButtonLedInterface.c` | Same as above using an external button |
| `004_ButtonLedInterruptInterface.c` | Button-triggered LED toggling using GPIO interrupts (EXTI) |
| `005_SPI_SendDataTesting.c` | Basic SPI data transmission test |
| `006_ArduinoSPISendOnly.c` | SPI master send to an Arduino slave |
| `007_UARTSend.c` | USART transmission, viewable via a serial terminal (e.g. PuTTY) |
| `008_I2C_ArduinoMasterSend.c` | I2C master send to an Arduino slave |

## Project structure

```
stm32f1xx_drivers/
├── drivers/
│   ├── Inc/          # Driver headers + MCU register definitions (stm32f103xx.h)
│   └── Src/           # Driver implementations (GPIO, RCC, SPI, I2C, USART)
├── Src/                # Example/application source files
├── Startup/            # Startup assembly file (startup_stm32f103rbtx.s)
├── STM32F103RBTX_FLASH.ld   # Linker script
└── Debug/              # STM32CubeIDE build output (objects, .elf, .map, makefiles)
```

## Hardware

- **Board:** ST Nucleo-F103RB
- **MCU:** STM32F103RB (Arm Cortex-M3)

## Getting started

### Prerequisites

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- ST-Link drivers/tools (bundled with STM32CubeIDE) for flashing/debugging
- A serial terminal (e.g. PuTTY) for the USART example
- An Arduino board for the SPI/I2C slave examples

### Build & flash

1. Clone the repository:
   ```bash
   git clone https://github.com/yuktaj18/Nucleo-F103RB.git
   ```
2. Open **STM32CubeIDE** and import `stm32f1xx_drivers` as an existing project (`File → Import → Existing Projects into Workspace`).
3. In `Src/`, keep only the example `.c` file you want to run active in the build 
4. Build the project.
5. Connect the Nucleo-F103RB via USB and flash/debug using the built-in ST-Link.

## Notes

- These drivers directly manipulate peripheral registers as defined in `stm32f103xx.h`; no ST HAL/LL libraries are used.
- The I2C example uses `PB8` (SCL) and `PB9` (SDA).
- This is a learning/reference project and is under active development — APIs may change as new peripherals and features are added.

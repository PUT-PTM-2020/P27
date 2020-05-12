################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/VL53L0X/core/src/vl53l0x_api.c \
../Lib/VL53L0X/core/src/vl53l0x_api_calibration.c \
../Lib/VL53L0X/core/src/vl53l0x_api_core.c \
../Lib/VL53L0X/core/src/vl53l0x_api_ranging.c \
../Lib/VL53L0X/core/src/vl53l0x_api_strings.c 

OBJS += \
./Lib/VL53L0X/core/src/vl53l0x_api.o \
./Lib/VL53L0X/core/src/vl53l0x_api_calibration.o \
./Lib/VL53L0X/core/src/vl53l0x_api_core.o \
./Lib/VL53L0X/core/src/vl53l0x_api_ranging.o \
./Lib/VL53L0X/core/src/vl53l0x_api_strings.o 

C_DEPS += \
./Lib/VL53L0X/core/src/vl53l0x_api.d \
./Lib/VL53L0X/core/src/vl53l0x_api_calibration.d \
./Lib/VL53L0X/core/src/vl53l0x_api_core.d \
./Lib/VL53L0X/core/src/vl53l0x_api_ranging.d \
./Lib/VL53L0X/core/src/vl53l0x_api_strings.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/VL53L0X/core/src/vl53l0x_api.o: ../Lib/VL53L0X/core/src/vl53l0x_api.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/core/inc" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S/Inc" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/platform/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/VL53L0X/core/src/vl53l0x_api.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/VL53L0X/core/src/vl53l0x_api_calibration.o: ../Lib/VL53L0X/core/src/vl53l0x_api_calibration.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/core/inc" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S/Inc" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/platform/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/VL53L0X/core/src/vl53l0x_api_calibration.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/VL53L0X/core/src/vl53l0x_api_core.o: ../Lib/VL53L0X/core/src/vl53l0x_api_core.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/core/inc" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S/Inc" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/platform/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/VL53L0X/core/src/vl53l0x_api_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/VL53L0X/core/src/vl53l0x_api_ranging.o: ../Lib/VL53L0X/core/src/vl53l0x_api_ranging.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/core/inc" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S/Inc" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/platform/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/VL53L0X/core/src/vl53l0x_api_ranging.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/VL53L0X/core/src/vl53l0x_api_strings.o: ../Lib/VL53L0X/core/src/vl53l0x_api_strings.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/core/inc" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S/Inc" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/platform/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/VL53L0X/core/src/vl53l0x_api_strings.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


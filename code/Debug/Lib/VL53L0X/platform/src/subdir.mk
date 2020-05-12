################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/VL53L0X/platform/src/vl53l0x_platform.c \
../Lib/VL53L0X/platform/src/vl53l0x_platform_log.c 

OBJS += \
./Lib/VL53L0X/platform/src/vl53l0x_platform.o \
./Lib/VL53L0X/platform/src/vl53l0x_platform_log.o 

C_DEPS += \
./Lib/VL53L0X/platform/src/vl53l0x_platform.d \
./Lib/VL53L0X/platform/src/vl53l0x_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/VL53L0X/platform/src/vl53l0x_platform.o: ../Lib/VL53L0X/platform/src/vl53l0x_platform.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/core/inc" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S/Inc" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/platform/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/VL53L0X/platform/src/vl53l0x_platform.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/VL53L0X/platform/src/vl53l0x_platform_log.o: ../Lib/VL53L0X/platform/src/vl53l0x_platform_log.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/core/inc" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S/Inc" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/VL53L0X/platform/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/VL53L0X/platform/src/vl53l0x_platform_log.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


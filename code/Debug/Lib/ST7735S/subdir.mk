################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/ST7735S/ST7735S.c \
../Lib/ST7735S/ST7735S_dev_config.c 

OBJS += \
./Lib/ST7735S/ST7735S.o \
./Lib/ST7735S/ST7735S_dev_config.o 

C_DEPS += \
./Lib/ST7735S/ST7735S.d \
./Lib/ST7735S/ST7735S_dev_config.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/ST7735S/ST7735S.o: ../Lib/ST7735S/ST7735S.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/ST7735S/ST7735S.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/ST7735S/ST7735S_dev_config.o: ../Lib/ST7735S/ST7735S_dev_config.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/ST7735S/ST7735S_dev_config.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/ST7735S/Fonts/font12.c \
../Lib/ST7735S/Fonts/font16.c \
../Lib/ST7735S/Fonts/font20.c \
../Lib/ST7735S/Fonts/font24.c \
../Lib/ST7735S/Fonts/font8.c 

OBJS += \
./Lib/ST7735S/Fonts/font12.o \
./Lib/ST7735S/Fonts/font16.o \
./Lib/ST7735S/Fonts/font20.o \
./Lib/ST7735S/Fonts/font24.o \
./Lib/ST7735S/Fonts/font8.o 

C_DEPS += \
./Lib/ST7735S/Fonts/font12.d \
./Lib/ST7735S/Fonts/font16.d \
./Lib/ST7735S/Fonts/font20.d \
./Lib/ST7735S/Fonts/font24.d \
./Lib/ST7735S/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/ST7735S/Fonts/font12.o: ../Lib/ST7735S/Fonts/font12.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/ST7735S/Fonts/font12.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/ST7735S/Fonts/font16.o: ../Lib/ST7735S/Fonts/font16.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/ST7735S/Fonts/font16.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/ST7735S/Fonts/font20.o: ../Lib/ST7735S/Fonts/font20.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/ST7735S/Fonts/font20.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/ST7735S/Fonts/font24.o: ../Lib/ST7735S/Fonts/font24.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/ST7735S/Fonts/font24.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Lib/ST7735S/Fonts/font8.o: ../Lib/ST7735S/Fonts/font8.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Programowanie/STM/ptm-machine/code/Lib/ST7735S" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Lib/ST7735S/Fonts/font8.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


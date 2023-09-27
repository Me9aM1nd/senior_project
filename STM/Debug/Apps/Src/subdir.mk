################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Apps/Src/dev_trace.c \
../Apps/Src/hal_driver_def.c \
../Apps/Src/hal_gpio.c \
../Apps/Src/hrspo2_converter.c \
../Apps/Src/max30102_for_stm32_hal.c 

OBJS += \
./Apps/Src/dev_trace.o \
./Apps/Src/hal_driver_def.o \
./Apps/Src/hal_gpio.o \
./Apps/Src/hrspo2_converter.o \
./Apps/Src/max30102_for_stm32_hal.o 

C_DEPS += \
./Apps/Src/dev_trace.d \
./Apps/Src/hal_driver_def.d \
./Apps/Src/hal_gpio.d \
./Apps/Src/hrspo2_converter.d \
./Apps/Src/max30102_for_stm32_hal.d 


# Each subdirectory must supply rules for building sources it contributes
Apps/Src/%.o Apps/Src/%.su: ../Apps/Src/%.c Apps/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/universiteti/Senior project/senior_project/STM/Apps/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Apps-2f-Src

clean-Apps-2f-Src:
	-$(RM) ./Apps/Src/dev_trace.d ./Apps/Src/dev_trace.o ./Apps/Src/dev_trace.su ./Apps/Src/hal_driver_def.d ./Apps/Src/hal_driver_def.o ./Apps/Src/hal_driver_def.su ./Apps/Src/hal_gpio.d ./Apps/Src/hal_gpio.o ./Apps/Src/hal_gpio.su ./Apps/Src/hrspo2_converter.d ./Apps/Src/hrspo2_converter.o ./Apps/Src/hrspo2_converter.su ./Apps/Src/max30102_for_stm32_hal.d ./Apps/Src/max30102_for_stm32_hal.o ./Apps/Src/max30102_for_stm32_hal.su

.PHONY: clean-Apps-2f-Src


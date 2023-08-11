################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Apps/Src/max30102_for_stm32_hal.c \
../Apps/Src/stm32f1xx_it.c 

OBJS += \
./Apps/Src/max30102_for_stm32_hal.o \
./Apps/Src/stm32f1xx_it.o 

C_DEPS += \
./Apps/Src/max30102_for_stm32_hal.d \
./Apps/Src/stm32f1xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Apps/Src/%.o Apps/Src/%.su: ../Apps/Src/%.c Apps/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/user/Desktop/P/Senior project/senior_project/STM/Apps/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Apps-2f-Src

clean-Apps-2f-Src:
	-$(RM) ./Apps/Src/max30102_for_stm32_hal.d ./Apps/Src/max30102_for_stm32_hal.o ./Apps/Src/max30102_for_stm32_hal.su ./Apps/Src/stm32f1xx_it.d ./Apps/Src/stm32f1xx_it.o ./Apps/Src/stm32f1xx_it.su

.PHONY: clean-Apps-2f-Src


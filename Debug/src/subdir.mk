################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Camera_control.c \
../src/GPIO_config.c \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/usart.c 

OBJS += \
./src/Camera_control.o \
./src/GPIO_config.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/usart.o 

C_DEPS += \
./src/Camera_control.d \
./src/GPIO_config.d \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F411VETx -DSTM32F411E_DISCO -DDEBUG -DSTM32F411xE -DUSE_STDPERIPH_DRIVER -I"E:/STM32 Projects/OV7670_standard_peripheral/StdPeriph_Driver/inc" -I"E:/STM32 Projects/OV7670_standard_peripheral/inc" -I"E:/STM32 Projects/OV7670_standard_peripheral/CMSIS/device" -I"E:/STM32 Projects/OV7670_standard_peripheral/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



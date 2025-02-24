################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timebase.c \
../Src/uart.c 

OBJS += \
./Src/gpio.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timebase.o \
./Src/uart.o 

C_DEPS += \
./Src/gpio.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timebase.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32L031K6Tx -DSTM32 -DSTM32L0 -c -I../Inc -I"C:/uc_STM32L0Workspace/stm32L0Bootloader/ChipHeaders/CMSIS/Include" -I"C:/uc_STM32L0Workspace/stm32L0Bootloader/ChipHeaders/CMSIS/Device/STM32L0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timebase.d ./Src/timebase.o ./Src/timebase.su ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src


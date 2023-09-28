################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC1_HMI_ECU.c \
../app.c \
../gpio.c \
../keypad.c \
../lcd.c \
../timer1.c \
../uart.c 

OBJS += \
./MC1_HMI_ECU.o \
./app.o \
./gpio.o \
./keypad.o \
./lcd.o \
./timer1.o \
./uart.o 

C_DEPS += \
./MC1_HMI_ECU.d \
./app.d \
./gpio.d \
./keypad.d \
./lcd.d \
./timer1.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



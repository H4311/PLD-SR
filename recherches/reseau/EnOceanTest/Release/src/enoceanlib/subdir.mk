################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/enoceanlib/EnOceanPort.c \
../src/enoceanlib/EnOceanPortTest.c \
../src/enoceanlib/TCM120.c \
../src/enoceanlib/cssl.c 

OBJS += \
./src/enoceanlib/EnOceanPort.o \
./src/enoceanlib/EnOceanPortTest.o \
./src/enoceanlib/TCM120.o \
./src/enoceanlib/cssl.o 

C_DEPS += \
./src/enoceanlib/EnOceanPort.d \
./src/enoceanlib/EnOceanPortTest.d \
./src/enoceanlib/TCM120.d \
./src/enoceanlib/cssl.d 


# Each subdirectory must supply rules for building sources it contributes
src/enoceanlib/%.o: ../src/enoceanlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



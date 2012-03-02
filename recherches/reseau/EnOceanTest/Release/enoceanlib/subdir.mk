################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../enoceanlib/EnOceanPort.c \
../enoceanlib/EnOceanPortTest.c \
../enoceanlib/TCM120.c \
../enoceanlib/cssl.c 

OBJS += \
./enoceanlib/EnOceanPort.o \
./enoceanlib/EnOceanPortTest.o \
./enoceanlib/TCM120.o \
./enoceanlib/cssl.o 

C_DEPS += \
./enoceanlib/EnOceanPort.d \
./enoceanlib/EnOceanPortTest.d \
./enoceanlib/TCM120.d \
./enoceanlib/cssl.d 


# Each subdirectory must supply rules for building sources it contributes
enoceanlib/%.o: ../enoceanlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



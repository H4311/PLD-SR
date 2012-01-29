################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Trash/EnOceanDevice.cpp \
../src/Trash/EnOceanDevice_TempHumi.cpp 

OBJS += \
./src/Trash/EnOceanDevice.o \
./src/Trash/EnOceanDevice_TempHumi.o 

CPP_DEPS += \
./src/Trash/EnOceanDevice.d \
./src/Trash/EnOceanDevice_TempHumi.d 


# Each subdirectory must supply rules for building sources it contributes
src/Trash/%.o: ../src/Trash/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



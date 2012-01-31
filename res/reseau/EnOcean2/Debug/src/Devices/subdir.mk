################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Devices/DeviceTable.cpp \
../src/Devices/EnOceanDevice.cpp \
../src/Devices/EnOceanDevice_TempHumi.cpp \
../src/Devices/EnOceanSensorAPI.cpp 

OBJS += \
./src/Devices/DeviceTable.o \
./src/Devices/EnOceanDevice.o \
./src/Devices/EnOceanDevice_TempHumi.o \
./src/Devices/EnOceanSensorAPI.o 

CPP_DEPS += \
./src/Devices/DeviceTable.d \
./src/Devices/EnOceanDevice.d \
./src/Devices/EnOceanDevice_TempHumi.d \
./src/Devices/EnOceanSensorAPI.d 


# Each subdirectory must supply rules for building sources it contributes
src/Devices/%.o: ../src/Devices/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Simulator/Sensors/SensorSimulator.cpp \
../src/Simulator/Sensors/SensorSimulatorTempHumi.cpp 

OBJS += \
./src/Simulator/Sensors/SensorSimulator.o \
./src/Simulator/Sensors/SensorSimulatorTempHumi.o 

CPP_DEPS += \
./src/Simulator/Sensors/SensorSimulator.d \
./src/Simulator/Sensors/SensorSimulatorTempHumi.d 


# Each subdirectory must supply rules for building sources it contributes
src/Simulator/Sensors/%.o: ../src/Simulator/Sensors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



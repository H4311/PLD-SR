################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Simulator/EnOCeanBaseSimulator.cpp \
../src/Simulator/ServerSimulator.cpp 

OBJS += \
./src/Simulator/EnOCeanBaseSimulator.o \
./src/Simulator/ServerSimulator.o 

CPP_DEPS += \
./src/Simulator/EnOCeanBaseSimulator.d \
./src/Simulator/ServerSimulator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Simulator/%.o: ../src/Simulator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



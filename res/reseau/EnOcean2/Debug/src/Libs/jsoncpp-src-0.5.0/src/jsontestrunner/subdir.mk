################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Libs/jsoncpp-src-0.5.0/src/jsontestrunner/main.cpp 

OBJS += \
./src/Libs/jsoncpp-src-0.5.0/src/jsontestrunner/main.o 

CPP_DEPS += \
./src/Libs/jsoncpp-src-0.5.0/src/jsontestrunner/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/Libs/jsoncpp-src-0.5.0/src/jsontestrunner/%.o: ../src/Libs/jsoncpp-src-0.5.0/src/jsontestrunner/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



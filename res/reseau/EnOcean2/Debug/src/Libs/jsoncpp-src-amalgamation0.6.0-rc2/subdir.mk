################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Libs/jsoncpp-src-amalgamation0.6.0-rc2/jsoncpp.cpp 

OBJS += \
./src/Libs/jsoncpp-src-amalgamation0.6.0-rc2/jsoncpp.o 

CPP_DEPS += \
./src/Libs/jsoncpp-src-amalgamation0.6.0-rc2/jsoncpp.d 


# Each subdirectory must supply rules for building sources it contributes
src/Libs/jsoncpp-src-amalgamation0.6.0-rc2/%.o: ../src/Libs/jsoncpp-src-amalgamation0.6.0-rc2/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



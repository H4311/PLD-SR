################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EnOceanClient/EnOceanAnalyser.cpp \
../src/EnOceanClient/EnOceanReceptor.cpp \
../src/EnOceanClient/Receptor.cpp \
../src/EnOceanClient/ServerSettings.cpp \
../src/EnOceanClient/TCPServer.cpp 

OBJS += \
./src/EnOceanClient/EnOceanAnalyser.o \
./src/EnOceanClient/EnOceanReceptor.o \
./src/EnOceanClient/Receptor.o \
./src/EnOceanClient/ServerSettings.o \
./src/EnOceanClient/TCPServer.o 

CPP_DEPS += \
./src/EnOceanClient/EnOceanAnalyser.d \
./src/EnOceanClient/EnOceanReceptor.d \
./src/EnOceanClient/Receptor.d \
./src/EnOceanClient/ServerSettings.d \
./src/EnOceanClient/TCPServer.d 


# Each subdirectory must supply rules for building sources it contributes
src/EnOceanClient/%.o: ../src/EnOceanClient/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



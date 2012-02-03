################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Bdd/mysqlinsert.c \
../src/Bdd/test.c 

OBJS += \
./src/Bdd/mysqlinsert.o \
./src/Bdd/test.o 

C_DEPS += \
./src/Bdd/mysqlinsert.d \
./src/Bdd/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/Bdd/%.o: ../src/Bdd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



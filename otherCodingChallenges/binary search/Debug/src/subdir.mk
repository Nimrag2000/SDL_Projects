################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/binary\ search.c 

OBJS += \
./src/binary\ search.o 

C_DEPS += \
./src/binary\ search.d 


# Each subdirectory must supply rules for building sources it contributes
src/binary\ search.o: ../src/binary\ search.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/binary search.d" -MT"src/binary\ search.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



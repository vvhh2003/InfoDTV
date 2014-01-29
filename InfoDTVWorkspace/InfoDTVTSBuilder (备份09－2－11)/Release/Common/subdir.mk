################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Common/CodeConverter.cpp \
../Common/TSPacketStruct.cpp 

OBJS += \
./Common/CodeConverter.o \
./Common/TSPacketStruct.o 

CPP_DEPS += \
./Common/CodeConverter.d \
./Common/TSPacketStruct.d 


# Each subdirectory must supply rules for building sources it contributes
Common/%.o: ../Common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



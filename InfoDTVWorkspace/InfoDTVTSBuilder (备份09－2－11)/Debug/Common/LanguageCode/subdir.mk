################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Common/LanguageCode/UTFTOGB2312.cpp 

OBJS += \
./Common/LanguageCode/UTFTOGB2312.o 

CPP_DEPS += \
./Common/LanguageCode/UTFTOGB2312.d 


# Each subdirectory must supply rules for building sources it contributes
Common/LanguageCode/%.o: ../Common/LanguageCode/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



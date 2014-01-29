################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PSIDynamicDataProvider/PSIDynamicDataProvider.cpp \
../PSIDynamicDataProvider/PSIDynamicDataProviderFactory.cpp 

OBJS += \
./PSIDynamicDataProvider/PSIDynamicDataProvider.o \
./PSIDynamicDataProvider/PSIDynamicDataProviderFactory.o 

CPP_DEPS += \
./PSIDynamicDataProvider/PSIDynamicDataProvider.d \
./PSIDynamicDataProvider/PSIDynamicDataProviderFactory.d 


# Each subdirectory must supply rules for building sources it contributes
PSIDynamicDataProvider/%.o: ../PSIDynamicDataProvider/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVPSIDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



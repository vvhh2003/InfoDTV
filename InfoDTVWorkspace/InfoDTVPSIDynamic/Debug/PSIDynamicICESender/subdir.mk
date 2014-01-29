################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PSIDynamicICESender/PSIDynamicICESender.cpp 

OBJS += \
./PSIDynamicICESender/PSIDynamicICESender.o 

CPP_DEPS += \
./PSIDynamicICESender/PSIDynamicICESender.d 


# Each subdirectory must supply rules for building sources it contributes
PSIDynamicICESender/%.o: ../PSIDynamicICESender/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVPSIDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



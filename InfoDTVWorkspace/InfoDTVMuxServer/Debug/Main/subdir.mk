################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Main/InfoDTVMuxServer.cpp 

OBJS += \
./Main/InfoDTVMuxServer.o 

CPP_DEPS += \
./Main/InfoDTVMuxServer.d 


# Each subdirectory must supply rules for building sources it contributes
Main/%.o: ../Main/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



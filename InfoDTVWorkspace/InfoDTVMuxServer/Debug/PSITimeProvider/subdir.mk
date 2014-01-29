################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/PSITime.Provider/PSITimeDataProvider.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/PSITime.Provider/PSITimeDataProviderFactory.cpp 

OBJS += \
./PSITimeProvider/PSITimeDataProvider.o \
./PSITimeProvider/PSITimeDataProviderFactory.o 

CPP_DEPS += \
./PSITimeProvider/PSITimeDataProvider.d \
./PSITimeProvider/PSITimeDataProviderFactory.d 


# Each subdirectory must supply rules for building sources it contributes
PSITimeProvider/PSITimeDataProvider.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/PSITime.Provider/PSITimeDataProvider.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

PSITimeProvider/PSITimeDataProviderFactory.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/PSITime.Provider/PSITimeDataProviderFactory.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



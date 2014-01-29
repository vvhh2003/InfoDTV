################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/PSIDynamicDataProvider/PSIDynamicDataProvider.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/PSIDynamicDataProvider/PSIDynamicDataProviderFactory.cpp 

OBJS += \
./DataProviders/PSIDynamicDataProvider/PSIDynamicDataProvider.o \
./DataProviders/PSIDynamicDataProvider/PSIDynamicDataProviderFactory.o 

CPP_DEPS += \
./DataProviders/PSIDynamicDataProvider/PSIDynamicDataProvider.d \
./DataProviders/PSIDynamicDataProvider/PSIDynamicDataProviderFactory.d 


# Each subdirectory must supply rules for building sources it contributes
DataProviders/PSIDynamicDataProvider/PSIDynamicDataProvider.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/PSIDynamicDataProvider/PSIDynamicDataProvider.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

DataProviders/PSIDynamicDataProvider/PSIDynamicDataProviderFactory.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/PSIDynamicDataProvider/PSIDynamicDataProviderFactory.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



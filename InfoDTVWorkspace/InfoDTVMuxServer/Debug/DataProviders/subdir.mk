################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/SimpleTSFileDataProvider.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/SimpleTSFileDataProviderFactory.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/TSFilterOutFileDataProvider.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/TSFilterOutFileDataProviderFactory.cpp 

OBJS += \
./DataProviders/SimpleTSFileDataProvider.o \
./DataProviders/SimpleTSFileDataProviderFactory.o \
./DataProviders/TSFilterOutFileDataProvider.o \
./DataProviders/TSFilterOutFileDataProviderFactory.o 

CPP_DEPS += \
./DataProviders/SimpleTSFileDataProvider.d \
./DataProviders/SimpleTSFileDataProviderFactory.d \
./DataProviders/TSFilterOutFileDataProvider.d \
./DataProviders/TSFilterOutFileDataProviderFactory.d 


# Each subdirectory must supply rules for building sources it contributes
DataProviders/SimpleTSFileDataProvider.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/SimpleTSFileDataProvider.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

DataProviders/SimpleTSFileDataProviderFactory.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/SimpleTSFileDataProviderFactory.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

DataProviders/TSFilterOutFileDataProvider.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/TSFilterOutFileDataProvider.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

DataProviders/TSFilterOutFileDataProviderFactory.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/TSFilterOutFileDataProviderFactory.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/AntiDebug.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/CircularBuffer.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/CodeConverter.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/TSPacketStruct.cpp 

OBJS += \
./Common/AntiDebug.o \
./Common/CircularBuffer.o \
./Common/CodeConverter.o \
./Common/TSPacketStruct.o 

CPP_DEPS += \
./Common/AntiDebug.d \
./Common/CircularBuffer.d \
./Common/CodeConverter.d \
./Common/TSPacketStruct.d 


# Each subdirectory must supply rules for building sources it contributes
Common/AntiDebug.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/AntiDebug.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/CircularBuffer.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/CircularBuffer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/CodeConverter.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/CodeConverter.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/TSPacketStruct.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/TSPacketStruct.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



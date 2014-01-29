################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/MuxRuntimeConfig.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/SoftMultiplexer.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/TSChannelStream.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/TSDataPrepThread.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/TSMuxChannelStreams.cpp 

OBJS += \
./Multiplexer/MuxRuntimeConfig.o \
./Multiplexer/SoftMultiplexer.o \
./Multiplexer/TSChannelStream.o \
./Multiplexer/TSDataPrepThread.o \
./Multiplexer/TSMuxChannelStreams.o 

CPP_DEPS += \
./Multiplexer/MuxRuntimeConfig.d \
./Multiplexer/SoftMultiplexer.d \
./Multiplexer/TSChannelStream.d \
./Multiplexer/TSDataPrepThread.d \
./Multiplexer/TSMuxChannelStreams.d 


# Each subdirectory must supply rules for building sources it contributes
Multiplexer/MuxRuntimeConfig.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/MuxRuntimeConfig.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Multiplexer/SoftMultiplexer.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/SoftMultiplexer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Multiplexer/TSChannelStream.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/TSChannelStream.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Multiplexer/TSDataPrepThread.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/TSDataPrepThread.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Multiplexer/TSMuxChannelStreams.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/TSMuxChannelStreams.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/DTAPI/Include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



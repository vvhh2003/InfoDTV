################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/UDP/UDPRateLimiter.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/UDP/UDPTSBroadcast.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/UDP/UDPTSBroadcastThread.cpp 

OBJS += \
./Multiplexer/UDP/UDPRateLimiter.o \
./Multiplexer/UDP/UDPTSBroadcast.o \
./Multiplexer/UDP/UDPTSBroadcastThread.o 

CPP_DEPS += \
./Multiplexer/UDP/UDPRateLimiter.d \
./Multiplexer/UDP/UDPTSBroadcast.d \
./Multiplexer/UDP/UDPTSBroadcastThread.d 


# Each subdirectory must supply rules for building sources it contributes
Multiplexer/UDP/UDPRateLimiter.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/UDP/UDPRateLimiter.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Multiplexer/UDP/UDPTSBroadcast.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/UDP/UDPTSBroadcast.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Multiplexer/UDP/UDPTSBroadcastThread.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/UDP/UDPTSBroadcastThread.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



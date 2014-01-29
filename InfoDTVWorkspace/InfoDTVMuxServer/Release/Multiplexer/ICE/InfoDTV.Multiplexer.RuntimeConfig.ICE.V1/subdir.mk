################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICEMuxOnlyRuntimeConfiger.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/MultiplexerRuntimeConfigICE.cpp 

OBJS += \
./Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICEMuxOnlyRuntimeConfiger.o \
./Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/MultiplexerRuntimeConfigICE.o 

CPP_DEPS += \
./Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICEMuxOnlyRuntimeConfiger.d \
./Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/MultiplexerRuntimeConfigICE.d 


# Each subdirectory must supply rules for building sources it contributes
Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICEMuxOnlyRuntimeConfiger.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICEMuxOnlyRuntimeConfiger.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/MultiplexerRuntimeConfigICE.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/MultiplexerRuntimeConfigICE.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



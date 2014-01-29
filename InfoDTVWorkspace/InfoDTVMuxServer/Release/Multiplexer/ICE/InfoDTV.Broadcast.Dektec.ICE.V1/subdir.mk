################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/BroadcastController.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/ICEBroadcastController.cpp 

OBJS += \
./Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/BroadcastController.o \
./Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/ICEBroadcastController.o 

CPP_DEPS += \
./Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/BroadcastController.d \
./Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/ICEBroadcastController.d 


# Each subdirectory must supply rules for building sources it contributes
Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/BroadcastController.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/BroadcastController.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/ICEBroadcastController.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Multiplexer/ICE/InfoDTV.Broadcast.Dektec.ICE.V1/ICEBroadcastController.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



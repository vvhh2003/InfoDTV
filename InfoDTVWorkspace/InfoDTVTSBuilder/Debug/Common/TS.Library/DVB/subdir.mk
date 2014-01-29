################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/TS.Library/DVB/DefaultPSICrc32Counter.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/TS.Library/DVB/DefaultPSIDataStream.cpp 

OBJS += \
./Common/TS.Library/DVB/DefaultPSICrc32Counter.o \
./Common/TS.Library/DVB/DefaultPSIDataStream.o 

CPP_DEPS += \
./Common/TS.Library/DVB/DefaultPSICrc32Counter.d \
./Common/TS.Library/DVB/DefaultPSIDataStream.d 


# Each subdirectory must supply rules for building sources it contributes
Common/TS.Library/DVB/DefaultPSICrc32Counter.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/TS.Library/DVB/DefaultPSICrc32Counter.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/TS.Library/DVB/DefaultPSIDataStream.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/TS.Library/DVB/DefaultPSIDataStream.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



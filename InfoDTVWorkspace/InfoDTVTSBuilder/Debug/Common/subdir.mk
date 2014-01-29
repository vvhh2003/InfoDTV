################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/CircularBuffer.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/CodeConverter.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/TSPacketStruct.cpp 

OBJS += \
./Common/CircularBuffer.o \
./Common/CodeConverter.o \
./Common/TSPacketStruct.o 

CPP_DEPS += \
./Common/CircularBuffer.d \
./Common/CodeConverter.d \
./Common/TSPacketStruct.d 


# Each subdirectory must supply rules for building sources it contributes
Common/CircularBuffer.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/CircularBuffer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/CodeConverter.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/CodeConverter.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/TSPacketStruct.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common/TSPacketStruct.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/Common" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/XMLBINProcessor/PSIXMLBINProcessor.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/XMLBINProcessor/VBitStream.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/XMLBINProcessor/XMLBINProcessor.cpp 

OBJS += \
./XMLBINProcessor/PSIXMLBINProcessor.o \
./XMLBINProcessor/VBitStream.o \
./XMLBINProcessor/XMLBINProcessor.o 

CPP_DEPS += \
./XMLBINProcessor/PSIXMLBINProcessor.d \
./XMLBINProcessor/VBitStream.d \
./XMLBINProcessor/XMLBINProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
XMLBINProcessor/PSIXMLBINProcessor.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/XMLBINProcessor/PSIXMLBINProcessor.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVPSIDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

XMLBINProcessor/VBitStream.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/XMLBINProcessor/VBitStream.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVPSIDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

XMLBINProcessor/XMLBINProcessor.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/XMLBINProcessor/XMLBINProcessor.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVPSIDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



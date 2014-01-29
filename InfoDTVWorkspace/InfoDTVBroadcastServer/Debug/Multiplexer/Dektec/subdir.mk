################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Multiplexer/Dektec/DektecTSBroadcast.cpp \
../Multiplexer/Dektec/DektecTSBroadcastThread.cpp 

OBJS += \
./Multiplexer/Dektec/DektecTSBroadcast.o \
./Multiplexer/Dektec/DektecTSBroadcastThread.o 

CPP_DEPS += \
./Multiplexer/Dektec/DektecTSBroadcast.d \
./Multiplexer/Dektec/DektecTSBroadcastThread.d 


# Each subdirectory must supply rules for building sources it contributes
Multiplexer/Dektec/%.o: ../Multiplexer/Dektec/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



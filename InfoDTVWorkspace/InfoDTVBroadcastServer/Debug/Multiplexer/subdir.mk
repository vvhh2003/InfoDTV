################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Multiplexer/MuxRuntimeConfig.cpp \
../Multiplexer/SoftMultiplexer.cpp \
../Multiplexer/TSChannelStream.cpp \
../Multiplexer/TSDataPrepThread.cpp \
../Multiplexer/TSMuxChannelStreams.cpp 

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
Multiplexer/%.o: ../Multiplexer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Common/TS.Library/DefaultDataCounter.cpp \
../Common/TS.Library/DefaultTSDataStream.cpp \
../Common/TS.Library/DefaultTSPacketDataOperator.cpp \
../Common/TS.Library/DefaultTSStreamDataManager.cpp 

OBJS += \
./Common/TS.Library/DefaultDataCounter.o \
./Common/TS.Library/DefaultTSDataStream.o \
./Common/TS.Library/DefaultTSPacketDataOperator.o \
./Common/TS.Library/DefaultTSStreamDataManager.o 

CPP_DEPS += \
./Common/TS.Library/DefaultDataCounter.d \
./Common/TS.Library/DefaultTSDataStream.d \
./Common/TS.Library/DefaultTSPacketDataOperator.d \
./Common/TS.Library/DefaultTSStreamDataManager.d 


# Each subdirectory must supply rules for building sources it contributes
Common/TS.Library/%.o: ../Common/TS.Library/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



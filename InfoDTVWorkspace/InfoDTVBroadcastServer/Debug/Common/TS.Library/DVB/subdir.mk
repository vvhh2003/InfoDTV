################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Common/TS.Library/DVB/DefaultPSICrc32Counter.cpp \
../Common/TS.Library/DVB/DefaultPSIDataStream.cpp 

OBJS += \
./Common/TS.Library/DVB/DefaultPSICrc32Counter.o \
./Common/TS.Library/DVB/DefaultPSIDataStream.o 

CPP_DEPS += \
./Common/TS.Library/DVB/DefaultPSICrc32Counter.d \
./Common/TS.Library/DVB/DefaultPSIDataStream.d 


# Each subdirectory must supply rules for building sources it contributes
Common/TS.Library/DVB/%.o: ../Common/TS.Library/DVB/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



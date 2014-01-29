################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Common/TS.Library/InfoDTV/DyDoorwayInfoTable.cpp \
../Common/TS.Library/InfoDTV/DyIPInfoTable.cpp \
../Common/TS.Library/InfoDTV/ObjectInfoTable.cpp \
../Common/TS.Library/InfoDTV/ScenarioInfoTable.cpp \
../Common/TS.Library/InfoDTV/ServiceInfoTable.cpp 

OBJS += \
./Common/TS.Library/InfoDTV/DyDoorwayInfoTable.o \
./Common/TS.Library/InfoDTV/DyIPInfoTable.o \
./Common/TS.Library/InfoDTV/ObjectInfoTable.o \
./Common/TS.Library/InfoDTV/ScenarioInfoTable.o \
./Common/TS.Library/InfoDTV/ServiceInfoTable.o 

CPP_DEPS += \
./Common/TS.Library/InfoDTV/DyDoorwayInfoTable.d \
./Common/TS.Library/InfoDTV/DyIPInfoTable.d \
./Common/TS.Library/InfoDTV/ObjectInfoTable.d \
./Common/TS.Library/InfoDTV/ScenarioInfoTable.d \
./Common/TS.Library/InfoDTV/ServiceInfoTable.d 


# Each subdirectory must supply rules for building sources it contributes
Common/TS.Library/InfoDTV/%.o: ../Common/TS.Library/InfoDTV/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



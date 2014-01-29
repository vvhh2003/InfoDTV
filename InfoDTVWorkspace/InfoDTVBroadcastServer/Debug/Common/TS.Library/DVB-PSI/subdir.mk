################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Common/TS.Library/DVB-PSI/PATTable.cpp \
../Common/TS.Library/DVB-PSI/PMTTable.cpp \
../Common/TS.Library/DVB-PSI/PSITable.cpp \
../Common/TS.Library/DVB-PSI/PSITableBuilder.cpp \
../Common/TS.Library/DVB-PSI/PSITableBuilder2.cpp \
../Common/TS.Library/DVB-PSI/SDTTable.cpp \
../Common/TS.Library/DVB-PSI/TDTTable.cpp \
../Common/TS.Library/DVB-PSI/TOTTable.cpp 

OBJS += \
./Common/TS.Library/DVB-PSI/PATTable.o \
./Common/TS.Library/DVB-PSI/PMTTable.o \
./Common/TS.Library/DVB-PSI/PSITable.o \
./Common/TS.Library/DVB-PSI/PSITableBuilder.o \
./Common/TS.Library/DVB-PSI/PSITableBuilder2.o \
./Common/TS.Library/DVB-PSI/SDTTable.o \
./Common/TS.Library/DVB-PSI/TDTTable.o \
./Common/TS.Library/DVB-PSI/TOTTable.o 

CPP_DEPS += \
./Common/TS.Library/DVB-PSI/PATTable.d \
./Common/TS.Library/DVB-PSI/PMTTable.d \
./Common/TS.Library/DVB-PSI/PSITable.d \
./Common/TS.Library/DVB-PSI/PSITableBuilder.d \
./Common/TS.Library/DVB-PSI/PSITableBuilder2.d \
./Common/TS.Library/DVB-PSI/SDTTable.d \
./Common/TS.Library/DVB-PSI/TDTTable.d \
./Common/TS.Library/DVB-PSI/TOTTable.d 


# Each subdirectory must supply rules for building sources it contributes
Common/TS.Library/DVB-PSI/%.o: ../Common/TS.Library/DVB-PSI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../eternity4/dynamic.cpp \
../eternity4/persist.cpp \
../eternity4/persist_xml.cpp \
../eternity4/xmlscanner.cpp \
../eternity4/xmlstring_archive.cpp \
../eternity4/xmlstringscanner.cpp 

OBJS += \
./eternity4/dynamic.o \
./eternity4/persist.o \
./eternity4/persist_xml.o \
./eternity4/xmlscanner.o \
./eternity4/xmlstring_archive.o \
./eternity4/xmlstringscanner.o 

CPP_DEPS += \
./eternity4/dynamic.d \
./eternity4/persist.d \
./eternity4/persist_xml.d \
./eternity4/xmlscanner.d \
./eternity4/xmlstring_archive.d \
./eternity4/xmlstringscanner.d 


# Each subdirectory must supply rules for building sources it contributes
eternity4/%.o: ../eternity4/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



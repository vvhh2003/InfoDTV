################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../XMLBINProcessor/PSIXMLBINProcessor.cpp \
../XMLBINProcessor/VBitStream.cpp \
../XMLBINProcessor/XMLBINProcessor.cpp 

OBJS += \
./XMLBINProcessor/PSIXMLBINProcessor.o \
./XMLBINProcessor/VBitStream.o \
./XMLBINProcessor/XMLBINProcessor.o 

CPP_DEPS += \
./XMLBINProcessor/PSIXMLBINProcessor.d \
./XMLBINProcessor/VBitStream.d \
./XMLBINProcessor/XMLBINProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
XMLBINProcessor/%.o: ../XMLBINProcessor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



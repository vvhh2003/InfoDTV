################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataProviders/SPTSFileDataProvider/PCRPTSProcessor.cpp \
../DataProviders/SPTSFileDataProvider/SPTSFileDataProvider.cpp \
../DataProviders/SPTSFileDataProvider/SPTSFileDataProviderFactory.cpp \
../DataProviders/SPTSFileDataProvider/VBR2CBRProcessor.cpp 

OBJS += \
./DataProviders/SPTSFileDataProvider/PCRPTSProcessor.o \
./DataProviders/SPTSFileDataProvider/SPTSFileDataProvider.o \
./DataProviders/SPTSFileDataProvider/SPTSFileDataProviderFactory.o \
./DataProviders/SPTSFileDataProvider/VBR2CBRProcessor.o 

CPP_DEPS += \
./DataProviders/SPTSFileDataProvider/PCRPTSProcessor.d \
./DataProviders/SPTSFileDataProvider/SPTSFileDataProvider.d \
./DataProviders/SPTSFileDataProvider/SPTSFileDataProviderFactory.d \
./DataProviders/SPTSFileDataProvider/VBR2CBRProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
DataProviders/SPTSFileDataProvider/%.o: ../DataProviders/SPTSFileDataProvider/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



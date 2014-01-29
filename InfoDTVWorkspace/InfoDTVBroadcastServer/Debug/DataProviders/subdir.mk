################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataProviders/SimpleTSFileDataProvider.cpp \
../DataProviders/SimpleTSFileDataProviderFactory.cpp \
../DataProviders/TSFilterOutFileDataProvider.cpp \
../DataProviders/TSFilterOutFileDataProviderFactory.cpp 

OBJS += \
./DataProviders/SimpleTSFileDataProvider.o \
./DataProviders/SimpleTSFileDataProviderFactory.o \
./DataProviders/TSFilterOutFileDataProvider.o \
./DataProviders/TSFilterOutFileDataProviderFactory.o 

CPP_DEPS += \
./DataProviders/SimpleTSFileDataProvider.d \
./DataProviders/SimpleTSFileDataProviderFactory.d \
./DataProviders/TSFilterOutFileDataProvider.d \
./DataProviders/TSFilterOutFileDataProviderFactory.d 


# Each subdirectory must supply rules for building sources it contributes
DataProviders/%.o: ../DataProviders/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



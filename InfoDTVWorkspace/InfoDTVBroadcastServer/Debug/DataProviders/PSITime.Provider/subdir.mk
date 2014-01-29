################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataProviders/PSITime.Provider/PSITimeDataProvider.cpp \
../DataProviders/PSITime.Provider/PSITimeDataProviderFactory.cpp 

OBJS += \
./DataProviders/PSITime.Provider/PSITimeDataProvider.o \
./DataProviders/PSITime.Provider/PSITimeDataProviderFactory.o 

CPP_DEPS += \
./DataProviders/PSITime.Provider/PSITimeDataProvider.d \
./DataProviders/PSITime.Provider/PSITimeDataProviderFactory.d 


# Each subdirectory must supply rules for building sources it contributes
DataProviders/PSITime.Provider/%.o: ../DataProviders/PSITime.Provider/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



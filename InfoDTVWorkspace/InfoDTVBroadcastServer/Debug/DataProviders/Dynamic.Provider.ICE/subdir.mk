################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataProviders/Dynamic.Provider.ICE/BufferReciver.cpp \
../DataProviders/Dynamic.Provider.ICE/BufferTransferI.cpp \
../DataProviders/Dynamic.Provider.ICE/DynamicIPDataProvider.cpp \
../DataProviders/Dynamic.Provider.ICE/DynamicIPDataProviderFactory.cpp \
../DataProviders/Dynamic.Provider.ICE/ICEBufferSender.cpp 

OBJS += \
./DataProviders/Dynamic.Provider.ICE/BufferReciver.o \
./DataProviders/Dynamic.Provider.ICE/BufferTransferI.o \
./DataProviders/Dynamic.Provider.ICE/DynamicIPDataProvider.o \
./DataProviders/Dynamic.Provider.ICE/DynamicIPDataProviderFactory.o \
./DataProviders/Dynamic.Provider.ICE/ICEBufferSender.o 

CPP_DEPS += \
./DataProviders/Dynamic.Provider.ICE/BufferReciver.d \
./DataProviders/Dynamic.Provider.ICE/BufferTransferI.d \
./DataProviders/Dynamic.Provider.ICE/DynamicIPDataProvider.d \
./DataProviders/Dynamic.Provider.ICE/DynamicIPDataProviderFactory.d \
./DataProviders/Dynamic.Provider.ICE/ICEBufferSender.d 


# Each subdirectory must supply rules for building sources it contributes
DataProviders/Dynamic.Provider.ICE/%.o: ../DataProviders/Dynamic.Provider.ICE/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



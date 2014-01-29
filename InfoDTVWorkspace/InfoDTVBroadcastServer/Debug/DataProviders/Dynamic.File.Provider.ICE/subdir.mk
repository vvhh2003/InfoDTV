################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataProviders/Dynamic.File.Provider.ICE/DynICEBufferSender.cpp \
../DataProviders/Dynamic.File.Provider.ICE/DynamicBufferReciver.cpp \
../DataProviders/Dynamic.File.Provider.ICE/DynamicBufferTransferI.cpp \
../DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProvider.cpp \
../DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProviderFactory.cpp \
../DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProviderGlobalConfig.cpp 

OBJS += \
./DataProviders/Dynamic.File.Provider.ICE/DynICEBufferSender.o \
./DataProviders/Dynamic.File.Provider.ICE/DynamicBufferReciver.o \
./DataProviders/Dynamic.File.Provider.ICE/DynamicBufferTransferI.o \
./DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProvider.o \
./DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProviderFactory.o \
./DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProviderGlobalConfig.o 

CPP_DEPS += \
./DataProviders/Dynamic.File.Provider.ICE/DynICEBufferSender.d \
./DataProviders/Dynamic.File.Provider.ICE/DynamicBufferReciver.d \
./DataProviders/Dynamic.File.Provider.ICE/DynamicBufferTransferI.d \
./DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProvider.d \
./DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProviderFactory.d \
./DataProviders/Dynamic.File.Provider.ICE/DynamicFileDataProviderGlobalConfig.d 


# Each subdirectory must supply rules for building sources it contributes
DataProviders/Dynamic.File.Provider.ICE/%.o: ../DataProviders/Dynamic.File.Provider.ICE/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



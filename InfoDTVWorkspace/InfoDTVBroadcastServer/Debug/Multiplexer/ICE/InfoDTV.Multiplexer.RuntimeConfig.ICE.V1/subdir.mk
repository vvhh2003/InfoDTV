################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICERuntimeConfiger.cpp \
../Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/MultiplexerRuntimeConfigICE.cpp 

OBJS += \
./Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICERuntimeConfiger.o \
./Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/MultiplexerRuntimeConfigICE.o 

CPP_DEPS += \
./Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/ICERuntimeConfiger.d \
./Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/MultiplexerRuntimeConfigICE.d 


# Each subdirectory must supply rules for building sources it contributes
Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/%.o: ../Multiplexer/ICE/InfoDTV.Multiplexer.RuntimeConfig.ICE.V1/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



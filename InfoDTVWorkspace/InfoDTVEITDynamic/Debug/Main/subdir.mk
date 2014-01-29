################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Main/InfoDTVEITDynamic.cpp \
../Main/InfoDTVPSIDynamic.cpp 

OBJS += \
./Main/InfoDTVEITDynamic.o \
./Main/InfoDTVPSIDynamic.o 

CPP_DEPS += \
./Main/InfoDTVEITDynamic.d \
./Main/InfoDTVPSIDynamic.d 


# Each subdirectory must supply rules for building sources it contributes
Main/%.o: ../Main/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



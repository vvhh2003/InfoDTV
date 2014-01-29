################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVFileProcesser.cpp \
../InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVObject.cpp \
../InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilder.cpp \
../InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilderManager.cpp \
../InfoDTVDynamicBuilder/InfoDTVFileBuilder/PostIBLProcesser.cpp 

OBJS += \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVFileProcesser.o \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVObject.o \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilder.o \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilderManager.o \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/PostIBLProcesser.o 

CPP_DEPS += \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVFileProcesser.d \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVObject.d \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilder.d \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilderManager.d \
./InfoDTVDynamicBuilder/InfoDTVFileBuilder/PostIBLProcesser.d 


# Each subdirectory must supply rules for building sources it contributes
InfoDTVDynamicBuilder/InfoDTVFileBuilder/%.o: ../InfoDTVDynamicBuilder/InfoDTVFileBuilder/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



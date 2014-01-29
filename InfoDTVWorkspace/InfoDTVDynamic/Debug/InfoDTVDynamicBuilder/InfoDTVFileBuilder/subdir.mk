################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVFileProcesser.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVObject.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilder.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilderManager.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/PostIBLProcesser.cpp 

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
InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVFileProcesser.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVFileProcesser.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVObject.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVObject.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilder.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilder.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilderManager.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/InfoDTVTSBuilderManager.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

InfoDTVDynamicBuilder/InfoDTVFileBuilder/PostIBLProcesser.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/InfoDTVDynamicBuilder/InfoDTVFileBuilder/PostIBLProcesser.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVDynamic/../3rdParts/poco-1.3.3p1/Foundation/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



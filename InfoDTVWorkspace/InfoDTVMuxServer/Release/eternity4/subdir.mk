################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/dynamic.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/persist.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/persist_xml.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/xmlscanner.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/xmlstring_archive.cpp \
/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/xmlstringscanner.cpp 

OBJS += \
./eternity4/dynamic.o \
./eternity4/persist.o \
./eternity4/persist_xml.o \
./eternity4/xmlscanner.o \
./eternity4/xmlstring_archive.o \
./eternity4/xmlstringscanner.o 

CPP_DEPS += \
./eternity4/dynamic.d \
./eternity4/persist.d \
./eternity4/persist_xml.d \
./eternity4/xmlscanner.d \
./eternity4/xmlstring_archive.d \
./eternity4/xmlstringscanner.d 


# Each subdirectory must supply rules for building sources it contributes
eternity4/dynamic.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/dynamic.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eternity4/persist.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/persist.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eternity4/persist_xml.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/persist_xml.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eternity4/xmlscanner.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/xmlscanner.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eternity4/xmlstring_archive.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/xmlstring_archive.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eternity4/xmlstringscanner.o: /home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/eternity4/xmlstringscanner.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/../3rdParts/poco-1.3.3p1/Foundation/include/" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer/DataProviders/Dynamic.File.Provider.ICE" -I"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVBroadcastServer" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



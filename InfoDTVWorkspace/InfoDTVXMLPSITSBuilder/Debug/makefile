################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include XMLBINProcessor/subdir.mk
-include Main/subdir.mk
-include Common/subdir.mk
-include Common/TS.Library/InfoDTV/subdir.mk
-include Common/TS.Library/subdir.mk
-include Common/TS.Library/DVB-PSI/subdir.mk
-include Common/TS.Library/DVB/subdir.mk
-include Common/Log/subdir.mk
-include Common/LanguageCode/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: InfoDTVXMLPSITSBuilder

# Tool invocations
InfoDTVXMLPSITSBuilder: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L"/home/victor/workdisk/InfoDTVWorkspace/InfoDTVXMLPSITSBuilder/../3rdParts/poco-1.3.3p1/lib/Linux/i686" -o"InfoDTVXMLPSITSBuilder" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) InfoDTVXMLPSITSBuilder
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

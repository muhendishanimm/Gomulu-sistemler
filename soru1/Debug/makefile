################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
soru1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
soru1.list \

OBJCOPY_HEX += \
soru1.hex \

OBJCOPY_BIN += \
soru1.bin \


# All Target
all: soru1.elf secondary-outputs

# Tool invocations
soru1.elf: $(OBJS) $(USER_OBJS) C:\Users\aylin\STM32CubeIDE\workspace_1.2.0\soru1\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "soru1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\aylin\STM32CubeIDE\workspace_1.2.0\soru1\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="soru1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

soru1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "soru1.list"
	@echo 'Finished building: $@'
	@echo ' '

soru1.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "soru1.hex"
	@echo 'Finished building: $@'
	@echo ' '

soru1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "soru1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

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
deneme.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
deneme.list \

OBJCOPY_HEX += \
deneme.hex \

OBJCOPY_BIN += \
deneme.bin \


# All Target
all: deneme.elf secondary-outputs

# Tool invocations
deneme.elf: $(OBJS) $(USER_OBJS) C:\Users\aylin\STM32CubeIDE\workspace_1.2.0\deneme\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "deneme.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\aylin\STM32CubeIDE\workspace_1.2.0\deneme\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="deneme.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

deneme.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "deneme.list"
	@echo 'Finished building: $@'
	@echo ' '

deneme.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "deneme.hex"
	@echo 'Finished building: $@'
	@echo ' '

deneme.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "deneme.bin"
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

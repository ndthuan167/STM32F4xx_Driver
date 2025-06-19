# Target file
TARGET = main

# Arm GCC directory
ARM_GCC_DIRS := C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.2 rel1/bin/
ARM_GCC = $(ARM_GCC_DIRS)arm-none-eabi-gcc
ARM_GCC_ASM = $(ARM_GCC_DIRS)arm-none-eabi-as
ARM_GCC_LINKER = $(ARM_GCC_DIRS)arm-none-eabi-ld

#Arm Object cpy to hex file directory
OBJECT_CPY_DIRS := C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.2 rel1/bin/
OBJCPY = $(OBJECT_CPY_DIRS)arm-none-eabi-objcopy

# Directory for object copy to create hex file from elf file
OBJECT_CPY_DIRS := C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.2 rel1/arm-none-eabi/bin
OBJCPY = $(OBJECT_CPY_DIRS)/objcopy

# Peripheral directory
PERIPHERAL = Peripheral
OUTPUT_DIR = OBJ

# Projects sources
SRC_C_FILES = main.c
SRC_C_FILES += $(PERIPHERAL)/GPIO/GPIO.c
SRC_C_FILES += $(PERIPHERAL)/RCC/RCC.c
SRC_C_FILES += $(PERIPHERAL)/SystemTimer/Systick.c
SRC_C_FILES += $(PERIPHERAL)/Timer/Timer.c
SRC_C_FILES += $(PERIPHERAL)/USART/USART.c
SRC_C_FILES += $(PERIPHERAL)/SPI/SPI.c
SRC_C_FILES += $(PERIPHERAL)/I2C/I2C.c
SRC_C_FILES += $(PERIPHERAL)/DMA/DMA.c
SRC_C_FILES += $(PERIPHERAL)/CAN/CAN.c
SRC_C_FILES += $(PERIPHERAL)/ADC/ADC.c
SRC_C_FILES += $(PERIPHERAL)/EXTI/EXTI.c
SRC_C_FILES += $(PERIPHERAL)/NVIC/NVIC.c
SRC_C_FILES += StartupCode/STM32F407_Startup.c
SRC_C_FILES += syscalls.c

# Include header file
INC_H_FILES = -I$(PERIPHERAL)/GPIO/
INC_H_FILES += -I$(PERIPHERAL)/RCC/
INC_H_FILES += -I$(PERIPHERAL)/System
INC_H_FILES += -I$(PERIPHERAL)/Timer/
INC_H_FILES += -I$(PERIPHERAL)/USART/
INC_H_FILES += -I$(PERIPHERAL)/SPI/
INC_H_FILES += -I$(PERIPHERAL)/I2C/
INC_H_FILES += -I$(PERIPHERAL)/DMA/
INC_H_FILES += -I$(PERIPHERAL)/CAN/
INC_H_FILES += -I$(PERIPHERAL)/ADC/
INC_H_FILES += -I$(PERIPHERAL)/EXTI/
INC_H_FILES += -I$(PERIPHERAL)/NVIC/


# Option compile for Arm GCC compiler
CHIP:= cortex-m4
OPTIMIZE := O0
LINKER_FILE := LinkerFile/Linker_script.ld
ENDIAN := mlittle-endian

COMPILE_ARM_GCC_OPTION= -c -mcpu=$(CHIP) -mthumb -$(ENDIAN) -std=gnu11 -$(OPTIMIZE) $(INC_H_FILES)


# Option Linking for Arm GCC compiler
MAP_FILE = STM32F407.map
LINKING_ARM_OPTION= -T $(LINKER_FILE) -Wl,-Map=$(OUTPUT_DIR)/$(MAP_FILE)

## Compile
CFILES_OBJ = $(SRC_C_FILES:.c=.o)	# Create object files(.o) from all .c files in the project with same name

$(CFILES_OBJ):%.o:%.c
	@echo "Compiling $<..."
	@$(ARM_GCC) $(COMPILE_ARM_GCC_OPTION) -c $^ -o $@

## Linking
$(OUTPUT_DIR)/$(TARGET).elf: $(CFILES_OBJ)
	@echo "Linking $@..."
	@$(ARM_GCC) $(LINKING_ARM_OPTION) $(CFILES_OBJ) -o $@	-lm	-lgcc

## Create hex file from elf file.
$(OUTPUT_DIR)/$(TARGET).bin: $(OUTPUT_DIR)/$(TARGET).elf
	@$(OBJCPY) -O binary $^ $@
	@echo "Creating $@..."


$(OUTPUT_DIR)/$(TARGET).hex: $(OUTPUT_DIR)/$(TARGET).elf
	@$(OBJCPY) -O ihex $^ $@
	@echo "Creating $@..."

TARGET_RE = $(OUTPUT_DIR)/$(TARGET).bin	$(OUTPUT_DIR)/$(TARGET).hex

.PHONY build: $(TARGET_RE)

clean:
	rm -rf $(OUTPUT_DIR)/*.*

print-%:
	@echo $($(subst print-,,$@))


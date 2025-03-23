CC = arm-none-eabi-gcc

HOME_DIR := $(HOME)
MSPM0_SDK_PATH = $(HOME_DIR)/ti/mspm0_sdk
DEVICE = -D__MSPM0L1306__

# Compiler Flags (default to debug)
CFLAGS = -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft \
$(DEVICE) \
-I"$(HOME_DIR)/demo/demo_ti_l1306" \
-I"$(MSPM0_SDK_PATH)/source/third_party/CMSIS/Core/Include" \
-I"$(MSPM0_SDK_PATH)/source" \
-I"$(HOME)/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" \
-I"$(HOME)/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" \
-O0 -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(OBJ_DIR)/$(basename $(<F)).d_raw" \
-ffunction-sections \
-fdata-sections \
-std=c99

LDFLAGS = $(DEVICE) \
-O0 -g -gdwarf-3 -gstrict-dwarf -Wall -mthumb -mfloat-abi=soft -Wl,-Map,"$(BIN_DIR)/demo_l1306.map" -nostartfiles -static -Wl,--gc-sections \
-L"$(MSPM0_SDK_PATH)/source/ti/driverlib/lib/gcc/m0p/mspm0l11xx_l13xx" \
-L"$(MSPM0_SDK_PATH)/source" \
-L"$(HOME)/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/lib/thumb/v6-m/nofp" \
-march=armv6-m -mthumb

ORDERED_OBJS += \
-Wl,-T"./src/mspm0l1306.lds" \
"$(MSPM0_SDK_PATH)/source/ti/driverlib/lib/gcc/m0p/mspm0l11xx_l13xx/driverlib.a" \
-l:driverlib.a \
-lgcc \
-lc \
-lm \
-lnosys \

BIN_DIR = ./build
SRC_DIR = ./src
OBJ_DIR = ./build

SRC = $(shell find $(SRC_DIR) -name *.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TOTAL_FLASH = 65528
TOTAL_SRAM = 4096

TARGET_DEBUG = $(BIN_DIR)/app_debug.out
TARGET_RELEASE = $(BIN_DIR)/app_release.out

# Define paths to OpenOCD configuration files
OPENOCD_INTERFACE = /usr/local/share/openocd/scripts/interface/xds110.cfg
OPENOCD_TARGET = /usr/local/share/openocd/scripts/target/ti_mspm0.cfg

# OpenOCD command to start the server
OPENOCD_CMD = openocd -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET) -c "adapter speed 500"

# Debug and Release Flags
DEBUG_FLAGS = -O0 -g -gdwarf-3 -gstrict-dwarf
RELEASE_FLAGS = -O2 -flto

# Default target (debug build)
.DEFAULT_GOAL := debug

# Build Debug version
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET_DEBUG)

# Build Release version
release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET_RELEASE)

$(TARGET_DEBUG): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

$(TARGET_RELEASE): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo 'Finished building: $<'
	@echo ' '

# size: $(TARGET)
# 	arm-none-eabi-size $(TARGET)

size: $(TARGET_DEBUG) $(TARGET_RELEASE)
	@echo "Memory usage for $(TARGET_DEBUG):"
	@arm-none-eabi-size $(TARGET_DEBUG)
	@arm-none-eabi-objdump -h $(TARGET_DEBUG) | awk '\
	/text/    { flash += strtonum("0x" $$3); } \
	/rodata/  { flash += strtonum("0x" $$3); } \
	/data/    { flash += strtonum("0x" $$3); sram += strtonum("0x" $$3); } \
	/bss/     { sram += strtonum("0x" $$3); } \
	END { \
		printf "> FLASH  %d/%d (%.2f%%)\n", flash, $(TOTAL_FLASH), (flash / $(TOTAL_FLASH)) * 100; \
		printf "> SRAM   %d/%d (%.2f%%)\n", sram, $(TOTAL_SRAM), (sram / $(TOTAL_SRAM)) * 100; \
	}'

# Target to upload the binary to the MCU
upload: $(TARGET_DEBUG)
	@echo "Uploading $(TARGET_DEBUG) to the MCU..."
	@$(OPENOCD_CMD) -c "init" -c "reset init" -c "flash write_image erase $(TARGET_DEBUG) 0x00000000" -c "reset run" -c "shutdown"

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BIN_DIR)/*
	@rm -rf $(OBJ_DIR)/*
	@rm -f ./*.d_raw
	@rm -f ./*.map
	@echo "Clean complete."

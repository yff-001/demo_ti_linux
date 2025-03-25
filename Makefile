CC = arm-none-eabi-gcc

HOME_DIR := $(HOME)
MSPM0_SDK_PATH = $(HOME_DIR)/ti/mspm0_sdk
DEVICE = -D__MSPM0L1306__

# Compiler Flags
COMMON_CFLAGS = -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft \
$(DEVICE) \
-I"$(HOME_DIR)/demo/demo_ti_l1306" \
-I"$(MSPM0_SDK_PATH)/source/third_party/CMSIS/Core/Include" \
-I"$(MSPM0_SDK_PATH)/source" \
-I"$(HOME)/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" \
-I"$(HOME)/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" \
-ffunction-sections -fdata-sections -std=c99 -Wall -MMD -MP

DEBUG_FLAGS = -O0 -g -gdwarf-3 -gstrict-dwarf
RELEASE_FLAGS = -O2 -flto

COMMON_LDFLAGS = $(DEVICE) \
-march=armv6-m -mthumb -mfloat-abi=soft -nostartfiles -static -Wl,--gc-sections \
-L"$(MSPM0_SDK_PATH)/source/ti/driverlib/lib/gcc/m0p/mspm0l11xx_l13xx" \
-L"$(MSPM0_SDK_PATH)/source" \
-L"$(HOME)/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/lib/thumb/v6-m/nofp"

ORDERED_OBJS = -Wl,-T"./src/mspm0l1306.lds" \
"$(MSPM0_SDK_PATH)/source/ti/driverlib/lib/gcc/m0p/mspm0l11xx_l13xx/driverlib.a" \
-l:driverlib.a -lgcc -lc -lm -lnosys

# Directories
SRC_DIR = ./src
BUILD_DIR = ./build
OBJ_DIR_DEBUG = $(BUILD_DIR)/debug
OBJ_DIR_RELEASE = $(BUILD_DIR)/release
BIN_DIR_DEBUG = $(BUILD_DIR)/debug
BIN_DIR_RELEASE = $(BUILD_DIR)/release

# Source and Object Files
SRC = $(shell find $(SRC_DIR) -name *.c)
OBJ_DEBUG = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_DEBUG)/%.o, $(SRC))
OBJ_RELEASE = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_RELEASE)/%.o, $(SRC))

TOTAL_FLASH = 65528
TOTAL_SRAM = 4096

TARGET_DEBUG = $(BIN_DIR_DEBUG)/app_debug.out
TARGET_RELEASE = $(BIN_DIR_RELEASE)/app_release.out

# Ensure build directories exist
$(shell mkdir -p $(OBJ_DIR_DEBUG) $(OBJ_DIR_RELEASE) $(BIN_DIR_DEBUG) $(BIN_DIR_RELEASE))

# Debug build
debug: CFLAGS = $(COMMON_CFLAGS) $(DEBUG_FLAGS)
debug: LDFLAGS = $(COMMON_LDFLAGS) -Wl,-Map,"$(BIN_DIR_DEBUG)/demo_l1306.map"
debug: $(TARGET_DEBUG)

# Release build
release: CFLAGS = $(COMMON_CFLAGS) $(RELEASE_FLAGS)
release: LDFLAGS = $(COMMON_LDFLAGS) -Wl,-Map,"$(BIN_DIR_RELEASE)/demo_l1306.map"
release: $(TARGET_RELEASE)

OPENOCD_INTERFACE = /usr/local/share/openocd/scripts/interface/xds110.cfg
OPENOCD_TARGET = /usr/local/share/openocd/scripts/target/ti_mspm0.cfg

# OpenOCD command to start the server
OPENOCD_CMD = openocd -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET) -c "adapter speed 500"

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(LDFLAGS) -o $@ $^ $(ORDERED_OBJS)
	@echo "Finished building target: $@"

$(TARGET_RELEASE): $(OBJ_RELEASE)
	$(CC) $(LDFLAGS) -o $@ $^ $(ORDERED_OBJS)
	@echo "Finished building target: $@"

$(OBJ_DIR_DEBUG)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Finished building: $< (Debug)"

$(OBJ_DIR_RELEASE)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Finished building: $< (Release)"

# Memory usage report
size:
	@if [ -f "$(TARGET_DEBUG)" ]; then \
		echo "Memory usage for Debug build ($(TARGET_DEBUG)):"; \
		arm-none-eabi-size $(TARGET_DEBUG); \
		arm-none-eabi-objdump -h $(TARGET_DEBUG) | awk '\
		/text/    { flash += strtonum("0x" $$3); } \
		/rodata/  { flash += strtonum("0x" $$3); } \
		/data/    { flash += strtonum("0x" $$3); sram += strtonum("0x" $$3);} \
		/bss/     { sram += strtonum("0x" $$3); } \
		END { \
			printf "> FLASH  %d/%d (%.2f%%)\n", flash, $(TOTAL_FLASH), (flash / $(TOTAL_FLASH)) * 100; \
			printf "> SRAM   %d/%d (%.2f%%)\n", sram, $(TOTAL_SRAM), (sram / $(TOTAL_SRAM)) * 100; \
		}'; \
		echo ""; \
	fi
	@if [ -f "$(TARGET_RELEASE)" ]; then \
		echo "Memory usage for Release build ($(TARGET_RELEASE)):"; \
		arm-none-eabi-size $(TARGET_RELEASE); \
		arm-none-eabi-objdump -h $(TARGET_RELEASE) | awk '\
		/text/    { flash += strtonum("0x" $$3); } \
		/rodata/  { flash += strtonum("0x" $$3); } \
		/data/    { flash += strtonum("0x" $$3); sram += strtonum("0x" $$3);} \
		/bss/     { sram += strtonum("0x" $$3); } \
		END { \
			printf "> FLASH  %d/%d (%.2f%%)\n", flash, $(TOTAL_FLASH), (flash / $(TOTAL_FLASH)) * 100; \
			printf "> SRAM   %d/%d (%.2f%%)\n", sram, $(TOTAL_SRAM), (sram / $(TOTAL_SRAM)) * 100; \
		}'; \
		echo ""; \
	fi
	@if [ ! -f "$(TARGET_DEBUG)" ] && [ ! -f "$(TARGET_RELEASE)" ]; then \
		echo "No built binaries found. Run 'make debug' or 'make release' first."; \
	fi

# Upload target with validation for debug/release
upload: 
	@if [ -z "$(BUILD_TYPE)" ]; then \
		echo "Error: No build type specified (use 'make upload BUILD_TYPE=debug' or 'make upload BUILD_TYPE=release')"; \
		exit 1; \
	elif [ "$(BUILD_TYPE)" != "debug" ] && [ "$(BUILD_TYPE)" != "release" ]; then \
		echo "Error: Invalid build type specified (use 'debug' or 'release')"; \
		exit 1; \
	fi
	@echo "Uploading $(BUILD_TYPE) to the MCU..."
	@if [ "$(BUILD_TYPE)" = "debug" ]; then \
		$(OPENOCD_CMD) -c "init" -c "reset init" -c "flash write_image erase $(TARGET_DEBUG) 0x00000000" -c "reset run" -c "shutdown"; \
	elif [ "$(BUILD_TYPE)" = "release" ]; then \
		$(OPENOCD_CMD) -c "init" -c "reset init" -c "flash write_image erase $(TARGET_RELEASE) 0x00000000" -c "reset run" -c "shutdown"; \
	fi


# Clean build directories
clean:
	@echo "Cleaning build directories..."
	@rm -rf $(BUILD_DIR)/*
	@mkdir -p $(OBJ_DIR_DEBUG) $(OBJ_DIR_RELEASE) $(BIN_DIR_DEBUG) $(BIN_DIR_RELEASE)
	@echo "Clean complete."

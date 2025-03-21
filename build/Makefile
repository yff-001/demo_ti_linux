CC = arm-none-eabi-gcc

HOME_DIR := $(HOME)
DEVICE = -D__MSPM0L1306__

CFLAGS = -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft \
$(DEVICE) \
-I"$(HOME_DIR)/demo/demo_ti_l1306" \
-I"$(HOME)/ti/mspm0_sdk_2_00_00_03/source/third_party/CMSIS/Core/Include" \
-I"$(HOME)/ti/mspm0_sdk_2_00_00_03/source" \
-I"$(HOME)/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" \
-I"$(HOME)/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" \
-O2 \
-ffunction-sections \
-fdata-sections \
-g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" \
-std=c99

LDFLAGS = $(DEVICE) \
-O2 \
-ffunction-sections \
-fdata-sections \
-g -gdwarf-3 -gstrict-dwarf -Wall -mthumb -mfloat-abi=soft -Wl,-Map,"demo_l1306.map" -nostartfiles -static -Wl,--gc-sections \
-L"$(HOME)/ti/mspm0_sdk_2_00_00_03/source/ti/driverlib/lib/gcc/m0p/mspm0l11xx_l13xx" \
-L"$(HOME)/ti/mspm0_sdk_2_00_00_03/source" \
-L"$(HOME)/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/lib/thumb/v6-m/nofp" \
-march=armv6-m -mthumb

ORDERED_OBJS += \
-Wl,-T"../src/mspm0l1306.lds" \
"$(HOME)/ti/mspm0_sdk_2_00_00_03/source/ti/driverlib/lib/gcc/m0p/mspm0l11xx_l13xx/driverlib.a" \
-l:driverlib.a \
-lgcc \
-lc \
-lm \
-lnosys \

BIN_DIR = ./bin
SRC_DIR = ../src
OBJ_DIR = ./obj

# SRC = $(wildcard $(SRC_DIR)/*.c)
# OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
SRC = $(shell find $(SRC_DIR) -name *.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TOTAL_FLASH = 65528
TOTAL_SRAM = 4096

TARGET = $(BIN_DIR)/app.out

# Define paths to OpenOCD configuration files
OPENOCD_INTERFACE = /usr/local/share/openocd/scripts/interface/xds110.cfg
OPENOCD_TARGET = /usr/local/share/openocd/scripts/target/ti_mspm0.cfg

# OpenOCD command to start the server
OPENOCD_CMD = openocd -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET) -c "adapter speed 500"

all: $(TARGET)

$(TARGET): $(OBJ)
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

size: $(TARGET)
	@echo "Memory uage for $(TARGET):"
	@arm-none-eabi-objdump -h $(TARGET) | awk 'BEGIN { flash=0; sram=0; } \
	/\.text/ { flash += strtonum("0x" $$3); } \
	/\.rodata/ { flash += strtonum("0x" $$3); } \
	/\.data/ { flash += strtonum("0x" $$3); sram += strtonum("0x" $$3); } \
	/\.bss/ { sram += strtonum("0x" $$3); } \
	END { \
	flash_pct = (flash / $(TOTAL_FLASH)) * 100; \
	sram_pct = (sram / $(TOTAL_SRAM)) * 100; \
	flash_str = sprintf("> FLASH    %d/%d (%.2f%%)", flash, $(TOTAL_FLASH), flash_pct); \
	sram_str = sprintf("> SRAM %d/%d (%.2f%%)", sram, $(TOTAL_SRAM), sram_pct); \
	max_len = length(flash_str); \
	padding = max_len - length(sram_str); \
	printf "%s\n", flash_str; \
	printf "%*s%s\n", padding, "", sram_str; \
}'

# Target to upload the binary to the MCU
upload: $(TARGET)
	@echo "Uploading $(BINARY) to the MCU..."
	@$(OPENOCD_CMD) -c "init" -c "reset init" -c "flash write_image erase $(TARGET) 0x00000000" -c "reset run" -c "shutdown"

clean:
	@rm -rf ./bin/*
	@rm -rf ./obj/*
	@rm -f ./*.d_raw
	@rm -f ./*.map

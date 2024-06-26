CC = arm-none-eabi-gcc

CFLAGS = -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -D__MSPM0C1104__ -I"/home/yff/demo/demo_ti_l1306" -I"/home/yff/ti/mspm0_sdk_2_00_00_03/source/third_party/CMSIS/Core/Include" -I"/home/yff/ti/mspm0_sdk_2_00_00_03/source" -I"/home/yff/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"/home/yff/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99
LDFLAGS = -D__MSPM0C1104__ -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -mthumb -mfloat-abi=soft -Wl,-Map,"demo_l1306.map" -nostartfiles -static -Wl,--gc-sections -L"/home/yff/ti/mspm0_sdk_2_00_00_03/source/ti/driverlib/lib/gcc/m0p/mspm0l11xx_l13xx" -L"/home/yff/ti/mspm0_sdk_2_00_00_03/source" -L"/home/yff/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/lib/thumb/v6-m/nofp" -march=armv6-m -mthumb

ORDERED_OBJS += \
-Wl,-T"./src/mspm0l1306.lds" \
"/home/yff/ti/mspm0_sdk_2_00_00_03/source/ti/driverlib/lib/gcc/m0p/mspm0l11xx_l13xx/driverlib.a" \
-l:driverlib.a \
-lgcc \
-lc \
-lm \
-lnosys \

BIN_DIR = bin
SRC_DIR = src
OBJ_DIR = obj

# SRC = $(wildcard $(SRC_DIR)/*.c)
# OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
SRC = $(shell find $(SRC_DIR) -name *.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TARGET = $(BIN_DIR)/app.out

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

size: $(TARGET)
	arm-none-eabi-size $(TARGET)

clean:
	@rm -rf ./bin/*
	@rm -rf ./obj/*
	@rm -f ./*.d_raw
	@rm -f ./*.map

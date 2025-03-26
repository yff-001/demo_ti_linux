# Compiler for unit tests (host machine)
CC = gcc

# Directories
SRC_DIR = ../src
UNITY_DIR = ../lib/unity
BUILD_DIR = ./build

# Ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

# Find all test files
TESTS = $(wildcard *.c)
TEST_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(TESTS))

# Source files to test (exclude embedded-only files)
SRC_OBJS = $(BUILD_DIR)/communication.o

# Unity framework source
UNITY_SRC = $(UNITY_DIR)/unity.c

# Compiler flags
CFLAGS = -I$(SRC_DIR) -I$(UNITY_DIR) -std=c99 -Wall -Wextra -DUNIT_TEST

# Test binary
TEST_BIN = $(BUILD_DIR)/test_runner

# Default rule to build and run tests
all: $(TEST_BIN)
	@echo "Running unit tests..."
	@./$(TEST_BIN)

# Build test executable
$(TEST_BIN): $(TEST_OBJS) $(SRC_OBJS) $(UNITY_SRC)
	$(CC) $(CFLAGS) $^ -o $@

# Compile test files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile source files for unit testing (without MCU-specific includes)
$(BUILD_DIR)/communication.o: $(SRC_DIR)/handler/communication.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

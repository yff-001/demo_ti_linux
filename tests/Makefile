# Compiler for unit tests (host machine)
CC = gcc

# Directories
SRC_DIR = ../src
UNITY_DIR = ../lib/unity
BUILD_DIR = ./build

# Ensure build directory exists before compiling
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Find all test files (those prefixed with "test_")
TESTS = $(wildcard test_*.c)
TEST_BINS = $(patsubst %.c, $(BUILD_DIR)/%, $(TESTS))

# Explicitly list source files needed for unit tests
SRC_FILES = ../src/handler/communication.c ../src/event_queue.c
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Unity framework source
UNITY_SRC = $(UNITY_DIR)/unity.c
UNITY_OBJ = $(BUILD_DIR)/unity.o

# Compiler flags
CFLAGS = -I$(SRC_DIR) -I$(UNITY_DIR) -std=c99 -Wall -Wextra -DUNIT_TEST -g

# Default rule: build all tests
all: $(TEST_BINS)

# Run all tests
test: $(TEST_BINS)
	@echo "Running unit tests..."
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		$$test || exit 1; \
	done

# Build individual test executables
$(BUILD_DIR)/%: %.c $(UNITY_OBJ) $(SRC_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< $(UNITY_OBJ) $(SRC_OBJS) -o $@

# Compile Unity
$(UNITY_OBJ): $(UNITY_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile source files needed for unit tests
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

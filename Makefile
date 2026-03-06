CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude -Isrc -O3 -march=native
DEBUG_FLAGS = -g -O0 -fsanitize=address -fsanitize=undefined

# Define directories
SRC_DIR = src
BUILD_DIR = build

# Find all .c files in the SRC_DIR and its subdirectories
SRC = $(shell find $(SRC_DIR) -name '*.c')

# Map the .c paths to .o paths inside the BUILD_DIR
# e.g., src/core/init.c becomes build/src/core/init.o
OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC))

# The final executable will be in the build directory
EXEC = $(BUILD_DIR)/znet_run

.PHONY: all debug clean

all: $(EXEC)

debug: CFLAGS := -Wall -Wextra -Werror -std=c11 -Iinclude -Isrc $(DEBUG_FLAGS)
debug: $(EXEC)

# Link the object files into the final binary
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c files into .o files, creating directories as needed
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean just deletes the entire build directory
clean:
	rm -rf $(BUILD_DIR)
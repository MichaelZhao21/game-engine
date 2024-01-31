# Define compiler and flags
CC := gcc
CFLAGS := -W -Wall -Wextra -pedantic $(shell sdl2-config --cflags)
LIBS := -Iinclude -lpthread -Llib -lSDL2main $(shell sdl2-config --libs)

# Define directories
SOURCE_DIR := src
BUILD_DIR := build

# Define input files
FILES := $(SOURCE_DIR)/main.c

# Define output files for each input file (replace .c with .o)
OUT_FILES := $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(FILES))

# Default rule to build
all: $(OUT_FILES) $(BUILD_DIR)/main

# Compile each source file into an object file
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

# Link object files to create executable
$(BUILD_DIR)/main: $(OUT_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean target to remove all files in the build directory
clean:
	rm -rf $(BUILD_DIR)/*

# Phony targets
.PHONY: clean

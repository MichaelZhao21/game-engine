CC = gcc
CFLAGS = -W -Wall -Wextra -pedantic $(shell sdl2-config --cflags)
SOURCE_DIR = src
BUILD_DIR = build
LIB = $(shell sdl2-config --libs) -Iinclude -lpthread -Llib -lSDL2main

FILES = $(SOURCE_DIR)/main.c

all: main

main:
	$(CC) $(CFLAGS) $(FILES) -o $(BUILD_DIR)/main $(LIB)

clean:
	rm -rf $(BUILD_DIR)/*

CC := g++
CONFIG ?= debug

SRC_DIR := src
BIN_DIR := bin/$(CONFIG)

all:
	$(CC) src/hello.cpp -o$(BIN_DIR)/longDayFactory.exe
CC = gcc
CFlags = -Wall -Wextra -Ilib -lm -O3
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = build/rotator

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFlags) -o $@ $^

build/%.o: src/%.c | build
	$(CC) $(CFlags) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build/*

.PHONY: all clean 

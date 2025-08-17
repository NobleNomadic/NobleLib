# Compiler and flags
CC = gcc
CFLAGS = -nostdlib -nostartfiles -nodefaultlibs -fno-stack-protector
LDFLAGS = -static

# Target executable
TARGET = build/example
SOURCE = src/example.c src/noblelib.c

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCE) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCE)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Debug version with symbols
debug: CFLAGS += -g
debug: $(TARGET)

# Show what syscalls are being made
strace: $(TARGET)
	strace -e trace=write,exit ./$(TARGET)

.PHONY: all run clean debug strace

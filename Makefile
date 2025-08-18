# Compiler / Assembler
CC      = gcc
CFLAGS  = -nostdlib -nostartfiles -nodefaultlibs -fno-stack-protector -w -ffreestanding
LDFLAGS = -static
ASM     = nasm
ASFLAGS = -f elf64

# Paths
TARGET    = build/example
C_SOURCES = src/example.c src/noblelib.c
ASM_SOURCE= src/start.asm
ASM_OBJECT= build/start.o

# Default target
all: $(TARGET)

# Link everything
$(TARGET): $(C_SOURCES) $(ASM_OBJECT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	strip $(TARGET) 

# Assemble start.asm
$(ASM_OBJECT): $(ASM_SOURCE)
	$(ASM) $(ASFLAGS) $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build with symbols
debug: CFLAGS += -g
debug: clean all

# Clean build artifacts
clean:
	rm -f $(TARGET) $(ASM_OBJECT)

# Trace syscalls
strace: $(TARGET)
	strace -e trace=write,exit ./$(TARGET)

# Inspect disassembly
objdump: $(TARGET)
	objdump -d $(TARGET) | less

# Inspect ELF headers/sections
readelf: $(TARGET)
	readelf -a $(TARGET) | less

# Strip binary completely (no symbols, no notes)
strip: $(TARGET)
	objcopy --strip-all \
	        --remove-section=.comment \
	        --remove-section=.note.gnu.property \
	        --remove-section=.note.gnu.build-id \
	        --remove-section=.note.ABI-tag \
	        $(TARGET)


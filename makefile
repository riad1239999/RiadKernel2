# Makefile for compiling the kernel and generating a bootable image

# Compiler and assembler
CC = g++
AS = nasm
LD = ld

# Compiler flags
CFLAGS = -Wall -g -m32 -ffreestanding -nostdlib -fno-exceptions -fno-rtti
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
KERNEL_SRC = $(SRC_DIR)/kernel.cpp
KERNEL_OBJ = $(OBJ_DIR)/kernel.o
KERNEL_BIN = $(BIN_DIR)/kernel.bin

BOOT_SRC = $(SRC_DIR)/boot.asm
BOOT_OBJ = $(OBJ_DIR)/boot.o

# The output bootable image
OUTPUT_IMG = $(BIN_DIR)/bootable.iso

# Default target
all: $(OUTPUT_IMG)

# Rule to compile C++ files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile assembly files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

# Linking the kernel object files to create the kernel binary
$(KERNEL_BIN): $(KERNEL_OBJ) $(BOOT_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Rule to generate a bootable ISO image
$(OUTPUT_IMG): $(KERNEL_BIN)
	mkdir -p $(BIN_DIR)/iso/boot/grub
	cp $(KERNEL_BIN) $(BIN_DIR)/iso/boot/kernel.bin
	echo "set timeout=0" > $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo "set default=0" >> $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo "menuentry 'My OS' {" >> $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo "    multiboot /boot/kernel.bin" >> $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo "    boot" >> $(BIN_DIR)/iso/boot/grub/grub.cfg
	echo "}" >> $(BIN_DIR)/iso/boot/grub/grub.cfg

	# Create the ISO image using GRUB
	grub-mkrescue -o $(OUTPUT_IMG) $(BIN_DIR)/iso

# Clean up all generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Create the directories if they don't exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

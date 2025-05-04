# Compiler and linker settings
CC = g++
AS = nasm
LD = ld

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
BOOT_SRC = boot.asm
KERNEL_SRC = kernel.cpp kernel.asm
GRAPHICS_SRC = graphics_loader.cpp
LINKER_SCRIPT = linker.ld

# Output binary name
OUTPUT = riad_kernel.bin

# Flags
CFLAGS = -ffreestanding -O2 -Wall -g
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T $(LINKER_SCRIPT)

# Source files and object files
SOURCES = $(BOOT_SRC) $(KERNEL_SRC) $(GRAPHICS_SRC)
OBJECTS = $(addprefix $(OBJ_DIR)/, $(BOOT_SRC:.asm=.o) $(KERNEL_SRC:.cpp=.o) $(GRAPHICS_SRC:.cpp=.o))

# Targets
all: $(OUTPUT)

# Build the kernel binary
$(OUTPUT): $(OBJECTS)
	@echo "Linking..."
	$(LD) $(LDFLAGS) -o $(BIN_DIR)/$(OUTPUT) $(OBJECTS)

# Assemble bootloader
$(OBJ_DIR)/boot.o: $(SRC_DIR)/boot.asm
	@echo "Assembling bootloader..."
	$(AS) $(ASFLAGS) -o $(OBJ_DIR)/boot.o $(SRC_DIR)/boot.asm

# Compile kernel C++ files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Create directories if they don't exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

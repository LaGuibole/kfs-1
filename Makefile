# **************************************************************************** #
# 🎨 COLORS
# **************************************************************************** #
GREY    	=	\033[030m
RED     	=	\033[031m
GREEN   	=	\033[032m
YELLOW  	=	\033[033m
BLUE    	=	\033[034m
CYAN		=	\033[036m
BOLD		=	\033[1m
RESET   	=	\033[0m

# **************************************************************************** #
# 💾 VARIABLES
# **************************************************************************** #
# Cross-compiler paths
export PREFIX = $(HOME)/opt/cross
export TARGET = i686-elf
export PATH := $(PREFIX)/bin:$(PATH)

# Compiler & Linker
CC          = $(TARGET)-gcc
AS          = $(TARGET)-as
LD          = $(TARGET)-ld

# Fichiers
KERNEL_OUT  = build/guphilip_kfs.bin
ISO_OUT     = build/guphilip_kfs.iso
BOOT        = src/boot.s
KERNEL      = src/kernel.c
LINKER      = src/linker.ld

# Flags
CFLAGS      = -ffreestanding -O2 -nostdlib -fno-builtin -Wall -Wextra
LDFLAGS     = -T $(LINKER) -nostdlib

# **************************************************************************** #
# 📖 RULES
# **************************************************************************** #
all: build

build: fclean
	@mkdir -p build
	@echo "$(BOLD)$(YELLOW)[⚙] Assembling boot.s...$(RESET)"
	@$(AS) $(BOOT) -o build/boot.o
	@echo "$(BOLD)$(YELLOW)[⚙] Compiling kernel.c...$(RESET)"
	@$(CC) $(CFLAGS) -c $(KERNEL) -o build/kernel.o
	@echo "$(BOLD)$(GREEN)[✓] KERNEL BUILD DONE$(RESET)"
	@echo "$(BOLD)$(YELLOW)[⚙] Linking kernel...$(RESET)"
	@$(LD) $(LDFLAGS) -o $(KERNEL_OUT) build/boot.o build/kernel.o
	@echo "$(BOLD)$(GREEN)[✓] KERNEL LINK DONE$(RESET)"

build_debug: fclean
	@echo "$(BOLD)$(YELLOW)[✓] KERNEL DEBUG MODE ON$(RESET)"
	@mkdir -p build
	@$(AS) $(BOOT) -o build/boot.o
	@$(CC) $(CFLAGS) -g -c $(KERNEL) -o build/kernel.o
	@echo "$(BOLD)$(GREEN)[✓] KERNEL BUILD DONE$(RESET)"
	@$(LD) $(LDFLAGS) -o $(KERNEL_OUT) build/boot.o build/kernel.o
	@echo "$(BOLD)$(GREEN)[✓] KERNEL LINK DONE$(RESET)"

run: build
	@qemu-system-i386 -kernel $(KERNEL_OUT) -monitor stdio
	@echo "\n$(BOLD)$(CYAN)[✓] KERNEL EXIT DONE$(RESET)"

debug: build_debug
	@qemu-system-i386 -kernel $(KERNEL_OUT) -s -S &
	@gdb -x .gdbinit
	@echo "\n$(BOLD)$(CYAN)[✓] KERNEL DEBUG EXIT DONE$(RESET)"

iso: build
	@mkdir -p build/iso/boot/grub
	@cp grub.cfg build/iso/boot/grub
	@cp $(KERNEL_OUT) build/iso/boot
	@grub-mkrescue -o $(ISO_OUT) build/iso
	@echo "$(BOLD)$(GREEN)[✓] KERNEL ISO BUILD$(RESET)"

run-iso: iso
	@qemu-system-i386 -cdrom $(ISO_OUT)
	@echo "\n$(BOLD)$(CYAN)[✓] KERNEL EXIT DONE$(RESET)"

clean:
	@rm -rf $(KERNEL_OUT) $(ISO_OUT)
	@echo "$(BOLD)$(RED)[♻︎] DELETE KERNEL DONE$(RESET)"

fclean:
	@clear
	@rm -rf build/
	@echo "$(BOLD)$(RED)[♻︎] DELETE BUILD/ DONE$(RESET)"

re: fclean all

.PHONY: all clean fclean re build build_debug run debug iso run-iso
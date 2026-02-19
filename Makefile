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
export PREFIX = $(HOME)/opt/cross
export TARGET = i686-elf
export PATH := $(PREFIX)/bin:$(PATH)

CC          = $(TARGET)-gcc
AS          = $(TARGET)-as
LD          = $(TARGET)-ld

KERNEL_OUT  = build/kfs.bin
ISO_OUT     = build/kfs.iso
LINKER      = src/boot/linker.ld

SRC_C       := $(wildcard src/**/*.c src/*.c)
SRC_S       := $(wildcard src/**/*.S src/*.S)
OBJ_C       := $(SRC_C:%.c=build/%.o)
OBJ_S       := $(SRC_S:%.S=build/%.o)
OBJ         := $(OBJ_S) $(OBJ_C)

CFLAGS      = -std=c17 \
			-fno-builtin \
			-fno-exceptions \
			-fno-stack-protector \
			-nostdlib \
			-nodefaultlibs \
			-mno-sse \
			-mno-red-zone \
			-mno-sse2 \
			-mno-sse3 \
			-mno-mmx \
			-mno-80387 \
			-fno-pic \
			-fomit-frame-pointer \
			-ffreestanding \
			-fstrict-volatile-bitfields \
			-Iincludes \
			-Iincludes/asm \
			-Wall \
			-Wextra
LDFLAGS     = -T $(LINKER) -nostdlib

# **************************************************************************** #
# 📖 RULES
# **************************************************************************** #
all: build

build: fclean $(KERNEL_OUT)

$(KERNEL_OUT): $(OBJ)
	@echo "$(BOLD)$(YELLOW)[⚙] Linking kernel...$(RESET)"
	@$(LD) $(LDFLAGS) -o $@ $(OBJ)
	@echo "$(BOLD)$(GREEN)[✓] KERNEL LINK DONE$(RESET)"

build/%.o: %.S
	@mkdir -p $(dir $@)
	@echo "$(BOLD)$(YELLOW)[⚙] Assembling with preprocessor $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

build/%.o: %.s
	@mkdir -p $(dir $@)
	@echo "$(BOLD)$(YELLOW)[⚙] Assembling $<...$(RESET)"
	@$(AS) $< -o $@

build/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BOLD)$(YELLOW)[⚙] Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

run: iso
	@qemu-system-i386 -cdrom $(ISO_OUT) -monitor stdio
	@echo "\n$(BOLD)$(CYAN)[✓] KERNEL EXIT DONE$(RESET)"

debug: build
	@qemu-system-i386 -cdrom $(ISO_OUT) -s -S &
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
#include "term.h"
#include "asm/multiboot.h"
#include "printk/printk.h"
#include "dump.h"

extern void	init_gdt(void);
extern int kernel_stack_top;

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main()
{
    terminal_initialize();
    printk("Welcome to KFS-1 kernel!\n");
    printk("Build date: %s %s\n", __DATE__, __TIME__);
    printk("VGA resolution: %dx%d\n", VGA_WIDTH, VGA_HEIGHT);
    printk("Kernel loaded at: %p\n", kernel_main);
    print_stack_dump(10);
}
#include "term.h"
#include "asm/multiboot.h"
#include "printk/printk.h"
#include "dump.h"
#include "gdt.h"

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
    init_gdt();
    terminal_initialize();
    print_stack_dump();
}
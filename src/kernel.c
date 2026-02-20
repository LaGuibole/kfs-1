#include "term.h"
#include "asm/multiboot.h"
#include "printk/printk.h"
#include "dump.h"
#include "gdt.h"
#include "io.h"
#include "pic.h"
#include "idt.h"

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
    pic_remap(0x20, 0x28);
    outb(0xFF, PIC_MASTER_DATA);
    outb(0xFF, PIC_SLAVE_DATA);
    init_idt();
    pic_unmask_irq(1);

    __asm__ volatile ("sti");
    for (;;) {
        __asm__ volatile ("hlt");
    }
}
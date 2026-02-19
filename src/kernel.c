#include "term.h"
#include "asm/multiboot.h"

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
    terminal_putstr("Hello World, this is KFS-1, cpoulain branleur !\n");
    terminal_putstr("Tiens tiens tiens, la newline marche, pas si branleur le cpoulain...\n");
    terminal_putstr("HaAHHAHAHAHAHAHAHAHAHAHAHAHAHHHHHHHHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHHAHAHAHAAHHAHAHAHHAHAHAH");
    terminal_putstr("\nMeme l'overflow est gere :)))");
    terminal_putstr("\nBim le curseur !");
}
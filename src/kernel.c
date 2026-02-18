#include "vga.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main()
{
    terminal_initialize();
    terminal_writestring("Hello World, this is KFS-1, cpoulain branleur !\n");
}
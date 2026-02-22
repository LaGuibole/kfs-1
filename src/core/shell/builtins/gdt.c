#include "shell/shell.h"
#include "gdt.h"

void cmd_gdt(char **args, int argc)
{
	terminal_putchar('\n');
	(void)args;
	(void)argc;
	print_gdt_dump();
}
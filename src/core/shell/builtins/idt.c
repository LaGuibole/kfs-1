#include "shell/shell.h"
#include "idt.h"

void cmd_idt(char **args, int argc)
{
	terminal_putchar('\n');
	(void)args;
	(void)argc;
	print_idt();
}
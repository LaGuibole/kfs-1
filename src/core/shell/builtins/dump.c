#include "shell/shell.h"
#include "dump.h"

void cmd_dump(char**args, int argc)
{
	terminal_putchar('\n');
	(void)args;
	(void)argc;
	print_stack_dump();
}
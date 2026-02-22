#include "shell/shell.h"

void cmd_echo(char **args, int argc)
{
	terminal_putchar('\n');
	for (int i = 1; i < argc; i++)
	{
		terminal_putstr(args[i]);
		if (i < argc - 1)
			terminal_putchar(' ');
	}
	terminal_putchar('\n');
}
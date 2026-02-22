#include "shell/shell.h"
#include "shell/exec.h"
#include "shell/term.h"
#include "printk/printk.h"
#include "gdt.h"
#include "idt.h"

static const t_cmd g_commands[] = {
	{ "help", cmd_help },
	{ "gdt", cmd_gdt },
	{ "idt", cmd_idt },
	{ "dump", cmd_dump },
	{ "echo", cmd_echo },
	{ "clear", cmd_clear },
	{ "tabs", cmd_tabs },
	{ "troll", cmd_troll },
	{ NULL, NULL },
};

static int parse_args(char *buffer, char **argv, int max_args)
{
	int argc = 0;

	while (*buffer)
	{
		while (*buffer == ' ')
			buffer++;
		if (!*buffer)
			break;
		if (argc < max_args)
			argv[argc++] = buffer;
		while(*buffer && *buffer != ' ')
			buffer++;
		if (*buffer == ' ')
			*buffer++ = '\0';
	}
	return argc;
}

void shell_exec(char *input)
{
	char    buffer[INPUT_BUFFER_SIZE];
	char	*argv[32];
	int		argc;
	int		i = 0;

	while (input[i] && i < INPUT_BUFFER_SIZE - 1)
	{
		buffer[i] = input[i];
		i++;
	}
	buffer[i] = '\0';
	
	
	if (buffer[0] == '\0')
	{
		terminal_putchar('\n');
		terminal_prompt();
		return ;
	}

	argc = parse_args(buffer, argv, 32);
	if (argc == 0)
	{
		terminal_putchar('\n');
		terminal_prompt();
		return ; 
	}

	i = 0;
	while (g_commands[i].name)
	{
		if (strcmp(argv[0], g_commands[i].name) == 0)
		{
			g_commands[i].handler(argv, argc);
			terminal_prompt();
			return;
		}
		i++;
	}
	terminal_putstr("\nUnknown command: ");
	terminal_putstr(argv[0]);
	terminal_putchar('\n');
	terminal_prompt();
}
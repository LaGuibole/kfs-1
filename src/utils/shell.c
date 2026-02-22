#include "shell.h"
#include "term.h"
#include "printk/printk.h"
#include "dump.h"
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

void cmd_help(char **args, int argc)
{
	(void)args;
	(void)argc;
	terminal_putstr("\nAvailable commands:\n");
	terminal_putstr("    help    - Show this message\n");
	terminal_putstr("    gdt     - Print GDT Table\n");
	terminal_putstr("    idt     - Print IDT Table\n");
	terminal_putstr("    dump    - Print Stack Dump\n");
	terminal_putstr("    echo    - Print arguments\n");
	terminal_putstr("    clear   - Clear current tab\n");
	terminal_putstr("    tabs    - Show tab info\n");
	terminal_putstr("    troll   - Surprise :D\n");
}

void cmd_clear(char **args, int argc)
{
	(void)args;
	(void)argc;

	extern t_tabs	tabs[];
	extern u8		selected_tab;

	for (int y = 1; y < VGA_HEIGHT; y++)
		for (int x = 0; x < VGA_WIDTH; x++)
			tabs[selected_tab].tab_buffer[y][x] = 0;
	tabs[selected_tab].cursor_x = 0;
	tabs[selected_tab].cursor_y = 1;
	terminal_dump_tab();
}

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

void cmd_tabs(char **args, int argc)
{
	terminal_putchar('\n');
	(void)args;
	(void)argc;
	extern u8 selected_tab;
	printk("Current tab: %d / %d\n", selected_tab, (TERM_TAB_COUNT - 1));
}

void cmd_dump(char**args, int argc)
{
	terminal_putchar('\n');
	(void)args;
	(void)argc;
	print_stack_dump();
}

void cmd_gdt(char **args, int argc)
{
	terminal_putchar('\n');
	(void)args;
	(void)argc;
	print_gdt_dump();
}

void cmd_idt(char **args, int argc)
{
	terminal_putchar('\n');
	(void)args;
	(void)argc;
	print_idt();
}

void cmd_troll(char **args, int argc)
{
	terminal_putchar('\n');
    (void)args; (void)argc;
    terminal_putstr("                    _____\n");
    terminal_putstr("                 ,-'     `._\n");
    terminal_putstr("               ,'           `.        ,-.\n");
    terminal_putstr("             ,'               \\       ),.\\\n");
    terminal_putstr("   ,.       /                  \\     /(  \\;\n");
    terminal_putstr("  /'\\\\     ,o.        ,ooooo.   \\  ,'  `-')\n");
    terminal_putstr("  )) )`. d8P\"Y8.    ,8P\"\"\"\"\"Y8.  `'  .--\"'\n");
    terminal_putstr(" (`-'   `Y'  `Y8    dP       `'     /\n");
    terminal_putstr("  `----.(   __ `    ,' ,---.       (\n");
    terminal_putstr("         ),--.`.   (  ;,---.        )\n");
    terminal_putstr("        / \\O_,' )   \\  \\O_,'        |\n");
    terminal_putstr("       ;  `-- ,'       `---'        |\n");
    terminal_putstr("       |    -'         `.           |\n");
    terminal_putstr("      _;    ,            )          :\n");
    terminal_putstr("   _.'|     `.:._   ,.:\" `..        |\n");
    terminal_putstr("--'   |   .'     \"\"\"         `      |`.\n");
    terminal_putstr("      |  :;      :   :     _.       |`.`.-'--.\n");
    terminal_putstr("      |  ' .     :   :__.,'|/       |  \\\n");
    terminal_putstr("      `     \\--.__.-'|_|_|-/        /   )\n");
    terminal_putstr("       \\     \\_   `--^\"__,'        ,    |\n");
    terminal_putstr("       ;  `    `--^---'          ,'     |\n");
    terminal_putstr("        \\  `                    /      /\n");
    terminal_putstr("         \\   `    _ _          /\n");
    terminal_putstr("          \\           `       /\n");
    terminal_putstr("           \\           '    ,'\n");
    terminal_putstr("            `.       ,   _,'\n");
    terminal_putstr("              `-.___.---'\n");
    terminal_putstr("\n");
    terminal_putstr("  Somebody once told me the world is gonna roll me...\n");
}
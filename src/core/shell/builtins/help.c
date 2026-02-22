#include "shell/shell.h"

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
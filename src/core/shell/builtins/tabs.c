#include "shell/shell.h"
#include "printk/printk.h"

void cmd_tabs(char **args, int argc)
{
	terminal_putchar('\n');
	(void)args;
	(void)argc;
	extern u8 selected_tab;
	printk("Current tab: %d / %d\n", selected_tab, (TERM_TAB_COUNT - 1));
}
#include "shell/tabs.h"

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
	tab_dump();
}
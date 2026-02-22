#include "shell/tabs.h"

u8 selected_tab = 0;
t_tabs  tabs[TERM_TAB_COUNT] = {0};

void tab_switch(u8 new_tab)
{
    if (new_tab >= TERM_TAB_COUNT || new_tab == selected_tab)
        return;

    selected_tab = new_tab;
    tab_dump();
    if (tabs[selected_tab].tab_buffer[tabs[selected_tab].cursor_y][(tabs[selected_tab].cursor_x-1)] == 0)
        terminal_prompt();
}

void    tab_initialize()
{
    for (int i = 0; i < TERM_TAB_COUNT; i++)
    {
        tabs[i].cursor_x = 0;
        tabs[i].cursor_y = 0;
        for (int k = 0; k < VGA_HEIGHT; k++)
            for (int j = 0; j < VGA_WIDTH; j++)
                tabs[i].tab_buffer[k][j] = 0;
    }
    for (int t = 0; t < TERM_TAB_COUNT; t++)
        fill_buf_header(t);
}

void tab_dump()
{
    int y;
    int x;
    u8 original_cursor_x = tabs[selected_tab].cursor_x;
    u8 original_cursor_y = tabs[selected_tab].cursor_y;

    for (y = 1; y < VGA_HEIGHT; ++y)
        for (x = 0; x < VGA_WIDTH; ++x)
            vga_putchar_colored_at(x, y, VGA_BLANK_ENTRY, VGA_DEFAULT_COLOR);
    terminal_printheader();
    for (y = 1; y < VGA_HEIGHT; ++y)
    {
        for (x = 0; x < VGA_WIDTH; ++x)
        {
            u16 entry = tabs[selected_tab].tab_buffer[y][x];
            char c = entry & 0xFF;
            u8 color = (entry >> 8) & 0xFF;
            if (c != 0)
                terminal_putchar_colored_at(x, y, c, color);
        }
    }
    tabs[selected_tab].cursor_x = original_cursor_x;
    tabs[selected_tab].cursor_y = original_cursor_y ? original_cursor_y : 1;
    vga_cursor_at(original_cursor_x, original_cursor_y);
}
#include "shell/term.h"

void terminal_putchar_at(u8 x, u8 y, char c)
{
    vga_putchar_at(x, y, c);
}

void terminal_putchar_colored_at(u8 x, u8 y, char c, u8 color)
{
    tabs[selected_tab].cursor_x = x;
    tabs[selected_tab].cursor_y = y;
    vga_putchar_colored_at(x, y, c, color);
}

void terminal_putchar_colored(char c, u8 color)
{
    if (tabs[selected_tab].cursor_y >= VGA_HEIGHT)
        return;
    if (c != '\n')
    {
        vga_putchar_colored_at(tabs[selected_tab].cursor_x, tabs[selected_tab].cursor_y, c, color);
        if (tabs[selected_tab].cursor_y > 0)
            tabs[selected_tab].tab_buffer[tabs[selected_tab].cursor_y][tabs[selected_tab].cursor_x] = vga_entry(c, color);
        ++tabs[selected_tab].cursor_x;
    }
    if (tabs[selected_tab].cursor_x >= VGA_WIDTH || c == '\n')
    {
        ++tabs[selected_tab].cursor_y;
        tabs[selected_tab].cursor_x = 0;
    }
    if (tabs[selected_tab].cursor_y >= VGA_HEIGHT)
    {
        tabs[selected_tab].cursor_y = VGA_HEIGHT - 1;
        vga_scroll_down();
        terminal_scroll_down_buffer();
    }
    vga_cursor_at(tabs[selected_tab].cursor_x, tabs[selected_tab].cursor_y);
}

void terminal_putchar(char c)
{
    terminal_putchar_colored(c, VGA_DEFAULT_COLOR);
}

int terminal_putstr(const char *str)
{
    int i = 0;
    for (; str[i]; i++)
        terminal_putchar(str[i]);
    return (i);
}

int terminal_putstr_colored(const u16 *str)
{
    int i = 0;
    for (; str[i]; i++)
        terminal_putchar_colored(str[i] & 0xFF, (str[i] >> 8) & 0xFF);
    return (i);
}

void terminal_putnchar(char c, int count)
{
    while (count--)
        terminal_putchar(c);
}
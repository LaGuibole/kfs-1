#include "shell/term.h"

u16 headers[TERM_TAB_COUNT][VGA_WIDTH + 1];

void fill_buf_header(int tab_idx)
{
    u8 tab_color = 0x02 + (0x01 * (tab_idx + 1));
    u8 highlight_color = 0x20 + (0x10 * (tab_idx + 1));

    // Fill the header with default blank entries (using tab color)
    for (int i = 0; i < VGA_WIDTH; i++)
        headers[tab_idx][i] = vga_entry('-', tab_color);

    // Draw left border
    headers[tab_idx][5] = vga_entry('/', tab_color);

    // Draw tab numbers, centered between the borders
    int tab_area_start = 6;
    int tab_area_end = tab_area_start + TERM_TAB_COUNT * 2 + 1;
    int curr_tab = 0;
    for (int i = tab_area_start; i < tab_area_end && i < VGA_WIDTH; i++)
    {
        if (i % 2 == 0)
        {
            headers[tab_idx][i] = vga_entry(' ', tab_color);
        }
        else
        {
            u8 color = (curr_tab == tab_idx) ? highlight_color : tab_color;
            headers[tab_idx][i] = vga_entry('0' + curr_tab, color);
            curr_tab++;
        }
    }

    // Draw right border
    if (tab_area_end < VGA_WIDTH)
        headers[tab_idx][tab_area_end] = vga_entry('/', tab_color);
}

void terminal_printheader()
{
    u8 saved_x = tabs[selected_tab].cursor_x;
    u8 saved_y = tabs[selected_tab].cursor_y;

    tabs[selected_tab].cursor_x = 0;
    tabs[selected_tab].cursor_y = 0;
    terminal_putstr_colored(headers[selected_tab]);

    tabs[selected_tab].cursor_x = saved_x;
    tabs[selected_tab].cursor_y = saved_y ? saved_y : 1;
    vga_cursor_at(tabs[selected_tab].cursor_x, tabs[selected_tab].cursor_y);
}
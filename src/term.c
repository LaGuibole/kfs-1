/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:17:20 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/20 17:09:37 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"
#include "vga.h"
#include "printk/printk.h"
#include "dump.h"

/* -------------------------------------------------------------------------- */
/*                              Globals variables                             */
/* -------------------------------------------------------------------------- */

u8 selected_tab = 0;
u16 headers[TERM_TAB_COUNT][VGA_WIDTH + 1];
t_tabs  tabs[TERM_TAB_COUNT] = {0};

/* -------------------------------------------------------------------------- */
/*                           Header implementations                           */
/* -------------------------------------------------------------------------- */

void terminal_switch_tab(u8 new_tab)
{
    if (new_tab >= TERM_TAB_COUNT || new_tab == selected_tab)
        return;

    selected_tab = new_tab;
    terminal_dump_tab();
}

void terminal_scroll_down_buffer()
{
    // Move lines 2..(VGA_HEIGHT-1) up by one (skip header at row 0)
    for (int y = 1; y < VGA_HEIGHT - 1; ++y)
        for (int x = 0; x < VGA_WIDTH; ++x)
            tabs[selected_tab].tab_buffer[y][x] = tabs[selected_tab].tab_buffer[y + 1][x];

    // Clear the last line
    for (int x = 0; x < VGA_WIDTH; ++x)
        tabs[selected_tab].tab_buffer[VGA_HEIGHT - 1][x] = 0;
}

void terminal_dump_tab()
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
    // tabs[selected_tab].cursor_y = saved_y ? saved_y : 1;
    vga_cursor_at(tabs[selected_tab].cursor_x, tabs[selected_tab].cursor_y);
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

void terminal_initialize()
{
    tab_initialize();
    terminal_reset();
    vga_enable_cursor(0,15);
    terminal_dump_tab();
    terminal_putchar('\n');
    terminal_putstr(" 444444      22222222           OOOOOOOOO    SSSSSSSSS  \n");
    terminal_putstr(" 444444      22222222          OOOOOOOOOOO   SSSSSSSSS  \n");
    terminal_putstr("444   444   222     222       OOO       OOO SSS        \n");
    terminal_putstr("444   444           222       OOO       OOO SSS        \n");
    terminal_putstr("444444444444     222222       OOO       OOO  SSSSSSS   \n");
    terminal_putstr("444444444444   222222         OOO       OOO   SSSSSSS  \n");
    terminal_putstr("      444        222          OOO       OOO        SSS \n");
    terminal_putstr("      444      222            OOO       OOO        SSS \n");
    terminal_putstr("      444     222222222        OOOOOOOOOOO   SSSSSSSSS  \n");
    terminal_putstr("      444     222222222         OOOOOOOOO    SSSSSSSSS  \n");
    terminal_putchar('\n');
    terminal_prompt();
}

void terminal_reset()
{
    tabs[selected_tab].cursor_x = 0;
    tabs[selected_tab].cursor_y = 0;
    vga_reset_screen();
}

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

// void terminal_backspace()
// {
//     int i;
//     if (tabs[selected_tab].cursor_x == 0 && tabs[selected_tab].cursor_y <= 1)
//         return ;
//     if (tabs[selected_tab].cursor_x == 0)
//     {
//         --tabs[selected_tab].cursor_y;
//         for (i = 0; tabs[selected_tab].tab_buffer[tabs[selected_tab].cursor_y][i] == VGA_BLANK_ENTRY; i++)
//             ;
//         for (i = 0; tabs[selected_tab].tab_buffer[tabs[selected_tab].cursor_y][i] != VGA_BLANK_ENTRY; i++)
//             ; 
//         tabs[selected_tab].cursor_x = (i - 1) % VGA_WIDTH;
//     }
//     else
//         --tabs[selected_tab].cursor_x;
//     tabs[selected_tab].tab_buffer[tabs[selected_tab].cursor_y][tabs[selected_tab].cursor_x] = vga_entry(VGA_BLANK_ENTRY, VGA_DEFAULT_COLOR);
//     vga_putchar_colored_at(tabs[selected_tab].cursor_x, tabs[selected_tab].cursor_y, VGA_BLANK_ENTRY, VGA_DEFAULT_COLOR);
//     vga_cursor_at(tabs[selected_tab].cursor_x, tabs[selected_tab].cursor_y);
// }

void terminal_backspace()
{
    if (tabs[selected_tab].cursor_x == 0 && tabs[selected_tab].cursor_y <= 1)
        return;

    if (tabs[selected_tab].cursor_x == tabs[selected_tab].prompt_start_x
            && tabs[selected_tab].cursor_y == tabs[selected_tab].prompt_start_y)
            return;

    if (tabs[selected_tab].cursor_x == 0)
    {
        --tabs[selected_tab].cursor_y;
        int last_x = VGA_WIDTH - 1;
        while (last_x > 0 && (tabs[selected_tab].tab_buffer[tabs[selected_tab].cursor_y][last_x] & 0xFF) == VGA_BLANK_ENTRY)
            --last_x;
        if ((tabs[selected_tab].tab_buffer[tabs[selected_tab].cursor_y][last_x] & 0xFF) == VGA_BLANK_ENTRY)
            tabs[selected_tab].cursor_x = 0;
        else
            tabs[selected_tab].cursor_x = last_x;
    }
    else
        --tabs[selected_tab].cursor_x;
    tabs[selected_tab].tab_buffer[tabs[selected_tab].cursor_y][tabs[selected_tab].cursor_x] = vga_entry(VGA_BLANK_ENTRY, VGA_DEFAULT_COLOR);
    vga_putchar_colored_at(tabs[selected_tab].cursor_x, tabs[selected_tab].cursor_y, VGA_BLANK_ENTRY, VGA_DEFAULT_COLOR);
    vga_cursor_at(tabs[selected_tab].cursor_x, tabs[selected_tab].cursor_y);
}

void terminal_prompt()
{
    int i = 0;
    while (PROMPT[i])
        terminal_putchar_colored(PROMPT[i++], VGA_COLOR_GREEN);
    tabs[selected_tab].prompt_start_x = tabs[selected_tab].cursor_x;
    tabs[selected_tab].prompt_start_y = tabs[selected_tab].cursor_y;
}
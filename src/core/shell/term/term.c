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

#include "shell/tabs.h"
#include "vga.h"
#include "printk/printk.h"
#include "dump.h"

/* -------------------------------------------------------------------------- */
/*                           Header implementations                           */
/* -------------------------------------------------------------------------- */

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

void terminal_initialize()
{
    tab_initialize();
    terminal_reset();
    vga_enable_cursor(0,15);
    tab_dump();
    terminal_putchar('\n');
    terminal_putstr(" 444444      22222222           OOOOOOOOO    SSSSSSSSS  \n");
    terminal_putstr(" 444444      22222222          OOOOOOOOOOO   SSSSSSSSS  \n");
    terminal_putstr("444   444   222     222       OOO       OOO SSS         \n");
    terminal_putstr("444   444           222       OOO       OOO SSS         \n");
    terminal_putstr("444444444444     222222       OOO       OOO  SSSSSSS    \n");
    terminal_putstr("444444444444     222222       OOO       OOO   SSSSSSS   \n");
    terminal_putstr("      444        222          OOO       OOO        SSS  \n");
    terminal_putstr("      444      222            OOO       OOO        SSS  \n");
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
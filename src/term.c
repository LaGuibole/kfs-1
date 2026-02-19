/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:17:20 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/18 18:25:39 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

/* -------------------------------------------------------------------------- */
/*                              Globals variables                             */
/* -------------------------------------------------------------------------- */

u8  cursor_x;
u8  cursor_y;

/* -------------------------------------------------------------------------- */
/*                           Header implementations                           */
/* -------------------------------------------------------------------------- */

void terminal_initialize()
{
    cursor_x = 0;
    cursor_y = 0;
    vga_reset_screen();   
}

void    terminal_putchar_at(u8 x, u8 y, char c)
{
    vga_putchar_at(x, y, c);
}

void    terminal_putchar_colored_at(u8 x, u8 y, char c, u8 color)
{
    vga_putchar_colored_at(x, y, c, color);   
}

void    terminal_putchar(char c)
{
    if (cursor_y >= VGA_HEIGHT)
        return;
    if (c != '\n')
    {
        vga_putchar_colored_at(cursor_x, cursor_y, c, VGA_DEFAULT_COLOR);
        ++cursor_x;
    }
    if (cursor_x >= VGA_WIDTH || c == '\n')
    {
        ++cursor_y;
        cursor_x = 0;
    }
    if (cursor_y >= VGA_HEIGHT)
    {
        cursor_y = VGA_HEIGHT - 1;
        vga_scroll_down();
    }
    vga_cursor_at(cursor_x, cursor_y);
}

int    terminal_putstr(const char *str)
{
    int i = 0;
    for (; str[i]; i++)
        terminal_putchar(str[i]);
    return (i);
}
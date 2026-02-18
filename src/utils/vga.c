/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:07:06 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/18 15:34:06 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vga.h"

static size_t      terminal_row;
static size_t      terminal_column;
static size_t      terminal_color;
static u16*        terminal_buffer = (u16*)VGA_MEMORY;

static inline u8 vga_entry_color(t_vga_color fg, t_vga_color bg)
{
    return fg | bg << 4;
}

static inline u16 vga_entry(unsigned char uc, u8 color)
{
    return (u16) uc | (u16) color << 8;
}

void terminal_initialize()
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_DARK_GREY);

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(u8 color)
{
    terminal_color = color;
}

void terminal_putentryat(char c, u8 color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
}
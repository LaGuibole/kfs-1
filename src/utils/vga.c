/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:07:06 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/20 15:59:29 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vga.h"

u16*         video_buffer = (u16*)VGA_MEMORY;

u8 vga_entry_color(t_vga_color fg, t_vga_color bg)
{
    return (u8)fg | (u8)bg << 4;
}

u16 vga_entry(unsigned char uc, u8 color)
{
    return (u16) uc | (u16)(color << 8);
}

void    vga_reset_screen()
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i)
        video_buffer[i] = VGA_DEFAULT_COLOR << 8 | VGA_BLANK_ENTRY;
    vga_cursor_at(0, 0);
}

void    vga_putchar_at(u8 x, u8 y, char c)
{
    u16 vga_entry = video_buffer[y * VGA_WIDTH + x]; // Get the current entry at the position
    vga_entry = (vga_entry & 0xFF00) | (u8)c; // Update only the character part, keep the color
    video_buffer[y * VGA_WIDTH + x] = vga_entry; // Write the updated entry back to the buffer
}

void    vga_putchar_colored_at(u8 x, u8 y, char c, u8 color)
{
    video_buffer[y * VGA_WIDTH + x] = vga_entry((u8)c, color); // Write the character with the specified color directly to the buffer
}

void    vga_enable_cursor(u8 cursor_start, u8 cursor_end)
{
    outb(CURSOR_START_REG, REG_SELECT_PORT);
    outb((inb(DATA_PORT) & CURSOR_START_MASK) | cursor_start, DATA_PORT);
    outb(CURSOR_END_REG, REG_SELECT_PORT);
    outb((inb(DATA_PORT) & CURSOR_END_MASK) | cursor_end, DATA_PORT);
}

void    vga_cursor_at(u8 x, u8 y)
{
    x %= VGA_WIDTH;
    y %= VGA_HEIGHT;

    u16 new_pos = x + VGA_WIDTH * y;

    outb(CURSOR_LOW_BYTE, REG_SELECT_PORT);
    outb((u8) (new_pos & 0xFF), DATA_PORT);
    outb(CURSOR_HIGH_BYTE, REG_SELECT_PORT);
    outb((u8) ((new_pos >> 8) & 0xFF), DATA_PORT);
}

void    vga_scroll_down()
{
    memmove(&video_buffer[VGA_WIDTH], &video_buffer[VGA_WIDTH * 2], VGA_WIDTH * (VGA_HEIGHT - 2) * sizeof(u16));
    for (int i = VGA_WIDTH * (VGA_HEIGHT - 1); i < VGA_WIDTH * VGA_HEIGHT; ++i)
        video_buffer[i] = VGA_DEFAULT_COLOR << 8 | VGA_BLANK_ENTRY;
}
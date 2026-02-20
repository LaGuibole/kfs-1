/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:07:18 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/20 13:01:33 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VGA_H
# define VGA_H

#include "string.h"
#include "io.h"
#include "mem.h"

/* -------------------------------------------------------------------------- */
/*                                  Constants                                 */
/* -------------------------------------------------------------------------- */

#define VGA_WIDTH           80
#define VGA_HEIGHT          25
#define VGA_MEMORY          0xB8000
#define VGA_DEFAULT_COLOR   0x0F
#define VGA_BLANK_ENTRY     0x00

extern u16* video_buffer;

typedef enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
} t_vga_color;

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

void    vga_reset_screen();
void    vga_putchar_at(u8 x, u8 y, char c);
void    vga_putchar_colored_at(u8 x, u8 y, char c, u8 color);
void    vga_enable_cursor(u8 cursor_start, u8 cursor_end);
void    vga_cursor_at(u8 x, u8 y);
void    vga_scroll_down();
u8      vga_entry_color(t_vga_color fg, t_vga_color bg);
u16     vga_entry(unsigned char uc, u8 color);

#endif
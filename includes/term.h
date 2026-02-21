/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:48:30 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/20 16:07:05 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

#include "vga.h"
#include "shell.h"

#define TERM_TAB_COUNT  10
#define PROMPT          "cgpoulipOS >  "  

typedef struct s_tabs
{
	u8  cursor_x;
	u8  cursor_y;
	u16 tab_buffer[VGA_HEIGHT][VGA_WIDTH];
	u8 input_buffer[INPUT_BUFFER_SIZE];
	u16 input_len;
	u8  prompt_start_x;
	u8  prompt_start_y;
}   t_tabs;

extern t_tabs   tabs[TERM_TAB_COUNT];
extern u8   selected_tab;

void    terminal_initialize();
void    terminal_putchar_at(u8 x, u8 y, char c);
void    terminal_putchar_colored_at(u8 x, u8 y, char c, u8 color);
void    terminal_putchar(char c);
int     terminal_putstr(const char *str);
void    terminal_putnchar(char c, int count);
int     terminal_putstr_colored(const u16 *str);
void    terminal_putchar_colored(char c, u8 color);
void    terminal_reset();
void    terminal_switch_tab(u8 new_tab);
void    terminal_printheader();
void    terminal_dump_tab();
void    terminal_putchar_colored_at(u8 x, u8 y, char c, u8 color);
void    terminal_scroll_down_buffer();
void    terminal_backspace();
void    terminal_prompt();

#endif
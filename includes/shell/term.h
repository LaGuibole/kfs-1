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

#include "shell.h"
#include "vga.h"

/* -------------------------------------------------------------------------- */
/*                           Core terminal functions                          */
/* -------------------------------------------------------------------------- */

void    terminal_initialize();
void    terminal_backspace();
void    terminal_prompt();
void    terminal_reset();
void    terminal_scroll_down_buffer();

/* -------------------------------------------------------------------------- */
/*                                Term writter                                */
/* -------------------------------------------------------------------------- */

void    terminal_putchar_colored_at(u8 x, u8 y, char c, u8 color);
void    terminal_putchar_at(u8 x, u8 y, char c);
void    terminal_putchar_colored_at(u8 x, u8 y, char c, u8 color);
void    terminal_putchar(char c);
int     terminal_putstr(const char *str);
void    terminal_putnchar(char c, int count);
int     terminal_putstr_colored(const u16 *str);
void    terminal_putchar_colored(char c, u8 color);

/* -------------------------------------------------------------------------- */
/*                              Headers functions                             */
/* -------------------------------------------------------------------------- */

void    terminal_printheader();
void	fill_buf_header(int tab_idx);

#endif
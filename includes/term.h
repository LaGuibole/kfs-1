/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:48:30 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/18 17:46:22 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

#include "vga.h"

extern u8 cursor_x;
extern u8 cursor_y;

void    terminal_initialize();
void    terminal_putchar_at(u8 x, u8 y, char c);
void    terminal_putchar_colored_at(u8 x, u8 y, char c, u8 color);
void    terminal_putchar(char c);
int     terminal_putstr(const char *str);

#endif
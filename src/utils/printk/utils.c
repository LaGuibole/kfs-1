/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:08:56 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 16:17:43 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk/printk.h"
#include "term.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void    printk_putchar(char c)
{
	terminal_putchar(c);
}

void	printk_putnchar(char c, int count)
{
	terminal_putnchar(c, count);
}

int		printk_putstr(const char *str)
{
	return (terminal_putstr(str));
}

int	isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
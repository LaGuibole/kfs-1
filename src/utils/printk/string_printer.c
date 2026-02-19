/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:07:57 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 16:18:30 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk/printk.h"

/* -------------------------------------------------------------------------- */
/*                              Helper prototypes                             */
/* -------------------------------------------------------------------------- */

static void	putnstr(const char *str, size_t len);

/* -------------------------------------------------------------------------- */
/*                           Helper implementations                           */
/* -------------------------------------------------------------------------- */

int	string_printer(t_format *fmt, char *str)
{
	size_t	s_len;
	size_t	len;

	s_len = strlen(str);
	if (format_flag_has_precision(fmt))
		s_len = min(fmt->precision, s_len);
	fmt->width = max(0, fmt->width - s_len);
	len = s_len + fmt->width;
	if (format_flag_has_left_justify(fmt))
		putnstr(str, s_len);
	printk_putnchar(' ', fmt->width);
	if (!format_flag_has_left_justify(fmt))
		putnstr(str, s_len);
	return (len);
}

/* -------------------------------------------------------------------------- */
/*                           Helper implementations                           */
/* -------------------------------------------------------------------------- */

static void	putnstr(const char *str, size_t len)
{
	while (len--)
		printk_putchar(*str++);
}
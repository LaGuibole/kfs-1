/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:06:40 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 16:17:52 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk/printk.h"

/* -------------------------------------------------------------------------- */
/*                              Helper prototypes                             */
/* -------------------------------------------------------------------------- */

static int	len_n(long n);
static void	print_number(unsigned long n);
static void	print(t_format *fmt, long n, int pn);

/* -------------------------------------------------------------------------- */
/*                           Header implementations                           */
/* -------------------------------------------------------------------------- */

int	number_printer(t_format *fmt, long n)
{
	int	number_size;

	if (format_flag_has_precision(fmt) && fmt->precision == 0 && n == 0)
		number_size = 0;
	else
		number_size = len_n(n);
	fmt->precision -= number_size;
	if (n < 0 || format_flag_has_align_sign(fmt)
		|| format_flag_has_force_sign(fmt))
		++number_size;
	if (format_flag_has_zero_padding(fmt)
		&& !format_flag_has_left_justify(fmt)
		&& !format_flag_has_precision(fmt))
		fmt->precision = fmt->width - number_size;
	fmt->precision = max(0, fmt->precision);
	fmt->width = max(0, fmt->width - number_size - fmt->precision);
	print(fmt, n, number_size != 0);
	return (number_size + fmt->width + fmt->precision);
}

/* -------------------------------------------------------------------------- */
/*                           Helper implementations                           */
/* -------------------------------------------------------------------------- */

static int	len_n(long n)
{
	int	len;

	len = 1;
	if (n < 0)
		n = -n;
	while (n > 9)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static void	print_number(unsigned long n)
{
	if (n > 9)
		print_number(n / 10);
	printk_putchar((n % 10) + '0');
}

static void	print(t_format *fmt, long n, int pn)
{
	if (!format_flag_has_left_justify(fmt))
		printk_putnchar(' ', fmt->width);
	if (!format_flag_has_force_sign(fmt)
		&& format_flag_has_align_sign(fmt) && n >= 0)
		printk_putchar(' ');
	if (format_flag_has_force_sign(fmt) && n >= 0)
		printk_putchar('+');
	if (n < 0)
	{
		n = -n;
		printk_putchar('-');
	}
	printk_putnchar('0', fmt->precision);
	if (pn)
		print_number((unsigned long) n);
	if (format_flag_has_left_justify(fmt))
		printk_putnchar(' ', fmt->width);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_printers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:48:11 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 16:17:36 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk/printk.h"

int	_char_printer(va_list *arg_list, t_format *fmt)
{
	int	len;

	if (fmt->width <= 0)
		fmt->width = 1;
	len = fmt->width--;
	if (format_flag_has_left_justify(fmt))
		printk_putchar(va_arg(*arg_list, int));
	while (fmt->width--)
		printk_putchar(' ');
	if (!format_flag_has_left_justify(fmt))
		printk_putchar(va_arg(*arg_list, int));
	return (len);
}

int	_decimal_printer(va_list *arg_list, t_format *fmt)
{
	int	x;

	x = va_arg(*arg_list, int);
	return (number_printer(fmt, (long) x));
}

int	_integer_printer(va_list *arg_list, t_format *fmt)
{
	int	x;

	x = va_arg(*arg_list, int);
	return (number_printer(fmt, (long) x));
}

int	_lo_hex_printer(va_list *arg_list, t_format *fmt)
{
	unsigned int	x;

	x = va_arg(*arg_list, unsigned int);
	fmt->flags &= ~(FMT_FLAG__ALIGN_SIGN | FMT_FLAG__FORCE_SIGN);
	return (hex_printer(fmt, (size_t) x, 0));
}

int	_pointer_printer(va_list *arg_list, t_format *fmt)
{
	void	*ptr;
	size_t	n;

	ptr = va_arg(*arg_list, void *);
	n = *(long *)&ptr;
	if (!n)
		return (string_printer(fmt, "(nil)"));
	fmt->flags |= FMT_FLAG__HEX_PREFIX;
	return (hex_printer(fmt, n, 0));
}

int	_string_printer(va_list *arg_list, t_format *fmt)
{
	char	*str;

	str = va_arg(*arg_list, char *);
	if (str)
		return (string_printer(fmt, str));
	if (!format_flag_has_precision(fmt)
		|| (unsigned long) fmt->precision + 1 >= sizeof(NULL_STRING))
		return (string_printer(fmt, (char *) NULL_STRING));
	return (string_printer(fmt, (char *) ""));
}

int	_unsigned_printer(va_list *arg_list, t_format *fmt)
{
	unsigned int	x;

	x = va_arg(*arg_list, unsigned int);
	fmt->flags &= ~(FMT_FLAG__ALIGN_SIGN | FMT_FLAG__FORCE_SIGN);
	return (number_printer(fmt, (long) x));
}

int	_up_hex_printer(va_list *arg_list, t_format *fmt)
{
	unsigned int	x;

	x = va_arg(*arg_list, unsigned int);
	fmt->flags &= ~(FMT_FLAG__ALIGN_SIGN | FMT_FLAG__FORCE_SIGN);
	return (hex_printer(fmt, (size_t) x, 1));
}

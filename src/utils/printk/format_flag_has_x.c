/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_flag_has_x.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:37:44 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 14:38:39 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk/utils.h"

int	format_flag_has_align_sign(t_format *fmt)
{
	return ((fmt->flags & FMT_FLAG__ALIGN_SIGN) != 0);
}

int	format_flag_has_precision(t_format *fmt)
{
	return ((fmt->flags & FMT_FLAG__PRECISION) != 0);
}

int	format_flag_has_left_justify(t_format *fmt)
{
	return ((fmt->flags & FMT_FLAG__LEFT_JUSTIFY) != 0);
}

int	format_flag_has_hex_prefix(t_format *fmt)
{
	return ((fmt->flags & FMT_FLAG__HEX_PREFIX) != 0);
}

int	format_flag_has_force_sign(t_format *fmt)
{
	return ((fmt->flags & FMT_FLAG__FORCE_SIGN) != 0);
}

int	format_flag_has_zero_padding(t_format *fmt)
{
	return ((fmt->flags & FMT_FLAG__ZERO_PADDING) != 0);
}
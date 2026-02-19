/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printk.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:45:29 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 16:17:20 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTK_H
# define PRINTK_H

#include "printk/utils.h"
#include "string.h"
#include "mem.h"

extern char printk_buffer[4096];

int	printk(const char *fmt, ...);

#endif

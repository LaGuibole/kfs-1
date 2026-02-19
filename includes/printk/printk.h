/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prink.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:45:29 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 14:46:32 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTK_H
# define PRINTK_H

extern char printk_buffer[4096];

int	printk(const char *fmt, ...);

#endif

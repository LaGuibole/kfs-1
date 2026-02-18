/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:37:45 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/18 15:45:10 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include "types.h"

void	*memchr(
			const void *s,
			int c,
			size_t n
			);

int		memcmp(
			const void *s1,
			const void *s2,
			size_t n
			);

void	*memcpy(
			void *restrict dst,
			const void *restrict src,
			size_t n
			);

void	*memmove(
			void *dst,
			const void *src,
			size_t n
			);

void	*memset(
			void *ptr,
			int c,
			size_t n
			);

void	memswap(
			void *_a,
			void *_b,
			size_t n
			);

#endif
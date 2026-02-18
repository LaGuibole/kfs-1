/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:47:26 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/18 15:57:36 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

char	*strchr(
			const char *s,
			int c
			);

int		strcmp(
			const char *s1,
			const char *s2
			);

char	*strcpy(
			char *dst,
			const char *src
			);

void	striteri(
			char *str,
			void (*f)(unsigned int, char*)
			);

size_t	strlcat(
			char *dest,
			const char *src,
			size_t size
			);

size_t	strlcpy(
			char *dst,
			const char *src,
			size_t size
			);

size_t	strlen(
			const char *str
			);

int		strncmp(
			const char *s1,
			const char *s2,
			size_t n
			);

char	*strnstr(
			const char *big,
			const char *little,
			size_t len
			);

char	*strrchr(
			const char *s,
			int c
			);
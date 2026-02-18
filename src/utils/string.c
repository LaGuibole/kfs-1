/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:12:44 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/18 16:02:22 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

/* -------------------------------------------------------------------------- */
/*                           Header implementations                           */
/* -------------------------------------------------------------------------- */

char    *strchr(const char* s, int c)
{
	while (*s)
	{
		if (*(t_byte *)s == (t_byte)c)
			return ((char *) s);
		++s;
	}
	if (*(t_byte *)s == (t_byte)c)
		return ((char *) s);
	return (NULL);
}

int     strcmp(const char* s1, const char* s2)
{
	while (*s1)
	{
		if (*(t_byte *)s1 != *(t_byte *)s2)
			break ;
		s1++;
		s2++;
	}
	return (*(t_byte *)s1 - *(t_byte *)s2);
}

char    *strcpy(char* dst, const char* src)
{
    char *ret = dst;

    while (*src)
        *dst++ = *src++;
    *dst = '\0';
    return (ret);
}

void    striteri(char* str, void (*f)(unsigned int, char*))
{
    unsigned int i = 0;

    while (str[i])
    {
        f(i, &str[i]);
        ++i;
    }
}

size_t  strlcat(char* dest, const char* src, size_t size)
{
    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);

    if (size <= dest_len)
        return (size + src_len);
    size_t copy_len = size - dest_len - 1;
    if (copy_len > src_len)
        copy_len = src_len;
    for (size_t i = 0; i < copy_len; ++i)
        dest[dest_len + i] = src[i];
    dest[dest_len + copy_len] = '\0';
    return (dest_len + src_len);
}

size_t strlcpy(char* dst, const char* src, size_t size)
{
    size_t src_len = strlen(src);

    if (size == 0)
        return (src_len);
    size_t copy_len = size - 1;
    if (copy_len > src_len)
        copy_len = src_len;
    for (size_t i = 0; i < copy_len; ++i)
        dst[i] = src[i];
    dst[copy_len] = '\0';
    return (src_len);
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

int     strncmp(const char* s1, const char* s2, size_t n)
{
    while (n--)
    {
        if (*s1 == '\0' || *(t_byte *)s1 != *(t_byte *)s2)
            return (*(t_byte *)s1 - *(t_byte *)s2);
        s1++;
        s2++;
    }
    return 0;
}

char    *strnstr(const char* big, const char* little, size_t len)
{
    size_t little_len = strlen(little);

    if (little_len == 0)
        return (char *)big;
    for (size_t i = 0; big[i] && i + little_len <= len; ++i)
    {
        if (big[i] == little[0] && strncmp(&big[i], little, little_len) == 0)
            return (char *)&big[i];
    }
    return NULL;
}

char    *strrchr(const char* s, int c)
{
    const char* last = NULL;

    while (*s)
    {
        if (*(t_byte *)s == (t_byte)c)
            last = s;
        ++s;
    }
    if (*(t_byte *)s == (t_byte)c)
        return ((char *) s);
    return (char *)last;
}
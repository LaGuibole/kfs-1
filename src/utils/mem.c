/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:29:54 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/18 15:49:53 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/* -------------------------------------------------------------------------- */
/*                              Helper prototypes                             */
/* -------------------------------------------------------------------------- */

static void swap(t_byte *a, t_byte *b);

/* -------------------------------------------------------------------------- */
/*                           Header implementations                           */
/* -------------------------------------------------------------------------- */

void    *memchr(
    const void *s,
    int c,
    size_t n
)
{
    while (n--)
    {
        if (*((t_byte *)s) == (t_byte)c)
            return (void *)s;
        ++s;
    }
    return (NULL);
}

int     memcmp(
    const void *s1,
    const void *s2,
    size_t n
)
{
    while (n--)
    {
        if (*((t_byte *)s1) != *((t_byte *)s2))
            return (*((t_byte *)s1) - *((t_byte *)s2));
        ++s1;
        ++s2;
    }
    return (0);
}

void    *memcpy(
    void *restrict dst,
    const void *restrict src,
    size_t n
)
{
    void *ret = dst;

    if (!dst || !src)
        return (NULL);
    while (n--)
        *((t_byte *)dst++) = *((t_byte *)src++);
    return (ret);
}

void    *memmove(
    void *dst,
    const void *src,
    size_t n
)
{
    void *dst_cpy = dst;

    if (!dst || !src)
        return NULL;
    if (dst > src && (size_t)((char *)dst - (char *)src) < n)
    {
        dst = (char *)dst + n - 1;
        src = (const char *)src + n - 1;
        while (n--)
            *(char *)dst-- = *(const char *)src--;
    }
    else
    {
        while (n--)
            *(char *)dst++ = *(const char *)src++;
    }
    return dst_cpy;
}

void    *memset(
    void *ptr,
    int c,
    size_t n
)
{
    void *ret = ptr;

    while (n--)
        *((t_byte *)ptr++) = (t_byte)c;
    return (ret);
}

void    memswap(
    void *_a,
    void *_b,
    size_t n
)
{
    t_byte *a = (t_byte *)_a;
    t_byte *b = (t_byte *)_b;

    while (n--)
        swap(a++, b++);
}

/* -------------------------------------------------------------------------- */
/*                           Helper implementations                           */
/* -------------------------------------------------------------------------- */

static void swap(t_byte *a, t_byte *b)
{
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:48:30 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/18 15:23:34 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#ifndef __ASSEMBLY__

typedef char                i8;
typedef short               i16;
typedef int                 i32;
typedef long int            i64;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long int   u64;

typedef u32                 uaddr; 
typedef u32				    size_t;
typedef u8					t_byte;

#endif

#define NULL ((void *)0)

#define HEX_PREFIX "0x"
#define HEX_CHARSET "0123456789ABCDEF"

#define BIN_PREFIX "0b"
#define BIN_CHARSET "0123456789ABCDEF"

#endif
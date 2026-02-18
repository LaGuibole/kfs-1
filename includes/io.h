/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:00:11 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/18 18:13:33 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

#ifndef __ASSEMBLY__

#define outb(value, port) \
    __asm__ ("outb %%al,%%dx"::"a" (value), "d" (port))

#define outw(value, port) \
    __asm__ ("outw %%ax,%%dx"::"a" (value), "d" (port))

#define inb(port) ({ \
    unsigned char _v; \
    __asm__ volatile ("inb %%dx,%%al":"=a" (_v):"d" (port)); \
    _v; \
    })

#define outb_p(value, port) \
    __asm__ ("outb %%al,%%dx\n" \
            "\tjmp 1f\n" \
            "1:\tjmp 1f\n" \
            "1:"::"a" (value), "d" (port))

#define inb_p(port) ({ \
	unsigned char _v; \
	__asm__ volatile ("inb %%dx,%%al\n" \
		"\tjmp 1f\n" \
		"1:\tjmp 1f\n" \
		"1:":"=a" (_v):"d" (port)); \
	_v; \
	})

#define CURSOR_START_REG    0x0A
#define CURSOR_END_REG      0x0B
#define REG_SELECT_PORT     0x3D4
#define DATA_PORT           0x3D5
#define CURSOR_START_MASK   0xC0
#define CURSOR_END_MASK     0xE0
#define CURSOR_LOW_BYTE     0x0F
#define CURSOR_HIGH_BYTE    0x0E

#endif

#endif
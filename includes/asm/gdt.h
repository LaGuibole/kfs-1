/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:40:06 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 13:49:23 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_GDT_H
#define ASM_GDT_H

/* -------------------------------------------------------------------------- */
/*                         GDT Access Byte Definitions                        */
/* -------------------------------------------------------------------------- */

/* -------- 0x9A: Present, ring 0, exec, R, accessed=0 (kernel code) -------- */
#define GDT_ACCESS_KERNEL_CODE  0x9A
/* -------- 0x92: Present, ring 0, data, W, accessed=0 (kernel data) -------- */
#define GDT_ACCESS_KERNEL_DATA  0x92
/* - 0x96: Present, ring 0, data, W, expand-down, accessed=0 (kernel stack) - */
#define GDT_ACCESS_KERNEL_STACK 0x96

/* --------- 0xFA: Present, ring 3, exec, R, accessed=0 (user code) --------- */
#define GDT_ACCESS_USER_CODE    0xFA
/* --------- 0xF2: Present, ring 3, data, W, accessed=0 (user data) --------- */
#define GDT_ACCESS_USER_DATA    0xF2
/* -- 0xF6: Present, ring 3, data, W, expand-down, accessed=0 (user stack) -- */
#define GDT_ACCESS_USER_STACK   0xF6

/* -------------------------------------------------------------------------- */
/*                         GDT Flags Byte Definitions                         */
/* -------------------------------------------------------------------------- */

/* ---- 0xCF: 4 KiB granularity, 32-bit protected mode, "standard" flags ---- */
#define GDT_FLAGS_STANDARD      0xCF

#endif
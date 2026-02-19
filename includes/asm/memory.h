/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:02:56 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 12:12:44 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
    Defines constants / macro to help with memory management
    Compliant with multiboot
*/
#ifndef  ASM_MEMORY_H
# define ASM_MEMORY_H

# define KERNEL_HIGHER_HALF_OFFSET 0xC0000000
# define KERNEL_PHYS_START 0x00100000
# define KERNEL_VIRT_START (KERNEL_HIGHER_HALF_OFFSET + KERNEL_PHYS_START)
# define KERNEL_PHYS(__virt) (__virt - KERNEL_HIGHER_HALF_OFFSET)
# define KERNEL_VIRT(__phys) (__phys + KERNEL_HIGHER_HALF_OFFSET)

# define KERNEL_STACK_SIZE 0x4000U

# define PAGE_SIZE 0x1000

# ifndef __ASSEMBLY__



# endif 

#endif
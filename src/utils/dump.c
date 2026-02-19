/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:29:51 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 16:30:07 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk/printk.h"

void print_stack_dump(int max_frames)
{
	u32 *ebp;
	u32 *esp;
	int i = 0;

	// Get current EBP and ESP
	__asm__ volatile ("movl %%ebp, %0" : "=r"(ebp));
	__asm__ volatile ("movl %%esp, %0" : "=r"(esp));

	printk("Stack dump (ebp=%p, esp=%p):\n", ebp, esp);
	while (ebp && i < max_frames)
	{
		u32 ret_addr = *(ebp + 1);
		printk("  [%02d] ebp=%p ret=0x%08x\n", i, ebp, ret_addr);
		ebp = (u32 *)(*ebp);
		i++;
	}
}
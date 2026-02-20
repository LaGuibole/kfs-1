/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:29:51 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/20 16:45:45 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk/printk.h"

void print_stack_dump()
{
    u32 *ebp;
    u32 *esp;
    int i = 0;

    // Get current EBP and ESP
    __asm__ volatile ("movl %%ebp, %0" : "=r"(ebp));
    __asm__ volatile ("movl %%esp, %0" : "=r"(esp));

    printk("Stack dump (ebp=%p, esp=%p):\n", ebp, esp);
    u32 *frame_esp = esp;
    while (ebp && i < ebp - esp)
    {
        u32 ret_addr = *(ebp + 1);
        u32 *next_ebp = (u32 *)(*ebp);
        printk("  [%02d] ebp=%p ret=0x%08x\n", i, ebp, ret_addr);

        // Dump stack contents for this frame
        u32 *dump_start = (i == 0) ? frame_esp : ebp + 2;
        u32 *dump_end = next_ebp ? next_ebp : dump_start + 32; // fallback limit

        int count = 0;
        for (u32 *p = dump_start; p < dump_end; p += 4)
        {
            // Print address at start of line
            if ((count % 16) == 0)
                printk("    %p: ", p);

            // Print 4 words per line
            for (int j = 0; j < 4 && p + j < dump_end; ++j)
                printk("%08x ", *(p + j));

            // Print ASCII
            printk(" |");
            for (int j = 0; j < 4 && p + j < dump_end; ++j)
            {
                u32 val = *(p + j);
                for (int k = 0; k < 4; ++k)
                {
                    char c = (val >> (k * 8)) & 0xFF;
                    printk("%c", (c >= 32 && c <= 126) ? c : '.');
                }
            }
            printk("|\n");
            count += 16;
        }

        ebp = next_ebp;
        i++;
    }
}
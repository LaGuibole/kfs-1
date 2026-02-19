/* Declaring constants for multiboot header */
#include <asm/memory.h>
#include <asm/multiboot.h>

.extern kernel_main										/* Declare external symbol for main kernel func */
.global _start											/* Make start label globally visible */
.global bootstrap_pde									/* Init paging directory entry */

/* Constants for paging */
.set PDE_PRESENT,      0x1								/* Page Directory Entry present flag */
.set PDE_RW,           0x2								/* Page Directory Entry R/W flag */
.set PDE_FLAGS,        PDE_PRESENT | PDE_RW				/* Previous flags compilation */
.set PAGE_TABLE_ADDR,  128								/* Physical addresse of the page table */
.set PAGE_SIZE_4MB,    0x00400000						/* 4MB offset for second page table */
.set NUM_PDE_IDENTITY, 2								/* Number of identity-mapped PDEs */
.set NUM_PDE_HIGHER,   2								/* Number of higher-half mapped PDEs */
.set NUM_PDE_TOTAL,    1024								/* Total number of PDEs in directory */

.section .bootstrap, "ax"								/* Bootstrap executable code section */
.type _start, @function									/* _start as function symbol */
_start:													/* Boot code entry point */
	cli													/* Clear interrupts */
	leal KERNEL_PHYS(bootstrap_pde), %ecx				/* Load physical address of bootstrap_pde into ECX */
	movl %ecx, %cr3										/* Set cr3 to PD base address */
	movl %cr4, %ecx										/* Load cr4 into ECX */
	orl $0x00000010, %ecx								/* Enable Physical Address Extension in cr4 */
	movl %ecx, %cr4										/* Write back into cr4 */
	movl %cr0, %ecx										/* cr0 into ECX */
	orl $0x80000001, %ecx								/* Enable paging and protected mode in cr0 */
	movl %ecx, %cr0										/* Write back to cr0 */
	movl $_higher_half, %ecx							/* Load address of _higher_half into ECX */
	jmp *%ecx											/* Jump to higher half & clear CPU pipeline */
	
.section .text, "ax"									/* Executable code section */
_higher_half:											/* Higher half kernel entry point */
	movl $kernel_stack_top, %esp						/* Stack pointer to top of kernel stack */
	pushl %eax											/* Push EAX (Multiboot magic) onto stack */
	pushl %ebx											/* Push EBX (Multiboot info pointer) onto stack */
	call kernel_main									/* Call main kernel func */
_1:														/* Infinite halt */
	hlt
	jmp _1

.section .data											/* Data section */
.align PAGE_SIZE										/* Align PD to page size */
bootstrap_pde:											/* Page Directory Entry table */
	.long PAGE_TABLE_ADDR + PDE_FLAGS					/* First PDE: identity map 0-4MB, present+RW */
	.long PAGE_SIZE_4MB + PAGE_TABLE_ADDR + PDE_FLAGS	/* Second PDE: identity map 4-8MB, present+RW */
	.rept (768 - NUM_PDE_IDENTITY)						/* Fill remaining identity PDEs with zeros */
	.long 0
	.endr
	.long PAGE_TABLE_ADDR + PDE_FLAGS					/* First higher-half PDE: map kernel to higher half */
	.long PAGE_SIZE_4MB + PAGE_TABLE_ADDR + PDE_FLAGS	/* Second higher-half PDE */
	.rept (256 - NUM_PDE_HIGHER)						/* Fill remaining higher-half PDEs with zeros */
	.long 0
	.endr

.section .bss											/* Uninitialized data section */
.align 16												/* Align kernel stack to 16 bytes */
kernel_stack_bottom:									/* Bottom of kernel stack */
	.skip KERNEL_STACK_SIZE								/* Reserve space for kernel stack */
.global kernel_stack_top								/* Make kernel_stack_top globally visible */
kernel_stack_top:										/* Rest is top of kernel stack */

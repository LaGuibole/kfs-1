/* Declaring constants for multiboot header */
#include <asm/memory.h>
#include <asm/multiboot.h>

.extern kernel_main										/* Declare external symbol for main kernel func */
.global _start											/* Make start label globally visible */
.extern bootstrap_pde									/* Init paging directory entry */

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

.section .bss											/* Uninitialized data section */
.align 16												/* Align kernel stack to 16 bytes */
kernel_stack_bottom:									/* Bottom of kernel stack */
	.skip KERNEL_STACK_SIZE								/* Reserve space for kernel stack */
.global kernel_stack_top								/* Make kernel_stack_top globally visible */
kernel_stack_top:										/* Rest is top of kernel stack */

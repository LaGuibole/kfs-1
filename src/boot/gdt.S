#include <asm/gdt.h>
.section .gdt, "a"
.align 16

/* -------------------------------------------------------------------------- */
/*                       Global Descriptor Table Layout                       */
/* -------------------------------------------------------------------------- */

/* ---- Each entry is 8 bytes. The selectors are offsets into this table. --- */
/* ----------------- 0x00: Null descriptor (required by x86) ---------------- */
/* ------------------------ 0x08: Kernel code segment ----------------------- */
/* ------------------------ 0x10: Kernel data segment ----------------------- */
/* ------------------ 0x18: Kernel stack segment (optional) ----------------- */
/* ------------------------- 0x20: User code segment ------------------------ */
/* ------------------------- 0x28: User data segment ------------------------ */
/* ------------------- 0x30: User stack segment (optional) ------------------ */

gdt_start:
	.quad 0x0000000000000000		/* Null descriptor (never used) */

gdt_kernel_code:
	.word 0xFFFF					/* Segment limit (low 16 bits) */
	.word 0x0000					/* Base address (low 16 bits) */
	.byte 0x00						/* Base address (next 8 bits) */
	.byte GDT_ACCESS_KERNEL_CODE	/* Access byte (see gdt.h) */
	.byte GDT_FLAGS_STANDARD		/* Flags (see gdt.h) */
	.byte 0x00						/* Base address (high 8 bits) */

gdt_kernel_data:
	.word 0xFFFF
	.word 0x0000
	.byte 0x00
	.byte GDT_ACCESS_KERNEL_DATA
	.byte GDT_FLAGS_STANDARD
	.byte 0x00

gdt_kernel_stack:
	.word 0xFFFF
	.word 0x0000
	.byte 0x00
	.byte GDT_ACCESS_KERNEL_STACK
	.byte GDT_FLAGS_STANDARD
	.byte 0x00

gdt_user_code:
	.word 0xFFFF
	.word 0x0000
	.byte 0x00
	.byte GDT_ACCESS_USER_CODE
	.byte GDT_FLAGS_STANDARD
	.byte 0x00

gdt_user_data:
	.word 0xFFFF
	.word 0x0000
	.byte 0x00
	.byte GDT_ACCESS_USER_DATA
	.byte GDT_FLAGS_STANDARD
	.byte 0x00

gdt_user_stack:
	.word 0xFFFF
	.word 0x0000
	.byte 0x00
	.byte GDT_ACCESS_USER_STACK
	.byte GDT_FLAGS_STANDARD
	.byte 0x00

gdt_end:

gdt_pointer:
	.word gdt_end - gdt_start - 1
	.long gdt_start

.global init_gdt
.section .text, "ax"

init_gdt:
	lgdt gdt_pointer				/* Load the GDT register with the address and size of our GDT */
	ljmp $0x8, $flush				/* Far jump to reload CS with the new GDT's code segment selector (0x8 = kernel code) */
flush:
	mov $0x10, %eax           		/* 0x10 = kernel data segment selector */
	mov %eax, %ds             		/* Reload DS with kernel data segment */
	mov %eax, %ss             		/* Reload SS with kernel data segment */
	mov %eax, %es             		/* Reload ES with kernel data segment */
	mov %eax, %fs             		/* Reload FS with kernel data segment */
	mov %eax, %gs             		/* Reload GS with kernel data segment */
	ret                       		/* Return to caller (now running with new GDT) */
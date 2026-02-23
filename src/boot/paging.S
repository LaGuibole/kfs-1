/* Declaring constants for multiboot header */
#include <asm/memory.h>
#include <asm/multiboot.h>

.global bootstrap_pde

/* Constants for paging */
.set PDE_PRESENT,      0x1								/* Page Directory Entry present flag */
.set PDE_RW,           0x2								/* Page Directory Entry R/W flag */
.set PDE_FLAGS,        PDE_PRESENT | PDE_RW				/* Previous flags compilation */
.set PAGE_TABLE_ADDR,  128								/* Physical addresse of the page table */
.set PAGE_SIZE_4MB,    0x00400000						/* 4MB offset for second page table */
.set NUM_PDE_IDENTITY, 2								/* Number of identity-mapped PDEs */
.set NUM_PDE_HIGHER,   2								/* Number of higher-half mapped PDEs */
.set NUM_PDE_TOTAL,    1024								/* Total number of PDEs in directory */

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
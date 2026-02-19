#include <asm/multiboot.h>

.extern multiboot_header

.section .multiboot, "a"
.align 4 // Align to 4KB (32-bits)
multiboot_header:
header_start:
    .long MULTIBOOT2_HEADER_MAGIC /* Holy magic number */
    .long MULTIBOOT_ARCHITECTURE_I386 /* Defines arch */
    .long header_end - header_start /* Header length */
    .long -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + (header_end - header_start)) /* Checksum to validate header */
    .word 0 /* Filling with zeros */
    .word 0 /* Filling with zeros */
    .long 8 /* Define end of multiboot header tag */
header_end:
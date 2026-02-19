OUTPUT_FORMAT(elf32-i386)         /* Output format: 32-bit ELF for i386 */
ENTRY(_start)                     /* Kernel entry point symbol */

_kernel_higher_half_offset = 0xC0000000;      /* Offset for higher-half kernel mapping */
_kernel_physical_start = 0x00100000;          /* Physical address where kernel is loaded (1 MiB) */
_kernel_virtual_start = _kernel_physical_start + _kernel_higher_half_offset; /* Virtual base address */

/* Section layout for the kernel binary */
SECTIONS {
    . = 0x800;                    /* Set initial location counter (for GDT, before kernel) */

    .gdt ALIGN(4K) : {            /* Global Descriptor Table section, page-aligned */
        KEEP(*(.gdt))             /* Keep all .gdt sections from input files */
    }

    . = _kernel_physical_start;   /* Move location counter to kernel physical start (1 MiB) */

    .bootstrap ALIGN(4K) : {      /* Bootstrap section, page-aligned */
        KEEP(*(.multiboot))       /* Keep the multiboot header section (must be first in kernel) */
        *(.bootstrap)            /* Include all .bootstrap sections */
    }

    . = ALIGN(4K);                /* Align to next 4K boundary */
    . += _kernel_higher_half_offset; /* Switch to higher-half virtual addresses */

    .text ALIGN(4K): AT(ADDR(.text) - _kernel_higher_half_offset) { /* Code section, page-aligned */
        *(.text)                  /* Include all .text sections */
    }

    .rodata ALIGN(4K): AT(ADDR(.rodata) - _kernel_higher_half_offset) { /* Read-only data section */
        *(.rodata)                /* Include all .rodata sections */
    }

    .bss ALIGN(4K): AT(ADDR(.bss) - _kernel_higher_half_offset) {     /* Uninitialized data section */
        *(.bss)                   /* Include all .bss sections */
        *(COMMON)                 /* Include common symbols */
    }

    .data ALIGN(4K): AT(ADDR(.data) - _kernel_higher_half_offset) {   /* Initialized data section */
        *(.data)                  /* Include all .data sections */
    }

    . = ALIGN(4K);                /* Align to next 4K boundary */
    phys_kernel_end = . - _kernel_higher_half_offset; /* Mark end of kernel in physical memory */
}
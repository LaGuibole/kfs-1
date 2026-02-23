#include "memory/paging.h"
#include "mem.h"

static page_directory_t *kernel_directory = NULL;

// void paging_init() {
// 	kernel_directory = (page_directory_t*)ALIGN_PAGE_UP(0x100000); // or use your allocator
// 	memset(kernel_directory, 0, sizeof(page_directory_t));

// 	// Identity map the first 8MB (for boot, multiboot info, etc.)
// 	for (int i = 0; i < 2; i++) {
// 		page_table_t *table = (page_table_t*)ALIGN_PAGE_UP(0x101000 + i * PAGE_SIZE);
// 		memset(table, 0, sizeof(page_table_t));
// 		for (int j = 0; j < PAGE_ENTRIES; j++) {
// 			table->entries[j] = (i * PAGE_ENTRIES + j) * PAGE_SIZE | PAGE_PRESENT | PAGE_RW;
// 		}
// 		kernel_directory->entries[i] = ((uint32_t)table) | PAGE_PRESENT | PAGE_RW;
// 	}

// 	// Map the higher half (kernel)
// 	for (int i = 0; i < 2; i++) {
// 		page_table_t *table = (page_table_t*)ALIGN_PAGE_UP(0x103000 + i * PAGE_SIZE);
// 		memset(table, 0, sizeof(page_table_t));
// 		for (int j = 0; j < PAGE_ENTRIES; j++) {
// 			table->entries[j] = (i * PAGE_ENTRIES + j) * PAGE_SIZE | PAGE_PRESENT | PAGE_RW;
// 		}
// 		kernel_directory->entries[768 + i] = ((uint32_t)table) | PAGE_PRESENT | PAGE_RW;
// 	}

// 	__asm__ volatile("mov %0, %%cr3" :: "r"(kernel_directory));
//     u32 cr0;
//     __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
//     cr0 |= 0x80000001; // Enable paging and protected mode
//     __asm__ volatile("mov %0, %%cr0" :: "r"(cr0));
// }
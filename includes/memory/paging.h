#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

/* Paging constants */
#define PAGE_SIZE           0x1000      // 4KB
#define PAGE_ENTRIES        1024        // Entries per page table/directory

/* Page flags */
#define PAGE_PRESENT        0b0000000001
#define PAGE_RW             0b0000000010
#define PAGE_USER           0b0000000100
#define PAGE_PWT            0b0000001000
#define PAGE_PCD            0b0000010000
#define PAGE_ACCESSED       0b0000100000
#define PAGE_DIRTY          0b0001000000
#define PAGE_4MB            0b0010000000
#define PAGE_GLOBAL         0b0100000000

/* Address manipulation */
#define PAGE_FRAME_MASK     0xFFFFF000

#define IS_PAGE_ALIGNED(x)  (!((x) & 0xFFF))
#define ALIGN_PAGE_UP(x)    (((x) + PAGE_SIZE - 1) & PAGE_FRAME_MASK)
#define ALIGN_PAGE_DOWN(x)  ((x) & PAGE_FRAME_MASK)

/* Page table entry and directory entry are just uint32_t */
typedef uint32_t page_entry_t;

/* Page table: 1024 entries */
typedef struct {
    page_entry_t entries[PAGE_ENTRIES];
} page_table_t;

/* Page directory: 1024 entries */
typedef struct {
    page_entry_t entries[PAGE_ENTRIES];
} page_directory_t;

/* Helper macros for page table/directory manipulation */
#define PAGE_SET_FRAME(entry, addr)   ((entry) = ((entry) & ~PAGE_FRAME_MASK) | ((addr) & PAGE_FRAME_MASK))
#define PAGE_GET_FRAME(entry)         ((entry) & PAGE_FRAME_MASK)
#define PAGE_SET_FLAGS(entry, flags)  ((entry) |= (flags))
#define PAGE_CLEAR_FLAGS(entry, flags) ((entry) &= ~(flags))

// void    paging_init();

#endif // PAGING_H
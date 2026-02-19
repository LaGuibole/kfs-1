#ifndef GDT_H
# define GDT_H

#include "types.h"

#define GDT_ENTRIES 7
#define GDT_ADDRESS  0x00000800

struct gdt_entry_struct
{
    u16 limit;
    u16 base_low;
    u8  base_middle;
    u8  access;
    u8  flags;
    u8  base_high;
}__attribute__((packed));

struct gdt_ptr_struct
{
    u16 limit;
    unsigned int base;
}__attribute__((packed));

void init_gdt();
void set_gdt_gate(u32 num, u32 base, u32 limit, u8 access, u8 gran);

# endif
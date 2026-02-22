#include "gdt.h"
#include "printk/printk.h"
#include "asm/memory.h"

extern void gdt_flush(u32 ptr);

struct gdt_entry_struct gdt_entries[GDT_ENTRIES] __attribute__((section(".gdt")));
struct gdt_ptr_struct   gdt_ptr;

void init_gdt()
{
	gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * GDT_ENTRIES) - 1;
	gdt_ptr.base = (u32)&gdt_entries;

	set_gdt_gate(0,0,0,0,0);            		// null segment - convention
	set_gdt_gate(1,0,0xFFFFFFFF,0x9A,0xCF);		// kernel code segment
	set_gdt_gate(2,0,0xFFFFFFFF,0x92,0xCF);		// kernel data segment
	set_gdt_gate(3,0,0xFFFFFFFF,0x96,0xCF);		// kernel stack
	set_gdt_gate(4,0,0xFFFFFFFF,0xFA,0xCF);		// User code segment
	set_gdt_gate(5,0,0xFFFFFFFF,0xF2,0xCF);		// User data segment
	set_gdt_gate(6,0,0xFFFFFFFF,0xF6,0xCF);		// User stack

	gdt_flush(((u32)&gdt_ptr));
}

void set_gdt_gate(u32 num, u32 base, u32 limit, u8 access, u8 gran)
{
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;

	gdt_entries[num].limit = (limit & 0xFFFF);
	gdt_entries[num].flags = (limit >> 16) & 0x0F;
	gdt_entries[num].flags |= (gran & 0xF0);

	gdt_entries[num].access = access;
}

static void decode_gdt_entry(u8 *entry, u32 *base, u32 *limit, u8 *type, u8 *dpl, u8 *present)
{
    *limit   = (entry[0]) | (entry[1] << 8) | ((entry[6] & 0x0F) << 16);
    *base    = (entry[2]) | (entry[3] << 8) | (entry[4] << 16) | (entry[7] << 24);
    *type    = entry[5] & 0x0F;
    *dpl     = (entry[5] >> 5) & 0x03;
    *present = (entry[5] >> 7) & 0x01;

    if (entry[6] & 0x80)
        *limit = (*limit << 12) | 0xFFF;
}

void print_gdt_dump()
{
    struct gdt_ptr_struct gdtr_value;
    __asm__ volatile ("sgdt %0" : "=m"(gdtr_value));

    u8  *gdt     = (u8 *)gdtr_value.base;
    u16  entries = (gdtr_value.limit + 1) / 8;

    printk("GDT base: 0x%08x  limit: 0x%04x  (%u entries)\n\n",
           gdtr_value.base, gdtr_value.limit, entries);

    printk("%-5s  %-10s  %-10s  %-6s  %-4s  %-7s  %s\n",
           "IDX", "BASE", "LIMIT", "TYPE", "DPL", "PRESENT", "RAW");
    printk("-----  ----------  ----------  ------  ----  -------"
           "  -----------------------\n");

    for (u16 i = 0; i < entries; i++) {
        u8  *entry = &gdt[i * 8];
        u32  base, limit;
        u8   type, dpl, present;

        decode_gdt_entry(entry, &base, &limit, &type, &dpl, &present);

        printk("[%03u]  0x%08x  0x%08x  0x%02x    %u     %s"
               "        %02x %02x %02x %02x %02x %02x %02x %02x\n",
               i,
               base, limit,
               type, dpl,
               present ? "yes" : "no ",
               entry[0], entry[1], entry[2], entry[3],
               entry[4], entry[5], entry[6], entry[7]);
    }
}

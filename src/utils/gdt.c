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

void print_gdt_dump()
{
    struct gdt_ptr_struct gdtr_value;
    __asm__ volatile ("sgdt %0" : "=m"(gdtr_value));
    printk("GDT base: 0x%08x, limit: 0x%04x\n", gdtr_value.base, gdtr_value.limit);
	u8 *gdt = (u8 *)gdtr_value.base;
    for (u16 i = 0; i < gdtr_value.limit + 1; i += 8) {
        printk("GDT[%02d]: ", i / 8);
        for (int j = 0; j < 8; j++) {
            printk("%02x ", gdt[i + j]);
        }
        printk("\n");
    }
}

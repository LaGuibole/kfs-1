#include "gdt.h"

extern void gdt_flush(u32 ptr);

struct gdt_entry_struct gdt_entries[GDT_ENTRIES];
struct gdt_ptr_struct   *gdt_ptr = (struct gdt_ptr_struct*)GDT_ADDRESS;

void init_gdt()
{
	gdt_ptr->limit = (sizeof(struct gdt_entry_struct) * GDT_ENTRIES) - 1;
	gdt_ptr->base = (u32)&gdt_entries;

	set_gdt_gate(0,0,0,0,0);            		// null segment - convention
	set_gdt_gate(1,0,0xFFFFFFFF,0x9A,0xCF);		// kernel code segment
	set_gdt_gate(2,0,0xFFFFFFFF,0x92,0xCF);		// kernel data segment
	set_gdt_gate(3,0,0xFFFFFFFF,0x96,0xCF);		// kernel stack
	set_gdt_gate(4,0,0xFFFFFFFF,0xFA,0xCF);		// User code segment
	set_gdt_gate(5,0,0xFFFFFFFF,0xF2,0xCF);		// User data segment
	set_gdt_gate(6,0,0xFFFFFFFF,0xF6,0xCF);		// User stack

	gdt_flush((u32)gdt_ptr);
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

#include "gdt.h"
#include "printk/printk.h"
#include "asm/memory.h"

extern void gdt_flush(u32 ptr);

struct gdt_entry_struct gdt_entries[GDT_ENTRIES] __attribute__((section(".gdt")));
struct gdt_ptr_struct   gdt_ptr;


/*
	Inits GDT 
	Steps : 1 - Configure GDT pointer
			2 - fill GDT segments (null, kernel code/data/stack, user code/data/stack)
			3 - Flush GDT into GDTR register via assembly stub
*/
void init_gdt()
{
	// step 1
	gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * GDT_ENTRIES) - 1;
	gdt_ptr.base = (u32)&gdt_entries;
	// step 2
	set_gdt_gate(0,0,0,0,0);            		// null segment - convention
	set_gdt_gate(1,0,0xFFFFFFFF,0x9A,0xCF);		// kernel code segment
	set_gdt_gate(2,0,0xFFFFFFFF,0x92,0xCF);		// kernel data segment
	set_gdt_gate(3,0,0xFFFFFFFF,0x96,0xCF);		// kernel stack
	set_gdt_gate(4,0,0xFFFFFFFF,0xFA,0xCF);		// User code segment
	set_gdt_gate(5,0,0xFFFFFFFF,0xF2,0xCF);		// User data segment
	set_gdt_gate(6,0,0xFFFFFFFF,0xF6,0xCF);		// User stack
	// step 3
	gdt_flush(((u32)&gdt_ptr));
}

/*
	Fill a GDT Entry :
	num		= Segment index (0-6)
	base	= Start adress of the segment
	limit	= Size of the segments (0xFFFFFFFF = 4gb flat)
	access	= Access byte (present, DPL, type flags)
	gran	= Granularity byte (page granularity, 32-bit, limit high nibble)
*/
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

/*
	Decode a raw 8-byte GDT entry into fields
	Steps : 
		1 - Reconstruct 20-bit limit from byte 0-1 and high nibble of byte 6
		2 - Reconstruct the 32-bit base from bytes 2,3,4, 7
		3 - Extract type, DPL and present bit from the access byte (byte 5)
		4 - If granularityu bit is set,s cale limit to page gran (shift + fill low 12 bits) (4GB)
*/
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


/*
	Dump the current GDT loaded in GDTR
	Steps :
		1 - Read GTDR register to get base and limit of the active GDT
		2 - Compute number of entries from the limit 
		3 - Iterate over each entry, decode it and print fiels + raw bytes
*/
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
		 "      %02x %02x %02x %02x %02x %02x %02x %02x\n",
		 i,
		 base, limit,
		 type, dpl,
		 present ? "yes" : "no ",
		 entry[0], entry[1], entry[2], entry[3],
		 entry[4], entry[5], entry[6], entry[7]);
    }
}

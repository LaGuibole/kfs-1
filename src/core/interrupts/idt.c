#include "idt.h"
#include "printk/printk.h"
#include "shell/term.h"

static idt_entry_t  idt[IDT_ENTRIES];
static idt_ptr_t    idt_ptr;

/*
	Fill a IDT Entry
	num = Interruption number (0-255)
	handler = address of the C function
	selector = CS Kernel selector (0x0008)
	flags = 0x8E interrupt gate 32-buits, DPL=0, present
*/
void idt_set_gate(u8 num, u32 handler, u16 selector, u8 flags)
{
	idt[num].offset_low = handler & 0xFFFF;				// lower 16 bits
	idt[num].offset_high = (handler >> 16) & 0xFFFF;	// higher 16 bits
	idt[num].selector = selector;
	idt[num].zero = 0;
	idt[num].flags = flags;
}

/*
	Function to init IDT
	Steps: 
		1 - Configure IDT pointer
		2 - FIll IDT with a generic handler, this way no interrupt will fall in the VOIIIIID
		3 - Plug the keyboard handler on INT 0x21
		4 - Load IDT into IDTR register
*/
void init_idt()
{
	//step 1
	idt_ptr.limit = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;
	idt_ptr.base = (u32)&idt;
	// step 2
	extern void isr_default(void);
	for (int i = 0; i < IDT_ENTRIES; i++)
		idt_set_gate(i, (u32)isr_default, 0x0008, 0x8E);
	// step 3
	extern void isr_keyboard(void);
	    idt_set_gate(0x21, (u32)isr_keyboard, 0x0008, 0x8E);
	//step 4
	__asm__ volatile("lidt %0" : : "m"(idt_ptr));
}

void print_idt(void)
{
    int printed = 0;

    terminal_putstr("------------------------------------------------------------\n");
    terminal_putstr("Vec  | Base       | Sel    | Flags | Type\n");
    terminal_putstr("------------------------------------------------------------\n");

    for (int i = 29; i < IDT_ENTRIES && printed < IDT_PRINT_MAX; i++)
    {
        idt_entry_t *entries = &idt[i];
        u32 base = ((u32)entries->offset_high << 16) | entries->offset_low;

        if (base == 0)
            continue;

        const char *type = "UNKNOWN";
        u8 gate_type = entries->flags & 0x0F;
        if (gate_type == 0xE)       type = "INT GATE";
        else if (gate_type == 0xF)  type = "TRAP GATE";
        else if (gate_type == 0x5)  type = "TASK GATE";

        printk("%3d  | 0x%08x | 0x%04x | 0x%02x  | %s%s\n",
            i,
            base,
            entries->selector,
            entries->flags,
            type,
            (i == 0x21) ? " <-- KEYBOARD" : ""
        );
        printed++;
    }

    if (printed == IDT_PRINT_MAX)
        terminal_putstr("... limited print, increase IDT_PRINT_MAX to see all 256 entries ! ;)\n");
    terminal_putstr("------------------------------------------------------------\n");
}
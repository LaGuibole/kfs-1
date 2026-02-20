#ifndef IDT_H
# define IDT_H

#include "types.h"

#define IDT_ENTRIES 256

/*
	Structure for 1 IDT Entry (8 bytes)
*/
typedef struct {
	u16 offset_low;     // 0-15 bits address handler
	u16 selector;       // kernel CS segment selector (0x0008)
	u8  zero;			// always 0
	u8  flags;			// P (Present)| DPL (Descriptor Privilege Level 0:kernel 3:user) | type (0x8E for interrupt gate ; disable IRQ for the handler)
	u16 offset_high;	// 16-31 bits adress handler
} __attribute__((packed)) idt_entry_t;

/*
	Descriptor for lidt (same as lgdt)
*/
typedef struct {
	u16 limit;			// IDT size - 1
	u32 base;			// IDT address
} __attribute__((packed)) idt_ptr_t;

void init_idt();
void set_idt_gate(u8 num, u32 handler, u16 selector, u8 flags);

#endif
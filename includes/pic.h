#ifndef     PIC_H
# define    PIC_H

#include "types.h"

// PIC I/O PORTS
#define PIC_MASTER_CMD      0x20
#define PIC_MASTER_DATA     0x21
#define PIC_SLAVE_CMD       0xA0
#define PIC_SLAVE_DATA      0xA1

// Base vectors after remapping
#define PIC_MASTER_OFFSET   0x20    // IRQ0 -> INT 0x20
#define PIC_SLAVE_OFFSET    0x28    // IRQ8 -> INT 0x28

#define ICW1_INIT           0x11

#define ICW4_8086           0x01

void pic_remap(u8 master_offset, u8 slave_offset);
void pic_send_eoi(u8 irq);

void pic_mask_irq(u8 irq);
void pic_unmask_irq(u8 irq);

#endif
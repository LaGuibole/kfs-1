#include "pic.h"
#include "io.h"

/*
	io_wait adds a delay after an outb on a selected pic port
	older PIC could be quite slow, if we do not add delay we will
	be in risk to send the next command while the first one isn't properly
	treated.
	Writing on 0x80 (POST diag port) is a common technique (i believe its what linux does)
	0x80 is a sort of dummy port
*/
static void io_wait()
{
	outb(0x80, 0);
}

/*
	Remap offsets interruptions between PIC Master & Slave
	By default, PIC maps IRQ on vectors 0x08-0x0F which collides with
	CPU exceptions.
	We will remap them to 0x20 and 0x28 (free spaces)
	Steps :
		1 - Save current masks
		2 - Sending ICW1 to launch init
		3 - Sending new offsets (ICW2) 
		4 - Master / SLave config (ICW3)
		5 - Switch to 8086 mode (ICW4)
		6 - Restoring origins masks
*/
void pic_remap(u8 master_offset, u8 slave_offset)
{
	// step 1 
	u8 master_mask = inb(PIC_MASTER_DATA);
	u8 slave_mask = inb(PIC_SLAVE_DATA);
	// step 2
	outb(PIC_MASTER_CMD, ICW1_INIT); io_wait();
	outb(PIC_SLAVE_CMD, ICW1_INIT); io_wait();
	// step 3
	outb(PIC_MASTER_DATA, master_offset); io_wait();
	outb(PIC_SLAVE_DATA, slave_offset); io_wait();
	// step 4
	outb(PIC_MASTER_DATA, 0x04); io_wait();
	outb(PIC_SLAVE_DATA, 0x02); io_wait();
	// step 5
	outb(PIC_MASTER_DATA, ICW4_8086); io_wait();
	outb(PIC_SLAVE_DATA, ICW4_8086); io_wait();
	// step 6
	outb(PIC_MASTER_DATA, master_mask);
	outb(PIC_SLAVE_DATA, slave_mask);
}

/*
	EOI = End Of Interrupt
	Aims to tell the PIC that the interruoion has been treated
	If the interruption request (IRQ) comes from the slave, we need to send eoi
	to both, master doen't know that slave has terminated its instruction
*/
void pic_send_eoi(u8 irq)
{
	if (irq >= 8)
		outb(PIC_SLAVE_CMD, 0x20);
	outb(PIC_MASTER_CMD, 0x20);
}

/*
	Disable a given IRQ
*/
void pic_mask_irq(u8 irq)
{
	u16 port;
	u8	value;

	if (irq < 8)
		port = PIC_MASTER_DATA; 
	else 
	{
		port = PIC_SLAVE_DATA;
		irq -= 8;
	}
	value = inb(port) | (1 << irq);
	outb(port, value);
}

/*
	Reactivate a given IRQ
*/
void pic_unmask_irq(u8 irq)
{
	u16 port;
	u8 value;

	if (irq < 8)
		port = PIC_MASTER_DATA;
	else
	{
		port = PIC_SLAVE_DATA;
		irq -= 8;
	}
	value = inb(port) & ~(1 << irq);
	outb(port, value);
}
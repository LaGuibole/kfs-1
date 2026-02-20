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
	outb(0, 0x80);
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
	//step 1
	u8 master_mask = inb(PIC_MASTER_DATA);
	u8 slave_mask = inb(PIC_SLAVE_DATA);
	// step 2
	outb(ICW1_INIT, PIC_MASTER_CMD); io_wait();
	outb(ICW1_INIT, PIC_SLAVE_CMD);  io_wait();
	// step 3
	outb(master_offset, PIC_MASTER_DATA); io_wait();
	outb(slave_offset,  PIC_SLAVE_DATA);  io_wait();
	// step 4
	outb(0x04, PIC_MASTER_DATA); io_wait();
	outb(0x02, PIC_SLAVE_DATA);  io_wait();
	// step 5
	outb(ICW4_8086, PIC_MASTER_DATA); io_wait();
	outb(ICW4_8086, PIC_SLAVE_DATA);  io_wait();
	// step 6
	outb(master_mask, PIC_MASTER_DATA);
	outb(slave_mask,  PIC_SLAVE_DATA);
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
		outb(0x20, PIC_SLAVE_CMD);
	outb(0x20, PIC_MASTER_CMD);
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
	outb(value, port);
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
	outb(value, port);
}
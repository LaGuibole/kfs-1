#include "pic.h"
#include "io.h"


/*
    Will be called for any interruption that is not keyboard related
*/
void default_handler()
{
    // panic
}

void keyboard_handler()
{
    u8 scancode = inb(0x60);
    // todo : traduire le scandoe 
    pic_send_eoi(1); // IRQ1 => send EOI on PIC master
}

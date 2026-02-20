#include "pic.h"
#include "io.h"
#include "keyboard.h"
#include "term.h"


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
    
    char c = keyboard_scancode_ascii(scancode);
    if (c != 0)
    {
        if (c >= KEY_F1 && c <= KEY_F10)
            terminal_switch_tab(c % KEY_F1);
        else
            terminal_putchar(c);
    }
    pic_send_eoi(1); // IRQ1 => send EOI on PIC master
}


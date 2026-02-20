#include "pic.h"
#include "io.h"
#include "keyboard.h"
#include "term.h"
#include "printk/printk.h"


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
        if (scancode >= KEY_F1 && scancode <= KEY_F10)
            terminal_switch_tab(c % 0xFFFFFFF0 - 1);    
        else if (c == '\b')
            terminal_backspace();
        else
            terminal_putchar(c);
    }
    pic_send_eoi(1); // IRQ1 => send EOI on PIC master
}


#include "pic.h"
#include "io.h"
#include "keyboard.h"
#include "shell/exec.h"
#include "shell/tabs.h"
#include "printk/printk.h"


/*
    Will be called for any interruption that is not keyboard related
*/
void default_handler()
{
    // panic
}

// void keyboard_handler()
// {
//     u8 scancode = inb(0x60);
    
//     char c = keyboard_scancode_ascii(scancode);
//     if (c != 0)
//     {
//         if (scancode >= KEY_F1 && scancode <= KEY_F10)
//             tab_switch(c % 0xFFFFFFF0 - 1);    
//         else if (c == '\b')
//             terminal_backspace();
//         else if (c == '\n')
//         {
//             shell_exec((char *)tabs[selected_tab].input_buffer);
//             tabs[selected_tab].input_len = 0;
//             tabs[selected_tab].input_buffer[0] = '\0';  
//         }
//         else
//             terminal_putchar(c);
//     }
//     pic_send_eoi(1); // IRQ1 => send EOI on PIC master
// }

void keyboard_handler()
{
    u8 scancode = inb(0x60);
    
    char c = keyboard_scancode_ascii(scancode);
    if (c != 0)
    {
        if (scancode >= KEY_F1 && scancode <= KEY_F10)
            tab_switch(c % 0xFFFFFFF0 - 1);    
        else if (c == '\b')
        {
            if (tabs[selected_tab].input_len > 0)
            {
                tabs[selected_tab].input_len--;
                tabs[selected_tab].input_buffer[tabs[selected_tab].input_len] = '\0';
            }
            terminal_backspace();
        }
        else if (c == '\n')
        {
            shell_exec((char *)tabs[selected_tab].input_buffer);
            tabs[selected_tab].input_len = 0;
            tabs[selected_tab].input_buffer[0] = '\0';  
        }
        else
        {
            u16 len = tabs[selected_tab].input_len;
            if (len < INPUT_BUFFER_SIZE - 1)
            {
                tabs[selected_tab].input_buffer[len] = c;
                tabs[selected_tab].input_buffer[len + 1] = '\0';
                tabs[selected_tab].input_len++;
            }
            terminal_putchar(c);
        }
    }
    pic_send_eoi(1);
}
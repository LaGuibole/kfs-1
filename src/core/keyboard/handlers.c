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
    // panic to do
}

/*
    Keyboard Interrupt Handle (mapped on INT 0x21 / 33)
    Steps : 
        1 - Read scancode from keyboard I/O port 0x60
        2 - Convert scancode to ASCII vhar
        3 - if F1-F10 switch to corresponding tab
        4 - If backspace : erase
        5 - If enter : execute buffered cmd
        6 - Otherwise : append char in buffer
        7 - Send eoi to PIC
*/
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
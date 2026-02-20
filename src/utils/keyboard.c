#include "pic.h"
#include "io.h"
#include "types.h"
#include "keyboard.h"

static u8 shift_pressed = 0;
static u8 caps_lock = 0;

char keyboard_scancode_ascii(u8 scancode)
{
    if (scancode & 0x80)
    {
        u8 released = scancode & 0x7F; // take off bit 7
        if (released == SC_LSHIFT || released == SC_RSHIFT)
            shift_pressed = 0;
        return 0; // no need to produce a char
    }

    // modifiers handling
    if (scancode == SC_LSHIFT || scancode == SC_RSHIFT)
    {
        shift_pressed = 1;
        return 0;
    }
    if (scancode == SC_CAPS)
    {
        caps_lock = !caps_lock;
        return 0;
    }

    u8 use_upper = shift_pressed ^ caps_lock; // invert shift effect if caps lkock

    char c = use_upper ? scancode_table_upper[scancode] : scancode_table_lower[scancode];
    return c;
}
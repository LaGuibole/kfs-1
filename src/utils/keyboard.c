#include "pic.h"
#include "io.h"
#include "types.h"
#include "keyboard.h"

static u8 shift_pressed = 0;
static u8 caps_lock = 0;
static u8 is_extended_scancode = 0;

static const char scancode_table_lower[128] = {
/*00*/  0,    0,    '1',  '2',  '3',  '4',  '5',  '6',
/*08*/  '7',  '8',  '9',  '0',  '-',  '=',  '\b', '\t',
/*10*/  'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',
/*18*/  'o',  'p',  '[',  ']',  '\n', 0,    'a',  's',
/*20*/  'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',
/*28*/  '\'', '`',  0,    '\\', 'z',  'x',  'c',  'v',
/*30*/  'b',  'n',  'm',  ',',  '.',  '/',  0,    '*',
/*38*/  0,    ' ',  0,    0xF0 + 1,   0xF0 + 2,   0xF0 + 3,   0xF0 + 4,   0xF0 + 5,
/*40*/  0xF0 + 6,   0xF0 + 7,   0xF0 + 8,   0xF0 + 9,   0xF0 + 10,  0,    0,    '7',
/*48*/  '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
/*50*/  '2',  '3',  '0',  '.',  0,    0,    0,    0,
/*58*/  0,  0,    0,    0,    0,    0,    0,    0,
/*60*/  0,    0,    0,    0,    0,    0,    0,    0,
/*68*/  0,    0,    0,    0,    0,    0,    0,    0,
/*70*/  0,    0,    0,    0,    0,    0,    0,    0,
/*78*/  0,    0,    0,    0,    0,    0,    0,    0,
};

static const char scancode_table_upper[128] = {
/*00*/  0,    0,    '!',  '@',  '#',  '$',  '%',  '^',
/*08*/  '&',  '*',  '(',  ')',  '_',  '+',  '\b', '\t',
/*10*/  'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',
/*18*/  'O',  'P',  '{',  '}',  '\n', 0,    'A',  'S',
/*20*/  'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':',
/*28*/  '"',  '~',  0,    '|',  'Z',  'X',  'C',  'V',
/*30*/  'B',  'N',  'M',  '<',  '>',  '?',  0,    '*',
/*38*/  0,    ' ',  0,    0xF0 + 1,   0xF0 + 2,   0xF0 + 3,   0xF0 + 4,   0xF0 + 5,
/*40*/  0xF0 + 6,   0xF0 + 7,   0xF0 + 8,   0xF0 + 9,   0xF0 + 10,  0,    0,    '7',
/*48*/  '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
/*50*/  '2',  '3',  '0',  '.',  0,    0,    0,    0,
/*58*/  0,  0,    0,    0,    0,    0,    0,    0,
/*60*/  0,    0,    0,    0,    0,    0,    0,    0,
/*68*/  0,    0,    0,    0,    0,    0,    0,    0,
/*70*/  0,    0,    0,    0,    0,    0,    0,    0,
/*78*/  0,    0,    0,    0,    0,    0,    0,    0,
};

char keyboard_scancode_ascii(u8 scancode)
{
    if (scancode == 0xE0)
    {
        is_extended_scancode = 1;
        return 0;
    }

    if (is_extended_scancode)
    {
        is_extended_scancode = 0;
        return 0;
    }

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
#ifndef KEYBOARD_H
# define KEYBOARD_H

#include "types.h"

#define KEY_INVALID 	0x00
#define KEY_SHIFT		0x01
#define KEY_CTRL		0x02
#define KEY_ALT			0x03
#define KEY_CAPS		0x04
#define	KEY_ENTER		'\n'
#define	KEY_BAKCSPACE	'\b'
#define KEY_TAB			'\t'

// Modifiers
#define SC_LSHIFT		0x2A
#define	SC_RSHIFT		0x36
#define	SC_CAPS			0x3A

void keyboard_init();
char keyboard_scancode_ascii(u8 scancode);

#endif
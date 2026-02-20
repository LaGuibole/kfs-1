#ifndef KEYBOARD_H
# define KEYBOARD_H

#include "types.h"

#define KEY_INVALID 	0x00
#define KEY_SHIFT		0x01
#define KEY_CTRL		0x02
#define KEY_ALT			0x03
#define KEY_CAPS		0x04
#define	KEY_ENTER		'\n'
#define	KEY_BACKSPACE	'\b'
#define KEY_TAB			'\t'

// Modifiers
#define SC_LSHIFT		0x2A
#define	SC_RSHIFT		0x36
#define	SC_CAPS			0x3A

// Functiosn
#define KEY_F1			0x3B
#define KEY_F2			0x3C
#define KEY_F3			0x3D
#define KEY_F4			0x3E
#define KEY_F5			0x3F
#define KEY_F6			0x40
#define KEY_F7			0x41
#define KEY_F8			0x42
#define KEY_F9			0x43
#define KEY_F10			0x44
#define KEY_F11			0		//0x57 unset
#define KEY_F12			0		//0x58 unset


void keyboard_init();
char keyboard_scancode_ascii(u8 scancode);

#endif
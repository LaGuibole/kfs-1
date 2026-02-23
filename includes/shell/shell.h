#ifndef SHELL_H
# define SHELL_H

#include "term.h"
#include "types.h"
#include "vga.h"

#define INPUT_BUFFER_SIZE   246

#define TERM_TAB_COUNT  10
#define PROMPT          "PedrOS >  "  

/* -------------------------- State flags for tabs -------------------------- */
#define TAB_FLAG_HAS_PROMPT 0b00000001

typedef struct s_tabs
{
	u8  cursor_x;
	u8  cursor_y;
	u8 input_buffer[INPUT_BUFFER_SIZE];
	u8  prompt_start_x;
	u8  prompt_start_y;
	u8  state_flags;
	u16 tab_buffer[VGA_HEIGHT][VGA_WIDTH];
	u16 input_len;
}   t_tabs;

typedef struct s_cmd 
{
    const char  *name;
    void        (*handler)(char **args, int argc);
} t_cmd;

extern t_tabs   tabs[TERM_TAB_COUNT];
extern u8   selected_tab;
extern u16 headers[TERM_TAB_COUNT][VGA_WIDTH + 1];

#endif
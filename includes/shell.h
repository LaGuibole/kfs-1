#ifndef SHELL_H
# define SHELL_H

#include "types.h"

#define INPUT_BUFFER_SIZE   242

typedef struct s_cmd 
{
    const char  *name;
    void        (*handler)(char **args, int argc);
} t_cmd;

void cmd_help(char **args, int argc);
void cmd_clear(char **args, int argc);
void cmd_echo(char **args, int argc);
void cmd_tabs(char **args, int argc);
void cmd_dump(char**args, int argc);
void cmd_gdt(char**args, int argc);
void cmd_idt(char **args, int argc);
void cmd_troll(char**args, int argc);

void shell_exec(char *input);

#endif
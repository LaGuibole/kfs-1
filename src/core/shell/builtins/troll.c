#include "shell/shell.h"

void cmd_troll(char **args, int argc)
{
	terminal_putchar('\n');
    (void)args; (void)argc;
    terminal_putstr("                    _____\n");
    terminal_putstr("                 ,-'     `._\n");
    terminal_putstr("               ,'           `.        ,-.\n");
    terminal_putstr("             ,'               \\       ),.\\\n");
    terminal_putstr("   ,.       /                  \\     /(  \\;\n");
    terminal_putstr("  /'\\\\     ,o.        ,ooooo.   \\  ,'  `-')\n");
    terminal_putstr("  )) )`. d8P\"Y8.    ,8P\"\"\"\"\"Y8.  `'  .--\"'\n");
    terminal_putstr(" (`-'   `Y'  `Y8    dP       `'     /\n");
    terminal_putstr("  `----.(   __ `    ,' ,---.       (\n");
    terminal_putstr("         ),--.`.   (  ;,---.        )\n");
    terminal_putstr("        / \\O_,' )   \\  \\O_,'        |\n");
    terminal_putstr("       ;  `-- ,'       `---'        |\n");
    terminal_putstr("       |    -'         `.           |\n");
    terminal_putstr("      _;    ,            )          :\n");
    terminal_putstr("   _.'|     `.:._   ,.:\" `..        |\n");
    terminal_putstr("--'   |   .'     \"\"\"         `      |`.\n");
    terminal_putstr("      |  :;      :   :     _.       |`.`.-'--.\n");
    terminal_putstr("      |  ' .     :   :__.,'|/       |  \\\n");
    terminal_putstr("      `     \\--.__.-'|_|_|-/        /   )\n");
    terminal_putstr("       \\     \\_   `--^\"__,'        ,    |\n");
    terminal_putstr("       ;  `    `--^---'          ,'     |\n");
    terminal_putstr("        \\  `                    /      /\n");
    terminal_putstr("         \\   `    _ _          /\n");
    terminal_putstr("          \\           `       /\n");
    terminal_putstr("           \\           '    ,'\n");
    terminal_putstr("            `.       ,   _,'\n");
    terminal_putstr("              `-.___.---'\n");
    terminal_putstr("\n");
    terminal_putstr("  Somebody once told me the world is gonna roll me...\n");
}
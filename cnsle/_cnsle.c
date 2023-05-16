#include "../_Imports.h"
void Console_print()
{

    initscr();
    getmaxyx(stdscr, MAX_Y, MAX_X);
    endwin();

    for (int i = 0; i < ((MAX_X - strlen(SCRN_TITLE)) / 2); i++)
        printf(" ");
    printf(SCRN_TITLE);
    printf("\nLanguage : %s\n]} INFO: Ecrivez %s pour Quitter le programme. {[\n\n", __Langage, __Console_Exit_Code_P);
}

void Console_readline()
{

    printf("Votre mot }=$ ");

    getline(&mot, &s_mot, stdin);
}
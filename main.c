#include "_Imports.h"

int main()
{
    NewQs();

    s_mot = 1024;
    mot = malloc(s_mot * sizeof(char));
    char *re;

    char ch;
    while (1)
    {
        system("clear");
        printf("1- Console\n2- GUI\n3- Exit\n\tInput: ");
        while (1)
        {
            ch = getchar();

            if (ch == '1')
            {
                system("clear");
                Console_print();
                break;
            }
            else if (ch == '2')
            {
                system("clear");
                scrn_inis();
                break;
            }
            else if (ch == '3')
            {
                system("clear");
                exit(0);
            }
        }
        while (1)
        {

            if (IS_NCURSES) // Avec Interface
            {
                create_win_intrf();
                handle_win();
            }
            else // Console Normale
            {
                Console_readline();
            }

            if (!strcmp(mot, __Console_Exit_Code))
                break;

            switch (CheckWord(mot))
            {
            case -1:
                re = MOT_VIDE;
                break;
            case 0:
                re = MOT_NO;
                break;
            case 1:
                re = MOT_YES;
                break;
            default:
                re = "Erreur\n";
                break;
            }

            if (IS_NCURSES)
                print_TARGET(re);
            else
                printf("%s\n", re);
        }

        if (IS_NCURSES)
        {
            unload_scrn();
            IS_NCURSES = 0;
        }
    }
    if (errno == EINTR)
    {
        system("clear");
    }
    return 0;
}

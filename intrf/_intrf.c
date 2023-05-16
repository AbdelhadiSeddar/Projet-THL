#include "../_Imports.h"
#include "_intrf.h"

int curs, tot;

char *mot;
size_t s_mot;

int MAX_Y, MAX_X;
int TARG_Y, TARG_X;
int WIN_Y, WIN_X;
WINDOW *WIN, *S_WIN;
WINDOW *TARGET_WIN, *S_TARGET_WIN;

int IS_NCURSES = 0;

void scrn_inis()
{
    IS_NCURSES = 1;
    clear();
    initscr();
    getmaxyx(stdscr, MAX_Y, MAX_X);
    SetColors();
    SetBckGrnd();

    raw();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
}

void SetColors()
{

    start_color();
    init_pair(BCKGRND, COLOR_BLACK, COLOR_CYAN);
    init_pair(BCKGRND_WIN, COLOR_RED, COLOR_WHITE);
    init_pair(BCKGRND_TARG, COLOR_BLACK, COLOR_WHITE);
    init_pair(BTN_SELECT, COLOR_WHITE, COLOR_BLUE);
    init_pair(BTN_UNSELECT, COLOR_RED, COLOR_WHITE);

    init_pair(R_BLCK, COLOR_BLACK, COLOR_CYAN);
    init_pair(W_BLCK, COLOR_BLACK, COLOR_WHITE);
    init_pair(R_GREN, COLOR_GREEN, COLOR_CYAN);
    init_pair(W_GREN, COLOR_GREEN, COLOR_WHITE);
}

void ShowInf()
{
    attrset(COLOR_PAIR(R_BLCK));
    mvprintw(0, (MAX_X - strlen(SCRN_TITLE)) / 2, "%s\n", SCRN_TITLE);

    char *help = "Press [ ESC ] to Exit.";
    attrset(COLOR_PAIR(R_BLCK));
    mvprintw(MAX_Y - 1, MAX_X - strlen(help) - 1, "Press [ ");
    attrset(COLOR_PAIR(R_GREN) | A_DIM);
    mvprintw(MAX_Y - 1, MAX_X - strlen(help + 8) - 1, "ESC");
    attrset(COLOR_PAIR(R_BLCK));
    mvprintw(MAX_Y - 1, MAX_X - strlen(help + 12) - 1, "] to Exit.");
}

void SetBckGrnd()
{
    wbkgdset(stdscr, COLOR_PAIR(BCKGRND));
    clear();
}

void create_win_intrf()
{
    ShowInf();

    WIN_X = (MAX_X - 54) / 2;
    WIN_Y = (MAX_Y - 8) / 2;
    S_WIN = newwin(8, 54, WIN_Y + 1, WIN_X + 1);
    WIN = newwin(8, 54, WIN_Y, WIN_X);
    keypad(WIN, TRUE);

    wbkgdset(S_WIN, COLOR_PAIR(SHADOW));
    wbkgdset(WIN, COLOR_PAIR(BCKGRND_WIN));
    wclear(WIN);
    box(WIN, 0, 0);

    wattron(WIN, A_UNDERLINE | A_BLINK);
    mvwprintw(WIN, 0, (54 - strlen("[ Verifier ]")) / 2, "[ Verifier ]");
    wattroff(WIN, A_UNDERLINE | A_BLINK);

    wattron(WIN, A_DIM);
    mvwprintw(WIN, 2, (54 - strlen(__Langage)) / 2, __Langage);
    wattroff(WIN, A_DIM);

    wattrset(WIN, COLOR_PAIR(W_BLCK));
    mvwprintw(WIN, 4, 3, "Votre Mot ~> ");
    wrefresh(S_WIN);
    wrefresh(WIN);
    refresh();
}
void w_clear(WINDOW *__WINDOW, WINDOW *__SHADOW)
{
    clear();
    delwin(__WINDOW);
    delwin(__SHADOW);
    refresh();
}

void unload_scrn()
{
    endwin();
    exit(0);
}

void create_win_target(int Height, int Width, const char *Title, int BTN_TYPE)
{
    w_clear(WIN, S_WIN);

    TARG_X = (MAX_X - Width) / 2;
    TARG_Y = (MAX_Y - Height) / 2;
    S_TARGET_WIN = newwin(Height, Width, TARG_Y + 1, TARG_X + 1);
    TARGET_WIN = newwin(Height, Width, TARG_Y, TARG_X);

    wbkgd(S_TARGET_WIN, COLOR_PAIR(SHADOW));
    wbkgd(TARGET_WIN, COLOR_PAIR(BCKGRND_WIN));
    box(TARGET_WIN, 0, 0);

    mvwprintw(TARGET_WIN, 0, (Width - strlen(Title)) / 2, Title);

    switch (BTN_TYPE)
    {
    case BTN_OK:
        wattron(TARGET_WIN, COLOR_PAIR(BTN_SELECT));
        mvwprintw(TARGET_WIN, Height - 2, (Width - strlen("< Ok >")) / 2, "< Ok >");
        wattroff(TARGET_WIN, COLOR_PAIR(BTN_SELECT));
        break;
    case BTN_OK_CANCEL:
        break;
    case BTN_SUBMIT:
        break;
    case BTN_YES_NO:
        break;

    default:
        break;
    }
    wrefresh(S_TARGET_WIN);
    wrefresh(TARGET_WIN);
}

void handle_win()
{
    wmove(WIN, 4, 15);

    char tmp[1024];

    curs = (tot = 16);
    char ch;
    while (1)
    {
        ch = wgetch(WIN);
        if (ch == KEY_L)
            wmove(WIN, 4, (curs > 15 ? (curs -= 1) : (curs = 14)));
        else if (ch == KEY_R)
            wmove(WIN, 4, (curs != tot ? (curs += 1) : (curs = tot)));
        else if (ch == KEY_ENTR)
        {
            break;
        }
        else if (ch == KEY_ESC)
        {
            unload_scrn();
        }
        else if (IsInAllowedChars((ch)))
        {
            mvwprintw(WIN, 4, curs, "%c", ch);
            mot[curs - 16] = ch;
            if ((curs - 16) == strlen(mot))
                mot[curs - 16 + 1] = '\0';

            curs++;
            tot += (tot <= curs ? 1 : 0);
        }
        wrefresh(WIN);
    }
}
void print_TARGET(const char *__Resultat)
{
    create_win_target(7, strlen(__Resultat) + 6, "{ Resultat }", BTN_OK);
    wattron(TARGET_WIN, A_BOLD | COLOR_PAIR(!strcmp(__Resultat, MOT_YES) ? W_GREN : W_RED));
    mvwprintw(TARGET_WIN, 2, 3, __Resultat);
    wattroff(TARGET_WIN, A_BOLD | COLOR_PAIR(!strcmp(__Resultat, MOT_YES) ? W_GREN : W_RED));
    wrefresh(TARGET_WIN);
    refresh();
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == KEY_ENTR)
        {
            free(mot);
            mot = calloc(s_mot, sizeof(char));
            break;
        }
        else if (ch == KEY_ESC)
        {
            unload_scrn();
        }
    }
    refresh();
}

int IsInAllowedChars(char c)
{
    if (c >= 32 && c <= 57)
        return 1;
    if (c >= 63 && c <= 90)
        return 1;
    if (c >= 95 && c <= 122)
        return 1;

    return 0;
}

#ifndef _INTRF_H
#define _INTRF_H

////////////////////////////////////
///
///     Screen Title
///
////////////////////////////////////

#define SCRN_TITLE "projet THL: Seddar Abdelhadi"

////////////////////////////////////
///
///     Color Pairs
///
////////////////////////////////////

#define BCKGRND 10
#define BCKGRND_WIN 11
#define BCKGRND_TARG 12
#define SHADOW 13

#define R_BLCK 200
#define W_BLCK 201
#define R_GREN 210
#define W_GREN 211
#define W_RED 11

#define BTN_SELECT 34
#define BTN_UNSELECT 35

////////////////////////////////////
///
///     Public Variables
///
////////////////////////////////////

extern int IS_NCURSES;
extern int MAX_Y, MAX_X;
extern int WIN_Y, WIN_X;

extern char *mot;
extern size_t s_mot;

extern WINDOW *WIN, *S_WIN;

////////////////////////////////////
///
///     Public Functions
///
////////////////////////////////////

extern void scrn_inis();
extern void SetColors();

extern void ShowInf();
extern void unload_scrn();

extern void create_win_intrf();
extern void SetBckGrnd();
extern void handle_win();

extern int IsInAllowedChars(char c);
extern void print_TARGET(const char *__Resultat);
////////////////////////////////////
///
///     Public KeyBinds
///
////////////////////////////////////

#define KEY_U 3
#define KEY_D 2
#define KEY_L 4
#define KEY_R 5

#define KEY_F12 20

#define KEY_ENTR 10
#define KEY_ESC 27
#define KEY_DEL 7

////////////////////////////////////
///
///     Public Button Types
///
////////////////////////////////////

#define BTN_NULL -1
#define BTN_OK 0
#define BTN_OK_CANCEL 1
#define BTN_YES_NO 2
#define BTN_SUBMIT 3
#endif
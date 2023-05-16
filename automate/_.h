#ifndef _H
#define _H

////////////////////////////////////
///
///     Public Macros
///
///     _e_ -> Index De la fin (Epsilon)
///     _v_e_ -> Valeur D'epsilon
///
////////////////////////////////////

/// Epsilon

#define _e_ -1
#define _v_e_ '\0'

/// Text Output

#define MOT_VIDE "Mot Vide."
#define MOT_NO "Mot Appartient pas."
#define MOT_YES "Mot Appartient."

////////////////////////////////////
///
///     Declaration Type
///
////////////////////////////////////

typedef struct AUTOMATE_T
{
    int n_Next;

    char *c;
    int *Next;
} Q;

////////////////////////////////////
///
///     Public Variables
///
////////////////////////////////////

extern char *__Langage;

////////////////////////////////////
///
///     Public Functions
///
////////////////////////////////////

extern void NewQs();
extern int ExistNextC(int _Index_Current, char _Character, int *_Index_Next);
extern int CheckWord(char *__Word);

#endif

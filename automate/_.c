#include "../_Imports.h"

Q *q = NULL;

int __N_Etas_Debut = 1;
int *__Etas_Debut;

int __Etas;
char *__Langage;

Q NewQ(char *__Characteres_Possibles, int __Nombre_Possibilites)
{
    Q q;
    q.n_Next = __Nombre_Possibilites;

    q.c = calloc(__Nombre_Possibilites, sizeof(char));
    q.Next = calloc(__Nombre_Possibilites, sizeof(int));

    strncpy(q.c, __Characteres_Possibles, __Nombre_Possibilites);
    return q;
}
/*
    q[n] = NewQ("abc...", m);
    q[n].Next[0] = n1;
    q[n].Next[1] = n2;
    .
    .
    .
    q[n].Next[0] = nm;
*/
void NewQs()
{
    __Langage = "L = {ba^(n) / n >= 0}";

    __Etas = 2;
    q = calloc(__Etas, sizeof(Q));

    q[0] = NewQ("b", 1);
    q[0].Next[0] = 1;

    q[1] = NewQ("a\0", 2);
    q[1].Next[0] = 1;
    q[1].Next[1] = _e_;

    __N_Etas_Debut = 1;
    __Etas_Debut = calloc(__N_Etas_Debut, sizeof(int));

    __Etas_Debut[0] = 0;
}

int ExistNextC(int _Current_Index, char _Character, int *_Index_Next)
{
    for (int i = 0; i < q[_Current_Index].n_Next; i++)
    {
        if (q[_Current_Index].c[i] == _Character)
        {
            if (_Index_Next != NULL)
                *_Index_Next = i;
            return 1;
        }
    }
    return 0;
}

int CheckWord_R(char *__Word, int __Current_Index, int *_Store_Index)
{
    if ((!strcmp(__Word, "\n") || !strcmp(__Word, "\0")))
        if (ExistNextC(__Current_Index, _v_e_, NULL))
            return 1;
        else
            return 0;

    if (ExistNextC(__Current_Index, __Word[0], _Store_Index))
    {
        return CheckWord_R(__Word + 1, q[__Current_Index].Next[*_Store_Index], _Store_Index);
    }
    return 0;
}

int CheckWord(char *_Word)
{
    if (!strcmp(_Word, "\n") || !strcmp(_Word, "\0"))
    {
        for (int u = 0; u < __N_Etas_Debut; u++)
            if (ExistNextC(__Etas_Debut[u], _v_e_, NULL))
                return 1;
        return -1;
    }

    int i, re = 0;

    for (int u = 0; u < __N_Etas_Debut; u++)
        if (ExistNextC(__Etas_Debut[u], _Word[0], &i))
        {
            re = CheckWord_R(_Word + 1, q[0].Next[i], &i);
            if (re)
                return re;
        }
    return 0;
}

#ifndef _CNSLE_H
#define _CNSLE_H

////////////////////////////////////
///
///     Public Macros
///
////////////////////////////////////

#define __Console_Exit_Code "@exit\n"
#define __Console_Exit_Code_P "@exit"

////////////////////////////////////
///
///     Public Functions
///
////////////////////////////////////

extern void Console_print();
extern void Console_readline();

#endif
#include "exec.h"

/**
** @brief Execute the do_group rule
*/

extern s_global *g_global;
int exec_dogroup(s_list *dogroup)
{
    return exec_compound(dogroup->brothers->son_list);
}

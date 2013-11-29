#include "exec.h"

extern s_global *g_global;
int exec_dogroup(s_list *dogroup)
{
    return exec_compound(dogroup->brothers->son_list);
}

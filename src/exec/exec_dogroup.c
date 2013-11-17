#include "exec.h"

int exec_dogroup(s_list *dogroup)
{
    /* return exec of son's first brother which is a compound list */
    return exec_compound(dogroup->brothers->node->son_list);
}

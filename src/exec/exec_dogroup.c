#include "exec.h"

/**
** @brief Execute the do_group rule
*/
int exec_dogroup(s_list *dogroup)
{
    return exec_compound(dogroup->brothers->son_list);
}

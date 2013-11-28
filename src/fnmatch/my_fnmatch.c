#include "fn_match.h"
#include "my_fnmatch.h"

int my_fnmatch(const char *pattern, const char *string)
{
    if (pattern == NULL || string == NULL)
        return 1;
    if (pattern[0] != '.' && string[0] == '.')
        return 1;
    int r_val = 0;
    s_queue *queue = NULL;
    queue = init_queue();
    parser(queue, pattern);
    r_val = match(queue->head, string);
    free_queue_match(queue);
    free(queue);
    return r_val;
}

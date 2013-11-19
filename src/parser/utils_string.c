#include <ctype.h>
#include "utils_string.h"

/**
** @brief Checks if a string is actually a number
*/

bool my_isdigit(char *s)
{
    if (s[0] == '\0')
        return false;

    for (int i = 0; s[i]; ++i)
      if (!isdigit(s[i]))
            return false;
        return true;
}

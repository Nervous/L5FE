#include <ctype.h>
#include "utils_string.h"

bool my_isdigit(char *s)
{
    if (s[0] == '\0')
        return false;

    for (int i = 0; s[i]; ++i)
      if (!isdigit(s[i]))
            return false;
        return true;
}

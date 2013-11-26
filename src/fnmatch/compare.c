#include "fifo.h"

static int only_stars(s_list *list)
{
  while (list != NULL && list->star == 1)
    list = list->next;

  if (list == NULL)
    return 0;
  else
    return 1;
}

static int star_loop(s_list *list, const char *str, int index)
{

  if (!compare(list->next, str, index))
    return 0;
  else
    {
      if (str[index] == '\0')
	return 1;
      return (star_loop(list, str, index+1));
    }
}

int compare(s_list *list, const char *str, int i)
{
  while (list != NULL && str[i] != '\0')
    {
      if (list->star)
	return star_loop(list, str, i);

      int index = str[i];
      if (list->array[index] == 0)
	return 1;
      list = list->next;
      i++;
    }

  if (list != NULL)
    return only_stars(list);
  else if (str[i] != '\0')
    return 1;
  else
    return 0;
}

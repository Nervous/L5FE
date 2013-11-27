#include <string.h>
#include "my_fnmatch.h"
#include "../struct.h"

extern s_global *g_global;

static void free_dir_list2(char **dir_list2)
{
    for (int i = 0; dir_list2[i] != NULL; i++)
        free(dir_list2[i]);
    free(dir_list2);
}

static char *free_concat_slashs(char *str1, char *str2, int slashs, int b_free)
{
    int index = 0;
    int len = strlen(str1) + strlen(str2) + slashs + 1; //for '\0'
    char *result = malloc(len * sizeof (char));
    for (unsigned int i = 0; i < strlen(str1); i++)
    {
        result[index] = str1[i];
        index++;
    }
    for (int i = 0; i <= slashs; i++)
    {
        result[index] = '/';
        index++;
    }
    for (unsigned int i = 0; i < strlen(str2) + 1; i++) //+1 to get '\0'
    {
        result[index] = str2[i];
        index++;
    }
    if (b_free)
    {
        free(str1);
        free(str2);
    }
    return result;
}

static char *return_empty()
{
    char *res = malloc(sizeof (char));
    res[0] = '\0';
    return res;
}


static char *my_concat(char *str1, char *str2)
{
    if (str2[0] == '\0')
    {
        free(str2);
        return str1;
    }
    int index = 0;
    int len = strlen(str1) + strlen(str2) + 2; //for '\0'
    char *result = malloc(len * sizeof (char));
    for (unsigned int i = 0; i < strlen(str1); i++)
    {
        result[index] = str1[i];
        index++;
    }
    result[index] = ' ';
    index++;
    for (unsigned int i = 0; i < strlen(str2) + 1; i++) //+1 to get '\0'
    {
        result[index] = str2[i];
        index++;
    }
    free(str1);
    free(str2);
    return result;
}
static void free_my_var(char *tofree1, char* tofree2, char *tofree3, char**fr)
{
    free(tofree1);
    free(tofree2);
    free(tofree3);
    free_dir_list2(fr);
}

static char *path_exp_rec(char *pwd, char *current_dir,
    char *pattern, int slashs)
{
    char *c_dir = NULL;
    char *result;
    char *tmp = free_concat_slashs(pwd, current_dir, 0, 0);
    char **dir_list2 = get_dir_list2(tmp);
    free(tmp);
    int sep_pos = 0;
    int slash_count = 0;
    while (pattern[sep_pos] != '\0' && pattern[sep_pos] != '/')
        sep_pos++;
    if (pattern[sep_pos] == '\0')
        return return_empty();
    while (pattern[sep_pos++] == '/')
        slash_count++;
    char *c_pattern = strdup(pattern);
    c_pattern[sep_pos - slash_count + 1] = '\0';
    char *rem_pattern = strdup(&(pattern[sep_pos + 1]));
    for (int i = 0; dir_list2[i] != NULL; i++)
        if (my_fnmatch(c_pattern, dir_list2[i]))
        {
            c_dir = free_concat_slashs(current_dir, c_pattern, slashs, 0);
            tmp = path_exp_rec(pwd, c_dir, rem_pattern, slash_count);
            result = my_concat(result, tmp);
        }
    free_my_var(c_pattern, rem_pattern, c_dir, dir_list2);
    return result;
}

char *path_exp(char* str)
{
    if (str != NULL)
    {
        int sep_pos = 0;
        int slash_count = 0;
        while (str[sep_pos] != '\0' && str[sep_pos] != '/')
            sep_pos++;
        while (str[sep_pos] == '\0')
            slash_count++;
        return path_exp_rec(g_global->current_dir, "", str, 0);
    }
    return NULL;
}
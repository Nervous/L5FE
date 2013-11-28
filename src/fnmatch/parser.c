#include "fn_match.h"

static void add_elem(int array[], char index)
{
    int i = index;
    array[i] = 1;
}

static void add_rangelem(int array[], int start, int end)
{
    for (int i = start; i < end; i++)
        array[i] = 1;
}

static void reverse(int array[])
{
    for (int i = 0; i < 128; i++)
        array[i] = (array[i] == 0) ? 1 : 0;
}

static int check_is_close(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ']' && i == 1 && str[0] == '!')
            continue;
        if (str[i] == ']' && i != 0)
            return 1;
    }
    return 0;
}

static void loop_range_atexit(s_queue *queue, char start_range, int is_reverse)
{
    if (start_range != -1)
    {
        add_elem(queue->tail->array_char, '-');
        add_elem(queue->tail->array_char, start_range);
    }
    if (is_reverse)
        reverse(queue->tail->array_char);
}

static void loop_range(s_queue *queue, const char *str, int *i)
{
    int is_first = 1;
    int is_reverse = 0;
    char start_range = -1;

    add_queue(queue, 0);
    while ((str[*i] != ']' && str[*i] != '\0') || is_first)
    {
        if (start_range != -1)
        {
            add_rangelem(queue->tail->array_char, start_range, str[*i] + 1);
            start_range = -1;
        }
        else if (is_first && str[*i] == '!' && is_reverse == 0)
        {
            is_reverse = 1;
            *i = *i + 1;
            continue;
        }
        else if (str[*i + 1] == '-')
        {
            start_range = str[*i];
            *i = *i + 1;
        }
        else
            add_elem(queue->tail->array_char, str[*i]);
        is_first = 0;
        *i = *i + 1;
    }
    loop_range_atexit(queue, start_range, is_reverse);
    if (str[*i] == '\0')
        *i = *i - 1;
}

static void parser_again(s_queue *queue, const char *str, int *i, int *is_char)
{
    if (str[*i] == '?')
    {
        add_queue(queue, 0);
        add_rangelem(queue->tail->array_char, 0, 128);
    }
    else if (str[*i] == '\\' && str[*i + 1] != '\0' && (str[*i + 1] == '*' 
                || str[*i + 1] == '?' || str[*i + 1] == '['))
        *is_char = 1;
    else if (str[*i] == '[' && check_is_close(&str[*i + 1]))
    {
        *i = *i + 1;
        loop_range(queue, str, i);
    }
    else
    {
        add_queue(queue, 0);
        add_elem(queue->tail->array_char, str[*i]);
    }

}

int parser(s_queue *queue, const char *str)
{
    int is_char = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (is_char)
        {
            add_queue(queue, 0);
            add_elem(queue->tail->array_char, str[i]);
            is_char = 0;
        }
        else if (str[i] == '*')
            add_queue(queue, 1);
        else
            parser_again(queue, str, &i, &is_char);
    }
    return 0;
}

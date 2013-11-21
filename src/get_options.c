#include "get_options.h"
#include "readline/readline.c"
#include "exec/exec.h"

extern s_global *g_global;

static void load_config();

/**
 ** @brief Display the Usage message on the standard error output
 */

static int print_usage(char * msg, char *str)
{
    fprintf(stderr, msg, str);
    fprintf(stderr, "Usage : 42sh [options] [file]\n");
    return 2;
}

static char *get_string(int argc, char **argv, int i)
{
    int cur_arg = i;
    int count = 0;

    for (; cur_arg < argc; cur_arg++)
    {
        for (unsigned int j = 0; j < strlen(argv[cur_arg]); j++)
            count++;
        count++;
    }

    char *value = malloc(sizeof (char) * count);
    value = strcpy(value, argv[i]);
    for (cur_arg = i + 1; cur_arg < argc; cur_arg++)
    {
        value = strcat(value, " ");
        value = strcat(value, argv[cur_arg]);
    }
    value[count] = '\0';

    return value;
}

static int options2(int argc, char **argv, int i)
{
    if (strcmp(argv[i], "-c") == 0)
    {
        if (i + 1 < argc)
        {
            if (g_global->norc != 1)
                load_config();
            g_global->readline = get_string(argc, argv, i + 1);
            parse();
            return -1;
        }
        else
            return print_usage("%s option needs a parameter\n", argv[i]);
    }
    else if (strcmp(argv[i], "-O") == 0 || strcmp(argv[i], "+O") == 0)
    {
        if (i + 1 < argc)
        {
            return 0;
        }
        else
            return print_usage("%s option needs a parameter\n", argv[i]);
    }

    return print_usage("Option %s is not a valid option\n", argv[i]);
}

/**
 ** @brief Compare the current option to every known option and perform the
 ** appropriate action
 */

static int options(int argc, char **argv, int i)
{
    if (strcmp(argv[i], "--version") == 0)
    {
        printf("Version 0.5\n");
        exit(0);
        /* NEED TO FREE GLOBAL */
    }
    else if (strcmp(argv[i], "--ast-print") == 0)
    {
        g_global->ast = 1;
        return 0;
    }
    else if (strcmp(argv[i], "--norc") == 0)
    {
        g_global->norc = 1;
        return 0;
    }

    return options2(argc, argv, i);
}

/**
 ** @brief Reads the file passed as an argument to 42sh and stores it into a
 ** single single to parse and execute
 */

static int get_file(char *filename, bool config)
{
    FILE *file;

    if ((file = fopen(filename, "r")) == NULL)
    {
        if (config)
            return -4242;
        fprintf(stderr, "%s: File not found\n", filename);
        exit(127);
    }

    char *value = malloc(sizeof (char));
    value = strcpy(value, "");
    char *tmp = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&tmp, &len, file)) != -1)
    {
        value = realloc(value, sizeof (char) * (strlen(value) + len));
        value = strcat(value, tmp);
    }

    g_global->readline = value;
    g_global->file = 1;

    fclose(file);
    free(tmp);

    return parse();
}

void load_config()
{
    get_file("etc/42shrc", true);
    exec_input(get_root(g_global->current_node));
    release_ast(get_root(g_global->current_node));
    g_global->current_node = NULL;
    g_global->pos = 0;

    char *home = getenv("HOME");
    char *buf = malloc(sizeof (char) * (strlen(home) + 9));
    strcpy(buf, home);
    strcat(buf, "/.42shrc");
    get_file(buf, true);
    free(buf);
    g_global->pos = 0;

    exec_input(get_root(g_global->current_node));
    release_ast(get_root(g_global->current_node));
    g_global->current_node = NULL;
}

/**
 ** @brief Parses the argument passed to 42sh to find the options. If no
 ** argument is provided, 42sh will run in interactive mode
 */

int get_options(int argc, char **argv)
{
    if (argc == 1)
    {
        load_config();
        readline();
        return 0;
    }

    int ret;

    for (int i = 1; i < argc; i++)
        if (strncmp(argv[i], "-", 1) == 0 || strncmp(argv[i], "+", 1) == 0)
        {
            if ((ret = options(argc, argv, i)) != 0)
                return ret + (ret == -1);
        }
        else
        {
            if (g_global->norc != 1)
                load_config();
            return get_file(argv[i], false);
        }

    if (g_global->norc != 1)
        load_config();
    readline();
    return 0;
}

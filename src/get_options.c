#include "get_options.h"

extern s_global *g_global;

/**
** @brief Display the Usage message on the standard error output
*/

static int print_usage(char * msg, char *str)
{
    fprintf(stderr, msg, str);
    fprintf(stderr, "Usage : 42sh [options] [file]\n");
    return 2;
}

/* static char *get_string(int argc, char **argv, int i) */
/* { */
/*     int cur_arg = i + 1; */
/*     int count = 0; */

/*     for (; cur_arg < argc; cur_arg++) */
/*     { */
/*         for (unsigned int j = 0; j < strlen(argv[cur_arg]); j++) */
/*             count++; */
/*         count++; */
/*     } */

/*     char *value = malloc(sizeof (char) * count); */
/*     value = strcpy(value, argv[i]); */
/*     for (cur_arg = i + 1; cur_arg < argc; cur_arg++) */
/*     { */
/*         value = strcat(value, " "); */
/*         value = strcat(value, argv[cur_arg]); */
/*     } */

/*     return value; */
/* } */

/* static int options2(int argc, char **argv, int i) */
/* { */
/*     if (strcmp(argv[i], "-c") == 0) */
/*     { */
/*         if (i + 1 < argc) */
/*         { */
/*             /\* Need to be updated to reflect the correct behaviour of 42sh*\/ */
/*             g_global->readline = get_string(argc, argv, i + 1); */
/*             parse(); */
/*             return -1; */
/*         } */
/*         else */
/*             return print_usage("%s option needs a parameter\n", argv[i]); */
/*     } */
/*     else if (strcmp(argv[i], "-O") == 0 || strcmp(argv[i], "+O") == 0) */
/*     { */
/*         if (i + 1 < argc) */
/*         { */
/*             /\* Not implemented yet *\/ */
/*             parse(); */
/*             return 42; */
/*         } */
/*         else */
/*             return print_usage("%s option needs a parameter\n", argv[i]); */
/*     } */

/*     return print_usage("Option %s is not a valid option\n", argv[i]); */
/* } */

/* /\** */
/* ** @brief Compare the current option to every known option and perform the */
/* ** appropriate action */
/* *\/ */

/* static int options(int argc, char **argv, int i) */
/* { */
/*     if (strcmp(argv[i], "--version") == 0) */
/*     { */
/*         printf("Version 0.5\n"); */
/*         exit(0); /\* NEED TO FREE GLOBAL *\/ */
/*     } */
/*     else if (strcmp(argv[i], "--ast-print") == 0) */
/*     { */
/*         g_global->ast = 1; */
/*         return 0; */
/*     } */
/*     else if (strcmp(argv[i], "--norc") == 0) */
/*     { */
/*         g_global->norc = 1; */
/*         return 0; */
/*     } */

/*     return options2(argc, argv, i); */
/* } */

/* /\** */
/* ** @brief Reads the file passed as an argument to 42sh and stores it into a */
/* ** single single to parse and execute */
/* *\/ */

/* int get_file(char *filename) */
/* { */
/*     FILE *file; */

/*     if ((file = fopen(filename, "r")) == NULL) */
/*     { */
/*         fprintf(stderr, "%s: File not found\n", filename); */
/*         exit(127); */
/*     } */

/*     /\*size_t size = 1024; */
/*     char *buf = malloc(sizeof (char) * size); */
/*     char *value = malloc(sizeof (char) * size); */
/*     while (fgets(buf, size, file) != NULL) */
/*     { */
/*         if (strlen(value) + strlen(buf) > size) */
/*         { */
/*             value = realloc(buf, 1024); */
/*             size += 1024; */
/*         } */
/*         value = strcat(value, buf); */
/*     }*\/ */

/*     char *value = malloc(sizeof (char)); */
/*     char *tmp = NULL; */
/*     size_t len = 0; */
/*     ssize_t read; */

/*     while ((read = getline(&tmp, &len, file)) != -1) */
/*     { */
/*         value = realloc(value, sizeof (char) * (strlen(value) + len)); */
/*         value = strcat(value, tmp); */
/*     } */

/*     g_global->readline = value; */

/*     return parse(); */
/* } */

/* /\** */
/* ** @brief Parses the argument passed to 42sh to find the options. If no */
/* ** argument is provided, 42sh will run in interactive mode */
/* *\/ */

/* int get_options(int argc, char **argv) */
/* { */
/*     if (argc == 1) */
/*     { */
/*         return 42; //calling readline */
/*         //readline(); */
/*     } */

/*     int ret; */

/*     for (int i = 1; i < argc; i++) */
/*     { */
/*         char *opt = argv[i]; */
/*         if (strncmp(opt, "-", 1) == 0 || strncmp(opt, "+", 1) == 0) */
/*         { */
/*             if ((ret = options(argc, argv, i)) != 0) */
/*                 return ret + (ret == -1); */
/*         } */
/*         else */
/*             return get_file(argv[i]); //executing first arg as command file */
/*     } */

/*     //calling readline */
/*     //readline(); */
/*     return 42; */
/* } */

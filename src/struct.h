typedef struct token
{
    int type;
    char *content;
    struct list *son_list;
} s_token;

typedef struct list
{
    s_token *node;
    struct list *next;
} s_list;

#include <minishell.h>

// <

void make_input(t_list *token, t_minishell *data)
{
    char *name;
    int fd;

    (void)data;
    name = token->next->value;
    fd = open(token->next->value, O_RDONLY);
    if (fd == -1)
    {
        dprintf(2, "bash: %s: No such file or directory\n", name);
        exit(1);
    }
}
